/*******************************************************************************
  USB Status Indicator LED

  Company:
    Microchip Technology Inc.

  File Name:
    led_usb_status.c

  Summary:
    Indicates the USB device status to the user via an LED.

  Description:
    Indicates the USB device status to the user via an LED.
    * The LED is turned off for suspend mode.
    * It blinks quickly with 50% on time when configured
    * It blinks slowly at a low on time (~5% on, 95% off) for all other states.
*******************************************************************************/
#include <stdint.h>
#include "pic16f1459/system.h"
#include "../framework/usb/usb_device.h" 

void APP_LEDUpdateUSBStatus(void)
{
    static uint16_t ledCount = 0;

    if(USBIsDeviceSuspended() == true)
    {
        LED_Off(LED_USB_DEVICE_STATE);
        return;
    }

    switch(USBGetDeviceState())
    {         
        case CONFIGURED_STATE:
            /* We are configured.  Blink fast.
             * On for 75ms, off for 75ms, then reset/repeat. */
            if(ledCount == 1)
            {
                LED_On(LED_USB_DEVICE_STATE);
            }
            else if(ledCount == 75)
            {
                LED_Off(LED_USB_DEVICE_STATE);
            }
            else if(ledCount > 150)
            {
                ledCount = 0;
            }
            break;

        default:
            /* We aren't configured yet, but we aren't suspended so let's blink with
             * a slow pulse. On for 50ms, then off for 950ms, then reset/repeat. */
            if(ledCount == 1)
            {
                LED_On(LED_USB_DEVICE_STATE);
            }
            else if(ledCount == 50)
            {
                LED_Off(LED_USB_DEVICE_STATE);
            }
            else if(ledCount > 950)
            {
                ledCount = 0;
            }
            break;
    }

    /* Increment the millisecond counter. */
    ledCount++;
}
