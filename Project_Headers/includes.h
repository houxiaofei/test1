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

#define Y0 SIU.GPDI[56].R
#define Y1 SIU.GPDI[55].R
#define Y2 SIU.GPDI[50].R
#define Y3 SIU.GPDI[49].R
#define Y4 SIU.GPDI[52].R
#define Y5 SIU.GPDI[51].R
#define Y6 SIU.GPDI[54].R
#define Y7 SIU.GPDI[53].R


//		SIU.PCR[49].R = 0x0102;//   D1_Y3
//		SIU.PCR[50].R = 0x0102;//   D2_Y2
//		SIU.PCR[51].R = 0x0102;//   D3_Y5
//		SIU.PCR[52].R = 0x0102;//   D4_Y4
//		SIU.PCR[53].R = 0x0102;//   D5_Y7
//		SIU.PCR[54].R = 0x0102;//   D6_Y6
//		SIU.PCR[55].R = 0x0102;//   D7_Y1
//		SIU.PCR[56].R = 0x0102;//   D8_Y0

#endif /* INCLUDE_H_ */
