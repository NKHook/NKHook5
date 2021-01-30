cmake_minimum_required (VERSION 2.8.11)
project (NKHook5)


add_library(NKHook5 SHARED 
    main.cpp
    Utils.cpp
)

link_directories(Lib/PolyHook_2_0/_install/lib/)

target_include_directories(NKHook5 PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook_2_0/_install/include")


target_link_libraries(NKHook5 PRIVATE PolyHook_2 capstone)

