@echo off

echo Copying Assimp32d.dll

xcopy  "C:\Users\Jordan\Dropbox\Foundation\Assimp\bin\assimp_debug-dll_win32\Assimp32d.dll" "Foundation\" /y
xcopy  "C:\Users\Jordan\Dropbox\Foundation\Assimp\bin\assimp_debug-dll_win32\Assimp32d.dll" "Bin\Win32\Debug\" /y

echo Copying Assimp32.dll

xcopy  "C:\Users\Jordan\Dropbox\Foundation\Assimp\bin\assimp_release-dll_win32\Assimp32.dll" "Foundation\" /y
xcopy  "C:\Users\Jordan\Dropbox\Foundation\Assimp\bin\assimp_release-dll_win32\Assimp32.dll" "Bin\Win32\Release\" /y

pause