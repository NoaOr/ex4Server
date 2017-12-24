cmake_minimum_required(VERSION 3.8)
project(ex4Server)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Server.cpp Server.h FileReader.cpp
        FileReader.h Command.cpp Command.h CommandsManager.cpp CommandsManager.h
        ListGamesCommand.cpp ListGamesCommand.h StartCommand.cpp
        StartCommand.h Game.cpp Game.h JoinCommand.cpp JoinCommand.h)

set(CMAKE_CXX_FLAGS -pthread)
add_executable(ex4Server ${SOURCE_FILES})