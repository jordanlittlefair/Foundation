#pragma once

#ifndef _ENTITYSYSTEMGENERATOR_SYSTEMNODESHEADERGENERATOR_HPP_
#define _ENTITYSYSTEMGENERATOR_SYSTEMNODESHEADERGENERATOR_HPP_

#include "CodeGenerator.hpp"

#include "SystemNodeDefinitions.hpp"

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class SystemNodesHeaderGenerator:
	public CodeGenerator
{
	public:

		bool Generate(	const SystemNodeDefinitions& systemnode_definitions,
						const std::string& output_file );
	private:

		bool CreateSystemNodeCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition );
};

}
}

#endif