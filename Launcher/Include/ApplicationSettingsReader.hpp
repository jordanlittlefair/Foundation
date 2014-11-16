#pragma once

#ifndef _APPLICATIONSETTINGSREADER_HPP_
#define _APPLICATIONSETTINGSREADER_HPP_

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