#include "../Include/Component.hpp"

using namespace Fnd::EntitySystem;

Component::Component():
	_entity_id(~0),
	_index(~0)
{
}

void Component::SetIndex( unsigned int index )
{
	_index = index;
}

unsigned int Component::GetIndex() const
{
	return _index;
}

void Component::SetOwningEntity( unsigned int entity_id )
{
	_entity_id = entity_id;
}

void Component::KillOwningEntity()
{
    if ( _entity_id != ~0u )
	{
		//TODO:_entity->Kill();
	}
}

Component::~Component()
{
}
