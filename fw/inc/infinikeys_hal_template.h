/*----------------------------------------------------------------
 * FILENAME :		infinikeys_hal.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			BRIEF
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	16.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		DESCRIPTION_OF_FILE
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_HAL_TEMPLATE_H_
#define INFINIKEYS_HAL_TEMPLATE_H_

#include "infinikeys_common.h"

void IK_HAL_SetMatrixProbeLine(uint8_t probe_line, uint8_t state);
uint8_t IK_HAL_ReadMatrixSenseLine(uint8_t sense_line);

#endif /* INFINIKEYS_HAL_TEMPLATE_H_ */
