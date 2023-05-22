cmake_minimum_required(VERSION 3.00)

project(COMPILER_FOR_PL0 CXX)
set(CMAKE_CXX_STANDARD 11)

set(exe_name pl0_compiler)

set(SOURCE_LIST
    lexemes.h
    regex_pattern.h
    main.cpp
    str_opekit.h
    lexical_analyzer.h
    lexical_analyzer.cpp
    slr1.cpp
    slr1.h
    analysis_table.h
    analysis_table.cpp
    semantic_analyzer.cpp
    semantic_analyzer.h
    intermediate_code_generator.cpp
    intermediate_code_generator.h
    DAG_optimizer.cpp
    DAG_optimizer.h)

# pl0_compiler
add_executable(${exe_name} ${SOURCE_LIST})

# regex_patterns
add_executable(reg_patterns main.cpp)
# add macro _PRINT_REGEX_ for executable reg_patterns
target_compile_definitions(reg_patterns PRIVATE _PRINT_REGEX_)

# Copy all files in test_files to binary directory
include_directories(${CMAKE_SOURCE_DIR}/test_files)
file(COPY ${CMAKE_SOURCE_DIR}/test_files DESTINATION ${CMAKE_BINARY_DIR})

# Copy all files in data to binary directory
include_directories(${CMAKE_SOURCE_DIR}/data)
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

# Create the output directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output)
