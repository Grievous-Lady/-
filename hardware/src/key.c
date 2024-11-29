/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	led.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2016-11-23
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		LED��ʼ��������
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/

//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//Ӳ������
#include "key.h"
#include "delay.h"
#include "led.h"



/*
************************************************************
*	�������ƣ�	Led_Init
*
*	�������ܣ�	��������ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void Key_Init(void)
{

	GPIO_InitTypeDef gpio_initstruct;
	
	EXTI_InitTypeDef exit_initstruct;
	
	NVIC_InitTypeDef nvic_initstruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//��GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);	//��ֹJTAG����
	
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IPU;				//����Ϊ���
	gpio_initstruct.GPIO_Pin = GPIO_Pin_1;						//����ʼ����Pin��
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;				//�ɳ��ص����Ƶ��
	
	GPIO_Init(GPIOA, &gpio_initstruct);							//��ʼ��GPIO
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
	exit_initstruct.EXTI_Line = EXTI_Line1;
	exit_initstruct.EXTI_LineCmd = ENABLE;
	exit_initstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	exit_initstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&exit_initstruct);
	
	
	
	nvic_initstruct.NVIC_IRQChannel = EXTI1_IRQn;
	nvic_initstruct.NVIC_IRQChannelCmd = ENABLE;
	nvic_initstruct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_initstruct.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&nvic_initstruct);
}

void EXTI1_IRQHandler()
{
	DelayXms(10);
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0)
	{
		if(led_info.Led_Status == LED_ON)
		{
			Led_Set(LED_OFF);
		}
		else
		{
				Led_Set(LED_ON);;
		}
			EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
