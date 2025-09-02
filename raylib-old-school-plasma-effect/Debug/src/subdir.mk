################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/raylib-old-school-plasma-effect.cpp 

CPP_DEPS += \
./src/raylib-old-school-plasma-effect.d 

OBJS += \
./src/raylib-old-school-plasma-effect.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++26 -I/usr/local/include -I/home/descourt/Téléchargements/raylib-master/src -O0 -g3 -Wall -c -fmessage-length=0 -v -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/raylib-old-school-plasma-effect.d ./src/raylib-old-school-plasma-effect.o

.PHONY: clean-src

