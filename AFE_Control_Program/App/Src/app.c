/*
 * app.c
 *
 *  Created on: Nov 15, 2026
 *      Author: Noah Brueske
 */

#include "app.h"
#include "bms.h"

app_status_t app_init(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef *hlpuart) {

	return bms_init(hi2c);

}


void app_loop() {

}

