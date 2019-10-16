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

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

void IK_Lighting_Init(void)
{

}

void IK_Lighting_Setup(IK_LightingConfig_t cfg)
{
	lighting_handle.LEDs = malloc(sizeof(IK_LED_t * cfg.LEDCount));

	if (lighting_handle.LEDs == NULL)
		return;

	lighting_handle.Config = cfg;
	lighting_handle.Configured = TRUE;
}

void IK_Lighting_Update(void)
{
	// Update all registered LEDs.
}
