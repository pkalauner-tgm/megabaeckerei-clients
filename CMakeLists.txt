cmake_minimum_required(VERSION 3.2)
project(simulation-mixer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lws2_32")

set(SOURCE_FILES src/main.cpp src/Mixer.cpp src/Mixer.h src/SocketHandler.cpp src/SocketHandler.h)
add_executable(simulation-mixer ${SOURCE_FILES})
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS serialization REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

if(WIN32)
    target_link_libraries(simulation-mixer wsock32 ws2_32 ${Boost_LIBRARIES})
endif()