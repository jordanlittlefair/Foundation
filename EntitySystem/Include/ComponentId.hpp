#pragma once

#ifndef _COMPONENTID_HPP_
#define _COMPONENTID_HPP_

namespace Fnd
{
namespace EntitySystem
{

/**
	A struct to store a component by its id.
	The component_id is the id of the component's type\n
	and the component_index is the index used as a lookup into\n
	the map referenced by component_id.
*/
struct ComponentId
{
	unsigned int component_type;
	unsigned int component_index;

	ComponentId()
	{
	}

	inline	ComponentId( unsigned int type, unsigned int index ):
		component_type(type),
		component_index(index)
	{
	}

	inline bool operator ==( const ComponentId& rhs ) const
	{
		return ( component_type == rhs.component_type ) && ( component_index == rhs.component_index );
	}
	inline bool operator !=( const ComponentId& rhs ) const
	{
		return ( component_type != rhs.component_type ) || ( component_index != rhs.component_index );
	}
};

}
}

#endif