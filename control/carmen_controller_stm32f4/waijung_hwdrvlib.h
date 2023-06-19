/*
 * File: waijung_hwdrvlib.h
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

#ifndef RTW_HEADER_waijung_hwdrvlib_h_
#define RTW_HEADER_waijung_hwdrvlib_h_
#define USB_VCP_STM32F4_REC
#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "usb_conf.h"
#include "carmen_controller.h"         //Sr Antonio v1.5
#define USB_VCP_STM32F4_CONFIGURED

//#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
//        #if defined ( __ICCARM__ ) /*!< IAR Compiler */
//            #pragma data_alignment = 4
//            #pragma pack(4)
//         #endif
//#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
//#if defined   (__CC_ARM)      /* ARM Compiler */
//      #pragma pack(4)
//#elif defined (__ICCARM__)    /* IAR Compiler */
//      #pragma data_alignment=4
//      #pragma pack(4)
//#endif
#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "usb_conf.h"
#include "carmen_controller.h"         //Sr Antonio v1.5
#define USB_VCP_STM32F4_CONFIGURED

//#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
//        #if defined ( __ICCARM__ ) /*!< IAR Compiler */
//            #pragma data_alignment = 4
//            #pragma pack(4)
//         #endif
//#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */
//#if defined   (__CC_ARM)      /* ARM Compiler */
//      #pragma pack(4)
//#elif defined (__ICCARM__)    /* IAR Compiler */
//      #pragma data_alignment=4
//      #pragma pack(4)
//#endif
#include "rtwtypes.h"
#include "stm32f4xx.h"

/*
 * Bit banding
 *
 * The Cortex memory map includes two bit-band regions.
 * These regions map each word in an alias region of memory to a bit in
 * a bit-band region of memory. Writing to a word in the alias region
 * has the same effect as a read-modify-write operation on the targeted bit
 * in the bit-band region.
 *
 * In the STM32F4xxx both peripheral registers and SRAM are mapped in
 * a bit-band region. This allows single bit-band write and read operations
 * to be performed.
 *
 * A mapping formula shows how to reference each word in the alias region
 * to a corresponding bit in the bit-band region. The mapping formula is:
 * bit_word_addr = bit_band_base + (byte_offset x 32) + (bit_number × 4)
 *
 * BB_base      is the base address of the bit-band region for a register. (PERIPH_BB_BASE at 0x42000000 or SRAM_BB_BASE at 0x22000000)
 * Reg_base     is the base address of a register in the memory region. (PERIPH_BASE at 0x40000000 or SRAM_BASE at 0x20000000)
 * Register     is a register in the memory region that contains the targeted bit.
 * Bit_number   is the targeted bit number (0 - 31).
 *
 * PERIPH_BB_BASE, SRAM_BB_BASE, PERIPH_BASE, and SRAM_BASE are defined in stm32f10x.h
 *
 * Example for determining bit banding bit.
 * Determine DMA Transfer Complete Flag using bit banding.
 * TCIFx is the flag for DMA Channel x
 * This bit is set by hardware. It is cleared by software writing 1 to
 * the corresponding bit in the DMA_IFCR register.
 * TCIFx = 0: No transfer complete (TC) event on channel x
 * TCIFx = 1: A transfer complete (TC) event occurred on channel x
 *
 * DMA Channel:       1 2 3  4  5  6  7
 * Flag bit position: 1 5 9 13 17 21 25 (in DMA_ISR register)
 * (For DMA2 Channel 6 and 7 is irrelevant since it only has 5 channels.)
 *
 * CTCIFx: Channel x transfer complete clear (x = 1 ..7)
 * This bit is set and cleared by software.
 * CTCIFx = 0: No effect
 * CTCIFx = 1: Clear the corresponding TCIF flag in the DMA_ISR register
 *
 */
