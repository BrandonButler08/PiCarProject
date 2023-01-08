#include "IR_LS.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

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
	// if (-1 == write(fd, c_buf, numbytes))
	// { // writes to file
	// 	printf("failed to write %s\n", path);
	// 	return (-1);
	// }

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
		printf("Failed to set GPIO direction: %d\n",pin);
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