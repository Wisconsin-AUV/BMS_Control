/*
 * app_status.h
 *
 *  Created on: Nov 15, 2026
 *      Author: Noah
 */

#ifndef INC_APP_STATUS_H_
#define INC_APP_STATUS_H_

typedef enum {
	APP_OK = 0,
	// bq69200 (0x10 - 0x1F)
	BQ_ERR_I2C = 0x10
	// telem_link (0x20 - 0x2F)
	// hotswap (0x30 - 0x3F)
	// bms (0x40 - 0x4F)
} app_status_t;


#endif /* INC_APP_STATUS_H_ */
