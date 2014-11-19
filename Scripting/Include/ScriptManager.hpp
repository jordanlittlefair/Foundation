#pragma once

#ifndef _SCRIPTING_SCRIPTMANAGER_HPP_
#define _SCRIPTING_SCRIPTMANAGER_HPP_

#include <string>
#include <vector>
#include <list>
#include <map>
#include <memory>

#include "Script.hpp"

namespace Fnd
{
namespace EntitySystem
{
class EntitySystem;
}
namespace Input
{
class IInput;
}
}

namespace Fnd
{
namespace Scripting
{

class ScriptManager
{
	public:

		ScriptManager();

		virtual void AddScript( unsigned int entity_id, std::string& script_name ) = 0;	// filename or 'id' name

		void SetEntitySystem( Fnd::EntitySystem::EntitySystem* entity_system );

		void SetInputHandler( Fnd::Input::IInput* input_handler );

		void Update( const Fnd::CommonResources::FrameData& frame_data );

		~ScriptManager();

		Fnd::EntitySystem::EntitySystem* GetEntitySystem();
		
		Fnd::Input::IInput* GetInputHandler();

	protected:

		void AddScript( unsigned int entity_id, Script* script );

	private:

		Fnd::EntitySystem::EntitySystem* _entity_system;
		Fnd::Input::IInput* _input_handler;

		struct Entity
		{
			unsigned int entity_id;

			std::list<std::shared_ptr<Script>> scripts;
		};

		std::map<unsigned int,Entity> _entities;
};

}
}

#endif