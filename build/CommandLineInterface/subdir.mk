################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommandLineInterface/commandline_reader.cpp \
../CommandLineInterface/commandline_utility.cpp 

OBJS += \
./CommandLineInterface/commandline_reader.o \
./CommandLineInterface/commandline_utility.o 

CPP_DEPS += \
./CommandLineInterface/commandline_reader.d \
./CommandLineInterface/commandline_utility.d 


# Each subdirectory must supply rules for building sources it contributes
CommandLineInterface/%.o: ../CommandLineInterface/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


