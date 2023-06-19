/*
 * File: waijung_hwdrvlib.c
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

#include "waijung_hwdrvlib.h"

/* ########################################################################
 * Timer
 * ########################################################################
 */

/* Low precision non-Blocking delay timer.
 ** Relolution of timer is one TICK step interrupt.
 */
void SysTimer_Start(SYS_TIMER_STRUCT* timer, uint32_t ms)
{
  /* Calculate amount of tick count */
  timer->length = (uint32_t)((float)ms/(1000*SYS_TICKSTEP));

  /* Capture current tick */
  timer->start = (uint32_t)systick_count;
}

int SysTimer_IsTimeout(SYS_TIMER_STRUCT* timer)
{
  uint32_t Capture;

  /* Capture current tick */
  Capture = (uint32_t)systick_count;

  /* Check */
  if (Capture >= timer->start) {
    if ((Capture - timer->start) >= timer->length)
      return 1;
  } else {
    if (((0xFFFFFFFF - timer->start)+Capture) >= timer->length)
      return 1;
  }

  return 0;
}

/* Improved precision non-Blocking delay timer.
 ** Relolution of timer is 1uS.
 */
void SysTimer_uS_Start(SYS_TIMER_uS_STRUCT *timer, uint32_t us)
{
  /* Tick */
  timer->tick = SYS_CURRENT_TICK;

  /* Tick overflow count */
  timer->tid = (uint32_t)systick_count;

  /* Target */
  timer->target_us = us*((uint32_t)HCLK/1000000);
}

int SysTimer_uS_IsTimeout(SYS_TIMER_uS_STRUCT* timer)
{
  uint32_t curr_tick;
  uint32_t curr_tid;

  /* Already timeout ? */
  if (timer->target_us == 0) {
    return 1;
  }

  /* Capture current tick */
  curr_tick = SYS_CURRENT_TICK;
  curr_tid = systick_count;

  /* Processing TID*/
  while (timer->tid != curr_tid) {
    if (timer->target_us > timer->tick) {
      timer->target_us -= timer->tick;
      timer->tid ++;
      timer->tick = SYSTICKRELOADVALUE-1;
    } else {
      timer->target_us = 0;
      return 1;                        /* Timeout */
    }
  }

  /* Processing Tick */
  if ((timer->tick > curr_tick) && ((timer->tick - curr_tick) > timer->target_us))
  {
    timer->target_us = 0;
    return 1;                          /* Timeout */
  }

  /* Need wait */
  return 0;
}

/* Blocking delay, uS */
void SysTimer_delay_us(uint32_t us)
{
  SYS_TIMER_uS_STRUCT timer;
  SysTimer_uS_Start(&timer, us);
  while (SysTimer_uS_IsTimeout(&timer) == 0) ;
}

/* Blocking delay, mS */
void SysTimer_delay_ms(uint32_t ms)
{
  SYS_TIMER_STRUCT timer;
  SysTimer_Start(&timer, ms);
  while (SysTimer_IsTimeout(&timer) == 0) ;
}

/* ########################################################################
 * Name: <S24>/Digital Output3
 * Id: ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3
 * ########################################################################
 */
uint16_t ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3_portVal;
void enable_ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

  /* Configure PA in output Push Pull mode for ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3 Block*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/* ########################################################################
 * I2C transaction processing
 * ########################################################################
 */
