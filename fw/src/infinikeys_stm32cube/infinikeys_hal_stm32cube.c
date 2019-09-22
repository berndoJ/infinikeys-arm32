/*----------------------------------------------------------------
 * FILENAME :		infinikeys_hal_stm32cube.c
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Infinikeys STM32 Cube HAL module.
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	21.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		Infinikeys hardware abstraction layer for the STM32 Cube
 * 		software platform.
 * 
 *--------------------------------------------------------------*/

#include "infinikeys_stm32cube/infinikeys_hal_stm32cube.h"

#if defined(IK_PLATFORM_STM32_CUBE)

/* --------------------------------------------------------------
 * DEFINITIONS
 * ------------------------------------------------------------*/

#define _SENSE_LINE(i) _sense_ports[i], _sense_pins[i]
#define _PROBE_LINE(i) _probe_ports[i], _probe_pins[i]

/* --------------------------------------------------------------
 * VARIABLE DEFINITIONS
 * ------------------------------------------------------------*/

static GPIO_TypeDef* const _sense_ports[IK_MATRIX_SENSE_LINE_COUNT] = IK_STM32CUBE_HAL_MATRIX_SENSE_LINE_PORTS;
static const uint16_t _sense_pins[IK_MATRIX_SENSE_LINE_COUNT] = IK_STM32CUBE_HAL_MATRIX_SENSE_LINE_PINS;
static GPIO_TypeDef* const _probe_ports[IK_MATRIX_PROBE_LINE_COUNT] = IK_STM32CUBE_HAL_MATRIX_PROBE_LINE_PORTS;
static const uint16_t _probe_pins[IK_MATRIX_PROBE_LINE_COUNT] = IK_STM32CUBE_HAL_MATRIX_PROBE_LINE_PINS;

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

void IK_HAL_Setup(void)
{
	// Set all probe lines to LOW.
	for (uint8_t i = 0; i < IK_MATRIX_PROBE_LINE_COUNT; i++)
	{
		HAL_GPIO_WritePin(_PROBE_LINE(i), GPIO_PIN_RESET);
	}
}

void IK_HAL_SetMatrixProbeLine(uint8_t probe_line, IK_LogicLevel_t state)
{
	if (probe_line >= IK_MATRIX_PROBE_LINE_COUNT)
		return;
	switch (state)
	{
	case IK_LOGIC_LEVEL_HIGH:
		HAL_GPIO_WritePin(_PROBE_LINE(probe_line), GPIO_PIN_SET);
		break;
	case IK_LOGIC_LEVEL_LOW:
	default:
		HAL_GPIO_WritePin(_PROBE_LINE(probe_line), GPIO_PIN_RESET);
		break;
	}
}

IK_LogicLevel_t IK_HAL_ReadMatrixSenseLine(uint8_t sense_line)
{
	if (sense_line >= IK_MATRIX_SENSE_LINE_COUNT)
		return IK_LOGIC_LEVEL_LOW;
	return HAL_GPIO_ReadPin(_SENSE_LINE(sense_line)) ? IK_LOGIC_LEVEL_HIGH : IK_LOGIC_LEVEL_LOW;
}

#endif
