cmake_minimum_required(VERSION 3.17)
set(CMAKE_GENERATOR_PLATFORM Win32)
project(NKHook5 VERSION 1.0 LANGUAGES CSharp CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(NKHook5)
add_subdirectory(Loader)
add_subdirectory(Managed)
add_subdirectory(ExampleMod)

make_directory(Binaries)
configure_file(${PROJECT_SOURCE_DIR}/Managed/Release/Managed.dll Binaries/Managed.dll COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/ExampleMod/Release/ExampleMod.dll Binaries/ExampleMod.dll COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/NKHook5/Release/NKHook5.dll Binaries/NKHook5.dll COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/Loader/Release/wininet.dll Binaries/wininet.dll COPYONLY)