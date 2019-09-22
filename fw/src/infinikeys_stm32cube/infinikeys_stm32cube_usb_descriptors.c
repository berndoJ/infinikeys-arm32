/*----------------------------------------------------------------
 * FILENAME :		infinikeys_stm32cube_usb_descriptors.c
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

#include "infinikeys_stm32cube/infinikeys_stm32cube_usb_descriptors.h"

#if defined(IK_PLATFORM_STM32_CUBE)

#include "usbd_desc.h"

// Infinikeys USB configuration descriptor.
uint8_t IK_USB_ConfigurationDescriptor[IK_USB_CONFIG_DESC_SIZE] __attribute__((aligned(4))) =
{
	// --- CONFIGURATION DESCRIPTOR ---
	0x09, 										// bLength: Length of this descriptor = 9 bytes.
	USB_DESC_TYPE_CONFIGURATION,				// bDescriptorType: Descriptor type = CONFIGURATION (02h).
	IK_USB_CONFIG_DESC_SIZE, 0x00,				// wTotalLength: Total length including interface and endpoint descriptors.
	0x01,										// bNumInterfaces: Number of interfaces in this configuration.
	0x01,										// bConfigurationValue: Configuration value used by SET_CONFIGURATION to select this configuration.
	0x00,										// iConfiguration: Index of string that describes this configuration.
	0xc0,										// bmAttributes: Specifies a bitmap to describe behavior of this configuration.
	IK_USB_MAX_DEVICE_CURRENT,					// bMaxPower: Maximum power required for this configuration (in 2 mA units).

	// --- IK HID INTERFACE DESCRIPTOR ---
	0x09,										// bLength: Length of this descriptor = 9 bytes.
	USB_DESC_TYPE_INTERFACE,					// bDescriptorType: Descriptor type = INTERFACE (04h).
	0x00,										// bInterfaceNumber: Zero based index of this interface.
	0x00,										// bAlternateSetting: Alternate setting value.
	0x02,										// bNumEndpoints: Number of endpoints used by this interface (not including EP0).
	0x03,										// bInterfaceClass: Interface class = CUSTOM_HID.
	0x00,										// bInterfaceSubclass: Interface subclass. 1 = BOOT, 0 = No BOOT.
	0x00,										// bInterfaceProtocol: Interface protocol. 0 = None, 1 = Keyboard, 2 = Mouse.
	0x00,										// iInterface: Index to string describing this interface.

	// --- IK HID DESCRIPTOR ---
	0x09,										// bLength: Length of this descriptor = 9 bytes.
	IK_HID_DESC_TYPE,							// bDescriptorType: Descriptor type = IK_HID (21h).
	0x11, 0x01,									// bcdHID: HID class specification release number.
	0x00,										// bCountryCode: Hardware target country.
	0x01,										// bNumDescriptors: Number of descriptors.
	IK_HID_REPORT_DESC_TYPE,					// bDescriptorType: Descriptor type.
	IK_HID_REPORT_DESC_SIZE, 0x00,				// bDescriptorLength: Length of the descriptor.

	// --- IK HID EPIN DESCRIPTOR ---
	0x07,										// bLength: Length of this descriptor = 7 bytes.
	USB_DESC_TYPE_ENDPOINT,						// bDescriptorType: Descriptor type = ENDPOINT (05h).
	IK_HID_EPIN_ADDR,							// bEndpointAddress: USB-defined endpoint address.
	0x03,										// bmAttributes: Endpoint Attributes: Interrupt, No Sync, Data Endpoint.
	IK_HID_EPIN_SIZE, 0x00,						// wMaxPacketSize: Maximum packet size for this endpoint.
	IK_HID_EPIN_INTERVAL_MS,					// bInterval: Polling interval in milliseconds for interrupt endpoints.

	// --- IK HID EPOUT DESCRIPTOR ---
	0x07,										// bLength: Length of this descriptor = 7 bytes.
	USB_DESC_TYPE_ENDPOINT,						// bDescriptorType: Descriptor type = ENDPOINT (05h).
	IK_HID_EPOUT_ADDR,							// bEndpointAddress: USB-defined endpoint address.
	0x03,										// bmAttributes: Endpoint Attributes: Interrupt, No Sync, Data Endpoint.
	IK_HID_EPOUT_SIZE, 0x00,					// wMaxPacketSize: Maximum packet size for this endpoint.
	IK_HID_EPOUT_INTERVAL_MS					// bInterval: Polling interval in milliseconds for interrupt endpoints.
};

// Infinikeys USB HID descriptor.
uint8_t IK_USB_HIDDescriptor[IK_HID_DESC_SIZE] __attribute__((aligned(4))) =
{
	// --- IK HID DESCRIPTOR ---
	0x09,										// bLength: Length of this descriptor = 9 bytes.
	IK_HID_DESC_TYPE,							// bDescriptorType: Descriptor type = IK_HID (21h).
	0x11, 0x01,									// bcdHID: HID class specification release number.
	0x00,										// bCountryCode: Hardware target country.
	0x01,										// bNumDescriptors: Number of descriptors.
	IK_HID_REPORT_DESC_TYPE,					// bDescriptorType: Descriptor type.
	IK_HID_REPORT_DESC_SIZE, 0x00				// bDescriptorLength: Length of the descriptor.
};

// Infinikeys USB device qualifier descriptor.
uint8_t IK_USB_DeviceQualifierDescriptor[USB_LEN_DEV_QUALIFIER_DESC] __attribute__((aligned(4))) =
{
	USB_LEN_DEV_QUALIFIER_DESC,					// bLength: Length of this descriptor = 10 bytes.
	USB_DESC_TYPE_DEVICE_QUALIFIER,				// bDescriptorType: Descriptor type = DEVICE_QUALIFIER (06h).
	0x00, 0x02,									// bcdUSB: Identifies the version of the USB specification that this descriptor structure complies with.
	0x00,										// bDeviceClass: Specifies the class code of the device as assigned by the USB specification group.
	0x00,										// bDeviceSubClass: Specifies the subclass code of the device as assigned by the USB specification group.
	0x00,										// bDeviceProtocol: Specifies the protocol code of the device as assigned by the USB specification group.
	0x40,										// bMaxPacketSize0: Specifies the maximum packet size, in bytes, for endpoint zero of the device. The value must be set to 8, 16, 32, or 64.
	0x01,										// bNumConfigurations: Specifies the total number of possible configurations for the device.
	0x00										// bReserved: Reserved. (Set to 00h)
};

// Infinikeys USB HID report descriptor.
uint8_t IK_USB_HIDReportDescriptor[IK_HID_REPORT_DESC_SIZE] __attribute__((aligned(4))) =
{
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x06,                    // USAGE (Keyboard)
	0xa1, 0x01,                    // COLLECTION (Application)

	0x85, 0x01,                    //   REPORT_ID (1)

	0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
	0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
	0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
	0x75, 0x01,                    //   REPORT_SIZE (1)
	0x95, 0x08,                    //   REPORT_COUNT (8)
	0x81, 0x02,                    //   INPUT (Data,Var,Abs)

	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)

	0x95, 0x05,                    //   REPORT_COUNT (5)
	0x75, 0x01,                    //   REPORT_SIZE (1)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
	0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)

	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x75, 0x03,                    //   REPORT_SIZE (3)
	0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)

	0x95, IK_KEY_ROLLOVER,		   //   REPORT_COUNT (VAR)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
	0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
	0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
	0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
	0x81, 0x00,                    //   INPUT (Data,Ary,Abs)

	0xc0,                          // END_COLLECTION


	0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor Defined Page 1)
	0x09, 0x01,                    // USAGE (Vendor Usage 1)
	0xa1, 0x01,                    // COLLECTION (Application)

	0x85, 0x02,                    //   REPORT_ID (2)

	0x06, 0x00, 0xff,              //   USAGE_PAGE (Vendor Defined Page 1)
	0x09, 0x01,                    //   USAGE (Vendor Usage 1)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)
	0x75, 0x08,                    //   REPORT_SIZE (8)/
	0x95, 0x03,                    //   REPORT_COUNT (3)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)

	0xc0                           // END_COLLECTION
};

#endif /* IK_PLATFORM_STM32_CUBE */

