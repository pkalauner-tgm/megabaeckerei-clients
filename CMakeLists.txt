cmake_minimum_required(VERSION 3.2)
project(simulation)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lws2_32")

set(SOURCE_FILES src/main.cpp src/WaterTank.cpp src/WaterTank.h src/SocketHandler.cpp src/SocketHandler.h)
add_executable(simulation ${SOURCE_FILES})
if(WIN32)
    target_link_libraries(simulation wsock32 ws2_32)
endif()