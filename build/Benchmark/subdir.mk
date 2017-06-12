################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Benchmark/bench_mark.cpp \
../Benchmark/bench_mark_management.cpp \
../Benchmark/benchmark_exception.cpp \
../Benchmark/data_object.cpp \
../Benchmark/neutral.cpp \
../Benchmark/running.cpp \
../Benchmark/state.cpp \
../Benchmark/stopped.cpp \
../Benchmark/time_stop.cpp \
../Benchmark/wrong_time_exception.cpp 

OBJS += \
./Benchmark/bench_mark.o \
./Benchmark/bench_mark_management.o \
./Benchmark/benchmark_exception.o \
./Benchmark/data_object.o \
./Benchmark/neutral.o \
./Benchmark/running.o \
./Benchmark/state.o \
./Benchmark/stopped.o \
./Benchmark/time_stop.o \
./Benchmark/wrong_time_exception.o 

CPP_DEPS += \
./Benchmark/bench_mark.d \
./Benchmark/bench_mark_management.d \
./Benchmark/benchmark_exception.d \
./Benchmark/data_object.d \
./Benchmark/neutral.d \
./Benchmark/running.d \
./Benchmark/state.d \
./Benchmark/stopped.d \
./Benchmark/time_stop.d \
./Benchmark/wrong_time_exception.d 


# Each subdirectory must supply rules for building sources it contributes
Benchmark/%.o: ../Benchmark/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -I"../CryptoInterface" -I"../DataAccessInterface" -I"../Benchmark" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


