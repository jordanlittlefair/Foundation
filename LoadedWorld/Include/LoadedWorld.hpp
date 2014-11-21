#pragma once

#ifndef _LOADEDWORLD_LOADEDWORLD_HPP_
#define _LOADEDWORLD_LOADEDWORLD_HPP_

#include "../../GameComponentInterfaces/Include/IWorld.hpp"

namespace Fnd
{
namespace LoadedWorld
{

class LoadedWorld:
	public Fnd::GameComponentInterfaces::IWorld
{
	public:

		LoadedWorld();
	
		void SetWorldMessageListener( Fnd::GameComponentInterfaces::IWorldMessageListener* game );

		// LoadedWorld only supports a single world file (a single level).
		void SetWorldSetupData( const Fnd::Settings::WorldSettings& world_setup_data );

		bool Initialise();

		~LoadedWorld();

	private:

		Fnd::GameComponentInterfaces::IWorldMessageListener* _game;

		Fnd::Settings::WorldSettings _world_setup_data;
};

}
}

#endif