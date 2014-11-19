#pragma once

#ifndef _ASSETMANAGER_ASSETMANAGER_HPP_
#define _ASSETMANAGER_ASSETMANAGER_HPP_

#include "../../Utility/Include/XmlManager.hpp"
#include "../../Utility/Include/IdGenerator.hpp"
#include "Texture2D.hpp"
#include "Model.hpp"

#include <map>
#include <vector>
#include <memory>

namespace Fnd
{
namespace GameComponentInterfaces
{
class IAssetManagerMessageListener;
}
}

namespace Fnd
{
namespace AssetManager
{

class Texture2D;
struct Texture2DData;

class Model;
struct ModelData;

/**
	A class to manage loaded assets.
*/
class AssetManager
{
	private:

		/**
			A struct to describe the asset files to load.
		*/
		struct AssetData
		{
			struct Model
			{
				std::string name;
				std::string filename;
				float scale;
			};

			std::vector<Model> models;
		};

	public:

		/**
			Default Constructor.
		*/
		AssetManager();

		/**
			Set the a pointer to the game.
			@param game A pointer to the IAssetManagerMessageListener inferface of the Game component.
		*/
		void SetGame( Fnd::GameComponentInterfaces::IAssetManagerMessageListener* game );

		/**
			Load an asset file containing the assets required by the game.
			@param filename The name of the assets file.
			@returns Returns true if successful.
		*/
		bool LoadAssets( std::string& filename );

		/**
			Load a 2d texture.
			@param data The data required to load and create the texture.
			@return Returns the id of the loaded texture.
		*/
		unsigned int LoadTexture2D( const Texture2DData& data );

		/**
			Get a loaded 2d texture.
			@param id The id of the texture.
			@return Returns a pointer to the texture, or null if the texture does not exist.
		*/
		Texture2D* GetTexture2D( unsigned int id );

		/**
			Load a model.
			@param data The data required to load and create the model
			@return Returns the id of the loaded model.
		*/
		unsigned int LoadModel( const AssetData::Model& data );

		/**
			Get a loaded model.
			@param id The id of the model.
			@return Returns a pointer to the model, or null if the model does not exist.
		*/
		Model* GetModel( unsigned int id );

		/**
			Get an asset's id by name.
			@param name The name of the asset to get.
			@return Returns the id of the asset.
			@note All asset names must be unique- this method does not differentiate between different asset types.
		*/
		unsigned int GetAssetByName( const std::string& name );

		const ModelData& GetModelData( unsigned int id );

	private:

		/**
			Get the asset data from an xml file.
			@param assets_file The name of the assets file to load.
			@return Returns the contents of the assets file as a struct.
		*/
		AssetData GetAssetData( const std::string& assets_file );

		Fnd::GameComponentInterfaces::IAssetManagerMessageListener* _game;

		// There is currently only one counter for all assets
		Fnd::Utility::IdGenerator _id_generator;

		std::map<unsigned int,std::unique_ptr<Texture2D>> _texture2d_map;
		std::map<unsigned int,std::unique_ptr<Model>> _model_map;

		std::map<unsigned int,ModelData> _model_data;
};

}
}

#endif