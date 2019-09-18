/*----------------------------------------------------------------
 * FILENAME :		infinikeys_actionhandler.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Handler for Keyboard Actions.
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	18.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		Handles keyboard actions, similar to macros.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_ACTIONHANDLER_H_
#define INFINIKEYS_ACTIONHANDLER_H_

#include "infinikeys_common.h"

void IK_ACT_ExecuteRaw(uint8_t* raw_data, uint16_t raw_data_size);

#endif /* INFINIKEYS_ACTIONHANDLER_H_ */
