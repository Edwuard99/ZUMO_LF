################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Headers/ZumoSensors.c" \

C_SRCS += \
../Project_Headers/ZumoSensors.c \

OBJS += \
./Project_Headers/ZumoSensors.o \

OBJS_QUOTED += \
"./Project_Headers/ZumoSensors.o" \

C_DEPS += \
./Project_Headers/ZumoSensors.d \

OBJS_OS_FORMAT += \
./Project_Headers/ZumoSensors.o \

C_DEPS_QUOTED += \
"./Project_Headers/ZumoSensors.d" \


# Each subdirectory must supply rules for building sources it contributes
Project_Headers/ZumoSensors.o: ../Project_Headers/ZumoSensors.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Project_Headers/ZumoSensors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Project_Headers/ZumoSensors.o"
	@echo 'Finished building: $<'
	@echo ' '


