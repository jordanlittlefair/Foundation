#pragma once

#ifndef _SETTINGS_ENGINESETTINGS_HPP_
#define _SETTINGS_ENGINESETTINGS_HPP_

#include "../../CommonResources/Include/Texture2DDesc.hpp"
#include "../../CommonResources/Include/PipelineDesc.hpp"

#include <string>
#include <map>

namespace Fnd
{
namespace Settings
{

class EngineSettings
{
public:

	//-change to xxxSettings
	//-use enums instead of strings
	//-only store 1 implementation, dont store impl name

	struct WindowSettings
	{
		struct WindowImplementation
		{
			int placeholder;
		};

		std::map<std::string,WindowImplementation> implementations;
		std::string implementation;	// Updated by the Setup.xml file to the chosen implementation
	};

	struct GraphicsSettings
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

	struct Settings
	{
		WindowSettings window_config;
		GraphicsSettings graphics_config;
	};

	bool LoadConfiguration( const std::string& filename );

	const Settings& GetConfig() const;

	Settings& GetConfigNonConst();

private:

	bool LoadWindowImplementation( const std::string& directory, const std::string& filename, const std::string& name );

	bool LoadGraphicsCommon( const std::string& directory, const std::string& filename );

	bool LoadGraphicsImplementation( const std::string& directory, const std::string& filename, const std::string& name );

	Settings _config;
};
}
}

#endif