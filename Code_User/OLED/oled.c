/********************************************************
  * @file        	oled.c
  * @author      	LGG
  * @version     	V1.0.0
  * @data        	2017年06月6号
  * @brief       	OELD文件
  *
********************************************************/


/*includes----------------------------------------------*/
#include "oled.h"
#include "oledfont.h" 
/*definition--------------------------------------------*/

unsigned char oled_RAM[128][8] = {0};


// //限制数到给定的最大值
// void OLED_LimMax(int *Dat, int Lim)
// {
// 	if ((*Dat) >= Lim)
// 		(*Dat) = Lim;
// }
// //限制数到给定的最小值
// void OLED_LimMin(int *Dat, int Lim)
// {
// 	if ((*Dat) <= Lim)
// 		(*Dat) = Lim;
// }
// //画圆和圆弧用 限制最大最小值
// void OLED_CandA_LimMaxMin(int *X_Left, int *X_Right, int *Y_Up, int *Y_Down)
// {
// 	OLED_LimMin(X_Left, 0);
// 	OLED_LimMin(Y_Up, 0);
// 	OLED_LimMax(X_Right, 127);
// 	OLED_LimMax(Y_Down, 63);
// }
//将显示内存刷新至oled，入口参数为刷新坐标
void OLED_Renew(u8 x)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_WR_Byte (0xb0+i,OLED_CMD);
		OLED_WR_Byte (0x00,OLED_CMD);
		OLED_WR_Byte (0x10,OLED_CMD);
		for(n=0;n<=x;n++){
			OLED_WR_Byte(oled_RAM[n][i],OLED_DATA);
		}
	}
}
#if 0
//画点函数
void OLED_DrawPoint(int16_t x,int16_t y)
{
	double abs_y=y/8;
	double tem_y;
	u8 dat;
	
	if(x>127 || y>63 || x<0 || y<0)	//限制点的范围	
		return;
		
	tem_y=y%8;
	abs_y=ceil(abs_y);
	switch((u8)tem_y){
	case 0:dat=0x01;break;
	case 1:dat=0x02;break;
	case 2:dat=0x04;break;
	case 3:dat=0x08;break;
	case 4:dat=0x10;break;
	case 5:dat=0x20;break;
	case 6:dat=0x40;break;
	case 7:dat=0x80;break;
	}
	oled_RAM[x][(u8)abs_y]+=dat;

}
#else
void OLED_DrawPoint(int16_t x,int16_t y)	//画点 ,点亮该点，x:0~127 , y:0~63.
{
	if(x>127 || y>63 || x<0 || y<0)	//限制点的范围	
		return;
	oled_RAM[x][y/8] |=  1<<y%8;			//点亮
}

void OLED_ClosePoint(int16_t x,int16_t y)	//画点 ,熄灭该点，x:0~127 , y:0~63
{
	if(x>127 || y>63 || x<0 || y<0)	//限制点的范围	
		return;
	oled_RAM[x][y/8] &= ~(1<<y%8);		//熄灭
}
#endif


//画圆
void DrawCircle(int x1, int y1, int r) 
{
	u8 x0 = 0;
	u8 y0 = 0;                    //定义全局变量x0,y0:坐标轴中心（x0,y0
	int d0, x = 0, y = r;//d0是判别式的值
	d0 = 1.25 - r;   //判别式的初始值，1.25可以改为1
	while (x < y) 
	{
		if (d0 >= 0) 
		{
			d0 = d0 + 2 * (x - y) + 5;            //d0一定要先比x,y更新
			x += 1;                //因为d0表达式中的x,y是上一个点
			y -= 1;
			OLED_DrawPoint(((x + x1) + x0), (y0 + (y + y1)));         //(x,y)
			OLED_DrawPoint(((-x + x1) + x0), (y0 + (y + y1)));        //(-x,y)
			OLED_DrawPoint(((y + x1) + x0), (y0 + (x + y1)));         //(y,x)
			OLED_DrawPoint(((-y + x1) + x0), (y0 + (x + y1)));        //(-y,x)
			OLED_DrawPoint(((x + x1) + x0), (y0 + (-y + y1)));        //(x,-y)
			OLED_DrawPoint(((-x + x1) + x0), (y0 + (-y + y1)));       //(-x,-y)
			OLED_DrawPoint(((y + x1) + x0), (y0 + (-x + y1)));        //(y,-y)
			OLED_DrawPoint(((-y + x1) + x0), (y0 + (-x + y1)));       //(-y,-x)

		}
		else 
		{
			d0 = d0 + 2 * x + 3;
			x += 1;
			y = y;
			OLED_DrawPoint(((x + x1) + x0), (y0 + (y + y1)));         //(x,y)
			OLED_DrawPoint(((-x + x1) + x0), (y0 + (y + y1)));        //(-x,y)
			OLED_DrawPoint(((y + x1) + x0), (y0 + (x + y1)));         //(y,x)
			OLED_DrawPoint(((-y + x1) + x0), (y0 + (x + y1)));        //(-y,x)
			OLED_DrawPoint(((x + x1) + x0), (y0 + (-y + y1)));        //(x,-y)
			OLED_DrawPoint(((-x + x1) + x0), (y0 + (-y + y1)));       //(-x,-y)
			OLED_DrawPoint(((y + x1) + x0), (y0 + (-x + y1)));        //(y,-y)
			OLED_DrawPoint(((-y + x1) + x0), (y0 + (-x + y1)));       //(-y,-x)

		}
	}
    	
}

