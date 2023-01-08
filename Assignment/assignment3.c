/**************************************************************
* Class: CSC-615-01 Spring 2020
* Name: Brandon Butler Dimitri Rodriguez Troy Carloni
* Student ID: 920819091 917276105 918195634
* Github ID: BrandonButler08 UntitledI troyc529
* Group Name: Team Alpha
* Project: Final Assignment
*
* File: assignment3.c
*
* Description: Runs the car and avoids obstacles.
*
**************************************************************/

#include "assignment3.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define c_buf_SIZE 3   // char buffer size
#define PATH_LENGTH 35 // char * path length


#define MAX_POW 4096
#define BASEPIN 300
#define HERTZ 50

#define sense1  12// pin#
#define sense2  20// pin#
#define sense3  16 // pin#

#define iRed1 13  // front side,
#define iRed2 19 // front right side,
#define iRed3 5  // back right side,

// enables/disables GPIO pin
static int GPIOonOff(int pin, char* path)
{
	char c_buf[c_buf_SIZE];
	int numbytes;
	int fd;

	fd = open(path, O_WRONLY); // open file descriptor for gpio export

	if (-1 == fd)
	{ // error checking for failed open
		printf("failed to open %s\n", path);
		return (-1);
	}

	numbytes = snprintf(c_buf, c_buf_SIZE, "%d", pin); // formats string for write
	 if (-1 == write(fd, c_buf, numbytes))
	 { // writes to file
		printf("failed to write %s\n", path);
	 	return (-1);
	 }

	close(fd); // close file

	return (0);
}

// sets GPIO direction
static int GPIODirection(int pin, char* direction, int length)
{
	char path[PATH_LENGTH];
	int fd;

	snprintf(path, PATH_LENGTH, "/sys/class/gpio/gpio%d/direction", pin); // formats string for path
	fd = open(path, O_WRONLY);											  // open file descriptor for direction set
	if (-1 == fd)
	{ // error checking for failed open
		printf("Failed to open GPIO direction\n");
		return (-1);
	}

	if (-1 == write(fd, direction, length))
	{ // writes to file
		printf("Failed to set GPIO direction: %d\n", pin);
		return (-1);
	}

	close(fd); // close file

	return (0);
}

// writes either 1 or 0 to GPIO value
static int GPIOWrite(int pin, int value)
{
	char path[PATH_LENGTH];
	int fd;
	const char high_Low[] = "01";

	snprintf(path, PATH_LENGTH, "/sys/class/gpio/gpio%d/value", pin); // formats string for path
	fd = open(path, O_WRONLY);										  // open file descriptor for GPIO value set
	if (-1 == fd)
	{ // error checking for failed open
		printf("Failed to open GPIO value for writing\n");
		return (-1);
	}

if (1 != write(fd, &high_Low[value], 1))
{ // writes to file
	printf("Failed to write\n");
	return (-1);
}

close(fd); // close file
return (0);
}

// Reads from GPIO pin
static int GPIORead(int pin)
{
	char path[PATH_LENGTH];
	int fd;
	char input[3];

	snprintf(path, PATH_LENGTH, "/sys/class/gpio/gpio%d/value", pin); // formats string for path
	fd = open(path, O_RDONLY);										  // open file descriptor for read
	if (-1 == fd)
	{
		printf("Failed to open read\n");
		return (-1);
	}

	if (-1 == read(fd, input, 3)) // read fd capture data
	{
		printf("Failed to read\n");
		return (-1);
	}

	close(fd); // close file

	return (atoi(input)); // converts string to int
}

