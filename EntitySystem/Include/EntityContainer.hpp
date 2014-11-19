#pragma once

#ifndef _ENTITYSYSTEM_ENTITYCONTAINER_HPP_
#define _ENTITYSYSTEM_ENTITYCONTAINER_HPP_

#include <map>

#include "../Include/Entity.hpp"
#include "../../Utility/Include/IdGenerator.hpp"

namespace Fnd
{
namespace EntitySystem
{

class EntityContainer
{
	public:

		EntityContainer( EntitySystem* entity_system );

		Entity* CreateEntity();

		Entity* GetEntity( unsigned int entity_index );

		Entity* GetEntityByName( const std::string& name );

		bool RemoveEntity( unsigned int entity_index );

		bool RemoveEntity( Entity* entity );

		~EntityContainer();

	private:

		EntitySystem* _entity_system;

		Fnd::Utility::IdGenerator _id_generator;

		std::map<unsigned int, Entity> _entities;
};

}
}

#endif