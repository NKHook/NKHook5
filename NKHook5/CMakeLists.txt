if(MSVC)
    add_compile_options(
            $<$<CONFIG:>:/MT> #---------|
            $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
            $<$<CONFIG:Release>:/MT> #--|
    )
endif()

add_library(NKHook5 SHARED)

target_sources(NKHook5 PRIVATE 
    "main.cpp"
    "Utils.cpp"
 "Classes/CLoc.h")

add_subdirectory(Patches)
add_subdirectory(Classes)

message("${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(NKHook5 PRIVATE PolyHook_2 ghstl)