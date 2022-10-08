if(MSVC)
    add_compile_options(
            $<$<CONFIG:>:/MT> #---------|
            $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
            $<$<CONFIG:Release>:/MT> #--|
    )
endif()

add_executable(DevKit)

target_sources(DevKit PRIVATE
	"main.cpp"
    "Settings.cpp"
    "FeatureMgr.cpp"
)

add_subdirectory(Features)
add_subdirectory(Packager)
add_subdirectory(Proj)

target_link_libraries(DevKit PRIVATE Common)