SYS_TIMER_uS_STRUCT i2c_processing_timer;
I2C_RESULT i2c_trans_proc(I2C_TypeDef* I2Cx, uint32_t timeout, I2C_TRANSACTION
  *transaction)
{
  volatile uint16_t tmp;
  uint16_t NumByteWritten;
  uint16_t NumByteToRead;
  uint16_t i;
  I2C_RESULT sta = I2C_OK;

  /* Enable Acknowledgement */
  I2C_AcknowledgeConfig(I2Cx, ENABLE);

  /* WRITE */
  if ((transaction->writecount > 0) || ((transaction->writecount == 0) &&
       (transaction->readcount == 0))) {
    /* Check Busy flag */
    SysTimer_uS_Start(&i2c_processing_timer, timeout);
    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY)) {
      if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {/* Timeout */
        sta = I2C_TIMEOUT;
        goto ____i2c_error;
      }
    }

    /* Clear I2C status */
    I2C_ClearFlag(I2Cx, I2C_FLAG_AF);

    /* Generate START */
    I2C_GenerateSTART(I2Cx, ENABLE);

    /* Test on EV5 and clear it */
    SysTimer_uS_Start(&i2c_processing_timer, timeout);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)) {
      if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {/* Timeout */
        sta = I2C_TIMEOUT;
        goto ____i2c_error;
      }
    }

    /* Slave address */
    I2C_Send7bitAddress(I2Cx, (transaction->slaveaddress),
                        I2C_Direction_Transmitter);

    /* Test on EV6 and clear it */
    SysTimer_uS_Start(&i2c_processing_timer, timeout);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
      if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {/* Timeout */
        sta = I2C_TIMEOUT;
        goto ____i2c_error;
      } else {
        if (I2C_GetFlagStatus(I2Cx, I2C_FLAG_AF) == SET) {
          sta = I2C_NAK;
          goto ____i2c_error;
        }
      }
    }

    /* Write data */
    for (NumByteWritten=0; NumByteWritten<transaction->writecount;
         NumByteWritten++) {
      /* Send byte */
      I2C_SendData(I2Cx, transaction->writebuffer[NumByteWritten]);

      /* Test on BTF and clear it */
      SysTimer_uS_Start(&i2c_processing_timer, timeout);
      while (!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF)) {
        if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {/* Timeout */
          sta = I2C_TIMEOUT;
          goto ____i2c_error;
        } else {
          if (I2C_GetFlagStatus(I2Cx, I2C_FLAG_AF) == SET) {
            sta = I2C_NAK;
            goto ____i2c_error;
          }
        }
      }
    }

    /* Wait till all data have been physically transferred on the bus */
    SysTimer_uS_Start(&i2c_processing_timer, timeout);
    while (!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF)
           && (SysTimer_uS_IsTimeout(&i2c_processing_timer) == 0)) {
      /* Do nothing */
    }

    /* Send STOP condition, if no Read */
    if ((transaction->readcount <= 0) || SysTimer_uS_IsTimeout
        (&i2c_processing_timer) || ((transaction->options &
          I2C_OPTION_STOPBEFORE_RESTART) > 0)) {
      I2C_GenerateSTOP(I2Cx, ENABLE);
    }

    /* Check timeout */
    if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
      sta = I2C_TIMEOUT;
      goto ____i2c_error;
    }

    /* Write delay */
    SysTimer_uS_Start(&i2c_processing_timer, transaction->waitwritetime);
    while (SysTimer_uS_IsTimeout(&i2c_processing_timer) == 0) ;
  }

  /* READ */
  if (transaction->readcount == 0) {
    /* Do nothing */
  } else {
    if (transaction->writecount == 0) {/* Bus will Busy if previous transactio is WRITE */
      /* Check Busy flag */
      SysTimer_uS_Start(&i2c_processing_timer, timeout);
      while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY)) {
        if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {/* Timeout */
          sta = I2C_TIMEOUT;
          goto ____i2c_error;
        }
      }
    }

    /* Clear I2C status */
    I2C_ClearFlag(I2Cx, I2C_FLAG_AF);

    /* Set POS bit if read count is 2 */
    if (transaction->readcount == 2) {
      I2Cx->CR1 |= 0x0800;
    }

    /* Generate START */
    I2C_GenerateSTART(I2Cx, ENABLE);

    /* Test on EV5 and clear it */
    SysTimer_uS_Start(&i2c_processing_timer, timeout);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)) {
      if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
        sta = I2C_TIMEOUT;
        goto ____i2c_error;
      }
    }

    /* Slave address */
    I2C_Send7bitAddress(I2Cx, (transaction->slaveaddress),
                        I2C_Direction_Receiver);

    /* Wait on ADDR flag to be set (ADDR is still not cleared at this level) */
    SysTimer_uS_Start(&i2c_processing_timer, timeout);
    while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_ADDR) == RESET) {
      if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
        sta = I2C_TIMEOUT;
        goto ____i2c_error;
      } else {
        if (I2C_GetFlagStatus(I2Cx, I2C_FLAG_AF) == SET) {
          I2C_GenerateSTOP(I2Cx, ENABLE);
          sta = I2C_NAK;
          goto ____i2c_error;
        }
      }
    }

    switch (transaction->readcount) {
      /* Read 1 byte */
     case 1:
      /* It is last byte, disable Acknowledgement */
      I2C_AcknowledgeConfig(I2Cx, DISABLE);

      /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
         software sequence must complete before the current byte end of transfer */
      __disable_irq();

      /* Clear ADDR register by reading SR1 then SR2 register (SR1 has already been read) */
      tmp = I2Cx->SR2;

      /* Send STOP Condition */
      I2C_GenerateSTOP(I2Cx, ENABLE);

      /* Re-enable IRQs */
      __enable_irq();

      /* Wait for the byte to be received */
      SysTimer_uS_Start(&i2c_processing_timer, timeout);
      while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_RXNE) == RESET) {
        if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
          sta = I2C_TIMEOUT;
          goto ____i2c_error;
        }
      }

      /* Read the byte received from the Slave */
      transaction->readbuffer[0] = I2C_ReceiveData(I2Cx);

      /* Wait to make sure that STOP control bit has been cleared */
      SysTimer_uS_Start(&i2c_processing_timer, timeout);
      while (I2Cx->CR1 & I2C_CR1_STOP) {
        if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
          sta = I2C_TIMEOUT;
          goto ____i2c_error;
        }
      }
      break;

      /* Read 2 bytes */
     case 2:
      /* EV6_1: The acknowledge disable should be done just after EV6,
         that is after ADDR is cleared, so disable all active IRQs around ADDR clearing and
         ACK clearing */
      __disable_irq();

      /* Clear ADDR by reading SR2 register  */
      tmp = I2Cx->SR2;

      /* Clear ACK */
      I2C_AcknowledgeConfig(I2Cx, DISABLE);

      /*Re-enable IRQs */
      __enable_irq();

      /* Test on BTF and clear it */
      SysTimer_uS_Start(&i2c_processing_timer, timeout);
      while (!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF)) {
        if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
          sta = I2C_TIMEOUT;
          goto ____i2c_error;
        }
      }

      /* Disable IRQs around STOP programming and data reading because of the limitation ?*/
      __disable_irq();

      /* Program the STOP */
      I2C_GenerateSTOP(I2Cx, ENABLE);

      /* Read first data */
      transaction->readbuffer[0] = I2Cx->DR;

      /* Re-enable IRQs */
      __enable_irq();

      /* Read second data */
      transaction->readbuffer[1] = I2Cx->DR;

      /* Wait to make sure that STOP control bit has been cleared */
      SysTimer_uS_Start(&i2c_processing_timer, timeout);
      while (I2Cx->CR1 & I2C_CR1_STOP) {
        if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
          sta = I2C_TIMEOUT;
          goto ____i2c_error;
        }
      }

      /* Enable Acknowledgement to be ready for another reception */
      I2C_AcknowledgeConfig(I2Cx, ENABLE);

      /* Clear POS bit */
      I2Cx->CR1 &= 0xF7FF;
      break;

      /* Read more than 2 bytes */
     default:
      /* Clear ADDR by reading SR2 status register */
      tmp = I2Cx->SR2;

      /* While there is data to be read */
      NumByteToRead = transaction->readcount;
      i = 0;
      while (NumByteToRead > 0) {
        /* Poll on BTF to receive data because in polling mode we can not guarantee the
           EV7 software sequence is managed before the current byte transfer completes */
        SysTimer_uS_Start(&i2c_processing_timer, timeout);
        while (!I2C_GetFlagStatus(I2Cx, I2C_FLAG_BTF)) {
          if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
            sta = I2C_TIMEOUT;
            goto ____i2c_error;
          }
        }

        /* Receive bytes from first byte until byte N-3 */
        if (NumByteToRead != 3) {
          /* Read data */
          transaction->readbuffer[i] = I2Cx->DR;

          /* */
          i++;

          /* Decrement the read bytes counter */
          NumByteToRead--;
        } else {                       /* it remains to read three data: data N-2, data N-1, Data N */
          /* Clear ACK */
          I2C_AcknowledgeConfig(I2Cx, DISABLE);

          /* Disable IRQs around data reading and STOP programming because of the limitation ? */
          __disable_irq();

          /* Read Data N-2 */
          transaction->readbuffer[i] = I2Cx->DR;

          /* Increment */
          i++;

          /* Program the STOP */
          I2C_GenerateSTOP(I2Cx, ENABLE);

          /* Read DataN-1 */
          transaction->readbuffer[i] = I2Cx->DR;

          /* Re-enable IRQs */
          __enable_irq();

          /* Increment */
          i++;

          /* Wait until RXNE is set (DR contains the last data) */
          SysTimer_uS_Start(&i2c_processing_timer, timeout);
          while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_RXNE) == RESET) {
            if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
              sta = I2C_TIMEOUT;
              goto ____i2c_error;
            }
          }

          /* Read DataN */
          transaction->readbuffer[i] = I2Cx->DR;

          /* Reset the number of bytes to be read by master */
          NumByteToRead = 0;
        }
      }

      /* Wait to make sure that STOP control bit has been cleared */
      SysTimer_uS_Start(&i2c_processing_timer, timeout);
      while (I2Cx->CR1 & I2C_CR1_STOP) {
        if (SysTimer_uS_IsTimeout(&i2c_processing_timer)) {
          sta = I2C_TIMEOUT;
          goto ____i2c_error;
        }
      }

      /* Enable Acknowledgement to be ready for another reception */
      I2C_AcknowledgeConfig(I2Cx, ENABLE);
      break;
    }
  }

  /* No Error */
  return I2C_OK;

  /* Error */
 ____i2c_error:
  /* Generate STOP */
  I2C_GenerateSTOP(I2Cx, ENABLE);

  /* Wait to make sure that STOP control bit has been cleared */
  SysTimer_uS_Start(&i2c_processing_timer, timeout);
  while ((I2Cx->CR1 & I2C_CR1_STOP) && (SysTimer_uS_IsTimeout
          (&i2c_processing_timer) == 0)) ;

  /* Return fail status */
  return sta;
}

