#pragma once

#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include "../../CommonResources/Include/Texture2DDesc.hpp"
#include "../../CommonResources/Include/PipelineDesc.hpp"

#include <string>
#include <map>

namespace Fnd
{
namespace Configuration
{
struct WindowConfig
{
	struct WindowImplementation
	{
		int placeholder;
	};

	std::map<std::string,WindowImplementation> implementations;
	std::string implementation;	// Updated by the Setup.xml file to the chosen implementation
};

struct GraphicsConfig
{
	struct Model
	{
		std::string filename;
	};

	struct GraphicsImplementation
	{
		std::map<std::string,Fnd::CommonResources::PipelineDesc> shader_pipelines;

		std::map<std::string,Fnd::CommonResources::Texture2DDesc> textures;
	};

	struct GraphicsCommon
	{
		std::map<std::string,Fnd::CommonResources::Texture2DDesc> textures;
		std::map<std::string,Model> models;
	};

	std::map<std::string,GraphicsImplementation> implementations;
	std::string implementation;	// Updated by the Setup.xml file to the chosen implementation
	
	GraphicsCommon common;
};

struct Config
{
	WindowConfig window_config;
	GraphicsConfig graphics_config;
};

class Configuration
{
public:
	bool LoadConfiguration( const std::string& filename );

	const Config& GetConfig() const;

	Config& GetConfigNonConst();

private:

	bool LoadWindowImplementation( const std::string& directory, const std::string& filename, const std::string& name );

	bool LoadGraphicsCommon( const std::string& directory, const std::string& filename );

	bool LoadGraphicsImplementation( const std::string& directory, const std::string& filename, const std::string& name );

	Config _config;
};
}
}

#endif