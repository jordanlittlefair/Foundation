#pragma once

#ifndef _SYSTEM_HPP_
#define _SYSTEM_HPP_

#include "EntitySystem.hpp"
#include "../../AssetManager/Include/AssetManager.hpp"
#include "../../CommonResources/Include/FrameData.hpp"

namespace Fnd
{
namespace EntitySystem
{

class System
{
	public:
	
		System( const std::string& system_name );

		void SetEntitySystem( EntitySystem* entity_system );
		void SetAssetManager( Fnd::AssetManager::AssetManager* asset_manager );

		std::string GetSystemName() const;

		void Update( const Fnd::CommonResources::FrameData& frame_data );

		virtual bool Initialise() = 0;

		virtual void AddNode( SystemNode* node );	// Or use an Id?

		virtual std::vector<std::string> GetRegisteredNodes(); // returns a vector of node names which this system requires notifications from.

		virtual ~System();

	protected:

		EntitySystem& GetEntitySystem();
		Fnd::AssetManager::AssetManager& GetAssetManager();

		virtual void OnUpdate( const Fnd::CommonResources::FrameData& frame_data ) = 0;

	private:

		std::string _system_name;
		EntitySystem* _entity_system;
		Fnd::AssetManager::AssetManager* _asset_manager;
};

}
}

#endif