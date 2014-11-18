@echo off

echo Copying Assimp32d.dll

xcopy  "Assimp\bin\assimp_debug-dll_win32\Assimp32d.dll" "Foundation\" /y
xcopy  "Assimp\bin\assimp_debug-dll_win32\Assimp32d.dll" "Bin\Win32\Debug\" /y

echo Copying Assimp32.dll

xcopy  "Assimp\bin\assimp_release-dll_win32\Assimp32.dll" "Foundation\" /y
xcopy  "Assimp\bin\assimp_release-dll_win32\Assimp32.dll" "Foundation\Engine" /y
xcopy  "Assimp\bin\assimp_release-dll_win32\Assimp32.dll" "Bin\Win32\Release\" /y

echo Copying d3dcompiler_46.dll

xcopy "dlls\d3dcompiler_46.dll" "Foundation\" /y
xcopy "dlls\d3dcompiler_46.dll" "Bin\Win32\Debug\" /y
xcopy "dlls\d3dcompiler_46.dll" "Bin\Win32\Release\" /y

pause