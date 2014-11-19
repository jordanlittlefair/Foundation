#pragma once

#ifndef _ENTITYSYSTEMGENERATOR_COMPONENTDEFINITIONS_HPP_
#define _ENTITYSYSTEMGENERATOR_COMPONENTDEFINITIONS_HPP_

#include <string>
#include <vector>

namespace Fnd
{
namespace EntitySystemCodeGeneration
{

class ComponentDefinitions
{
	public:

		struct ComponentDefinition
		{
			std::string component_name;

			struct ComponentData
			{
				std::string data_name;
				std::string data_type;
				bool is_required;			// true if not supplied
				std::string default_value;	// only applicable if 'is_required' is false
				//bool is_clamped;			
				//std::string min;			// TODO: needs work to clamp vectors properly, and other data type clamping (quaternions etc)
				//std::string max;
			};

			std::vector<ComponentData> data;
		};

		bool Load( const std::string& filename );

		unsigned int GetNumComponents() const;

		const ComponentDefinition& GetComponentDefinition( unsigned int i ) const;

	private:

		std::vector<ComponentDefinition> _components;
};

}
}

#endif