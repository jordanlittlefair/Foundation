#pragma once

#ifndef _SETUP_HPP_
#define _SETUP_HPP_

#include "GameComponentData.hpp"

#include <string>

namespace Fnd
{
namespace Setup
{

class Setup
{
	public:

		Setup();

		bool LoadSetupFile( const std::string& directory, const std::string& filename );

		const LoggerSetupData& GetLoggerSetupData() const;
		const WindowSetupData& GetWindowSetupData() const;
		const GraphicsSetupData& GetGraphicsSetupData() const;
		const PhysicsSetupData& GetPhysicsSetupData() const;
		const WorldSetupData& GetWorldSetupData() const;
		const ScriptingSetupData& GetScriptingSetupData() const;

	private:
		
		LoggerSetupData _logger_data;
		WindowSetupData _window_data;
		GraphicsSetupData _graphics_data;
		PhysicsSetupData _physics_data;
		WorldSetupData _world_data;
		ScriptingSetupData _scripting_data;
};

}
}

#endif