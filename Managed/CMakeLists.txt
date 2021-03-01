set(CMAKE_CXX_STANDARD 17) # C++ CLI supports C++17 latest

add_library(Managed SHARED 
    Main.cpp
)

set_target_properties(Managed PROPERTIES COMMON_LANGUAGE_RUNTIME "")