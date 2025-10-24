cmake_minimum_required(VERSION 3.17)
project(NKHook5 VERSION 1.0 LANGUAGES CXX)

include(FetchContent)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

# Only Visual Studio platforms are supported
if (NOT CMAKE_GENERATOR_PLATFORM STREQUAL Win32)
    message(FATAL_ERROR "NKHook5 can only be built on Win32 using the Visual Studio 17 2022 or newer generator.")
endif ()

message("BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if (NOT (CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "Release"))
    message(FATAL_ERROR "NKHook5 can only be built in Debug or Release mode.")
endif()

#Get the git diff ID thing and make a compile def for it
EXECUTE_PROCESS(
      COMMAND git rev-parse --short HEAD
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "NKHOOK_BUILD_VERSION"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)

add_compile_definitions(NKHOOK_BUILD_TAG=0.10.2)
add_compile_definitions(NKHOOK_BUILD_VERSION=${NKHOOK_BUILD_VERSION})
add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)
add_compile_options(/openmp)

if(MSVC)
    add_compile_options(
            $<$<CONFIG:>:/MT> #---------|
            $<$<CONFIG:Debug>:/MTd> #---|-- Statically link the runtime libraries
            $<$<CONFIG:Release>:/MT> #--|
            $<$<CONFIG:RelWithDebInfo>:/MT> #--|
    )
endif()

#Fetch & Install PolyHook2
FetchContent_Declare(
    plh
    GIT_REPOSITORY https://github.com/stevemk14ebr/PolyHook_2_0.git
    GIT_TAG e8d33f54f9d11943f86fc326dae31dcc8ea7c389
)
FetchContent_GetProperties(plh)
if(NOT plh_POPULATED)
    FetchContent_Populate(plh)
    set(POLYHOOK_BUILD_DLL ON)
    add_subdirectory(${plh_SOURCE_DIR} ${plh_BINARY_DIR})
endif()

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG master
)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR})
    include_directories(${json_SOURCE_DIR}/include)
endif()

FetchContent_Declare(
    menum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
    GIT_TAG master
)
FetchContent_GetProperties(menum)
if(NOT menum_POPULATED)
    FetchContent_Populate(menum)
    add_subdirectory(${menum_SOURCE_DIR} ${menum_BINARY_DIR})
endif()

FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11
    GIT_TAG        v2.2.0
)
FetchContent_MakeAvailable(cli11)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)
FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
    FetchContent_Populate(stb)
    add_library(stb INTERFACE)
    target_include_directories(stb INTERFACE ${stb_SOURCE_DIR})
endif()

FetchContent_Declare(
    binpack
    GIT_REPOSITORY https://github.com/chris-stones/BinPack2D.git
    GIT_TAG master
)
FetchContent_GetProperties(binpack)
if(NOT binpack_POPULATED)
    FetchContent_Populate(binpack)
    add_library(binpack INTERFACE)
    target_include_directories(binpack INTERFACE ${binpack_SOURCE_DIR})
endif()

FetchContent_Declare(
    libhat
    GIT_REPOSITORY https://github.com/BasedInc/libhat.git
    GIT_TAG master
)
FetchContent_GetProperties(libhat)
if(NOT libhat_POPULATED)
    FetchContent_Populate(libhat)
    message("${libhat_SOURCE_DIR}")
    message("${libhat_BINARY_DIR}")
    add_subdirectory(${libhat_SOURCE_DIR} ${libhat_BINARY_DIR})
endif()

set(BOOST_INCLUDE_LIBRARIES config container intrusive smart_ptr spirit variant)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.80.0
    OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(Boost)
set(Boost_INCLUDE_DIR ${Boost_SOURCE_DIR})
set(Boost_ROOT ${Boost_SOURCE_DIR})

FetchContent_Declare(
        jsonspirit
        GIT_REPOSITORY https://github.com/png85/json_spirit.git
        GIT_TAG master
)
FetchContent_GetProperties(jsonspirit)
if(NOT jsonspirit_POPULATED)
    FetchContent_Populate(jsonspirit)
    set(BUILD_STATIC_LIBRARIES ON)
    set(BUILD_STATIC_LIBS ON)
    set(JSON_SPIRIT_DEMOS OFF)
    set(JSON_SPIRIT_TESTS OFF)
    add_subdirectory(${jsonspirit_SOURCE_DIR} ${jsonspirit_BINARY_DIR})
    target_include_directories(json_spirit PUBLIC ${jsonspirit_SOURCE_DIR})
    target_link_libraries(json_spirit PRIVATE Boost::config Boost::smart_ptr Boost::spirit Boost::variant)
endif()

add_subdirectory(Common)
add_subdirectory(DevKit)
add_subdirectory(NKHook5)
add_subdirectory(Loader)