################################################################################
# MRS Version: 2.4.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Profile/battservice.c \
../Profile/devinfoservice.c \
../Profile/hiddev.c \
../Profile/hidtouchservice.c \
../Profile/scanparamservice.c 

C_DEPS += \
./Profile/battservice.d \
./Profile/devinfoservice.d \
./Profile/hiddev.d \
./Profile/hidtouchservice.d \
./Profile/scanparamservice.d 

OBJS += \
./Profile/battservice.o \
./Profile/devinfoservice.o \
./Profile/hiddev.o \
./Profile/hidtouchservice.o \
./Profile/scanparamservice.o 

DIR_OBJS += \
./Profile/*.o \

DIR_DEPS += \
./Profile/*.d \

DIR_EXPANDS += \
./Profile/*.253r.expand \


# Each subdirectory must supply rules for building sources it contributes
Profile/%.o: ../Profile/%.c
	@	riscv-wch-elf-gcc -march=rv32imc_zba_zbb_zbc_zbs_xw -mabi=ilp32 -mcmodel=medany -msmall-data-limit=8 -mno-save-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common --param=highcode-gen-section-name=1 -g -DDEBUG=0 -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Startup" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/APP/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HID_Touch/Profile/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/StdPeriphDriver/inc" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/HAL/include" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/Ld" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/BLE/LIB" -I"d:/Data/Document/Peripheral/wch/CH585EVT/EVT/EXAM/SRC/RVMSIS" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

