################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../attuatore.c \
../funzioni_backend.c \
../funzioni_frontend.c 

OBJS += \
./attuatore.o \
./funzioni_backend.o \
./funzioni_frontend.o 

C_DEPS += \
./attuatore.d \
./funzioni_backend.d \
./funzioni_frontend.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include -O0 -g3 -pedantic -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


