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
