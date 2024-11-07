del bin /s /q
rmdir bin
mkdir bin
cd bin
del CMakeCache.txt
cmake .. -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 17 2022" -A Win32
cmake --build . --config Debug
cmake --build . --config Release

timeout 5 > NUL

mkdir Artifacts
cd Artifacts
mkdir Debug
mkdir Release
cd ..
copy "NKHook5\Debug\NKHook5.dll" "Artifacts\Debug\NKHook5.dll"
copy "Loader\Debug\wininet.dll" "Artifacts\Debug\wininet.dll"
copy "NKHook5\Release\NKHook5.dll" "Artifacts\Release\NKHook5.dll"
copy "Loader\Release\wininet.dll" "Artifacts\Release\wininet.dll"