//画涟漪
void DrawEcho(void)
{
    uint8_t width = 127;
    uint8_t height = 63;
    uint16_t i = 0;
 int Radius = (width>height?width:height)/2+12;
 for(i=0; i < Radius; i+=2) 
 {
    OLED_Clear();
    
    DrawCircle(width / 2, height / 2, i );

    DrawCircle(width / 2, height / 2, (i + Radius/3) % Radius );

    DrawCircle(width / 2, height / 2, (i + Radius*2/3) % Radius );
    
    OLED_Renew(127);   // Update screen with each newly-drawn circle
	delay_ms(10);
  }  
}



///*
//	@brief			ms延迟函数
//	@param			无
//	@retval			无
//*/
//static void delay_ms(unsigned int ms)//延迟函数，MS级别
//{
//	unsigned int x,y;
//	for(x = ms;x>0;x--)
// {
//		for(y = 12000;y>0;y--);
// }
//}


/*
	@brief			初始化OLED与单片机的IO接口
	@param			无
	@retval			无
 */
static void OLED_GPIO_SPI_Init(void)
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//使能AB端口和SPI1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_SPI1, ENABLE);	 
	
	// 配置PB0和PB1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOB
 	GPIO_SetBits(GPIOB,GPIO_Pin_0|GPIO_Pin_1);	

  
  /* 配置SCK引脚 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* 配置MISO引脚 OLED这里不需要MISO 所以隐藏掉了 */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* 配置MOSI引脚 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* 配置CS引脚 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* CS引脚拉高 */
  GPIO_SetBits(GPIOA, GPIO_Pin_4);

  /* 配置SPI1 */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);

  /* 允许SPI1  */
  SPI_Cmd(SPI1, ENABLE);
	
}


/*
	@brief			SPI发送一个字节
	@param			Txdata：发送的数据
	@retval			无
 */
uint8_t SPI1_Communication(uint8_t TxData)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

  /* Send byte through the SPI1 peripheral */
  SPI_I2S_SendData(SPI1, TxData);

  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI1);
}


/*
	@brief			对OLED写入一个字节
	@param			dat：数据
					cmd：1，写诶数据；0，写入命令
	@retval			无
 */
void OLED_WR_Byte(unsigned char dat,unsigned char cmd)
{
	if(cmd)  //如果cmd为高，则发送的是数据
	  	OLED_DC_HIGH;	//将DC拉高
	else    //如果cmd为低，则发送的是命令
		OLED_DC_LOW;	//将DC拉低
		
	SPI_CS_LOW; //片选拉低，选通器件
		
	SPI1_Communication(dat); //发送数据
		
	SPI_CS_HIGH; //片选拉高，关闭器件
	OLED_DC_HIGH; //DC拉高，空闲时为高电平
}


/*
	@brief			设置数据写入的起始行、列
	@param			x： 列的起始低地址与起始高地址；0x00~0x0f：设置起始列低地址（在页寻址模式）；
						0x10~0x1f：设置起始列高地址（在页寻址模式）
					y：起始页地址 0~7
	@retval			无
 */
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);//写入页地址
	OLED_WR_Byte((x&0x0f),OLED_CMD);  //写入列的地址  低半字节
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);//写入列的地址 高半字节
}   	     	  


