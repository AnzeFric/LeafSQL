cmake_minimum_required(VERSION 4.1)
project(LeafSQL)

set(CMAKE_CXX_STANDARD 20)

add_executable(LeafSQL main.cpp
        QueryParser/QueryParser.cpp
        QueryParser/QueryParser.h
        Token.h
        Lexer/Lexer.cpp
        Lexer/Lexer.h
        SelectFromStatement.cpp
        SelectFromStatement.h
)
