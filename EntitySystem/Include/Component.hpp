#pragma once

#ifndef _COMPONENT_HPP_
#define _COMPONENT_HPP_

#include "ComponentId.hpp"

namespace Fnd
{
namespace EntitySystem
{
class Entity;
class SystemNode;
class ComponentMaps;

/**
	Base class for Components.
	Stores a list of nodes which the Component is attached to, and contains methods to add and remove Nodes from this list.

	Components should not directly inherit this, but should use the 'ComponentTemplate' instead.
*/
class Component
{
	public:

		// Set the index/id of this component.
		void SetIndex( unsigned int index );

		// Get the index/id of this component;
		unsigned int GetIndex() const;

		// Set the Component's owning Entity.
		void SetOwningEntity( unsigned int entity_id );

		// Kill the Entity to which this Component belongs.
		void KillOwningEntity();

        // Virtual Destructor.
		virtual ~Component();

		// Get the ID of the component.
		virtual unsigned int GetComponentID() const = 0;

	protected:

		// Default Constructor.
		// Cannot be instantiated directly; must use the ComponentTemplate class.
		Component();

	private:

		unsigned int _entity_id;
		unsigned int _index;
};


/*
	Template class for Components.

	T should be a struct containing the component's data.
*/
template <typename T, unsigned int component_id>
class ComponentTemplate:
	public Component
{
	public:

		// Default Constructor.
		ComponentTemplate();

		// Get the ID of the component.
		// Inherited from Component.
		unsigned int GetComponentID() const;

		static unsigned int GetComponentIDstatic();

		// Destructor.
		~ComponentTemplate();

		// The data stored in this component.
		T data;
};


/*
	Implementation
*/

template <typename T, unsigned int component_id>
ComponentTemplate<T,component_id>::ComponentTemplate():
	Component(),
	data()
{
}

template <typename T, unsigned int component_id>
unsigned int ComponentTemplate<T,component_id>::GetComponentID() const
{
	return component_id;
}

template <typename T, unsigned int component_id>
unsigned int ComponentTemplate<T,component_id>::GetComponentIDstatic()
{
	return component_id;
}

template <typename T, unsigned int component_id>
ComponentTemplate<T,component_id>::~ComponentTemplate()
{
}

}
}

#endif
