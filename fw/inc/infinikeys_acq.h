/*----------------------------------------------------------------
 * FILENAME :		infinikeys_acq.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Key state acquisition module.
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	16.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		This module deals with the acquisition of keystates from
 * 		the keyboard matrix and updates the keystate table in
 * 		infinikeys.h.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_ACQ_H_
#define INFINIKEYS_ACQ_H_

#include "infinikeys_common.h"

/* --------------------------------------------------------------
 * FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

/* Description
 * Configures the InfiniKeys key state acquisition module.
 *
 * Parameters
 * - uint8_t* p_pressedkeys_table: Pointer to the pressed keys table the acquisition module should use.
 * - uint16_t pressedkeys_table_size: Size of the pressed keys table.
 */
void _IK_ACQ_Config(uint8_t* p_pressedkeys_table, uint16_t pressedkeys_table_size);

/*
 * Description
 * Initiates a new keyboard matrix state poll.
 */
void _IK_ACQ_Poll(void);

#endif /* INFINIKEYS_ACQ_H_ */
