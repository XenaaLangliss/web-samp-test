@echo off
REM TD Animation Plugin Build Script
REM For Windows (using MSVC or MinGW)

echo ========================================
echo Building TD Animation Plugin...
echo ========================================

REM Clean previous build
if exist build rmdir /s /q build
mkdir build
cd build

REM Create output directory
mkdir bin

echo Compiling TDAnimation.cpp...
cl /c /std:c++17 /O2 /MD /EHsc /I..\SDK /I.. ..\TDAnimation.cpp /FoTDAnimation.obj

if errorlevel 1 (
    echo Error compiling TDAnimation.cpp
    exit /b 1
)

echo Compiling main.cpp...
cl /c /std:c++17 /O2 /MD /EHsc /I..\SDK /I.. ..\main.cpp /Fomain.obj

if errorlevel 1 (
    echo Error compiling main.cpp
    exit /b 1
)

echo Linking plugin...
link /DLL /OUT:bin\td_animation.dll TDAnimation.obj main.obj

if errorlevel 1 (
    echo Error linking plugin
    exit /b 1
)

echo ========================================
echo Build successful!
echo Plugin: build\bin\td_animation.dll
echo ========================================

REM Copy include file
copy ..\td_animation_plugin.inc bin\

echo Include file copied to build\bin\
