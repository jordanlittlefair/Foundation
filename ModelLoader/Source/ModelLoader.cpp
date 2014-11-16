#include "../Include/ModelLoader.hpp"

#include <functional>

#include "../../AssetManager/Include/Model.hpp"
#include "../../Utility/Include/FileSystem.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace Fnd::ModelLoader;
using namespace Fnd::AssetManager;

inline Fnd::Math::Vector2 ToFndVector( const aiVector2D& vec ) { return Fnd::Math::Vector2( vec.x, vec.y ); }
inline Fnd::Math::Vector3 ToFndVector( const aiVector3D& vec ) { return Fnd::Math::Vector3( vec.x, vec.y, vec.z ); }
inline Fnd::Math::Matrix4 ToFndMatrix( const aiMatrix4x4& mat ) 
{
	return Fnd::Math::Matrix4( 
		mat.a1, mat.a2, mat.a3, mat.a4,
		mat.b1, mat.b2, mat.b3, mat.b4,
		mat.c1, mat.c2, mat.c3, mat.c4,
		mat.d1, mat.d2, mat.d3, mat.d4 );
}

bool ModelLoader::LoadModel(	const std::string& filename,
								float scale,
								unsigned int flags,
								Fnd::AssetManager::ModelData& model_data )
{
	std::string directory;
	{
		std::string name_temp;
		Fnd::Utility::FileSystem::GetPathAndName( filename, directory, name_temp );
	}
	Assimp::Importer importer;

	//OutputDebugString( "Reading file....\n" );
	const aiScene* scene = importer.ReadFile(	filename, 
												aiProcess_JoinIdenticalVertices |
												aiProcess_MakeLeftHanded | 
												aiProcess_FlipWindingOrder |
												aiProcess_ImproveCacheLocality |
												aiProcess_RemoveRedundantMaterials |
												aiProcess_FindDegenerates |
												aiProcess_FindInvalidData |
												aiProcess_FindInstances |
												aiProcess_OptimizeMeshes |
												aiProcess_ValidateDataStructure |
												aiProcess_Triangulate | 
												//aiProcess_CalcTangentSpace | 
												//aiProcess_GenUVCoords |
												aiProcess_GenNormals |
												0 );
	
	//OutputDebugString( "File read complete.\n" );
	if ( !scene )
	{
		//OutputDebugString( importer.GetErrorString() );
		return nullptr;
	}

	/*
		Add each Mesh to the vector.
	*/
	for ( unsigned int i = 0; i < scene->mNumMeshes; ++i )
	{
		auto ai_mesh = scene->mMeshes[i];

		ModelData::Mesh mesh;
		
		/*
			Calculate vertices.
		*/

		for ( unsigned int j = 0; j < ai_mesh->mNumVertices; ++j )
		{
			ModelData::Mesh::Vertex vertex;
			
			vertex.position = ToFndVector( ai_mesh->mVertices[j]);

			// Scale
			vertex.position *= scale;

			vertex.normal = ToFndVector( ai_mesh->mNormals[j] );
			if ( ai_mesh->mTangents )
			{
				vertex.tangent = ToFndVector( ai_mesh->mTangents[j] );
			}
			else
			{
				vertex.tangent = normalise( cross( vertex.normal, Fnd::Math::Vector3( 0, 1, 0 ) ) );
				if ( length( vertex.tangent ) != 1.0f )//abs( length( vertex.tangent ) - 1.0f ) > 0.01f )
				{
					vertex.tangent = Fnd::Math::normalise( cross( Fnd::Math::Vector3( 1, 0, 0 ), vertex.normal ) );
				}
			}
			if ( ai_mesh->mTextureCoords[0] )
			{
				vertex.texcoord = Fnd::Math::Vector2( ai_mesh->mTextureCoords[0][j].x, ai_mesh->mTextureCoords[0][j].y );
			}
			else
			{
				vertex.texcoord = Fnd::Math::Vector2( 0, 0 );
			}

			mesh.vertices.push_back( vertex );
		}

		/*
			Calculate indices.
		*/

		for ( unsigned int j = 0; j < ai_mesh->mNumFaces; ++j )
		{
			mesh.indices.push_back( ai_mesh->mFaces[j].mIndices[0] );
			mesh.indices.push_back( ai_mesh->mFaces[j].mIndices[1] );
			mesh.indices.push_back( ai_mesh->mFaces[j].mIndices[2] );
		}

		/*
			Add the mesh to the vector.
		*/
		model_data.meshes.push_back( mesh );
	}

	/*
		Add the textures
	*/
	for ( unsigned int i = 0; i < scene->mNumMaterials; ++i )
	{
		aiMaterial* ai_mat = scene->mMaterials[i];

		ModelData::Material material;

		{
			/*
				Opacity
			*/
			aiString ai_opacity_filename;
			ai_mat->GetTexture( aiTextureType_OPACITY, 0, &ai_opacity_filename );
			if ( ai_opacity_filename.length != 0 )
			{
				std::string opacity_filename = Fnd::Utility::FileSystem::CanonicaliseFile( directory + ai_opacity_filename.C_Str() );

				material.opacity_map = opacity_filename;
			}
		}
		{
			/*
				Normal
			*/
			aiString ai_normal_filename;
			ai_mat->GetTexture( aiTextureType_HEIGHT, 0, &ai_normal_filename );
			if ( ai_normal_filename.length != 0 )
			{
				std::string normal_filename = Fnd::Utility::FileSystem::CanonicaliseFile( directory + ai_normal_filename.C_Str() );

				material.normal_map = normal_filename;
			}
		}
		{
			/*
				Diffuse
			*/
			aiString ai_diffuse_filename;
			ai_mat->GetTexture( aiTextureType_DIFFUSE, 0, &ai_diffuse_filename );
			if ( ai_diffuse_filename.length != 0 )
			{
				std::string diffuse_filename = Fnd::Utility::FileSystem::CanonicaliseFile( directory + ai_diffuse_filename.C_Str() );

				material.diffuse_map = diffuse_filename;
			}
		}
		{
			/*
				Roughness
			*/
			aiString ai_roughness_filename;
			ai_mat->GetTexture( aiTextureType_SHININESS, 0, &ai_roughness_filename );
			if ( ai_roughness_filename.length != 0 )
			{
				std::string roughness_filename = Fnd::Utility::FileSystem::CanonicaliseFile( directory + ai_roughness_filename.C_Str() );

				material.roughness_map = roughness_filename;
			}
		}
		{
			/*
				Specular
			*/
			aiString ai_specular_filename;
			ai_mat->GetTexture( aiTextureType_SPECULAR, 0, &ai_specular_filename );
			if ( ai_specular_filename.length != 0 )
			{
				std::string specular_filename = Fnd::Utility::FileSystem::CanonicaliseFile( directory + ai_specular_filename.C_Str() );

				material.specular_map = specular_filename;
			}
		}
		{
			/*
				Fresnel
			*/
			aiString ai_fresnel_filename;
			ai_mat->GetTexture( aiTextureType_UNKNOWN, 0, &ai_fresnel_filename );
			if ( ai_fresnel_filename.length != 0 )
			{
				std::string fresnel_filename = Fnd::Utility::FileSystem::CanonicaliseFile( directory + ai_fresnel_filename.C_Str() );

				material.fresnel_map = fresnel_filename;
			}
		}

		model_data.materials.push_back(material);
	}

	/*
		Add the model instances.
	*/
	aiNode* root_node = scene->mRootNode;

	std::function<void ( aiNode*, ModelData::MeshNode&)> AddNodeFun;

	AddNodeFun = [scene,&AddNodeFun,scale]( aiNode* node, ModelData::MeshNode& parent )
	{
		parent.children.push_back( ModelData::MeshNode() );

		for ( unsigned int i = 0; i < node->mNumMeshes; ++i )
		{
			parent.children.back().mesh_indices.push_back( node->mMeshes[i] );

			parent.children.back().material_index = scene->mMeshes[node->mMeshes[i]]->mMaterialIndex;
		}
		
		parent.children.back().transform = ToFndMatrix( node->mTransformation );

		// Scale
		parent.children.back().transform.m30 *= scale;
		parent.children.back().transform.m31 *= scale;
		parent.children.back().transform.m32 *= scale;
		
		for ( unsigned int i = 0; i < node->mNumChildren; ++i )
		{
			AddNodeFun( node->mChildren[i], parent.children.back() );
		}
	};
	
	for ( unsigned int i = 0; i < root_node->mNumMeshes; ++i )
	{
		model_data.root_node.mesh_indices.push_back( root_node->mMeshes[i] );
	}
	
	model_data.root_node.transform = ToFndMatrix( root_node->mTransformation );
	
	for ( unsigned int i = 0; i < root_node->mNumChildren; ++i )
	{
		AddNodeFun( root_node->mChildren[i], model_data.root_node );
	}
	
	return true;
}