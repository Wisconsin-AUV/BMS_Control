/*
 * bq692000pwr.c
 *
 *  Created on: Nov 15, 2026
 *      Author: Noah Brueske
 */

#include "bq692000pwr.h"
#include "bq_details.h"

static I2C_HandleTypeDef *bq_hi2c;

/*
 * PRIVATE FUNCTIONS
 */

/*
 * Reads value of designated register
 */
static app_status_t bq_read(uint8_t reg, uint8_t *buffer, uint16_t len) {

	if (HAL_I2C_Mem_Read(bq_hi2c, BQ_ADDR, reg, I2C_MEMADD_SIZE_8BIT, buffer, len, I2C_TIMEOUT_MS) != HAL_OK) {
		 return BQ_ERR_I2C;
	 }

	 return APP_OK;
}

/*
 * Writes value to designated register
 */
static app_status_t bq_write(uint8_t reg, uint8_t *buffer, uint16_t len) {

	if (HAL_I2C_Mem_Write(bq_hi2c, BQ_ADDR, reg, I2C_MEMADD_SIZE_8BIT, buffer, len, I2C_TIMEOUT_MS) != HAL_OK) {
		return BQ_ERR_I2C;
	}

	return APP_OK;
}


/*
 * grabs I2C handle and makes sure bq is ready to receive data
 */
app_status_t bq_init(I2C_HandleTypeDef *hi2c) {

	HAL_StatusTypeDef status;
	uint8_t buff_cc_cfg = 0;
	uint8_t buff_sys_ctrl1 = 0;
	uint8_t buff_sys_ctrl2 = 0;

	// grab handle and check if bq is ready
	bq_hi2c = hi2c;
	status = HAL_I2C_IsDeviceReady(bq_hi2c, BQ_ADDR, I2C_NUM_TRIALS, I2C_TIMEOUT_MS);
	if (status != HAL_OK) {
		return BQ_ERR_I2C;
	}

	/*
	 * CC_CFG REGISTER INITIALIZATION
	 */
	buff_cc_cfg = BQ_CC_CFG_VAL; // based on datasheet, cc_cfg reg should be initialized to this value
	if (bq_write(BQ_REG_CC_CFG, &buff_cc_cfg, sizeof(buff_cc_cfg)) != APP_OK) {
		return BQ_ERR_I2C;
	}

	/*
	 * SYSTEM CONTROL REGISTER INITIALIZATION
	 */
	// enable adc
	buff_sys_ctrl1 |= BQ_MASK_ADC_EN;
	// select temperature source -> thermistor (for TSx_HI and TSx_LO)
	buff_sys_ctrl1 |= BQ_MASK_TEMP_SEL;
	// keep OV, UV, OCD, and SCD delays
	buff_sys_ctrl2 &= ~BQ_MASK_DELAY_DIS;
	// Select continuous coulomb counter operation (can be set to 0 to enable one-shot mode)
	buff_sys_ctrl2 |= BQ_MASK_CC_EN;
	// fet discharge is disabled initially
	buff_sys_ctrl2 &= ~BQ_MASK_DSG_ON;
	// fet charge is disabled initially
	buff_sys_ctrl2 &= ~BQ_MASK_CHG_ON;
	// write to registers
	if (bq_write(BQ_REG_SYS_CTRL1, &buff_sys_ctrl1, sizeof(buff_sys_ctrl1)) != APP_OK) {
		return BQ_ERR_I2C;
	}
	if (bq_write(BQ_REG_SYS_CTRL2, &buff_sys_ctrl2, sizeof(buff_sys_ctrl2)) != APP_OK) {
			return BQ_ERR_I2C;
	}

	/*
	 * PROTECT REGISTER INITIALIZATION TODO
	 */




	return APP_OK;
}

/*
 * Returns sys_stat register
 */
app_status_t bq_get_sys_stat(bq_sys_stat_t *bq_sys_stat) {
	uint8_t buffer;

	// read value
	if (bq_read(BQ_REG_SYS_STAT, &buffer, sizeof(buffer)) != APP_OK) {
		return BQ_ERR_I2C;
	}

	// Fill struct with values that were read
	bq_sys_stat->cc_ready = (buffer & BQ_MASK_CC_READY) != 0;
	bq_sys_stat->device_xready = (buffer & BQ_MASK_DEVICE_XREADY) != 0;
	bq_sys_stat->ocd = (buffer & BQ_MASK_OCD) != 0;
	bq_sys_stat->ov = (buffer & BQ_MASK_OV) != 0;
	bq_sys_stat->overd_alert = (buffer & BQ_MASK_OVRD_ALERT) != 0;
	bq_sys_stat->scd = (buffer & BQ_MASK_SCD) != 0;
	bq_sys_stat->uv = (buffer & BQ_MASK_UV) != 0;

	return APP_OK;
}


/*
 * Sets Cell balancing registers
 */
app_status_t bq_set_cell_bal(bq_cell_bal_t *bq_cell_bal) {
	uint8_t buffer = 0;
	bool *cells = bq_cell_bal->cells;

	// build the cell buffer to transmit
	for (int i = 0; i < NUM_CELLS; i++) {
		if (cells[i]) {
			buffer |= (1 << i); // if cell is true, write a 1 to buffer at that cells location
		}
	}

	// write values
	if (bq_write(BQ_REG_CELL_BAL, &buffer, sizeof(buffer)) != APP_OK) {
		return BQ_ERR_I2C;
	}

	return APP_OK;
}


