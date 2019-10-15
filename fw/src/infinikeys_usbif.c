/*----------------------------------------------------------------
 * FILENAME :		infinikeys_usbif.c
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			USB Interface Module
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	18.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		This module connects InfiniKeys to the USB bus.
 * 
 *--------------------------------------------------------------*/

#include "infinikeys_usbif.h"

#include <stdlib.h>
#include "infinikeys_kbcfg.h"

#if defined(IK_PLATFORM_STM32_CUBE)
#include "usb_device.h"
#include "infinikeys_stm32cube/infinikeys_stm32cube_usb_if.h"
#endif

/* --------------------------------------------------------------
 * VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

uint8_t IK_HID_PressedKeys_Buffer[IK_KEY_ROLLOVER];
uint8_t IK_HID_ModifierKeys[8];
uint8_t IK_HID_OEMReservedReportByte = 0x00;

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

void IK_USBIF_SendHIDReport(void)
{
#if defined(IK_PLATFORM_STM32_CUBE)
	uint8_t hid_report_length = IK_KEY_ROLLOVER + 3;
	uint8_t hid_report_buffer[hid_report_length];

	hid_report_buffer[0] = 0x01; // Report ID: 1
	hid_report_buffer[1] =
			(IK_NTH_BIT(IK_HID_MODIFIER_L_CTRL) * IK_HID_ModifierKeys[IK_HID_MODIFIER_L_CTRL]) |
			(IK_NTH_BIT(IK_HID_MODIFIER_L_SHIFT) * IK_HID_ModifierKeys[IK_HID_MODIFIER_L_SHIFT]) |
			(IK_NTH_BIT(IK_HID_MODIFIER_L_ALT) * IK_HID_ModifierKeys[IK_HID_MODIFIER_L_ALT]) |
			(IK_NTH_BIT(IK_HID_MODIFIER_L_GUI) * IK_HID_ModifierKeys[IK_HID_MODIFIER_L_GUI]) |
			(IK_NTH_BIT(IK_HID_MODIFIER_R_CTRL) * IK_HID_ModifierKeys[IK_HID_MODIFIER_R_CTRL]) |
			(IK_NTH_BIT(IK_HID_MODIFIER_R_SHIFT) * IK_HID_ModifierKeys[IK_HID_MODIFIER_R_SHIFT]) |
			(IK_NTH_BIT(IK_HID_MODIFIER_R_ALT) * IK_HID_ModifierKeys[IK_HID_MODIFIER_R_ALT]) |
			(IK_NTH_BIT(IK_HID_MODIFIER_R_GUI) * IK_HID_ModifierKeys[IK_HID_MODIFIER_R_GUI]);
	hid_report_buffer[2] = IK_HID_OEMReservedReportByte; // Second byte: OEMReserved

	for (uint8_t i = 0; i < IK_KEY_ROLLOVER; i++)
	{
		hid_report_buffer[3 + i] = IK_HID_PressedKeys_Buffer[i]; // Remaining bytes: Pressed keys
	}

	// Send the HID report.
	IK_STM32CUBE_USBD_HID_SendReport(&hUsbDeviceFS, hid_report_buffer, hid_report_length);
#endif
}

void IK_USBIF_RecieveHIDReportCB(uint8_t* report_buf, uint16_t report_buf_size)
{
	if (report_buf_size > 0)
	{
		switch (report_buf[0])
		{
		case IK_CFG_HID_REPORT_ID:
			// Config update report. (Data transfer report)
			if (report_buf_size > 1)
			{
				uint8_t cmd = report_buf[1];
				switch (cmd)
				{
				case IK_CFG_CMD_TEST:
					// Test command.
					break;
				case IK_CFG_CMD_SET_KEYMAP:
					/*
					 * SET_KEYMAP command data: (Starting at report index 1)
					 * [2] - Key Layer (0x00 - 0xff)
					 * [3] - Key Map Type - According to IK_KeyMapType_t enum values (see IK_KeyMapType_t for min/max values)
					 * [4] - Matrix ID LOWBYTE (0x00 - 0xff)
					 * [5] - Matrix ID HIBYTE (0x00 - 0xff)
					 */
					if (report_buf_size > 6)
					{
						uint8_t map_key_layer = report_buf[2];
						uint16_t map_matrix_id = report_buf[4] + (report_buf[5] << 8);

						if (map_key_layer < IK_CFG_GetKeyLayerCount() && map_matrix_id < IK_KEY_MAP_TABLE_MATRIX_SIZE)
						{
							IK_KeyMap_t map;

							map.Type = report_buf[3];
							map.Metadata = NULL;

							switch (map.Type)
							{
							case KEYMAP_MODIFIER:
								/*
								 * [6] - Modifier key type (enum IK_ModifierType_t)
								 */
								;
								IK_ModifierMapMetadata_t* mod_metadata = (IK_ModifierMapMetadata_t*)malloc(sizeof(IK_ModifierMapMetadata_t));

								if (mod_metadata == NULL)
									break;

								mod_metadata->ModifierType = report_buf[6];
								mod_metadata->ModifierMetadata = NULL;

								switch (mod_metadata->ModifierType)
								{
								case MODIFIER_TYPE_HID:
									/*
									 * [7] - HID modifier key. (enum IK_HIDModifier_t)
									 */
									;
									IK_HIDModifierMapMetadata_t* hid_mod_metadata = (IK_HIDModifierMapMetadata_t*)malloc(sizeof(IK_HIDModifierMapMetadata_t));

									if (hid_mod_metadata == NULL)
										break;

									hid_mod_metadata->HIDModifierCode = report_buf[7];
									mod_metadata->ModifierMetadata = hid_mod_metadata;
									break;
								case MODIFIER_TYPE_KEY_LAYER:
									/*
									 * [7] - Key layer the modifier key switches to (0x00 - 0xff)
									 */
									;
									IK_KeyLayerModifierMetadata_t* kl_mod_metadata = (IK_KeyLayerModifierMetadata_t*)malloc(sizeof(IK_KeyLayerModifierMetadata_t));

									if (kl_mod_metadata == NULL)
										break;

									kl_mod_metadata->KeyLayer = report_buf[7];
									mod_metadata->ModifierMetadata = kl_mod_metadata;
									break;
								default:
									break;
								}

								map.Metadata = mod_metadata;
								break;
							case KEYMAP_STATIC:
								/*
								 * [6] - HID keycode (0x00 - 0xff)
								 */
								;
								IK_StaticMapMetadata_t* s_metadata = (IK_StaticMapMetadata_t*)malloc(sizeof(IK_StaticMapMetadata_t));

								if (s_metadata == NULL)
									break;

								s_metadata->Keycode = report_buf[6];

								map.Metadata = s_metadata;
								break;
							case KEYMAP_ACTION:
								/*
								 * TODO: Implement action mapping transfer.
								 */
								;
								IK_ActionMapMetadata_t* act_metadata = (IK_ActionMapMetadata_t*)malloc(sizeof(IK_ActionMapMetadata_t));

								if (act_metadata == NULL)
									break;

								map.Metadata = act_metadata;
								break;
							case KEYMAP_NONE:
								break;
							default:
								break;
							}

							// Load the new keymap to the keymap table.
							IK_CFG_LoadKeyMapToTable(map_key_layer, map_matrix_id, map);
						}
					}
					/* OLD IMPLEMENTATION
					if (report_buf_size > 6)
					{
						uint8_t key_layer = report_buf[2];
						uint16_t matrix_id = report_buf[3] + (report_buf[4] << 8);
						if (key_layer < IK_CFG_GetKeyLayerCount() && matrix_id < IK_KEY_MAP_TABLE_MATRIX_SIZE)
						{
							IK_KeyMap_t new_key_map;

							// Set up basic struct variables.
							new_key_map.Type = report_buf[5];
							new_key_map.DataSize = report_buf[6];

							// Create data array, add the recieved data to it and add it to the key map struct.
							if (report_buf_size > 6 + new_key_map.DataSize && new_key_map.DataSize > 0)
							{
								uint8_t* new_key_map_data = malloc(new_key_map.DataSize);

								if (new_key_map_data != NULL)
								{
									for (uint8_t i = 0; i < new_key_map.DataSize; i++)
									{
										new_key_map_data[i] = report_buf[7 + i];
									}

									new_key_map.Data = new_key_map_data;
								}
							}

							// Load in the new key map to the key map table.
							IK_CFG_LoadKeyMapToTable(key_layer, matrix_id, new_key_map);
						}
					}
					*/
					break;
				case IK_CFG_CMD_REINIT_KEYMAP:
					/*
					 * REINIT_KEYMAP command:
					 * Reinits the key map table with the given parameters.
					 * [0] - Key Layer Count (0x00 - IK_MATRIX_MAX_KEY_LAYERS)
					 */
					if (report_buf_size > 2)
					{
						uint8_t klc = report_buf[2];
						IK_CFG_ReInitKeyMap(klc);
					}
					break;
				default:
					// Invalid command.
					break;
				}
			}
			break;
		case IK_KEYBOARD_HID_REPORT_ID:
			// Keyboard Report. (States of lock LEDs, ...)
			break;
		default:
			// Non-registered keyboard HID report id.
			break;
		}
	}
}
