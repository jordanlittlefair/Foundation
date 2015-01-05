#include "../Include/ComponentMapsHeaderGenerator.hpp"

#include "../Include/ComponentDefinitionTags.hpp"

#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;

bool ComponentMapsHeaderGenerator::Generate(	const ComponentDefinitions& component_definitions,
						const std::string& output_file )
{
	SetFilename( output_file );

	WriteComment();

	WriteHeaderGuardStart();

	AddInclude( "Components.hpp" );
	AddInclude( "../../Utility/Include/IdGenerator.hpp" );
	AddInclude( "../../GameComponentInterfaces/Include/IWorld.hpp" );
	WriteIncludeFiles();
	File() << "#include <map>\n\n";
	
	File() << "namespace Fnd\n{\nnamespace EntitySystem\n{\n\n";
	File() << "class EntitySystem;\n\n";

	File() << "class ComponentMaps\n";
	File() << "{\n";

	File() << "private:\n";

	/*
		For each component node, create component code.
	*/
	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		if ( !CreateComponentDeclarationCode(component_definitions.GetComponentDefinition(i), i ) )
		{
			return false;
		}
	}

	File() << "\tFnd::Utility::IdGenerator _id_generator;\n\n";

	File() << "public:\n\n";
	
	File() << "\t/**\n";
	File() << "\t\tDefault constructor.\n";
	File() << "\t*/\n";
	File() << "\tComponentMaps();\n\n";

	File() << "\t/**\n";
	File() << "\t\tGet an existing component from its type and index.\n";
	File() << "\t\t@note Returns null if the component doesn't exist.\n";
	File() << "\t\t@tparam ComponentType The type of component.\n";
	File() << "\t\t@param index The index of the component.\n";
	File() << "\t\t@return Returns a pointer to the requested component.\n";
	File() << "\t*/\n";
	File() << "\ttemplate <typename ComponentType>\n";
	File() << "\tinline ComponentType* GetComponent( unsigned int index );\n\n";

	File() << "\t/**\n";
	File() << "\t\tGet an existing component from its type and index.\n";
	File() << "\t\t@note Returns null if the component doesn't exist.\n";
	File() << "\t\t@param component_id The id of the component type.\n";
	File() << "\t\t@param index The index of the component.\n";
	File() << "\t\t@return Returns a pointer to the requested component.\n";
	File() << "\t*/\n";
	File() << "\t Component* GetComponent( unsigned int component_id, unsigned int index );\n\n";

	File() << "\t/**\n";
	File() << "\t\tGet the map of 'ComponentType' components.\n";
	File() << "\t\t@tparam ComponentType The type of component to get the map for.\n";
	File() << "\t\t@return Returns a map of 'ComponentType' components.\n";
	File() << "\t*/\n";
	File() << "\ttemplate <typename ComponentType>\n";
	File() << "\tstd::map<unsigned int, ComponentType>& GetComponentMap();\n\n";

	File() << "\t/**\n";
	File() << "\t\tGet the map of 'ComponentType' components.\n";
	File() << "\t\t@tparam ComponentType The type of component to get the map for.\n";
	File() << "\t\t@return Returns a map of 'ComponentType' components.\n";
	File() << "\t*/\n";
	File() << "\ttemplate <typename ComponentType>\n";
	File() << "\tinline const std::map<unsigned int, ComponentType>& GetComponentMap() const;\n\n";

	File() << "\t/**\n";
	File() << "\t\tAdd a component to a map.\n";
	File() << "\t\t@tparam ComponentType The type of component to add.\n";
	File() << "\t\t@param component The new component with initial data.\n";
	File() << "\t\t@return Returns the id of the added component.\n";
	File() << "\t*/\n";
	File() << "\ttemplate <typename ComponentType>\n";
	File() << "\tinline ComponentType* AddComponent( const ComponentType& component = ComponentType() );\n\n";

	File() << "\t/**\n";
	File() << "\t\tCreate a Component from a WorldData::Entity::Component.\n";
	File() << "\t\tReturns null if the creation failed.\n";
	File() << "\t\t@param component_node The WorldData::Entity::Component which describes a component.\n";
	File() << "\t\t@return Returns a pointer to the component if successful.\n";
	File() << "\t*/\n";
	File() << "\tComponent* CreateComponent( const Fnd::GameComponentInterfaces::WorldData::Entity::Component& component_data, EntitySystem& entity_system, unsigned int& component_id );\n\n";

	File() << "\ttemplate <typename ComponentType>\n";
	File() << "\tinline bool RemoveComponent( ComponentType* component );\n\n";

	File() << "\tbool RemoveComponent( Component* component );\n\n";

	File() << "};\n\n";

	File() << "}\n}\n\n";

	/*
		Template function implementations.
	*/

	File() << "namespace Fnd\n{\nnamespace EntitySystem\n{\n\n";

	File() << "/*\n\tGetComponent<> implementations.\n*/\n\n";

	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		if ( !CreateGetComponentTemplateSpecialisationCode( component_definitions.GetComponentDefinition(i), i ) )
		{
			return false;
		}
	}

	File() << "\n/*\n\tGetComponentMap<> implementations.\n*/\n\n";

	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		if ( !CreateGetComponentMapTemplateSpecialisationCode( component_definitions.GetComponentDefinition(i), i,false) )
		{
			return false;
		}
	}

	File() << "\n/*\n\tAddComponent<> implementations.\n*/\n\n";

	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		if ( !CreateAddComponentTemplateSpecialisationCode( component_definitions.GetComponentDefinition(i), i ) )
		{
			return false;
		}
	}

	File() << "\n/*\n\tRemoveComponent<> implementations.\n*/\n\n";

	for ( unsigned int i = 0; i < component_definitions.GetNumComponents(); ++i )
	{
		if ( !CreateRemoveComponentTemplateSpecialisationCode(component_definitions.GetComponentDefinition(i), i ) )
		{
			return false;
		}
	}

	File() << "\n}\n}\n\n";

	WriteHeaderGuardEnd();

	return CodeGenerator::WriteToFile();
}

