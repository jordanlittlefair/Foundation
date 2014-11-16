#include "../Include/ScriptManager.hpp"

#include "../Include/Script.hpp"

using namespace Fnd::Scripting;

ScriptManager::ScriptManager():
	_entity_system(nullptr),
	_input_handler(nullptr)
{
}

void ScriptManager::AddScript( unsigned int entity_id, Script* script )
{
	_entities[entity_id].entity_id = entity_id;
	_entities[entity_id].scripts.push_back(std::shared_ptr<Script>(script));
}

void ScriptManager::SetEntitySystem( Fnd::EntitySystem::EntitySystem* entity_system )
{
	_entity_system = entity_system;
}

void ScriptManager::SetInputHandler( Fnd::Input::IInput* input_handler )
{
	_input_handler = input_handler;
}

void ScriptManager::Update( const Fnd::CommonResources::FrameData& frame_data )
{
	for ( auto entity_iter = _entities.begin(); entity_iter != _entities.end(); ++entity_iter )
	{
		for ( auto script_iter = entity_iter->second.scripts.begin(); script_iter != entity_iter->second.scripts.end(); ++script_iter )
		{
			// Doesn't yet handle adding/removing entities/components.
			script_iter->get()->OnUpdate( frame_data );
		}
	}
}

Fnd::EntitySystem::EntitySystem* ScriptManager::GetEntitySystem()
{
	return _entity_system;
}

Fnd::Input::IInput* ScriptManager::GetInputHandler()
{
	return _input_handler;
}

ScriptManager::~ScriptManager()
{
}