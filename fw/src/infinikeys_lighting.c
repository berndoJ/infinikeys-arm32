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
#include <math.h>
#include "infinikeys_hal.h"

/* --------------------------------------------------------------
 * VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

IK_LightingHandle_t IK_Lighting_Handle;

static IK_AnimationPlane_t anim_plane;
static IK_Animation_t anim;
static uint32_t anim_offset = 0;

/* --------------------------------------------------------------
 * STATIC FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

static uint8_t _IK_ConvertRGBToMonochrome(IK_Color_t col);
static float _IK_Lighting_Vec2f_Dist(IK_Vector2f_t a, IK_Vector2f_t b);
static float _IK_Lighting_LengthIntensityFunc(float l, float d);
static IK_Color_t _IK_Lighting_ColorTransition(IK_Color_t a, IK_Color_t b, float split);

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

void IK_Lighting_Init(void)
{
	/*anim.TransitionCount = 0;
	anim.Transitions = NULL;
	anim.AnimVectorCount = 0;
	anim.AnimVectors = NULL;
	anim.Duration = 0;*/
	anim.TransitionCount = 6;
	anim.Transitions = malloc(sizeof(IK_AnimationTransition_t) * 6);

	anim.AnimVectorCount = 2;
	anim.AnimVectors = malloc(sizeof(IK_Vector2f_t) * 2);

	anim.Transitions[0].AnimVectorIndex = 0;
	anim.Transitions[0].TransitionOffset = 0;
	anim.Transitions[0].TransitionDuration = 1000;
	anim.Transitions[0].ColorFrom.Red = 0xff;
	anim.Transitions[0].ColorFrom.Green = 0x00;
	anim.Transitions[0].ColorFrom.Blue = 0x00;
	anim.Transitions[0].ColorTo.Red = 0x00;
	anim.Transitions[0].ColorTo.Green = 0xff;
	anim.Transitions[0].ColorTo.Blue = 0x00;

	anim.Transitions[1].AnimVectorIndex = 0;
	anim.Transitions[1].TransitionOffset = 1000;
	anim.Transitions[1].TransitionDuration = 1000;
	anim.Transitions[1].ColorFrom.Red = 0x00;
	anim.Transitions[1].ColorFrom.Green = 0xff;
	anim.Transitions[1].ColorFrom.Blue = 0x00;
	anim.Transitions[1].ColorTo.Red = 0x00;
	anim.Transitions[1].ColorTo.Green = 0x00;
	anim.Transitions[1].ColorTo.Blue = 0xff;

	anim.Transitions[2].AnimVectorIndex = 0;
	anim.Transitions[2].TransitionOffset = 2000;
	anim.Transitions[2].TransitionDuration = 1000;
	anim.Transitions[2].ColorFrom.Red = 0x00;
	anim.Transitions[2].ColorFrom.Green = 0x00;
	anim.Transitions[2].ColorFrom.Blue = 0xff;
	anim.Transitions[2].ColorTo.Red = 0xff;
	anim.Transitions[2].ColorTo.Green = 0x00;
	anim.Transitions[2].ColorTo.Blue = 0x00;


	anim.Transitions[3].AnimVectorIndex = 1;
	anim.Transitions[3].TransitionOffset = 0;
	anim.Transitions[3].TransitionDuration = 1000;
	anim.Transitions[3].ColorFrom.Red = 0xff;
	anim.Transitions[3].ColorFrom.Green = 0x00;
	anim.Transitions[3].ColorFrom.Blue = 0x00;
	anim.Transitions[3].ColorTo.Red = 0x00;
	anim.Transitions[3].ColorTo.Green = 0xff;
	anim.Transitions[3].ColorTo.Blue = 0x00;

	anim.Transitions[4].AnimVectorIndex = 1;
	anim.Transitions[4].TransitionOffset = 1000;
	anim.Transitions[4].TransitionDuration = 1000;
	anim.Transitions[4].ColorFrom.Red = 0x00;
	anim.Transitions[4].ColorFrom.Green = 0xff;
	anim.Transitions[4].ColorFrom.Blue = 0x00;
	anim.Transitions[4].ColorTo.Red = 0x00;
	anim.Transitions[4].ColorTo.Green = 0x00;
	anim.Transitions[4].ColorTo.Blue = 0xff;

	anim.Transitions[5].AnimVectorIndex = 1;
	anim.Transitions[5].TransitionOffset = 2000;
	anim.Transitions[5].TransitionDuration = 1000;
	anim.Transitions[5].ColorFrom.Red = 0x00;
	anim.Transitions[5].ColorFrom.Green = 0x00;
	anim.Transitions[5].ColorFrom.Blue = 0xff;
	anim.Transitions[5].ColorTo.Red = 0xff;
	anim.Transitions[5].ColorTo.Green = 0x00;
	anim.Transitions[5].ColorTo.Blue = 0x00;


	anim.AnimVectors[0].x = 0.1F;
	anim.AnimVectors[0].y = 0.5F;

	anim.AnimVectors[1].x = 0.9F;
	anim.AnimVectors[1].y = 0.5F;

	anim.Duration = 3000;

	anim_plane.VectorCount = 0;
	anim_plane.Vectors = NULL;
}

