cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER avr-gcc)
set(CMAKE_OBJCOPY avr-objcopy)
set(CMAKE_SIZE avr-size)

project(HC-SR04 C)

set(MCU atmega328p)
set(F_CPU 16000000UL)

add_executable(HC-SR04.elf
        src/main.c
        src/main.h
        include/Pin.h
        include/Pin.c
)

target_compile_options(HC-SR04.elf PRIVATE
        -mmcu=${MCU}
        -DF_CPU=${F_CPU}
        -Os
        -Wall
        -Wextra
        -std=c11
)

target_link_options(HC-SR04.elf PRIVATE
        -mmcu=${MCU}
)

add_custom_command(
        TARGET HC-SR04.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom
        HC-SR04.elf HC-SR04.hex
        COMMAND ${CMAKE_SIZE} HC-SR04.elf
)

add_custom_target(flash
        COMMAND avrdude -c arduino -p m328p -P COM7 -b 115200
        -U flash:w:HC-SR04.hex
        DEPENDS HC-SR04.elf
)