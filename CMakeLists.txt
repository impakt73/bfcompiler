project(bfcompiler)
cmake_minimum_required(VERSION 2.8)

set(SRC_LIST
    src/main.cpp
    src/Lexer.h
    src/Lexer.cpp
    src/Token.h
    src/Parser.h
    src/Parser.cpp
    src/NodeType.h
    src/Node.h
    src/CommandType.h
    src/CommandNode.h
    src/LoopNode.h
    src/Interpreter.h
    src/Interpreter.cpp)

include_directories(src)

set(cmake_build_type Debug)

SET( BIN_DIR ${CMAKE_HOME_DIRECTORY}/bin )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}" )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}" )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}" )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}" )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BIN_DIR}" )
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BIN_DIR}" )

SET( CMAKE_DEBUG_POSTFIX "_Debug" )
SET( CMAKE_RELEASE_POSTFIX "_Release" )

set( CMAKE_C_COMPILER "clang" )
set( CMAKE_CXX_COMPILER "clang++" )

IF( UNIX )
    set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
ENDIF()

add_executable(${PROJECT_NAME} ${SRC_LIST})

