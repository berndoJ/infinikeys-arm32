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

/*
 * Description
 * Initiates a new keyboard matrix state poll.
 *
 * Parameters
 * - uint8_t* pressed_keys_table: Pointer to the pressed keys table the poll function should store the results in.
 * - uint16_t pressed_keys_table_size: Size of the pressed keys table.
 */
void _IK_ACQ_Poll(uint8_t* pressed_keys_table, uint16_t pressed_keys_table_size);

#endif /* INFINIKEYS_ACQ_H_ */
