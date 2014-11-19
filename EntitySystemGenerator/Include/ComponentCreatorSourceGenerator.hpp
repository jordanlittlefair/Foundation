#pragma once

#ifndef _ENTITYSYSTEMGENERATOR_COMPONENTCREATORSOURCEGENERATOR_HPP_
#define _ENTITYSYSTEMGENERATOR_COMPONENTCREATORSOURCEGENERATOR_HPP_

#include "CodeGenerator.hpp"

#include "ComponentDefinitions.hpp"

#include <vector>

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class ComponentCreatorSourceGenerator:
	public CodeGenerator
{
	public:

		ComponentCreatorSourceGenerator();

		bool Generate(	const ComponentDefinitions& component_definitions,
						const std::string& output_file );

	private:

		bool CreateComponentCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index );
};

}
}

#endif