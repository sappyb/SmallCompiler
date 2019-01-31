cmake_minimum_required(VERSION 3.8)
project(compiler)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bytecode.c
        bytecode.h
        calcclass.c
        compile.c
        error.c
        global.h
        init.c
        javaclass.c
        javaclass.h
        lexer.c
        lextest.c
        symbol.c)

add_executable(compiler ${SOURCE_FILES})