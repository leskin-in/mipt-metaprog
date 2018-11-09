cmake_minimum_required(VERSION 3.9)
project(mipt_metaprog)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        hw_1
        hw_1/Command.h
        hw_1/Strategy.h
        hw_1/hardcoded_settings.h
        hw_1/Mediator.cpp hw_1/Storage.cpp hw_1/Controller.cpp hw_1/IOProcessor.cpp
        hw_1/Proxy.h
        hw_1/main.cpp
)
