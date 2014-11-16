#pragma once

#ifndef _SYSTEMNODESCONTAINERSOURCEGENERATOR_HPP_
#define _SYSTEMNODESCONTAINERSOURCEGENERATOR_HPP_

#include "CodeGenerator.hpp"

#include "SystemNodeDefinitions.hpp"

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class SystemNodesContainerSourceGenerator:
	public CodeGenerator
{
	public:

		bool Generate(	const SystemNodeDefinitions& systemnodes_definition,
						const std::string& output_file );
	private:

		bool CreateSystemNodeCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition );
};

}
}

#endif