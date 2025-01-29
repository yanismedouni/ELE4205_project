cmake_minimum_required(VERSION 3.4)
project(Projet CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(Projet ${all_SRCS})


find_package(OpenCV 3.1.0 EXACT REQUIRED PATHS /opt/poky/2.1.3/sysroots/aarch64-poky-linux/*)

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})
else(OpenCV_FOUND)
    message(FATAL ERROR "OpenCV Library Not found!")
endif(OpenCV_FOUND)