/*
	@brief			开显示
	@param			无
	@retval			无
 */ 
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //设置OLED电荷泵
	OLED_WR_Byte(0X14,OLED_CMD);  //使能，开
	OLED_WR_Byte(0XAF,OLED_CMD);  //开显示
}


/*
	@brief			关显示
	@param			无
	@retval			无
 */  
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0XAE,OLED_CMD);  //关显示
	OLED_WR_Byte(0X8D,OLED_CMD);  //设置OLED电荷泵
	OLED_WR_Byte(0X10,OLED_CMD);  //失能，关
}		   			 


/*
	@brief			清屏
	@param			无
	@retval			无
 */	  
void OLED_Clear(void)  
{  
	unsigned char i,n;		    //定义变量
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //从0~7页依次写入
		OLED_WR_Byte (0x00,OLED_CMD);      //列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //列高地址  
		for(n=0;n<128;n++)
		{
			OLED_WR_Byte(0,OLED_DATA); //写入 0 清屏
			oled_RAM[n][i]=0;
		}
	}
}


/*
	@brief			显示一个字符
	@param			x：起始列
					y：起始页，SIZE = 16占两页；SIZE = 12占1页
					chr：字符
	@retval			无
 */
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' '; //获取字符的偏移量	
		if(x>Max_Column-1){x=0;y=y+2;} //如果列数超出了范围，就从下2页的第0列开始

		if(SIZE ==16) //字符大小如果为 16 = 8*16
			{
				OLED_Set_Pos(x,y);	//从x y 开始画点
				for(i=0;i<8;i++)  //循环8次 占8列
				OLED_WR_Byte(F8X16[c*16+i],OLED_DATA); //找出字符 c 的数组位置，先在第一页把列画完
				OLED_Set_Pos(x,y+1); //页数加1
				for(i=0;i<8;i++)  //循环8次
				OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA); //把第二页的列数画完
			}
		else 	//字符大小为 6 = 6*8
			{	
				OLED_Set_Pos(x,y+1); //一页就可以画完
				for(i=0;i<6;i++) //循环6次 ，占6列
				OLED_WR_Byte(F6x8[c][i],OLED_DATA); //把字符画完
			}
}


/*
	@brief			计算m^n
	@param			m：输入的一个数
					n：输入数的次方
	@retval			result：一个数的n次方
 */
unsigned int oled_pow(unsigned char m,unsigned char n)
{
	unsigned int result=1;	 
	while(n--)result*=m;    
	return result;
}				  


/*
	@brief			在指定的位置，显示一个指定长度大小的数
	@param			x：起始列
					y：起始页
					num：数字
					len：数字的长度
					size：显示数字的大小
	@retval			无
 */		  
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size)
{         	
	unsigned char t,temp;  //定义变量
	unsigned char enshow=0;		//定义变量

	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;//取出输入数的每个位，由高到低
		if(enshow==0&&t<(len-1)) //enshow：是否为第一个数；t<(len-1)：判断是否为最后一个数
		{
			if(temp==0) //如果该数为0 
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');//显示 0 ；x+(size2/2)*t根据字体大小偏移的列数（8）
				continue; //跳过剩下语句，继续重复循环（避免重复显示）
			}else enshow=1; 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); //显示一个位；x+(size2/2)*t根据字体大小偏移的列数（8）
	}
} 


/*
	@brief			显示字符串
	@param			x：起始列
					y：起始页
					*chr：第一个字符首地址
	@retval			无
 */
void OLED_ShowString(unsigned char x,unsigned char y,unsigned char *chr)
{
	unsigned char j=0; //定义变量

	while (chr[j]!='\0') //如果不是最后一个字符
	{		
		OLED_ShowChar(x,y,chr[j]); //显示字符
		if(SIZE == 16)
			x+=8; //列数加8 ，一个字符的列数占8
		else
			x+=6;
		if(x>=128){x=0;y+=2;} //如果x大于等于128，切换页，从该页的第一列显示
		j++; //下一个字符
	}
}


/*
	@brief			显示中文
	@param			x：起始列；一个字体占16列
					y：起始页；一个字体占两页
					no：字体的序号
	@retval			无
 */
