if(MSVC)
    add_compile_options(
            $<$<CONFIG:>:/MT> #---------|
            $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
            $<$<CONFIG:Release>:/MT> #--|
    )
endif()

link_directories("${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook_2_0/_install/lib/")

add_library(NKHook5 SHARED)

target_sources(NKHook5 PRIVATE 
    "main.cpp"
    "Utils.cpp"
)

add_subdirectory(Patches)

target_include_directories(NKHook5 PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Lib/PolyHook_2_0/_install/include")

message("${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(NKHook5 PRIVATE PolyHook_2 capstone)