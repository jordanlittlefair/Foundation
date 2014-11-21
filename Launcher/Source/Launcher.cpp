#include "../Include/Launcher.hpp"
#include "../../Utility/Include/FileSystem.hpp"

#include <Windows.h>

using namespace Fnd::Launcher;
using namespace Fnd::Utility;

Launcher::Launcher()
{
}

void Launcher::SetEngineDirectory( const std::string& directory )
{
	_engine_directory = FileSystem::CanonicaliseDirectory( directory );
}

void Launcher::SetApplicationDirectory( const std::string& directory )
{
	_application_directory = FileSystem::CanonicaliseDirectory( directory );
}

Launcher::ApplicationReturnCode Launcher::Launch()
{
	std::string executable_name = FileSystem::CanonicaliseFile( _engine_directory + "Game.exe" );
	std::string config_str;

	// Can probably do a better check than this....
#ifdef WIN32
	config_str = "Windows";
#elif defined MAC
	config_str = "Mac";
#else
	config_str = "Linux";
#endif

	std::string command_line = executable_name + " " + _application_directory + " " + config_str;

	char command_line_str[MAX_PATH] = {0};
	strcpy_s(command_line_str, command_line.c_str());

	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;
	ZeroMemory( &startup_info, sizeof(startup_info) );
	startup_info.cb = sizeof(startup_info);
	ZeroMemory( &process_info, sizeof(process_info) );
	
	int process_res = CreateProcess( executable_name.c_str(), command_line_str, nullptr, nullptr, false, 0, nullptr, _engine_directory.c_str(), &startup_info, &process_info );

	if ( process_res )
	{
		DWORD return_code = ReturnCode_FailedToLaunch;

		WaitForSingleObject( process_info.hProcess, INFINITE );

		// Get the exit code.
		int exit_res = GetExitCodeProcess(process_info.hProcess, &return_code);
 
		// Close the handles.
		CloseHandle( process_info.hProcess );
		CloseHandle( process_info.hThread );
		
		return (ApplicationReturnCode)return_code;
	}
	else
	{
		return ReturnCode_FailedToLaunch;
	}	
}