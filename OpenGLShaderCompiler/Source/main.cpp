#include "../Include/OpenGLShaderCompiler.hpp"
#include "../../GraphicsResources/Include/ShaderCompilerConfig.hpp"

#include "../../Utility/Include/FileSystem.hpp"

int main()
{
	Fnd::GraphicsResources::ShaderCompilerConfig config;
	if ( !config.Load( "OpenGLShaderCompiler/", "Config.xml" ) ) 
	{
		return 0;
	}

	/*
		Create directories
	*/
	auto directories = Fnd::Utility::FileSystem::GetDirectories( config.GetShaderData().output_directory );
	std::string directory;
	for ( unsigned int i = 0; i < directories.size(); ++i )
	{
		directory += directories[i];
		Fnd::Utility::FileSystem::CreateNewDirectory( directory );
		directory += '/';
	}

	Fnd::OpenGLShaderCompiler::OpenGLShaderCompiler compiler;

	if ( !compiler.CompileShaders( config.GetShaderData() ) )
	{
		return 0;
	}

	return 0;
}