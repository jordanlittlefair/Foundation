#include "../Include/DirectX11ShaderCompiler.hpp"
#include "../../GraphicsResources/Include/ShaderCompilerConfig.hpp"

#include "../../Utility/Include/FileSystem.hpp"

int main()
{
	Fnd::GraphicsResources::ShaderCompilerConfig config;
	if ( !config.Load( "DirectX11ShaderCompiler/", "Config.xml" ) ) 
	{
		return 0;
	}

	/*
		Create directories
	*/
	auto directories = Fnd::Utility::FileSystem::GetDirectories( config.GetShaderData().output_directory_debug );
	std::string directory;
	for ( unsigned int i = 0; i < directories.size(); ++i )
	{
		directory += directories[i];
		auto res = Fnd::Utility::FileSystem::CreateNewDirectory( directory );
		directory += '/';
	}

	Fnd::DirectX11ShaderCompiler::DirectX11ShaderCompiler compiler;

	if ( !compiler.CompileShaders( config.GetShaderData() ) )
	{
		return 0;
	}


	system( "pause" );

	return 0;
}