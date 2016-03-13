/*
 * init.c
 *
 *  Created on: Dec 17, 2015
 *      Author: lenovo
 */

#include "includes.h"

void initALL(void)
{
	disableWatchdog();
	initModesAndClock();
	initEMIOS_0Image();
	enableIrq();
	initTestIO();
	initLINFlex_0_UART();
	//initOLED();

}

/*********************************************************************************************/
/*********************************  关闭看门狗 **********************************************/
/*********************************************************************************************/
void disableWatchdog(void)
{
	SWT.SR.R = 0x0000c520; /* Write keys to clear soft lock bit */
	SWT.SR.R = 0x0000d928;
	SWT.CR.R = 0x8000010A; /* Clear watchdog enable (WEN) */
}

//*****************************************************************************************************************
//*			 *************************时钟初始化 *******************************************************    	  *
//*****************************************************************************************************************
void initModesAndClock(void) 
{
	ME.MER.R = 0x0000001D;          /* Enable DRUN, RUN0, SAFE, RESET modes */
	//Initialize PLL before turning it on                    
	//设置sysclk
	//CGM.FMPLL_CR.R = 0x02400100;    /* 8 MHz xtal: Set PLL0 to 64 MHz */  
	CGM.FMPLL_CR.R = 0x01280000;      /* 8 MHz xtal: Set PLL0 to 80 MHz */
	//CGM.FMPLL_CR.R = 0x013C0000;    /* 8 MHz xtal: Set PLL0 to 120 MHz */   
	ME.RUN[0].R = 0x001F0064;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL     sysclk选择锁相环时钟*/
	ME.RUNPC[0].R = 0x00000010;    /* Peri. Cfg. 1 settings: only run in RUN0 mode      选择RUN0模式*/
	/*************************PCTL[?] 选择需要时钟模块****************************/
	ME.PCTL[32].R = 0x00; 			/* MPC56xxB/P/S ADC 0: select ME.RUNPC[0] */
	ME.PCTL[48].R = 0x00;           /* MPC56xxB/P/S LINFlex 0: select ME.RUNPC[0] */
	ME.PCTL[68].R = 0x00;           /* MPC56xxB/S SIUL:  select ME.RUNPC[0] */ 
	ME.PCTL[72].R = 0x00;           /* MPC56xxB/S EMIOS 0:  select ME.RUNPC[0] */ 
	//Mode Transition to enter RUN0 mode      
	ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
	ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */ 
	    
	while (ME.GS.B.S_MTRANS) {}     // Wait for mode transition to complete 等待模式转换完成    
	/********************************** Note: could wait here using timer and/or I_TC IRQ*/                          
	while(ME.GS.B.S_CURRENTMODE != 4) {} // Verify RUN0 is the current mode 等待选择RUN0模式
	//开peri0、1、2
	CGM.SC_DC[0].R = 0x80;//LIN
	CGM.SC_DC[1].R = 0x80;//FLEXCAN,DSPI
	CGM.SC_DC[2].R = 0x80;//eMIOS,CTU,ADC
}

//*****************************************************************************************************************
//****************************************中断初始化******************************************************    	  *
//*****************************************************************************************************************
void enableIrq(void) 
{
  INTC.CPR.B.PRI = 0;          /* Single Core: Lower INTC's current priority */
  asm(" wrteei 1");	    	   /* Enable external interrupts */
}

