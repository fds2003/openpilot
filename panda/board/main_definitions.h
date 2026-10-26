#pragma once

#include "main_declarations.h"

// ********************* Globals **********************
uint8_t hw_type = 0;
board *current_board;
uint32_t uptime_cnt = 0;
uint16_t reset_flags = 0U;

// F4 没有 stm32h7/sound.h，也没有 SPI 驱动；
// 而 main_comms.h 会无条件引用这两个变量，所以在 F4 上由这里定义。
#ifdef STM32F4
uint16_t sound_output_level;
uint16_t spi_error_count;
#endif

// heartbeat state
uint32_t heartbeat_counter = 0;
uint32_t heartbeat_tick_counter = 0;        // 8Hz
bool heartbeat_lost = false;
bool heartbeat_disabled = false;            // set over USB

// siren state
bool siren_enabled = false;
