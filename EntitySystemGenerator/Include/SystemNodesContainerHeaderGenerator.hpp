#pragma once

#ifndef _ENTITYSYSTEMGENERATOR_SYSTEMNODESCONTAINERHEADERGENERATOR_HPP_
#define _ENTITYSYSTEMGENERATOR_SYSTEMNODESCONTAINERHEADERGENERATOR_HPP_

#include "CodeGenerator.hpp"

#include "SystemNodeDefinitions.hpp"

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class SystemNodesContainerHeaderGenerator:
	public CodeGenerator
{
	public:

		bool Generate(	const SystemNodeDefinitions& systemnodes_definition,
						const std::string& output_file );
	private:

		bool CreateGetMethodCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition );
		bool CreateVariableCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition );
		bool CreateGetNodeMapSpecialisationCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition );
		bool CreateAddSystemNodeSpecialisationCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition );
		bool CreateRemoveSystemNodeSpecialisationCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition );
};

}
}

#endif