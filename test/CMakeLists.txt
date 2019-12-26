cmake_minimum_required(VERSION 3.0)

#-----------------------------------------------------------------------------#
find_package(Threads REQUIRED)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_CXX_COMPILER arm-linux-g++)
set(CMAKE_C_COMPILER arm-linux-gcc)
#-----------------------------------------------------------------------------#

set(TARGET testbench)

add_executable(${TARGET} test.cpp ../src/uart.cpp)
target_link_libraries(${TARGET} /home/trongphuong/Work/BBB/libraries/crc32/bin/libcrc32.a)
target_include_directories(${TARGET} PUBLIC ../include
							/home/trongphuong/Work/BBB/libraries/crc32/include)

#-----------------------------------------------------------------------------#
target_compile_options(${TARGET} PUBLIC -std=gnu++11
										-Wall
										-Werror
										-O2
)
#-----------------------------------------------------------------------------#
install(TARGETS ${TARGET} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)