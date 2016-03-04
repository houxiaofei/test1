/*
 * video.c
 *
 *  Created on: Dec 17, 2015
 *      Author: lenovo
 */

#include "includes.h"

//*************************************************************************
//*		 *************************��������*****************************   *
//*************************************************************************
//����ͼ����
word crow = 0;           //�м�����        
word trow = 1;            //ѡ�������
word prow = 0;  	  	 //����ͷ������ǰ��
word pcolumn = 0;        //����ͷ������ǰ��
//����������־
byte fieldover = 0;		//һ������������־�� 
//������ά����    
byte a_pix[ROWS][COLUMNS];   // �ɼ��Ҷ�����

//*************************************************************************
//*   **************************�жϺ���****************************      *
//*************************************************************************
//void FieldInputCapture(void)	//��׽���ж� 
//{
//    EMIOS_0.CH[5].CCR.B.FEN=0;  //�رճ��ж� 
//	prow=0;pcolumn=0;
//	EMIOS_0.CH[6].CSR.B.FLAG = 1;
//	EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж�
//}
//
//void RowInputCapture(void) 		//��׽���ж�
//{
//	EMIOS_0.CH[6].CSR.B.FLAG = 1;  //������ж�
//	if(prow>ROWS-1)
//	{
//		EMIOS_0.CH[6].CCR.B.FEN=0; 	//�ر����ж�
//		fieldover=1; //��������
//	}
//	else
//	{
//		for(pcolumn=0;pcolumn<COLUMNS;pcolumn++)
//		{
//			//a_pix[prow][pcolumn]=Y0+Y1<<1+Y2<<2+Y3<<3+Y4<<4+Y5<<5+Y6<<6+Y7<<7;
//			a_pix[prow][pcolumn]=Y0+Y1*2+Y2*4+Y3*8+Y4*16+Y5*32+Y6*64+Y7*128;
//		}
//		prow++;
//	}
//}

//*************************************************************************
//*   **************************�жϺ���2****************************      *
//*************************************************************************
void FieldInputCapture(void)	//��׽���ж� 
{
	EMIOS_0.CH[5].CSR.B.FLAG = 1;//������жϱ�־λ
    EMIOS_0.CH[5].CCR.B.FEN=0;  //�رճ��ж� 
	prow=0;pcolumn=0;crow=0;trow=1;
	EMIOS_0.CH[6].CSR.B.FLAG = 1;  //������ж�
	EMIOS_0.CH[6].CCR.B.FEN=1;  //�����ж�
}

void RowInputCapture(void) 		//��׽���ж�
{
	crow++;
	EMIOS_0.CH[6].CSR.B.FLAG = 1;  //������ж�
	if(prow>ROWS-1)
	{
		EMIOS_0.CH[6].CCR.B.FEN=0; 	//�ر����ж�
		fieldover=1; //��������
	}
	else if(crow>trow)
	{
		for(pcolumn=0;pcolumn<COLUMNS;pcolumn++)
		{
			//a_pix[prow][pcolumn]=Y0+Y1<<1+Y2<<2+Y3<<3+Y4<<4+Y5<<5+Y6<<6+Y7<<7;
			a_pix[prow][pcolumn]=Y0+Y1*2+Y2*4+Y3*8+Y4*16+Y5*32+Y6*64+Y7*128;
		}
		prow++;
		trow+=3;
	}
	else
	{}
}
//*   **************************ͼ����****************************      *
void VideoCopy(byte a[ROWS][COLUMNS],byte b[ROWS][COLUMNS])
{
	int i,j;
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLUMNS;j++)
		{
			a[i][j]=b[i][j];
		}
	}
}