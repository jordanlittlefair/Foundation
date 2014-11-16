#pragma once

#ifndef _COMPONENTSHEADERGENERATOR_HPP_
#define _COMPONENTSHEADERGENERATOR_HPP_

#include "CodeGenerator.hpp"

#include "ComponentDefinitions.hpp"

#include <map>

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class ComponentsHeaderGenerator:
	public CodeGenerator
{
	public:

		bool Generate(	const ComponentDefinitions& component_definitions,
						const std::string& output_file );
	private:

		bool CreateComponentCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index );

		bool CreateGetComponentIdTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index );
};

}
}

#endif