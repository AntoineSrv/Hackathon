/*
 * Led.h
 *
 *  Created on: Mar 3, 2024
 *      Author: serva
 */
#include "stm32f4xx_hal.h"
#include <string.h>
#define LED_PIN GPIO_PIN_5
#define LED_PORT GPIOA

#define TLED_ON	"LED ON "
#define TLED_OFF "LED OFF"

extern UART_HandleTypeDef huart2;


void changerEtatLed();
