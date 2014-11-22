#include "../Include/EngineSettings.hpp"
#include "../../Utility/Include/XmlManager.hpp"

using namespace Fnd::Settings;
using namespace Fnd::Utility;


bool EngineSettings::Load( const std::string& filename, const ApplicationSettings& application_settings )
{
	auto last_slash = filename.find_last_of('/');
	std::string directory = ( last_slash != std::string::npos ) ? filename.substr(0,filename.find_last_of('/')) + '/' : "";

	XmlManager setup_xml;
	if ( !setup_xml.CreateFromFile( filename ) )
	{
		return false;
	}

	auto root_node = setup_xml.Xml().first_node("Config");

	if ( !root_node )
	{
		return false;
	}

	{
		auto window_root = root_node->first_node("Window");
		if ( !window_root )
		{
			return false;
		}

		auto window_iter = window_root->first_node();
		std::map<EngineConfig::WindowImplementation,WindowSettings> available_impls;
		while (window_iter)
		{
			EngineConfig::WindowImplementation impl = EngineConfig::GetWindowImplementation(window_iter->name());
			if ( !impl )
			{
				continue;
			}

			available_impls[impl] = LoadWindowImplementation( "", "", "" );

			window_iter = window_iter->next_sibling();
		}

		_window_settings = available_impls[application_settings.GetWindowSettings().implementation];
	}

	{
		auto graphics_root = root_node->first_node("Graphics");
		std::map<EngineConfig::GraphicsImplementation,GraphicsSettings> available_impls;
		if ( !graphics_root )
		{
			return false;
		}

		auto graphics_iter = graphics_root->first_node();

		while (graphics_iter)
		{
			auto impl_dir_attrib = graphics_iter->first_attribute("directory");
			if ( !impl_dir_attrib )
			{
				return false;
			}
			auto impl_file_attrib = graphics_iter->first_attribute("config_file");
			if ( !impl_file_attrib )
			{
				return false;
			}
			std::string impl_directory = directory + impl_dir_attrib->value();
			std::string impl_config_file = impl_file_attrib->value();

			EngineConfig::GraphicsImplementation impl = EngineConfig::GetGraphicsImplementation(graphics_iter->name());
			if ( !impl )
			{
				continue;
			}

			available_impls[impl] = LoadGraphicsImplementation( impl_directory, impl_config_file, graphics_iter->value() );

			graphics_iter = graphics_iter->next_sibling();
		}
			
		_graphics_settings = available_impls[application_settings.GetGraphicsSettings().implementation];

		auto common_dir_attrib = graphics_root->first_attribute("common_directory");
		if ( !common_dir_attrib )
		{
			return false;
		}
		auto common_file_attrib = graphics_root->first_attribute("common_config_file");
		if ( !common_file_attrib )
		{
			return false;
		}
		std::string common_directory = directory + common_dir_attrib->value();
		std::string common_config_file = common_file_attrib->value();

		_graphics_settings.common = LoadGraphicsCommon( common_directory,common_config_file );
	}

	return true;
}

EngineSettings::WindowSettings EngineSettings::LoadWindowImplementation( const std::string& directory, const std::string& filename, const std::string& name )
{
	// There are currently no window config files in the Engine.
	WindowSettings ret;

	ret.placeholder = 0;

	return ret;
}

