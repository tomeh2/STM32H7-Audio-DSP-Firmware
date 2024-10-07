################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Custom/Src/console.c \
../Custom/Src/driver_manager.c \
../Custom/Src/encoder.c \
../Custom/Src/interface.c \
../Custom/Src/linked_list.c \
../Custom/Src/logger.c \
../Custom/Src/parameter.c 

OBJS += \
./Custom/Src/console.o \
./Custom/Src/driver_manager.o \
./Custom/Src/encoder.o \
./Custom/Src/interface.o \
./Custom/Src/linked_list.o \
./Custom/Src/logger.o \
./Custom/Src/parameter.o 

C_DEPS += \
./Custom/Src/console.d \
./Custom/Src/driver_manager.d \
./Custom/Src/encoder.d \
./Custom/Src/interface.d \
./Custom/Src/linked_list.d \
./Custom/Src/logger.d \
./Custom/Src/parameter.d 


# Each subdirectory must supply rules for building sources it contributes
Custom/Src/%.o Custom/Src/%.su Custom/Src/%.cyclo: ../Custom/Src/%.c Custom/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu18 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DSTM32_THREAD_SAFE_STRATEGY=2 -DENABLE_LOGGING -c -I../Core/Inc -I../../Drivers/CMSIS/DSP/Include -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Device_Library/Class/AUDIO/Inc -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Inc" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Drivers/Internal" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/DSP/Inc" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Console/Inc" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Console" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Audio/Inc" -I../Core/ThreadSafe -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/CM7/Custom/Drivers/CS4272" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/Drivers/CMSIS/Include" -I"C:/Projects/STM32/STM32H7-Audio-DSP-Firmware/Drivers/CMSIS/DSP/Include" -O0 -ffunction-sections -fdata-sections -Wall -Wextra -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Custom-2f-Src

clean-Custom-2f-Src:
	-$(RM) ./Custom/Src/console.cyclo ./Custom/Src/console.d ./Custom/Src/console.o ./Custom/Src/console.su ./Custom/Src/driver_manager.cyclo ./Custom/Src/driver_manager.d ./Custom/Src/driver_manager.o ./Custom/Src/driver_manager.su ./Custom/Src/encoder.cyclo ./Custom/Src/encoder.d ./Custom/Src/encoder.o ./Custom/Src/encoder.su ./Custom/Src/interface.cyclo ./Custom/Src/interface.d ./Custom/Src/interface.o ./Custom/Src/interface.su ./Custom/Src/linked_list.cyclo ./Custom/Src/linked_list.d ./Custom/Src/linked_list.o ./Custom/Src/linked_list.su ./Custom/Src/logger.cyclo ./Custom/Src/logger.d ./Custom/Src/logger.o ./Custom/Src/logger.su ./Custom/Src/parameter.cyclo ./Custom/Src/parameter.d ./Custom/Src/parameter.o ./Custom/Src/parameter.su

.PHONY: clean-Custom-2f-Src

