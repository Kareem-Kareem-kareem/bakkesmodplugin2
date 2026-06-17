@echo off
if not defined BAKKESMOD_SDK (
    echo Please set BAKKESMOD_SDK environment variable to the path of BakkesMod SDK.
    exit /b 1
)

mkdir build 2>nul
cd build
cmake .. -G "Visual Studio 16 2019" -A x64
if errorlevel 1 exit /b %errorlevel%
cmake --build . --config Release
echo Build complete. DLL located in build\Release\SpawnMiddle.dll
pause
