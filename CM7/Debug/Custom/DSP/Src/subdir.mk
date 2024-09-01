################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Custom/DSP/Src/delay_line.c \
../Custom/DSP/Src/modulator.c 

OBJS += \
./Custom/DSP/Src/delay_line.o \
./Custom/DSP/Src/modulator.o 

C_DEPS += \
./Custom/DSP/Src/delay_line.d \
./Custom/DSP/Src/modulator.d 


# Each subdirectory must supply rules for building sources it contributes
Custom/DSP/Src/%.o Custom/DSP/Src/%.su Custom/DSP/Src/%.cyclo: ../Custom/DSP/Src/%.c Custom/DSP/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu18 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DSTM32_THREAD_SAFE_STRATEGY=2 -DENABLE_LOGGING -c -I../Core/Inc -I../../Drivers/CMSIS/DSP/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Inc" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Drivers/Internal" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/DSP/Inc" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Console/Inc" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Console" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Audio/Inc" -I../Core/ThreadSafe -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Drivers/CS4272" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/Drivers/CMSIS/Include" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Custom-2f-DSP-2f-Src

clean-Custom-2f-DSP-2f-Src:
	-$(RM) ./Custom/DSP/Src/delay_line.cyclo ./Custom/DSP/Src/delay_line.d ./Custom/DSP/Src/delay_line.o ./Custom/DSP/Src/delay_line.su ./Custom/DSP/Src/modulator.cyclo ./Custom/DSP/Src/modulator.d ./Custom/DSP/Src/modulator.o ./Custom/DSP/Src/modulator.su

.PHONY: clean-Custom-2f-DSP-2f-Src

