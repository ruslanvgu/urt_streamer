cmake_minimum_required(VERSION 3.15)
project(urt_streamer)

include_directories(include)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  message("Building on Linux")
  # Добавить настройки сборки для Linux
else()
  message("Building on other system")
  # Установка директорий
  set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
  set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
  set(CMAKE_CXX_STANDARD 11)
  set(Boost_INCLUDE_DIRS c:/boost/include/boost)
  set(Boost_LIBRARIES c:/boost/lib)
  set(Boost_USE_STATIC_LIBS OFF)
  set(Boost_USE_MULTITHREADED ON)
  set(Boost_USE_STATIC_RUNTIME OFF)
  find_package(Boost REQUIRED COMPONENTS system thread)
endif()


# Find Boost library
include_directories(${Boost_INCLUDE_DIRS})
# Link Boost library
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})

# Исходники
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/converter.cpp
    ${SRC_DIR}/reader.cpp
    ${SRC_DIR}/sender.cpp
    ${SRC_DIR}/storage.cpp
    ${SRC_DIR}/manager.cpp
)

# Заголовочные файлы
set(INC_FILES
    ${INC_DIR}/converter.h
    ${INC_DIR}/reader.h
    ${INC_DIR}/sender.h
    ${INC_DIR}/storage.h
    ${INC_DIR}/manager.h
)


# Add your source files
 add_executable(${CMAKE_PROJECT_NAME} ${SRC_DIR} ${INC_DIR})


