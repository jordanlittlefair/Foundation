#include "../Include/ComponentMapsSourceGenerator.hpp"

#include "..\Include\ComponentDefinitionTags.hpp"
#include "../../Utility/Include/XmlManager.hpp"

#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;

bool ComponentMapsSourceGenerator::Generate(	const ComponentDefinitions& component_definitions,
												const std::string& output_file )
{
	SetFilename( output_file );

	WriteComment();

	AddInclude( "../Include/ComponentMaps.hpp" );

	WriteIncludeFiles();

	File() << "using namespace Fnd::EntitySystem;\n\n";

	File() << "ComponentMaps::ComponentMaps()\n";
	File() << "{\n";
	File() << "}\n\n";

	File() << "Component* ComponentMaps::GetComponent( unsigned int component_id, unsigned int index )\n";
	File() << "{\n";

	File() << "\tswitch (component_id)\n";
	File() << "\t{\n";

	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		File() << "\t\tcase " << i << ":\n";
		File() << "\t\t\treturn GetComponent<" << component_definitions.GetComponentDefinition(i).component_name << ">(index);\n";
	}

	File() << "\t\tdefault:\n";
	File() << "\t\t\treturn nullptr;\n";

	File() << "}\n";

	File() << "}\n\n";	

	File() << "bool ComponentMaps::RemoveComponent( Component* component )\n";
	File() << "{\n";
	File() << "\tswitch (component->GetComponentID())\n";
	File() << "\t{\n";
	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		File() << "\t\tcase " << i << ":\n";
		File() << "\t\t\treturn RemoveComponent( (" << component_definitions.GetComponentDefinition(i).component_name << "*)component );\n";
	}
	File() << "\t\tdefault:\n";
	File() << "\t\t\treturn false;\n";
	File() << "}\n";

	File() << "}\n\n";

	return CodeGenerator::WriteToFile();
}