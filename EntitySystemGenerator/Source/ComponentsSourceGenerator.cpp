#include "..\Include\ComponentsSourceGenerator.hpp"
#include "..\Include\ComponentDataConversion.hpp"

#include "..\..\Utility\Include\XmlManager.hpp"

#include "..\Include\ComponentDefinitionTags.hpp"

#include <algorithm>
#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;

ComponentsSourceGenerator::ComponentsSourceGenerator()
{
}

bool ComponentsSourceGenerator::Generate(	const ComponentDefinitions& component_definitions,
											const std::string& output_file )
{
	SetFilename( output_file );

	WriteComment();
	
	AddInclude( "../Include/Components.hpp" );
	AddInclude( "../Include/ComponentDataConversion.hpp" );
	AddInclude( "../../Utility/Include/XmlManager.hpp" );

	WriteIncludeFiles();

	File() << "using namespace Fnd::EntitySystem;\n\n";

	/*
		For each component node, create component code.
	*/
	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		if ( !CreateComponentCode( component_definitions.GetComponentDefinition(i), i ) )
		{
			return false;
		}
	}
	
	return CodeGenerator::WriteToFile();
}

bool ComponentsSourceGenerator::CreateComponentCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index )
{
	File() << component_definition.component_name << "_s::" << component_definition.component_name << "_s()";

	// The number of data values which require construction.
	unsigned int non_default_data_count = 0;
	for ( unsigned int i = 0; i < component_definition.data.size(); ++i )
	{
		if ( !component_definition.data[i].default_value.empty() )
		{
			++non_default_data_count;
		}
	}

	if (0) //if ( non_default_data_count != 0 )
	{
		File() << ":";
	}
	File() << '\n';
	
	/*
		For each data node.
	*/
	unsigned int constructor_count = 0;
	for ( unsigned int i = 0; i < component_definition.data.size(); ++i )
	{
		//if ( !component_definition.data[i].default_value.empty() )
		if(0)
		{
			++constructor_count;

			File() << "\t" << component_definition.data[i].data_name << "(";

			//File() << default_attrib->value();
		
			File() << ")";
			if ( i != constructor_count - 1 )
			{
				File() << ",";
			}

			File() << "\n";
		}
	}
	
	File() << "{\n}\n\n";

	// Destructor.	TODO: release memory OR add a Destroy method
	File() << component_definition.component_name <<  "_s::~" << component_definition.component_name << "_s()\n{\n";

	File() << "}\n\n";

	return true;
}