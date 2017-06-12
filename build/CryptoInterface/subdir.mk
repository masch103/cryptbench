################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CryptoInterface/hash_utility.cpp \
../CryptoInterface/hashfunction.cpp \
../CryptoInterface/hashfunction_factory.cpp \
../CryptoInterface/md5.cpp \
../CryptoInterface/ripemd160.cpp \
../CryptoInterface/sha1.cpp \
../CryptoInterface/sha224_256.cpp \
../CryptoInterface/sha3.cpp \
../CryptoInterface/sha384_512.cpp \
../CryptoInterface/stream_reader.cpp \
../CryptoInterface/whirl_constants.cpp \
../CryptoInterface/whirlpool.cpp 

OBJS += \
./CryptoInterface/hash_utility.o \
./CryptoInterface/hashfunction.o \
./CryptoInterface/hashfunction_factory.o \
./CryptoInterface/md5.o \
./CryptoInterface/ripemd160.o \
./CryptoInterface/sha1.o \
./CryptoInterface/sha224_256.o \
./CryptoInterface/sha3.o \
./CryptoInterface/sha384_512.o \
./CryptoInterface/stream_reader.o \
./CryptoInterface/whirl_constants.o \
./CryptoInterface/whirlpool.o 

CPP_DEPS += \
./CryptoInterface/hash_utility.d \
./CryptoInterface/hashfunction.d \
./CryptoInterface/hashfunction_factory.d \
./CryptoInterface/md5.d \
./CryptoInterface/ripemd160.d \
./CryptoInterface/sha1.d \
./CryptoInterface/sha224_256.d \
./CryptoInterface/sha3.d \
./CryptoInterface/sha384_512.d \
./CryptoInterface/stream_reader.d \
./CryptoInterface/whirl_constants.d \
./CryptoInterface/whirlpool.d 


# Each subdirectory must supply rules for building sources it contributes
CryptoInterface/%.o: ../CryptoInterface/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -I"../DataAccessInterface" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


