################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/adc_dma.c \
../Core/Src/app_scope.c \
../Core/Src/fonts.c \
../Core/Src/ili9341.c \
../Core/Src/main.c \
../Core/Src/oszi_adc.c \
../Core/Src/scope_fps.c \
../Core/Src/scope_grid.c \
../Core/Src/scope_overlay.c \
../Core/Src/scope_ranges.c \
../Core/Src/scope_wave.c \
../Core/Src/stm32l4xx_hal_msp.c \
../Core/Src/stm32l4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l4xx.c \
../Core/Src/tft_port.c 

OBJS += \
./Core/Src/adc_dma.o \
./Core/Src/app_scope.o \
./Core/Src/fonts.o \
./Core/Src/ili9341.o \
./Core/Src/main.o \
./Core/Src/oszi_adc.o \
./Core/Src/scope_fps.o \
./Core/Src/scope_grid.o \
./Core/Src/scope_overlay.o \
./Core/Src/scope_ranges.o \
./Core/Src/scope_wave.o \
./Core/Src/stm32l4xx_hal_msp.o \
./Core/Src/stm32l4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l4xx.o \
./Core/Src/tft_port.o 

C_DEPS += \
./Core/Src/adc_dma.d \
./Core/Src/app_scope.d \
./Core/Src/fonts.d \
./Core/Src/ili9341.d \
./Core/Src/main.d \
./Core/Src/oszi_adc.d \
./Core/Src/scope_fps.d \
./Core/Src/scope_grid.d \
./Core/Src/scope_overlay.d \
./Core/Src/scope_ranges.d \
./Core/Src/scope_wave.d \
./Core/Src/stm32l4xx_hal_msp.d \
./Core/Src/stm32l4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l4xx.d \
./Core/Src/tft_port.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L432xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/adc_dma.cyclo ./Core/Src/adc_dma.d ./Core/Src/adc_dma.o ./Core/Src/adc_dma.su ./Core/Src/app_scope.cyclo ./Core/Src/app_scope.d ./Core/Src/app_scope.o ./Core/Src/app_scope.su ./Core/Src/fonts.cyclo ./Core/Src/fonts.d ./Core/Src/fonts.o ./Core/Src/fonts.su ./Core/Src/ili9341.cyclo ./Core/Src/ili9341.d ./Core/Src/ili9341.o ./Core/Src/ili9341.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/oszi_adc.cyclo ./Core/Src/oszi_adc.d ./Core/Src/oszi_adc.o ./Core/Src/oszi_adc.su ./Core/Src/scope_fps.cyclo ./Core/Src/scope_fps.d ./Core/Src/scope_fps.o ./Core/Src/scope_fps.su ./Core/Src/scope_grid.cyclo ./Core/Src/scope_grid.d ./Core/Src/scope_grid.o ./Core/Src/scope_grid.su ./Core/Src/scope_overlay.cyclo ./Core/Src/scope_overlay.d ./Core/Src/scope_overlay.o ./Core/Src/scope_overlay.su ./Core/Src/scope_ranges.cyclo ./Core/Src/scope_ranges.d ./Core/Src/scope_ranges.o ./Core/Src/scope_ranges.su ./Core/Src/scope_wave.cyclo ./Core/Src/scope_wave.d ./Core/Src/scope_wave.o ./Core/Src/scope_wave.su ./Core/Src/stm32l4xx_hal_msp.cyclo ./Core/Src/stm32l4xx_hal_msp.d ./Core/Src/stm32l4xx_hal_msp.o ./Core/Src/stm32l4xx_hal_msp.su ./Core/Src/stm32l4xx_it.cyclo ./Core/Src/stm32l4xx_it.d ./Core/Src/stm32l4xx_it.o ./Core/Src/stm32l4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l4xx.cyclo ./Core/Src/system_stm32l4xx.d ./Core/Src/system_stm32l4xx.o ./Core/Src/system_stm32l4xx.su ./Core/Src/tft_port.cyclo ./Core/Src/tft_port.d ./Core/Src/tft_port.o ./Core/Src/tft_port.su

.PHONY: clean-Core-2f-Src

