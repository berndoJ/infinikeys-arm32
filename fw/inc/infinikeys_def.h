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

#include "infinikeys_cfg.h"

#if defined(IK_PLATFORM_STM32_CUBE)
#elif defined(INFINIKEYS_DEF_H_)
#else
#error No Infinikeys platform specified.
#endif

/* --------------------------------------------------------------
 * DEFINITIONS
 * ------------------------------------------------------------*/

#define __INFINIKEYS

#define IK_LOGIC_LEVEL_LOW							0x00
#define IK_LOGIC_LEVEL_HIGH							0x01

#define IK_PHYSICAL_KEY_COUNT						(IK_MATRIX_PROBE_LINE_COUNT * IK_MATRIX_SENSE_LINE_COUNT)

#define IK_MATRIX_ID_FROM_LINES(p,s)				((p * IK_MATRIX_SENSE_LINE_COUNT) + s)

#define IK_KEY_MAP_MODIFIER_TYPE_HID				0x00
#define IK_KEY_MAP_MODIFIER_TYPE_LAYER				0x01

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
 */
typedef enum {
	KEYMAP_MODIFIER,
	KEYMAP_STATIC,
	KEYMAP_ACTION
} IK_KeyMapType_t;

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
