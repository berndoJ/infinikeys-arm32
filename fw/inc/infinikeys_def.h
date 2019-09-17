/*----------------------------------------------------------------
 * FILENAME :		infinikeys_def.h
 * PROJECT :		infinikeys-arm32
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Definintion file of this project.
 * 
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	16.09.2019	
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		Definintion file of this project.
 * 
 *--------------------------------------------------------------*/

#ifndef INFINIKEYS_DEF_H_
#define INFINIKEYS_DEF_H_

#include "infinikeys_cfg.h"

#define __INFINIKEYS

#define IK_LOGIC_LEVEL_LOW							0x00
#define IK_LOGIC_LEVEL_HIGH							0x01

#define IK_PHYSICAL_KEY_COUNT						(IK_MATRIX_PROBE_LINE_COUNT * IK_MATRIX_SENSE_LINE_COUNT)

#define IK_MATRIX_ID_FROM_LINES(p,s)				((p * IK_MATRIX_SENSE_LINE_COUNT) + s)

#endif /* INFINIKEYS_DEF_H_ */
