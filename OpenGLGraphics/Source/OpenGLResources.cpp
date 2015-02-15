#include "../Include/OpenGLResources.hpp"

#include "../../Utility/Include/Image.hpp"
#include "../../Utility/Include/Utility.hpp"
#include "../../Utility/Include/MipMapGenerator.hpp"
#include "../../Utility/Include/String.hpp"

#include "../../ModelLoader/Include/ModelLoader.hpp"
#include "../../AssetManager/Include/Model.hpp"

#include <fstream>

using namespace Fnd::OpenGLGraphics;
using namespace Fnd::Utility;

Pipeline::Pipeline():
	vs(0),
	hs(0),
	ds(0),
	gs(0),
	fs(0),
	cs(0)
{
}

Texture2D::Texture2D():
	framebuffer(0),
	texture(0),
	width(0),
	height(0),
	mip_levels(0)
{
}

EngineMesh::EngineMesh():
	vertex_vbo(0),
	index_vbo(0),
	vao(0),
	num_indices(0)
{
}

OpenGLResources::OpenGLResources( OpenGLGraphics* graphics ):
	_graphics(nullptr)
{
}

void OpenGLResources::SetConfig( const Fnd::Settings::EngineSettings::GraphicsSettings& config )
{
	_config = config;
}

bool OpenGLResources::GetSourceCodeFromFile( const std::string& filename, std::vector<char>& buffer ) const
{
	std::ifstream filestream( filename, std::ios::in | std::ios::binary | std::ios::ate );

	if ( filestream.is_open() )
	{
		auto end = filestream.tellg();
		filestream.seekg(std::ios::beg);
		auto start = filestream.tellg();

		auto length = end-start;

		buffer.resize((unsigned int)length);

		if ( length != 0 )
		{
			filestream.read(&buffer[0],length);
		}

		filestream.close();

		return true;
	}

	return false;
}

const Fnd::CommonResources::PipelineDesc OpenGLResources::GetPipelineData( const std::string& pipeline ) const
{
	auto found_iter = _config.shader_pipelines.find(pipeline);
	if ( found_iter == _config.shader_pipelines.end() )
	{		
		return Fnd::CommonResources::PipelineDesc();
	}
	else
	{
		return found_iter->second;
	}
}

bool OpenGLResources::Initialise()
{
	if ( !LoadShaders() )
	{
		return false;
	}

	if ( !LoadEngineTextures() )
	{
		return false;
	}

	if ( !LoadEngineModels() )
	{
		return false;
	}

	return true;
}

bool OpenGLResources::LoadTexture( const Fnd::CommonResources::Texture2DDesc& texture_desc, const std::string& explicit_name )
{
	if ( _textures.find( texture_desc.filename ) != _textures.end() )
		return true;

	if ( texture_desc.filename.empty() )
		return false;

	Texture2D engine_texture;
	Fnd::Utility::Image image;

	unsigned int format = texture_desc.format;
		
	if ( image.CreateImageFromFile( texture_desc.filename, (Fnd::Utility::Image::Format)format, 0, 0, 0, 0 ) != Fnd::Utility::Image::Result::OK_Return )
	{
		return false;
	}

	engine_texture.mip_levels = Min( MipMapGenerator::GetNumMipLevels( image ), texture_desc.generate_mips ? ~0u : 1u );

	auto mipmaps = Fnd::Utility::MipMapGenerator::GenerateMipMaps( image, engine_texture.mip_levels );

	engine_texture.width = image.GetWidth();
	engine_texture.height = image.GetHeight();

	GLenum gl_format = 0;

	switch (format)
	{
	case 1:
		gl_format = GL_R;
		break;
	case 2:
		gl_format = GL_RG;
		break;
	case 3:
		gl_format = GL_RGB;
		break;
	case 4:
		gl_format = GL_RGBA;
		break;
	default:
		break;
	}

	glGenFramebuffers( 1, &engine_texture.framebuffer );
	glBindFramebuffer( GL_TEXTURE_2D, engine_texture.framebuffer );

	glGenTextures( 1, &engine_texture.texture );
	glBindTexture( GL_TEXTURE_2D, engine_texture.texture );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, (int)mipmaps.size() );

	for ( unsigned int i = 0; i < mipmaps.size(); ++i )
	{
		glTexImage2D( GL_TEXTURE_2D, i, gl_format, mipmaps[i].GetWidth(), mipmaps[i].GetHeight(), 0, gl_format, GL_UNSIGNED_BYTE, mipmaps[i].GetData() );
	}

	glFramebufferTexture( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, engine_texture.texture, 0 );

	GLenum draw_buffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers( 1, draw_buffers );
	
	glBindTexture( GL_TEXTURE_2D, 0 );
	glBindFramebuffer( GL_TEXTURE_2D, 0 );

	if ( glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE )
		return false;

	_textures[ explicit_name.empty() ? texture_desc.filename : explicit_name ] = engine_texture;

	return true;
}

