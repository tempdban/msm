/*
 * fusb302 usb phy driver for type-c and PD
 *
 * Copyright (C) 2015, 2016 Fairchild Semiconductor Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Seee the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
/*
 * THIS FILE DEFINES EVERY PLATFORM-DEPENDENT ELEMENT THAT THE CORE REQUIRES.
 * 
 * INSTRUCTIONS FOR THIS FILE:
 * 1. Modify this file with a definition of Generic Type Definitions
 * (FSC_S8, FSC_U32, etc) Either by include or putting directly in this file.
 * 2. Include this as a header file for your platform.c and implement the 
 * function headers as defined below.
 * 
 * It is the driver-writer's responsibility to implement each function
 * stub and to allocate/initialize/reserve sufficient system resources.
 * 
 */
#ifndef _FSC_PLATFORM_H_
#define _FSC_PLATFORM_H_

/* PLATFORM_NONE
 * 
 * This is a set of stubs for no platform in particular.
 */
#ifdef PLATFORM_NONE
#include "../Platform_None/FSCTypes.h"
#endif // PLATFORM_NONE

/* PLATFORM_PIC32
 * 
 * This platform is for the Microchip PIC32 microcontroller.
 */
#ifdef PLATFORM_PIC32
#include "../Platform_PIC32/GenericTypeDefs.h"
#endif // PLATFORM_PIC32

/* PLATFORM_ARM
 *
 * This platform is for the ARM M0.
 */
#ifdef PLATFORM_ARM
#include "../Platform_ARM/app/FSCTypes.h"
#endif // PLATFORM_ARM

/* PLATFORM_ARM_M7
 *
 * This platform is for the ARM M7.
 */
#ifdef PLATFORM_ARM_M7
#include "../Platform_ARM_M7/app/FSCTypes.h"
#endif // PLATFORM_ARM_M7

/* FSC_PLATFORM_LINUX
 * 
 * This platform is for the Linux kernel driver.
 */
#ifdef FSC_PLATFORM_LINUX
#include "../Platform_Linux/FSCTypes.h"
#endif // FSC_PLATFORM_LINUX

#include "TypeC_Types.h"

typedef enum {
    VBUS_LVL_5V,
  /*VBUS_LVL_9V, */
    VBUS_LVL_12V,
  /*VBUS_LVL_15V,*/
  /*VBUS_LVL_20V,*/
    VBUS_LVL_COUNT,
    VBUS_LVL_ALL = 99
} VBUS_LVL;

typedef enum {
    NONE,
    CC1,
    CC2,
} CC_ORIENTATION;

typedef enum {
    SINK = 0,
    SOURCE
} SourceOrSink;

/*******************************************************************************
* Function:        platform_set/get_vbus_lvl_enable
* Input:           level - specify the vbus level
*                  blnEnable - enable or disable the specified vbus level
*                  blnDisableOthers - if true, ensure all other levels are off
* Return:          Boolean - State of vbus
* Description:     Provide access to the VBUS control pin(s).
******************************************************************************/
void platform_set_vbus_lvl_enable(VBUS_LVL level, FSC_BOOL blnEnable, FSC_BOOL blnDisableOthers);
FSC_BOOL platform_get_vbus_lvl_enable(VBUS_LVL level);

/*******************************************************************************
 * Function:        platform_set_vconn_enable
 * Input:           blnEnable - enable or disable VCONN
 * Return:          Boolean - State of VCONN GPIO
 * Description:     Provide access to the VCONN control pin(s).
 ******************************************************************************/
FSC_BOOL platform_set_vconn_enable(FSC_BOOL blnEnable);

/*******************************************************************************
 * Function:        platform_set_vbus_discharge
 * Input:           Boolean
 * Return:          None
 * Description:     Enable/Disable Vbus Discharge Path
 ******************************************************************************/
void platform_set_vbus_discharge(FSC_BOOL blnEnable);

/*******************************************************************************
 * Function:        platform_get_device_irq_state
 * Input:           None
 * Return:          Boolean.  TRUE = Interrupt Active
 * Description:     Get the state of the INT_N pin.  INT_N is active low.  This
 *                  function handles that by returning TRUE if the pin is
 *                  pulled low indicating an active interrupt signal.
 ******************************************************************************/
FSC_BOOL platform_get_device_irq_state( void );
        
/*******************************************************************************
 * Function:        platform_i2c_write
 * Input:           SlaveAddress - Slave device bus address
 *                  RegAddrLength - Register Address Byte Length
 *                  DataLength - Length of data to transmit
 *                  PacketSize - Maximum size of each transmitted packet
 *                  IncSize - Number of bytes to send before incrementing addr
 *                  RegisterAddress - Internal register address
 *                  Data - Buffer of char data to transmit
 * Return:          Error state
 * Description:     Write a char buffer to the I2C peripheral.
 ******************************************************************************/
FSC_BOOL platform_i2c_write(FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data);

/*******************************************************************************
 * Function:        platform_i2c_read
 * Input:           SlaveAddress - Slave device bus address
 *                  RegAddrLength - Register Address Byte Length
 *                  DataLength - Length of data to attempt to read
 *                  PacketSize - Maximum size of each received packet
 *                  IncSize - Number of bytes to recv before incrementing addr
 *                  RegisterAddress - Internal register address
 *                  Data - Buffer for received char data
 * Return:          Error state.
 * Description:     Read char data from the I2C peripheral.
 ******************************************************************************/
FSC_BOOL platform_i2c_read( FSC_U8 SlaveAddress,
                            FSC_U8 RegAddrLength,
                            FSC_U8 DataLength,
                            FSC_U8 PacketSize,
                            FSC_U8 IncSize,
                            FSC_U32 RegisterAddress,
                            FSC_U8* Data);

/*****************************************************************************
* Function:        platform_enable_timer
* Input:           enable - TRUE to enable platform timer, FALSE to disable
* Return:          None
* Description:     Enables or disables platform timer
******************************************************************************/
void platform_enable_timer(FSC_BOOL enable);

/******************************************************************************
 * Function:        platform_delay_10us
 * Input:           delayCount - Number of 10us delays to wait
 * Return:          None
 * Description:     Perform a blocking software delay in intervals of 10us
 ******************************************************************************/
void platform_delay_10us( FSC_U32 delayCount );

/*******************************************************************************
* Function:        platform_notify_cc_orientation
* Input:           orientation - Orientation of CC (NONE, CC1, CC2)
* Return:          None
* Description:     A callback used by the core to report to the platform the 
*                  current CC orientation. Called in SetStateAttached... and
*                  SetStateUnattached functions.                 
******************************************************************************/
void platform_notify_cc_orientation(CC_ORIENTATION orientation);

/*******************************************************************************
* Function:        platform_notify_pd_contract
* Input:           contract - TRUE: Contract, FALSE: No Contract
* Return:          None
* Description:     A callback used by the core to report to the platform the 
*                  current PD contract status. Called in PDPolicy.
*******************************************************************************/
void platform_notify_pd_contract(FSC_BOOL contract);

/*******************************************************************************
* Function:        platform_notify_unsupported_accessory
* Input:           None
* Return:          None
* Description:     A callback used by the core to report entry to the
*                  Unsupported Accessory state. The platform may implement
*                  USB Billboard.
*******************************************************************************/
void platform_notify_unsupported_accessory(void);

void platform_notify_attached_source(int value, bool connected);

int platform_set_sink_current_previous(CCTermType Termination);

#endif  // _FSC_PLATFORM_H_
