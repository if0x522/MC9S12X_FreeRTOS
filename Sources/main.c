#include <hidef.h>            /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "Clock.h"
#include "FreeRTOS.h"
#include "task.h"
#include "COM0.h"


// 任务优先级
#define START_TASK_PRIO 1
// 任务堆栈大小
#define START_STK_SIZE 80
// 任务句柄
TaskHandle_t StartTask_Handler;
// 任务函数
void start_task(void *pvParameters);

// 任务优先级
#define TASK1_TASK_PRIO 2
// 任务堆栈大小
#define TASK1_STK_SIZE 50
// 任务句柄
TaskHandle_t Task1Task_Handler;
// 任务函数
void task1_task(void *pvParameters);

// 任务优先级
#define TASK2_TASK_PRIO 3
// 任务堆栈大小
#define TASK2_STK_SIZE 50
// 任务句柄
TaskHandle_t Task2Task_Handler;
// 任务函数
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

// 开始任务任务函数
void start_task(void *pvParameters){
    taskENTER_CRITICAL();    // 进入临界区
    // 创建TASK1任务
    xTaskCreate((TaskFunction_t)task1_task,
                (const char*)"task1_task",
                (uint16_t)TASK1_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK1_TASK_PRIO,
                (TaskHandle_t*)&Task1Task_Handler);
    // 创建任务二
    xTaskCreate((TaskFunction_t)task2_task,
                (const char*)"task2_task",
                (uint16_t)TASK2_STK_SIZE,
                (void *)NULL,
                (UBaseType_t)TASK2_TASK_PRIO,
                (TaskHandle_t*)&Task2Task_Handler);
     
     vTaskDelete(StartTask_Handler); // 删除开始任务
     taskEXIT_CRITICAL();     //退出临界区
}
// 任务1
void task1_task(void *pvParameters){
   while(1){
     os_printf((byte *)"task1\r\n");
     vTaskDelay(500);
   }
}
// 任务2
void task2_task(void *pvParameters){
   while(1){
     os_printf((byte *)"task2\r\n");
     vTaskDelay(300);
   }
}

void vApplicationIdleHook(void){

}