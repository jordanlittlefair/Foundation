#pragma once

#ifndef _LAUNCHER_APPLICATIONSETTINGSREADER_HPP_
#define _LAUNCHER_APPLICATIONSETTINGSREADER_HPP_

#include <string>

namespace Fnd
{
namespace Launcher
{

class ApplicationSettingsReader
{
	public:

		static std::string GetEngineDirectory( const std::string& filename );
};

}
}

#endif