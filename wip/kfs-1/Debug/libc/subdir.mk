################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libc/stdio.cpp 

C_SRCS += \
../libc/string.c 

O_SRCS += \
../libc/stdio.o \
../libc/string.o 

CPP_DEPS += \
./libc/stdio.d 

C_DEPS += \
./libc/string.d 

OBJS += \
./libc/stdio.o \
./libc/string.o 


# Each subdirectory must supply rules for building sources it contributes
libc/%.o: ../libc/%.cpp libc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

libc/%.o: ../libc/%.c libc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	x86_64-w64-mingw32-gcc.exe -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libc

clean-libc:
	-$(RM) ./libc/stdio.d ./libc/stdio.o ./libc/string.d ./libc/string.o

.PHONY: clean-libc

