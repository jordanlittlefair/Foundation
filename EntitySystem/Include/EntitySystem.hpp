#pragma once

#ifndef _ENTITYSYSTEM_ENTITYSYSTEM_HPP_
#define _ENTITYSYSTEM_ENTITYSYSTEM_HPP_

#include <map>
#include <vector>
#include <memory>

#include "Component.hpp"
#include "Components.hpp"
#include "../../GameComponentInterfaces/Include/IWorld.hpp"

namespace Fnd
{
namespace EntitySystem
{

class System;
class ComponentMaps;
class EntityContainer;
class SystemNodesContainer;

/**
	A container and manager for entities and components.
*/
class EntitySystem
{
	public:

		EntitySystem();

		ComponentMaps& GetComponentMaps();

		EntityContainer& GetEntityContainer();

		SystemNodesContainer& GetSystemNodesContainer();
						
		void RegisterSystem( System* system );

		void OnAddSystemNode( SystemNode* system_node );

	private:

		std::map<std::string,std::vector<Fnd::EntitySystem::System*>> _node_systems;	// map with <systemnode name, vector of systems which need updating>- needs a better name

		std::unique_ptr<ComponentMaps> _component_maps;
		std::unique_ptr<EntityContainer> _entity_container;
		std::unique_ptr<SystemNodesContainer> _system_nodes_container;
};

}
}

#endif