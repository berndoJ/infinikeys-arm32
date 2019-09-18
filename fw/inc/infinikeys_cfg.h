/*----------------------------------------------------------------
 * FILENAME :		infinikeys_cfg.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			InfiniKeys Configuration File
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	16.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		Configuration header for the InfiniKeys firmware
 * 		extension.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_CFG_H_
#define INFINIKEYS_CFG_H_

#include "infinikeys_hal_template.h"

#define IK_MATRIX_PROBE_LINE_COUNT		10
#define IK_MATRIX_SENSE_LINE_COUNT		10

#define IK_KEY_ROLLOVER					5

#endif /* INFINIKEYS_CFG_H_ */
