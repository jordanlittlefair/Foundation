#pragma once

#ifndef _ENTITYSYSTEMGENERATORCONFIG_HPP_
#define _ENTITYSYSTEMGENERATORCONFIG_HPP_

#include <string>

namespace Fnd
{
namespace EntitySystemGenerator
{

class EntitySystemGeneratorConfig
{
	public:

		struct Directories
		{
			std::string input;
			std::string output;
		};

		bool LoadConfigFile( const std::string& directory, const std::string& filename );

		Directories GetDirectories();

	private:

		Directories _directories;
};

}
}

#endif