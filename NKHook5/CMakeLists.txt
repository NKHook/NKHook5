cmake_minimum_required (VERSION 2.8.11)
project (NKHook5)

set(CMAKE_CXX_STANDARD 20)

link_directories("${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook_2_0/_install/lib/")

add_library(NKHook5 SHARED 
    main.cpp
    Utils.cpp
)

target_include_directories(NKHook5 PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook_2_0/_install/include")

message("${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(NKHook5 PUBLIC PolyHook_2 capstone)