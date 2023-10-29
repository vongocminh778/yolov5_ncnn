cmake_minimum_required(VERSION 3.5)

project(yolov5)
set(CMAKE_BUILD_TYPE Release)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0) 
pkg_check_modules(GST REQUIRED
                    gstreamer-1.0
                    gstreamer-video-1.0
                    gstreamer-app-1.0
                    )

include_directories(${CMAKE_SOURCE_DIR}/seriallib)

# OpenCV
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV Libs: \n${OpenCV_LIBS}\n")
message(STATUS "OpenCV Libraries: \n${OpenCV_LIBRARIES}\n")
message(STATUS "OpenCV Headers: \n${OpenCV_INCLUDE_DIRS}\n")

# NCNN
set(ncnn_DIR /home/minhmap/DATA/8.Project/ncnn/build/install/lib/cmake/ncnn)
find_package(ncnn REQUIRED)
                    
                    
find_package(OpenMP REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

####################### INCLUDE   #############################

include_directories(${INCLUDE_DIRS} ${GST_INCLUDE_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(${PROJECT_NAME} main.cpp yoloV5.cpp ${CMAKE_SOURCE_DIR}/seriallib/serialib.cpp)

target_link_libraries(${PROJECT_NAME} ncnn ${OpenCV_LIBS} ${GST_LIBRARIES})

# cmake_minimum_required(VERSION 3.10)
# project(UART_Serial)

# set(CMAKE_C_STANDARD 99)

# include_directories(${CMAKE_SOURCE_DIR}/seriallib)

# add_executable(UART_Serial PC2arduino.cpp ${CMAKE_SOURCE_DIR}/seriallib/serialib.cpp)

# target_link_libraries(UART_Serial PRIVATE serialport)