void OLED_ShowCHinese(unsigned char x,unsigned char y,unsigned char no)
{      			    
	unsigned char t,adder=0; //定义变量

	OLED_Set_Pos(x,y);	//从 x y 开始画点，先画第一页
    for(t=0;t<16;t++) //循环16次，画第一页的16列
		{
			OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);//画no在数组位置的第一页16列的点
			adder+=1; //数组地址加1
     	}	
		OLED_Set_Pos(x,y+1); //画第二页
    for(t=0;t<16;t++)//循环16次，画第二页的16列
		{	
			OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);//画no在数组位置的第二页16列的点
			adder+=1;//数组地址加1
        }					
}


/*
	@brief			显示图片
	@param			x0：起始列地址
					y0：起始页地址
					x1：终止列地址
					y1：终止页地址
					BMP[]：存放图片代码的数组
	@retval			无
 */
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 	unsigned int j=0; //定义变量
 	unsigned char x,y; //定义变量
  
 	if(y1%8==0) y=y1/8;   //判断终止页是否为8的整数倍
 	 else y=y1/8+1;

		for(y=y0;y<y1;y++) //从起始页开始，画到终止页
		{
			OLED_Set_Pos(x0,y); //在页的起始列开始画
   			for(x=x0;x<x1;x++) //画x1 - x0 列
	    		{
	    			OLED_WR_Byte(BMP[j++],OLED_DATA);	//画图片的点    	
	    		}
		}
} 


/*
	@brief			OLED初始化函数
	@param			无
	@retval			无
 */				    
void OLED_Init(void)
{
	OLED_GPIO_SPI_Init();	//GPIO口初始化
 
	OLED_RES_HIGH;
	delay_ms(100);
	OLED_RES_LOW;
	delay_ms(200);	//延迟，由于单片机上电初始化比OLED快，所以必须加上延迟，等待OLED上电初始化完成
	OLED_RES_HIGH;
	delay_ms(200);

	OLED_WR_Byte(0xAE,OLED_CMD);	//关闭显示
	OLED_WR_Byte(0x2e,OLED_CMD);	//关闭滚动

	OLED_WR_Byte(0x00,OLED_CMD);	//设置低列地址
	OLED_WR_Byte(0x10,OLED_CMD);	//设置高列地址
	OLED_WR_Byte(0x40,OLED_CMD);	//设置起始行地址
	OLED_WR_Byte(0xB0,OLED_CMD);	//设置页地址

	OLED_WR_Byte(0x81,OLED_CMD);	// 对比度设置，可设置亮度
	OLED_WR_Byte(0xFF,OLED_CMD);	//  265  

	OLED_WR_Byte(0xA1,OLED_CMD);	//设置段（SEG）的起始映射地址；column的127地址是SEG0的地址
	OLED_WR_Byte(0xA6,OLED_CMD);	//正常显示；0xa7逆显示

	OLED_WR_Byte(0xA8,OLED_CMD);	//设置驱动路数
	OLED_WR_Byte(0x3F,OLED_CMD);	//1/64duty
	
	OLED_WR_Byte(0xC8,OLED_CMD);	//重映射模式，COM[N-1]~COM0扫描

	OLED_WR_Byte(0xD3,OLED_CMD);	//设置显示偏移
	OLED_WR_Byte(0x00,OLED_CMD);	//无偏移
	
	OLED_WR_Byte(0xD5,OLED_CMD);	//设置震荡器分频（默认）
	OLED_WR_Byte(0x80,OLED_CMD);	
	
	OLED_WR_Byte(0xD8,OLED_CMD);	//设置 area color mode off（没有）
	OLED_WR_Byte(0x05,OLED_CMD);
	
	OLED_WR_Byte(0xD6,OLED_CMD);	//放大显示
	OLED_WR_Byte(0x00,OLED_CMD);
	
	OLED_WR_Byte(0xD9,OLED_CMD);	//设置 Pre-Charge Period（默认）
	OLED_WR_Byte(0xF1,OLED_CMD);
	
	OLED_WR_Byte(0xDA,OLED_CMD);	//设置 com pin configuartion（默认）
	OLED_WR_Byte(0x12,OLED_CMD);
	
	OLED_WR_Byte(0xDB,OLED_CMD);	//设置 Vcomh，可调节亮度（默认）
	OLED_WR_Byte(0x30,OLED_CMD);
	
	OLED_WR_Byte(0x8D,OLED_CMD);	//设置OLED电荷泵
	OLED_WR_Byte(0x14,OLED_CMD);	//开显示
	
	OLED_WR_Byte(0xA4,OLED_CMD);	// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);	// Disable Inverse Display On (0xa6/a7) 
	
	OLED_WR_Byte(0xAF,OLED_CMD);	//开启OLED面板显示
	OLED_Clear();	//清屏
	OLED_Set_Pos(0,0); 	 //画点
}  


