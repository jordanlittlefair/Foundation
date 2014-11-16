#include "../Include/EntitySystem.hpp"

#include "../Include/System.hpp"

#include "../Include/ComponentMaps.hpp"
#include "../Include/EntityContainer.hpp"
#include "../Include/SystemNodesContainer.hpp"

using namespace Fnd::EntitySystem;

//Component* EntitySystem::GetComponent( const ComponentId& component_id )
//{
//	return _component_maps.GetComponent( component_id.component_type, component_id.component_index );
//

EntitySystem::EntitySystem():
	_entity_container( new EntityContainer(this) ),
	_component_maps( new ComponentMaps() ),
	_system_nodes_container( new SystemNodesContainer(this) )
{
}

ComponentMaps& EntitySystem::GetComponentMaps()
{
	return *_component_maps;
}

EntityContainer& EntitySystem::GetEntityContainer()
{
	return *_entity_container;
}

SystemNodesContainer& EntitySystem::GetSystemNodesContainer()
{
	return *_system_nodes_container;
}

void EntitySystem::RegisterSystem( System* system )
{
	std::vector<std::string> system_nodes = system->GetRegisteredNodes();

	for ( unsigned int i = 0; i < system_nodes.size(); ++i )
	{
		_node_systems[system_nodes[i]].push_back(system);
	}
}

void EntitySystem::OnAddSystemNode( SystemNode* system_node )
{
	auto& systems_to_update = _node_systems[system_node->GetName()];

	for ( unsigned int i = 0; i < systems_to_update.size(); ++i )
	{
		systems_to_update[i]->AddNode( system_node );
	}
}