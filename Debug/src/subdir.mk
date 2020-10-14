################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Main.cpp 

OBJS += \
./src/Main.o 

CPP_DEPS += \
./src/Main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
<<<<<<< HEAD
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\winte\OneDrive\Tiedostot\GitHub\Plotter_Project\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_chip_15xx\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\inc" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\src\include" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\FreeRTOS\src\portable\GCC\ARM_CM3" -I"C:\Users\winte\Documents\MCUXpressoIDE_11.0.0_2516\USB2\lpc_chip_15xx\inc\usbd" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
=======
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\danie\Documents\GitHub\Plotter_Project\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\lpc_chip_15xx\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\FreeRTOS\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\FreeRTOS\src\include" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\FreeRTOS\src\portable\GCC\ARM_CM3" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\Labs" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\lpc_chip_15xx\inc\usbd" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
>>>>>>> parent of fd8aefd... Merge branch 'Testi' of https://github.com/Egiboi/Plotter_Project into Testi
	@echo 'Finished building: $<'
	@echo ' '


