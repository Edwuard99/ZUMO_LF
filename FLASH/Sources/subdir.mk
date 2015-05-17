################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/PID.c" \
"../Sources/ProcessorExpert.c" \
"../Sources/ZumoMotors.c" \
"../Sources/ZumoSensors.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/PID.c \
../Sources/ProcessorExpert.c \
../Sources/ZumoMotors.c \
../Sources/ZumoSensors.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/Events.o \
./Sources/PID.o \
./Sources/ProcessorExpert.o \
./Sources/ZumoMotors.o \
./Sources/ZumoSensors.o \
./Sources/sa_mtb.o \

OBJS_QUOTED += \
"./Sources/Events.o" \
"./Sources/PID.o" \
"./Sources/ProcessorExpert.o" \
"./Sources/ZumoMotors.o" \
"./Sources/ZumoSensors.o" \
"./Sources/sa_mtb.o" \

C_DEPS += \
./Sources/Events.d \
./Sources/PID.d \
./Sources/ProcessorExpert.d \
./Sources/ZumoMotors.d \
./Sources/ZumoSensors.d \
./Sources/sa_mtb.d \

OBJS_OS_FORMAT += \
./Sources/Events.o \
./Sources/PID.o \
./Sources/ProcessorExpert.o \
./Sources/ZumoMotors.o \
./Sources/ZumoSensors.o \
./Sources/sa_mtb.o \

C_DEPS_QUOTED += \
"./Sources/Events.d" \
"./Sources/PID.d" \
"./Sources/ProcessorExpert.d" \
"./Sources/ZumoMotors.d" \
"./Sources/ZumoSensors.d" \
"./Sources/sa_mtb.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/PID.o: ../Sources/PID.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/PID.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/PID.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/ProcessorExpert.o: ../Sources/ProcessorExpert.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ProcessorExpert.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ProcessorExpert.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/ZumoMotors.o: ../Sources/ZumoMotors.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ZumoMotors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ZumoMotors.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/ZumoSensors.o: ../Sources/ZumoSensors.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/ZumoSensors.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/ZumoSensors.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


