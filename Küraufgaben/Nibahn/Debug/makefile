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
Nibahn.lss \

FLASH_IMAGE += \
Nibahn.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Nibahn.elf secondary-outputs

# Tool invocations
Nibahn.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Nibahn.map -L/home/defaultuser/Documents/niboLib/lib -mmcu=atmega128 -o "Nibahn.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Nibahn.lss: Nibahn.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Nibahn.elf  >"Nibahn.lss"
	@echo 'Finished building: $@'
	@echo ' '

Nibahn.hex: Nibahn.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Nibahn.elf  "Nibahn.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Nibahn.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega128 Nibahn.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Nibahn.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
