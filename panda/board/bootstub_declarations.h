#pragma once

// ******************** Prototypes ********************
void print(const char *a){ UNUSED(a); }
void puth(unsigned int i){ UNUSED(i); }
static void hexdump(const void *a, int l){ UNUSED(a); UNUSED(l); }
__attribute__((unused)) static void puth4(unsigned int i){ UNUSED(i); }
void puth2(unsigned int i){ UNUSED(i); }
// No UART support in bootloader (F4 的 uart.h 会用到这两个符号)
typedef struct uart_ring uart_ring;
void uart_init(uart_ring *q, int baud) { UNUSED(q); UNUSED(baud); }
typedef struct board board;
typedef struct harness_configuration harness_configuration;
void pwm_init(TIM_TypeDef *TIM, uint8_t channel);
void pwm_set(TIM_TypeDef *TIM, uint8_t channel, uint8_t percentage);

// ********************* Globals **********************
uint8_t hw_type = 0;
board *current_board;
