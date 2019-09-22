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

/* --------------------------------------------------------------
 * PRIVATE VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

static uint8_t pressed_keys_buffer[IK_PHYSICAL_KEY_COUNT];

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

void IK_KeyboardPollCyleTick(void)
{
	// Acquire keyboard states.
	_IK_ACQ_Poll(pressed_keys_buffer, IK_PHYSICAL_KEY_COUNT);

	// Parse the pressed keys and send necessary HID reports.
	_IK_Parser_ParseKeyStates(pressed_keys_buffer, IK_PHYSICAL_KEY_COUNT);
}
