################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DigitalIoPin.cpp \
../src/Fmutex.cpp \
../src/Laser.cpp \
../src/LpcUart.cpp \
../src/Parser.cpp \
../src/Servo.cpp \
../src/XYdriver.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc15xx.cpp \
../src/mainP.cpp 

C_SRCS += \
../src/ITM_write.c \
../src/cdc_desc.c \
../src/cdc_main.c \
../src/cdc_vcom.c \
../src/crp.c \
../src/heap_lock_monitor.c \
../src/sysinit.c 

OBJS += \
./src/DigitalIoPin.o \
./src/Fmutex.o \
./src/ITM_write.o \
./src/Laser.o \
./src/LpcUart.o \
./src/Parser.o \
./src/Servo.o \
./src/XYdriver.o \
./src/cdc_desc.o \
./src/cdc_main.o \
./src/cdc_vcom.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc15xx.o \
./src/crp.o \
./src/heap_lock_monitor.o \
./src/mainP.o \
./src/sysinit.o 

CPP_DEPS += \
./src/DigitalIoPin.d \
./src/Fmutex.d \
./src/Laser.d \
./src/LpcUart.d \
./src/Parser.d \
./src/Servo.d \
./src/XYdriver.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc15xx.d \
./src/mainP.d 

C_DEPS += \
./src/ITM_write.d \
./src/cdc_desc.d \
./src/cdc_main.d \
./src/cdc_vcom.d \
./src/crp.d \
./src/heap_lock_monitor.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"D:\Githubin jutut\Plotter_Project\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\lpc_board_nxp_lpcxpresso_1549\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\lpc_chip_15xx\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\FreeRTOS\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\FreeRTOS\src\include" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\FreeRTOS\src\portable\GCC\ARM_CM3" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\lpc_chip_15xx\inc\usbd" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"D:\Githubin jutut\Plotter_Project\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\lpc_board_nxp_lpcxpresso_1549\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\lpc_chip_15xx\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\FreeRTOS\inc" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\FreeRTOS\src\include" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\FreeRTOS\src\portable\GCC\ARM_CM3" -I"D:\metropoliaohjelmat\MCUXpressoIDE_11.0.0_2516\ide\Signalboardex2\lpc_chip_15xx\inc\usbd" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


