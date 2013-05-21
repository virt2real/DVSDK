################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../whetstone.c 

OBJS += \
./whetstone.o 

C_DEPS += \
./whetstone.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	$(CROSS_COMPILE)gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


