################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../command_queue.cpp \
../entity.cpp \
../globals.cpp \
../input_handler.cpp \
../main.cpp \
../math_ext.cpp \
../sdl_window.cpp \
../spritesheet.cpp 

OBJS += \
./command_queue.o \
./entity.o \
./globals.o \
./input_handler.o \
./main.o \
./math_ext.o \
./sdl_window.o \
./spritesheet.o 

CPP_DEPS += \
./command_queue.d \
./entity.d \
./globals.d \
./input_handler.d \
./main.d \
./math_ext.d \
./sdl_window.d \
./spritesheet.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


