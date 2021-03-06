################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/TWR-MCF5225X_sysinit.c" \
"../Sources/console_io_cf.c" \
"../Sources/dtim.c" \
"../Sources/exceptions.c" \
"../Sources/i2c.c" \
"../Sources/main.c" \
"../Sources/oct_nunchuk.c" \
"../Sources/pit.c" \
"../Sources/uart_support.c" \

C_SRCS += \
../Sources/TWR-MCF5225X_sysinit.c \
../Sources/console_io_cf.c \
../Sources/dtim.c \
../Sources/exceptions.c \
../Sources/i2c.c \
../Sources/main.c \
../Sources/oct_nunchuk.c \
../Sources/pit.c \
../Sources/uart_support.c \

S_SRCS += \
../Sources/int.s \

S_SRCS_QUOTED += \
"../Sources/int.s" \

OBJS += \
./Sources/TWR-MCF5225X_sysinit_c.obj \
./Sources/console_io_cf_c.obj \
./Sources/dtim_c.obj \
./Sources/exceptions_c.obj \
./Sources/i2c_c.obj \
./Sources/int_s.obj \
./Sources/main_c.obj \
./Sources/oct_nunchuk_c.obj \
./Sources/pit_c.obj \
./Sources/uart_support_c.obj \

OBJS_QUOTED += \
"./Sources/TWR-MCF5225X_sysinit_c.obj" \
"./Sources/console_io_cf_c.obj" \
"./Sources/dtim_c.obj" \
"./Sources/exceptions_c.obj" \
"./Sources/i2c_c.obj" \
"./Sources/int_s.obj" \
"./Sources/main_c.obj" \
"./Sources/oct_nunchuk_c.obj" \
"./Sources/pit_c.obj" \
"./Sources/uart_support_c.obj" \

C_DEPS += \
./Sources/TWR-MCF5225X_sysinit_c.d \
./Sources/console_io_cf_c.d \
./Sources/dtim_c.d \
./Sources/exceptions_c.d \
./Sources/i2c_c.d \
./Sources/main_c.d \
./Sources/oct_nunchuk_c.d \
./Sources/pit_c.d \
./Sources/uart_support_c.d \

OBJS_OS_FORMAT += \
./Sources/TWR-MCF5225X_sysinit_c.obj \
./Sources/console_io_cf_c.obj \
./Sources/dtim_c.obj \
./Sources/exceptions_c.obj \
./Sources/i2c_c.obj \
./Sources/int_s.obj \
./Sources/main_c.obj \
./Sources/oct_nunchuk_c.obj \
./Sources/pit_c.obj \
./Sources/uart_support_c.obj \

C_DEPS_QUOTED += \
"./Sources/TWR-MCF5225X_sysinit_c.d" \
"./Sources/console_io_cf_c.d" \
"./Sources/dtim_c.d" \
"./Sources/exceptions_c.d" \
"./Sources/i2c_c.d" \
"./Sources/main_c.d" \
"./Sources/oct_nunchuk_c.d" \
"./Sources/pit_c.d" \
"./Sources/uart_support_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/TWR-MCF5225X_sysinit_c.obj: ../Sources/TWR-MCF5225X_sysinit.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/TWR-MCF5225X_sysinit.args" -o "Sources/TWR-MCF5225X_sysinit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/console_io_cf_c.obj: ../Sources/console_io_cf.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/console_io_cf.args" -o "Sources/console_io_cf_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/dtim_c.obj: ../Sources/dtim.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/dtim.args" -o "Sources/dtim_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/exceptions_c.obj: ../Sources/exceptions.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/exceptions.args" -o "Sources/exceptions_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/i2c_c.obj: ../Sources/i2c.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/i2c.args" -o "Sources/i2c_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/int_s.obj: ../Sources/int.s
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ColdFire Assembler'
	"$(CF_ToolsDirEnv)/mwasmmcf" @@"Sources/int.args" -o "Sources/int_s.obj" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/main.args" -o "Sources/main_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/oct_nunchuk_c.obj: ../Sources/oct_nunchuk.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/oct_nunchuk.args" -o "Sources/oct_nunchuk_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/pit_c.obj: ../Sources/pit.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/pit.args" -o "Sources/pit_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/uart_support_c.obj: ../Sources/uart_support.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ColdFire Compiler'
	"$(CF_ToolsDirEnv)/mwccmcf" @@"Sources/uart_support.args" -o "Sources/uart_support_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '


