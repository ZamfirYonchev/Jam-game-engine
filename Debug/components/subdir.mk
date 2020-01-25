################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/attached_health.cpp \
../components/attached_position.cpp \
../components/character_health_visuals.cpp \
../components/character_visuals.cpp \
../components/chase_ai_control.cpp \
../components/collision.cpp \
../components/control.cpp \
../components/guide_control.cpp \
../components/health.cpp \
../components/input_control.cpp \
../components/interaction.cpp \
../components/menu_item_visuals.cpp \
../components/movement.cpp \
../components/position.cpp \
../components/visuals.cpp 

OBJS += \
./components/attached_health.o \
./components/attached_position.o \
./components/character_health_visuals.o \
./components/character_visuals.o \
./components/chase_ai_control.o \
./components/collision.o \
./components/control.o \
./components/guide_control.o \
./components/health.o \
./components/input_control.o \
./components/interaction.o \
./components/menu_item_visuals.o \
./components/movement.o \
./components/position.o \
./components/visuals.o 

CPP_DEPS += \
./components/attached_health.d \
./components/attached_position.d \
./components/character_health_visuals.d \
./components/character_visuals.d \
./components/chase_ai_control.d \
./components/collision.d \
./components/control.d \
./components/guide_control.d \
./components/health.d \
./components/input_control.d \
./components/interaction.d \
./components/menu_item_visuals.d \
./components/movement.d \
./components/position.d \
./components/visuals.d 


# Each subdirectory must supply rules for building sources it contributes
components/%.o: ../components/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


