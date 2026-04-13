################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include StdPeriphDriver/subdir.mk
-include Startup/subdir.mk
-include Profile/subdir.mk
-include LIB/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
HID_Touch.hex \

SECONDARY_LIST += \
HID_Touch.lst \

SECONDARY_SIZE += \
HID_Touch.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: HID_Touch.elf secondary-outputs

# Tool invocations
HID_Touch.elf: $(OBJS) $(USER_OBJS_ESCAPE)
	@	riscv-wch-elf-gcc -march=rv32imc_zba_zbb_zbc_zbs_xw -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common --param=highcode-gen-section-name=1 -g -T "d:\Data\Document\Peripheral\wch\CH585EVT\EVT\EXAM\SRC\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"d:\Data\Document\Peripheral\wch\CH585EVT\EVT\EXAM\BLE\HID_Touch" -L"d:\Data\Document\Peripheral\wch\CH585EVT\EVT\EXAM\BLE\LIB" -L"d:\Data\Document\Peripheral\wch\CH585EVT\EVT\EXAM\SRC\StdPeriphDriver" -Xlinker --print-memory-usage -Wl,-Map,"HID_Touch.map" --specs=nano.specs --specs=nosys.specs -o "HID_Touch.elf" $(OBJS) $(LIBS)
HID_Touch.hex: HID_Touch.elf
	@	riscv-wch-elf-objcopy -O ihex "HID_Touch.elf" "HID_Touch.hex"
HID_Touch.lst: HID_Touch.elf
	@	riscv-wch-elf-objdump --source --all-headers --demangle -M xw --line-numbers --wide "HID_Touch.elf" > "HID_Touch.lst"
HID_Touch.siz: HID_Touch.elf
	riscv-wch-elf-size --format=berkeley "HID_Touch.elf"

# Other Targets
clean:
	-$(RM) $(DIR_OBJS) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE) HID_Touch.elf
	-$(RM) $(DIR_EXPANDS) $(CALLGRAPH_DOT)
	-$(RM) $(DIR_DEPS)
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets