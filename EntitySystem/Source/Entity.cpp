#include "../Include/Entity.hpp"

#include "../Include/Components.hpp"

#include "../Include/EntitySystem.hpp"
#include "../Include/ComponentMaps.hpp"

#include <iostream>

#include <algorithm>

using namespace Fnd::EntitySystem;

Entity::Entity():
	_id(InvalidComponentId)
{
}

void Entity::SetId( unsigned int id )
{
	_id = id;
}

void Entity::SetName( const std::string& name )
{
	_name = name;
}

unsigned int Entity::GetId() const
{
	return _id;
}

std::string Entity::GetName() const
{
	return _name;
}

bool Entity::AddComponent( Component* component )
{
	auto iter = _components.find(component->GetComponentID());

	if ( iter != _components.end() )
	{
		return false;
	}
	else
	{
		_components[component->GetComponentID()] = component->GetIndex();
		component->SetOwningEntity(_id);
		
		return true;
	}
}

Component* Entity::GetComponent( unsigned int component_type, EntitySystem& entity_system ) const
{
	auto iter = _components.find( component_type );

	if ( iter != _components.end() )
	{
		return entity_system.GetComponentMaps().GetComponent( component_type, iter->second );
	}
	else
	{
		return nullptr;
	}
}

unsigned int Entity::GetComponentId( unsigned int component_type ) const
{
	auto iter = _components.find( component_type );

	if ( iter != _components.end() )
	{
		return iter->second;
	}
	else
	{
		return ~0;
	}
}

bool Entity::RemoveComponent( unsigned int component_type, EntitySystem& entity_system )
{
	auto iter = _components.find( component_type );

	if ( iter != _components.end() )
	{
		auto component = entity_system.GetComponentMaps().GetComponent( component_type, iter->second );
		if ( component )
		{
			component->SetOwningEntity(~0);
		}

		_components.erase(iter);

		return true;
	}
	else
	{
		return false;
	}
}


template <class ComponentType>
ComponentType* Fnd::EntitySystem::Entity::GetComponent( Fnd::EntitySystem::EntitySystem& entity_system ) const
{
    auto iter = _components.find( ComponentType::GetComponentIDstatic() );
    
    if ( iter != _components.end() )
    {
        return entity_system.GetComponentMaps().GetComponent<ComponentType>(iter->second);
    }
    else
    {
        return nullptr;
    }
}

void Entity::ClearComponents( EntitySystem& entity_system )
{
	for ( auto iter = _components.begin(); iter != _components.end(); ++iter )
	{
		auto component = entity_system.GetComponentMaps().GetComponent( iter->first, iter->second );
		if ( component )
		{
			component->SetOwningEntity(~0);
		}
	}
	_components.clear();
}

Entity::~Entity()
{
   assert( _components.empty() && "Entity is being deleted with components!" );
}

