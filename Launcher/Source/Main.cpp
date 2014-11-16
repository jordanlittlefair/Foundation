#include "../Include/Launcher.hpp"
#include "../Include/ApplicationSettingsReader.hpp"
#include "../../Utility/Include/FileSystem.hpp"
#include "../../Utility/Include/MessageBox.hpp"

using namespace Fnd::Utility;
using namespace Fnd::Launcher;

int _stdcall
WinMain (	_In_ struct HINSTANCE__* hIinstance,
			_In_opt_ struct HINSTANCE__* hPrevInstance,
			_In_ char* lpszCmdLine,
			_In_ int nCmdShow )
{
	std::string application_dir = FileSystem::GetWorkingDirectory();

	std::string engine_dir = ApplicationSettingsReader::GetEngineDirectory("ApplicationSettings.xml");

	if ( engine_dir.size() > 2 && engine_dir[1] == ':' )
	{
		// absolute directory
	}
	else
	{
		engine_dir = FileSystem::CanonicaliseDirectory( application_dir + '/' + engine_dir );
	}
		
	Launcher launcher;
	launcher.SetEngineDirectory( engine_dir );
	launcher.SetApplicationDirectory( application_dir );

	Launcher::ApplicationReturnCode return_code = Launcher::ReturnCode_FailedToLaunch;

	do
	{
		return_code = launcher.Launch();

		if ( return_code == Launcher::ReturnCode_FailedToLaunch )
		{
			Fnd::Utility::BlockingMessageBox( "Error", "Failed to launch Game.exe" );
		}
		else if ( return_code == Launcher::ReturnCode_FailedToInitialise )
		{
			Fnd::Utility::BlockingMessageBox( "Error", "Failed to initialise Game.exe" );
		}
	}
	while ( return_code == Launcher::ReturnCode_Restart );

	return 0;
}