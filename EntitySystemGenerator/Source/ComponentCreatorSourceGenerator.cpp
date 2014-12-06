#include "..\Include\ComponentCreatorSourceGenerator.hpp"
#include "..\Include\ComponentDataConversion.hpp"

#include "..\Include\ComponentDefinitionTags.hpp"

#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;

ComponentCreatorSourceGenerator::ComponentCreatorSourceGenerator()
{
}

bool ComponentCreatorSourceGenerator::Generate(	const ComponentDefinitions& component_definitions,
						const std::string& output_file )
{
	SetFilename( output_file );

	WriteComment();

	AddInclude( "../Include/ComponentDataConversion.hpp" );
	AddInclude( "../Include/EntitySystem.hpp" );
	AddInclude( "../Include/SystemNodes.hpp" );
	AddInclude( "../Include/Components.hpp" );
	AddInclude( "../Include/Entity.hpp" );
	AddInclude( "../Include/ComponentMaps.hpp" );
	AddInclude( "../Include/EntitySystem.hpp" );
	AddInclude( "../Include/EntityContainer.hpp" );
	AddInclude( "../Include/SystemNodes.hpp" );
	AddInclude( "../Include/SystemNodesContainer.hpp" );

	WriteIncludeFiles();

	File() << "#include <algorithm>\n\n";

	File() << "using namespace Fnd::EntitySystem;\n\n";
		
	File() << "template <typename ComponentType>\nComponent* CreateComponentInternal( const Fnd::GameComponentInterfaces::WorldData::Entity::Component& component_data, EntitySystem& entity_system );\n\n";

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

	File() << "Component* Fnd::EntitySystem::ComponentMaps::CreateComponent( const Fnd::GameComponentInterfaces::WorldData::Entity::Component& component_data, EntitySystem& entity_system, unsigned int& component_id )\n";
	File() << "{\n";
	
	
	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		File() << "\tif ( component_data.name == \"" << component_definitions.GetComponentDefinition(i).component_name << "\" )\n";
		File() << "\t{\n";

		std::string component_str = component_definitions.GetComponentDefinition(i).component_name;
		std::string component_upper;
		for ( unsigned int j = 0; j < component_str.length(); ++j )
		{
			component_upper += toupper(component_str[j]);
		}
		component_upper += "_ID";

		File() << "\t\tcomponent_id = " << component_upper << ";\n";
		File() << "\t\treturn CreateComponentInternal<" << component_definitions.GetComponentDefinition(i).component_name << ">( component_data, entity_system );\n";
		File() << "\t}\n";

		if ( i == component_definitions.GetNumComponents() - 1 && i != 0 ) 
		{
			File() << "\telse\n";
		}
	}
	
	File() << "\treturn nullptr;\n";

	File() << "}\n\n";

	return CodeGenerator::WriteToFile();
}

bool ComponentCreatorSourceGenerator::CreateComponentCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index )
{
	File() << "template <>\nComponent* CreateComponentInternal<" << component_definition.component_name << ">( const Fnd::GameComponentInterfaces::WorldData::Entity::Component& component_data, EntitySystem& entity_system )\n{\n";

	File() << "\t" << component_definition.component_name << " tempcomponent;\n";
	File() << "\tbool success = true;\n";
	//File() << "return ComponentId();\n}\n"; return true;
	
	for ( unsigned int i = 0; i < component_definition.data.size(); ++i )
	{
		File() << "\tdo\n\t{\n";

		if ( ComponentDataConversion::IsAutoConverted( component_definition.data[i].data_type ) )
		{

			//do some 'is specialised' checks here to avoid trying to get the value

			File() << "\t\tauto data = component_data.data.find(\"" << component_definition.data[i].data_name << "\");\n";
		
			File() << "\t\tif ( data == component_data.data.end() )\n";
			File() << "\t\t{\n";

			if ( component_definition.data[i].is_required )
			{
				File() << "\t\t\tsuccess = false;\n";
				File() << "\t\t\tbreak;\n";
			}
			else
			{
				File() << "\t\t\tConvertFromString<" << component_definition.data[i].data_type << ">( \"" << component_definition.data[i].default_value << "\", " << "tempcomponent.data." << component_definition.data[i].data_name << " );\n";
				File() << "\t\t\tbreak;\n";
			}
			
			File() << "\t\t}\n\n";

			File() << "\t\tconst char* as_string = data->second.value.c_str();\n\n";
		

			File() << "\t\tConvertFromString<" << component_definition.data[i].data_type << ">( as_string, " << "tempcomponent.data." << component_definition.data[i].data_name << " );\n";
			std::string conversion_code = ComponentDataConversion::GetConversionCode( component_definition.data[i].data_type );

		}
		else
		{
			return false;
		}		

		File() << "\t}\n\twhile(false);\n\n";
	}

	File() << "\tif ( success )\n\t{\n";
	File() << "\t\treturn entity_system.GetComponentMaps().AddComponent<" << component_definition.component_name << ">(tempcomponent);\n";
	File() << "\t}\n\telse\n\t{\n";
	File() << "\t\treturn nullptr;\n";
	File() << "\t}\n";

	File() << "}\n\n";
	
	return true;
}