#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/time.h"

#include "ReadReceiver.h"

#define NUM_CHANNELS 1

int main()
{
    // needed for printf
    stdio_init_all();

    // set PwmIn
    uint pins[3] = {18,19,20};
    ReadReceiver receiver(pins, 3);

    while (true)
    {
        // adviced empty (for now) function of sdk
        tight_loop_contents();

        // translate pwm of input to output
        int PW0 = receiver.readMicroseconds(0);
        int PW1 = receiver.readMicroseconds(1);
        int PW2 = receiver.readMicroseconds(2);
        printf("PW= %d, %d, %d\n", PW0, PW1, PW2);
        sleep_ms(100);
    }
}