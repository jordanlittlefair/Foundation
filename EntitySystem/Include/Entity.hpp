#pragma once

#ifndef _ENTITYSYSTEM_ENTITY_HPP_
#define _ENTITYSYSTEM_ENTITY_HPP_

#include <map>

#include "Components.hpp"
#include "EntitySystem.hpp"

namespace Fnd
{
namespace EntitySystem
{
class EntitySystem;
class Component;
/*
	An Entity class which stores Components.
*/
class Entity
{
	public:

        // Constructor.
		Entity();

		void SetId( unsigned int id );

		unsigned int GetId() const;

		// Set the name of the Entity.
		void SetName( const std::string& name );

		// Get the name of the Entity.
		std::string GetName() const;

		bool AddComponent( Component* component );

		template <class ComponentType>
		ComponentType* GetComponent( EntitySystem& entity_system ) const;

		Component* GetComponent( unsigned int component_type, EntitySystem& entity_system ) const;

		// Get a component's index by the Component ID.
		unsigned int GetComponentId( unsigned int component_type ) const;

		template <class ComponentType>
		unsigned int GetComponentId() const;

		// Remove a Component from the Entity by the Component type ID.
		bool RemoveComponent( unsigned int component_type, EntitySystem& entity_system );

		template <typename ComponentType>
		bool RemoveComponent( EntitySystem& entity_system );

		// Must be called before deleting the Entity.
		void ClearComponents( EntitySystem& entity_system );

		// Destructor.
		~Entity();

	private:

		std::string _name;

		unsigned int _id;

		// <type_id, index>
		std::map<unsigned int, unsigned int> _components;
};

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

template <class ComponentType>
unsigned int Fnd::EntitySystem::Entity::GetComponentId() const
{
	return GetComponentId( Fnd::EntitySystem::GetComponentId<ComponentType>() );
}

template <typename ComponentType>
bool Fnd::EntitySystem::Entity::RemoveComponent( EntitySystem& entity_system )
{
	auto iter = _components.find(GetComponentId<ComponentType>());
	if ( iter != _components.end() )
	{
		auto component = GetComponent<ComponentType>( entity_system );
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

}
}

#endif
