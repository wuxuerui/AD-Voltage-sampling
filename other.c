#include <stdio.h>
#include "other.h"


void delay_ms(uint timer)	  //������ʱ����
{
	uchar i;
	while(timer--)
	{
		for(i=200;i>0;i--);
		for(i=120;i>0;i--);
	}	
}


void delay_us(uchar timer)	  //΢����ʱ����
{
	while(timer--);
}


/*
 * ���ƣ�binary_to_decimal()
 * ���ܣ�����������ת��Ϊʮ��������
 */
/*
uchar binary_to_decimal(uchar binary)
{
	uchar decimal,i,j,binary_tmp;
	uchar sumtmp = 1;
	for(i=4;i>0;i--)
	{
		binary_tmp = binary&0x08;
		if(binary_tmp)
		{
			if(i>1)
			{
				for(j=i;j>1;j--)
				{
					sumtmp = sumtmp*2;
				}
				decimal += sumtmp;
				sumtmp = 1;
			}
			else if(i == 1)
			{
				decimal += 1;
			}
			else
			{
				;
			} 
		}
		binary = binary<<1;
	}
	return decimal;
}
*/