#ifndef ReadReceiver_H
#define ReadReceiver_H

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"

#include "ReadReceiver.h"
#include "ReadReceiver.pio.h"

// class that reads PWM pulses on max 4 pins
class ReadReceiver
{
public:
    ReadReceiver(uint *pin_list, uint num_channels);
    // read the pulsewidth in ms
    int readMicroseconds(uint ch);

private:
    // set the irq handler
    static void pio_irq_handler()
    {
        int state_machine = -1;
        // check which IRQ was raised:
        for (int i = 0; i < 4; i++)
        {
            if (pio0_hw->irq & 1<<i)
            {
                // clear interrupt
                pio0_hw->irq = 1 << i;
                // read pulse width from the FIFO
                pulsewidth[i] = pio_sm_get(pio, i);
                // read low period from the FIFO
                //period[i] = pio_sm_get(pio, i)
                // clear interrupt
                pio0_hw->irq = 1 << i;
            }
        }
    }
    // the pio instance
    static PIO pio;
    // number of channels
    uint channels;
    // data about the PWM input measured in pio clock cycles
    static uint32_t pulsewidth[4];
};

#endif