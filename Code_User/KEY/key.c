#include "key.h"

// �������¼�ʱ
// -------------------------
u8 WKUP_Cnt = 0;	
u8 KEY1_Cnt = 0;
u8 KEY2_Cnt = 0;
u8 KEY_UP_Cnt = 0;
u8 KEY_DOWN_Cnt = 0;
u8 KEY_LEFT_Cnt = 0;
u8 KEY_RIGHT_Cnt = 0;
u8 KEY_A_Cnt = 0;
u8 KEY_AA_Cnt = 0;
u8 KEY_B_Cnt = 0;
u8 KEY_BB_Cnt = 0;
u8 KEY_Rocker1_Cnt = 0;
u8 KEY_Rocker2_Cnt = 0;
// -------------------------

// 12��������״̬������Ϊ1���ɿ�Ϊ0
//-------------------------------
volatile u8 F_KEY_Down[13] = { 0 };
//-------------------------------



// ������ʼ��
//---------------------
void KEY_Init_JX(void)
{	
	GPIO_InitTypeDef  GPIO_InitStructure;						// ����GPIO_InitTypeDef�ͽṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		// JTAGʧ��
	
	// ʹ��GPIOA��GPIOC�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	// ʹ��GPIOʱ��
	
	
	// ������WKUP--PA0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				// WKUP--PA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 			// ��������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		// ����ģʽ����Ҫ��˿��ٶ�
	GPIO_Init(GPIOA, &GPIO_InitStructure);					// �����趨������ʼ��PA0
	
	
	// ������KEY_LeftRocker--PA8��KEY_UP--PA11��KEY_DOWN--PA12��KEY_LEFT--PA15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			// ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);					// �����趨������ʼ��
	
	
	// ������KEY_RIGHT--PB3��KEY_A--PB6��KEY_A+--PB7��KEY_B--PB8��KEY_B+--PB9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			// ��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);					// �����趨������ʼ��
	
	
	// ������KEY_1--PC14��KEY_2--PC13��KEY_RightRocker--PC15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			// ��������
	GPIO_Init(GPIOC, &GPIO_InitStructure);					// �����趨������ʼ��
	
}




// ����ɨ�躯��
//------------------------------------------
void RF2G4_KEY_Scan_JX(void)
{
	// WKUP
	//------------------------------------
	if(!WKUP_in)
	{ WKUP_Cnt = 0; F_KEY_Down[WKUP] = 0;}
	else
	{	WKUP_Cnt ++ ;
		if( WKUP_Cnt>10 )
		{ F_KEY_Down[WKUP] = 1; }
	}
	//------------------------------------
	
	// KEY1
	//------------------------------------
	if(KEY1_in)
	{ KEY1_Cnt = 0; F_KEY_Down[KEY1] = 0;}
	else
	{	KEY1_Cnt ++ ;
		if( KEY1_Cnt>10 )
		{ F_KEY_Down[KEY1] = 1; }
	}
	//------------------------------------

	// KEY2
	//------------------------------------
	if(KEY2_in)
	{ KEY2_Cnt = 0; F_KEY_Down[KEY2] = 0;}
	else
	{	KEY2_Cnt ++ ;
		if( KEY2_Cnt>10 )
		{ F_KEY_Down[KEY2] = 1; }
	}
	//------------------------------------
	
	// KEY_UP
	//------------------------------------
	if(KEY_UP_in)
	{ KEY_UP_Cnt = 0; F_KEY_Down[KEY_UP] = 0;}
	else
	{	KEY_UP_Cnt ++ ;
		if( KEY_UP_Cnt>10 )
		{ F_KEY_Down[KEY_UP] = 1; }
	}
	//------------------------------------
	
	// KEY_DOWN
	//------------------------------------
	if(KEY_DOWN_in)
	{ KEY_DOWN_Cnt = 0; F_KEY_Down[KEY_DOWN] = 0;}
	else
	{	KEY_DOWN_Cnt ++ ;
		if( KEY_DOWN_Cnt>10 )
		{ F_KEY_Down[KEY_DOWN] = 1; }
	}
	//------------------------------------
	
	// KEY_LEFT
	//------------------------------------
	if(KEY_LEFT_in)
	{ KEY_LEFT_Cnt = 0; F_KEY_Down[KEY_LEFT] = 0;}
	else
	{	KEY_LEFT_Cnt ++ ;
		if( KEY_LEFT_Cnt>10 )
		{ F_KEY_Down[KEY_LEFT] = 1; }
	}
	//------------------------------------
	
	// KEY_RIGHT
	//------------------------------------
	if(KEY_RIGHT_in)
	{ KEY_RIGHT_Cnt = 0; F_KEY_Down[KEY_RIGHT] = 0;}
	else
	{	KEY_RIGHT_Cnt ++ ;
		if( KEY_RIGHT_Cnt>10 )
		{ F_KEY_Down[KEY_RIGHT] = 1; }
	}
	//------------------------------------
	
	// KEY_A
	//------------------------------------
	if(KEY_A_in)
	{ KEY_A_Cnt = 0; F_KEY_Down[KEY_A] = 0;}
	else
	{	KEY_A_Cnt ++ ;
		if( KEY_A_Cnt>10 )
		{ F_KEY_Down[KEY_A] = 1; }
	}
	//------------------------------------
	
	// KEY_AA
	//------------------------------------
	if(KEY_AA_in)
	{ KEY_AA_Cnt = 0; F_KEY_Down[KEY_AA] = 0;}
	else
	{	KEY_AA_Cnt ++ ;
		if( KEY_AA_Cnt>10 )
		{ F_KEY_Down[KEY_AA] = 1; }
	}
	//------------------------------------
	
	// KEY_B
	//------------------------------------
	if(KEY_B_in)
	{ KEY_B_Cnt = 0; F_KEY_Down[KEY_B] = 0;}
	else
	{	KEY_B_Cnt ++ ;
		if( KEY_B_Cnt>10 )
		{ F_KEY_Down[KEY_B] = 1; }
	}
	//------------------------------------
	
	// KEY_BB
	//------------------------------------
	if(KEY_BB_in)
	{ KEY_BB_Cnt = 0; F_KEY_Down[KEY_BB] = 0;}
	else
	{	KEY_BB_Cnt ++ ;
		if( KEY_BB_Cnt>10 )
		{ F_KEY_Down[KEY_BB] = 1; }
	}
	//------------------------------------
	
	// KEY_Rocker1
	//------------------------------------
	if(KEY_Rocker1_in)
	{ KEY_Rocker1_Cnt = 0; F_KEY_Down[KEY_Rocker1] = 0;}
	else
	{	KEY_Rocker1_Cnt ++ ;
		if( KEY_Rocker1_Cnt>10 )
		{ F_KEY_Down[KEY_Rocker1] = 1; }
	}
	//------------------------------------
	
	// KEY_RightRocker
	//------------------------------------
	if(KEY_Rocker2_in)
	{ KEY_Rocker2_Cnt = 0; F_KEY_Down[KEY_Rocker2] = 0;}
	else
	{	KEY_Rocker2_Cnt ++ ;
		if( KEY_Rocker2_Cnt>10 )
		{ F_KEY_Down[KEY_Rocker2] = 1; }
	}
	//------------------------------------
}
//------------------------------------------

