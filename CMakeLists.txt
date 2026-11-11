cmake_minimum_required(VERSION 3.20)
project(TicTacToe CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tictactoe main.cpp Board.cpp Player.cpp)

if(MINGW)
    target_link_options(tictactoe PRIVATE -static)
endif()
