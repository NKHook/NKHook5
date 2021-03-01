cmake_minimum_required(VERSION 3.17)
set(CMAKE_GENERATOR_PLATFORM Win32)
project(NKHook5 VERSION 1.0 LANGUAGES CSharp CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(NKHook5)
add_subdirectory(Loader)
add_subdirectory(Managed)
add_subdirectory(ExampleMod)