/*----------------------------------------------------------------
 * FILENAME :		infinikeys_kbcfg.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Dynamic Keyboard Configuration Module
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	17.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		This module is used to manage the local dynamic
 * 		configuration of the keyboard. This configuration can be
 * 		updated dynamically over USB without flashing a new
 * 		firmware to the device.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_KBCFG_H_
#define INFINIKEYS_KBCFG_H_

#include "infinikeys_common.h"

/* --------------------------------------------------------------
 * ENUMS
 * ------------------------------------------------------------*/

/*
 * Description
 * This enum type is used to represent a type of key map.
 *
 * Values
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
 * Describes a type of modifier key.
 *
 * Values
 * - MODIFIER_TYPE_HID: Default HID modifier key. (e.g. L-CTRL, R-SHIFT, ...)
 * - MODIFIER_TYPE_KEY_LAYER: Key layer modifier key.
 */
typedef enum {
	MODIFIER_TYPE_HID = 0,
	MODIFIER_TYPE_KEY_LAYER = 1
} IK_ModifierType_t;

/*
 * Description
 * HID modifier keys.
 *
 * Values
 * - HID_MODIFIER_L_CTRL: Left control key.
 * - HID_MODIFIER_L_SHIFT: Left shift key.
 * - HID_MODIFIER_L_ALT: Left alt key.
 * - HID_MODIFIER_L_GUI: Left GUI key. (Light Windows / Linux / Apple key)
 * - HID_MODIFIER_R_CTRL: Right control key.
 * - HID_MODIFIER_R_SHIFT: Right shit key.
 * - HID_MODIFIER_R_ALT: Right alt key. (AltGr on some QWERTZ layouts)
 * - HID_MODIFIER_R_GUI: Right GUI key. (Right Windows / Linux / Apple key)
 */
typedef enum {
	HID_MODIFIER_L_CTRL = 0,
	HID_MODIFIER_L_SHIFT = 1,
	HID_MODIFIER_L_ALT = 2,
	HID_MODIFIER_L_GUI = 3,
	HID_MODIFIER_R_CTRL = 4,
	HID_MODIFIER_R_SHIFT = 5,
	HID_MODIFIER_R_ALT = 6,
	HID_MODIFIER_R_GUI = 7
} IK_HIDModifier_t;

/* --------------------------------------------------------------
 * STRUCTS
 * ------------------------------------------------------------*/

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
	void* Metadata;
} IK_KeyMap_t;

/*
 * Description
 * Represents modifier key map metadata.
 */
typedef struct {
	IK_ModifierType_t ModifierType;
	void* ModifierMetadata;
} IK_ModifierMapMetadata_t;

/*
 * Description
 * Metadata for HID modifier key maps.
 */
typedef struct {
	IK_HIDModifier_t HIDModifierCode;
} IK_HIDModifierMapMetadata_t;

/*
 * Description
 * Metadata for key layer modifier keys.
 */
typedef struct {
	uint8_t KeyLayer;
} IK_KeyLayerModifierMetadata_t;

/*
 * Description
 * Static key map metadata.
 */
typedef struct {
	uint8_t Keycode;
} IK_StaticMapMetadata_t;

/*
 * Description
 * Action / macro key map metadata.
 */
typedef struct {
	IK_Action_t Action;
} IK_ActionMapMetadata_t;

/* --------------------------------------------------------------
 * VARIABLE DECLARATIONS
 * ------------------------------------------------------------*/

/*
 * Pointer to the keyboar configuration key mapping table.
 * The table has following array structure:
 * xx[key_layer][matrix_id]
 */
extern IK_KeyMap_t** IK_CFG_KeyMapTable;

/*
 * The ID of the currently selected / active key layer. This
 * is used to parse keystrokes as they are looked up in the
 * corresponding table of the current key layer. (Possiblility
 * of multiple function layers on top of the normal key map)
 */
extern uint8_t IK_CFG_CurrentKeyLayer;

/* --------------------------------------------------------------
 * FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

/*
 * Description
 * Initialises the keyboard configuration module.
 */
uint8_t IK_CFG_Init(void);

/*
 * Description
 * De-initialises the keyboard configuration module.
 */
void IK_CFG_DeInit(void);

/*
 * Description:
 * This function retrieves the default fallback keyboard layer
 * set by the configuration.
 *
 * Returns uint8_t: ID of the fallback key layer.
 */
uint8_t IK_CFG_GetFallbackKeyLayer(void);

/*
 * Description
 * Sets the current fallback key layer. If the key layer given is
 * not within the span.
 *
 * Parameters
 * - uint8_t new_fb_kay_layer: The new fallback layer ID.
 */
void IK_CFG_SetFallbackKeyLayer(uint8_t new_fb_key_layer);

/*
 * Description
 * Gets the key layer count of the current key matrix table.
 *
 * Returns uint8_t: Key layer count of the current key matrix table.
 */
uint8_t IK_CFG_GetKeyLayerCount(void);

/*
 * Description
 * This function gets a key map from the given matrix id and key layer.
 *
 * Parameters
 * - uint8_t key_layer: The key lay the key map is located on.
 * - uint16_t matrix_id: The matrix id to get the keymap of.
 *
 * Returns IK_KeyMap_t*: Pointer to the key map of the given matrix id on the given key layer.
 */
IK_KeyMap_t* IK_CFG_GetKeyMap(uint8_t key_layer, uint16_t matrix_id);

/*
 * Description
 * Sets a key map of the specified key on the specified layer to
 * the given key map value.
 *
 * Parameters
 * - uint8_t key_layer: The key layer the key map is on.
 * - uint16_t matrix_id: The key which the map refers to.
 * - IK_KeyMap_t key_map: The new key map value to set the map table location to.
 */
void IK_CFG_LoadKeyMapToTable(uint8_t key_layer, uint16_t matrix_id, IK_KeyMap_t key_map);

/*
 * Description
 * Re-initialises the key map table with the given layer
 * count. This function has to be used in order to achieve
 * layer counts greater than 1 because the init function
 * initialises the key map table to consist of only 1 key
 * layer.
 *
 * Parameters
 * - uint8_t layer_count: The key layer count of the reinitialised key map.
 */
void IK_CFG_ReInitKeyMap(uint8_t layer_count);

#endif /* INFINIKEYS_KBCFG_H_ */