//*****************************************************************************************************************
//************************************视频信号场行中断初始化***********************************************  	  *
//*****************************************************************************************************************
void initEMIOS_0Image(void) 
{
	//eMIOS0 B通道0设置/* EMIOS 0 CH 0: Modulus Counter */
	EMIOS_0.CH[0].CCR.B.UCPRE=0;	    /* Set channel prescaler to divide by 1 */
	EMIOS_0.CH[0].CCR.B.UCPEN = 1;   /* Enable prescaler; uses default divide by 1 */
	//EMIOS_0.CH[0].CCR.B.FREN = 1; 	/* Freeze channel counting when in debug mode */
	EMIOS_0.CH[0].CADR.R = 50000;/********设置周期20ms  50HZ*******/
	EMIOS_0.CH[0].CCR.B.MODE = 0x50; /* Modulus Counter Buffered (MCB) */
	EMIOS_0.CH[0].CCR.B.BSL = 0x3;	/* Use internal counter */
	
	//B14场中断捕捉下降沿
	EMIOS_0.CH[6].CCR.B.MODE = 0x02; // Mode is SAIC, continuous 
	EMIOS_0.CH[6].CCR.B.BSL = 0x01; /* Use counter bus B (default) */
	EMIOS_0.CH[6].CCR.B.EDSEL = 1;  //Both edges
//	EMIOS_0.CH[5].CCR.B.EDPOL=0; //Edge Select falling edge
//	EMIOS_0.CH[5].CCR.B.FEN=1;  //interupt enbale
	SIU.PCR[30].R = 0x0102;  // Initialize pad for eMIOS channel Initialize pad for input
	SIU.PSMI[16].R=1;//E0UC[6]选择B14
	INTC_InstallINTCInterruptHandler(FieldInputCapture,144,4);
	
	//B14行中断捕捉上升沿
	EMIOS_0.CH[5].CCR.B.MODE = 0x02; // Mode is SAIC, continuous 
	EMIOS_0.CH[5].CCR.B.BSL = 0x01; /* Use counter bus B (default) */
	EMIOS_0.CH[5].CCR.B.EDPOL=1; //Edge Select rising edge
	//EMIOS_0.CH[7].CCR.B.FEN=1;  //interupt enbale
	SIU.PCR[29].R = 0x0102;  // Initialize pad for eMIOS channel Initialize pad for input 
	SIU.PSMI[15].R=1;//E0UC[5]选择B13
	INTC_InstallINTCInterruptHandler(RowInputCapture,143,3); 
	
	//A3像素中断捕捉上升沿
//	EMIOS_0.CH[3].CCR.B.MODE = 0x02; // Mode is SAIC, continuous 
//	EMIOS_0.CH[3].CCR.B.BSL = 0x01; /* Use counter bus B (default) */
//	EMIOS_0.CH[3].CCR.B.EDPOL=1; //Edge Select rising edge
//	//EMIOS_0.CH[7].CCR.B.FEN=1;  //interupt enbale
//	SIU.PCR[3].R = 0x0102;  // Initialize pad for eMIOS channel Initialize pad for input 
//	INTC_InstallINTCInterruptHandler(PixelInputCapture,142,2);
	 
}

/*************************蓝牙初始化***********************/
void initLINFlex_0_UART(void) 
{
	LINFLEX_0.LINCR1.B.INIT=1;  //进入初始化模式
	LINFLEX_0.LINCR1.R=0x00000015; 
	LINFLEX_0.LINIER.B.DTIE=0; //允许发送中断
	/*波特率算法baud=Fperiph_clk/(16*LFDIV)
	DIV_M=LFDIV整数部分
	DIV_F=LFDIV小数部分*16  */
      //38400:64M-104+3
	LINFLEX_0.LINIBRR.B.DIV_M =86;  	//波特率设置38400:80M-130+3 57600:80M-86+13 115200:80M-43+6 
	LINFLEX_0.LINFBRR.B.DIV_F =13;	//38400:64M-104+3
    LINFLEX_0.UARTCR.B.UART=1;
	LINFLEX_0.UARTCR.R=0x00000033;//8-bit data UART mode
	LINFLEX_0.LINCR1.B.INIT=0; //退出初始化模式
	
	SIU.PCR[18].R = 0x0400;    /* MPC56xxB: Configure port B2 as LIN0TX */
    SIU.PCR[19].R = 0x0103;    /* MPC56xxB: Configure port B3 as LIN0RX */
  //	INTC_InstallINTCInterruptHandler(LINFlex_TX_Interrupt,80,6); 
}

/*********************摄像头IO初始化***********************/
void initTestIO(void)
{
//	SIU.PCR[50].R = 0x0102;//D2_Y0
//	SIU.PCR[49].R = 0x0102;//D1_Y1
//	SIU.PCR[52].R = 0x0102;//D4_Y2
//	SIU.PCR[51].R = 0x0102;//D3_Y3
//	SIU.PCR[54].R = 0x0102;//D6_Y4
//    SIU.PCR[53].R = 0x0102;//D5_Y5
//	SIU.PCR[56].R = 0x0102;//D8_Y6
//	SIU.PCR[55].R = 0x0102;//D7_Y7
	
	//摄像头1
		SIU.PCR[49].R = 0x0102;//   D1_Y3
		SIU.PCR[50].R = 0x0102;//   D2_Y2
		SIU.PCR[51].R = 0x0102;//   D3_Y5
		SIU.PCR[52].R = 0x0102;//   D4_Y4
		SIU.PCR[53].R = 0x0102;//   D5_Y7
		SIU.PCR[54].R = 0x0102;//   D6_Y6
		SIU.PCR[55].R = 0x0102;//   D7_Y1
		SIU.PCR[56].R = 0x0102;//   D8_Y0
	
	SIU.PCR[12].R = 0x0200;//A12 LED0
	SIU.PCR[13].R = 0x0200;//A13 LED1
	SIU.PCR[14].R = 0x0200;//A14 LED2
	SIU.PCR[15].R = 0x0200;//A15 LED3
	LED0=1;
	LED1=1;
	LED2=1;
	LED3=1;

}
