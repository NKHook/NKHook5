message("BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

add_library(bzip2 STATIC IMPORTED)
set_target_properties(bzip2 PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/${CMAKE_BUILD_TYPE}/bzip2.lib")

add_library(lzma STATIC IMPORTED)
set_target_properties(lzma PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/${CMAKE_BUILD_TYPE}/lzma.lib")

add_library(zlib STATIC IMPORTED)
set_target_properties(zlib PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/${CMAKE_BUILD_TYPE}/zlib.lib")

add_library(ziplib_link STATIC IMPORTED)
set_target_properties(ziplib_link PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/${CMAKE_BUILD_TYPE}/ZipLib.lib")

add_library(ZipLib INTERFACE)
target_include_directories(ZipLib INTERFACE "${CMAKE_CURRENT_LIST_DIR}/ZipLib")
target_link_libraries(ZipLib INTERFACE bzip2 lzma zlib ziplib_link)