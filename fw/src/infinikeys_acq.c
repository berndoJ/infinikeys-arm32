/*----------------------------------------------------------------
 * FILENAME :		infinikeys_acq.c
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

#include "infinikeys_acq.h"

#include "infinikeys_hal.h"

/* --------------------------------------------------------------
 * STATIC VARIABLES
 * ------------------------------------------------------------*/

/*
 * Pointer to the pressed keys table.
 */
static uint8_t* _pressedkeys_table;

/*
 * Size of the pressed keys table.
 */
static uint16_t _pressedkeys_table_size;

/*
 * Callback function pointer that gets called after completion of a keyboard poll.
 */
static void (*_poll_callback_func)(void);

/* --------------------------------------------------------------
 * FUNCTION DEFINITIONS
 * ------------------------------------------------------------*/

void _IK_ACQ_Poll(void)
{
	// Clear the pressed keys table.
	for (uint16_t i = 0; i < _pressedkeys_table_size; i++)
	{
		_pressedkeys_table[i] = 0x00;
	}
	// Index for writing to the table.
	uint16_t pressedkeys_index = 0;

	// Before a poll, set all probe lines to LOW.
	for (uint8_t probe_line_index = 0; probe_line_index < IK_MATRIX_PROBE_LINE_COUNT; probe_line_index++)
	{
		IK_HAL_SetMatrixProbeLine(probe_line_index, IK_LOGIC_LEVEL_LOW);
	}

	// Read the whole matrix.
	for (uint8_t probe_line_index = 0; probe_line_index < IK_MATRIX_PROBE_LINE_COUNT; probe_line_index++)
	{
		// Set the probe line level to HIGH.
		IK_HAL_SetMatrixProbeLine(probe_line_index, IK_LOGIC_LEVEL_HIGH);

		// Loop over the sense lines and read their status.
		for (uint8_t sense_line_index = 0; sense_line_index < IK_MATRIX_SENSE_LINE_COUNT; sense_line_index++)
		{
			// Check if the key is pressed.
			if (IK_HAL_ReadMatrixSenseLine(sense_line_index) == IK_LOGIC_LEVEL_HIGH)
			{
				if (pressedkeys_index < _pressedkeys_table_size)
				{
					_pressedkeys_table[pressedkeys_index] = IK_MATRIX_ID_FROM_LINES(probe_line_index, sense_line_index);
					pressedkeys_index++;
				}
				//else
				//{
					// Key pressed but could not be registered because the pressed keys table is too small.
				//}
			}
		}
	}

	// Call the callback function after completion of a poll.
	_poll_callback_func();
}

void _IK_ACQ_Config(uint8_t* p_pressedkeys_table, uint16_t pressedkeys_table_size, void (*poll_callback_func)(void))
{
	_pressedkeys_table = p_pressedkeys_table;
	_pressedkeys_table_size = pressedkeys_table_size;
	_poll_callback_func = poll_callback_func;
}
