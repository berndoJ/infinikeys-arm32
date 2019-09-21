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

/*
 * Holds the fallback key layer configuration setting.
 */
static uint8_t IK_CFG_FallbackKeyLayer = 0;

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

uint8_t IK_CFG_GetFallbackKeyLayer(void)
{
	return IK_CFG_FallbackKeyLayer;
}

IK_KeyMap_t* IK_CFG_GetKeyMap(uint16_t matrix_id)
{
	// TODO: Implement real solution. (Currently test code)
	// --- START OF TEST CODE ---
	// This test code always returns a static key binding to the keyboard key "A".
	// So no matter which matrix id is given - the key is mapped to "A".
	IK_KeyMap_t tst_map;
	uint8_t tst_map_data[1];

	tst_map_data[0] = 0x04; // "A" key on the keyboard.

	tst_map.Type = KEYMAP_STATIC;
	tst_map.DataSize = 1;
	tst_map.Data = tst_map_data;

	return &tst_map;
	// --- END OF TEST CODE ---
}