int main(void)
{
	char line[3];
	char iR[3];
	char test[3];
	int obstacleBoolFlag = 1;
	int waitCount = 0;

	char c_arr[2][26] = { {"/sys/class/gpio/export"}, {"/sys/class/gpio/unexport"} };

	if (DEV_ModuleInit()) // Module Initialize, the library and initialize the pins, SPI protocol
		exit(0);



	//initialize LS pins
	if (-1 == GPIOonOff(sense1, c_arr[0])) // turn button pin on
		return (4);

	
	if (-1 == GPIOonOff(sense2, c_arr[0])) // turn button pin on
		return (4);

	
	if (-1 == GPIOonOff(sense3, c_arr[0])) // turn button pin on
		return (4);


	
	if (-1 == GPIOonOff(iRed1, c_arr[0])) // turn button pin on
		return (4);
	if (-1 == GPIOonOff(iRed2, c_arr[0])) // turn button pin on
		return (4);
	if (-1 == GPIOonOff(iRed3, c_arr[0])) // turn button pin on
		return (4);
		
	usleep(1500000);

	//Set pin direction to read
	if (-1 == GPIODirection(sense1, "in", 2))
		return (2);
	
	if (-1 == GPIODirection(sense2, "in", 2))
		return (2);
	
	if (-1 == GPIODirection(sense3, "in", 2))
		return (2);

	
	if (-1 == GPIODirection(iRed1, "in", 2))
		return (2);
	if (-1 == GPIODirection(iRed2, "in", 2))
		return (2);
	if (-1 == GPIODirection(iRed3, "in", 2))
		return (2);
		



	m_Initialize(); // initializes motor


	//continuously reads sensor, determines operation by string output from reads
	while (1) {
		//reads Line sensors, formats for logic interpretation
		test[0] = '0' + !GPIORead(sense1);
		test[1] = '0' + !GPIORead(sense2);
		test[2] = '0' + !GPIORead(sense3);

		for (int i = 0; i < 3; i++) {
			line[i] = test[i];
		}

		//reads iR sensors, formats for logic interpretation
		iR[0] = '0' + !GPIORead(iRed1);
		iR[1] = '0' + !GPIORead(iRed2);
		iR[2] = '0' + !GPIORead(iRed3);


		//if font iR sensor detects obstacle, sets boolean to true
		if (strcmp("100", iR) == 0) {
			obstacleBoolFlag = 0;
		}

	
		//if middle line sensor detects line drive fwd
		if (strcmp("101", line) == 0) {
			//printf("Driving foward");
			m_Run(FORWARD, 100);
			usleep(500);
			m_Stop();

		}
		
		//  logic for determining when to turn left
		else if (strcmp("001", line) == 0 || strcmp("011", line) == 0) {
			//printf("Turning left");
			m_Left(100);
			usleep(1000);
	
		}
		//  logic for determining when to turn right
		else if (strcmp("100", line) == 0 || strcmp("110", line) == 0) {
			//	printf("Turning right");
			m_Right(100);
			usleep(1000);
		}
		// logic filler, run forward if any of the following scenarios occur
		else if (strcmp("000", line) == 0 || strcmp("111", line) == 0 || strcmp("100", iR) == 0) {
			m_Run(FORWARD, 100);
			usleep(500);
			m_Stop();
		
		}


		//if obstacle run alternate operations
		if (obstacleBoolFlag == 0) {
			printf("Backing up");
			m_Run(BACKWARD, 100);
			usleep(150000);
			m_Stop();
			m_Left(100);
			usleep(730000);
			m_Stop();
			usleep(300);
			m_Run(FORWARD, 100);
			usleep(1100000);
			m_Right(100);
			usleep(730000);
			m_Run(FORWARD, 100);
			usleep(4000000);
			m_Right(100);
			usleep(730000);
	
		}
		//after traversing obstacle drive fwd until line is found revert back to line logic
		while (obstacleBoolFlag == 0) {

			m_Run(FORWARD, 100);
			usleep(500);

			iR[0] = '0' + !GPIORead(iRed1);
			iR[1] = '0' + !GPIORead(iRed2);
			iR[2] = '0' + !GPIORead(iRed3);
			waitCount++;
		


			//waitcount gives the vehicle time to get off the line before searching for it again
			if (waitCount > 1000) {
				test[0] = '0' + !GPIORead(sense1);
				test[1] = '0' + !GPIORead(sense2);
				test[2] = '0' + !GPIORead(sense3);
				//if any sensor detects line revert back to line logic
				if (test[0] == '0' || test[1] == '0' || test[2] == '0') {
					obstacleBoolFlag = 1;
					waitCount = 0;
					m_Stop();
					printf("BACK ON LINE SENSOR\n");
				}
			}
		}

	}

		

	
	

	usleep(1000000);
	printf("Stopping\n");
	m_Stop();		  // stops motor
	DEV_ModuleExit(); // Module exits, closes SPI and BCM2835 library
	printf("finished\n");
	return 0;
}
