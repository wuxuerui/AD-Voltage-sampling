#include "AD7076.h"

/*
 * 名称：AD7606_startconvst()
 * 功能：启动转换
 */
void AD7606_startconvst(void)
{
	convst = 0;
	delay_us(1);
	convst = 1;
}

/*
 * 名称：AD7606_reset()
 * 功能：复位模块
 */

void AD7606_reset(void)
{
	rst = 0;
	rst = 1;
//	delay_us(1);
	rst = 0;
}

/*
 * 名称：AD7606_setinputvoltage()
 * 功能：设置测试电压范围
 * rage=1为-10V~+10V
 * rage=0位-5V~+5V
 */
void AD7606_setinputvoltage(uchar vol)
{
	if(vol ==1)
	{
		rage = 1;
	}else{
		rage = 0;
	}
}

/*
 * 名称：AD7606_setOS()
 * 功能：设置过采样频率
 */
void AD7606_setOS(uchar uCoS)
{
	switch(uCoS)
	{
		case sampling_0times:	 //无过采样
			OS0 = 0;
			OS1 = 0;
			OS2 = 0;
			break;
		case sampling_2times:	 //2倍过采样
			OS0 = 1;
			OS1 = 0;
			OS2 = 0;
			break;
		case sampling_4times:	 //4倍过采样
			OS0 = 0;
			OS1 = 1;
			OS2 = 0;
			break;
		case sampling_8times:	 //8倍过采样
			OS0 = 1;
			OS1 = 1;
			OS2 = 0;
			break;
		case sampling_16times:	 //16倍过采样
			OS0 = 0;
			OS1 = 0;
			OS2 = 1;
			break;
		case sampling_32times:	 //32倍过采样
			OS0 = 1;
			OS1 = 0;
			OS2 = 1;
			break;
		case sampling_64times:	 //64倍过采样
			OS0 = 0;
			OS1 = 1;
			OS2 = 1;
			break;
		default:
			break;
	}
}

/*
 * 名称：AD7606_read_data()
 * 功能：读取数据
 * 返回值：返回一个结构体指针，该指针为指向结构体数组的首地址
 */
struct DB_data_struct *AD7606_read_data(void)
{
	uchar i;
//	uchar DB_data_H,DB_data_L;
	struct DB_data_struct DB_data[8];  //申请一个结构体数组，用于存储8个通道的16位数据
	for(i=0;i<8;i++)
	{
		rd_and_cs = 0;				  //在并行模式下，RD和CS同时置低，将使得数据更新在并行总线上
		DB_data[i].DB_data_L = P0;
		DB_data[i].DB_data_H = P2;
		rd_and_cs = 1;
//		DB_data[i] = (DB_data_H<<8)|DB_data_L;
	}
	return DB_data; 
}

/*
 * 名称：AD7606_init()
 * 功能：初始化AD7606模块
 *       初始化为无过采样，即采样频率为200ksps,采样电压范围为-5V~+5V
 */

void AD7606_init(void)
{
	AD7606_setOS(sampling_0times);
	AD7606_setinputvoltage(0);
	AD7606_reset();
	AD7606_startconvst();
}
