################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../systems/collision_system.cpp \
../systems/control_system.cpp \
../systems/damage_system.cpp \
../systems/entity_system.cpp \
../systems/movement_system.cpp \
../systems/rendering_system.cpp 

OBJS += \
./systems/collision_system.o \
./systems/control_system.o \
./systems/damage_system.o \
./systems/entity_system.o \
./systems/movement_system.o \
./systems/rendering_system.o 

CPP_DEPS += \
./systems/collision_system.d \
./systems/control_system.d \
./systems/damage_system.d \
./systems/entity_system.d \
./systems/movement_system.d \
./systems/rendering_system.d 


# Each subdirectory must supply rules for building sources it contributes
systems/%.o: ../systems/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


