cmake_minimum_required(VERSION 3.1)
project(simpleChat)

set(CMAKE_CXX_STANDARD 14)


set(SOURCES
        src/main.cpp
        src/Server.cpp
        src/ClientHandler.cpp
)

set(HEADERS
        src/headers/Server.h
        src/headers/ClientHandler.h
)


add_executable(SIMPLE_CHAT ${SOURCES} ${HEADERS})

add_executable(SIMPLE_CLIENT src/Client.cpp)
