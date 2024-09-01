################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include USB_DEVICE/Target/subdir.mk
-include USB_DEVICE/App/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/subdir.mk
-include Custom/Src/subdir.mk
-include Custom/Drivers/Internal/subdir.mk
-include Custom/Drivers/CS4272/subdir.mk
-include Custom/DSP/Src/subdir.mk
-include Custom/Console/Src/subdir.mk
-include Custom/Audio/Src/subdir.mk
-include Core/ThreadSafe/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Common/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Audio Processor Firmware_CM7
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Audio\ Processor\ Firmware_CM7.elf \

MAP_FILES += \
Audio\ Processor\ Firmware_CM7.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Audio\ Processor\ Firmware_CM7.list \


# All Target
all: main-build

# Main-build Target
main-build: Audio\ Processor\ Firmware_CM7.elf secondary-outputs

# Tool invocations
Audio\ Processor\ Firmware_CM7.elf Audio\ Processor\ Firmware_CM7.map: $(OBJS) $(USER_OBJS) C:\Projects\STM32\Audio\ Processor\ Firmware\CM7\STM32H755ZITX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Audio Processor Firmware_CM7.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Projects\STM32\Audio Processor Firmware\CM7\STM32H755ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Audio Processor Firmware_CM7.map" -Wl,--gc-sections -static -L../../Drivers/CMSIS/Lib/GCC --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -u _printf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Audio\ Processor\ Firmware_CM7.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Audio Processor Firmware_CM7.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Audio\ Processor\ Firmware_CM7.elf Audio\ Processor\ Firmware_CM7.list Audio\ Processor\ Firmware_CM7.map Audio\\ Processor\\ Firmware_CM7.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
