cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp User.cpp User.h Group.cpp Group.h AVLTREE.h Movie.cpp Movie.h Wet1Exceptions.h wet1util.h StreamingDBa1.cpp StreamingDBa1.h)