bool ComponentMapsHeaderGenerator::CreateComponentDeclarationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index )
{
	std::string component_str = component_definition.component_name;
	std::string component_lower;
	for ( unsigned int i = 0; i < component_str.length(); ++i )
	{
		component_lower += tolower(component_str[i]);
	}

	File() << "\tstd::map<unsigned int, " << component_definition.component_name << "> " << component_lower << ";\n";

	return true;
}

bool ComponentMapsHeaderGenerator::CreateGetComponentTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index )
{
	File() << "template <>\n";
	File() << "inline " << component_definition.component_name << "* ComponentMaps::GetComponent<" << component_definition.component_name << ">( unsigned int index )\n";
	File() << "{\n";

	std::string component_str = component_definition.component_name;
	std::string component_lower;
	for ( unsigned int i = 0; i < component_str.length(); ++i )
	{
		component_lower += tolower(component_str[i]);
	}

	File() << "\tauto iter = " << component_lower << ".find(index);\n";
	File() << "\treturn ( iter == " <<  component_lower << ".end() ) ? nullptr : &((*iter).second);\n";

	File() << "}\n";

	return true;
}

bool ComponentMapsHeaderGenerator::CreateGetComponentMapTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index, bool is_const )
{
	File() << "template <>\n";
	File() << "inline " << ( is_const ? "const " : "" ) << "std::map<unsigned int," << component_definition.component_name << ">& ComponentMaps::GetComponentMap<" << component_definition.component_name << ">()" << ( is_const ? " const" : "" ) << "\n";
	File() << "{\n";

	std::string component_str = component_definition.component_name;
	std::string component_lower;
	for ( unsigned int i = 0; i < component_str.length(); ++i )
	{
		component_lower += tolower(component_str[i]);
	}

	File() << "\treturn " << component_lower << ";\n";

	File() << "}\n";

	return true;
}

bool ComponentMapsHeaderGenerator::CreateAddComponentTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index )
{
	File() << "template <>\n";
	File() << "inline " << component_definition.component_name << "* ComponentMaps::AddComponent<" << component_definition.component_name << ">( const " << component_definition.component_name << "& component)\n";
	File() << "{\n";

	std::string component_str = component_definition.component_name;
	std::string component_lower;
	for ( unsigned int i = 0; i < component_str.length(); ++i )
	{
		component_lower += tolower(component_str[i]);
	}

	File() << "\tunsigned int index = _id_generator.GetId();\n";
	File() << "\t" << component_lower << "[index] = component;\n";
	File() << "\t" << component_lower << "[index].SetIndex(index);\n";
	File() << "\treturn &" << component_lower << "[index];\n";

	File() << "}\n";

	return true;
}

bool ComponentMapsHeaderGenerator::CreateRemoveComponentTemplateSpecialisationCode( const ComponentDefinitions::ComponentDefinition& component_definition, unsigned int component_index )
{
	File() << "template <>\n";
	File() << "inline bool ComponentMaps::RemoveComponent<" << component_definition.component_name << ">( " << component_definition.component_name << "* component )\n";
	File() << "{\n";

	std::string component_str = component_definition.component_name;
	std::string component_lower;
	for ( unsigned int i = 0; i < component_str.length(); ++i )
	{
		component_lower += tolower(component_str[i]);
	}

	File() << "\tauto iter = " << component_lower << ".find(component->GetIndex());\n";
	
	File() << "\tif ( iter != " << component_lower << ".end() )\n";
	File() << "\t{\n";
	File() << "\t\t" << component_lower << ".erase(iter);\n";
	File() << "\t\treturn true;\n";
	File() << "\t}\n";
	File() << "\telse\n";
	File() << "\t{\n";
	File() << "\t\treturn false;\n";
	File() << "\t}\n\n";

	File() << "\treturn true;\n";
	File() << "}\n";

	return true;
}