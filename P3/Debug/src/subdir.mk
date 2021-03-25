################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/D8Led.c \
../src/button.c \
../src/gpio.c \
../src/intcontroller.c \
../src/keyboard.c \
../src/leds.c \
../src/main.c \
../src/timer.c \
../src/utils.c 

S_UPPER_SRCS += \
../src/init.S 

OBJS += \
./src/D8Led.o \
./src/button.o \
./src/gpio.o \
./src/init.o \
./src/intcontroller.o \
./src/keyboard.o \
./src/leds.o \
./src/main.o \
./src/timer.o \
./src/utils.o 

C_DEPS += \
./src/D8Led.d \
./src/button.d \
./src/gpio.d \
./src/intcontroller.d \
./src/keyboard.d \
./src/leds.d \
./src/main.d \
./src/timer.d \
./src/utils.d 

S_UPPER_DEPS += \
./src/init.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


