#include "..\Include\ComponentsHeaderGenerator.hpp"

#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;

bool ComponentsHeaderGenerator::Generate(	const ComponentDefinitions& component_definitions,
											const std::string& output_file )
{
	SetFilename( output_file );

	WriteComment();

	WriteHeaderGuardStart();

	AddInclude( "Component.hpp" );
	AddInclude( "ComponentDataTypes.hpp" );

	WriteIncludeFiles();

	File() << "namespace Fnd\n{\nnamespace EntitySystem\n{\n\n";

	File() << "static const unsigned int InvalidComponentId = -1;\n\n";
	File() << "static const unsigned int InvalidComponentIndex = -1;\n\n";
	File() << "static const ComponentId InvalidComponent( InvalidComponentId, InvalidComponentIndex );\n\n";

	File() << "/**\n";
	File() << "\tGet the id of a component type.\n";
	File() << "\t@tparam ComponentType The type of component to add.\n";
	File() << "\t@return Returns the id of ComponentType.\n";
	File() << "*/\n";
	File() << "template <typename ComponentType>\n";
	File() << "inline unsigned int GetComponentId();\n\n";

	/*
		For each component node, create a component.
	*/
	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		if ( !CreateComponentCode( component_definitions.GetComponentDefinition(i), i ) )
		{
			return false;
		}
	}

	/*
		Create GetComponent<> template specialisation code.
	*/
	File() << "\n/*\n\tGetComponentId<> implementations.\n*/\n\n";

	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		if ( !CreateGetComponentIdTemplateSpecialisationCode(component_definitions.GetComponentDefinition(i),i) )
		{
			return false;
		}
	}


	File() << "}\n}\n\n";

	WriteHeaderGuardEnd();

	return CodeGenerator::WriteToFile();
}

bool ComponentsHeaderGenerator::CreateComponentCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index )
{	
	// struct ComponentX_s
	// {
	File() << "/// Struct generated for " << component_definition.component_name << ".\n";
	File() << "struct " << component_definition.component_name <<  "_s\n{\n";

	// ComponentX_s();
	File() << "\t" << component_definition.component_name << "_s();\n";

	// ~Component_s();
	File() << "\t~" << component_definition.component_name << "_s();\n\n";
	
	/*
		For each data node.
	*/
	for ( unsigned int i = 0; i < component_definition.data.size(); ++i )
	{
		// If this data node is not a special tag
		File() << '\t';

		File() << component_definition.data[i].data_type << ' ';
		
		// variable_name;
		File() << component_definition.data[i].data_name << ";\n";
	}
	
	// };
	File() << "};\n";

	// #define ComponentX_ID x
	File() << "#define ";
	std::string component_str = component_definition.component_name;
	std::string component_upper;
	for ( unsigned int i = 0; i < component_str.length(); ++i )
	{
		component_upper += toupper(component_str[i]);
	}
	File() << component_upper << "_ID " << component_index << "\n";

	// typedef ComponentTemplate<ComponentX_s,COMPONENTX_ID> ComponentX;
	File() << "/// Component<> class generated for " << component_definition.component_name << ".\n";
	File() << "typedef Fnd::EntitySystem::ComponentTemplate<" << component_definition.component_name << "_s, " << component_upper << "_ID> " 
			<< component_definition.component_name <<  ";\n\n";

	return true;
}

bool ComponentsHeaderGenerator::CreateGetComponentIdTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index )
{
	File() << "template <>\n";
	File() << "inline unsigned int GetComponentId<" << component_definition.component_name << ">()\n";
	File() << "{\n";

	std::string component_str = component_definition.component_name;
	std::string component_upper;
	for ( unsigned int i = 0; i < component_str.length(); ++i )
	{
		component_upper += toupper(component_str[i]);
	}
	component_upper += "_ID";
	File() << "\treturn " << component_upper << ";\n";

	File() << "}\n";

	return true;
}