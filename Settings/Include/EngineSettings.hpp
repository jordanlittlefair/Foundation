#pragma once

#ifndef _SETTINGS_ENGINESETTINGS_HPP_
#define _SETTINGS_ENGINESETTINGS_HPP_

#include "../../CommonResources/Include/Texture2DDesc.hpp"
#include "../../CommonResources/Include/PipelineDesc.hpp"

#include "ApplicationSettings.hpp"

#include <string>
#include <map>

namespace Fnd
{
namespace Settings
{

class EngineSettings
{
public:
	
	struct WindowSettings
	{
		int placeholder;
	};

	struct GraphicsSettings
	{
		struct Model
		{
			std::string filename;
		};

		std::map<std::string,Fnd::CommonResources::PipelineDesc> shader_pipelines;

		std::map<std::string,Fnd::CommonResources::Texture2DDesc> textures;

		struct GraphicsCommon
		{
			std::map<std::string,Fnd::CommonResources::Texture2DDesc> textures;
			std::map<std::string,Model> models;
		};
	
		GraphicsCommon common;
	};

	bool Load( const std::string& filename, const ApplicationSettings& application_settings );

	const WindowSettings& GetWindowSettings() const;

	const GraphicsSettings& GetGraphicsSettings() const;

private:

	WindowSettings LoadWindowImplementation( const std::string& directory, const std::string& filename, const std::string& name );

	GraphicsSettings::GraphicsCommon LoadGraphicsCommon( const std::string& directory, const std::string& filename );

	GraphicsSettings LoadGraphicsImplementation( const std::string& directory, const std::string& filename, const std::string& name );

	WindowSettings _window_settings;
	GraphicsSettings _graphics_settings;
};
}
}

#endif