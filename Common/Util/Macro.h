#pragma once

#define STRING_EXPAND(s) #s
#define STRING(s) STRING_EXPAND(s)

//Define the build ver if CMake failed to or it wasn't build with it
#ifndef NKHOOK_BUILD_VERSION
#define NKHOOK_BUILD_VERSION Unknown
#endif