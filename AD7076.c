#include "AD7076.h"

/*
 * ���ƣ�AD7606_startconvst()
 * ���ܣ�����ת��
 */
void AD7606_startconvst(void)
{
	convst = 0;
	delay_us(1);
	convst = 1;
}

/*
 * ���ƣ�AD7606_reset()
 * ���ܣ���λģ��
 */

void AD7606_reset(void)
{
	rst = 0;
	rst = 1;
//	delay_us(1);
	rst = 0;
}

/*
 * ���ƣ�AD7606_setinputvoltage()
 * ���ܣ����ò��Ե�ѹ��Χ
 * rage=1Ϊ-10V~+10V
 * rage=0λ-5V~+5V
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
 * ���ƣ�AD7606_setOS()
 * ���ܣ����ù�����Ƶ��
 */
void AD7606_setOS(uchar uCoS)
{
	switch(uCoS)
	{
		case sampling_0times:	 //�޹�����
			OS0 = 0;
			OS1 = 0;
			OS2 = 0;
			break;
		case sampling_2times:	 //2��������
			OS0 = 1;
			OS1 = 0;
			OS2 = 0;
			break;
		case sampling_4times:	 //4��������
			OS0 = 0;
			OS1 = 1;
			OS2 = 0;
			break;
		case sampling_8times:	 //8��������
			OS0 = 1;
			OS1 = 1;
			OS2 = 0;
			break;
		case sampling_16times:	 //16��������
			OS0 = 0;
			OS1 = 0;
			OS2 = 1;
			break;
		case sampling_32times:	 //32��������
			OS0 = 1;
			OS1 = 0;
			OS2 = 1;
			break;
		case sampling_64times:	 //64��������
			OS0 = 0;
			OS1 = 1;
			OS2 = 1;
			break;
		default:
			break;
	}
}

/*
 * ���ƣ�AD7606_read_data()
 * ���ܣ���ȡ����
 * ����ֵ������һ���ṹ��ָ�룬��ָ��Ϊָ��ṹ��������׵�ַ
 */
struct DB_data_struct *AD7606_read_data(void)
{
	uchar i;
//	uchar DB_data_H,DB_data_L;
	struct DB_data_struct DB_data[8];  //����һ���ṹ�����飬���ڴ洢8��ͨ����16λ����
	for(i=0;i<8;i++)
	{
		rd_and_cs = 0;				  //�ڲ���ģʽ�£�RD��CSͬʱ�õͣ���ʹ�����ݸ����ڲ���������
		DB_data[i].DB_data_L = P0;
		DB_data[i].DB_data_H = P2;
		rd_and_cs = 1;
//		DB_data[i] = (DB_data_H<<8)|DB_data_L;
	}
	return DB_data; 
}

/*
 * ���ƣ�AD7606_init()
 * ���ܣ���ʼ��AD7606ģ��
 *       ��ʼ��Ϊ�޹�������������Ƶ��Ϊ200ksps,������ѹ��ΧΪ-5V~+5V
 */

void AD7606_init(void)
{
	AD7606_setOS(sampling_0times);
	AD7606_setinputvoltage(0);
	AD7606_reset();
	AD7606_startconvst();
}
