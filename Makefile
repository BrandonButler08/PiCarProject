#/**************************************************************
#* Class: CSC-615-01 Spring 2020
#* Name: Troy Carloni
#* Student ID: 918195634
#* Github ID: troyc529
#* Project: Final Project
#*
#* File: Makefile
#*
#* Description: makefile for assignment
#*
#**************************************************************/
DIR_OBJ = ./lib
DIR_BIN = ./bin
DIR_Config = ./lib/Config
DIR_Driver = ./lib/Driver
DIR_PCA9685 = ./lib/PCA9685
DIR_Assignment = ./Assignment

OBJ_C = $(wildcard ${DIR_OBJ}/*.c ${DIR_Assignment}/*.c ${DIR_Config}/*.c ${DIR_Driver}/*.c ${DIR_PCA9685}/*.c )
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

TARGET = assignment3
#BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc

DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG)

DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG)

# USELIB = USE_BCM2835_LIB
# USELIB = USE_WIRINGPI_LIB
USELIB = USE_DEV_LIB
DEBUG = -D $(USELIB) 
ifeq ($(USELIB), USE_BCM2835_LIB)
    LIB = -lbcm2835 -lm 
else ifeq ($(USELIB), USE_WIRINGPI_LIB)
    LIB = -lwiringPi -lm 

endif 

 



${TARGET}:${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB) -lm

${DIR_BIN}/%.o : $(DIR_Assignment)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB) -I $(DIR_OBJ) -I $(DIR_Config) -I $(DIR_Driver) -I $(DIR_PCA9685)

${DIR_BIN}/%.o : $(DIR_OBJ)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB) -I $(DIR_Config)
    
${DIR_BIN}/%.o : $(DIR_Config)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB)

${DIR_BIN}/%.o : $(DIR_PCA9685)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB) -I $(DIR_Config)

${DIR_BIN}/%.o : $(DIR_Driver)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ $(LIB) -I $(DIR_Config) -I $(DIR_PCA9685)

run: $(TARGET)
	./$(TARGET)

clean :
	rm $(TARGET) 
	rm $(DIR_BIN)/*.* 
