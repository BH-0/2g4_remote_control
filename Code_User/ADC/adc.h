#ifndef __ADC_H
#define __ADC_H


#include "stm32f10x.h"
#include "bit_band.h"
#include "delay.h"
#include "dma.h"


//------------------------------------------------------------
#define		C_ADC_Channel			2		// ADCͨ����
#define		N_ADC_Channel_1			1		// ADCͨ��1
#define		N_ADC_Channel_2			2		// ADCͨ��2
#define		N_ADC_Channel_3			3		// ADCͨ��3
#define		N_ADC_Channel_6			6		// ADCͨ��6
#define 	C_Channel_Sample		10		// ADC��������
//------------------------------------------------------------

//--------------------------------------------------------------------------
extern u8   C_ADC_Sample ;					// ADC��������
	
extern u32  AM_ADC_Channel1_Sample ;		// ADCͨ��1�����ܼ�
extern u32  AM_ADC_Channel3_Sample ;		// ADCͨ��3�����ܼ�
	
extern volatile u16  AV_ADC_Channel1_Sample ;		// ADC_CH1ƽ��ֵ
extern volatile u16  AV_ADC_Channel3_Sample ;		// ADC_CH3ƽ��ֵ


extern u16 ADC1_Value[C_Channel_Sample][C_ADC_Channel];	// DMA�������ݴ�Ŵ�
//--------------------------------------------------------------------------

// ҡ�˵�ADC��ʼ��
void ADC1_Rocker_Init(void);

// ��ȡADCͨ��1/3��ƽ��ֵ
void ADC1_Value_average(void);


#endif	/* __ADC_H */