const Pipeline& OpenGLResources::GetShaders( const std::string& pipeline ) const
{
	auto found_iter = _pipelines.find(pipeline);
	if ( found_iter == _pipelines.end() )
	{
		auto default_iter = _pipelines.find("");
		
		return default_iter->second;
	}
	else
	{
		return found_iter->second;
	}
}

const Texture2D& OpenGLResources::GetTexture( const std::string& texture ) const
{
	auto found_iter = _textures.find(texture);
	if ( found_iter == _textures.end() )
	{
		auto default_iter = _textures.find("");
		
		return default_iter->second;
	}
	else
	{
		return found_iter->second;
	}
}

const EngineMesh& OpenGLResources::GetMesh( const std::string& mesh ) const
{
	auto found_iter = _meshes.find(mesh);
	if ( found_iter == _meshes.end() )
	{
		auto default_iter = _meshes.find("");
		
		return default_iter->second;
	}
	else
	{
		return found_iter->second;
	}
}

OpenGLResources::~OpenGLResources()
{
	for ( auto pipeline_iter = _pipelines.begin(); pipeline_iter != _pipelines.end(); ++pipeline_iter )
	{
		if ( pipeline_iter->second.vs )
		{
			glDeleteShader( pipeline_iter->second.vs );
			pipeline_iter->second.vs = 0;
		}
		if ( pipeline_iter->second.hs )
		{
			glDeleteShader( pipeline_iter->second.hs );
			pipeline_iter->second.hs = 0;
		}
		if ( pipeline_iter->second.ds )
		{
			glDeleteShader( pipeline_iter->second.ds );
			pipeline_iter->second.ds = 0;
		}
		if ( pipeline_iter->second.gs )
		{
			glDeleteShader( pipeline_iter->second.gs );
			pipeline_iter->second.gs = 0;
		}
		if ( pipeline_iter->second.fs )
		{
			glDeleteShader( pipeline_iter->second.fs );
			pipeline_iter->second.fs = 0;
		}
		if ( pipeline_iter->second.program )
		{
			glDeleteProgram( pipeline_iter->second.program );
			pipeline_iter->second.program = 0;
		}
	}

	for ( auto texture_iter = _textures.begin(); texture_iter != _textures.end(); ++texture_iter )
	{
		if ( texture_iter->second.texture )
		{
			glDeleteTextures( 1, &texture_iter->second.texture );
			texture_iter->second.texture = 0;
		}
		if ( texture_iter->second.framebuffer )
		{
			glDeleteFramebuffers( 1, &texture_iter->second.framebuffer );
			texture_iter->second.framebuffer = 0;
		}
	}

	for ( auto mesh_iter = _meshes.begin(); mesh_iter != _meshes.end(); ++mesh_iter )
	{
		if ( mesh_iter->second.vertex_vbo )
		{
			glDeleteBuffers( 1, &mesh_iter->second.vertex_vbo );
			mesh_iter->second.vertex_vbo = 0;
		}
		if ( mesh_iter->second.index_vbo )
		{
			glDeleteBuffers( 1, &mesh_iter->second.index_vbo );
			mesh_iter->second.index_vbo = 0;
		}
		if ( mesh_iter->second.vao )
		{
			glDeleteVertexArrays( 1, &mesh_iter->second.vao );
			mesh_iter->second.vao = 0;
		}
	}
}