/* ########################################################################
 * Name: <S8>/I2C Master Read//Write
 * Id: ControlLogicReadSensorSensorReadoutI2CMasterReadWrite
 * (I2CMasterReadWrite)
 * ########################################################################
 */
I2C_TRANSACTION I2CMasterReadWrite;
uint8_t I2CMasterReadWrite_RBuffer[2];

/* Enable module */
void enable_ControlLogicReadSensorSensorReadoutI2CMasterReadWrite(void)
{
  I2CMasterReadWrite.options = 0;
  I2CMasterReadWrite.writecount = 0;
  I2CMasterReadWrite.writebuffer = (uint8_t*)0;
  I2CMasterReadWrite.readcount = 2;
  I2CMasterReadWrite.readbuffer = I2CMasterReadWrite_RBuffer;
  I2CMasterReadWrite.waitwritetime = 0*1000UL;/* uS */
}

/* ########################################################################
 * Name: <Root>/I2C Master Setup1
 * Id: I2CMasterSetup1
 * (I2CMasterSetup1)
 * ########################################################################
 */
I2C_RESULT i2c1_trans_proc(uint8_t slaveaddress, I2C_TRANSACTION *transaction)
{
  uint8_t i;
  I2C_RESULT res;

  /* Update Slave address */
  transaction->slaveaddress = slaveaddress;

  /* Transaction processing */
  if ((res = i2c_trans_proc(I2C1, I2C1_TIMEOUT_uS, transaction)) != I2C_OK) {
    /* Temporary disable module to reset I2C */
    disable_I2CMasterSetup1();

    /* Detect if Slave hold low SDA line (this cause stuck on I2C bus),
     ** use GPIO toggle to generate clock on SCL line until slave release SDA.
     */
    i = 0;
    while ((i++<16) && (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == Bit_RESET))
    {
      GPIO_ResetBits(GPIOB, GPIO_Pin_8);
      SysTimer_delay_us(5);            /* 5uS */
      GPIO_SetBits(GPIOB, GPIO_Pin_8);
      SysTimer_delay_us(4);            /* 4uS */
    }

    /* Re-enable I2C */
    enable_I2CMasterSetup1();
  }

  return res;
}

