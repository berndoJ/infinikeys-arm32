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

#if defined(IK_PLATFORM_STM32_CUBE)
#include "infinikeys_usbif_stm32cube.h"
#endif

/* --------------------------------------------------------------
 * DEFINITIONS
 * ------------------------------------------------------------*/

//#define IK_HID_MODIFIER_BIT_L_CTRL			(1 << 0)
//#define IK_HID_MODIFIER_BIT_L_SHIFT			(1 << 1)
//#define IK_HID_MODIFIER_BIT_L_ALT			(1 << 2)
//#define IK_HID_MODIFIER_BIT_L_GUI			(1 << 3)
//#define IK_HID_MODIFIER_BIT_R_CTRL			(1 << 4)
//#define IK_HID_MODIFIER_BIT_R_SHIFT			(1 << 5)
//#define IK_HID_MODIFIER_BIT_R_ALT			(1 << 6)
//#define IK_HID_MODIFIER_BIT_R_GUI			(1 << 7)

/* --------------------------------------------------------------
 * VARIABLE DECLARATIONS
 * ------------------------------------------------------------*/

/*
 * Buffer array for all pressed HID keys on the keyboard. It is used
 * when a new HID report gets constructed.
 */
extern uint8_t IK_HID_PressedKeys_Buffer[IK_KEY_ROLLOVER];

/*
 * Buffer for the modifier key byte. This byte gets sent to the USB
 * host when a report gets sent, indicating which modifier keys
 * on the keyboard are pressed.
 */
extern uint8_t IK_HID_ModifierKeys;

/*
 * Buffer for the OEM reserved byte that gets sent over to the USB
 * host whenever a HID keyboard report is issued.
 */
extern uint8_t IK_HID_OEMReservedReportByte;

/* --------------------------------------------------------------
 * FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

/*
 * Description
 * This function triggers a new HID report. The report gets
 * constructed of the currently known keyboard information and
 * gets sent to the USB host.
 */
void IK_USBIF_SendHIDReport(void);

#endif /* INFINIKEYS_USBIF_H_ */
