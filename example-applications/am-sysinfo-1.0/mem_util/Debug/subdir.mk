################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mem_util.c 

OBJS += \
./mem_util.o 

C_DEPS += \
./mem_util.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Linux GCC C Compiler'
	$(CROSS_COMPILE)gcc -O0 -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm926ej-s -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


