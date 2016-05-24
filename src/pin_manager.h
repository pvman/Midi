/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB� Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25.2
        Device            :  PIC16F1459
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SDI aliases
#define SDI_TRIS               TRISBbits.TRISB4
#define SDI_LAT                LATBbits.LATB4
#define SDI_PORT               PORTBbits.RB4
#define SDI_WPU                 WPUBbits.WPUB4
#define SDI_ANS                ANSELBbits.ANSB4 
#define SDI_SetHigh()    do { SDI_LAT  = 1; } while(0)
#define SDI_SetLow()   do { SDI_LAT  = 0; } while(0)
#define SDI_Toggle()   do { SDI_LAT  = ~SDI_LAT ; } while(0)
#define SDI_GetValue()         SDI_PORT
#define SDI_SetDigitalInput()    do { SDI_TRIS = 1; } while(0)
#define SDI_SetDigitalOutput()   do { SDI_TRIS = 0; } while(0)

#define SDI_SetPullup()    do { SDI_WPU = 1; } while(0)
#define SDI_ResetPullup()   do { SDI_WPU = 0; } while(0)
#define SDI_SetAnalogMode()   do { SDI_ANS = 1; } while(0)
#define SDI_SetDigitalMode()   do { SDI_ANS = 0; } while(0)
// get/set SPI_SS aliases
#define SPI_SS_TRIS               TRISBbits.TRISB5
#define SPI_SS_LAT                LATBbits.LATB5
#define SPI_SS_PORT               PORTBbits.RB5
#define SPI_SS_ANS                ANSELBbits.ANSB5
#define SPI_SS_SetHigh()    do { SPI_SS_LAT = 1; } while(0)
#define SPI_SS_SetLow()   do { SPI_SS_LAT = 0; } while(0)
#define SPI_SS_Toggle()   do { SPI_SS_LAT = ~SPI_SS_LAT; } while(0)
#define SPI_SS_GetValue()         SPI_SS_PORT
#define SPI_SS_SetDigitalInput()    do { SPI_SS_TRIS = 1; } while(0)
#define SPI_SS_SetDigitalOutput()   do { SPI_SS_TRIS = 0; } while(0)

#define SPI_SS_SetAnalogMode()   do { SPI_SS_ANS = 1; } while(0)
#define SPI_SS_SetDigitalMode()   do { SPI_SS_ANS = 0; } while(0)
// get/set SCK aliases
#define SCK_TRIS               TRISBbits.TRISB6
#define SCK_LAT                LATBbits.LATB6
#define SCK_PORT               PORTBbits.RB6
#define SCK_WPU                WPUBbits.WPUB6
#define SCK_SetHigh()    do { SCK_LAT = 1; } while(0)
#define SCK_SetLow()   do { SCK_LAT = 0; } while(0)
#define SCK_Toggle()   do { SCK_LAT = ~SCK_LAT; } while(0)
#define SCK_GetValue()         SCK_PORT
#define SCK_SetDigitalInput()    do { SCK_TRIS = 1; } while(0)
#define SCK_SetDigitalOutput()   do { SCK_TRIS = 0; } while(0)

#define SCK_SetPullup()    do { SCK_WPU = 1; } while(0)
#define SCK_ResetPullup()   do { SCK_WPU = 0; } while(0)
// get/set BLE_IRQ aliases
#define BLE_IRQ_TRIS               TRISBbits.TRISB7
#define BLE_IRQ_LAT                LATBbits.LATB7
#define BLE_IRQ_PORT               PORTBbits.RB7
#define BLE_IRQ_WPU                WPUBbits.WPUB7
#define BLE_IRQ_SetHigh()    do { BLE_IRQ_LAT = 1; } while(0)
#define BLE_IRQ_SetLow()   do { BLE_IRQ_LAT = 0; } while(0)
#define BLE_IRQ_Toggle()   do { BLE_IRQ_LAT = ~BLE_IRQ_LAT; } while(0)
#define BLE_IRQ_GetValue()         BLE_IRQ_PORT
#define BLE_IRQ_SetDigitalInput()    do { BLE_IRQ_TRIS = 1; } while(0)
#define BLE_IRQ_SetDigitalOutput()   do { BLE_IRQ_TRIS = 0; } while(0)

#define BLE_IRQ_SetPullup()    do { BLE_IRQ_WPU = 1; } while(0)
#define BLE_IRQ_ResetPullup()   do { BLE_IRQ_WPU = 0; } while(0)
// get/set LED aliases
#define LED_TRIS               TRISCbits.TRISC2
#define LED_LAT                LATCbits.LATC2
#define LED_PORT               PORTCbits.RC2
#define LED_ANS                ANSELCbits.ANSC2
#define LED_SetHigh()    do { LED_LAT = 1; } while(0)
#define LED_SetLow()   do { LED_LAT = 0; } while(0)
#define LED_Toggle()   do { LED_LAT = ~LED_LAT; } while(0)
#define LED_GetValue()         LED_PORT
#define LED_SetDigitalInput()    do { LED_TRIS = 1; } while(0)
#define LED_SetDigitalOutput()   do { LED_TRIS = 0; } while(0)

#define LED_SetAnalogMode()   do { LED_ANS = 1; } while(0)
#define LED_SetDigitalMode()   do { LED_ANS = 0; } while(0)
// get/set SDO aliases
#define SDO_TRIS               TRISCbits.TRISC7
#define SDO_LAT                LATCbits.LATC7
#define SDO_PORT               PORTCbits.RC7
#define SDO_ANS                ANSELCbits.ANSC7
#define SDO_SetHigh()    do { SDO_LAT = 1; } while(0)
#define SDO_SetLow()   do { SDO_LAT = 0; } while(0)
#define SDO_Toggle()   do { SDO_LAT = ~SDO_LAT; } while(0)
#define SDO_GetValue()         SDO_PORT.RC7
#define SDO_SetDigitalInput()    do { SDO_TRIS = 1; } while(0)
#define SDO_SetDigitalOutput()   do { SDO_TRIS = 0; } while(0)

#define SDO_SetAnalogMode()   do { SDO_ANS = 1; } while(0)
#define SDO_SetDigitalMode()   do { SDO_ANS = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */