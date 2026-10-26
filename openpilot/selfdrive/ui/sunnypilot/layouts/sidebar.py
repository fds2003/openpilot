"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
import math

import pyray as rl
from dataclasses import dataclass
from openpilot.selfdrive.ui.ui_state import ui_state, ChestnutState
from openpilot.system.ui.lib.application import gui_app, FontWeight
from openpilot.system.ui.lib.multilang import tr_noop
from openpilot.system.ui.lib.text_measure import measure_text_cached


METRIC_HEIGHT = 126
METRIC_MARGIN = 30
METRIC_START_Y = 300
HOME_BTN = rl.Rectangle(60, 860, 180, 180)

CHESTNUT_ICON_WIDTH = 180
CHESTNUT_ICON_HEIGHT = 133

# eGPU 状态框：与上方指标框同款（圆角边框 + 左侧色条），位于 GPU 图标上方
METRIC_WIDTH = 240
# 无 eGPU 框时保持原来的三框布局；有 eGPU 框时四个框同尺寸、等间距排布：
# 300/442/584/726，间距 16，末框止于 852，距 HOME 按钮(860) 8 px。
# 300 以下是空档(上面是 IP 文本 y=247、麦克风指示 y=245，到 ~285 结束)。
METRIC_START_Y = 300
EGPU_STATUS_BOX_HEIGHT = METRIC_HEIGHT   # 与指标框同尺寸
EGPU_STATUS_BOX_GAP = 8                  # 末框与 HOME 按钮的间距
METRIC_BOX_GAP = 16                      # 四个框之间的等间距(排布公式据此算出)
EGPU_STATUS_FONT_SIZE = 30
BASE_METRIC_OFFSETS = (338, 496, 654)    # 没有 eGPU 框时的原始位置


# Color scheme
class Colors:
  WHITE = rl.WHITE
  WHITE_DIM = rl.Color(255, 255, 255, 85)
  GRAY = rl.Color(84, 84, 84, 255)

  # Status colors
  GOOD = rl.WHITE
  WARNING = rl.Color(218, 202, 37, 255)
  DANGER = rl.Color(201, 34, 49, 255)
  PROGRESS = rl.Color(0, 134, 233, 255)   # eGPU 加载中

  # eGPU 状态框左侧色条（与 GPU 图标配色一致）
  EGPU_GREEN = rl.Color(67, 217, 108, 255)

  # UI elements
  METRIC_BORDER = rl.Color(255, 255, 255, 85)
  BUTTON_NORMAL = rl.WHITE
  BUTTON_PRESSED = rl.Color(255, 255, 255, 166)


@dataclass(slots=True)
class MetricData:
  label: str
  value: str
  color: rl.Color

  def update(self, label: str, value: str, color: rl.Color):
    self.label = label
    self.value = value
    self.color = color


