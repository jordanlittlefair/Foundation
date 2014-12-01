#pragma once

#ifndef _DIRECTX11SHADERCOMPILER_DIRECTX11SHADERCOMPILER_HPP_
#define _DIRECTX11SHADERCOMPILER_DIRECTX11SHADERCOMPILER_HPP_

#include "../../GraphicsResources/Include/ShaderCompilerConfig.hpp"

namespace Fnd
{
namespace DirectX11ShaderCompiler
{

class DirectX11ShaderCompiler
{
	public:

		bool CompileShaders( const Fnd::GraphicsResources::ShaderCompilerConfig::ShaderData& shader_data );

	private:

		bool CompileShader( const std::string& filename, const std::string& output_filename, const std::string& target, unsigned int flags );

		std::wstring GetWString( const char char_array[] );
};

}
}

#endif