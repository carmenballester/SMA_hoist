/*
 * File: carmen_controller.h
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

#ifndef RTW_HEADER_carmen_controller_h_
#define RTW_HEADER_carmen_controller_h_
#ifndef carmen_controller_COMMON_INCLUDES_
# define carmen_controller_COMMON_INCLUDES_
#include <string.h>
#include "rtwtypes.h"
#include "waijung_hwdrvlib.h"
#endif                                 /* carmen_controller_COMMON_INCLUDES_ */

#include "carmen_controller_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/* Block signals (auto storage) */
typedef struct {
  real32_T Saturation1;                /* '<S2>/Saturation1' */
  real32_T USBVCPReceiverSTM32F4_o1;   /* '<S3>/USB VCP Receiver STM32F4' */
  real32_T USBVCPReceiverSTM32F4_o2;   /* '<S3>/USB VCP Receiver STM32F4' */
  real32_T DataStoreRead6;             /* '<S4>/Data Store Read6' */
  real32_T DataTypeConversion;         /* '<S4>/Data Type Conversion' */
  real32_T ManualSwitch;               /* '<S4>/Manual Switch' */
  real32_T ManualSwitch1;              /* '<S4>/Manual Switch1' */
  uint8_T I2CMasterReadWrite_o1;       /* '<S8>/I2C Master Read//Write' */
  uint8_T I2CMasterReadWrite_o2;       /* '<S8>/I2C Master Read//Write' */
  uint8_T I2CMasterReadWrite_o3;       /* '<S8>/I2C Master Read//Write' */
  uint8_T USBVCPReceiverSTM32F4_o3;    /* '<S3>/USB VCP Receiver STM32F4' */
} BlockIO_carmen_controller;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  int32_T UD_DSTATE;                   /* '<S17>/UD' */
  real32_T CONTROL;                    /* '<Root>/Data Store Memory1' */
  real32_T REF_AMPLITUDE;              /* '<Root>/Data Store Memory11' */
  real32_T PWM_OUT;                    /* '<Root>/Data Store Memory30' */
  real32_T INTENSITY;                  /* '<Root>/Data Store Memory4' */
  real32_T TEMPERATURE;                /* '<Root>/Data Store Memory6' */
  int32_T MEASUR_REAL;                 /* '<Root>/Data Store Memory25' */
  uint16_T MEASUR_CURR;                /* '<Root>/Data Store Memory3' */
  uint16_T OFFSET;                     /* '<Root>/Data Store Memory7' */
  uint16_T MEASUR_PREV;                /* '<Root>/Data Store Memory9' */
  int8_T STEPS;                        /* '<Root>/Data Store Memory5' */
  uint8_T UPDATE_OFFSET;               /* '<S6>/Data Store Memory' */
  uint8_T SENSOR_ERROR;                /* '<Root>/Data Store Memory14' */
  uint8_T AUX;                         /* '<Root>/Data Store Memory2' */
  uint8_T ENABLE_CONTROL;              /* '<Root>/Data Store Memory24' */
} D_Work_carmen_controller;

/* Parameters for system: '<S14>/If Action Subsystem1' */
struct rtP_IfActionSubsystem1_carmen_c_ {
  uint8_T Constant_Value;              /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S18>/Constant'
                                        */
};

