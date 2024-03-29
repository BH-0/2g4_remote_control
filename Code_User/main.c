/*
###################################################
---------------------------------------------------
深圳市技新电子科技有限公司 www.jixin.pro  
---------------------------------------------------

---------------------------------------------------
工程硬件平台：2.4G遥控手柄 V1.0
工程程序版本：2G4 Telecontrol V1.0.0.0
---------------------------------------------------

---------------------------------------------------
硬件连接：请参考《2.4G遥控手柄原理图》
---------------------------------------------------

---------------------------------------------------
程序功能：

检测按键和摇杆，通过2.4G模块将指令数据发出(共14个数据)
---------------------------------------------------
###################################################
*/

#include "stm32f10x.h"
#include "bit_band.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "oled.h"
#include "adc.h"
#include "spi.h"
#include "rf2G4.h"
#include "dma.h"
#include "usart.h"
#include "usmart.h"	


// 全局变量
//------------------------------------------------------------------
u16 C_TIM2_IT_Update = 0 ;	// TIM3的定时计次

u8  One_Ms_Timing = 0 ;		// 1ms全局时基

u8 F_2G4_Send = 0 ;			// RF准备发射标志位

u8 F_2G4_Receive = 0 ;			// RF准备接收志位
//------------------------------------------------------------------



int main(void)
{	
	// 变量定义
	//------------------------------------------------------------
	u8 L_CNT = 0 ;				// 循环计数
	u8 sum = 0 ;	//计时
	u16 ret = 0 ;	//返回值
	//u8 J_2G4_Data_Send = 0;		// 标志位：判断是否需发射数据
	
	volatile u8 F_No_motion = 0 ;		// 标志位：当前无动作
	//------------------------------------------------------------
	
	
	// 注：程序中使用中断时，NVIC分组设置应尽量位于程序起始处，并且在设置后尽量不要再更改NVIC分组
	//------------------------------------------------------------------------------------------
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //NVIC分组2：2位抢占优先级，2位响应优先级
	
	delay_Init();				// 延时初始化（注：调用延时函数之前，必须先调用delay_Init()将SysTick初始化）

    uart_init(115200);          //初始化串口1

    usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART
	
	LED_Init_JX() ;				// 初始化LED硬件接口：Green--PB4、Blue--PB5
	
	TIM3_Time_Init();			// 定时器3初始化
	
	KEY_Init_JX() ;				// 初始化按键硬件接口
	
	DMA_Init_JX();				// DMA初始化（搬运ADC数据）
	
	ADC1_Rocker_Init();			// ADC初始化（摇杆）
	
	RF2G4_Init();				// 2.4G无线射频初始化

	
	// 初始化OLED
	//-----------------------------------------
	OLED_Init();				// 初始化OLED  
	OLED_Clear(); 				// 清屏
	OLED_Printf(0, 0, "2.4G Telecontrol");
	//-----------------------------------------
	
	// 判断SI24R1是否正常
	//-----------------------------------------
	if(RF2G4_Check())
	{ 
		OLED_ShowString(0, 2, "2G4 ERROR");
		while(1){}
	}
	// else
	// { OLED_ShowString(0, 2, "2G4 OK"); }
	//-----------------------------------------
	//for(;;);
	handshake();	//握手
	OLED_ShowString(0, 0, "connected!");
	// RF2G4_Tx_Packet((u8 *)RF2G4_Send_Data,14);		// 发射指令
	// RF2G4_RX_Mode_X();	//切换为接收
	delay_ms(100);
	while(1)
	{  
#if 1
		//------------------------------------------------------------------
		if( One_Ms_Timing == 1 )// 1ms时基
		{
			One_Ms_Timing = 0 ;
			
			// 按键检测
			//-------------------
			RF2G4_KEY_Scan_JX();
			
			// 摇杆检测
			//--------------------------------------
			ADC1_Value_average();	// 获取ADC平均值
			
			
			// 准备射频数据
			//-------------------------------------------------------
			for(L_CNT=0;L_CNT<10;L_CNT++)
			{
				RF2G4_Send_Data[L_CNT] = F_KEY_Down[L_CNT]; //放入按键值，只发送前10个按键，剩下三个留作本地操作
			}
			
			RF2G4_Send_Data[10] = (u8)(AV_ADC_Channel1_Sample / 16);    //放入摇杆值
			RF2G4_Send_Data[11] = (u8)(AV_ADC_Channel2_Sample / 16);    //放入摇杆值
			RF2G4_Send_Data[12] = (u8)(AV_ADC_Channel3_Sample / 16);    //放入摇杆值
			RF2G4_Send_Data[13] = (u8)(AV_ADC_Channel6_Sample / 16);    //放入摇杆值
		}
		//------------------------------------------------------------------
#endif

        
		//--------------------------------
		if( F_2G4_Send == 1 )// 射频发送(50ms发射一帧数据)
		{
			F_2G4_Send = 0;		// 清除发射标志位
			RF2G4_TX_Mode_X();	//切换为发送
			RF2G4_Tx_Packet((u8 *)RF2G4_Send_Data,14);		// 发射指令
			//RF2G4_RX_Mode_X();	//切换为接收
			LED_Blue =!LED_Blue;  //发射
			//刷新oled
			sum++;
		}
		else if(F_2G4_Receive == 1)	//10ms接收
		 {
			F_2G4_Receive = 0;
			RF2G4_RX_Mode_X();	//切换为接收
			ret = RF2G4_Rx_Packet((u8 *)RF2G4_Receive_Data, 14);
			if (ret == 0) //收到了数据
			{
				printf("%d:收到数据\r\n",sum);
				sum = 0;
				LED_Green =!LED_Green;  //接收
                OLED_main((char *)RF2G4_Receive_Data);
			}
		}

		if(sum > 10)	//断开连接
		{
			handshake();	//等待重连
			sum = 0;	//重新连接成功
			OLED_ShowString(0, 0, "connected!");
		}
	}
}


