################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../kernel/main.cpp 

O_SRCS += \
../kernel/kern.o \
../kernel/main.o 

CPP_DEPS += \
./kernel/main.d 

OBJS += \
./kernel/main.o 


# Each subdirectory must supply rules for building sources it contributes
kernel/%.o: ../kernel/%.cpp kernel/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-kernel

clean-kernel:
	-$(RM) ./kernel/main.d ./kernel/main.o

.PHONY: clean-kernel

