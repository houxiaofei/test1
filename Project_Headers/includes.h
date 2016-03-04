/*
 * include.h
 *
 *  Created on: Dec 17, 2015
 *      Author: lenovo
 */

#ifndef INCLUDE_H_
#define INCLUDE_H_

#include "MPC5604B.h"
#include "init.h"
#include "video.h"
#include "IntcInterrupts.h"
#include "debug.h"
#include "sci.h"

#define LED0 SIU.GPDO[12].R
#define LED1 SIU.GPDO[13].R
#define LED2 SIU.GPDO[14].R
#define LED3 SIU.GPDO[15].R

#define Y0 SIU.GPDI[50].R
#define Y1 SIU.GPDI[49].R
#define Y2 SIU.GPDI[52].R
#define Y3 SIU.GPDI[51].R
#define Y4 SIU.GPDI[54].R
#define Y5 SIU.GPDI[53].R
#define Y6 SIU.GPDI[56].R
#define Y7 SIU.GPDI[55].R



#endif /* INCLUDE_H_ */
