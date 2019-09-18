/*----------------------------------------------------------------
 * FILENAME :		infinikeys_parser.c
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes
 * BREIF :			Keystate parser module.
 * 
 * Copyright (c) 2019 Johannes. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	17.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		This module parses the pressed key states to keyboard
 * 		actions. The parsing is made according to the keyboard
 * 		configuration.
 * 
 *--------------------------------------------------------------*/

#include "infinikeys_parser.h"

#include <string.h>
#include "infinikeys_usbif.h"
#include "infinikeys_actionhandler.h"

// TODO : Implement following functions and global variables in other modules of the extension.
static IK_KeyMap_t* IK_CFG_GetKeyMap(uint16_t matrix_id) { return 0; }
static uint8_t IK_CFG_GetFallbackKeyLayer(void) { return 0; }
static uint8_t IK_CFG_CurrentKeyLayer = 0;

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

void _IK_Parser_ParseKeyStates(uint8_t* pressedkeys_table, uint16_t pressedkeys_table_size)
{
	// Index for filling the HID pressed keys buffer.
	uint16_t hid_pressedkeys_buffer_index = 0;
	// Buffer for setting new key layer to.
	uint8_t new_key_layer = IK_CFG_GetFallbackKeyLayer();

	// Clear the HID report pressed key table.
	memset(IK_HID_PressedKeys_Buffer, 0x00, IK_KEY_ROLLOVER);
	// Clear the HID report modifier byte.
	IK_HID_ModifierKeys = 0x00;

	// Parse the pressed keys table.
	for (uint16_t pk_idx = 0; pk_idx < pressedkeys_table_size; pk_idx++)
	{
		uint8_t pressed_keycode = pressedkeys_table[pk_idx];
		// Get the key mapping.
		IK_KeyMap_t* pressed_keymap = IK_CFG_GetKeyMap(pressed_keycode);
		// Switch the action based on the key mapping type.
		switch (pressed_keymap->Type)
		{
		case KEYMAP_MODIFIER:
			if (pressed_keymap->DataSize >= 2)
			{
				// Retrieve the type of modifier - HID or Layer
				uint8_t modifier_type = pressed_keymap->Data[0];
				switch (modifier_type)
				{
				case IK_KEY_MAP_MODIFIER_TYPE_HID:
					// Next keymap data byte is the HID modifier bit.
					IK_HID_ModifierKeys |= pressed_keymap->Data[1];
					break;
				case IK_KEY_MAP_MODIFIER_TYPE_LAYER:
					// Next keymap data byte is the new keyboard layer to switch to.
					new_key_layer = pressed_keymap->Data[1];
					break;
				}
			}
			break;
		case KEYMAP_STATIC:
			if (pressed_keymap->DataSize >= 1)
			{
				// Retrieve the HID keycode (static binding from key to HID code)
				uint8_t hid_keycode = pressed_keymap->Data[0];
				// Add the HID keycode to the HID key report queue.
				if (hid_pressedkeys_buffer_index < IK_KEY_ROLLOVER)
				{
					IK_HID_PressedKeys_Buffer[hid_pressedkeys_buffer_index] = hid_keycode;
					hid_pressedkeys_buffer_index++;
				}
			}
			break;
		case KEYMAP_ACTION:
			// Execute action.
			IK_ACT_ExecuteRaw(pressed_keymap->Data, pressed_keymap->DataSize);
			break;
		}
	}

	// Send new HID report.
	IK_USBIF_SendHIDReport();

	// Switch to new key layer (fallback if no key layer modifier is pressed)
	IK_CFG_CurrentKeyLayer = new_key_layer;
}
