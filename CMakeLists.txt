cmake_minimum_required(VERSION 4.2)
project(todo_list_manager)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB LOGGER_FILES
        logger.cpp
        logger.h
        pch.h
        task.cpp
        task.h
        task_manager.cpp
        task_manager.h
        command.cpp
        command.h
)

add_library(tdlm_static STATIC ${LOGGER_FILES}) # 输出到 build/lib
add_library(tdlm_shared SHARED ${LOGGER_FILES})

add_executable(todo_list_manager main.cpp ${LOGGER_FILES})