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


//IR readdriver functions


//pin functions
#define c_buf_SIZE 3   // char buffer size
#define PATH_LENGTH 35 // char * path length

// enables/disables GPIO pin
static int GPIOonOff(int pin, char* path);


// sets GPIO direction
static int GPIODirection(int pin, char* direction, int length);


// writes either 1 or 0 to GPIO value
static int GPIOWrite(int pin, int value);


// Reads from GPIO pin
static int GPIORead(int pin);


