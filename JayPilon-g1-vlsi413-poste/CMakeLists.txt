cmake_minimum_required(VERSION 3.4)
project(Client CXX)

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

add_executable(Client ${all_SRCS})


find_package(OpenCV 3.4.6 EXACT REQUIRED)

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBRARIES})
else(OpenCV_FOUND)
    message(FATAL ERROR "OpenCV Library Not found!")
endif(OpenCV_FOUND)

# Manually specify include directories for ZBar
include_directories(/usr/include /usr/include/zbar)

# Link the ZBar library
find_library(ZBAR_LIB zbar REQUIRED PATHS /usr/lib /usr/local/lib)

if(ZBAR_LIB)
    target_link_libraries(${PROJECT_NAME} ${ZBAR_LIB})
else()
    message(FATAL_ERROR "ZBar Library Not found!")
endif()