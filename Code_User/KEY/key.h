#ifndef __KEY_H
#define __KEY_H


#include "stm32f10x.h"
#include "bit_band.h"
#include "delay.h"

// 12��������״̬������Ϊ1���ɿ�Ϊ0
//-------------------------------
extern volatile u8 F_KEY_Down[13];
//-------------------------------


// ��������궨��
//------------------------------------------------------------------------
#define 	WKUP_in					PA_in(0)	// WKUP--PA0
#define 	KEY1_in					PC_in(14)	// KEY_1--PC14
#define 	KEY2_in					PC_in(13)	// KEY_2--PC13

#define 	KEY_UP_in				PA_in(11)	// KEY_UP--PA11
#define 	KEY_DOWN_in				PA_in(12)	// KEY_DOWN--PA12
#define 	KEY_LEFT_in				PA_in(15)	// KEY_LEFT--PA15
#define 	KEY_RIGHT_in			PB_in(3)	// KEY_RIGHT--PB3

#define 	KEY_A_in				PB_in(6)	// KEY_A  -- PB6
#define 	KEY_AA_in				PB_in(7)	// KEY_A+ -- PB7
#define 	KEY_B_in				PB_in(8)	// KEY_B  -- PB8
#define 	KEY_BB_in				PB_in(9)	// KEY_B+ -- PB9


#define 	KEY_Rocker1_in			PA_in(8)	// KEY_LeftRocker--PA8
#define 	KEY_Rocker2_in			PC_in(15)	// KEY_RightRocker--PC15
//------------------------------------------------------------------------

// �������
//--------------------------------------------------------------

#define 	KEY_UP				0				// ��
#define 	KEY_DOWN			1				// ��
#define 	KEY_LEFT			2				// ��
#define 	KEY_RIGHT			3				// ��
#define 	KEY_A				4				// A
#define 	KEY_AA				5				// A+
#define 	KEY_B				6				// B
#define 	KEY_BB				7				// B+

#define 	KEY_Rocker1			8				// ҡ��1�İ���
#define 	KEY_Rocker2			9				// ҡ��2�İ���

#define 	WKUP				10				// ���Ѽ�
#define 	KEY1				11				// ����1
#define 	KEY2				12				// ����1

// ������ʼ��
//----------------------------
void KEY_Init_JX(void);

// ����ɨ�躯��
//----------------------------
void RF2G4_KEY_Scan_JX(void);


#endif	/* __KEY_H */
