cmake_minimum_required(VERSION 3.30)
project("Magazine_Subscribing_Manage_System")

set(CMAKE_CXX_STANDARD 20)

add_executable( main
        src/main.cpp
        src/Magazine.cpp
        src/Magazine.h
        src/Subscriber.cpp
        src/Subscriber.h
        src/Database.cpp
        src/Database.h
        src/Subscription.cpp
        src/Subscription.h
        src/json.hpp
        src/Interface.cpp
        src/Interface.h
)
