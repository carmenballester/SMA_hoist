/*
 * File: main.c
 *
 * Created with Beyond Control Blockset + Modified Free Waijung Blockset
 *
 * Real-Time Workshop code generated for Simulink model carmen_controller.
 *
 * Model version                        : 1.126
 * Real-Time Workshop file version      : 8.5 (R2013b) 08-Aug-2013
 * Real-Time Workshop file generated on : Fri Jun 17 11:56:17 2022
 * TLC version                          : 8.5 (Aug  6 2013)
 * C/C++ source code generated on       : Fri Jun 17 11:56:18 2022
 *
 * Target selection: stm32f4.tlc
 * Embedded hardware selection: ARM Compatible->Cortex - M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "waijung_hwdrvlib.h"
#include "carmen_controller.h"
#include "rtwtypes.h"                  /* MathWorks types */

/*
 * rt_Onestep is called from a timer ISR at the base sample time of 0.002 sec.
 * The ISR is void SysTick_Handler(void) and is defined in stm32f4xx_it.c
 */
void rt_OneStep(void);
volatile unsigned int systick_count = 0;
static volatile int systick_active = 1;

/* Main program */
int_T main(void)
{
  /* Initialize model */
  carmen_controller_initialize();

  /* Continue indefinitely */
  if (SysTick_Config(SYSTICKRELOADVALUE)) {
    /* Capture error */
    while (1) ;
  }

  NVIC_SetPriority(SysTick_IRQn,15);
  while (1) {
    /* If IDLE TASK Code exist, it will be executed continuosly */
#ifdef IDLE_TASK_STM32F4

    //Sr Antonio
#ifdef IDLE_EXECUTION_TIME_STM32F4

    reset_IDLE_exec_timer_STM32F4();

#endif

    carmen_controller_IDLE();

    //Sr Antonio
#ifdef IDLE_EXECUTION_TIME_STM32F4

    calculate_IDLE_spent_time_STM32F4();

#endif
#endif

  }
}

void rt_OneStep(void)
{
  systick_active = 1;

  /* Tick counter */
  systick_count++;

  /* Step the model */
  //Sr Antonio
#ifdef EXECUTION_TIME_STM32F4

  reset_exec_timer_STM32F4();

#endif

  carmen_controller_step();

  /* Get model outputs here */

  //Sr Antonio
#ifdef EXECUTION_TIME_STM32F4

  calculate_spent_time_STM32F4();

#endif

  /* Profiler update */
}

/* [EOF] */
