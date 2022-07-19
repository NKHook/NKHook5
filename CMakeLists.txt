cmake_minimum_required(VERSION 3.17)
set(CMAKE_GENERATOR_PLATFORM Win32)
project(NKHook5 VERSION 1.0 LANGUAGES CSharp CXX)

include(FetchContent)
set(CMAKE_CXX_STANDARD 20)

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

add_subdirectory(NKHook5)
add_subdirectory(Loader)

make_directory(Binaries)
if(EXISTS ${PROJECT_SOURCE_DIR}/NKHook5/Release/NKHook5.dll)
	configure_file(${PROJECT_SOURCE_DIR}/NKHook5/Release/NKHook5.dll ${PROJECT_SOURCE_DIR}/Binaries/NKHook5.dll COPYONLY)
endif()
if(EXISTS ${PROJECT_SOURCE_DIR}/Loader/Release/wininet.dll)
	configure_file(${PROJECT_SOURCE_DIR}/Loader/Release/wininet.dll ${PROJECT_SOURCE_DIR}/Binaries/wininet.dll COPYONLY)
endif()