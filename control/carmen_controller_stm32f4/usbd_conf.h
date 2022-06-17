/*
 * File: usbd_conf.h
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

#ifndef RTW_HEADER_usbd_conf_h_
#define RTW_HEADER_usbd_conf_h_

/**
 ******************************************************************************
 * @file    usbd_conf.h
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    22-July-2011
 * @brief   USB Device configuration file
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

/* Includes ------------------------------------------------------------------*/

/** @defgroup USB_CONF_Exported_Defines
 * @{
 */
#define USBD_CFG_MAX_NUM               1
#define USBD_ITF_MAX_NUM               1
#define USB_MAX_STR_DESC_SIZ           50

/** @defgroup USB_VCP_Class_Layer_Parameter
 * @{
 */
#define CDC_IN_EP                      0x81                      /* EP1 for data IN */
#define CDC_OUT_EP                     0x01                      /* EP1 for data OUT */
#define CDC_CMD_EP                     0x82                      /* EP2 for CDC commands */

/* CDC Endpoints parameters: you can fine tune these values depending on the needed baudrates and performance. */
#ifdef USE_USB_OTG_HS
#define CDC_DATA_MAX_PACKET_SIZE       512                       /* Endpoint IN & OUT Packet size */
#define CDC_CMD_PACKET_SZE             8                         /* Control Endpoint Packet size */
#define CDC_IN_FRAME_INTERVAL          40                        /* Number of micro-frames between IN transfers */
#define APP_RX_DATA_SIZE               2048                      /* Total size of IN buffer:
                                                                    APP_RX_DATA_SIZE*8/MAX_BAUDARATE*1000 should be > CDC_IN_FRAME_INTERVAL*8 */
#else
#define CDC_DATA_MAX_PACKET_SIZE       64                        /* 64 Endpoint IN & OUT Packet size */
#define CDC_CMD_PACKET_SZE             8                         /* Control Endpoint Packet size */
#define CDC_IN_FRAME_INTERVAL          5                         /* 5 Number of frames between IN transfers */
#define APP_RX_DATA_SIZE               2048                      /* Total size of IN buffer:
                                                                    APP_RX_DATA_SIZE*8/MAX_BAUDARATE*1000 should be > CDC_IN_FRAME_INTERVAL */
#endif                                 /* USE_USB_OTG_HS */

#define APP_FOPS                       VCP_fops

/**
 * @}
 */

/** @defgroup USB_CONF_Exported_Types
 * @{
 */
/**
 * @}
 */

/** @defgroup USB_CONF_Exported_Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup USB_CONF_Exported_Variables
 * @{
 */
/**
 * @}
 */

/** @defgroup USB_CONF_Exported_FunctionsPrototype
 * @{
 */
/**
 * @}
 */
#endif                                 //__USBD_CONF__H__

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
/**
 ******************************************************************************
 * @file    usbd_conf.h
 * @author  MCD Application Team
 * @version V1.0.0
 * @date    22-July-2011
 * @brief   USB Device configuration file
 ******************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

/* Includes ------------------------------------------------------------------*/

/** @defgroup USB_CONF_Exported_Defines
 * @{
 */
#define USBD_CFG_MAX_NUM               1
#define USBD_ITF_MAX_NUM               1
#define USB_MAX_STR_DESC_SIZ           50

/** @defgroup USB_VCP_Class_Layer_Parameter
 * @{
 */
#define CDC_IN_EP                      0x81                      /* EP1 for data IN */
#define CDC_OUT_EP                     0x01                      /* EP1 for data OUT */
#define CDC_CMD_EP                     0x82                      /* EP2 for CDC commands */

/* CDC Endpoints parameters: you can fine tune these values depending on the needed baudrates and performance. */
#ifdef USE_USB_OTG_HS
#define CDC_DATA_MAX_PACKET_SIZE       512                       /* Endpoint IN & OUT Packet size */
#define CDC_CMD_PACKET_SZE             8                         /* Control Endpoint Packet size */
#define CDC_IN_FRAME_INTERVAL          40                        /* Number of micro-frames between IN transfers */
#define APP_RX_DATA_SIZE               2048                      /* Total size of IN buffer:
                                                                    APP_RX_DATA_SIZE*8/MAX_BAUDARATE*1000 should be > CDC_IN_FRAME_INTERVAL*8 */
#else
#define CDC_DATA_MAX_PACKET_SIZE       64                        /* 64 Endpoint IN & OUT Packet size */
#define CDC_CMD_PACKET_SZE             8                         /* Control Endpoint Packet size */
#define CDC_IN_FRAME_INTERVAL          5                         /* 5 Number of frames between IN transfers */
#define APP_RX_DATA_SIZE               2048                      /* Total size of IN buffer:
                                                                    APP_RX_DATA_SIZE*8/MAX_BAUDARATE*1000 should be > CDC_IN_FRAME_INTERVAL */
#endif                                 /* USE_USB_OTG_HS */

#define APP_FOPS                       VCP_fops

/**
 * @}
 */

/** @defgroup USB_CONF_Exported_Types
 * @{
 */
/**
 * @}
 */

/** @defgroup USB_CONF_Exported_Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup USB_CONF_Exported_Variables
 * @{
 */
/**
 * @}
 */

/** @defgroup USB_CONF_Exported_FunctionsPrototype
 * @{
 */
/**
 * @}
 */
#endif                                 //__USBD_CONF__H__

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
#endif                                 /* RTW_HEADER_usbd_conf_h_ */

/* [EOF] */