#pragma once

#ifndef _GRAPHICSRESOURCES_SHADERCOMPILERCONFIG_HPP_
#define _GRAPHICSRESOURCES_SHADERCOMPILERCONFIG_HPP_

#include <string>
#include <map>

namespace Fnd
{
namespace GraphicsResources
{

class ShaderCompilerConfig
{
	public:

		struct ShaderData
		{
			std::string source_directory;
			std::string output_directory;
			std::string output_directory_debug;
			std::string compiled_extension;
			std::string shader_model;

			struct Pipeline
			{
				std::string vertex_shader;
				std::string hull_shader;
				std::string domain_shader;
				std::string geometry_shader;
				std::string pixel_shader;

				std::string compute_shader;
			};

			std::map<std::string,Pipeline> pipelines;
		};

		bool Load( const std::string& directory, const std::string& filename );

		const ShaderData& GetShaderData() const;

	private:

		ShaderData _shader_data;
};

}
}

#endif