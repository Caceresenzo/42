################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../drivers/keyboard.cpp \
../drivers/timer.cpp \
../drivers/vga.cpp 

O_SRCS += \
../drivers/keyboard.o \
../drivers/vga.o 

CPP_DEPS += \
./drivers/keyboard.d \
./drivers/timer.d \
./drivers/vga.d 

OBJS += \
./drivers/keyboard.o \
./drivers/timer.o \
./drivers/vga.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.cpp drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/keyboard.d ./drivers/keyboard.o ./drivers/timer.d ./drivers/timer.o ./drivers/vga.d ./drivers/vga.o

.PHONY: clean-drivers

