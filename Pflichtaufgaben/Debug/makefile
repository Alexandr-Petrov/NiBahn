################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
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

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Pflichtaufgaben.lss \

FLASH_IMAGE += \
Pflichtaufgaben.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Pflichtaufgaben.elf secondary-outputs

# Tool invocations
Pflichtaufgaben.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Pflichtaufgaben.map -L/home/defaultuser/Documents/niboLib/lib -mmcu=atmega128 -o "Pflichtaufgaben.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Pflichtaufgaben.lss: Pflichtaufgaben.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Pflichtaufgaben.elf  >"Pflichtaufgaben.lss"
	@echo 'Finished building: $@'
	@echo ' '

Pflichtaufgaben.hex: Pflichtaufgaben.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Pflichtaufgaben.elf  "Pflichtaufgaben.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Pflichtaufgaben.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 Pflichtaufgaben.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Pflichtaufgaben.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
