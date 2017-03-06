/* 
 * File:   driver.c
 * Author: wellern
 *
 * Created on February 9, 2017, 3:10 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <plib.h>

//#define sensor IOPORT_B
//#define senPins BIT_0 | BIT_1 | BIT_2 | BIT_3
//#define motor IOPORT D
//#define motPins BIT_1 | BIT_2 | BIT_6 | BIT_7
//#define rPi IOPORT_
//#define rPins BIT_0 | BIT_1 | BIT_2
/*
 * This Program will read values in from raspberry pi to determine route to take
 * We then wait untile we reach a black line before we execute instructions
 */
int main(int argc, char** argv) {
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
    PORTSetPinsDigitalOut(IOPORT_B, BIT_10 | BIT_11 | BIT_12 | BIT_13); //this sets all the LED's as outputs
    PORTSetPinsDigitalIn(IOPORT_B, BIT_0 | BIT_1 | BIT_2 | BIT_3);
    PORTSetPinsDigitalOut(IOPORT_D, BIT_1 | BIT_2 | BIT_6 | BIT_7);
    PORTSetPinsDigitalIn(IOPORT_E, BIT_8 | BIT_9);  //Choice bits, JH = INT1/RE8 = GPIO 2, JE = INT2/RE9 = GPIO 0
    PORTSetBits(IOPORT_D, BIT_6);
    PORTClearBits(IOPORT_D, BIT_7);

    //PORTSetPinsDigitalIn(rPi, rPins);

     //This block sets up the output comarator to a PWM
    //Chapter 16 page 31 of family reference maual
    OC2CON = 0x0000; // Turn off the OC2 when performing the setup
    OC2R = 0x0064; // Initialize primary Compare register
    OC2RS = 0x0064; // Initialize secondary Compare register
    OC2CON = 0x0006; // Configure for PWM mode without Fault pin
    OC2CONSET = 0x8000; // Enable OC2

    OC3CON = 0x0000; // Turn off the OC2 when performing the setup
    OC3R = 0x0064; // Initialize primary Compare register
    OC3RS = 0x0064; // Initialize secondary Compare register
    OC3CON = 0x0006; // Configure for PWM mode without Fault pin
    OC3CONSET = 0x8000; // Enable OC2

    //Family reference manual Chapter 14 page 14
    T2CON = 0x0010; //Configure timer
    T2CONSET = 0x8000; // Enable Timer2
    PR2 = 0x03E8; // Load period register

    SetDCOC2PWM(400);
    SetDCOC3PWM(400);
    PORTClearBits(IOPORT_B, BIT_10 | BIT_11 | BIT_12 | BIT_13);
    int temp = 1;
    int dir = 1;
    //int lane = 0;
    //Wait for instruction from raspberry pi
    
    while(dir == 1)
    {
        if(PORTReadBits(IOPORT_E,BIT_9)){
            while(temp!= 100000)
                temp++;
            temp = 1;
            dir = 0;
            SetDCOC2PWM(400);
            SetDCOC3PWM(000);
            while(temp!= 80000){
                temp++;
                }
            temp = 1;
            SetDCOC2PWM(400);
            SetDCOC3PWM(400);

        }else if(PORTReadBits(IOPORT_E,BIT_8)) {
                while(temp!= 1000000)
                    temp++;
                temp = 1;
                dir = 0;
                SetDCOC2PWM(000);
                SetDCOC3PWM(400);
                while(temp!= 80000){
                    temp++;
                }
                temp = 1;
                SetDCOC2PWM(400);
                SetDCOC3PWM(400);
                while(temp!= 100000){
                temp++;
                }
            temp = 1;
        }
    }
    /*
    dir = 2;
    //Wait till we reach end of road
    while(1){

        if(!PORTReadBits(IOPORT_B, BIT_1)){
        if(dir == 1){
            SetDCOC2PWM(400);
            SetDCOC3PWM(000);
            while(temp!= 100000){
                temp++;
                }
            temp = 1;
            SetDCOC2PWM(000);
            SetDCOC3PWM(000);
            while(temp!= 100000){
                temp++;
                }
            temp = 1;
            }else{// if(dir == 2){
                SetDCOC2PWM(000);
                SetDCOC3PWM(400);
                while(temp!= 100000){
                    temp++;
                }
                temp = 1;
                SetDCOC2PWM(000);
                SetDCOC3PWM(000);
                while(temp!= 100000){
                temp++;
                }
            temp = 1;
            }
            //lane = 1;
        }
    }
*/
    /*
     * Interupt to wait for rPi
     * Interupt to wait for black line
     * Carry out routine under black line
     * How do we make sure rPi before black line if they are both interrupts
     */
    

    while(1){

    }
    return (EXIT_SUCCESS);
}

