/*
 * bms.c
 *
 *  Created on: Nov 15, 2026
 *      Author: Noah Brueske
 */

#include "bms.h"
#include "bq692000pwr.h"

app_status_t bms_init(I2C_HandleTypeDef *hi2c) {

	return bq_init(hi2c);
}
