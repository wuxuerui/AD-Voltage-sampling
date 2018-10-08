/*
 * This is a program for testing AD7606	used STC89C52RC
 * The line connecting AD7606 with STC89C52RC is:
 * STC89C52RC    |    AD7606
 * 	 P0			 |	  DB[0:7]
 *   P2          |    DB[8:15]
 *   OS0         |    P1^0
 *   OS1         |    P1^1
 *   OS2         |    P1^2
 *   rage        |    P1^3
 *   convst      |    P1^4
 *   busy        |    P1^5
 *   rst         |    P1^6
 *   rd_and_cs   |    P1^7
 *   green_led   |    P3^6
 *   red_led     |    P3^7
 *	 GND		 |    GND
 *   +5V		 |    VCC
 *   green_led   |    P3_6
 *   red_led     |    P3_7
 * Author : jinming chen
 * Compang : Hongwei in dongguan
 * Date : Sep 1	,2015
 */

#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include "AD7076.h"
#include "other.h"

//uchar introduce1[] = "This is a program "; 
//uchar introduce2[] = "for testing AD7606\r\n";

uchar newline[] = "\r\n";
uchar space	 [] = " ";

	int time=0;
	int count=0;
	int adcdata;
/*
uchar *data_to_string(uchar Data)
{
	uchar tmp;
	tmp = Data & 0x0f;
	str[1] =DB_str[binary_to_decimal(tmp)];
	tmp = Data>>4;
	str[0] =DB_str[binary_to_decimal(tmp)];
	return str;
}
*/


void serial_init(void)
{
	SCON = 0x50;  //UART为模式一，8位数据，允许接收
	TMOD |= 0x20;	//定时器1为模式二，8位自动重装
	PCON |= 0x80;	//SMOD=1
	TH1 =0xfd;		//波特率为19200，晶振频率为11.0592MHz
	IE = 0x00;
	TR1 = 1;
	TI = 1; 
}

//向串口发送一个函数
void serial_send_byte(uchar ch) 
{ 
	SBUF=ch; 
    while (TI== 0); 
    TI = 0 ; 
}


//向串口发送一串字符数据
void serial_send_string(uchar *p)
{
	while(*p != '\0')
	{
		SBUF = *p;
		while(TI == 0);
		TI = 0;
		p++;
	} 	
}
 void Timer1Init(void)		//10??@11.0592MHz
{
	TMOD |= 0x10;	
	TL0 = 0xA4;		//??????
	TH0 = 0xFF;
	TF0 = 0;		
	TR0 = 1;		
	 EA = 1;              
    ET0 = 1;         
}
int main()
{
	struct DB_data_struct *DB_data;
	uchar k,tmp;
	uchar adctx[6]={'\0'};
	uchar adctx2[3]={'\0'};
	serial_init();
	AD7606_init();
	while(1)
	{
		AD7606_startconvst();
		while((busy == 1))		//当busy为低电平时，数据转换完毕，此时可以读取数据
		{
			;
		}
		DB_data = AD7606_read_data();
		adcdata=((int)(DB_data->DB_data_H)<<8)|((int)(DB_data->DB_data_L));
		if(adcdata<0)
		{
			adcdata=-(int)(adcdata*0.00152588);

			
			serial_send_byte('-');
			adctx2[0]=adcdata/10+'0';
			adctx2[1]=adcdata%10+'0';
			serial_send_string(adctx2);
			serial_send_byte('\n');
		}
		else
			{		
			adcdata=(int)(adcdata*0.00152588);
			
			
		
		adctx2[0]=adcdata/10+'0';
		adctx2[1]=adcdata%10+'0';
		serial_send_string(adctx2);
		serial_send_byte('\n');
		}

			DB_data += 8;
		 
		
		
	//delay_ms(1);
	}
	return 0;	
}

void Timer0_ISR(void)   interrupt  1      //10us
{
   TL0 = 0xA4;		//??????
	TH0 = 0xFF;
   count++;

       
}
