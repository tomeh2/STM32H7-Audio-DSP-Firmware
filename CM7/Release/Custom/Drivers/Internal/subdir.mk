################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Custom/Drivers/Internal/internal_peripheral_driver.c \
../Custom/Drivers/Internal/uart_driver.c \
../Custom/Drivers/Internal/usb_audio_driver.c 

OBJS += \
./Custom/Drivers/Internal/internal_peripheral_driver.o \
./Custom/Drivers/Internal/uart_driver.o \
./Custom/Drivers/Internal/usb_audio_driver.o 

C_DEPS += \
./Custom/Drivers/Internal/internal_peripheral_driver.d \
./Custom/Drivers/Internal/uart_driver.d \
./Custom/Drivers/Internal/usb_audio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Custom/Drivers/Internal/%.o Custom/Drivers/Internal/%.su Custom/Drivers/Internal/%.cyclo: ../Custom/Drivers/Internal/%.c Custom/Drivers/Internal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DSTM32_THREAD_SAFE_STRATEGY=2 -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -I../Core/ThreadSafe -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Audio/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Core/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Console/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Drivers/CS4272" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Drivers/Internal" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/DSP/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/CM7/Custom/Inc" -I"C:/Projects/STM32/Audio Processor Firmware/Drivers/CMSIS/DSP/Include" -I"C:/Projects/STM32/Audio Processor Firmware/Drivers/CMSIS/Include" -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Custom-2f-Drivers-2f-Internal

clean-Custom-2f-Drivers-2f-Internal:
	-$(RM) ./Custom/Drivers/Internal/internal_peripheral_driver.cyclo ./Custom/Drivers/Internal/internal_peripheral_driver.d ./Custom/Drivers/Internal/internal_peripheral_driver.o ./Custom/Drivers/Internal/internal_peripheral_driver.su ./Custom/Drivers/Internal/uart_driver.cyclo ./Custom/Drivers/Internal/uart_driver.d ./Custom/Drivers/Internal/uart_driver.o ./Custom/Drivers/Internal/uart_driver.su ./Custom/Drivers/Internal/usb_audio_driver.cyclo ./Custom/Drivers/Internal/usb_audio_driver.d ./Custom/Drivers/Internal/usb_audio_driver.o ./Custom/Drivers/Internal/usb_audio_driver.su

.PHONY: clean-Custom-2f-Drivers-2f-Internal