class SidebarSP:
  def __init__(self):
    self._chestnut_green_img = gui_app.texture("icons_mici/chestnut_green.png", CHESTNUT_ICON_WIDTH, CHESTNUT_ICON_HEIGHT)
    self._chestnut_default_img = gui_app.texture("icons_mici/chestnut.png", CHESTNUT_ICON_WIDTH, CHESTNUT_ICON_HEIGHT)
    self._chestnut_orange_img = gui_app.texture("icons_mici/chestnut_orange.png", CHESTNUT_ICON_WIDTH, CHESTNUT_ICON_HEIGHT)

  def _get_home_icon(self, default_img: rl.Texture) -> tuple[rl.Texture, rl.Vector2, float]:
    default_pos = rl.Vector2(HOME_BTN.x, HOME_BTN.y)
    state = ui_state.chestnut_state
    if state == ChestnutState.DISCONNECTED:
      return default_img, default_pos, 1.0

    if state == ChestnutState.LOADING:
      icon = self._chestnut_default_img
      opacity = 0.35 + 0.65 * (0.5 - 0.5 * math.cos(rl.get_time() * 6.0))
    elif state in (ChestnutState.UNCOMPILED, ChestnutState.FAILED):
      icon, opacity = self._chestnut_orange_img, 1.0
    else:
      icon, opacity = self._chestnut_green_img, 1.0

    x = HOME_BTN.x + (HOME_BTN.width - icon.width) / 2
    y = HOME_BTN.y + (HOME_BTN.height - icon.height) / 2
    return icon, rl.Vector2(x, y), opacity

  def _egpu_status_visible(self) -> bool:
    """仅在 eGPU 真的接上并跑着时才显示状态框。"""
    if ui_state.chestnut_state == ChestnutState.DISCONNECTED or not ui_state.chestnut_present:
      return False
    # chestnutState 在大模型运行期间会被监控线程主动停发（modeld 独占 eGPU 的 USB 接口），
    # 而那正是最需要显示状态框的时候。这时改用 modeld 自己发布的 chestnutGpuState。
    return bool(ui_state.sm.seen.get('chestnutState') or ui_state.sm.seen.get('chestnutGpuState'))

  def _draw_egpu_status(self, rect: rl.Rectangle) -> None:
    """GPU 图标上方的 eGPU 状态框：第一行 当前功率+温度，第二行 频率。

    样式与上方指标框一致（圆角边框 + 左侧色条）。未接 eGPU 或读不到遥测时整块不绘制。
    """
    sm = ui_state.sm
    if not self._egpu_status_visible():
      return
    try:
      if sm.alive.get('chestnutState') and sm.valid.get('chestnutState'):
        cs = sm['chestnutState']
      elif sm.alive.get('chestnutGpuState'):
        cs = sm['chestnutGpuState']
      else:
        return
      line1 = f"{cs.powerDrawW:.0f}W/{cs.tempC:.0f}°C"
      line2 = f"{cs.gpuClockMhz:.0f}MHz"
    except Exception:
      return

    box = rl.Rectangle(rect.x + METRIC_MARGIN,
                       int(HOME_BTN.y) - EGPU_STATUS_BOX_HEIGHT - EGPU_STATUS_BOX_GAP,
                       METRIC_WIDTH, EGPU_STATUS_BOX_HEIGHT)

    # 左侧色条：与 GPU 图标状态一致（在线绿 / 加载中蓝 / 异常黄）
    state = ui_state.chestnut_state
    if state == ChestnutState.LOADING:
      bar_color = Colors.PROGRESS
    elif state in (ChestnutState.UNCOMPILED, ChestnutState.FAILED):
      bar_color = Colors.WARNING
    else:
      bar_color = Colors.EGPU_GREEN

    edge_rect = rl.Rectangle(box.x + 4, box.y + 4, 100, EGPU_STATUS_BOX_HEIGHT - 8)
    rl.begin_scissor_mode(int(box.x + 4), int(box.y), 18, int(box.height))
    rl.draw_rectangle_rounded(edge_rect, 0.3, 10, bar_color)
    rl.end_scissor_mode()

    # 边框
    rl.draw_rectangle_rounded_lines_ex(box, 0.3, 10, 2, Colors.METRIC_BORDER)

    # 两行文字（框内垂直居中，水平居中于色条右侧区域）
    font = gui_app.font(FontWeight.SEMI_BOLD)
    sizes = [measure_text_cached(font, t, EGPU_STATUS_FONT_SIZE) for t in (line1, line2)]
    total_h = sum(s.y for s in sizes)
    ty = box.y + (box.height / 2 - total_h / 2)
    for text, size in zip((line1, line2), sizes):
      pos = rl.Vector2(box.x + 22 + (box.width - 22 - size.x) / 2, ty)
      rl.draw_text_ex(font, text, pos, EGPU_STATUS_FONT_SIZE, 0, Colors.WHITE)
      ty += size.y

  def _metric_slot_ys(self, rect: rl.Rectangle, count: int) -> list[float]:
    """指标框(含 eGPU 框)的绝对 y 坐标。

    count==3 时保持基类原来的 338/496/654；count==4(接了 eGPU)时四个框同尺寸、
    等间距地从 300 排到 852，间距由公式算出(当前参数下为 16)。
    """
    if count <= 3:
      return [rect.y + o for o in BASE_METRIC_OFFSETS]
    top = rect.y + METRIC_START_Y
    bottom = HOME_BTN.y - EGPU_STATUS_BOX_GAP - METRIC_HEIGHT
    step = (bottom - top) / (count - 1)
    return [top + i * step for i in range(count)]

  def _draw_metrics_w_sunnylink(self, rect: rl.Rectangle, _temp, _panda, _connect):
    metrics = [_temp, _panda, _connect]  # sunnylink status hidden
    start_y = int(rect.y) + METRIC_START_Y
    # eGPU 在线时底部给状态框让位（指标框整体上移），未接 eGPU 时恢复常规排布
    reserve = (EGPU_STATUS_BOX_HEIGHT + EGPU_STATUS_BOX_GAP + METRIC_BOX_GAP) if self._egpu_status_visible() else METRIC_MARGIN
    available_height = max(0, int(HOME_BTN.y) - reserve - METRIC_HEIGHT - start_y)
    spacing = available_height / max(1, len(metrics) - 1)

    self._draw_egpu_status(rect)
    return metrics, start_y, spacing