/* Parameters (auto storage) */
struct Parameters_carmen_controller_ {
  real_T USBVCPReceiverSTM32F4_P1;     /* Expression: speed
                                        * Referenced by: '<S3>/USB VCP Receiver STM32F4'
                                        */
  real_T USBVCPReceiverSTM32F4_P2;     /* Expression: data_size
                                        * Referenced by: '<S3>/USB VCP Receiver STM32F4'
                                        */
  real_T USBVCPReceiverSTM32F4_P6;     /* Expression: sampletime
                                        * Referenced by: '<S3>/USB VCP Receiver STM32F4'
                                        */
  real_T USBVCPSendSTM32F4_P1;         /* Expression: speed
                                        * Referenced by: '<S4>/USB VCP Send STM32F4'
                                        */
  real_T USBVCPSendSTM32F4_P2;         /* Expression: data_size
                                        * Referenced by: '<S4>/USB VCP Send STM32F4'
                                        */
  real_T USBVCPSendSTM32F4_P6;         /* Expression: sampletime
                                        * Referenced by: '<S4>/USB VCP Send STM32F4'
                                        */
  real32_T Saturation1_UpperSat;       /* Computed Parameter: Saturation1_UpperSat
                                        * Referenced by: '<S2>/Saturation1'
                                        */
  real32_T Saturation1_LowerSat;       /* Computed Parameter: Saturation1_LowerSat
                                        * Referenced by: '<S2>/Saturation1'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S4>/Constant'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S4>/Constant1'
                                        */
  real32_T DataStoreMemory1_InitialValue;/* Computed Parameter: DataStoreMemory1_InitialValue
                                          * Referenced by: '<Root>/Data Store Memory1'
                                          */
  real32_T DataStoreMemory11_InitialValue;/* Expression: single(0)
                                           * Referenced by: '<Root>/Data Store Memory11'
                                           */
  real32_T DataStoreMemory30_InitialValue;/* Computed Parameter: DataStoreMemory30_InitialValue
                                           * Referenced by: '<Root>/Data Store Memory30'
                                           */
  real32_T DataStoreMemory4_InitialValue;/* Computed Parameter: DataStoreMemory4_InitialValue
                                          * Referenced by: '<Root>/Data Store Memory4'
                                          */
  real32_T DataStoreMemory6_InitialValue;/* Computed Parameter: DataStoreMemory6_InitialValue
                                          * Referenced by: '<Root>/Data Store Memory6'
                                          */
  int32_T UD_InitialCondition;         /* Computed Parameter: UD_InitialCondition
                                        * Referenced by: '<S17>/UD'
                                        */
  int32_T Constant_Value_o;            /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S16>/Constant'
                                        */
  int32_T DataStoreMemory25_InitialValue;/* Computed Parameter: DataStoreMemory25_InitialValue
                                          * Referenced by: '<Root>/Data Store Memory25'
                                          */
  int16_T ShiftArithmetic_Power2Exponent;/* Computed Parameter: ShiftArithmetic_Power2Exponent
                                          * Referenced by: '<S23>/Shift Arithmetic'
                                          */
  int16_T ShiftArithmetic1_Power2Exponent;/* Computed Parameter: ShiftArithmetic1_Power2Exponent
                                           * Referenced by: '<S23>/Shift Arithmetic1'
                                           */
  uint16_T USBVCPReceiverSTM32F4_P3[5];/* Computed Parameter: USBVCPReceiverSTM32F4_P3
                                        * Referenced by: '<S3>/USB VCP Receiver STM32F4'
                                        */
  uint16_T USBVCPReceiverSTM32F4_P4[19];/* Computed Parameter: USBVCPReceiverSTM32F4_P4
                                         * Referenced by: '<S3>/USB VCP Receiver STM32F4'
                                         */
  uint16_T USBVCPReceiverSTM32F4_P5[5];/* Computed Parameter: USBVCPReceiverSTM32F4_P5
                                        * Referenced by: '<S3>/USB VCP Receiver STM32F4'
                                        */
  uint16_T USBVCPSendSTM32F4_P3[5];    /* Computed Parameter: USBVCPSendSTM32F4_P3
                                        * Referenced by: '<S4>/USB VCP Send STM32F4'
                                        */
  uint16_T USBVCPSendSTM32F4_P4[27];   /* Computed Parameter: USBVCPSendSTM32F4_P4
                                        * Referenced by: '<S4>/USB VCP Send STM32F4'
                                        */
  uint16_T USBVCPSendSTM32F4_P5[5];    /* Computed Parameter: USBVCPSendSTM32F4_P5
                                        * Referenced by: '<S4>/USB VCP Send STM32F4'
                                        */
  uint16_T DataStoreMemory3_InitialValue;/* Computed Parameter: DataStoreMemory3_InitialValue
                                          * Referenced by: '<Root>/Data Store Memory3'
                                          */
  uint16_T DataStoreMemory7_InitialValue;/* Computed Parameter: DataStoreMemory7_InitialValue
                                          * Referenced by: '<Root>/Data Store Memory7'
                                          */
  uint16_T DataStoreMemory9_InitialValue;/* Computed Parameter: DataStoreMemory9_InitialValue
                                          * Referenced by: '<Root>/Data Store Memory9'
                                          */
  int8_T Constant2_Value;              /* Computed Parameter: Constant2_Value
                                        * Referenced by: '<S21>/Constant2'
                                        */
  int8_T DataStoreMemory5_InitialValue;/* Computed Parameter: DataStoreMemory5_InitialValue
                                        * Referenced by: '<Root>/Data Store Memory5'
                                        */
  uint8_T FixPtConstant_Value;         /* Computed Parameter: FixPtConstant_Value
                                        * Referenced by: '<S20>/FixPt Constant'
                                        */
  uint8_T Constant1_Value_h;           /* Computed Parameter: Constant1_Value_h
                                        * Referenced by: '<S21>/Constant1'
                                        */
  uint8_T Constant_Value_p;            /* Computed Parameter: Constant_Value_p
                                        * Referenced by: '<S22>/Constant'
                                        */
  uint8_T Constant_Value_g;            /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S8>/Constant'
                                        */
  uint8_T DataStoreMemory_InitialValue;/* Computed Parameter: DataStoreMemory_InitialValue
                                        * Referenced by: '<S6>/Data Store Memory'
                                        */
  uint8_T ManualSwitch_CurrentSetting; /* Computed Parameter: ManualSwitch_CurrentSetting
                                        * Referenced by: '<S4>/Manual Switch'
                                        */
  uint8_T ManualSwitch1_CurrentSetting;/* Computed Parameter: ManualSwitch1_CurrentSetting
                                        * Referenced by: '<S4>/Manual Switch1'
                                        */
  uint8_T DataStoreMemory14_InitialValue;/* Computed Parameter: DataStoreMemory14_InitialValue
                                          * Referenced by: '<Root>/Data Store Memory14'
                                          */
  uint8_T DataStoreMemory2_InitialValue;/* Computed Parameter: DataStoreMemory2_InitialValue
                                         * Referenced by: '<Root>/Data Store Memory2'
                                         */
  uint8_T DataStoreMemory24_InitialValue;/* Computed Parameter: DataStoreMemory24_InitialValue
                                          * Referenced by: '<Root>/Data Store Memory24'
                                          */
  boolean_T Constant_Value_of;         /* Computed Parameter: Constant_Value_of
                                        * Referenced by: '<S24>/Constant'
                                        */
  boolean_T Constant1_Value_m;         /* Computed Parameter: Constant1_Value_m
                                        * Referenced by: '<S24>/Constant1'
                                        */
  boolean_T Constant2_Value_o;         /* Computed Parameter: Constant2_Value_o
                                        * Referenced by: '<S24>/Constant2'
                                        */
  rtP_IfActionSubsystem1_carmen_c IfActionSubsystem1;/* '<S10>/If Action Subsystem1' */
  rtP_IfActionSubsystem1_carmen_c IfActionSubsystem1_h;/* '<S14>/If Action Subsystem1' */
};

