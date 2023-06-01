cmake_minimum_required(VERSION 3.15)
project(urt_streamer)

include_directories(include)

# Установка директорий
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Исходники
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/converter.cpp
    ${SRC_DIR}/reader.cpp
    ${SRC_DIR}/sender.cpp
    ${SRC_DIR}/storage.cpp
)

# Заголовочные файлы
set(INC_FILES
    ${INC_DIR}/converter.h
    ${INC_DIR}/reader.h
    ${INC_DIR}/sender.h
    ${INC_DIR}/storage.h
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES} ${INC_FILES})
