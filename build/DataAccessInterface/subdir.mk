################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../DataAccessInterface/bench_dao.cpp \
../DataAccessInterface/file_accessor.cpp \
../DataAccessInterface/file_bench_dao.cpp \
../DataAccessInterface/file_not_found_exception.cpp \
../DataAccessInterface/file_reader.cpp \
../DataAccessInterface/terminal_bench_dao.cpp 

OBJS += \
./DataAccessInterface/bench_dao.o \
./DataAccessInterface/file_accessor.o \
./DataAccessInterface/file_bench_dao.o \
./DataAccessInterface/file_not_found_exception.o \
./DataAccessInterface/file_reader.o \
./DataAccessInterface/terminal_bench_dao.o 

CPP_DEPS += \
./DataAccessInterface/bench_dao.d \
./DataAccessInterface/file_accessor.d \
./DataAccessInterface/file_bench_dao.d \
./DataAccessInterface/file_not_found_exception.d \
./DataAccessInterface/file_reader.d \
./DataAccessInterface/terminal_bench_dao.d 


# Each subdirectory must supply rules for building sources it contributes
DataAccessInterface/%.o: ../DataAccessInterface/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -O3 -I"../Benchmark" -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


