cmake_minimum_required(VERSION 3.16)

project(TypingTrainer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(TypingTrainer
    main.cpp
    typingtrainer.h
    typingtrainer.cpp
    typingtrainer.ui
)

target_link_libraries(TypingTrainer PRIVATE Qt6::Widgets)
