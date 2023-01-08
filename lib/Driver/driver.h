/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Troy Carloni
* Student ID: 918195634
* Github ID: troyc529
* Project: Assignment 3 - Start Your Motor
*
* File: driver.h
*
* Description: functions for controlling motor
*
**************************************************************/
#ifndef __TB6612FNG_
#define __TB6612FNG_

#include "DEV_Config.h"
#include "PCA9685.h"

//GPIO config
#define PWMA        PCA_CHANNEL_0
#define AIN1        PCA_CHANNEL_1
#define AIN2        PCA_CHANNEL_2

#define PWMB		PCA_CHANNEL_5
#define BIN1		PCA_CHANNEL_3
#define BIN2		PCA_CHANNEL_4

//motor directino
#define FORWARD 1
#define BACKWARD 2

//motor driver functions
void m_Initialize(void);
void m_Run(int dir, int speed);
void m_Stop();
void m_Left(int speed);
void m_Right(int speed);

#endif