################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../inc/Laser.cpp 

OBJS += \
./inc/Laser.o 

CPP_DEPS += \
./inc/Laser.d 


# Each subdirectory must supply rules for building sources it contributes
inc/%.o: ../inc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -std=c++11 -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\usb_cdc\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_chip_15xx\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_chip_15xx\inc\usbd" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\src\include" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\src\portable\GCC\ARM_CM3" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