/* Real-time Model Data Structure */
struct tag_RTM_carmen_controller {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block parameters (auto storage) */
extern Parameters_carmen_controller const const carmen_controller_P;

/* Block signals (auto storage) */
extern BlockIO_carmen_controller carmen_controller_B;

/* Block states (auto storage) */
extern D_Work_carmen_controller carmen_controller_DWork;

/* Model entry point functions */
extern void carmen_controller_initialize(void);
extern void carmen_controller_step(void);
extern void carmen_controller_terminate(void);

/* Real-time Model object */
extern RT_MODEL_carmen_controller *const carmen_controller_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'carmen_controller'
 * '<S1>'   : 'carmen_controller/Control Logic'
 * '<S2>'   : 'carmen_controller/PWM Output'
 * '<S3>'   : 'carmen_controller/USB Receiver'
 * '<S4>'   : 'carmen_controller/USB Send'
 * '<S5>'   : 'carmen_controller/Control Logic/Read Sensor'
 * '<S6>'   : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position'
 * '<S7>'   : 'carmen_controller/Control Logic/Read Sensor/Intensity Readout'
 * '<S8>'   : 'carmen_controller/Control Logic/Read Sensor/Sensor Readout'
 * '<S9>'   : 'carmen_controller/Control Logic/Read Sensor/Temperature Readout '
 * '<S10>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Anti-Slide'
 * '<S11>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Calculate Offset'
 * '<S12>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Check Update'
 * '<S13>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/MATLAB Function1'
 * '<S14>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Anti-Slide/If Action Subsystem'
 * '<S15>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Anti-Slide/If Action Subsystem1'
 * '<S16>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Anti-Slide/If Action Subsystem/Compare To Constant'
 * '<S17>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Anti-Slide/If Action Subsystem/Difference'
 * '<S18>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Anti-Slide/If Action Subsystem/If Action Subsystem1'
 * '<S19>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Anti-Slide/If Action Subsystem/If Action Subsystem2'
 * '<S20>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Anti-Slide/If Action Subsystem/If Action Subsystem2/Increment Stored Integer'
 * '<S21>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Calculate Offset/If Action Subsystem'
 * '<S22>'  : 'carmen_controller/Control Logic/Read Sensor/Calculate the SMA real position/Check Update/If Action Subsystem2'
 * '<S23>'  : 'carmen_controller/Control Logic/Read Sensor/Sensor Readout/Data Composer'
 * '<S24>'  : 'carmen_controller/Control Logic/Read Sensor/Sensor Readout/Select Sensor'
 * '<S25>'  : 'carmen_controller/Control Logic/Read Sensor/Temperature Readout /Lowpass Filter'
 * '<S26>'  : 'carmen_controller/Control Logic/Read Sensor/Temperature Readout /Subsystem'
 * '<S27>'  : 'carmen_controller/PWM Output/MATLAB Function'
 * '<S28>'  : 'carmen_controller/PWM Output/MATLAB Function1'
 */
#endif                                 /* RTW_HEADER_carmen_controller_h_ */

/* [EOF] */
