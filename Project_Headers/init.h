/*
 * init.h
 *
 *  Created on: Dec 17, 2015
 *      Author: lenovo
 */

#ifndef INIT_H_
#define INIT_H_

//*************************************************************************
//*	 *************************��ʼ������*************************	      *
//*************************************************************************
void initALL(void);	
void disableWatchdog(void);
void initModesAndClock(void);
void initEMIOS_0Image(void);
void initTestIO(void);
void enableIrq(void);
void initLINFlex_0_UART(void);
				
//*************************************************************************
//*		*************************�ӿں���***********************	      *
//*************************************************************************

//***********************�������ӿں���**********************************************************************//
//void SET_motor(signed int leftSpeed,signed int rightSpeed);//5kHz ����ת,Ҫ��λ     
//void SET_steer(unsigned int steer);	//50Hz ռ�ձ�:7.5%+-5% ��λ��50000*7.5%=3750  
//*************************�����ӿں���************************************************************************//
//void LINFlex_TX(unsigned char data);
//void LINFlex_RX_Interrupt(void);



#endif /* INIT_H_ */
