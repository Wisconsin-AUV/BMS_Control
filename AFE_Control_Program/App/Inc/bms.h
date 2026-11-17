/*
 * bms.h
 *
 *  Created on: Nov 15, 2026
 *      Author: Noah Brueske
 */

#ifndef INC_BMS_H_
#define INC_BMS_H_

#include "stm32g4xx_hal.h"
#include "app_status.h"

app_status_t bms_init(I2C_HandleTypeDef *hi2c);

#endif /* INC_BMS_H_ */
