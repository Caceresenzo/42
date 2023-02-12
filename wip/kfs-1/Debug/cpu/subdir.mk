################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cpu/gdt.cpp \
../cpu/idt.cpp \
../cpu/interrupt.cpp \
../cpu/io.cpp \
../cpu/multiboot.cpp \
../cpu/pit.cpp 

O_SRCS += \
../cpu/gdt.o \
../cpu/idt.o \
../cpu/interrupt.o \
../cpu/io.o \
../cpu/pit.o 

CPP_DEPS += \
./cpu/gdt.d \
./cpu/idt.d \
./cpu/interrupt.d \
./cpu/io.d \
./cpu/multiboot.d \
./cpu/pit.d 

OBJS += \
./cpu/gdt.o \
./cpu/idt.o \
./cpu/interrupt.o \
./cpu/io.o \
./cpu/multiboot.o \
./cpu/pit.o 


# Each subdirectory must supply rules for building sources it contributes
cpu/%.o: ../cpu/%.cpp cpu/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-cpu

clean-cpu:
	-$(RM) ./cpu/gdt.d ./cpu/gdt.o ./cpu/idt.d ./cpu/idt.o ./cpu/interrupt.d ./cpu/interrupt.o ./cpu/io.d ./cpu/io.o ./cpu/multiboot.d ./cpu/multiboot.o ./cpu/pit.d ./cpu/pit.o

.PHONY: clean-cpu