/* Enable module */
void enable_I2CMasterSetup1(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  I2C_InitTypeDef I2C_InitStructure;

  /* I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

  /* I2C_SCL_GPIO_CLK and I2C_SDA_GPIO_CLK Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Reset I2C IP */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);

  /* Release reset signal of I2C IP */
  RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);

  /* GPIO configuration */
  /* Connect PB8 to I2C_SCL*/
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);

  /* Connect PB9 to I2C_SDA*/
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);

  /* Configure I2C pins: SCL */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure sEE_I2C pins: SDA */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0xA0;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = 600000;/* 600kHz */

  /* I2C Peripheral Enable */
  I2C_Cmd(I2C1, ENABLE);

  /* Apply I2C1 configuration after enabling it */
  I2C_Init(I2C1, &I2C_InitStructure);
}

/* Disable module */
void disable_I2CMasterSetup1(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* I2C Peripheral Disable */
  I2C_Cmd(I2C1, DISABLE);

  /* I2C DeInit */
  I2C_DeInit(I2C1);

  /* I2C Periph clock disable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, DISABLE);

  /* GPIO configuration */
  /* Configure I2C pins: SCL */
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_SetBits(GPIOB, GPIO_Pin_8);
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure I2C pins: SDA */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void enable_PWMOutputUC3MBasicPWM(void)
{
  /* Block: PWMOutputUC3MBasicPWM */
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* GPIOB clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  /* GPIOB configuration */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Connect TIM2 pins to AF */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

  /* Time base configuration */
  // 0.001 sec , 1.0 Khz
  TIM_TimeBaseStructure.TIM_Period = 21000 ;

  //Timer Clock is configured to run at 21 Mhz, Sr Antonio
  //Only if HCLK = 168 Mhz !
  TIM_TimeBaseStructure.TIM_Prescaler = 3;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  /* PWM1 Mode configuration: Channel 2 */
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* TIM2 configure auto reload */
  TIM_ARRPreloadConfig(TIM2, ENABLE);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}

void disable_PWMOutputUC3MBasicPWM(void)
{
  TIM_Cmd(TIM2, DISABLE);
}

void terminate_PWMOutputUC3MBasicPWM(void)
{
  TIM_Cmd(TIM2, DISABLE);
}

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ )             /*!< IAR Compiler */

#pragma data_alignment = 4

#endif
#endif                                 /* USB_OTG_HS_INTERNAL_DMA_ENABLED */

__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

/* Data buffer for USB VCP RX */
__ALIGN_BEGIN Target_VCP_Rec_to_PC_BUF_PktType Target_VCP_Rec_to_PC_BUF
  __ALIGN_END __attribute__ ((section(".ccm")));
__ALIGN_BEGIN Target_VCP_Rec_to_PC_BUF_PktType * Target_VCP_Rec_to_PC_BUF_ptr
  __ALIGN_END;
uint8_t * Target_VCP_Rec_to_PC_BUF_ptr_uint8;
uint16_t vcpoutcnt;
uint8_t VCP_Rx_valid_data;             //Sr Antonio, in order to check header and terminator received data
uint16_t VCP_Rx_vector;                //Dr Antonio, Vector Support

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
#if defined ( __ICCARM__ )             /*!< IAR Compiler */

#pragma data_alignment = 4

#endif
#endif                                 /* USB_OTG_HS_INTERNAL_DMA_ENABLED */

__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

/* Data buffer for USB VCP TX */
__ALIGN_BEGIN Target_VCP_Send_to_PC_BUF_PktType Target_VCP_Send_to_PC_BUF
  __ALIGN_END __attribute__ ((section(".ccm")));
__ALIGN_BEGIN Target_VCP_Send_to_PC_BUF_PktType * Target_VCP_Send_to_PC_BUF_ptr
  __ALIGN_END;
uint8_t * Target_VCP_Send_to_PC_BUF_ptr_uint8;
uint16_t vcpincnt;
uint16_t VCP_Tx_vector;                //Dr Antonio, Vector Support

/* [EOF] */
