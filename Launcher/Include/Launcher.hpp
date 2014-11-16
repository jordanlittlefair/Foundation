#pragma once

#ifndef _LAUNCHER_HPP_
#define _LAUNCHER_HPP_

#include <string>

namespace Fnd
{
namespace Launcher
{

class Launcher
{
	public:

		Launcher();

		void SetEngineDirectory( const std::string& directory );
		void SetApplicationDirectory( const std::string& directory );

		enum ApplicationReturnCode
		{
			ReturnCode_OK = 0,
			ReturnCode_FailedToLaunch = 1,
			ReturnCode_FailedToInitialise = 2,
			ReturnCode_Restart = 3
		};

		ApplicationReturnCode Launch();

	private:

		std::string _engine_directory;
		std::string _application_directory;
};

}
}

#endif