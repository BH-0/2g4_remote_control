#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"


// �궨��
//--------------------------------------------------
#define LED_Green	PB_out(4)	// Green -- PB4
#define LED_Blue	PB_out(5)	// Blue  -- PB5



// ��ʼ��PB4��PB5
//--------------------------------------------------
void LED_Init_JX(void);		// PB4��PB5��Ϊ���������



#endif	/* __LED_H */
