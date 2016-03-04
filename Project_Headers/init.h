/*
 * init.h
 *
 *  Created on: Dec 17, 2015
 *      Author: lenovo
 */

#ifndef INIT_H_
#define INIT_H_

//*************************************************************************
//*	 *************************初始化函数*************************	      *
//*************************************************************************
void initALL(void);	
void disableWatchdog(void);
void initModesAndClock(void);
void initEMIOS_0Image(void);
void initTestIO(void);
void enableIrq(void);
void initLINFlex_0_UART(void);
				
//*************************************************************************
//*		*************************接口函数***********************	      *
//*************************************************************************

//***********************电机舵机接口函数**********************************************************************//
//void SET_motor(signed int leftSpeed,signed int rightSpeed);//5kHz 正反转,要限位     
//void SET_steer(unsigned int steer);	//50Hz 占空比:7.5%+-5% 中位：50000*7.5%=3750  
//*************************蓝牙接口函数************************************************************************//
//void LINFlex_TX(unsigned char data);
//void LINFlex_RX_Interrupt(void);



#endif /* INIT_H_ */
