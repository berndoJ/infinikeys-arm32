/*----------------------------------------------------------------
 * FILENAME :		infinikeys_usbif.h
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

#ifndef INFINIKEYS_USBIF_H_
#define INFINIKEYS_USBIF_H_

#include "infinikeys_common.h"

//#define IK_HID_MODIFIER_BIT_L_CTRL			(1 << 0)
//#define IK_HID_MODIFIER_BIT_L_SHIFT			(1 << 1)
//#define IK_HID_MODIFIER_BIT_L_ALT			(1 << 2)
//#define IK_HID_MODIFIER_BIT_L_GUI			(1 << 3)
//#define IK_HID_MODIFIER_BIT_R_CTRL			(1 << 4)
//#define IK_HID_MODIFIER_BIT_R_SHIFT			(1 << 5)
//#define IK_HID_MODIFIER_BIT_R_ALT			(1 << 6)
//#define IK_HID_MODIFIER_BIT_R_GUI			(1 << 7)

extern uint8_t IK_HID_PressedKeys_Buffer[IK_KEY_ROLLOVER];
extern uint8_t IK_HID_ModifierKeys;

void IK_USBIF_SendHIDReport(void);

#endif /* INFINIKEYS_USBIF_H_ */
