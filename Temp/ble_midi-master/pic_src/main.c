/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1459
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"

void LedFlash(void) {
    LED_SetHigh();
    __delay_ms(30);
    LED_SetLow();
    __delay_ms(20);
    LED_SetHigh();
    __delay_ms(30);
    LED_SetLow();
}

void SendMidiData(uint8_t tone, uint8_t velocity) {

    volatile uint8_t timeout_ms = 10;
    /* copy data */

    if (SPI_HasReceiveOverflowOccured()) {
        SPI_ClearReceiveOverflowStatus();
    }

    if (SPI_HasWriteCollisionOccured()) {
        SPI_ClearWriteCollisionStatus();
    }

    /* generate event */
    BLE_IRQ_SetHigh();
    BLE_IRQ_SetLow();

    while ((SPI_SS_GetValue() != 0) && (timeout_ms > 0)) {
        //__delay_ms(1);
        //--timeout_ms;
    }

    if (SPI_SS_GetValue() == 0) {
        //SPI_Exchange8bitBuffer(_tx_buff, DATA_BUFF_LEN, NULL);
        SPI_Exchange8bit(tone);
        SPI_Exchange8bit(velocity);
        SPI_Exchange8bit(0xAA);
    }

}
#define FSH_4 66
#define A_4 69
#define B_4 71
#define E_4 64
#define CSH_5 73
#define D_5 74
#define FSH_5 78
#define CSH_4 61
#define GSH_4 68    

#define REST  0

void PlayWrap(uint8_t tone, uint8_t velocity) {

    SendMidiData(tone, velocity);

    for (int i = 0; i < velocity * 7; i++)
        __delay_ms(1);

    LedFlash();
}

void PlayAlexF() {

    while (1) {
        // Axel F
        PlayWrap(FSH_4, 20);
        PlayWrap(REST, 0);
        PlayWrap(A_4, 30);
        PlayWrap(FSH_4, 20);
        PlayWrap(FSH_4, 10);
        PlayWrap(B_4, 20);
        PlayWrap(FSH_4, 20);
        PlayWrap(E_4, 20);
        PlayWrap(FSH_4, 20);
        PlayWrap(REST, 0);
        PlayWrap(CSH_5, 30);
        PlayWrap(FSH_4, 20);
        PlayWrap(FSH_4, 10);
        PlayWrap(D_5, 20);
        PlayWrap(CSH_5, 20);
        PlayWrap(A_4, 20);
        PlayWrap(FSH_4, 20);
        PlayWrap(CSH_5, 20);
        PlayWrap(FSH_5, 20);
        PlayWrap(FSH_4, 10);
        PlayWrap(E_4, 20);
        PlayWrap(E_4, 10);
        PlayWrap(CSH_4, 20);
        PlayWrap(GSH_4, 20);
        PlayWrap(FSH_4, 60);
        PlayWrap(REST, 0);
        __delay_ms(2000);
    }
}

/*
                         Main application
 */
void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    __delay_ms(5000);

    uint8_t tone = 36;

    PlayAlexF();
    
    while (1) {


        SendMidiData(tone, 1);
        LedFlash();

        if (tone != 0x45) {
            tone = 0x45;
        } else {
            tone = 0x60;
        }

        if (++tone > 84) {
            tone = 36;
        }

        __delay_ms(100);
    }
}
/**
 End of File
 */