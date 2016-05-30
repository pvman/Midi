#include <stdint.h>
#include <stdbool.h>
#include "pic16f1459/system.h"
#include "../framework/usb/usb.h"
#include "../framework/usb/usb_device_midi.h"
#include "app_device_ble_midi.h"

bool scan_task(uint8_t *note, uint8_t *velocity);

/** VARIABLES ******************************************************/
/* Some processors have a limited range of RAM addresses where the USB module
 * is able to access.  The following section is for those devices.  This section
 * assigns the buffers that need to be used by the USB module into those
 * specific areas.
 */
#if defined(FIXED_ADDRESS_MEMORY)
    #if defined(COMPILER_MPLAB_C18)
        #pragma udata DEVICE_AUDIO_MIDI_RX_DATA_BUFFER=DEVCE_AUDIO_MIDI_RX_DATA_BUFFER_ADDRESS
            static uint8_t ReceivedDataBuffer[64];
        #pragma udata DEVICE_AUDIO_MIDI_EVENT_DATA_BUFFER=DEVCE_AUDIO_MIDI_EVENT_DATA_BUFFER_ADDRESS
            static USB_AUDIO_MIDI_EVENT_PACKET midiData;
        #pragma udata
    #elif defined(__XC8)
        static uint8_t ReceivedDataBuffer[64] @ DEVCE_AUDIO_MIDI_RX_DATA_BUFFER_ADDRESS;
        static USB_AUDIO_MIDI_EVENT_PACKET midiData @ DEVCE_AUDIO_MIDI_EVENT_DATA_BUFFER_ADDRESS;
    #endif
#else
    static uint8_t ReceivedDataBuffer[64];
    static USB_AUDIO_MIDI_EVENT_PACKET midiData;
#endif

static USB_HANDLE USBTxHandle;
static USB_HANDLE USBRxHandle;

static uint8_t pitch, ble_pitch, ble_velocity;
static uint8_t ble_header = 0x80, ble_timestamp = 0, ble_midi_status = 0x90;

static bool sentNoteOff;

static USB_VOLATILE uint8_t msCounter;

