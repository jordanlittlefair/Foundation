#pragma once

#ifndef _OPENGLSHADERCOMPILER_OPENGLSHADERCOMPILER_HPP_
#define _OPENGLSHADERCOMPILER_OPENGLSHADERCOMPILER_HPP_

#include <string>

#include "../../GraphicsResources/Include/ShaderCompilerConfig.hpp"
#include "../../glew/Include/glew.hpp"

namespace Fnd
{
namespace OpenGLShaderCompiler
{

class OpenGLShaderCompiler
{
	public:

		OpenGLShaderCompiler();

		bool CompileShaders( const Fnd::GraphicsResources::ShaderCompilerConfig::ShaderData& shader_data );

	private:

		bool _initialised_successfully;

		GLuint CompileShader( const std::string& input_filename, const std::string& output_filename, GLuint type, std::string& error );
};

}
}

#endif
