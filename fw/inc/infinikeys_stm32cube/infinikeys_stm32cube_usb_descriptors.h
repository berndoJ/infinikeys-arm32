/*----------------------------------------------------------------
 * FILENAME :		infinikeys_stm32cube_usb_descriptors.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Infinikeys USB descriptors.
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	21.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		Contains the infinikeys USB device, configuration, HID,
 * 		report, ... descirptors.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_STM32CUBE_USB_DESCRIPTORS_H_
#define INFINIKEYS_STM32CUBE_USB_DESCRIPTORS_H_

#include "infinikeys_common.h"

#if defined(IK_PLATFORM_STM32_CUBE)

#include "infinikeys_stm32cube/infinikeys_stm32cube_usb_hid.h"

// Infinikeys USB configuration descriptor.
extern uint8_t IK_USB_ConfigurationDescriptor[IK_USB_CONFIG_DESC_SIZE] __attribute__((aligned(4)));

// Infinikeys USB HID descriptor.
extern uint8_t IK_USB_HIDDescriptor[IK_HID_DESC_SIZE] __attribute__((aligned(4)));

// Infinikeys USB device qualifier descriptor.
extern uint8_t IK_USB_DeviceQualifierDescriptor[USB_LEN_DEV_QUALIFIER_DESC] __attribute__((aligned(4)));

// Infinikeys USB HID report descriptor.
extern uint8_t IK_USB_HIDReportDescriptor[IK_HID_REPORT_DESC_SIZE] __attribute__((aligned(4)));

#endif /* IK_PLATFORM_STM32_CUBE */

#endif /* INFINIKEYS_STM32CUBE_USB_DESCRIPTORS_H_ */
