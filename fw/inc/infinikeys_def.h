/*----------------------------------------------------------------
 * FILENAME :		infinikeys_def.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Definintion file of this project.
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	16.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		Definintion file of this project.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_DEF_H_
#define INFINIKEYS_DEF_H_

// DEFINE ONLY WHEN DEBUG CONFIG SHOULD BE USED.
//#define INFINIKEYS_USE_DEBUG_CONFIG

#if !defined(INFINIKEYS_USE_DEBUG_CONFIG)
#	include "infinikeys_cfg.h"
#else
#	define IK_DEBUG_CONFIG
#	define IK_MATRIX_PROBE_LINE_COUNT		10
#	define IK_MATRIX_SENSE_LINE_COUNT		10
#	define IK_KEY_ROLLOVER					5
#endif

#if defined(IK_PLATFORM_STM32_CUBE)
#else
#	warning No Infinikeys platform specified.
#endif

/* --------------------------------------------------------------
 * DEFINITIONS
 * ------------------------------------------------------------*/

#define IK_PHYSICAL_KEY_COUNT						(IK_MATRIX_PROBE_LINE_COUNT * IK_MATRIX_SENSE_LINE_COUNT)
#define IK_KEY_MAP_TABLE_MATRIX_SIZE				(IK_PHYSICAL_KEY_COUNT + 1)

#define IK_MATRIX_ID_FROM_LINES(p,s)				((p * IK_MATRIX_SENSE_LINE_COUNT) + s + 1)

#define IK_NTH_BIT(n)								(1 << n)

#define IK_KEY_MAP_MODIFIER_TYPE_HID				0x00
#define IK_KEY_MAP_MODIFIER_TYPE_LAYER				0x01

#define IK_KEYBOARD_HID_REPORT_ID					0x01
#define IK_CFG_HID_REPORT_ID						0x02

/*
 * Configuration Command Allocation:
 * 0x00       :		Test command. (Used for testing firmware, ...; can be ignored)
 * 0x01 - 0x0f:		Basic configuration control commands.
 * 0x80 - 0x8f:		Key-mapping related commands.
 */

/*
 * TEST command:
 */
#define IK_CFG_CMD_TEST								0x00

/*
 * SET_KEYMAP command:
 * Adds a new key map with the given values to the key map table.
 * [0] - Key Layer (0x00 - 0xff)
 * [1] - Matrix ID LOWBYTE (0x00 - 0xff)
 * [2] - Matrix ID HIBYTE (0x00 - 0xff)
 * [3] - Key Map Type - According to IK_KeyMapType_t enum values (see IK_KeyMapType_t for min/max values)
 * [4] - Map Data Size - In bytes (0x00 - 0x3a)
 * [5 - 62] - Map Data (max. 58 bytes) (0x00 - 0xff)
 */
#define IK_CFG_CMD_SET_KEYMAP						0x80

/* --------------------------------------------------------------
 * STRUCTS, ENUMS AND TYPEDEFS
 * ------------------------------------------------------------*/

/*
 * Description
 * This enum type is used to represent a type of key map.
 *
 * Key map types:
 * - KEYMAP_MODIFIER: A key map to a modifier key.
 * - KEYMAP_STATIC: A static key map - just a normal key - such as the "A" key.
 * - KEYMAP_ACTION: A key map to an action. (Only used for macro keys)
 * - KEYMAP_NONE: The key is disabled.
 */
typedef enum {
	KEYMAP_MODIFIER = 0,
	KEYMAP_STATIC = 1,
	KEYMAP_ACTION = 2,
	KEYMAP_NONE = 3
} IK_KeyMapType_t;

/*
 * Description
 * Represents a logic level.
 *
 * IK Logic Levels:
 * - IK_LOGIC_LEVEL_LOW: Represents a 0 or low logic level.
 * - IK_LOGIC_LEVEL_HIGH: Represents a 1 or high logic level.
 */
typedef enum {
	IK_LOGIC_LEVEL_LOW = 0,
	IK_LOGIC_LEVEL_HIGH = 1
} IK_LogicLevel_t;

/*
 * Description
 * Struct which represents a key map. Through a struct of this
 * type a key map can be represented - for example mapping
 * the physical key "S" to the HID key "A" (through a static
 * key mapping in this case).
 */
typedef struct {
	IK_KeyMapType_t Type;
	uint16_t DataSize;
	uint8_t* Data;
} IK_KeyMap_t;

#endif /* INFINIKEYS_DEF_H_ */
