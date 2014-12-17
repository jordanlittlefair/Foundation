#include "../Include/OpenGLModel.hpp"

#include "../Include/OpenGLGraphics.hpp"

using namespace Fnd::OpenGLGraphics;

OpenGLModel::OpenGLModel( Fnd::OpenGLGraphics::OpenGLGraphics* graphics ):
	_graphics(graphics)
{
}

bool OpenGLModel::Create( const Fnd::AssetManager::ModelData& data )
{
#ifndef _WIN32
    return true;
#endif
	for ( unsigned int i = 0; i < data.meshes.size(); ++i )
	{
		_resource.meshes.push_back(Model::Mesh());
		Model::Mesh& mesh = _resource.meshes.back();
		
		auto& mesh_data = data.meshes[i];

		{
			glGenBuffers( 1, &mesh.vertex_vbo );
			glBindBuffer( GL_ARRAY_BUFFER, mesh.vertex_vbo );
			glBufferData( GL_ARRAY_BUFFER, mesh_data.vertices.size() * sizeof(Model::Mesh::Vertex), &mesh_data.vertices[0], GL_STATIC_DRAW );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
		}
		{
			glGenBuffers( 1, &mesh.index_vbo );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.index_vbo );
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, mesh_data.indices.size() * sizeof(int), &mesh_data.indices[0], GL_STATIC_DRAW );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

			mesh.num_indices = mesh_data.indices.size();
		}
		{
			glGenVertexArrays( 1, &mesh.vao );
			glBindVertexArray( mesh.vao );
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh.index_vbo );
			glBindBuffer( GL_ARRAY_BUFFER, mesh.vertex_vbo );
			glEnableVertexAttribArray(0);
			glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof(Model::Mesh::Vertex), (void*)0 );
			glEnableVertexAttribArray(1);
			glVertexAttribPointer( 1, 3, GL_FLOAT, GL_TRUE, sizeof(Model::Mesh::Vertex), (void*)12 );
			glEnableVertexAttribArray(2);
			glVertexAttribPointer( 2, 3, GL_FLOAT, GL_TRUE, sizeof(Model::Mesh::Vertex), (void*)24 );
			glEnableVertexAttribArray(3);
			glVertexAttribPointer( 3, 2, GL_FLOAT, GL_FALSE, sizeof(Model::Mesh::Vertex), (void*)36 );
		
			glBindVertexArray(0);
		}
	}

	_resource.root_node = data.root_node;

	return true;
}

OpenGLModel::~OpenGLModel()
{
	for ( unsigned int i = 0; i < _resource.meshes.size(); ++i )
	{
		if ( _resource.meshes[i].vertex_vbo )
		{
			glDeleteBuffers( 1, &_resource.meshes[i].vertex_vbo );
		}	
		if ( _resource.meshes[i].index_vbo )
		{
			glDeleteBuffers( 1, &_resource.meshes[i].index_vbo );
		}
		if ( _resource.meshes[i].vao )
		{
			glDeleteVertexArrays( 1, &_resource.meshes[i].vao );
		}
	}
}

void* OpenGLModel::GetResource()
{
	return (void*)&_resource;
}