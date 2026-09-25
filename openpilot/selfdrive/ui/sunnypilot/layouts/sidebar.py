"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
import math

import pyray as rl
import time
from dataclasses import dataclass
from openpilot.selfdrive.ui.ui_state import ui_state, ChestnutState
from openpilot.sunnypilot.sunnylink.api import UNREGISTERED_SUNNYLINK_DONGLE_ID
from openpilot.system.ui.lib.application import gui_app, FontWeight
from openpilot.system.ui.lib.multilang import tr_noop
from openpilot.system.ui.lib.text_measure import measure_text_cached


PING_TIMEOUT_NS = 80_000_000_000  # 80 seconds in nanoseconds
METRIC_HEIGHT = 126
METRIC_MARGIN = 30
METRIC_START_Y = 300
HOME_BTN = rl.Rectangle(60, 860, 180, 180)

CHESTNUT_ICON_WIDTH = 180
CHESTNUT_ICON_HEIGHT = 133

# eGPU 状态框：与上方指标框同款（圆角边框 + 左侧色条），位于 GPU 图标上方
METRIC_WIDTH = 240
EGPU_STATUS_BOX_HEIGHT = 126      # 与 METRIC_HEIGHT 一致，视觉上成一组
EGPU_STATUS_BOX_GAP = 8           # 与 HOME 按钮的间距
METRIC_BOX_GAP = 20               # 指标框与 eGPU 框的间距
EGPU_STATUS_FONT_SIZE = 30


# Color scheme
class Colors:
  WHITE = rl.WHITE
  WHITE_DIM = rl.Color(255, 255, 255, 85)
  GRAY = rl.Color(84, 84, 84, 255)

  # Status colors
  GOOD = rl.WHITE
  WARNING = rl.Color(218, 202, 37, 255)
  DANGER = rl.Color(201, 34, 49, 255)
  PROGRESS = rl.Color(0, 134, 233, 255)
  DISABLED = rl.Color(128, 128, 128, 255)

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
    self._sunnylink_status = MetricData(tr_noop("SUNNYLINK"), tr_noop("OFFLINE"), Colors.WARNING)
    self._chestnut_green_img = gui_app.texture("icons_mici/chestnut_green.png", CHESTNUT_ICON_WIDTH, CHESTNUT_ICON_HEIGHT)
    self._chestnut_default_img = gui_app.texture("icons_mici/chestnut.png", CHESTNUT_ICON_WIDTH, CHESTNUT_ICON_HEIGHT)
    self._chestnut_orange_img = gui_app.texture("icons_mici/chestnut_orange.png", CHESTNUT_ICON_WIDTH, CHESTNUT_ICON_HEIGHT)

  def _update_sunnylink_status(self):
    if not ui_state.params.get_bool("SunnylinkEnabled"):
      self._sunnylink_status.update(tr_noop("SUNNYLINK"), tr_noop("DISABLED"), Colors.DISABLED)
      return

    last_ping = ui_state.params.get("LastSunnylinkPingTime") or 0
    dongle_id = ui_state.params.get("SunnylinkDongleId")

    is_online = last_ping and (time.monotonic_ns() - last_ping) < PING_TIMEOUT_NS
    is_temp_fault = ui_state.params.get_bool("SunnylinkTempFault")
    is_registering = not is_temp_fault and dongle_id in (None, "", UNREGISTERED_SUNNYLINK_DONGLE_ID)

    # Determine status/color pair based on priority
    if last_ping:
      status, color = (tr_noop("ONLINE"), Colors.GOOD) if is_online else (tr_noop("ERROR"), Colors.DANGER)
    elif is_temp_fault:
      status, color = (tr_noop("FAULT"), Colors.WARNING)
    elif is_registering:
      status, color = (tr_noop("REGIST..."), Colors.PROGRESS)
    else:
      status, color = (tr_noop("OFFLINE"), Colors.DANGER)

    self._sunnylink_status.update(tr_noop("SUNNYLINK"), status, color)

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
    return bool(ui_state.sm.seen.get('chestnutState'))

  def _draw_egpu_status(self, rect: rl.Rectangle) -> None:
    """GPU 图标上方的 eGPU 状态框：第一行 当前功率+温度，第二行 频率。

    样式与上方指标框一致（圆角边框 + 左侧色条）。未接 eGPU 或读不到遥测时整块不绘制。
    """
    sm = ui_state.sm
    if not self._egpu_status_visible():
      return
    try:
      cs = sm['chestnutState']
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

  def _draw_metrics_w_sunnylink(self, rect: rl.Rectangle, _temp, _panda, _connect):
    metrics = [_temp, _panda, _connect]  # sunnylink status hidden
    start_y = int(rect.y) + METRIC_START_Y
    # eGPU 在线时底部给状态框让位（指标框整体上移），未接 eGPU 时恢复常规排布
    reserve = (EGPU_STATUS_BOX_HEIGHT + EGPU_STATUS_BOX_GAP + METRIC_BOX_GAP) if self._egpu_status_visible() else METRIC_MARGIN
    available_height = max(0, int(HOME_BTN.y) - reserve - METRIC_HEIGHT - start_y)
    spacing = available_height / max(1, len(metrics) - 1)

    self._draw_egpu_status(rect)
    return metrics, start_y, spacing
