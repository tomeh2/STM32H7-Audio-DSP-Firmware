################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Custom/Console/Src/con_modulator.c \
../Custom/Console/Src/console.c \
../Custom/Console/Src/help.c \
../Custom/Console/Src/insblk.c \
../Custom/Console/Src/lsblk.c \
../Custom/Console/Src/lsdrv.c \
../Custom/Console/Src/mkdelay.c \
../Custom/Console/Src/stat.c 

OBJS += \
./Custom/Console/Src/con_modulator.o \
./Custom/Console/Src/console.o \
./Custom/Console/Src/help.o \
./Custom/Console/Src/insblk.o \
./Custom/Console/Src/lsblk.o \
./Custom/Console/Src/lsdrv.o \
./Custom/Console/Src/mkdelay.o \
./Custom/Console/Src/stat.o 

C_DEPS += \
./Custom/Console/Src/con_modulator.d \
./Custom/Console/Src/console.d \
./Custom/Console/Src/help.d \
./Custom/Console/Src/insblk.d \
./Custom/Console/Src/lsblk.d \
./Custom/Console/Src/lsdrv.d \
./Custom/Console/Src/mkdelay.d \
./Custom/Console/Src/stat.d 


# Each subdirectory must supply rules for building sources it contributes
Custom/Console/Src/%.o Custom/Console/Src/%.su Custom/Console/Src/%.cyclo: ../Custom/Console/Src/%.c Custom/Console/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -I../Core/ThreadSafe -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Audio/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Core/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Console/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Drivers/CS4272" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Drivers/Internal" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/DSP/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/Drivers/CMSIS/DSP/Include" -I"C:/Projects/STM32/Audio Processor Firmware/Drivers/CMSIS/Include" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Custom-2f-Console-2f-Src

clean-Custom-2f-Console-2f-Src:
	-$(RM) ./Custom/Console/Src/con_modulator.cyclo ./Custom/Console/Src/con_modulator.d ./Custom/Console/Src/con_modulator.o ./Custom/Console/Src/con_modulator.su ./Custom/Console/Src/console.cyclo ./Custom/Console/Src/console.d ./Custom/Console/Src/console.o ./Custom/Console/Src/console.su ./Custom/Console/Src/help.cyclo ./Custom/Console/Src/help.d ./Custom/Console/Src/help.o ./Custom/Console/Src/help.su ./Custom/Console/Src/insblk.cyclo ./Custom/Console/Src/insblk.d ./Custom/Console/Src/insblk.o ./Custom/Console/Src/insblk.su ./Custom/Console/Src/lsblk.cyclo ./Custom/Console/Src/lsblk.d ./Custom/Console/Src/lsblk.o ./Custom/Console/Src/lsblk.su ./Custom/Console/Src/lsdrv.cyclo ./Custom/Console/Src/lsdrv.d ./Custom/Console/Src/lsdrv.o ./Custom/Console/Src/lsdrv.su ./Custom/Console/Src/mkdelay.cyclo ./Custom/Console/Src/mkdelay.d ./Custom/Console/Src/mkdelay.o ./Custom/Console/Src/mkdelay.su ./Custom/Console/Src/stat.cyclo ./Custom/Console/Src/stat.d ./Custom/Console/Src/stat.o ./Custom/Console/Src/stat.su

.PHONY: clean-Custom-2f-Console-2f-Src

