/*
 * bq692000pwr.h
 *
 *  Created on: Nov 15, 2026
 *      Author: Noah Brueske
 */

#ifndef INC_BQ692000PWR_H_
#define INC_BQ692000PWR_H_

#include "stm32g4xx_hal.h"
#include "app_status.h"
#include <stdbool.h>

// values remain latched until cleared
typedef struct {
	bool cc_ready; // Indicates that a fresh coulomb counter reading is available.
	bool device_xready; // Internal chip fault indicator. When this bit is set to 1, it should be cleared by the host.
	bool overd_alert; //  External pull-up on the ALERT pin indicator. Only active when ALERT pin is not already being driven high by the AFE.
	bool uv; //  Undervoltage fault event indicator.
	bool ov; // Overvoltage fault event indicator
	bool scd; // Short circuit in discharge fault event indicator.
	bool ocd; // Over current in discharge fault event indicator.
} bq_sys_stat_t;

#define NUM_CELLS 5
typedef struct {
	bool cells[NUM_CELLS]; // cells 1 - 5
} bq_cell_bal_t;


app_status_t bq_init(I2C_HandleTypeDef *hi2c);
app_status_t bq_get_sys_stat(bq_sys_stat_t *bq_sys_stat);

#endif /* INC_BQ692000PWR_H_ */
