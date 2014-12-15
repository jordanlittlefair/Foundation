#pragma once

#ifndef _OPENGLGRAPHICS_OPENGLMODEL_HPP_
#define _OPENGLGRAPHICS_OPENGLMODEL_HPP_

#include "../../AssetManager/Include/Model.hpp"

#ifdef _WIN32
#include "../../glew/Include/glew.hpp"
#else
#include <OpenGL/gl3.h>
#endif

#include <memory>

namespace Fnd
{
namespace OpenGLGraphics
{
class OpenGLGraphics;

class OpenGLModel:
	public Fnd::AssetManager::Model
{
	public:

		OpenGLModel( Fnd::OpenGLGraphics::OpenGLGraphics* graphics );

		bool Create( const Fnd::AssetManager::ModelData& data );

		~OpenGLModel();

		struct Model
		{
			struct Mesh
			{
				typedef Fnd::AssetManager::ModelData::Mesh::Vertex Vertex;

				GLuint vertex_vbo;
				GLuint index_vbo;
				GLuint vao;

				unsigned int num_indices;
			};

			typedef Fnd::AssetManager::ModelData::MeshNode MeshNode;

			std::vector<Mesh> meshes;

			MeshNode root_node;
		};

		void* GetResource();

	private:

		Fnd::OpenGLGraphics::OpenGLGraphics* _graphics;

		Model _resource;
};

}
}

#endif