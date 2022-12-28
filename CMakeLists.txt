cmake_minimum_required(VERSION 3.17)
project(NKHook5 VERSION 1.0 LANGUAGES CXX)

include(FetchContent)
set(CMAKE_CXX_STANDARD 20)

#Get the git diff ID thing and make a compile def for it
EXECUTE_PROCESS(
      COMMAND git rev-parse --short HEAD
      WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
      OUTPUT_VARIABLE "NKHOOK_BUILD_VERSION"
      ERROR_QUIET
      OUTPUT_STRIP_TRAILING_WHITESPACE)

add_compile_definitions(NKHOOK_BUILD_TAG=0.4.0)
add_compile_definitions(NKHOOK_BUILD_VERSION=${NKHOOK_BUILD_VERSION})
add_compile_definitions(_ITERATOR_DEBUG_LEVEL=0)

#Fetch & Install PolyHook2
FetchContent_Declare(
    plh
    GIT_REPOSITORY https://github.com/stevemk14ebr/PolyHook_2_0.git
    GIT_TAG master
)
FetchContent_GetProperties(plh)
if(NOT plh_POPULATED)
    FetchContent_Populate(plh)
    set(POLYHOOK_BUILD_DLL ON)
    add_subdirectory(${plh_SOURCE_DIR} ${plh_BINARY_DIR})
endif()

FetchContent_Declare(
    ghstl
    GIT_REPOSITORY https://github.com/DisabledMallis/GHSTL.git
    GIT_TAG main
)
FetchContent_GetProperties(ghstl)
if(NOT ghstl_POPULATED)
    FetchContent_Populate(ghstl)
    add_subdirectory(${ghstl_SOURCE_DIR} ${ghstl_BINARY_DIR})
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

# Build independent OpenCL library
FetchContent_Declare(
    oclh
    GIT_REPOSITORY https://github.com/KhronosGroup/OpenCL-Headers.git
    GIT_TAG main
)
FetchContent_GetProperties(oclh)
if(NOT oclh_POPULATED)
  FetchContent_Populate(oclh)
  add_subdirectory(${oclh_SOURCE_DIR} ${oclh_BINARY_DIR})
endif()
set(OPENCL_ICD_LOADER_HEADERS_DIR ${opencl-headers_SOURCE_DIR} CACHE PATH "") # for OpenCL ICD Loader
set(OpenCL_INCLUDE_DIR ${opencl-headers_SOURCE_DIR} CACHE PATH "") # for Boost::Compute

FetchContent_Declare(
    oclicdl
    GIT_REPOSITORY https://github.com/KhronosGroup/OpenCL-ICD-Loader.git
    GIT_TAG main
)
FetchContent_GetProperties(oclicdl)
if(NOT oclicdl_POPULATED)
    FetchContent_Populate(oclicdl)
    set(USE_DYNAMIC_VCXX_RUNTIME ON)
    add_subdirectory(${oclicdl_SOURCE_DIR} ${oclicdl_BINARY_DIR})
endif()

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
    usercall
    GIT_REPOSITORY https://github.com/widberg/usercall.hpp.git
    GIT_TAG master
)
FetchContent_MakeAvailable(usercall)

add_subdirectory(Common)
add_subdirectory(DevKit)
add_subdirectory(NKHook5)
add_subdirectory(Loader)