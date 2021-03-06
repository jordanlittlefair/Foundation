@echo off

echo "Configuring Foundation for Win32...."

echo "Copying Game.exe to Foundation/Engine/"
xcopy  "..\..\Bin\Win32\Release\Game.exe" "..\Engine\" /y

echo "Copying Launcher.exe to Foundation/Application"
mkdir ..\Application
xcopy  "..\..\Bin\Win32\Release\Launcher.exe" "..\Application" /y


echo "Copying Launcher.exe to Foundation/TestApp"
mkdir ..\Application
xcopy  "..\..\Bin\Win32\Release\Launcher.exe" "..\TestApp" /y

echo "Copying EntitySystemGenerator.exe to Foundation/"
xcopy  "..\..\Bin\Win32\Release\EntitySystemGenerator.exe" "..\" /y

echo "Copying DirectX11ShaderCompiler.exe to Foundation/"
xcopy  "..\..\Bin\Win32\Release\DirectX11ShaderCompiler.exe" "..\" /y

echo "Copying OpenGLShaderCompiler.exe to Foundation/"
xcopy  "..\..\Bin\Win32\Release\OpenGLShaderCompiler.exe" "..\" /y