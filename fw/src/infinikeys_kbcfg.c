/*----------------------------------------------------------------
 * FILENAME :		infinikeys_kbcfg.c
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

#include "infinikeys_kbcfg.h"

/* --------------------------------------------------------------
 * VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

uint8_t IK_CFG_CurrentKeyLayer = 0;

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

uint8_t IK_CFG_GetFallbackKeyLayer(void)
{
	return 0;
}

IK_KeyMap_t* IK_CFG_GetKeyMap(uint16_t matrix_id)
{
	return 0;
}
