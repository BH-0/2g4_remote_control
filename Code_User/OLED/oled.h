#ifndef __OLED__H
#define __OLED__H			  	 


#include "stm32f10x.h"
#include "delay.h"
#include <math.h>
#include "stdarg.h"		  //  标准头文件
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


/*--------------------引脚定义--------------------------*/
#define SPI_SCK_HIGH		GPIO_SetBits(GPIOA,GPIO_Pin_5)		//PA5（DO）输出高
#define	SPI_SCK_LOW			GPIO_ResetBits(GPIOA,GPIO_Pin_5)	//PA5（DO）输出低

#define SPI_MOSI_HIGH		GPIO_SetBits(GPIOA,GPIO_Pin_7)		//PA7（D1）输出高
#define	SPI_MOSI_LOW		GPIO_ResetBits(GPIOA,GPIO_Pin_7)	//PA7（D1）输出低

#define OLED_RES_HIGH		GPIO_SetBits(GPIOB,GPIO_Pin_0)		//PB0（RES）输出高
#define OLED_RES_LOW		GPIO_ResetBits(GPIOB,GPIO_Pin_0)	//PB0（RES）输出低

#define OLED_DC_HIGH		GPIO_SetBits(GPIOB,GPIO_Pin_1)		//PB1（DC）输出高
#define OLED_DC_LOW			GPIO_ResetBits(GPIOB,GPIO_Pin_1)	//PB1（DC）输出低

#define SPI_CS_HIGH			GPIO_SetBits(GPIOA,GPIO_Pin_4)		//PA4（CS）输出高
#define SPI_CS_LOW			GPIO_ResetBits(GPIOA,GPIO_Pin_4)	//PA4（CS）输出低

/*definition--------------------------------------------*/
#define OLED_CMD  	0		//写命令
#define OLED_DATA 	1		//写数据

#define SIZE 		8		//显示字符的大小 16
#define Max_Column	128		//最大列数
#define Max_Row		64		//最大行数
#define X_WIDTH 	128		//X轴的宽度
#define Y_WIDTH 	64	    //Y轴的宽度					  				   




/*--------------------------------------函数声明----------------------------------------*/
void OLED_WR_Byte(unsigned char dat,unsigned char cmd);	  //OLED写字节函数
void OLED_Display_On(void);	//开显示函数
void OLED_Display_Off(void);//关显示函数
void OLED_Init(void);	//OLED初始化函数
void OLED_Clear(void);  //清屏函数
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr); //显示字符函数
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size2); //在指定的位置，显示一个指定数的长度大小函数
void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p);	 //在指定位置开始显示字符串函数
void OLED_Set_Pos(unsigned char x, unsigned char y);		//画点函数
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no); //声明在指定位置显示汉字函数
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]); //显示图片函数
void OLED_Scroll(void);	//滚动函数

//画点函数
void OLED_DrawPoint(int16_t x,int16_t y);
//画点 ,熄灭该点，x:0~127 , y:0~63
void OLED_ClosePoint(int16_t x,int16_t y);
	
//将显示内存刷新至oled，入口参数为刷新坐标
void OLED_Renew(u8 x); 

// 画圆(x,y为圆?坐标，r为圆的半径，圆?的真实物理位置是x,y这个像素的左上?)
void DrawCircle(int x1, int y1, int r);

void OLED_Printf(u8 x , u8 y , char *p,... );	//OLED 格式化输出

//画涟漪
void DrawEcho(void);

//显示小车所有信息
void OLED_main(unsigned char *Data);

#endif  
	 



