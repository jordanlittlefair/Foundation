#include "../Include/Script.hpp"

using namespace Fnd::Scripting;

Script::Script( Fnd::Scripting::ScriptManager* script_manager ):
	_owning_entity_id(~0),
	_script_manager(script_manager)
{
}

void Script::SetOwningEntity( unsigned int entity_id )
{
	_owning_entity_id = entity_id;
}

unsigned int Script::GetOwningEntity() const
{
	return _owning_entity_id;
}

Fnd::Scripting::ScriptManager* Script::GetScriptManager()
{
	return _script_manager;
}

Script::~Script()
{
}