EngineSettings::GraphicsSettings::GraphicsCommon EngineSettings::LoadGraphicsCommon( const std::string& directory, const std::string& filename )
{
	EngineSettings::GraphicsSettings::GraphicsCommon ret;

	XmlManager setup_xml;
	if ( !setup_xml.CreateFromFile( directory + filename ) )
	{
		return ret;
	}

	auto root_node = setup_xml.Xml().first_node("Config");

	if ( !root_node )
	{
		return ret;
	}

	{
		auto textures_root = root_node->first_node("Textures");
		if ( !textures_root )
		{
			return ret;
		}

		auto textures_dir_attrib = textures_root->first_attribute("directory");
		if ( !textures_dir_attrib )
		{
			return ret;
		}
		std::string textures_directory = textures_dir_attrib->value();

		auto textures_iter = textures_root->first_node();
		while ( textures_iter )
		{
			auto texture_filename_attrib = textures_iter->first_attribute("filename");
			if ( !texture_filename_attrib )
			{
				return ret;
			}
			std::string texture_filename = directory + textures_directory + texture_filename_attrib->value();

			auto generate_mips_attrib = textures_iter->first_attribute("generate_mips");
			if ( !generate_mips_attrib )
			{
				return ret;
			}
			bool generate_mips = std::string(generate_mips_attrib->value()) == "true";

			auto format_attrib = textures_iter->first_attribute("format");
			if ( !format_attrib )
			{
				return ret;
			}

			using namespace Fnd::CommonResources;

			std::string format_str = format_attrib->value();
			Fnd::CommonResources::Texture2DDesc::Format format = Texture2DDesc::FormatUnknown;
			if ( format_str == "r" )
				format = Texture2DDesc::FormatR;
			else if ( format_str == "rg" )
				format = Texture2DDesc::FormatRG;
			else if ( format_str == "rgb" )
				format = Texture2DDesc::FormatRGB;
			else if ( format_str == "rgba" )
				format = Texture2DDesc::FormatRGBA;

			ret.textures[textures_iter->name()].filename = texture_filename;
			ret.textures[textures_iter->name()].generate_mips = generate_mips;
			ret.textures[textures_iter->name()].format = format;

			textures_iter = textures_iter->next_sibling();
		}
	}

	auto models_root = root_node->first_node("Models");
	if ( !models_root )
	{
		return ret;
	}

	auto models_dir_attrib = models_root->first_attribute("directory");
	if ( !models_dir_attrib )
	{
		return ret;
	}
	std::string textures_directory = models_dir_attrib->value();

	auto models_iter = models_root->first_node();
	while ( models_iter )
	{
		auto model_filename_attrib = models_iter->first_attribute("filename");
		if ( !model_filename_attrib )
		{
			return ret;
		}
		std::string model_filename = directory + textures_directory + model_filename_attrib->value();

		ret.models[models_iter->name()].filename = model_filename;

		models_iter = models_iter->next_sibling();
	}

	return ret;
}

EngineSettings::GraphicsSettings EngineSettings::LoadGraphicsImplementation( const std::string& directory, const std::string& filename, const std::string& name )
{
	EngineSettings::GraphicsSettings ret;

	XmlManager setup_xml;
	if ( !setup_xml.CreateFromFile( directory + filename ) )
	{
		return ret;
	}

	auto root_node = setup_xml.Xml().first_node("Config");

	if ( !root_node )
	{
		return ret;
	}

	auto shaders_root = root_node->first_node("Shaders");
	if ( !shaders_root )
	{
		return ret;
	}

#ifdef _DEBUG
	const char shaders_directory_attrib_name[] = "debug_directory";
#else
	const char shaders_directory_attrib_name[] = "directory";
#endif

	auto shaders_dir_attrib = shaders_root->first_attribute(shaders_directory_attrib_name);
	if ( !shaders_dir_attrib )
	{
		return ret;
	}
	std::string shaders_directory = shaders_dir_attrib->value();

	auto shaders_iter = shaders_root->first_node();
	while ( shaders_iter )
	{
		std::string pipeline_name = shaders_iter->name();
		Fnd::CommonResources::PipelineDesc pipeline;

		auto vs_attrib = shaders_iter->first_attribute("vs");
		if ( vs_attrib )
		{
			pipeline.vertex_shader = directory + shaders_directory + vs_attrib->value();
		}

		auto hs_attrib = shaders_iter->first_attribute("hs");
		if ( hs_attrib )
		{
			pipeline.hull_shader = directory + shaders_directory + hs_attrib->value();
		}

		auto ds_attrib = shaders_iter->first_attribute("ds");
		if ( ds_attrib )
		{
			pipeline.domain_shader = directory + shaders_directory + ds_attrib->value();
		}

		auto gs_attrib = shaders_iter->first_attribute("gs");
		if ( gs_attrib )
		{
			pipeline.geometry_shader = directory + shaders_directory + gs_attrib->value();
		}

		auto ps_attrib = shaders_iter->first_attribute("ps");
		if ( ps_attrib )
		{
			pipeline.pixel_shader = directory + shaders_directory + ps_attrib->value();
		}

		auto cs_attrib = shaders_iter->first_attribute("cs");
		if ( cs_attrib )
		{
			pipeline.compute_shader = directory + shaders_directory + cs_attrib->value();
		}

		ret.shader_pipelines[pipeline_name] = pipeline;

		shaders_iter = shaders_iter->next_sibling();
	}

	return ret;
}

const EngineSettings::WindowSettings& EngineSettings::GetWindowSettings() const
{
	return _window_settings;
}

const EngineSettings::GraphicsSettings& EngineSettings::GetGraphicsSettings() const
{
	return _graphics_settings;
}