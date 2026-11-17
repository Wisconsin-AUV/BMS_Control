/*
 * bq_registers.h
 *
 *  Created on: Nov 16, 2026
 *      Author: Noah
 *
 *
 */

#ifndef SRC_BQ_DETAILS_H_
#define SRC_BQ_DETAILS_H_

#define I2C_TIMEOUT_MS 10
#define I2C_NUM_TRIALS 5

/*
 * Device Address
 */
#define BQ_ADDR (0x08 << 1) // HAL expected address to be shifted left one bit

/*
 * SYS_STAT
 */
#define BQ_REG_SYS_STAT 0x00
// bit masks (these bits remain latched to 1 if not cleared)
#define BQ_MASK_CC_READY (1 << 7) // Indicates that a fresh coulomb counter reading is available
#define BQ_MASK_DEVICE_XREADY (1 << 5) // Internal chip fault indicator. When this bit is set to 1, it should be cleared by the host.
#define BQ_MASK_OVRD_ALERT (1 << 4) //  External pull-up on the ALERT pin indicator. Only active when ALERT pin is not already being driven high by the AFE itself.
#define BQ_MASK_UV (1 << 3) // Undervoltage fault event indicator
#define BQ_MASK_OV (1 << 2) // Overvoltage fault event indicator
#define BQ_MASK_SCD (1 << 1) // Short circuit in discharge fault event indicator.
#define BQ_MASK_OCD (1 << 0) // Over current in discharge fault event indicator.

/*
 * CELL BAL
 */
#define BQ_REG_CELL_BAL 0x01
// bit masks
#define BQ_MASK_CB1 (1 << 0)
#define BQ_MASK_CB2 (1 << 1)
#define BQ_MASK_CB3 (1 << 2)
#define BQ_MASK_CB4 (1 << 3)
#define BQ_MASK_CB5 (1 << 4)

/*
 * SYS_CTRL1
 */
#define BQ_REG_SYS_CTRL1 0x04
// bit masks
#define BQ_MASK_LOAD_PRESENT (1 << 7)
#define BQ_MASK_ADC_EN (1 << 4) // ADC enable command x
#define BQ_MASK_TEMP_SEL (1 << 3) //  TSx_HI and TSx_LO temperature source (0 = internal die, 1 = thermistor) x
#define BQ_MASK_SHUT_A (1 << 1) // Shut A and Shut B are used for the shutdown command. Must be written as
#define BQ_MASK_SHUT_B (1 << 0) // 1) [Shut_A] = 0, [Shut_B] = 1, 2) [Shut_A] = 1, [Shut_B] = 0 (other commands are ignored)

/*
 * SYS_CTRL2
 */
#define BQ_REG_SYS_CTRL2 0x05
// bit masks
#define BQ_MASK_DELAY_DIS (1 << 7) // set to disable OV, UV, OCD, and SCD delays (leave as 0 for now)
#define BQ_MASK_CC_EN (1 << 6) // Continuous vs One-shot coulomb counter reading mode (1 = enable continuous mode) x
#define BQ_MASK_CC_ONESHOT (1 << 5) // if in one-shot CC mode, set to trigger a single 250-ms reading
#define BQ_MASK_DSG_ON (1 << 1) // Discharge FET driver (0 = off, 1 = on)
#define BQ_MASK_CHG_ON (1 << 0) // Charge FET driver (0 = off, 1 = on)

/*
 * PROTECT1
 */
#define BQ_REG_PROTECT1 0x06
// bit masks
#define BQ_MASK_RSNS (1 << 7) // Allows for doubling the OCD and SCD thresholds simultaneously
#define BQ_MASK_SCD_D1 (1 << 4) // Short circuit in discharge delay setting (SCD_D1 and SCD_D2
#define BQ_MASK_SCD_D0 (1 << 3) // create the code which corresponds to a value in microseconds). Check datasheet
#define BQ_MASK_SCD_T2 (1 << 2) // Short circuit in discharge threshold setting. T2 - T0 create a the code which corresponds
#define BQ_MASK_SCD_T1 (1 << 1) // to a value in mV. Also depends on RSNS bit
#define BQ_MASK_SCD_T0 (1 << 0) // ''

/*
 * PROTECT 2
 */
#define BQ_REG_PROTECT2 0x07
// bit mask
#define BQ_MASK_OCD_D2 (1 << 6) //  Overcurrent in discharge delay setting (OCD_D2 - D0)
#define BQ_MASK_OCD_D1 (1 << 5) // creates the code corresponding to a value in ms. Check datasheet
#define BQ_MASK_OCD_D0 (1 << 4)
#define BQ_MASK_OCD_T3 (1 << 3) // Overcurrent in discharge threshold setting (OCD_T3 - R0)
#define BQ_MASK_OCD_T2 (1 << 2) // creates the code corresponding to a value in mV. Dependant on
#define BQ_MASK_OCD_T1 (1 << 1) // RSNS bit (in PROTECT1 reg). Check datasheet
#define BQ_MASK_OCD_T0 (1 << 0)

/*
 * Protect 3
 */
#define BQ_REG_PROTECT3 0x08
// bit mask
#define BQ_MASK_UV_D1 (1 << 7) // undervoltage delay settings (UV_D1 - D0)
#define BQ_MASK_UV_D0 (1 << 6) // creates the code corresponding to a value in s. check datasheet
#define BQ_MASK_OV_D1 (1 << 5) // overvoltage delay settings (OV_D1 - D0)
#define BQ_MASK_OV_D0 (1 << 4) // creates the code corresponding to a vlaue in s. check datasheet

/*
 * OV TRIP
 */
#define BQ_REG_OV_TRIP 0x09

/*
 * UV TRIP
 */
#define BQ_REG_UV_TRIP 0x0A

/*
 * CC_CFG
 */
#define BQ_REG_CC_CFG 0x0B
#define BQ_CC_CFG_VAL 0x19 // CC_CFG should be set to 0x19 on startup for optimal performance (datasheet)
#endif /* SRC_BQ_DETAILS_H_ */
