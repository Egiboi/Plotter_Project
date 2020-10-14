################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Communication/Fmutex.cpp \
../src/Communication/LpcUart.cpp \
../src/Communication/SerialUart.cpp 

C_SRCS += \
../src/Communication/ITM_write.c \
../src/Communication/cdc_desc.c \
../src/Communication/cdc_main.c \
../src/Communication/cdc_vcom.c 

OBJS += \
./src/Communication/Fmutex.o \
./src/Communication/ITM_write.o \
./src/Communication/LpcUart.o \
./src/Communication/SerialUart.o \
./src/Communication/cdc_desc.o \
./src/Communication/cdc_main.o \
./src/Communication/cdc_vcom.o 

CPP_DEPS += \
./src/Communication/Fmutex.d \
./src/Communication/LpcUart.d \
./src/Communication/SerialUart.d 

C_DEPS += \
./src/Communication/ITM_write.d \
./src/Communication/cdc_desc.d \
./src/Communication/cdc_main.d \
./src/Communication/cdc_vcom.d 


# Each subdirectory must supply rules for building sources it contributes
src/Communication/%.o: ../src/Communication/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\danie\Documents\GitHub\Plotter_Project\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\lpc_chip_15xx\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\FreeRTOS\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\FreeRTOS\src\include" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\FreeRTOS\src\portable\GCC\ARM_CM3" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\Labs" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\lpc_chip_15xx\inc\usbd" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Communication/%.o: ../src/Communication/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"C:\Users\danie\Documents\GitHub\Plotter_Project\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\lpc_board_nxp_lpcxpresso_1549\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\lpc_chip_15xx\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\FreeRTOS\inc" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\FreeRTOS\src\include" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\FreeRTOS\src\portable\GCC\ARM_CM3" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\Labs" -I"C:\Users\danie\Documents\Koulu\Vuosi 3\Periodi 1\ARM\MCU\lpc_chip_15xx\inc\usbd" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


