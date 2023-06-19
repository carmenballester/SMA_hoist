/*
 * File: carmen_controller.c
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

/* Block signals (auto storage) */
BlockIO_carmen_controller carmen_controller_B;

/* Block states (auto storage) */
D_Work_carmen_controller carmen_controller_DWork;

/* Real-time model */
RT_MODEL_carmen_controller carmen_controller_M_;
RT_MODEL_carmen_controller *const carmen_controller_M = &carmen_controller_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (carmen_controller_M->Timing.TaskCounters.TID[1])++;
  if ((carmen_controller_M->Timing.TaskCounters.TID[1]) > 4) {/* Sample time: [0.01s, 0.0s] */
    carmen_controller_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/*
 * Output and update for action system:
 *    '<S14>/If Action Subsystem1'
 *    '<S10>/If Action Subsystem1'
 */
void carmen_contr_IfActionSubsystem1(rtP_IfActionSubsystem1_carmen_c *localP,
  uint8_T *rtd_UPDATE_OFFSET)
{
  /* DataStoreWrite: '<S18>/Data Store Write' incorporates:
   *  Constant: '<S18>/Constant'
   */
  *rtd_UPDATE_OFFSET = localP->Constant_Value;
}

/* Model step function */
void carmen_controller_step(void)
{
  int8_T pasos;
  real32_T rtb_DataStoreRead2;
  real32_T rtb_DataStoreRead3;
  int32_T rtb_DataStoreRead1_m;
  real32_T rtb_act;
  int32_T u;

  /* S-Function (stm32f4_digital_output): '<S24>/Digital Output3' */

  /* ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3 */
  if (carmen_controller_P.Constant_Value_of == 0x01) {
    GPIO_SetBits(GPIOA, GPIO_Pin_4);
  } else {
    GPIO_ResetBits(GPIOA, GPIO_Pin_4);
  }

  if (carmen_controller_P.Constant1_Value_m == 0x01) {
    GPIO_SetBits(GPIOA, GPIO_Pin_5);
  } else {
    GPIO_ResetBits(GPIOA, GPIO_Pin_5);
  }

  if (carmen_controller_P.Constant2_Value_o == 0x01) {
    GPIO_SetBits(GPIOA, GPIO_Pin_6);
  } else {
    GPIO_ResetBits(GPIOA, GPIO_Pin_6);
  }

  /* I2C Transaction, Name: <S8>/I2C Master Read//Write
   * ID : I2CMasterReadWrite (ControlLogicReadSensorSensorReadoutI2CMasterReadWrite)
   * Info: Write byte(s)= 0, Read byte(s)= 2, Wait write time(mS)= 0,
   */
  {
    /* I2C Transaction processing */
    carmen_controller_B.I2CMasterReadWrite_o1 = (uint8_T)i2c1_trans_proc
      (carmen_controller_P.Constant_Value_g, &I2CMasterReadWrite);

    /* Update output */
    carmen_controller_B.I2CMasterReadWrite_o2 = I2CMasterReadWrite.readbuffer[0];/* Rd0 */
    carmen_controller_B.I2CMasterReadWrite_o3 = I2CMasterReadWrite.readbuffer[1];/* Rd1 */
  }

  /* DataStoreWrite: '<S8>/Data Store Write2' incorporates:
   *  ArithShift: '<S23>/Shift Arithmetic'
   *  ArithShift: '<S23>/Shift Arithmetic1'
   *  DataTypeConversion: '<S23>/Data Type  Conversion'
   *  DataTypeConversion: '<S23>/Data Type  Conversion1'
   *  S-Function (sfix_bitop): '<S23>/Bitwise Operator'
   */
  carmen_controller_DWork.MEASUR_CURR = (uint16_T)
    ((carmen_controller_B.I2CMasterReadWrite_o2 << 8 |
      carmen_controller_B.I2CMasterReadWrite_o3) >> 4);

  /* DataStoreWrite: '<S8>/Data Store Write4' */
  carmen_controller_DWork.SENSOR_ERROR =
    carmen_controller_B.I2CMasterReadWrite_o1;

  /* If: '<S12>/If1' incorporates:
   *  DataStoreRead: '<S12>/Data Store Read5'
   */
  if (carmen_controller_DWork.UPDATE_OFFSET == 210) {
    /* Outputs for IfAction SubSystem: '<S12>/If Action Subsystem2' incorporates:
     *  ActionPort: '<S22>/Action Port'
     */
    /* DataStoreWrite: '<S22>/Data Store Write' incorporates:
     *  Constant: '<S22>/Constant'
     */
    carmen_controller_DWork.UPDATE_OFFSET = carmen_controller_P.Constant_Value_p;

    /* DataStoreWrite: '<S22>/Data Store Write1' incorporates:
     *  Constant: '<S22>/Constant'
     */
    carmen_controller_DWork.AUX = carmen_controller_P.Constant_Value_p;

    /* End of Outputs for SubSystem: '<S12>/If Action Subsystem2' */
  }

  /* End of If: '<S12>/If1' */

  /* If: '<S10>/If' incorporates:
   *  DataStoreRead: '<S10>/Data Store Read1'
   */
  if (carmen_controller_DWork.MEASUR_REAL < 0) {
    /* Outputs for IfAction SubSystem: '<S10>/If Action Subsystem' incorporates:
     *  ActionPort: '<S14>/Action Port'
     */
    /* DataStoreRead: '<S14>/Data Store Read1' */
    rtb_DataStoreRead1_m = carmen_controller_DWork.MEASUR_REAL;

    /* Sum: '<S17>/Diff' incorporates:
     *  DataStoreRead: '<S14>/Data Store Read1'
     *  UnitDelay: '<S17>/UD'
     */
    u = carmen_controller_DWork.MEASUR_REAL - carmen_controller_DWork.UD_DSTATE;

    /* Abs: '<S14>/Abs' */
    if (u < 0) {
      u = -u;
    }

    /* If: '<S14>/If' incorporates:
     *  Abs: '<S14>/Abs'
     *  Constant: '<S16>/Constant'
     *  RelationalOperator: '<S16>/Compare'
     */
    if ((u <= carmen_controller_P.Constant_Value_o) == 1) {
      /* Outputs for IfAction SubSystem: '<S14>/If Action Subsystem2' incorporates:
       *  ActionPort: '<S19>/Action Port'
       */
      /* DataStoreWrite: '<S19>/Data Store Write' incorporates:
       *  Constant: '<S20>/FixPt Constant'
       *  DataStoreRead: '<S19>/Data Store Read'
       *  Sum: '<S20>/FixPt Sum1'
       */
      carmen_controller_DWork.UPDATE_OFFSET = (uint8_T)((uint32_T)
        carmen_controller_DWork.UPDATE_OFFSET +
        carmen_controller_P.FixPtConstant_Value);

      /* End of Outputs for SubSystem: '<S14>/If Action Subsystem2' */
    } else {
      /* Outputs for IfAction SubSystem: '<S14>/If Action Subsystem1' incorporates:
       *  ActionPort: '<S18>/Action Port'
       */
      carmen_contr_IfActionSubsystem1((rtP_IfActionSubsystem1_carmen_c *)
        &carmen_controller_P.IfActionSubsystem1_h,
        &carmen_controller_DWork.UPDATE_OFFSET);

      /* End of Outputs for SubSystem: '<S14>/If Action Subsystem1' */
    }

    /* End of If: '<S14>/If' */

    /* Update for UnitDelay: '<S17>/UD' */
    carmen_controller_DWork.UD_DSTATE = rtb_DataStoreRead1_m;

    /* End of Outputs for SubSystem: '<S10>/If Action Subsystem' */
  } else {
    /* Outputs for IfAction SubSystem: '<S10>/If Action Subsystem1' incorporates:
     *  ActionPort: '<S15>/Action Port'
     */
    carmen_contr_IfActionSubsystem1((rtP_IfActionSubsystem1_carmen_c *)
      &carmen_controller_P.IfActionSubsystem1,
      &carmen_controller_DWork.UPDATE_OFFSET);

    /* End of Outputs for SubSystem: '<S10>/If Action Subsystem1' */
  }

  /* End of If: '<S10>/If' */

  /* If: '<S11>/If' incorporates:
   *  DataStoreRead: '<S11>/Data Store Read1'
   */
  if (carmen_controller_DWork.AUX == 0) {
    /* Outputs for IfAction SubSystem: '<S11>/If Action Subsystem' incorporates:
     *  ActionPort: '<S21>/Action Port'
     */
    /* DataStoreWrite: '<S21>/Data Store Write5' incorporates:
     *  Constant: '<S21>/Constant1'
     */
    carmen_controller_DWork.AUX = carmen_controller_P.Constant1_Value_h;

    /* DataStoreWrite: '<S21>/Data Store Write2' incorporates:
     *  Constant: '<S21>/Constant2'
     */
    carmen_controller_DWork.STEPS = carmen_controller_P.Constant2_Value;

    /* DataStoreWrite: '<S21>/Data Store Write1' incorporates:
     *  DataStoreRead: '<S21>/Data Store Read3'
     */
    carmen_controller_DWork.OFFSET = carmen_controller_DWork.MEASUR_CURR;

    /* DataStoreWrite: '<S21>/Data Store Write3' incorporates:
     *  DataStoreRead: '<S21>/Data Store Read3'
     */
    carmen_controller_DWork.MEASUR_PREV = carmen_controller_DWork.MEASUR_CURR;

    /* End of Outputs for SubSystem: '<S11>/If Action Subsystem' */
  }

  /* End of If: '<S11>/If' */

  /* MATLAB Function: '<S6>/MATLAB Function1' incorporates:
   *  DataStoreRead: '<S6>/Data Store Read2'
   *  DataStoreRead: '<S6>/Data Store Read4'
   *  DataStoreRead: '<S6>/Data Store Read6'
   */
  pasos = carmen_controller_DWork.STEPS;

  /* MATLAB Function 'Control Logic/Read Sensor/Calculate the SMA real position/MATLAB Function1': '<S13>:1' */
  /* '<S13>:1:4' */
  if ((carmen_controller_DWork.MEASUR_CURR > 3500) &&
      (carmen_controller_DWork.MEASUR_PREV < 1000)) {
    /* '<S13>:1:6' */
    /* '<S13>:1:7' */
    /* '<S13>:1:8' */
    rtb_DataStoreRead1_m = carmen_controller_DWork.STEPS + 1;
    if (rtb_DataStoreRead1_m > 127) {
      rtb_DataStoreRead1_m = 127;
    }

    pasos = (int8_T)rtb_DataStoreRead1_m;
  }

  if ((carmen_controller_DWork.MEASUR_CURR < 1000) &&
      (carmen_controller_DWork.MEASUR_PREV > 3500)) {
    /* '<S13>:1:12' */
    /* '<S13>:1:13' */
    /* '<S13>:1:14' */
    rtb_DataStoreRead1_m = pasos - 1;
    if (rtb_DataStoreRead1_m < -128) {
      rtb_DataStoreRead1_m = -128;
    }

    pasos = (int8_T)rtb_DataStoreRead1_m;

    /* if(pasos>250) */
    /*    pasos=uint8(0);  */
    /* end */
  }

  /* '<S13>:1:20' */
  if (pasos == 0) {
    /* DataStoreWrite: '<S6>/Data Store Write8' incorporates:
     *  DataStoreRead: '<S6>/Data Store Read3'
     */
    /* '<S13>:1:22' */
    /* '<S13>:1:23' */
    carmen_controller_DWork.MEASUR_REAL = carmen_controller_DWork.OFFSET -
      carmen_controller_DWork.MEASUR_CURR;
  } else {
    /* DataStoreWrite: '<S6>/Data Store Write8' incorporates:
     *  DataStoreRead: '<S6>/Data Store Read3'
     */
    /* '<S13>:1:25' */
    carmen_controller_DWork.MEASUR_REAL = ((pasos << 12) +
      carmen_controller_DWork.OFFSET) - carmen_controller_DWork.MEASUR_CURR;
  }

  /* DataStoreWrite: '<S6>/Data Store Write5' incorporates:
   *  DataStoreRead: '<S6>/Data Store Read6'
   */
  carmen_controller_DWork.MEASUR_PREV = carmen_controller_DWork.MEASUR_CURR;

  /* DataStoreWrite: '<S6>/Data Store Write7' incorporates:
   *  MATLAB Function: '<S6>/MATLAB Function1'
   */
  carmen_controller_DWork.STEPS = pasos;

  /* MATLAB Function: '<S2>/MATLAB Function' incorporates:
   *  DataStoreRead: '<S2>/Data Store Read1'
   *  DataStoreRead: '<S2>/Data Store Read4'
   */
  /* MATLAB Function 'PWM Output/MATLAB Function': '<S27>:1' */
  if (carmen_controller_DWork.ENABLE_CONTROL == 0) {
    /* '<S27>:1:4' */
    /* '<S27>:1:5' */
    rtb_act = 0.0F;
  } else {
    /* '<S27>:1:7' */
    rtb_act = carmen_controller_DWork.CONTROL;
  }

  /* End of MATLAB Function: '<S2>/MATLAB Function' */

  /* MATLAB Function: '<S2>/MATLAB Function1' incorporates:
   *  DataStoreRead: '<S2>/Data Store Read2'
   */
  /* MATLAB Function 'PWM Output/MATLAB Function1': '<S28>:1' */
  if (carmen_controller_DWork.MEASUR_REAL > 75000) {
    /* '<S28>:1:4' */
    /* '<S28>:1:5' */
    rtb_act = 0.0F;
  } else {
    /* '<S28>:1:7' */
  }

  /* End of MATLAB Function: '<S2>/MATLAB Function1' */

  /* Saturate: '<S2>/Saturation1' */
  if (rtb_act >= carmen_controller_P.Saturation1_UpperSat) {
    carmen_controller_B.Saturation1 = carmen_controller_P.Saturation1_UpperSat;
  } else if (rtb_act <= carmen_controller_P.Saturation1_LowerSat) {
    carmen_controller_B.Saturation1 = carmen_controller_P.Saturation1_LowerSat;
  } else {
    carmen_controller_B.Saturation1 = rtb_act;
  }

  /* End of Saturate: '<S2>/Saturation1' */

  /* DataStoreWrite: '<S2>/Data Store Write1' */
  carmen_controller_DWork.PWM_OUT = carmen_controller_B.Saturation1;

  /* S-Function Block: <S2>/UC3M Basic PWM (stm32f4_basicpwm_fixed) */
  TIM2->CCR2 = (uint16_t) (carmen_controller_B.Saturation1 *
    PWMOutputUC3MBasicPWM_SF);
  if (carmen_controller_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function "USB VCP STM32F4 Rec" Output Block: <S3>/USB VCP Receiver STM32F4 */
    /* Move data from USB Rx buffer */
    VCP_Rx_valid_data = 0x01;
    if (Target_VCP_Rec_to_PC_BUF.header1!=0x0E) {
      VCP_Rx_valid_data = 0x00;
    }

    if (Target_VCP_Rec_to_PC_BUF.header2!=0x0E) {
      VCP_Rx_valid_data = 0x00;
    }

    if (Target_VCP_Rec_to_PC_BUF.terminator1!=0x0A) {
      VCP_Rx_valid_data = 0x00;
    }

    if (Target_VCP_Rec_to_PC_BUF.terminator2!=0x0A) {
      VCP_Rx_valid_data = 0x00;
    }

    if (VCP_Rx_valid_data == 0x01) {
      carmen_controller_B.USBVCPReceiverSTM32F4_o1=
        Target_VCP_Rec_to_PC_BUF.dat1;
      carmen_controller_B.USBVCPReceiverSTM32F4_o2=
        Target_VCP_Rec_to_PC_BUF.dat2;
      carmen_controller_B.USBVCPReceiverSTM32F4_o3=
        Target_VCP_Rec_to_PC_BUF.dat3;
    }

    /* DataStoreWrite: '<S3>/Data Store Write13' */
    carmen_controller_DWork.REF_AMPLITUDE =
      carmen_controller_B.USBVCPReceiverSTM32F4_o1;

    /* DataStoreWrite: '<S3>/Data Store Write2' */
    carmen_controller_DWork.CONTROL =
      carmen_controller_B.USBVCPReceiverSTM32F4_o2;

    /* DataStoreWrite: '<S3>/Data Store Write9' */
    carmen_controller_DWork.ENABLE_CONTROL =
      carmen_controller_B.USBVCPReceiverSTM32F4_o3;

    /* S-Function "USB VCP STM32F4 Send" Output Block: <S4>/USB VCP Send STM32F4 */
    /* Move data to USB Tx buffer */
    Target_VCP_Send_to_PC_BUF.dat1= carmen_controller_B.DataStoreRead6;
    Target_VCP_Send_to_PC_BUF.dat2= carmen_controller_B.DataTypeConversion;
    Target_VCP_Send_to_PC_BUF.dat3= carmen_controller_B.ManualSwitch1;
    Target_VCP_Send_to_PC_BUF.dat4= carmen_controller_B.ManualSwitch;
    Target_VCP_Send_to_PC_BUF_ptr_uint8 = (uint8_t *)
      Target_VCP_Send_to_PC_BUF_ptr;
    VCP_send(Target_VCP_Send_to_PC_BUF_ptr_uint8, UC3M_USBVCP_Send_Byte_Count);

    /* DataStoreRead: '<S4>/Data Store Read2' */
    rtb_DataStoreRead2 = carmen_controller_DWork.INTENSITY;

    /* DataStoreRead: '<S4>/Data Store Read3' */
    rtb_DataStoreRead3 = carmen_controller_DWork.TEMPERATURE;
  }

  /* DataStoreRead: '<S4>/Data Store Read6' */
  carmen_controller_B.DataStoreRead6 = carmen_controller_DWork.PWM_OUT;

  /* DataTypeConversion: '<S4>/Data Type Conversion' incorporates:
   *  DataStoreRead: '<S4>/Data Store Read1'
   */
  carmen_controller_B.DataTypeConversion = (real32_T)
    carmen_controller_DWork.MEASUR_REAL;
  if (carmen_controller_M->Timing.TaskCounters.TID[1] == 0) {
    /* ManualSwitch: '<S4>/Manual Switch' incorporates:
     *  Constant: '<S4>/Constant'
     */
    if (carmen_controller_P.ManualSwitch_CurrentSetting == 1) {
      carmen_controller_B.ManualSwitch = carmen_controller_P.Constant_Value;
    } else {
      carmen_controller_B.ManualSwitch = rtb_DataStoreRead3;
    }

    /* End of ManualSwitch: '<S4>/Manual Switch' */

    /* ManualSwitch: '<S4>/Manual Switch1' incorporates:
     *  Constant: '<S4>/Constant1'
     */
    if (carmen_controller_P.ManualSwitch1_CurrentSetting == 1) {
      carmen_controller_B.ManualSwitch1 = carmen_controller_P.Constant1_Value;
    } else {
      carmen_controller_B.ManualSwitch1 = rtb_DataStoreRead2;
    }

    /* End of ManualSwitch: '<S4>/Manual Switch1' */
  }

  rate_scheduler();
}

/* Model initialize function */
void carmen_controller_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)carmen_controller_M, 0,
                sizeof(RT_MODEL_carmen_controller));

  /* block I/O */
  (void) memset(((void *) &carmen_controller_B), 0,
                sizeof(BlockIO_carmen_controller));

  /* states (dwork) */
  (void) memset((void *)&carmen_controller_DWork, 0,
                sizeof(D_Work_carmen_controller));

  /* S-Function Block: <S8>/I2C Master Read//Write */
  enable_ControlLogicReadSensorSensorReadoutI2CMasterReadWrite();

  /* InitializeConditions for IfAction SubSystem: '<S10>/If Action Subsystem' */
  /* InitializeConditions for UnitDelay: '<S17>/UD' */
  carmen_controller_DWork.UD_DSTATE = carmen_controller_P.UD_InitialCondition;

  /* End of InitializeConditions for SubSystem: '<S10>/If Action Subsystem' */

  /* Start for DataStoreMemory: '<S6>/Data Store Memory' */
  carmen_controller_DWork.UPDATE_OFFSET =
    carmen_controller_P.DataStoreMemory_InitialValue;

  /* S-Function "USB VCP STM32F4 Send" Start Block: <S3>/USB VCP Receiver STM32F4 */
  /* Initialize the Data Rec Pointer */
  Target_VCP_Rec_to_PC_BUF_ptr= &Target_VCP_Rec_to_PC_BUF;
  Target_VCP_Rec_to_PC_BUF_ptr_uint8 = (uint8_t *) Target_VCP_Rec_to_PC_BUF_ptr;

  /* S-Function "USB VCP STM32F4 Send" Start Block: <S4>/USB VCP Send STM32F4 */
  /* Initialize Header Data */
  Target_VCP_Send_to_PC_BUF.header1= 0x0E;
  Target_VCP_Send_to_PC_BUF.header2= 0x0E;

  /* Initialize Terminator Data */
  Target_VCP_Send_to_PC_BUF.terminator1= 0x0A;
  Target_VCP_Send_to_PC_BUF.terminator2= 0x0A;

  /* Initialize the Data Send Pointer */
  Target_VCP_Send_to_PC_BUF_ptr= &Target_VCP_Send_to_PC_BUF;

  /* Initialize USB VCP Device */
  USBD_Init(&USB_OTG_dev,
            USB_OTG_FS_CORE_ID,
            &USR_desc,
            &USBD_CDC_cb,
            &USR_cb);

  /* Start for DataStoreMemory: '<Root>/Data Store Memory1' */
  carmen_controller_DWork.CONTROL =
    carmen_controller_P.DataStoreMemory1_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory11' */
  carmen_controller_DWork.REF_AMPLITUDE =
    carmen_controller_P.DataStoreMemory11_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory14' */
  carmen_controller_DWork.SENSOR_ERROR =
    carmen_controller_P.DataStoreMemory14_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory2' */
  carmen_controller_DWork.AUX =
    carmen_controller_P.DataStoreMemory2_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory24' */
  carmen_controller_DWork.ENABLE_CONTROL =
    carmen_controller_P.DataStoreMemory24_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory25' */
  carmen_controller_DWork.MEASUR_REAL =
    carmen_controller_P.DataStoreMemory25_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory3' */
  carmen_controller_DWork.MEASUR_CURR =
    carmen_controller_P.DataStoreMemory3_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory30' */
  carmen_controller_DWork.PWM_OUT =
    carmen_controller_P.DataStoreMemory30_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory4' */
  carmen_controller_DWork.INTENSITY =
    carmen_controller_P.DataStoreMemory4_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory5' */
  carmen_controller_DWork.STEPS =
    carmen_controller_P.DataStoreMemory5_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory6' */
  carmen_controller_DWork.TEMPERATURE =
    carmen_controller_P.DataStoreMemory6_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory7' */
  carmen_controller_DWork.OFFSET =
    carmen_controller_P.DataStoreMemory7_InitialValue;

  /* Start for DataStoreMemory: '<Root>/Data Store Memory9' */
  carmen_controller_DWork.MEASUR_PREV =
    carmen_controller_P.DataStoreMemory9_InitialValue;

  /* Level2 S-Function Block: '<S24>/Digital Output3' (stm32f4_digital_output) */
  enable_ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3();

  /* Level2 S-Function Block: '<Root>/I2C Master Setup1' (stm32f4_i2c) */
  enable_I2CMasterSetup1();

  /* Level2 S-Function Block: '<S2>/UC3M Basic PWM' (stm32f4_basicpwm_fixed) */
  enable_PWMOutputUC3MBasicPWM();
}

/* Model terminate function */
void carmen_controller_terminate(void)
{
  /* Terminate for S-Function (stm32f4_digital_output): '<S24>/Digital Output3' */

  /* terminate_ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3(); */

  /* Terminate for S-Function (stm32f4_i2c): '<S8>/I2C Master Read//Write' */

  /* terminate_ControlLogicReadSensorSensorReadoutI2CMasterReadWrite(); */

  /* Terminate for S-Function (stm32f4_i2c): '<Root>/I2C Master Setup1' */

  /* terminate_I2CMasterSetup1(); */

  /* Terminate for S-Function (stm32f4_basicpwm_fixed): '<S2>/UC3M Basic PWM' */

  /* terminate_PWMOutputUC3MBasicPWM(); */
}

/* [EOF] */
