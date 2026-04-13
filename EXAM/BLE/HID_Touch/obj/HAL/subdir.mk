################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/MCU.c \
d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/RTC.c \
d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/SLEEP.c 

C_DEPS += \
./HAL/MCU.d \
./HAL/RTC.d \
./HAL/SLEEP.d 

OBJS += \
./HAL/MCU.o \
./HAL/RTC.o \
./HAL/SLEEP.o 

DIR_OBJS += \
./HAL/*.o \

DIR_DEPS += \
./HAL/*.d \

DIR_EXPANDS += \
./HAL/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
HAL/MCU.o: d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/MCU.c
	@	riscv-wch-elf-gcc -march=rv32imc_zba_zbb_zbc_zbs_xw -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common --param=highcode-gen-section-name=1 -g -DDEBUG=0 -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Startup" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/APP/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/Profile/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/StdPeriphDriver/inc" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Ld" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/LIB" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
HAL/RTC.o: d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/RTC.c
	@	riscv-wch-elf-gcc -march=rv32imc_zba_zbb_zbc_zbs_xw -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common --param=highcode-gen-section-name=1 -g -DDEBUG=0 -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Startup" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/APP/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/Profile/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/StdPeriphDriver/inc" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Ld" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/LIB" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
HAL/SLEEP.o: d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/SLEEP.c
	@	riscv-wch-elf-gcc -march=rv32imc_zba_zbb_zbc_zbs_xw -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common --param=highcode-gen-section-name=1 -g -DDEBUG=0 -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Startup" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/APP/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/Profile/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/StdPeriphDriver/inc" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Ld" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/LIB" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