GLuint OpenGLResources::CompileShader( const std::string& input_filename, GLuint type, std::string& error )
{
	GLint compile_status = 0;

	GLuint shader = glCreateShader( type );

	std::vector<char> shader_source;
	if ( !GetSourceCodeFromFile( input_filename, shader_source ) )
		return 0;

	shader_source.push_back('\0');

	const char* shader_source_code = &shader_source.front();

	glShaderSource( shader, 1, &shader_source_code, 0 );
	
	glCompileShader( shader );

	glGetShaderiv( shader, GL_COMPILE_STATUS, &compile_status );

	if ( compile_status == GL_TRUE )
	{
		return shader;
	}
	else
	{
		const int length = 1024;
		GLchar log[length] = "";
		glGetShaderInfoLog( shader, length, nullptr, log );
		error = log;

		return 0;
	}
}

bool OpenGLResources::LoadShaders()
{
	// Create a default empty pipeline
	_pipelines[""] = Pipeline();

	for ( auto pipeline_iter = _config.shader_pipelines.begin(); pipeline_iter != _config.shader_pipelines.end(); ++pipeline_iter )
	{
		std::string name = pipeline_iter->first;

		if ( !pipeline_iter->second.vertex_shader.empty() )
		{
			std::string error;

			if ( !pipeline_iter->second.vertex_shader.empty() )
			{
				_pipelines[name].vs = CompileShader( pipeline_iter->second.vertex_shader, GL_VERTEX_SHADER, error );
				if ( !_pipelines[name].vs )
				{
					return false;
				}
			}

			if ( !pipeline_iter->second.geometry_shader.empty() )
			{
				_pipelines[name].gs = CompileShader( pipeline_iter->second.vertex_shader, GL_GEOMETRY_SHADER, error );
				if ( !_pipelines[name].gs )
				{
					return false;
				}
			}

			if ( !pipeline_iter->second.pixel_shader.empty() )
			{
				_pipelines[name].fs = CompileShader( pipeline_iter->second.pixel_shader, GL_FRAGMENT_SHADER, error );
				if ( !_pipelines[name].fs )
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool OpenGLResources::LoadEngineTextures()
{
	_textures[""] = Texture2D();
	
	for ( auto texture_iter = _config.common.textures.begin(); texture_iter != _config.common.textures.end(); ++texture_iter )
	{
		if ( !LoadTexture( texture_iter->second, texture_iter->first ) )
			return false;
	}

	return true;
}

bool OpenGLResources::LoadEngineModels()
{
	_meshes[""] = EngineMesh();

	for ( auto model_iter = _config.common.models.begin(); model_iter != _config.common.models.end(); ++model_iter )
	{
		Fnd::AssetManager::ModelData model_data;

		if ( !ModelLoader::ModelLoader::LoadModel( model_iter->second.filename, 1.0f, 0, model_data ) )
		{
			return false;
		}

		if ( model_data.meshes.size() != 1 )
		{
			return false;
		}

		auto& mesh_data = model_data.meshes[0];

		EngineMesh mesh;

		mesh.num_indices = (unsigned int)mesh_data.indices.size();

		glGenBuffers( 1, &mesh.vertex_vbo );
		glBindBuffer( GL_ARRAY_BUFFER, mesh.vertex_vbo );
		glBufferData( GL_ARRAY_BUFFER, mesh_data.vertices.size() * sizeof(EngineMesh::Vertex), &mesh_data.vertices[0], GL_STATIC_DRAW );
		glBindBuffer( GL_ARRAY_BUFFER, 0 );

		glGenBuffers( 1, &mesh.index_vbo );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.index_vbo );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, mesh_data.indices.size() * sizeof(unsigned int), &mesh_data.indices[0], GL_STATIC_DRAW );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

		glGenVertexArrays( 1, &mesh.vao );
		glBindVertexArray( mesh.vao );
		glBindBuffer( GL_ARRAY_BUFFER, mesh.vertex_vbo );
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.index_vbo );
		glEnableVertexAttribArray(0);
		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(EngineMesh::Vertex), 0 );

		glBindVertexArray(0);
		
		_meshes[model_iter->first] = mesh;
	}

	return true;
}