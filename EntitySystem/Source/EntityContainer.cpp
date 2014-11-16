#include "../Include/EntityContainer.hpp"

using namespace Fnd::EntitySystem;

EntityContainer::EntityContainer( EntitySystem* entity_system ):
	_entity_system(entity_system)
{
}

Entity* EntityContainer::CreateEntity()
{
	unsigned int id = _id_generator.GetId();

	Entity entity;
	entity.SetId(id);

	_entities[id].SetId(id);

	return &_entities[id];
}

Entity* EntityContainer::GetEntity( unsigned int entity_index )
{
	const auto iter = _entities.find(entity_index);

	if ( iter != _entities.end() )
	{
		return &(iter->second);
	}
	else
	{
		return nullptr;
	}
}

Entity* EntityContainer::GetEntityByName( const std::string& name )
{
	for ( auto iter = _entities.begin(); iter != _entities.end(); ++iter )
	{
		if ( name == iter->second.GetName() )
		{
			return &(iter->second);
		}
	}

	return nullptr;
}

bool EntityContainer::RemoveEntity( unsigned int entity_index )
{
	const auto iter = _entities.find(entity_index);

	if ( iter != _entities.end() )
	{
		iter->second.ClearComponents(*_entity_system);
		_entities.erase(iter);
		return true;
	}
	return false;
}

bool EntityContainer::RemoveEntity( Entity* entity )
{
	return RemoveEntity( entity->GetId() );
}

EntityContainer::~EntityContainer()
{
	for ( auto iter = _entities.begin(); iter != _entities.end(); ++iter )
	{
		iter->second.ClearComponents( *_entity_system );
	}
}