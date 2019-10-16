/*----------------------------------------------------------------
 * FILENAME :		infinikeys_lighting.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Keyboard Lighting Module
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	24.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		This module manages the keyboard lighting, separating it
 * 		into the management of physical LEDs, different lighting
 * 		modes per LED, animations and conditional lighting
 * 		effects.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_LIGHTING_H_
#define INFINIKEYS_LIGHTING_H_

#include "infinikeys_common.h"

/* --------------------------------------------------------------
 * ENUMS
 * ------------------------------------------------------------*/

/*
 * Description
 * Specifies the mode of an LED. This mode relates to what color
 * the LED appears as and what animation it follows.
 */
typedef enum {
	LIGHTING_TYPE_DISABLED,
	LIGHTING_TYPE_STATIC,
	LIGHTING_TYPE_ANIMATED,
	LIGHTING_TYPE_CONDITIONAL
} IK_LightingType_t;

/*
 * Description
 * Specifies the type of conditional lighting of an LED.
 */
typedef enum {
	CONDITIONAL_TYPE_KEY_DOWN
} IK_ConditionalType_t;

/* --------------------------------------------------------------
 * STRUCTS
 * ------------------------------------------------------------*/

/*
 * Description
 * Describes a RGB color value including an "alpha" / intensity
 * value which is used to represent the intensity of the LED.
 */
typedef struct {
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
	uint8_t Intensity;
} IK_LightColor_t;

/*
 * Description
 * Describes an LED on the keyboard.
 */
typedef struct {
	IK_LightingType_t LightingType;
	void* LEDConfig;
} IK_LED_t;

/*
 * Description
 * Configuration data structure for static LEDs.
 */
typedef struct {
	IK_LightColor_t Color;
} IK_StaticLEDConfig_t;

/*
 * Description
 * Configuration data structure for LED animated by the
 * animation plane.
 */
typedef struct {
	float AnimX;
	float AnimY;
} IK_AnimatedLEDConfig_t;

/*
 * Description
 * Configuration data structure for conditionally activated
 * LEDs.
 */
typedef struct {
	IK_ConditionalType_t Type;
	uint8_t ParametersSize;
	uint8_t* Parameters;
} IK_ConditionalLEDConfig_t;

#endif /* INFINIKEYS_LIGHTING_H_ */
