set(CMAKE_CXX_STANDARD 17) # C++ CLI supports C++17 latest

add_library(Managed SHARED 
    Main.cpp
)

add_dependencies(Managed NKHook5)

set_target_properties(Managed PROPERTIES COMMON_LANGUAGE_RUNTIME "")