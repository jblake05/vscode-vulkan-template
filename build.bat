@echo off

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

SET includes=/Isrc /I%VULKAN_SDK%/Include /I%VCPKG_WINDOWS%/include
SET links=/link /libpath:%VULKAN_SDK%/Lib vulkan-1.lib /libpath:%VCPKG_WINDOWS%/lib glfw3dll.lib
SET defines=/D DEBUG

echo "Building main..."

cl /EHsc %includes% %defines% src/main.cpp /std:c++20 /o ./out/main.exe %links%