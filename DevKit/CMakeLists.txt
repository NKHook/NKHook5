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
)

add_subdirectory(Features)

target_link_libraries(DevKit PRIVATE Common)