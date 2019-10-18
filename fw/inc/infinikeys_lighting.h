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

/*
 * Description
 * Describes a type of an LED. Used to discriminate between
 * RGB LEDs and monochrome LEDs.
 */
typedef enum {
	LIGHTING_RGB_LED,
	LIGHTING_MONOCHROME_LED,
	LIGHTING_MONOCHROME_LED_ONOFF
} IK_LEDChromaticType_t;

/* --------------------------------------------------------------
 * STRUCTS
 * ------------------------------------------------------------*/

/*
 * Description
 * Describes a RGB color value.
 */
typedef struct {
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
} IK_Color_t;

/*
 * Description
 * Describes an LED on the keyboard.
 */
typedef struct {
	IK_Bool_t Enabled;
	IK_LEDChromaticType_t ChromaticType;
	IK_LightingType_t LightingType;
	void* LEDConfig;
	void (*HALUpdateFunc)(uint8_t status_buffer_len, uint8_t* status_buffer);
} IK_LED_t;

/*
 * Description
 * Configuration data structure for static LEDs.
 */
typedef struct {
	IK_Color_t Color;
} IK_StaticLEDConfig_t;

/*
 * Description
 * Configuration data structure for LED animated by the
 * animation plane.
 */
typedef struct {
	IK_Vector2f_t AnimationPlaneVector;
} IK_AnimatedLEDConfig_t;

/*
 * Description
 * Configuration data structure for conditionally activated
 * LEDs.
 */
typedef struct {
	IK_ConditionalType_t Type;
	uint16_t ParametersSize;
	uint8_t* Parameters;
} IK_ConditionalLEDConfig_t;



typedef struct {
	uint16_t LEDCount;
} IK_LightingConfig_t;

typedef struct {
	IK_LightingConfig_t Config;
	IK_Bool_t Configured;
	IK_Bool_t GlobalLightingEnabled;
	IK_LED_t* LEDs;
} IK_LightingHandle_t;





typedef struct {
	IK_Vector2f_t Vector;
	IK_Color_t Color;
} IK_ColorVector_t;

typedef struct {
	uint32_t AnimStartTimeOffset; // (n) millisec after animation start.
	uint16_t AnimVectorCount;
	IK_ColorVector_t* AnimVectors;
} IK_AnimationFrame_t;

typedef struct {
	uint32_t FrameUpdateDelay; // Milliseconds - Smallest resolution
	uint16_t FrameCount;
	IK_AnimationFrame_t* Frames;
} IK_Animation_t;

typedef struct {
	uint16_t VectorCount;
	IK_ColorVector_t* Vectors;
} IK_AnimationPlane_t;

/* --------------------------------------------------------------
 * FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

/*
 * Description
 * Initializes the infinikeys lighting module. This function does
 * not activate / configure the lighting module.
 */
void IK_Lighting_Init(void);

void IK_Lighting_Setup(IK_LightingConfig_t cfg);

void IK_Lighting_Update(void);

IK_Color_t IK_Lighting_AnimPlaneGetColAt(IK_Vector2f_t loc);
void IK_Lighting_AnimPlaneUpdate(void);


#endif /* INFINIKEYS_LIGHTING_H_ */
