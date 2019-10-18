/*----------------------------------------------------------------
 * FILENAME :		infinikeys_lighting.c
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

#include "infinikeys_lighting.h"

#include <stdlib.h>

/* --------------------------------------------------------------
 * VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

static IK_LightingHandle_t lighting_handle;

static IK_AnimationPlane_t anim_plane;

/* --------------------------------------------------------------
 * STATIC FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

static uint8_t _IK_ConvertRGBToMonochrome(IK_LightColor_t col);

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

void IK_Lighting_Init(void)
{

}

void IK_Lighting_Setup(IK_LightingConfig_t cfg)
{
	lighting_handle.LEDs = malloc(sizeof(IK_LED_t) * cfg.LEDCount);

	if (lighting_handle.LEDs == NULL)
		return;

	lighting_handle.Config = cfg;
	lighting_handle.Configured = TRUE;
}

void IK_Lighting_Update(void)
{
	// Update all registered LEDs.
	for (uint16_t i_led; i_led < lighting_handle.Config.LEDCount; i_led++)
	{
		IK_LED_t c_led = lighting_handle.LEDs[i_led];

		// Get new led color value
		IK_Color_t new_color;
		switch (c_led.LightingType)
		{
		case LIGHTING_TYPE_STATIC:
			new_color = ((IK_StaticLEDConfig_t*)c_led.LEDConfig)->Color;
			break;
		case LIGHTING_TYPE_ANIMATED:
			// TODO: Code animation.
			break;
		case LIGHTING_TYPE_CONDITIONAL:
			// TODO: Code conditonal type.
			break;
		default:
			break;
		}

		uint8_t* status_buffer;

		// Switch led type
		switch (c_led.ChromaticType)
		{
		case LIGHTING_RGB_LED:
			status_buffer = malloc(sizeof(uint8_t) * 3);

			status_buffer[0] = new_color.Red;
			status_buffer[1] = new_color.Green;
			status_buffer[2] = new_color.Blue;

			c_led.HALUpdateFunc(3, status_buffer);
			break;
		case LIGHTING_MONOCHROME_LED:
			status_buffer = malloc(sizeof(uint8_t));

			status_buffer[0] = _IK_ConvertRGBToMonochrome(new_color);

			c_led.HALUpdateFunc(1, status_buffer);
			break;
		case LIGHTING_MONOCHROME_LED_ONOFF:
			status_buffer = malloc(sizeof(uint8_t));

			status_buffer[0] = (_IK_ConvertRGBToMonochrome(new_color)) > 0 ? 1 : 0;

			c_led.HALUpdateFunc(1, status_buffer);
			break;
		default:
			break;
		}
	}
}

IK_Color_t IK_Lighting_AnimPlaneGetColAt(IK_Vector2f_t loc)
{
	for (uint16_t i = 0; i < anim_plane.VectorCount; i++)
	{

	}
}

void IK_Lighting_AnimPlaneUpdate(void)
{

}

/* --------------------------------------------------------------
 * STATIC FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

static uint8_t _IK_ConvertRGBToMonochrome(IK_LightColor_t col)
{
	return (uint8_t)(((uint16_t)col.Red + (uint16_t)col.Green + (uint16_t)col.Blue) / 3);
}
