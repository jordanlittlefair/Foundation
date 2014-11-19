#pragma once

#ifndef _ENTITYSYSTEMGENERATOR_SYSTEMNODEDEFINITIONS_HPP_
#define _ENTITYSYSTEMGENERATOR_SYSTEMNODEDEFINITIONS_HPP_

#include <string>
#include <vector>

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class SystemNodeDefinitions
{
	public:

		struct SystemNodeDefinition
		{
			std::string node_name;

			struct NodeComponent
			{
				std::string component_name;
			};

			std::vector<NodeComponent> components;
		};

		bool Load( const std::string& filename );

		unsigned int GetNumSystemNodes() const;

		const SystemNodeDefinition& GetSystemNodeDefinition( unsigned int i ) const;

	private:

		std::vector<SystemNodeDefinition> _nodes;
};

}
}

#endif