/*
Authors:
- Oriol
- Pablo Arancibia Barahona
*/

#include "mbed.h"
 
DigitalIn enable(p17);
DigitalOut led(LED1);

int main()
{
    const int PULSE_MIN_TIME = 500;
    const int BLINKING_DURATION = 10000;
    const int STEP_TIME = 100;

    Timer pressTimer;
    Timer blinkTimer;
    Timer stepTimer;

    bool stateEnable = false;
    int blinkState = 0; // 0: off; 1: blinking;

    while (true) {
        if (enable && !stateEnable){ // if enable is pressed and before was not pressed
            pressTimer.start();
            stateEnable = true;

        } else if (!enable && stateEnable){ // if enable is not pressed and before was pressed
            pressTimer.stop();
            pressTimer.reset();
            stateEnable = false;
        }

        if (blinkState == 0) { // if is off
            led = false;
            if (pressTimer.read_ms() > PULSE_MIN_TIME) {
                blinkTimer.start()
                stepTimer.start()
                blinkState = 1 // start blinking
                pressTimer.stop();
                pressTimer.reset();
            }

        } else if (blinkState == 1) {
            if (blinkTimer.read_ms() > BLINKING_DURATION || pressTimer.read_ms() > PULSE_MIN_TIME){
                blinkState = 0;
                
                blinkTimer.stop();
                blinkTimer.reset();

                stepTimer.stop();
                stepTimer.reset();

                pressTimer.stop();
                pressTimer.reset();
            }

            if (stepTimer.read_ms() > STEP_TIME){ // step blinking
                stepTimer.stop();
                stepTimer.reset();
                led = !led;
                stepTimer.start();
            }
        }
    }
}
