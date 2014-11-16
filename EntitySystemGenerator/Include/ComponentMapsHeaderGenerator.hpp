#pragma once

#ifndef _COMPONENTMAPSHEADERGENERATOR_HPP_
#define _COMPONENTMAPSHEADERGENERATOR_HPP_

#include "CodeGenerator.hpp"

#include "ComponentDefinitions.hpp"

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class ComponentMapsHeaderGenerator:
	public CodeGenerator
{
	public:

		bool Generate(	const ComponentDefinitions& component_definitions,
						const std::string& output_file );

		bool CreateComponentDeclarationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index );

		bool CreateGetComponentTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index );

		bool CreateGetComponentMapTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index, bool is_const );

		bool CreateAddComponentTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index );

		bool CreateRemoveComponentTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index );
};

}
}

#endif