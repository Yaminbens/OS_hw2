################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Account.cpp \
../bank.cpp \
../locker.cpp \
../logs.cpp \
../main.cpp 

O_SRCS += \
../Account.o \
../bank.o \
../locker.o \
../logs.o \
../main.o 

OBJS += \
./Account.o \
./bank.o \
./locker.o \
./logs.o \
./main.o 

CPP_DEPS += \
./Account.d \
./bank.d \
./locker.d \
./logs.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


