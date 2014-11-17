#pragma once

#ifndef _COMPONENTMAPSSOURCEGENERATOR_HPP_
#define _COMPONENTMAPSSOURCEGENERATOR_HPP_

#include "CodeGenerator.hpp"

#include "ComponentDefinitions.hpp"

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class ComponentMapsSourceGenerator:
	public CodeGenerator
{
	public:

		bool Generate(	const ComponentDefinitions& component_definitions,
						const std::string& output_file );
};

}
}

#endif