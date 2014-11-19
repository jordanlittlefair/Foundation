#pragma once

#ifndef _GAMESYSTEMS_ASSETLINKERSYSTEM_HPP_
#define _GAMESYSTEMS_ASSETLINKERSYSTEM_HPP_

#include "../../EntitySystem/Include/System.hpp"

namespace Fnd
{
namespace GameSystems
{

class AssetLinkerSystem:
	public Fnd::EntitySystem::System
{
	public:

		AssetLinkerSystem();

		void AddNode( Fnd::EntitySystem::SystemNode* node );

		std::vector<std::string> GetRegisteredNodes();

		bool Initialise();

	protected:

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );
};

}
}

#endif