################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 41
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
FSL_LF_demo.elf \

EXECUTABLES_QUOTED += \
"FSL_LF_demo.elf" \

EXECUTABLES_OS_FORMAT += \
FSL_LF_demo.elf \

SECONDARY_SIZE += \
FSL_LF_demo.siz \

SECONDARY_SIZE_QUOTED += \
"FSL_LF_demo.siz" \

SECONDARY_SIZE_OS_FORMAT += \
FSL_LF_demo.siz \


# All Target
all: warning-messages explicit-dependencies FSL_LF_demo.elf secondary-outputs

# Tool invocations
FSL_LF_demo.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/ProcessorExpert.ld
	@echo 'Building target: $@'
	@echo 'Executing target #42 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED) @"FSL_LF_demo.args" -o"FSL_LF_demo.elf"
	@echo 'Finished building target: $@'
	@echo ' '

FSL_LF_demo.siz: FSL_LF_demo.elf
	@echo 'Executing target #43 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Print Size'
	"$(ARMSourceryDirEnv)/arm-none-eabi-size"  --format=berkeley FSL_LF_demo.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) "./*/*.o" "./*/*/*.o"  $(S_UPPER_DEPS_QUOTED) $(ASM_DEPS_QUOTED) $(SECONDARY_SIZE_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d" "./*/*/*.d"  $(ProjDirPath)/FLASH/FSL_LF_demo.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/ProcessorExpert.ld FSL_LF_demo.elf 

warning-messages: 

