#pragma once

#ifndef _OPENGLSHADERCOMPILER_OPENGLSHADERCOMPILER_HPP_
#define _OPENGLSHADERCOMPILER_OPENGLSHADERCOMPILER_HPP_

#include <string>

#include "../../GraphicsResources/Include/ShaderCompilerConfig.hpp"
#ifdef _WIN32
#include "../../glew/Include/glew.hpp"
#else
#include <OpenGL/gl3.h>
#endif

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

		GLuint CompileShader( const std::string& input_filename, const std::string& output_filename, const std::string& debug_output_filename, GLuint type, std::string& error );
};

}
}

#endif
