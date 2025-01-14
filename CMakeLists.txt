cmake_minimum_required(VERSION 3.10)  # CMake version check
project(fla_project)
set(CMAKE_CXX_STANDARD 14)

add_executable(fla fla-project/main.cpp fla-project/message.cpp fla-project/message.h 
                   fla-project/pda.cpp fla-project/pda.h 
                   fla-project/utils.cpp fla-project/utils.h 
                   fla-project/TM.cpp fla-project/TM.h)

