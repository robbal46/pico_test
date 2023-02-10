#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/irq.h"

#include "ReadReceiver.h"
#include "ReadReceiver.pio.h"

// class that reads PWM pulses from up to 4 pins
ReadReceiver::ReadReceiver(uint *pin_list, uint num_channels)
{
    // pio 0 is used
    pio = pio0;
    // load the pio program into the pio memory
    uint offset = pio_add_program(pio, &ReadReceiver_program);
    // start num_of_pins state machines
    for (int i = 0; i < num_channels; i++)
    {
        // prepare state machine i
        pulsewidth[i] = 0;

        // configure the used pins (pull down, controlled by PIO)
        gpio_pull_down(pin_list[i]);
        pio_gpio_init(pio, pin_list[i]);
        // make a sm config
        pio_sm_config c = ReadReceiver_program_get_default_config(offset);
        // set the 'jmp' pin
        sm_config_set_jmp_pin(&c, pin_list[i]);
        // set the 'wait' pin (uses 'in' pins)
        sm_config_set_in_pins(&c, pin_list[i]);
        // set shift direction
        sm_config_set_in_shift(&c, false, false, 0);
        // init the pio sm with the config
        pio_sm_init(pio, i, offset, &c);
        // enable the sm
        pio_sm_set_enabled(pio, i, true);
    }
    // set the IRQ handler
    irq_set_exclusive_handler(PIO0_IRQ_0, pio_irq_handler);
    // enable the IRQ
    irq_set_enabled(PIO0_IRQ_0, true);
    // allow irqs from the low 4 state machines
    pio0_hw->inte0 = PIO_IRQ0_INTE_SM0_BITS | PIO_IRQ0_INTE_SM1_BITS | PIO_IRQ0_INTE_SM2_BITS | PIO_IRQ0_INTE_SM3_BITS ;
};



int ReadReceiver::readMicroseconds(uint ch)
{
    // the measurements are taken with 2 clock cycles per timer tick
    return ((int)pulsewidth[ch] * 0.016);
};

// Static variables
uint32_t ReadReceiver::pulsewidth[4];
PIO ReadReceiver::pio;