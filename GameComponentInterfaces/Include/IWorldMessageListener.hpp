#pragma once

#ifndef _IWORLDMESSAGELISTENER_HPP_
#define _IWORLDMESSAGELISTENER_HPP_

namespace Fnd
{
namespace EntitySystem
{
class EntitySystem;
}
namespace AssetManager
{
class AssetManager;
}
namespace Scripting
{
class ScriptManager;
}
}

namespace Fnd
{
namespace GameComponentInterfaces
{

/*
	Interface class inherited by Game class.
	Allows the World to access data in the Game.
*/
class IWorldMessageListener
{
	public:

		virtual Fnd::EntitySystem::EntitySystem& GetEntitySystem() = 0;

		virtual Fnd::AssetManager::AssetManager& GetAssetManager() = 0;

		virtual Fnd::Scripting::ScriptManager& GetScriptManager() = 0;
};

}
}

#endif