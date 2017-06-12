################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommandHandling/basic_command.cpp \
../CommandHandling/bench_command.cpp \
../CommandHandling/command.cpp \
../CommandHandling/command_engine.cpp \
../CommandHandling/commandline_utility.cpp \
../CommandHandling/help_command.cpp \
../CommandHandling/list_command.cpp 

OBJS += \
./CommandHandling/basic_command.o \
./CommandHandling/bench_command.o \
./CommandHandling/command.o \
./CommandHandling/command_engine.o \
./CommandHandling/commandline_utility.o \
./CommandHandling/help_command.o \
./CommandHandling/list_command.o 

CPP_DEPS += \
./CommandHandling/basic_command.d \
./CommandHandling/bench_command.d \
./CommandHandling/command.d \
./CommandHandling/command_engine.d \
./CommandHandling/commandline_utility.d \
./CommandHandling/help_command.d \
./CommandHandling/list_command.d 


# Each subdirectory must supply rules for building sources it contributes
CommandHandling/%.o: ../CommandHandling/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -I"../DataAccessInterface" -I"../CryptoInterface" -I"../Benchmark" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


