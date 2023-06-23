cmake_minimum_required(VERSION 3.15)
project(urt_streamer)


include_directories(include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
#enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  message("########Building on Linux")
  # Установка директорий
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lstdc++fs")

else()
  message("#########Building on other system")

  #set(Boost_USE_STATIC_LIBS ON)
  #set(Boost_USE_MULTITHREADED ON)
  #set(BOOST_ROOT "C:/boost/include/boost")
  #set(BOOST_LIBRARYDIR "C:/boost/lib")
  #find_package(Boost REQUIRED COMPONENTS system thread)
  #include_directories(${Boost_INCLUDE_DIRS})
endif()



# Исходники
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/converter.cpp
    ${SRC_DIR}/reader.cpp
    ${SRC_DIR}/sender.cpp
    ${SRC_DIR}/storage.cpp
    ${SRC_DIR}/manager.cpp
    ${SRC_DIR}/settings.cpp
)

# Заголовочные файлы
set(INC_FILES
    ${INC_DIR}/converter.h
    ${INC_DIR}/reader.h
    ${INC_DIR}/sender.h
    ${INC_DIR}/storage.h
    ${INC_DIR}/manager.h
    ${INC_DIR}/settings.h
)

# Add your source files
 #add_executable(${CMAKE_PROJECT_NAME} ${SRC_DIR} ${INC_DIR})
 add_executable(urt_streamer ${SRC_FILES} ${INC_FILES})
 target_link_libraries(${PROJECT_NAME} stdc++fs)
# target_link_libraries(${CMAKE_PROJECT_NAME} Boost::system Boost::thread)

