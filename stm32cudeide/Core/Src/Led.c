/*
 * Led.c
 *
 *  Created on: Mar 3, 2024
 *      Author: serva
 */
#include "Led.h"


int allumer = 0;

void changerEtatLed(){
	allumer = 1 - allumer ;
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, allumer); // Allume la LED
	if (allumer){
		HAL_UART_Transmit(&huart2, (uint8_t*)TLED_ON, strlen(TLED_ON), HAL_MAX_DELAY); // Transmettre les données via USART2
	}else {
		HAL_UART_Transmit(&huart2, (uint8_t*)TLED_OFF, strlen(TLED_OFF), HAL_MAX_DELAY); // Transmettre les données via USART2
	}
}
