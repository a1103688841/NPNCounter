/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../../User/button.h"
#include "../../User/tm1637.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;
osThreadId seg_displayHandle;
uint32_t seg_displayBuffer[ 128 ];
osStaticThreadDef_t seg_displayControlBlock;
osThreadId counter_taskHandle;
uint32_t counter_taskBuffer[ 128 ];
osStaticThreadDef_t counter_taskControlBlock;
osThreadId button_taskHandle;
uint32_t button_taskBuffer[ 128 ];
osStaticThreadDef_t button_taskControlBlock;
osThreadId cmd_lineHandle;
uint32_t cmd_lineBuffer[ 128 ];
osStaticThreadDef_t cmd_lineControlBlock;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartSegDisplay(void const * argument);
void StartCounterTask(void const * argument);
void StartButtonTask(void const * argument);
void StartCmdLine(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t  xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t** ppxIdleTaskTCBBuffer, StackType_t** ppxIdleTaskStackBuffer, uint32_t* pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer   = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize   = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128, defaultTaskBuffer, &defaultTaskControlBlock);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of seg_display */
  osThreadStaticDef(seg_display, StartSegDisplay, osPriorityIdle, 0, 128, seg_displayBuffer, &seg_displayControlBlock);
  seg_displayHandle = osThreadCreate(osThread(seg_display), NULL);

  /* definition and creation of counter_task */
  osThreadStaticDef(counter_task, StartCounterTask, osPriorityIdle, 0, 128, counter_taskBuffer, &counter_taskControlBlock);
  counter_taskHandle = osThreadCreate(osThread(counter_task), NULL);

  /* definition and creation of button_task */
  osThreadStaticDef(button_task, StartButtonTask, osPriorityIdle, 0, 128, button_taskBuffer, &button_taskControlBlock);
  button_taskHandle = osThreadCreate(osThread(button_task), NULL);

  /* definition and creation of cmd_line */
  osThreadStaticDef(cmd_line, StartCmdLine, osPriorityIdle, 0, 128, cmd_lineBuffer, &cmd_lineControlBlock);
  cmd_lineHandle = osThreadCreate(osThread(cmd_line), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartSegDisplay */
/**
 * @brief Function implementing the seg_display thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSegDisplay */
void StartSegDisplay(void const * argument)
{
  /* USER CODE BEGIN StartSegDisplay */
    tm1637_task_init();
    /* Infinite loop */
    for (;;)
    {
        tm1637_task_proceess();
        osDelay(pdMS_TO_TICKS(200));
    }
  /* USER CODE END StartSegDisplay */
}

/* USER CODE BEGIN Header_StartCounterTask */
/**
 * @brief Function implementing the counter_task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartCounterTask */
void StartCounterTask(void const * argument)
{
  /* USER CODE BEGIN StartCounterTask */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
  /* USER CODE END StartCounterTask */
}

/* USER CODE BEGIN Header_StartButtonTask */
/**
 * @brief Function implementing the button_task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartButtonTask */
void StartButtonTask(void const * argument)
{
  /* USER CODE BEGIN StartButtonTask */
    /* Infinite loop */
    Button_Attach_ini();
    for (;;)
    {
        Button_Process();
        osDelay(pdMS_TO_TICKS(20));
    }
  /* USER CODE END StartButtonTask */
}

/* USER CODE BEGIN Header_StartCmdLine */
/**
 * @brief Function implementing the cmd_line thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartCmdLine */
void StartCmdLine(void const * argument)
{
  /* USER CODE BEGIN StartCmdLine */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
  /* USER CODE END StartCmdLine */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void pause_button_down_callcak()
{
    counter_display.pause_flag = 1;
}
void rst_button_down_callcak()
{
    counter_display.cnt = 0;
}
/* USER CODE END Application */

