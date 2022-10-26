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
 "ClassesEx/CModListScreen.h" "Classes/CMainButton.h" "Classes/CToggleButton.h")

add_subdirectory(Assets)
add_subdirectory(Classes)
add_subdirectory(MenuEditor)
add_subdirectory(Mod)
add_subdirectory(Patches)
add_subdirectory(Signatures)
add_subdirectory(thirdparty)
add_subdirectory(Util)

message("${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(NKHook5 PRIVATE PolyHook_2 ghstl opengl32 Common)