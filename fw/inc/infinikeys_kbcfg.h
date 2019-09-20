/*----------------------------------------------------------------
 * FILENAME :		infinikeys_kbcfg.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Dynamic Keyboard Configuration Module
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	17.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		This module is used to manage the local dynamic
 * 		configuration of the keyboard. This configuration can be
 * 		updated dynamically over USB without flashing a new
 * 		firmware to the device.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_KBCFG_H_
#define INFINIKEYS_KBCFG_H_

#include "infinikeys_common.h"

/* --------------------------------------------------------------
 * VARIABLE DECLARATIONS
 * ------------------------------------------------------------*/

extern uint8_t IK_CFG_CurrentKeyLayer;

/* --------------------------------------------------------------
 * FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

/*
 * Description:
 * This function retrieves the default fallback keyboard layer
 * set by the configuration.
 */
uint8_t IK_CFG_GetFallbackKeyLayer(void);

/*
 * Description
 * This function gets a key map from the given matrix id.
 *
 * Parameters
 * - uint16_t matrix_id: The matrix id to get the keymap of.
 */
IK_KeyMap_t* IK_CFG_GetKeyMap(uint16_t matrix_id);

#endif /* INFINIKEYS_KBCFG_H_ */
