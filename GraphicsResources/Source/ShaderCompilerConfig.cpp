#include "../Include/ShaderCompilerConfig.hpp"

#include "../../Utility/Include/XmlManager.hpp"
#include "../../Utility/Include/FileSystem.hpp"

#include <iostream>

using namespace Fnd::GraphicsResources;
using namespace Fnd::Utility;

bool ShaderCompilerConfig::Load( const std::string& directory, const std::string& filename )
{
	XmlManager xml_manager;
	xml_manager.CreateFromFile( directory + filename );

	auto root_node = xml_manager.Xml().first_node("Config");

	if ( !root_node )
	{
		std::cout << "Failed to find root 'Config' node" << std::endl;
		return false;
	}

	auto shaders_node = root_node->first_node("Shaders");

	if ( !shaders_node )
	{
		std::cout << "Failed to find root 'Shaders' node" << std::endl;
		return false;
	}

	auto source_dir_attrib = shaders_node->first_attribute("source_directory");

	if ( !source_dir_attrib )
	{
		std::cout << "Failed to find source_directory attribute" << std::endl;
		return false;
	}

	_shader_data.source_directory = FileSystem::CanonicaliseDirectory( directory + source_dir_attrib->value() );


	auto shaders_dir_attrib = shaders_node->first_attribute("output_directory");

	if ( !shaders_dir_attrib )
	{
		std::cout << "Failed to find output_directory attribute" << std::endl;
		return false;
	}

	_shader_data.output_directory = FileSystem::CanonicaliseDirectory( directory + shaders_dir_attrib->value() );


	auto shaders_debug_dir_attrib = shaders_node->first_attribute("output_directory_debug");

	if ( !shaders_debug_dir_attrib )
	{
		std::cout << "Failed to find output_directory_debug attribute" << std::endl;
		return false;
	}

	_shader_data.output_directory_debug = FileSystem::CanonicaliseDirectory( directory + shaders_debug_dir_attrib->value() );


	auto compiled_ext_attrib = shaders_node->first_attribute("compiled_extension");

	if ( !compiled_ext_attrib )
	{
		std::cout << "Failed to find compiled_extension attribute" << std::endl;
		return false;
	}

	_shader_data.compiled_extension = compiled_ext_attrib->value();


	auto shader_model_attrib = shaders_node->first_attribute("shader_model");

	if ( !shader_model_attrib )
	{
		std::cout << "Failed to find shader_model_attrib attribute" << std::endl;
		return false;
	}

	_shader_data.shader_model = shader_model_attrib->value();

	auto pipeline_iter = shaders_node->first_node();

	while ( pipeline_iter )
	{
		std::string name = pipeline_iter->name();
		ShaderData::Pipeline pipeline;

		auto vs_attrib = pipeline_iter->first_attribute("vs");
		if ( vs_attrib )
		{
			pipeline.vertex_shader = FileSystem::CanonicaliseFile( vs_attrib->value() );
		}

		auto hs_attrib = pipeline_iter->first_attribute("hs");
		if ( hs_attrib )
		{
			pipeline.hull_shader = FileSystem::CanonicaliseFile( hs_attrib->value() );
		}

		auto ds_attrib = pipeline_iter->first_attribute("ds");
		if ( ds_attrib )
		{
			pipeline.domain_shader = FileSystem::CanonicaliseFile( ds_attrib->value() );
		}

		auto gs_attrib = pipeline_iter->first_attribute("gs");
		if ( gs_attrib )
		{
			pipeline.geometry_shader = FileSystem::CanonicaliseFile( gs_attrib->value() );
		}

		auto ps_attrib = pipeline_iter->first_attribute("ps");
		if ( ps_attrib )
		{
			pipeline.pixel_shader = FileSystem::CanonicaliseFile( ps_attrib->value() );
		}

		auto cs_attrib = pipeline_iter->first_attribute("cs");
		if ( cs_attrib )
		{
			pipeline.compute_shader = FileSystem::CanonicaliseFile( cs_attrib->value() );
		}

		_shader_data.pipelines[name] = pipeline;

		pipeline_iter = pipeline_iter->next_sibling();
	}

	return true;
}

const ShaderCompilerConfig::ShaderData& ShaderCompilerConfig::GetShaderData() const
{
	return _shader_data;
}