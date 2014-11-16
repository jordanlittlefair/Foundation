#include "../Include/MockScriptManager.hpp"

using namespace Fnd::MockScripting;

#include "../Include/Scripts/CameraAnimation.hpp"
#include "../Include/Scripts/OculusCameraAnimation.hpp"

MockScriptManager::MockScriptManager()
{
}

void MockScriptManager::AddScript( unsigned int entity_id, std::string& script_name )
{
	if ( script_name == "CameraAnimationScript" )
	{
		auto script = new CameraAnimationScript( this );
		script->SetOwningEntity( entity_id );
		ScriptManager::AddScript( entity_id, script );
	}
	else if ( script_name == "OculusCameraAnimationScript" )
	{
		auto script = new OculusCameraAnimationScript( this );
		script->SetOwningEntity( entity_id );
		ScriptManager::AddScript( entity_id, script );
	}
}