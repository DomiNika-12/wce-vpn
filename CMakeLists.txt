cmake_minimum_required(VERSION 3.20.2)
project(dnsTest)

set(CMAKE_CXX_STANDARD 14)

add_executable(dnsTest main.cpp server.h server.cpp dns_message.cpp dns_message.h)