#define BitBanding(Register, Bit_number, Reg_base, BB_base) ((volatile uint32_t*) ((BB_base) + (((uint32_t) &(Register)) - ((Reg_base))<<5) + ((Bit_number)<<2)))
#define Peripheral_BB(Register, Bit_number) BitBanding(Register, Bit_number, PERIPH_BASE, PERIPH_BB_BASE)
#define SRAM_BB(Register, Bit_number)  BitBanding(Register, Bit_number, SRAM_BASE, SRAM_BB_BASE)

/*
 * Sample usage:
 * USART1->SR can be found from "stm32f4xx.h" and USART_FLAG_TC (6) can be found from "stm32f4xx_usart.h"
 * #define USART1_TC Peripheral_BB(USART1->SR, 6) USART_SR.TC bit
 *
 * Another example:
 * #define GPIOC_8 Peripheral_BB(GPIOC->ODR, 8)
 * *GPIOC_8 = 1;
 */

/*
 * Systick is configured such that the SysTick interrupt every 0.002 sec
 * which is the base sample time of the system.
 */
#define SYSTICKRELOADVALUE             336000

/*
 * HCLK (Hz)
 */
#define HCLK                           168000000

/*
 * Each Systick counter is TIMEPERSYSTICK sec.
 */
#define TIMEPERSYSTICK                 0.002 / 336000

/* ########################################################################
 * Name: <S24>/Digital Output3
 * Id: ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3
 * ########################################################################
 */
#define ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3_A4 Peripheral_BB(GPIOA->ODR, 4) /* Output pin */
#define ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3_A5 Peripheral_BB(GPIOA->ODR, 5) /* Output pin */
#define ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3_A6 Peripheral_BB(GPIOA->ODR, 6) /* Output pin */

/*
 * Define PWM Generation Scale Factor, Sr Antonio fixed it
 * TIMx_CCRx = (desired percentage  * TIMx_SF)
 * TIMx_SF = (TIM.PERIOD + 1) / 100.0
 */
#define PWMOutputUC3MBasicPWM_SF       (float) ((21000 + 1) / 100.0)

extern volatile unsigned int systick_count;

/* ########################################################################
 * Timer
 * ########################################################################
 */
#define SYS_CURRENT_TICK               (SysTick->VAL)
#define SYS_TICKSTEP                   0.002f

typedef struct {
  uint32_t start;
  uint32_t length;
} SYS_TIMER_STRUCT;

#define SYSTIMER_FLAGS_TIMEOUT         0x01

typedef struct {
  uint8_t flags;
  uint32_t tid;                        /* Tick count */
  uint32_t tick;                       /* Capture cuttent tick */
  uint32_t target_us;                  /* Target of systick */
} SYS_TIMER_uS_STRUCT;

extern volatile unsigned int systick_count;
void SysTimer_Start(SYS_TIMER_STRUCT* timer, uint32_t ms);
void SysTimer_uS_Start(SYS_TIMER_uS_STRUCT *timer, uint32_t us);
int SysTimer_IsTimeout(SYS_TIMER_STRUCT* timer);
int SysTimer_uS_IsTimeout(SYS_TIMER_uS_STRUCT* timer);
void SysTimer_delay_us(uint32_t us);

/* ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3 */
void enable_ControlLogicReadSensorSensorReadoutSelectSensorDigitalOutput3(void);

/* ########################################################################
 * I2C transaction processing
 * ########################################################################
 */
typedef enum {
  I2C_OK = 0,
  I2C_TIMEOUT,
  I2C_NAK                              /* No ACK from device */
} I2C_RESULT;

#define I2C_OPTION_STOPBEFORE_RESTART  0x01

typedef struct {
  uint8_t options;
  uint8_t slaveaddress;
  uint8_t *readbuffer;
  uint8_t *writebuffer;
  uint16_t writecount;
  uint16_t readcount;
  uint32_t waitwritetime;              /* us */
} I2C_TRANSACTION;

