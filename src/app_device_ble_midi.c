/*
 * File:   app_device_ble_midi.c
 * Author: user
 *
 * Created on 21 мая 2016 г., 11:29
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "app_device_ble_midi.h"
#include "pin_manager.h"
#include "spi.h" 

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

void PlayWrap(uint8_t tone, uint8_t velocity) {

    SendMidiData(tone, velocity);

    for (int i = 0; i < velocity * 7; i++)
        __delay_ms(1);
    
    //LedFlash();
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


void APP_DeviceBLETask(){
    
    uint8_t tone = 36; 
     SendMidiData(tone, 1);
       // LedFlash();

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
    
    
    
void BLEDeviceInt(){
    
    PIN_MANAGER_Initialize();
    SPI_Initialize(); 
    
}