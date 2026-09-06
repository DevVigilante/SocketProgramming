cmake_minimum_required(VERSION 3.16)

project(CppHttpServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(CppHttpServer
    src/main.cpp
    src/BaseSocket.cpp
)

target_include_directories(CppHttpServer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(TARGETS CppHttpServer
    RUNTIME DESTINATION bin
)