//----------------------------------------------------------------------------//
void APP_DeviceAudioMIDIInitialize()
{
    USBTxHandle = NULL;
    USBRxHandle = NULL;
    pitch = 0x3C;
    sentNoteOff = true;
    msCounter = 0;
    //enable the HID endpoint
    USBEnableEndpoint(USB_DEVICE_AUDIO_MIDI_ENDPOINT,USB_OUT_ENABLED|USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
    //Re-arm the OUT endpoint for the next packet
    USBRxHandle = USBRxOnePacket(USB_DEVICE_AUDIO_MIDI_ENDPOINT,(uint8_t*)&ReceivedDataBuffer,64);
}

void APP_DeviceAudioMIDISOFHandler()  {
    if(msCounter != 0)  msCounter--;
}

void APP_DeviceAudioMIDITasks()
{
   // if( USBGetDeviceState() < CONFIGURED_STATE || USBIsDeviceSuspended())
   //     return;

   // if(!USBHandleBusy(USBRxHandle))
  //  {
        //We have received a MIDI packet from the host, process it and then
        //  prepare to receive the next packet

        //INSERT MIDI PROCESSING CODE HERE

        //Get ready for next packet (this will overwrite the old data)
   //     USBRxHandle = USBRxOnePacket(USB_DEVICE_AUDIO_MIDI_ENDPOINT,(uint8_t*)&ReceivedDataBuffer,64);
   // }
    
    
        uint8_t scan_pitch = 0x3C, velocity = 0; 
        bool bscan = 0;
        bscan = scan_task(&scan_pitch, &velocity);
        if (bscan) {
            midiData.Val = 0;
            midiData.CableNumber = 0;
            midiData.CodeIndexNumber = MIDI_CIN_NOTE_ON;
            midiData.DATA_0 = 0x90;
            midiData.DATA_1 = scan_pitch;
            midiData.DATA_2 = velocity; 
            ble_pitch  = scan_pitch;
            ble_velocity = velocity;
        //    USBTxHandle = USBTxOnePacket(USB_DEVICE_AUDIO_MIDI_ENDPOINT,(uint8_t*)&midiData,4);
        // ble_header = 0x80, ble_timestamp = 0, ble_midi_status = 0x90;
            TMR2 = TMR2 | 0x80;
            ble_timestamp = TMR2;
            SendMidiData(ble_header, ble_timestamp, ble_midi_status, ble_pitch, ble_velocity);
            
            if( USBGetDeviceState() == CONFIGURED_STATE || USBIsDeviceSuspended())
            {
                    if(!USBHandleBusy(USBRxHandle))
                    {
                        USBRxHandle = USBRxOnePacket(USB_DEVICE_AUDIO_MIDI_ENDPOINT,(uint8_t*)&ReceivedDataBuffer,64);
                    }
                USBTxHandle = USBTxOnePacket(USB_DEVICE_AUDIO_MIDI_ENDPOINT,(uint8_t*)&midiData,4);                
            }
        }
    

    /* If the user button is pressed... */
   /* if(BUTTON_IsPressed(BUTTON_DEVICE_AUDIO_MIDI))
    {
        // and we haven't sent a transmission in the past 100ms... 
        /* and we have sent the NOTE_OFF for the last note... */
        /* and we aren't currently trying to transmit data... */
    /*    if(msCounter == 0 && sentNoteOff && !USBHandleBusy(USBTxHandle))  {
            //Then reset the 100ms counter
            msCounter = 100;
            midiData.Val = 0;   //must set all unused values to 0 so go ahead
                                //  and set them all to 0
            midiData.CableNumber = 0;
            midiData.CodeIndexNumber = MIDI_CIN_NOTE_ON;
            midiData.DATA_0 = 0x90;         //Note on
            midiData.DATA_1 = pitch;         //pitch
            midiData.DATA_2 = 0x7F;  //velocity
            USBTxHandle = USBTxOnePacket(USB_DEVICE_AUDIO_MIDI_ENDPOINT,(uint8_t*)&midiData,4);
            
    /*        sentNoteOff = false;
        }
    }
    else */
        if (msCounter == 0 && !sentNoteOff && !USBHandleBusy(USBTxHandle)) {
        //Debounce counter for 100ms
        msCounter = 100;
        midiData.Val = 0;   //must set all unused values to 0 so go ahead
                            //  and set them all to 0
        midiData.CableNumber = 0;
        midiData.CodeIndexNumber = MIDI_CIN_NOTE_OFF;
        midiData.DATA_0 = 0x90;     //Note off
        midiData.DATA_1 = pitch++;     //pitch
        midiData.DATA_2 = 0x00;        //velocity
        ble_pitch  = pitch;
        ble_velocity = 0x00;
        
        if(pitch == 0x49)
            pitch = 0x3C;
        //USBTxHandle = USBTxOnePacket(USB_DEVICE_AUDIO_MIDI_ENDPOINT,(uint8_t*)&midiData,4);
        TMR2 = TMR2 | 0x80;
        ble_timestamp = TMR2;
        SendMidiData(ble_header, ble_timestamp, ble_midi_status, ble_pitch, ble_velocity);
        sentNoteOff = true;
        
        if( USBGetDeviceState() == CONFIGURED_STATE || USBIsDeviceSuspended())
            {
                    if(!USBHandleBusy(USBRxHandle))
                    {
                        USBRxHandle = USBRxOnePacket(USB_DEVICE_AUDIO_MIDI_ENDPOINT,(uint8_t*)&ReceivedDataBuffer,64);
                    }
                USBTxHandle = USBTxOnePacket(USB_DEVICE_AUDIO_MIDI_ENDPOINT,(uint8_t*)&midiData,4);
            }
    }
}
