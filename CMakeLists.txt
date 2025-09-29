# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(lab6)
set(CMAKE_CXX_STANDARD 14)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/EnglishWords.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
    boggle.cpp
    lexicon.cpp
)

add_executable(boggle ${SOURCES})
