################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/LIB/ble_task_scheduler.S 

S_UPPER_DEPS += \
./LIB/ble_task_scheduler.d 

OBJS += \
./LIB/ble_task_scheduler.o 

DIR_OBJS += \
./LIB/*.o \

DIR_DEPS += \
./LIB/*.d \

DIR_EXPANDS += \
./LIB/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
LIB/ble_task_scheduler.o: d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/LIB/ble_task_scheduler.S
	@	riscv-wch-elf-gcc -march=rv32imc_zba_zbb_zbc_zbs_xw -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common --param=highcode-gen-section-name=1 -g -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