I2C_RESULT i2c_trans_proc(I2C_TypeDef* I2Cx, uint32_t timeout, I2C_TRANSACTION
  *transaction);

/* ************************************************************************
 ** Name: <S8>/I2C Master Read//Write
 ** Id: ControlLogicReadSensorSensorReadoutI2CMasterReadWrite
 ** ************************************************************************
 */
extern I2C_TRANSACTION I2CMasterReadWrite;
extern uint8_t I2CMasterReadWrite_RBuffer[];
void enable_ControlLogicReadSensorSensorReadoutI2CMasterReadWrite(void);

/* ************************************************************************
 ** Name: <Root>/I2C Master Setup1
 ** Id: I2CMasterSetup1
 ** ************************************************************************
 */
#define I2C1_TIMEOUT_uS                1000                      /* Timeout, uS */
#define I2C1_TRANSACTION(t)            (i2c1_trans_proc(t))

I2C_RESULT i2c1_trans_proc(uint8_t slaveaddress, I2C_TRANSACTION *transaction);
void enable_I2CMasterSetup1(void);
void disable_I2CMasterSetup1(void);
void enable_PWMOutputUC3MBasicPWM(void);/* PWMOutputUC3MBasicPWM */

/* S-Function "USB VCP STM32F4 Rec" declarations Block: <S3>/USB VCP Receiver STM32F4 */
extern USB_OTG_CORE_HANDLE USB_OTG_dev;//extern

/* Define packet typedef for "USB VCP STM32F4 Rec", Block: <S3>/USB VCP Receiver STM32F4 */
/* Binary Mode */
__packed typedef struct Target_VCP_Rec_to_PC_BUF_Pkt {
  uint8_t header1;
  uint8_t header2;
  float dat1;
  float dat2;
  uint8_t dat3;
  uint8_t terminator1;
  uint8_t terminator2;
} Target_VCP_Rec_to_PC_BUF_PktType;

/* Data buffer for USB VCP RX */
extern Target_VCP_Rec_to_PC_BUF_PktType Target_VCP_Rec_to_PC_BUF __attribute__
  ((section(".ccm")));
extern Target_VCP_Rec_to_PC_BUF_PktType * Target_VCP_Rec_to_PC_BUF_ptr;
extern uint8_t * Target_VCP_Rec_to_PC_BUF_ptr_uint8;
extern uint16_t vcpoutcnt;
extern uint8_t VCP_Rx_valid_data;
extern uint16_t VCP_Rx_vector;

#define UC3M_USBVCP_Rec_Byte_Count     13

/* S-Function "USB VCP STM32F4 Send" declarations Block: <S4>/USB VCP Send STM32F4 */
extern USB_OTG_CORE_HANDLE USB_OTG_dev;//extern

/* Define packet typedef for "USB VCP STM32F4 Send", Block: <S4>/USB VCP Send STM32F4 */
/* Binary Mode */
__packed typedef struct Target_VCP_Send_to_PC_BUF_Pkt {
  uint8_t header1;
  uint8_t header2;
  float dat1;
  float dat2;
  float dat3;
  float dat4;
  uint8_t terminator1;
  uint8_t terminator2;
} Target_VCP_Send_to_PC_BUF_PktType;

/* Data buffer for USB VCP TX */
extern Target_VCP_Send_to_PC_BUF_PktType Target_VCP_Send_to_PC_BUF __attribute__
  ((section(".ccm")));
extern Target_VCP_Send_to_PC_BUF_PktType * Target_VCP_Send_to_PC_BUF_ptr;
extern uint8_t * Target_VCP_Send_to_PC_BUF_ptr_uint8;
extern uint16_t vcpincnt;
extern uint16_t VCP_Tx_vector;

#define UC3M_USBVCP_Send_Byte_Count    20
#endif                                 /* RTW_HEADER_waijung_hwdrvlib_h_ */

/* [EOF] */
