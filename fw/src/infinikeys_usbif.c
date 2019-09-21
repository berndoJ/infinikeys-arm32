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

/* --------------------------------------------------------------
 * VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

uint8_t IK_HID_PressedKeys_Buffer[IK_KEY_ROLLOVER];
uint8_t IK_HID_ModifierKeys = 0x00;
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
	hid_report_buffer[1] = IK_HID_ModifierKeys; // First byte: Modifiers
	hid_report_buffer[2] = IK_HID_OEMReservedReportByte; // Second byte: OEMReserved

	for (uint8_t i = 0; i < IK_KEY_ROLLOVER; i++)
	{
		hid_report_buffer[3 + i] = IK_HID_PressedKeys_Buffer[i]; // Remaining bytes: Pressed keys
	}

	// Send the HID report.
	// TODO: Implement STM32 specific USB HID code.
#endif
}
