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

#include <stdio.h>
#include <stdlib.h>

/* --------------------------------------------------------------
 * VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

IK_KeyMap_t** IK_CFG_KeyMapTable;

uint8_t IK_CFG_CurrentKeyLayer = 0;

/* --------------------------------------------------------------
 * PRIVATE VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

/*
 * Holds the fallback key layer configuration setting.
 */
static uint8_t IK_CFG_FallbackKeyLayer = 0;

/*
 * The key layer count available in the current key map table.
 */
static uint8_t IK_CFG_KeyLayerCount = 0;

/*
 * "Empty" keymap. Used for disabled keys or matrix ids which are not defined.
 */
static IK_KeyMap_t _IK_KeyMap_None =
{
	KEYMAP_NONE,
	0,
	NULL
};

/* --------------------------------------------------------------
 * PRIVATE FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

static uint8_t _IK_CFG_AllocKeyMapTable(uint8_t key_layer_size, uint16_t key_matrix_size);
static void _IK_CFG_FreeKeyMapTableMemory(uint8_t key_layer_size, uint16_t key_matrix_size);

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

uint8_t IK_CFG_Init(void)
{
	// Generate a standard key map table (key map table filled with maps of type NONE)
	if (_IK_CFG_AllocKeyMapTable(1, IK_KEY_MAP_TABLE_MATRIX_SIZE) != 0)
		return 1;

	IK_CFG_KeyLayerCount = 1;
	IK_CFG_SetFallbackKeyLayer(0);
	IK_CFG_CurrentKeyLayer = 0;

	for (uint16_t i = 0; i < IK_KEY_MAP_TABLE_MATRIX_SIZE; i++)
	{
		IK_CFG_KeyMapTable[0][i] = _IK_KeyMap_None;
	}

	static uint8_t test_km_data[1] = { 0x04 };
	IK_KeyMap_t test_km =
	{
		KEYMAP_STATIC,
		1,
		test_km_data
	};
	IK_CFG_KeyMapTable[0][8] = test_km;

	return 0;
}

void IK_CFG_DeInit(void)
{
	_IK_CFG_FreeKeyMapTableMemory(IK_CFG_KeyLayerCount, IK_KEY_MAP_TABLE_MATRIX_SIZE);
}

uint8_t IK_CFG_GetFallbackKeyLayer(void)
{
	return IK_CFG_FallbackKeyLayer;
}

void IK_CFG_SetFallbackKeyLayer(uint8_t new_fb_key_layer)
{
	if (new_fb_key_layer >= IK_CFG_KeyLayerCount)
		return;
	IK_CFG_FallbackKeyLayer = new_fb_key_layer;
}

uint8_t IK_CFG_GetKeyLayerCount(void)
{
	return IK_CFG_KeyLayerCount;
}

IK_KeyMap_t* IK_CFG_GetKeyMap(uint16_t matrix_id)
{
	if (IK_CFG_CurrentKeyLayer >= IK_CFG_KeyLayerCount)
		IK_CFG_CurrentKeyLayer = IK_CFG_FallbackKeyLayer;

	if (matrix_id >= IK_KEY_MAP_TABLE_MATRIX_SIZE)
		matrix_id = 0;

	if (matrix_id == 0 || IK_CFG_KeyMapTable == NULL)
		return &_IK_KeyMap_None;

	IK_KeyMap_t* kl_map_table = IK_CFG_KeyMapTable[IK_CFG_CurrentKeyLayer];

	if (kl_map_table == NULL)
		return &_IK_KeyMap_None;

	return &kl_map_table[matrix_id];
}

/* --------------------------------------------------------------
 * PRIVATE FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

static uint8_t _IK_CFG_AllocKeyMapTable(uint8_t key_layer_size, uint16_t key_matrix_size)
{
	// Allocate the outer arrays.
	IK_CFG_KeyMapTable = (IK_KeyMap_t**)malloc(sizeof(IK_KeyMap_t*) * key_layer_size);

	// Check if the allocation was successful.
	if (IK_CFG_KeyMapTable == NULL)
		return 1;

	// Allocate the inner arrays.
	for (uint8_t i = 0; i < key_layer_size; i++)
	{
		IK_CFG_KeyMapTable[i] = (IK_KeyMap_t*)malloc(sizeof(IK_KeyMap_t) * key_matrix_size);

		// Check if the allocation was successful.
		if (IK_CFG_KeyMapTable[i] == NULL)
			return 1;
	}

	return 0;
}

static void _IK_CFG_FreeKeyMapTableMemory(uint8_t key_layer_size, uint16_t key_matrix_size)
{
	// Check for NULL pointer.
	if (IK_CFG_KeyMapTable == NULL)
		return;

	// Free all inner arrays.
	for (uint8_t i = 0; i < key_layer_size; i++)
	{
		IK_KeyMap_t* current_ptr = IK_CFG_KeyMapTable[i];

		// Check for NULL pointer.
		if (current_ptr == NULL)
			continue;

		free(current_ptr);
	}

	// Free the 2D-array itself.
	free(IK_CFG_KeyMapTable);
}






