#include <stdio.h>
#include "pico/stdlib.h"

int cmd[3];
bool newCmd = false;

void receiveSerial(int *data);

int main(){
    stdio_init_all();
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);


    while (true) {
        receiveSerial(cmd);
        if (newCmd){
            newCmd = false;
            if (cmd[0] == 0x01){
                gpio_put(25, true);
                sleep_ms(100);
                gpio_put(25, false);
            }
        }  
    }
    return 0;
}

void receiveSerial(int *data){
    static int pos = 0;

    // Check if first byte available
    int c = getchar_timeout_us(1);
    while (c != PICO_ERROR_TIMEOUT){
        // If terminating 0xFF byte
        if (c == 0xFF){
            pos = 0;
            newCmd = true;
        }
        else{
            data[pos++] = c;
        }

        c = getchar_timeout_us(10);
    }
}