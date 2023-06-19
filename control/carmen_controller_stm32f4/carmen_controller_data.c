/*
 * File: carmen_controller_data.c
 *
 * Created with Beyond Control Blockset + Modified Free Waijung Blockset
 *
 * Real-Time Workshop code generated for Simulink model carmen_controller.
 *
 * Model version                        : 1.145
 * Real-Time Workshop file version      : 8.5 (R2013b) 08-Aug-2013
 * Real-Time Workshop file generated on : Wed May 31 09:22:14 2023
 * TLC version                          : 8.5 (Aug  6 2013)
 * C/C++ source code generated on       : Wed May 31 09:22:20 2023
 *
 * Target selection: stm32f4.tlc
 * Embedded hardware selection: ARM Compatible->Cortex - M4
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "carmen_controller.h"
#include "carmen_controller_private.h"

/* Block parameters (auto storage) */
Parameters_carmen_controller const const carmen_controller_P = {
  1.0,                                 /* Expression: speed
                                        * Referenced by: '<S3>/USB VCP Receiver STM32F4'
                                        */
  1.0,                                 /* Expression: data_size
                                        * Referenced by: '<S3>/USB VCP Receiver STM32F4'
                                        */
  0.01,                                /* Expression: sampletime
                                        * Referenced by: '<S3>/USB VCP Receiver STM32F4'
                                        */
  1.0,                                 /* Expression: speed
                                        * Referenced by: '<S4>/USB VCP Send STM32F4'
                                        */
  1.0,                                 /* Expression: data_size
                                        * Referenced by: '<S4>/USB VCP Send STM32F4'
                                        */
  0.01,                                /* Expression: sampletime
                                        * Referenced by: '<S4>/USB VCP Send STM32F4'
                                        */
  100.0F,                              /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S2>/Saturation1'
                                        */
  0.0F,                                /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S2>/Saturation1'
                                        */
  1.0F,                                /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S4>/Constant'
                                        */
  1.0F,                                /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S4>/Constant1'
                                        */
  0.0F,                                /* Computed Parameter: DataStoreMemory1_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory1'
                                        */
  0.0F,                                /* Expression: single(0)
                                        * Referenced by: '<Root>/Data Store Memory11'
                                        */
  0.0F,                                /* Computed Parameter: DataStoreMemory30_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory30'
                                        */
  0.0F,                                /* Computed Parameter: DataStoreMemory4_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory4'
                                        */
  0.0F,                                /* Computed Parameter: DataStoreMemory6_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory6'
                                        */
  0,                                   /* Computed Parameter: UD_InitialCondition
                                        * Referenced by: '<S17>/UD'
                                        */
  15,                                  /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S16>/Constant'
                                        */
  0,                                   /* Computed Parameter: DataStoreMemory25_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory25'
                                        */
  8,                                   /* Computed Parameter: ShiftArithmetic_Power2Exponent
                                        * Referenced by: '<S23>/Shift Arithmetic'
                                        */
  -4,                                  /* Computed Parameter: ShiftArithmetic1_Power2Exponent
                                        * Referenced by: '<S23>/Shift Arithmetic1'
                                        */

  /*  Computed Parameter: USBVCPReceiverSTM32F4_P3
   * Referenced by: '<S3>/USB VCP Receiver STM32F4'
   */
  { 48U, 69U, 32U, 48U, 69U },

  /*  Computed Parameter: USBVCPReceiverSTM32F4_P4
   * Referenced by: '<S3>/USB VCP Receiver STM32F4'
   */
  { 115U, 105U, 110U, 103U, 108U, 101U, 32U, 115U, 105U, 110U, 103U, 108U, 101U,
    32U, 117U, 105U, 110U, 116U, 56U },

  /*  Computed Parameter: USBVCPReceiverSTM32F4_P5
   * Referenced by: '<S3>/USB VCP Receiver STM32F4'
   */
  { 48U, 65U, 32U, 48U, 65U },

  /*  Computed Parameter: USBVCPSendSTM32F4_P3
   * Referenced by: '<S4>/USB VCP Send STM32F4'
   */
  { 48U, 69U, 32U, 48U, 69U },

  /*  Computed Parameter: USBVCPSendSTM32F4_P4
   * Referenced by: '<S4>/USB VCP Send STM32F4'
   */
  { 115U, 105U, 110U, 103U, 108U, 101U, 32U, 115U, 105U, 110U, 103U, 108U, 101U,
    32U, 115U, 105U, 110U, 103U, 108U, 101U, 32U, 115U, 105U, 110U, 103U, 108U,
    101U },

  /*  Computed Parameter: USBVCPSendSTM32F4_P5
   * Referenced by: '<S4>/USB VCP Send STM32F4'
   */
  { 48U, 65U, 32U, 48U, 65U },
  0U,                                  /* Computed Parameter: DataStoreMemory3_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory3'
                                        */
  150U,                                /* Computed Parameter: DataStoreMemory7_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory7'
                                        */
  0U,                                  /* Computed Parameter: DataStoreMemory9_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory9'
                                        */
  0,                                   /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S21>/Constant2'
                                        */
  0,                                   /* Computed Parameter: DataStoreMemory5_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory5'
                                        */
  1U,                                  /* Computed Parameter: FixPtConstant_Value
                                        * Referenced by: '<S20>/FixPt Constant'
                                        */
  1U,                                  /* Computed Parameter: Constant1_Value_h
                                        * Referenced by: '<S21>/Constant1'
                                        */
  0U,                                  /* Computed Parameter: Constant_Value_p
                                        * Referenced by: '<S22>/Constant'
                                        */
  128U,                                /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S8>/Constant'
                                        */
  0U,                                  /* Computed Parameter: DataStoreMemory_InitialValue
                                        * Referenced by: '<S6>/Data Store Memory'
                                        */
  1U,                                  /* Computed Parameter: ManualSwitch_CurrentSetting
                                        * Referenced by: '<S4>/Manual Switch'
                                        */
  1U,                                  /* Computed Parameter: ManualSwitch1_CurrentSetting
                                        * Referenced by: '<S4>/Manual Switch1'
                                        */
  0U,                                  /* Computed Parameter: DataStoreMemory14_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory14'
                                        */
  0U,                                  /* Computed Parameter: DataStoreMemory2_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory2'
                                        */
  0U,                                  /* Computed Parameter: DataStoreMemory24_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory24'
                                        */
  0,                                   /* Computed Parameter: Constant_Value_of
                                        * Referenced by: '<S24>/Constant'
                                        */
  1,                                   /* Computed Parameter: Constant1_Value_m
                                        * Referenced by: '<S24>/Constant1'
                                        */
  1,                                   /* Computed Parameter: Constant2_Value_o
                                        * Referenced by: '<S24>/Constant2'
                                        */

  /* Start of '<S10>/If Action Subsystem1' */
  {
    0U                                 /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S15>/Constant'
                                        */
  }
  /* End of '<S10>/If Action Subsystem1' */
  ,

  /* Start of '<S14>/If Action Subsystem1' */
  {
    0U                                 /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S18>/Constant'
                                        */
  }
  /* End of '<S14>/If Action Subsystem1' */
};

/* [EOF] */
