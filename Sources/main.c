#include "includes.h"


int main(void) {
	
	initALL();
	//BlueTx();
	EMIOS_0.CH[5].CCR.B.FEN=1;  //�����ж� 
	 	for(;;) 
	  	{		
			if(fieldover)//��������������־
	  	  	{
	      		fieldover=0;         //��־����
	      		VideoCopy(A,a_pix);
	      		BlueTx();
	      		EMIOS_0.CH[5].CSR.B.FLAG = 1;//������жϱ�־λ
	      		EMIOS_0.CH[5].CCR.B.FEN=1;  //�����ж�
	    	}
	  	}
}



