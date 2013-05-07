cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED QtCore)
find_package(OpenCV REQUIRED)

include_directories(${QT_INCLUDES} ${OPENCV_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
add_definitions(${QT_DEFINITIONS})

set(DataLogger_SRCS datalogger.cpp)
qt4_automoc(${DataLogger_SRCS})
ADD_LIBRARY(DataLogger STATIC ${DataLogger_SRCS})

set(LoggerModule_SRCS loggermodule.cpp)
qt4_automoc(${LoggerModule_SRCS})
ADD_LIBRARY(LoggerModule STATIC ${LoggerModule_SRCS})

set(ImageLogger_SRCS imagelogger.cpp)
qt4_automoc(${ImageLogger_SRCS})
ADD_LIBRARY(ImageLogger STATIC ${ImageLogger_SRCS})

set(CombinedLogger_SRCS combinedlogger.cpp)
qt4_automoc(${CombinedLogger_SRCS})
ADD_LIBRARY(CombinedLogger STATIC ${CombinedLogger_SRCS})

	   
TARGET_LINK_LIBRARIES(CombinedLogger ${QT_QTCORE_LIBRARY} ${OpenCV_LIBS})
