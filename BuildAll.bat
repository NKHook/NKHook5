mkdir Build
cd Build
cmake .. -A Win32
cmake --build . --config Debug
cmake --build . --config Release