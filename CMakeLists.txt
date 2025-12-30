cmake_minimum_required(VERSION 4.1)
project(LeafSQL)

set(CMAKE_CXX_STANDARD 20)

add_executable(LeafSQL main.cpp
        QueryParser/QueryParser.cpp
        QueryParser/QueryParser.h
        QueryParser/Lexer/Lexer.cpp
        QueryParser/Lexer/Lexer.h
        Statements/SelectFromStatement/SelectFromStatement.cpp
        Statements/SelectFromStatement/SelectFromStatement.h
        QueryExecutor/QueryExecutor.cpp
        QueryExecutor/QueryExecutor.h
        Token/Token.h
        Token/Types/TokenType.h
        Token/Types/KeywordType.h
        Token/KeywordToken/KeywordToken.cpp
        Token/KeywordToken/KeywordToken.h
        Statements/InsertIntoStatement/InsertIntoStatement.cpp
        Statements/InsertIntoStatement/InsertIntoStatement.h
        Statements/UpdateStatement/UpdateStatement.cpp
        Statements/UpdateStatement/UpdateStatement.h
        Statements/DeleteFromStatement/DeleteFromStatement.cpp
        Statements/DeleteFromStatement/DeleteFromStatement.h
        Statements/CreateStatement/CreateStatement.cpp
        Statements/CreateStatement/CreateStatement.h
)
