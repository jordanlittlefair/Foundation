#pragma once

#ifndef _DIRECTX11SHADERCOMPILER_SHADERINCLUDER_HPP_
#define _DIRECTX11SHADERCOMPILER_SHADERINCLUDER_HPP_

#include <string>
#include <d3d11.h>

namespace Fnd
{
namespace DirectX11ShaderCompiler
{
class ShaderIncluder:
	public ID3DInclude
{
	public:

		// Constructor.
		// Takes the shader file as a parameter and gets the correct folder.
		ShaderIncluder( const std::string& shader );
 
		HRESULT __stdcall Open(	D3D_INCLUDE_TYPE IncludeType, 
								LPCSTR pFileName, 
								LPCVOID pParentData, 
								LPCVOID *ppData, 
								UINT *pBytes );

		HRESULT __stdcall Close( LPCVOID pData );

	private:

		std::string _shader_dir;

		std::string GetShaderFolder( const std::string& file_name );
};
}
}

#endif