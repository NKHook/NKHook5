if(MSVC)
    add_compile_options(
            $<$<CONFIG:>:/MT> #---------|
            $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
            $<$<CONFIG:Release>:/MT> #--|
    )
endif()

add_library(Common STATIC)

add_subdirectory(Extensions)
add_subdirectory(Files)
add_subdirectory(Logging)
add_subdirectory(Mod)
add_subdirectory(Sprites)
add_subdirectory(thirdparty)
add_subdirectory(Threading)
add_subdirectory(Util)

target_include_directories(Common PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(Common PUBLIC magic_enum nlohmann_json ZipLib CLI11 RapidXML stb)