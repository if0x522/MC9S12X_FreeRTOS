#include <hidef.h>            /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Clock.h"
#include "FreeRTOS.h"
#include "task.h"
#include "COM0.h"


// �������ȼ�
#define START_TASK_PRIO 1
// �����ջ��С
#define START_STK_SIZE 80
// ������
TaskHandle_t StartTask_Handler;
// ������
void start_task(void *pvParameters);

// �������ȼ�
#define TASK1_TASK_PRIO 2
// �����ջ��С
#define TASK1_STK_SIZE 50
// ������
TaskHandle_t Task1Task_Handler;
// ������
void task1_task(void *pvParameters);

// �������ȼ�
#define TASK2_TASK_PRIO 3
// �����ջ��С
#define TASK2_STK_SIZE 50
// ������
TaskHandle_t Task2Task_Handler;
// ������
void task2_task(void *pvParameters);

void main(void) 
{
    Clock_Init();
    COM0_Init();
    ECLKCTL = 0xC0;    //DISABLE ECLK 
    IRQCR_IRQEN = 0;   //DISABLE IRQ INTERRUPT 
    //EnableInterrupts;
    os_printf((byte *)"start RTOS\r\n");
    //TickTimer_SetFreqHz(100);
    //TickTimer_Enable();
    
    xTaskCreate((TaskFunction_t)start_task,
                (const char*)"start_task",
                (uint16_t)START_STK_SIZE,
                (void*)NULL,
                (UBaseType_t)START_TASK_PRIO,
                (TaskHandle_t*)&StartTask_Handler);
    vTaskStartScheduler();  
    os_printf((byte *)"ERROR !!\r\n");  
    for(;;)                                   
  {  
  }
}

// ��ʼ����������
void start_task(void *pvParameters){
    taskENTER_CRITICAL();    // �����ٽ���
    // ����TASK1����
    xTaskCreate((TaskFunction_t)task1_task,
                (const char*)"task1_task",
                (uint16_t)TASK1_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK1_TASK_PRIO,
                (TaskHandle_t*)&Task1Task_Handler);
    // ���������
    xTaskCreate((TaskFunction_t)task2_task,
                (const char*)"task2_task",
                (uint16_t)TASK2_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK2_TASK_PRIO,
                (TaskHandle_t*)&Task2Task_Handler);
     
     vTaskDelete(StartTask_Handler); // ɾ����ʼ����
     taskEXIT_CRITICAL();     //�˳��ٽ���
}
// ����1
void task1_task(void *pvParameters){
   while(1){
     os_printf((byte *)"task1\r\n");
     vTaskDelay(500);
   }
}
// ����2
void task2_task(void *pvParameters){
   while(1){
     os_printf((byte *)"task2\r\n");
     vTaskDelay(300);
   }
}

void vApplicationIdleHook(void){

}