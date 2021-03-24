set(CMAKE_CXX_STANDARD 17) # C++ CLI supports C++17 latest

add_library(Managed SHARED 
    Main.cpp
)

include_directories(../NKHook5)
target_link_libraries(Managed NKHook5)

set_target_properties(Managed PROPERTIES COMMON_LANGUAGE_RUNTIME "")