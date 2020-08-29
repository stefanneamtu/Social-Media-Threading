cmake_minimum_required(VERSION 3.17)
project(SocialMediaThreading)

set(CMAKE_CXX_STANDARD 17)

add_executable(SocialMediaThreading main.cpp Task.cpp Task.h Message.cpp Message.h User.cpp User.h Worker.cpp Worker.h Backlog.cpp Backlog.h Board.cpp Board.h SocialNetwork.cpp SocialNetwork.h)
