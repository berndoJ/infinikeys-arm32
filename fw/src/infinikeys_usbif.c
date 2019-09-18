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

uint8_t IK_HID_PressedKeys_Buffer[IK_KEY_ROLLOVER];
uint8_t IK_HID_ModifierKeys;

void IK_USBIF_SendHIDReport(void)
{

}
