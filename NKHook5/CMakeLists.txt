add_library(NKHook5 SHARED)
set_target_properties(NKHook5 PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

target_sources(NKHook5 PRIVATE 
    "main.cpp"
    "Utils.cpp"
)

add_subdirectory(Assets)
add_subdirectory(Classes)
add_subdirectory(ClassesEx)
add_subdirectory(Extensions)
add_subdirectory(MenuEditor)
add_subdirectory(Mod)
add_subdirectory(Patches)
add_subdirectory(Signatures)
add_subdirectory(thirdparty)
add_subdirectory(Util)

message("${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(NKHook5 PRIVATE PolyHook_2 libhat opengl32 Common Boost::config Boost::container Boost::intrusive Boost::smart_ptr Boost::spirit Boost::variant json_spirit)