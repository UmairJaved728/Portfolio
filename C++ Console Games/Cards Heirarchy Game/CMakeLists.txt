cmake_minimum_required(VERSION 3.24)
project(Project__Card_Game_)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project__Card_Game_
        main.cpp CCard.h Player.h CStudent.h CAdmin.h CPlagirarismHearing.h CCourseAccreditation.h CFeedBackForum.h CIndustrialPlacement.h Game.h CAdmin.cpp CCard.cpp CCourseAccreditation.cpp CFeedBackForum.cpp CIndustrialPlacement.cpp CPlagirarismHearing.cpp CStudent.cpp Game.cpp Player.cpp)
