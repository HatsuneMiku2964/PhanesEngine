chcp 65001 > nul

if exist *.sln del /f /q *.sln
if exist *.vcxproj del /f /q *.vcxproj
if exist *.vcxproj.user del /f /q *.vcxproj.user
if exist *.vcxproj.filters del /f /q *.vcxproj.filters

if exist bin rmdir /s /q bin
if exist bin-int rmdir /s /q bin-int

call vendor\premake\premake5.exe vs2022

PAUSE