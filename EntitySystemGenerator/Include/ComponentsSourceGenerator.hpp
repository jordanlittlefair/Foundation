#pragma once

#ifndef _COMPONENTSSOURCEGENERATOR_HPP_
#define _COMPONENTSSOURCEGENERATOR_HPP_

#include <string>

#include "CodeGenerator.hpp"

#include "ComponentDefinitions.hpp"

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class ComponentsSourceGenerator:
	public CodeGenerator
{
	public:

		ComponentsSourceGenerator();
		
		bool Generate(	const ComponentDefinitions& component_definitions,
						const std::string& output_file );
	private:

		bool CreateComponentCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index );
};

}
}

#endif