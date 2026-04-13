################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/hidtouch.c \
../APP/hidtouch_main.c 

C_DEPS += \
./APP/hidtouch.d \
./APP/hidtouch_main.d 

OBJS += \
./APP/hidtouch.o \
./APP/hidtouch_main.o 

DIR_OBJS += \
./APP/*.o \

DIR_DEPS += \
./APP/*.d \

DIR_EXPANDS += \
./APP/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c
	@	riscv-wch-elf-gcc -march=rv32imc_zba_zbb_zbc_zbs_xw -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common --param=highcode-gen-section-name=1 -g -DDEBUG=0 -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Startup" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/APP/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/Profile/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/StdPeriphDriver/inc" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Ld" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/LIB" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

