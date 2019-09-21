/*----------------------------------------------------------------
 * FILENAME :		infinikeys_hal_stm32cube.h
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

#if defined(IK_PLATFORM_STM32_CUBE)
#ifndef INFINIKEYS_HAL_STM32CUBE_H_
#define INFINIKEYS_HAL_STM32CUBE_H_

#include "infinikeys_common.h"

#if defined(IK_PLATFORM_STM32_CUBE_DEVICE_F1XX)
#	include "stm32f1xx_hal.h"
#else
#	error IK_PLATFORM_STM32_CUBE_DEVICE_XXXX not defined.
#endif

/* --------------------------------------------------------------
 * FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

/*
 * Description
 * Sets up the infinikeys HAL module.
 */
void IK_HAL_Setup(void);

/*
 * Description
 * Sets the specified matrix probe line to the specified logic
 * level.
 *
 * Parameters
 * - uint8_t probe_line: The probe line to set the logic level of.
 * - uint8_t state: The new logic level of the specified probe line.
 */
void IK_HAL_SetMatrixProbeLine(uint8_t probe_line, IK_LogicLevel_t state);

/*
 * Description
 * Reads the specified matrix sense line and returns its logic state.
 *
 * Returns
 * The logic state of the matrix sense line specified.
 */
IK_LogicLevel_t IK_HAL_ReadMatrixSenseLine(uint8_t sense_line);

#endif /* INFINIKEYS_HAL_STM32CUBE_H_ */
#endif /* IK_PLATFORM_STM32_CUBE */