void IK_Lighting_Setup(IK_LightingConfig_t cfg)
{
	IK_Lighting_Handle.LEDs = malloc(sizeof(IK_LED_t) * cfg.LEDCount);

	if (IK_Lighting_Handle.LEDs == NULL)
		return;

	IK_Lighting_Handle.Config = cfg;
	IK_Lighting_Handle.Configured = TRUE;
}

void IK_Lighting_Update(void)
{
	if (IK_Lighting_Handle.LEDs == NULL)
		return;

	// Update the animation plane.
	anim_plane.VectorCount = anim.AnimVectorCount;
	anim_plane.Vectors = realloc(anim_plane.Vectors, anim_plane.VectorCount);
	if (anim_plane.Vectors != NULL)
	{
		anim_offset++;
		if (anim_offset > anim.Duration)
			anim_offset = 0;
		for (uint16_t anim_vec_idx = 0; anim_vec_idx < anim.AnimVectorCount; anim_vec_idx++)
		{
			IK_Vector2f_t anim_vec = anim.AnimVectors[anim_vec_idx];
			for (uint16_t i_t = 0; i_t < anim.TransitionCount; i_t++)
			{
				IK_AnimationTransition_t t = anim.Transitions[i_t];
				if (t.AnimVectorIndex == anim_vec_idx)
				{
					if (t.TransitionOffset <= anim_offset && t.TransitionOffset + t.TransitionDuration > anim_offset)
					{
						anim_plane.Vectors[anim_vec_idx].Vector = anim_vec;
						anim_plane.Vectors[anim_vec_idx].Color = _IK_Lighting_ColorTransition(t.ColorFrom, t.ColorTo, (float)(anim_offset - t.TransitionOffset) / t.TransitionDuration);
					}
				}
			}
		}
	}

	// Update all registered LEDs.
	for (uint16_t i_led = 0; i_led < IK_Lighting_Handle.Config.LEDCount; i_led++)
	{
		IK_LED_t c_led = IK_Lighting_Handle.LEDs[i_led];

		// Get new led color value
		IK_Color_t new_color = { 0, 0, 0 };
		switch (c_led.LightingType)
		{
		case LIGHTING_TYPE_STATIC:
			;
			IK_StaticLEDConfig_t* s_cfg = (IK_StaticLEDConfig_t*)c_led.LEDConfig;

			if (s_cfg == NULL)
				break;

			new_color.Red = s_cfg->Color.Red;
			new_color.Green = s_cfg->Color.Green;
			new_color.Blue = s_cfg->Color.Blue;

			break;
		case LIGHTING_TYPE_ANIMATED:
			;
			IK_AnimatedLEDConfig_t* a_cfg = (IK_AnimatedLEDConfig_t*)c_led.LEDConfig;

			if (a_cfg == NULL)
				break;

			new_color = IK_Lighting_AnimPlaneGetColAt(a_cfg->AnimationPlaneVector);

			break;
		case LIGHTING_TYPE_CONDITIONAL:
			// TODO: Code conditonal type.
			break;
		default:
			break;
		}

		// Switch led type
		switch (c_led.ChromaticType)
		{
		case LIGHTING_RGB_LED:
			IK_HAL_SetRGBLED(c_led.LEDID, new_color.Red, new_color.Green, new_color.Blue);
			break;
		case LIGHTING_MONOCHROME_LED:
			// TODO: Implement!
			break;
		case LIGHTING_MONOCHROME_LED_ONOFF:
			// TODO: Implement!
			break;
		default:
			break;
		}
	}
}

