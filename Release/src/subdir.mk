################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/delay.c \
../src/ga6.c \
../src/main.c \
../src/ring.c \
../src/syscalls.c \
../src/system_stm32f10x.c \
../src/uart.c 

OBJS += \
./src/delay.o \
./src/ga6.o \
./src/main.o \
./src/ring.o \
./src/syscalls.o \
./src/system_stm32f10x.o \
./src/uart.o 

C_DEPS += \
./src/delay.d \
./src/ga6.d \
./src/main.d \
./src/ring.d \
./src/syscalls.d \
./src/system_stm32f10x.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I"D:/workspace/AC6/C10_GA6_DUST25_F103CT86_AC6/StdPeriph_Driver/inc" -I"D:/workspace/AC6/C10_GA6_DUST25_F103CT86_AC6/inc" -I"D:/workspace/AC6/C10_GA6_DUST25_F103CT86_AC6/CMSIS/device" -I"D:/workspace/AC6/C10_GA6_DUST25_F103CT86_AC6/CMSIS/core" -O3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


