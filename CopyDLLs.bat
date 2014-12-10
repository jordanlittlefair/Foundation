@echo off

echo Copying d3dcompiler_46.dll

xcopy "dlls\d3dcompiler_46.dll" "Foundation\" /y
xcopy "dlls\d3dcompiler_46.dll" "Bin\Win32\Debug\" /y
xcopy "dlls\d3dcompiler_46.dll" "Bin\Win32\Release\" /y

pause