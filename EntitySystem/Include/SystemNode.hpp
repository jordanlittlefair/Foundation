#pragma once

#ifndef _ENTITYSYSTEM_SYSTEMNODE_HPP_
#define _ENTITYSYSTEM_SYSTEMNODE_HPP_

#include <string>

namespace Fnd
{
namespace EntitySystem
{

class SystemNode
{
	public:

		SystemNode( const std::string& name );

		std::string GetName() const;

		void SetIndex( unsigned int index );

		unsigned int GetIndex() const;

	private:

		std::string _name;
		unsigned int _index;
};

}
}

#endif