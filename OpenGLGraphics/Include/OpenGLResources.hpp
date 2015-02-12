#pragma once

#ifndef _OPENGLGRAPHICS_DIRECTX11RESOURCES_HPP_
#define _OPENGLGRAPHICS_DIRECTX11RESOURCES_HPP_

#include "../../Settings/Include/EngineSettings.hpp"
#include "../../Math/Include/Math.hpp"

#include <vector>
#include "../../glew/Include/glew.hpp"

namespace Fnd
{
namespace OpenGLGraphics
{
class OpenGLGraphics;

struct Pipeline
{
	Pipeline();

	GLuint vs;
	GLuint hs;
	GLuint ds;
	GLuint gs;
	GLuint fs;
	GLuint cs;

	GLuint program;
};

struct Texture2D
{
	Texture2D();

	GLuint framebuffer;
	GLuint texture;

	unsigned int width;
	unsigned int height;
	unsigned int mip_levels;
};

struct EngineMesh	// Currently only positions, no normals, uvs etc
{
	struct Vertex
	{
		Fnd::Math::Vector3 position;
	};

	EngineMesh();

	GLuint vertex_vbo;
	GLuint index_vbo;
	GLuint vao;

	unsigned int num_indices;
};

class OpenGLResources
{
	public:

		OpenGLResources( OpenGLGraphics* graphics );

		void SetConfig( const Fnd::Settings::EngineSettings::GraphicsSettings& config );

		bool GetSourceCodeFromFile( const std::string& filename, std::vector<char>& buffer ) const;
		const Fnd::CommonResources::PipelineDesc GetPipelineData( const std::string& pipeline ) const;

		bool Initialise();

		// If the explicit_name is blank, the texture's name will be set to its filename (for internal 'unnamed' textures)
		// Textures associated with a name (like engine textures) should pass this name as explicit_name
		bool LoadTexture( const Fnd::CommonResources::Texture2DDesc& texture_desc, const std::string& explicit_name = "" );

		const Pipeline& GetShaders( const std::string& pipeline ) const;

		const Texture2D& GetTexture( const std::string& texture ) const;

		const EngineMesh& GetMesh( const std::string& mesh ) const;

		~OpenGLResources();

	private:

		// Duplicated in OpenGLShaderCompiler... could do with refactoring
		GLuint CompileShader( const std::string& input_filename, GLuint type, std::string& error );

		bool LoadShaders();

		bool LoadEngineTextures();

		bool LoadEngineModels();
		
		Fnd::OpenGLGraphics::OpenGLGraphics* _graphics;

		Fnd::Settings::EngineSettings::GraphicsSettings _config;

		std::map<std::string,Pipeline> _pipelines;
		std::map<std::string,Texture2D> _textures;
		std::map<std::string,EngineMesh> _meshes;
};

}
}

#endif