#pragma once

#ifndef _GAMECOMPONENTINTERFACES_IWORLD_HPP_
#define _GAMECOMPONENTINTERFACES_IWORLD_HPP_

#include <string>
#include <map>
#include <vector>
#include "../../Settings/Include/ApplicationSettings.hpp"

namespace Fnd
{
namespace GameComponentInterfaces
{

class IWorldMessageListener;

/**
	A struct to store a world consisting of multiple entities.
*/
struct WorldData
{
	struct Entity
	{
		struct Component
		{
			struct Data
			{
				std::string value;
			};

			std::string name;

			std::map<std::string,Data> data;
		};

		struct Node
		{
			std::string name;
		};

		struct Script
		{
			std::string name;

			std::map<std::string,std::string> variables;
		};

		std::string name;

		std::vector<Component> components;

		std::vector<Node> nodes;

		std::vector<Script> scripts;
	};

	std::vector<Entity> entities;
};

/**
	Base class for interacting with world implementations.

	Handles the loading and management of the world.
*/
class IWorld
{
	public:

		virtual void SetWorldMessageListener( Fnd::GameComponentInterfaces::IWorldMessageListener* game ) = 0;

		virtual void SetWorldSetupData( const Fnd::Settings::ApplicationSettings::WorldSettings& world_setup_data ) = 0;

		virtual bool Initialise() = 0;

		//virtual WorldData GetWorldData( const std::string& filename ) = 0;

		virtual ~IWorld() {};
};

}
}

#endif