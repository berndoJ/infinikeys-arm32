/*----------------------------------------------------------------
 * FILENAME :		infinikeys_parser.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Keystate parser module.
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	17.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		This module parses the pressed key states to keyboard
 * 		actions. The parsing is made according to the keyboard
 * 		configuration.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_PARSER_H_
#define INFINIKEYS_PARSER_H_

#include "infinikeys_common.h"

/* --------------------------------------------------------------
 * FUNCTION DECLARATIONS
 * ------------------------------------------------------------*/

/*
 * Description
 * -
 *
 * Parameters
 * - uint8_t* pressedkeys_table: Pointer to the pressed keys table. (Array containing all pressed keycodes)
 * - uint16_t pressedkeys_table_size: Size of the pressed keys table.
 */
void _IK_Parser_ParseKeyStates(uint8_t* pressedkeys_table, uint16_t pressedkeys_table_size);

#endif /* INFINIKEYS_PARSER_H_ */
