/*----------------------------------------------------------------
 * FILENAME :		infinikeys_hal.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Common HAL inclusion header.
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	21.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		Header for including a infinikeys HAL module.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_HAL_H_
#define INFINIKEYS_HAL_H_

#if defined(IK_PLATFORM_STM32_CUBE)
#	include "infinikeys_hal_stm32cube.h"
#else
#	warning No HAL platform specified.
void IK_HAL_Setup(void) {}
void IK_HAL_SetMatrixProbeLine(uint8_t probe_line, IK_LogicLevel_t state) {}
IK_LogicLevel_t IK_HAL_ReadMatrixSenseLine(uint8_t sense_line) { return IK_LOGIC_LEVEL_LOW; }
void IK_HAL_SetRGBLED(uint16_t led_id, uint8_t r, uint8_t g, uint8_t b) {}
void IK_HAL_SetMonochromeLED(uint16_t led_id, uint8_t intensity) {}
void IK_HAL_SetDualStateMonochromeLED(uint16_t led_id, IK_Bool_t enabled) {}
#endif

#endif /* INFINIKEYS_HAL_H_ */
