################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"D:/workspace/AC6/C10_GA6_DUST25_F103CT86_AC6/StdPeriph_Driver/inc" -I"D:/workspace/AC6/C10_GA6_DUST25_F103CT86_AC6/inc" -I"D:/workspace/AC6/C10_GA6_DUST25_F103CT86_AC6/CMSIS/device" -I"D:/workspace/AC6/C10_GA6_DUST25_F103CT86_AC6/CMSIS/core" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


