#include "usmart.h"
#include "usmart_str.h" 

////////////////////////////�û�������///////////////////////////////////////////////
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����) 
#include "delay.h"		
#include "oled.h"
												 
extern void led_set(u8 sta);
extern void test_fun(void(*ledset)(u8),u8 sta);
 
//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif
	(void*)delay_ms,"void delay_ms(u16 nms)",
	(void*)delay_us,"void delay_us(u32 nus)",
    (void*)OLED_Clear,"void OLED_Clear(void)",// ����
    (void*)OLED_ShowChar,"void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)",                                    //��ʾ�ַ�����
    (void*)OLED_ShowNum,"void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2)", //��ָ����λ�ã���ʾһ��ָ�����ĳ��ȴ�С����
    (void*)OLED_ShowString,"void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p)",	                             //��ָ��λ�ÿ�ʼ��ʾ�ַ�������
    (void*)OLED_Set_Pos,"void OLED_Set_Pos(unsigned char x, unsigned char y)",		                                                 //���㺯��

	(void*)OLED_DrawPoint,"void OLED_DrawPoint(int16_t x,int16_t y)",	//���㺯��
	(void*)OLED_Renew,"void OLED_Renew(u8 x)",	//ˢ����ʾ
	(void*)DrawCircle,"void DrawCircle(int x1, int y1, int r)", //��Բ
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
	0,	  	//��������
	0,	 	//����ID
	1,		//������ʾ����,0,10����;1,16����
	0,		//��������.bitx:,0,����;1,�ַ���	    
	0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
	0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};   



















