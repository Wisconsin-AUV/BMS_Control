/*
 * app.h
 *
 *  Created on: Nov 15, 2026
 *      Author: Noah Brueske
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "stm32g4xx_hal.h"
#include "app_status.h"

app_status_t app_init(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef *hlpuart);
void app_loop();

#endif /* INC_APP_H_ */
