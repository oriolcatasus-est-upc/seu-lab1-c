#include "mbed.h"
 
DigitalIn enable(p17);
DigitalOut led(LED1);

float pulseMinTime = 0.5;
float blinkingTime = 10;
float blinkingInterval = 0.1;

Timer timerPIN;
Timer timerLED;

float prevBlinkingRead = 0;

int statePIN = 0;
// 0 -> PIN 17 disabled
// 1 -> PIN 17 enabled for less than 0.5s
// 2 -> PIN 17 enabled for more than 0.5s

int stateLED = 0;
// 0 -> LED off
// 1 -> LED blinking

int main()
{
    while (true) {
        if (enable) {
            if (statePIN == 0) {
                timerPIN.start();
                statePIN = 1;
            }
            if (statePIN == 1 && timerPIN.read() > pulseMinTime) {
                timerPIN.stop();
                timerPIN.reset();
                statePIN = 2;
                if (stateLED == 0) {
                    timerLED.start();
                    led = true;
                    stateLED = 1;
                } else {
                    timerLED.stop();
                    timerLED.reset();
                    prevBlinkingRead = 0;
                    led = false;
                    stateLED = 0;
                }
            }
        } else {
            statePIN = 0;
        }

        if (stateLED == 1) {
            if (timerLED.read() < blinkingTime) {
                float diff = timerLED.read() - prevBlinkingRead;
                if (diff > blinkingInterval) {
                    led = !led;
                    prevBlinkingRead = timerLED.read();
                }
            } else {
                timerLED.stop();
                timerLED.reset();
                prevBlinkingRead = 0;
                led = false;
                stateLED = 0;
            }
        }
    }
}