IK_Color_t IK_Lighting_AnimPlaneGetColAt(IK_Vector2f_t loc)
{
	/*
	 * Calculation of the color is done as follows:
	 *
	 * x is the vector of the point the color is searched at.
	 * L_0 to L_n are the color vectors.
	 *
	 * Let I(l) = 1-(l(d)) when l<d and 0 when l>=d, where d is a constant (d>0)
	 * Let gamma = Sum(i=0,n: I(dist(x,L_i)))
	 * rgb(x) = Sum(i=0,n: (I(L_i)/g) * rgb(L_i))
	 */

	// CHECK IF COLOR / ANIMATION VECTORS ARE PRESENT
	if (anim_plane.VectorCount < 1)
	{
		IK_Color_t black = {
				0x00, 0x00, 0x00
		};
		return black;
	}

	// CALCULATE "gamma"
	float gamma = 0;
	for (uint16_t i = 0; i < anim_plane.VectorCount; i++)
	{
		gamma = gamma + _IK_Lighting_Vec2f_Dist(loc, anim_plane.Vectors[i].Vector);
	}

	// CALCULATE FLOAT "rgb"
	float r = 0, g = 0, b = 0;
	float d = 0.5F; // <-- Temporary solution for constant d.
	for (uint16_t i = 0; i < anim_plane.VectorCount; i++)
	{
		float dist = _IK_Lighting_Vec2f_Dist(loc, anim_plane.Vectors[i].Vector);
		r = r + ((_IK_Lighting_LengthIntensityFunc(dist, d) / gamma) * (anim_plane.Vectors[i].Color.Red));
		g = g + ((_IK_Lighting_LengthIntensityFunc(dist, d) / gamma) * (anim_plane.Vectors[i].Color.Green));
		b = b + ((_IK_Lighting_LengthIntensityFunc(dist, d) / gamma) * (anim_plane.Vectors[i].Color.Blue));
	}

	// Create a color.
	IK_Color_t loc_col;
	loc_col.Red = (uint8_t)floorf(r);
	loc_col.Green = (uint8_t)floorf(g);
	loc_col.Blue = (uint8_t)floorf(b);

	return loc_col;
}

void IK_Lighting_AnimPlaneUpdate(void)
{

}

/* --------------------------------------------------------------
 * STATIC FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

static uint8_t _IK_ConvertRGBToMonochrome(IK_Color_t col)
{
	return (uint8_t)(((uint16_t)col.Red + (uint16_t)col.Green + (uint16_t)col.Blue) / 3);
}

static float _IK_Lighting_Vec2f_Dist(IK_Vector2f_t a, IK_Vector2f_t b)
{
	return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}

static float _IK_Lighting_LengthIntensityFunc(float l, float d)
{
	return (l < d) ? (1 - (l / d)) : 0;
}

static IK_Color_t _IK_Lighting_ColorTransition(IK_Color_t a, IK_Color_t b, float split)
{
	IK_Color_t c_out;
	c_out.Red = a.Red + (split * ((int16_t)b.Red - (int16_t)a.Red));
	c_out.Green = a.Green + (split * ((int16_t)b.Green - (int16_t)a.Green));
	c_out.Blue = a.Blue + (split * ((int16_t)b.Blue - (int16_t)a.Blue));
	return c_out;
}