/***************
		// 射频发送(50ms发射一帧数据)
		//--------------------------------
		if( F_2G4_Send == 1 )
		{
			F_2G4_Send = 0;		// 清除发射标志位
			
			// 判断按键/摇杆的位置（无按键/中间档位，不发射，降低功耗）
			//-----------------------------------------------------
			for(L_CNT=0; L_CNT<10; L_CNT++)
			{
				J_2G4_Data_Send += RF2G4_Send_Data[L_CNT];
			}
			
#if 0	//有动作才发射
			if( J_2G4_Data_Send == 0 &&
			 	RF2G4_Send_Data[10]>118 && RF2G4_Send_Data[10]<145 && 
			 	RF2G4_Send_Data[11]>118 && RF2G4_Send_Data[11]<145 &&
				RF2G4_Send_Data[12]>118 && RF2G4_Send_Data[12]<145 && 
			 	RF2G4_Send_Data[13]>118 && RF2G4_Send_Data[13]<145
			 ) //判断到无动作
			{
				if( F_No_motion == 0 )
				{
					F_No_motion = 1; 		// 第一次回到无动作状态时，发送一次无动作指令
					
					RF2G4_Tx_Packet((u8 *)RF2G4_Send_Data,14);	// 发射指令
				}
			}
			
			else // if( J_2G4_Data_Send>0 || RF2G4_Send_Data[12]<=118 || RF2G4_Send_Data[12]>=137 || RF2G4_Send_Data[13]<=118 || RF2G4_Send_Data[13]>=137 )   //有动作
			{
				J_2G4_Data_Send = 0 ;	// 判断是否需发射数据标志位清0
				
				F_No_motion = 0;		// 当前无动作标志位清0
				
				RF2G4_Tx_Packet((u8 *)RF2G4_Send_Data,14);		// 发射指令
			}
#else	//50ms直接发射
			RF2G4_Tx_Packet((u8 *)RF2G4_Send_Data,14);		// 发射指令

#endif
		}
***************/
