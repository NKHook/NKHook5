cmake_minimum_required (VERSION 2.8.11)
project (NKHook5)

link_directories(../PolyHook_2_0/_install/lib/)

add_library(NKHook5 SHARED 
    main.cpp
    Utils.cpp
)

add_subdirectory(../PolyHook_2_0/polyhook2)

target_link_libraries(NKHook5 SHARED PolyHook_2 capstone)

