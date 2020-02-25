################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/distance.c \
../src/drive.c \
../src/main.c \
../src/presentation.c \
../src/start.c 

OBJS += \
./src/distance.o \
./src/drive.o \
./src/main.o \
./src/presentation.o \
./src/start.o 

C_DEPS += \
./src/distance.d \
./src/drive.d \
./src/main.d \
./src/presentation.d \
./src/start.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I/home/defaultuser/Documents/niboLib/include -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega128 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


