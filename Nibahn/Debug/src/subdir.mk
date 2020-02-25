################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Nibahn.c \
../src/Nibo_actions.c \
../src/protokoll.c \
../src/xBee.c 

OBJS += \
./src/Nibahn.o \
./src/Nibo_actions.o \
./src/protokoll.o \
./src/xBee.o 

C_DEPS += \
./src/Nibahn.d \
./src/Nibo_actions.d \
./src/protokoll.d \
./src/xBee.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/defaultuser/Documents/niboLib/include -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


