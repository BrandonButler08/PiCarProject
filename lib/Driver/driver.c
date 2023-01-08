/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Troy Carloni
* Student ID: 918195634
* Github ID: troyc529
* Project: Assignment 3 - Start Your Motor
*
* File: driver.c
*
* Description: functions for controlling motor
*
**************************************************************/
#include "Debug.h"
#include "driver.h"

//initializes PCA9685/frequency
void m_Initialize(void)
{
    PCA9685_Init(0x40);
    PCA9685_SetPWMFreq(800);
}

//sets speed of motor and direction
void m_Run(int dir, int speed)
{
    if(speed > 100) //max speed of 100
        speed = 100;


        PCA9685_SetPwmDutyCycle(PWMA, speed); //sets pwm to motor
        PCA9685_SetPwmDutyCycle(PWMB, speed);
        if(dir == FORWARD) { //determines direction for motor fwd/bckwd
            PCA9685_SetLevel(AIN1, 1);
            PCA9685_SetLevel(AIN2, 0);
            PCA9685_SetLevel(BIN1, 1);
            PCA9685_SetLevel(BIN2, 0);
        } else {
            PCA9685_SetLevel(AIN1, 0);
            PCA9685_SetLevel(AIN2, 1);
            PCA9685_SetLevel(BIN1, 0);
            PCA9685_SetLevel(BIN2, 1);
        }
    
}

void m_Right(int speed)
{

    if (speed > 100) //max speed of 100
        speed = 100;

    PCA9685_SetPwmDutyCycle(PWMA, speed); //sets pwm to motor
    PCA9685_SetPwmDutyCycle(PWMB, speed);
    //determines direction for motor fwd/bckwd
        PCA9685_SetLevel(AIN1, 1);
        PCA9685_SetLevel(AIN2, 0);
        PCA9685_SetLevel(BIN1, 0);
        PCA9685_SetLevel(BIN2, 1);
}

void m_Left(int speed)
{

    if (speed > 100) //max speed of 100
        speed = 100;

    PCA9685_SetPwmDutyCycle(PWMA, speed); //sets pwm to motor
    PCA9685_SetPwmDutyCycle(PWMB, speed);
    //determines direction for motor fwd/bckwd
    PCA9685_SetLevel(AIN1, 0);
    PCA9685_SetLevel(AIN2, 1);
    PCA9685_SetLevel(BIN1, 1);
    PCA9685_SetLevel(BIN2, 0);


}

//turns motor off
void m_Stop()
{
    PCA9685_SetPwmDutyCycle(PWMA, 0);
    PCA9685_SetPwmDutyCycle(PWMB, 0);
}