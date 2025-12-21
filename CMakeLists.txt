cmake_minimum_required(VERSION 4.1)
project(LeafSQL)

set(CMAKE_CXX_STANDARD 20)

add_executable(LeafSQL main.cpp
        QueryParser/QueryParser.cpp
        QueryParser/QueryParser.h
        Lexer/Lexer.cpp
        Lexer/Lexer.h
        SelectFromStatement/SelectFromStatement.cpp
        SelectFromStatement/SelectFromStatement.h
        QueryExecutor/QueryExecutor.cpp
        QueryExecutor/QueryExecutor.h
        Token/Token.h
        Token/Types/TokenType.h
        Token/Types/KeywordType.h
        Token/KeywordToken/KeywordToken.cpp
        Token/KeywordToken/KeywordToken.h
)
