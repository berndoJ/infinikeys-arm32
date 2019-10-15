/*----------------------------------------------------------------
 * FILENAME :		infinikeys.c
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Main extension file.
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

#include "infinikeys.h"

#include "infinikeys_acq.h"
#include "infinikeys_parser.h"
#include "infinikeys_kbcfg.h"

/* --------------------------------------------------------------
 * PRIVATE VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

static uint8_t pressed_keys_buffer[IK_PHYSICAL_KEY_COUNT];

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

uint8_t IK_Init(void)
{
	if (IK_CFG_Init() != 0)
		return 1;

	// TEST CODE START

	static IK_HIDModifierMapMetadata_t test_map_meta = {
			0x04
	};

	IK_KeyMap_t test_map = {
			KEYMAP_STATIC,
			&test_map_meta
	};

	IK_CFG_LoadKeyMapToTable(0, 8, test_map);

	// TEST CODE END

	return 0;
}

uint8_t IK_DeInit(void)
{
	return 0;
}

void IK_KeyboardPollCyleTick(void)
{
	// Acquire keyboard states.
	_IK_ACQ_Poll(pressed_keys_buffer, IK_PHYSICAL_KEY_COUNT);

	// Parse the pressed keys and send necessary HID reports.
	_IK_Parser_ParseKeyStates(pressed_keys_buffer, IK_PHYSICAL_KEY_COUNT);
}
