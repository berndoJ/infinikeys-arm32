/*----------------------------------------------------------------
 * FILENAME :		infinikeys.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Main extension file.
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	16.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		DESCRIPTION_OF_FILE
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_H_
#define INFINIKEYS_H_

// Include the project's common inclusion header file.
#include "infinikeys_common.h"

/* --------------------------------------------------------------
 * FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

uint8_t IK_Init(void);
uint8_t IK_DeInit(void);

void IK_KeyboardPollCyleTick(void);

#endif /* INFINIKEYS_H_ */
