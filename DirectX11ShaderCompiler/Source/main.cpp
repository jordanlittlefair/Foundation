#include "../../Setup/Include/Setup.hpp"
#include "../Include/DirectX11ShaderCompiler.hpp"
#include "../Include/DirectX11ShaderCompilerConfig.hpp"
int main()
{
	Fnd::DirectX11ShaderCompiler::DirectX11ShaderCompilerConfig config;
	if ( !config.Load( "DirectX11ShaderCompiler/", "Config.xml" ) ) 
	{
		return 0;
	}

	Fnd::DirectX11ShaderCompiler::DirectX11ShaderCompiler compiler;

	if ( !compiler.CompileShaders( config.GetShaderData() ) )
	{
		return 0;
	}


	system( "pause" );

	return 0;
}