/*
	@brief			OLED滚屏函数，范围0~1页，水平向左
	@param			无
	@retval			无
 */	
void OLED_Scroll(void)
{
	OLED_WR_Byte(0x2E,OLED_CMD);	//关闭滚动
	OLED_WR_Byte(0x27,OLED_CMD);	//水平向左滚动
	OLED_WR_Byte(0x00,OLED_CMD);	//虚拟字节
	OLED_WR_Byte(0x00,OLED_CMD);	//起始页 0
	OLED_WR_Byte(0x00,OLED_CMD);	//滚动时间间隔
	OLED_WR_Byte(0x01,OLED_CMD);	//终止页 1
	OLED_WR_Byte(0x00,OLED_CMD);	//虚拟字节
	OLED_WR_Byte(0xFF,OLED_CMD);	//虚拟字节
	OLED_WR_Byte(0x2F,OLED_CMD);	//开启滚动
}

void OLED_Printf(u8 x , u8 y , char *p,... )	//OLED 格式化输出
{
	char buf[32];
	va_list ap;
	va_start(ap,p);
	vsprintf(buf,p,ap);
	va_end(ap);
	OLED_ShowString(x,y,(unsigned char *)buf);
}


//显示小车所有信息
void OLED_main(unsigned char *Data)
{   
    float pitch=0,yaw=0;
	float Kp=0,Kd=0;	//平衡环
	int Kp_speed = 0;	//速度环
	float Tp=0,Td=0;	//平衡环

    if(Data[12] == 0)
    {
        pitch = (float)((Data[1]<<8)|Data[2])/32768*180;
        yaw = (float)((Data[3]<<8)|Data[4])/32768*180;
        //yaw = (float)((Data[5]<<8)|Data[6])/32768*180;
        OLED_Printf(0,0,"p%6.2f y%6.2f",pitch,yaw);	//俯仰 偏航
        
        Kp = (float)Data[5]/10;
        Kd = (float)Data[6]/100;
        Kp_speed = Data[7];
        OLED_Printf(0,1,"Kp%3.1f Kd%4.2f Sp%3d",Kp,Kd,Kp_speed);	//倾斜PD 速度P

        Tp = (float)Data[8]/-100;
        Td = (float)Data[9]/-100;
        OLED_Printf(0,2,"Tp%6.2f Td%6.2f ",Tp,Td);	//转向PD


        if((Data[13]&0x7f) == 0)
            OLED_Printf(0,6,"Mode:default  ");	//默认模式
        else if((Data[13]&0x7f) == 1)
            OLED_Printf(0,6,"Mode:obstacle ");	//避障模式
        else if((Data[13]&0x7f) == 2)
            OLED_Printf(0,6,"Mode:follow   ");	//跟随模式

        if((Data[13]&0x80)!=0)
            OLED_Printf(96,6,"[PID]");	//PID设置
        else
            OLED_Printf(96,6,"[RGB]");	//RGB设置

        if(Data[0] == 0x40)
        {
            OLED_Printf(0,5,"err:Angle ");	//角度过大
        }
        else if(Data[0] == 0x80)
        {
            OLED_Printf(0,5,"err:speed ");	//转速过大
        }else
        {                          
            OLED_Printf(0,5,"          ");	//恢复正常
        }
        
        if(Data[0] != 1)
        {
            OLED_ShowString(100,0,"OFF"); 
        }else
        {
            OLED_ShowString(100,0,"ON "); 
        }

    }
    else if(Data[12] != 0)  //进入升级
    {
        switch(Data[12])
        {
            case 1:
            	OLED_Clear(); 				// 清屏
                OLED_Printf(0,2,"Wifi connecting...");	//wifi连接中               
            break;
            case 2:
                OLED_Clear(); 				// 清屏
                OLED_Printf(0,2,"TCP connecting...");	//wifi连接中  
            break;
            case 3:
                OLED_Clear(); 				// 清屏
                OLED_Printf(0,2,"Upgrade...");	//wifi连接中
            break;
        }
    }
}



