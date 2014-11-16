#pragma once

#ifndef _WORLDLOADER_HPP_
#define _WORLDLOADER_HPP_

#include <string>

#include "../Include/WorldLoaderErrors.hpp"
#include "../../GameComponentInterfaces/Include/IWorld.hpp"

namespace Fnd
{
namespace WorldLoader
{

/**
	WorldLoader class loads and writes world files.

	Handles the loading and saving of world files.
*/
class WorldLoader
{
	public:

		/**
			A method to load an xml world file into a WorldData struct.
			@param filename The name of the world file to load.
			@param loaded_world_data A reference to a struct to store the loaded world data.
			@return Returns true if the load was successful.
		*/
		static bool LoadWorld( const std::string& directory, const std::string& filename, Fnd::GameComponentInterfaces::WorldData& loaded_world_data );
};

}
}

#endif
