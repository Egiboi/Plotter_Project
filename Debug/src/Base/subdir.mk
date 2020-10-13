################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Base/cr_cpp_config.cpp \
../src/Base/cr_startup_lpc15xx.cpp \
../src/Base/init.cpp 

C_SRCS += \
../src/Base/crp.c \
../src/Base/sysinit.c 

OBJS += \
./src/Base/cr_cpp_config.o \
./src/Base/cr_startup_lpc15xx.o \
./src/Base/crp.o \
./src/Base/init.o \
./src/Base/sysinit.o 

CPP_DEPS += \
./src/Base/cr_cpp_config.d \
./src/Base/cr_startup_lpc15xx.d \
./src/Base/init.d 

C_DEPS += \
./src/Base/crp.d \
./src/Base/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/Base/%.o: ../src/Base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\winte\OneDrive\Tiedostot\GitHub\Plotter_Project\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_chip_15xx\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\src\include" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\src\portable\GCC\ARM_CM3" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_chip_15xx\inc\usbd" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Base/%.o: ../src/Base/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\winte\OneDrive\Tiedostot\GitHub\Plotter_Project\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_chip_15xx\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\src\include" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\src\portable\GCC\ARM_CM3" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_chip_15xx\inc\usbd" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


