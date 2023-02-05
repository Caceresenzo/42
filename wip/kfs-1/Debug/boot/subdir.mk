################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../boot/crt0.o \
../boot/crti.o \
../boot/crtn.o \
../boot/head.o 

S_UPPER_SRCS += \
../boot/crti.S \
../boot/crtn.S \
../boot/head.S 

OBJS += \
./boot/crti.o \
./boot/crtn.o \
./boot/head.o 


# Each subdirectory must supply rules for building sources it contributes
boot/%.o: ../boot/%.S boot/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-boot

clean-boot:
	-$(RM) ./boot/crti.o ./boot/crtn.o ./boot/head.o

.PHONY: clean-boot

