#include "../Include/SystemNode.hpp"

using namespace Fnd::EntitySystem;

SystemNode::SystemNode( const std::string& name ):
	_name(name),
	_index(~0)
{
}

std::string SystemNode::GetName() const
{
	return _name;
}

void SystemNode::SetIndex( unsigned int index )
{
	_index = index;
}

unsigned int SystemNode::GetIndex() const
{
	return _index;
}