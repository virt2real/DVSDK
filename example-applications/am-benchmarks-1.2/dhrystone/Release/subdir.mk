################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../dhrystone.c 

OBJS += \
./dhrystone.o 

C_DEPS += \
./dhrystone.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	$(CROSS_COMPILE)gcc -O3 -c -DTIME -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


