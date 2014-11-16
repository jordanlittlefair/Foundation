#include "../Include/AssetManager.hpp"

#include "../../GameComponentInterfaces/Include/IAssetManagerMessageListener.hpp"
#include "../../GameComponentInterfaces/Include/IGraphics.hpp"
#include "../../ModelLoader/Include/ModelLoader.hpp"
#include "../../Utility/Include/XmlManager.hpp"
#include "../../Utility/Include/FileSystem.hpp"
#include "../../Logger/Include/Logger.hpp"

using namespace Fnd::AssetManager;
using namespace Fnd::ModelLoader;
using namespace Fnd::Logger;

AssetManager::AssetManager():
	_game(nullptr)
{
	_model_data[~0] = ModelData();
}

void AssetManager::SetGame( Fnd::GameComponentInterfaces::IAssetManagerMessageListener* game )
{
	_game = game;
}

AssetManager::AssetData AssetManager::GetAssetData( const std::string& assets_file )
{
	AssetData assets;

	std::string directory;
	std::string filename;
	Fnd::Utility::FileSystem::GetPathAndName( assets_file, directory, filename );

	Fnd::Utility::XmlManager assets_xml;
	if ( !assets_xml.CreateFromFile(assets_file) )
	{
		return assets;
	}
	
	auto assets_root = assets_xml.Xml().first_node("Assets");

	if ( !assets_root )
	{
		return assets;
	}

	auto model_group_iter = assets_root->first_node("Models");

	while ( model_group_iter )
	{
		auto models_iter = model_group_iter->first_node();

		auto model_group_dir_attrib = model_group_iter->first_attribute("directory");
		
		std::string model_group_dir = model_group_dir_attrib ? model_group_dir_attrib->value() : "";

		while ( models_iter )
		{
			AssetData::Model model;

			model.name = models_iter->name();

			auto filename_attrib = models_iter->first_attribute("filename");

			if ( filename_attrib )
			{
				model.filename = directory + model_group_dir + filename_attrib->value();
			}
			
			model.scale = 1.0f;
			auto scale_attrib = models_iter->first_attribute("scale");

			if ( scale_attrib )
			{
				model.scale = (float)atof( scale_attrib->value() );
			}

			assets.models.push_back(model);

			models_iter = models_iter->next_sibling();
		}

		model_group_iter = model_group_iter->next_sibling("Models");
	}

	return assets;
}

bool AssetManager::LoadAssets( std::string& filename )
{
	bool ret = true;

	Logger::Logger::GetInstance().Log( LogMessage( "Loading assets from \"" + filename + "\"...." ) );

	AssetData assets_data = GetAssetData( filename );
	
	for ( unsigned int i = 0; i < assets_data.models.size(); ++i )
	{
		if ( LoadModel(assets_data.models[i]) == ~0 )
		{
			ret =  false;
		}


	}

	if ( ret )
		Logger::Logger::GetInstance().Log( LogMessage( "Loaded assets from \"" + filename + "\"." ) );
	else
		Logger::Logger::GetInstance().Log( LogError( "Failed to load all assets from \"" + filename + "\"." ) );

	return ret;
}

unsigned int AssetManager::LoadTexture2D( const Texture2DData& data )
{
	Texture2D* texture = _game->GetGraphics()->GetNewTexture2D();

	if ( !texture )
	{
		return ~0;
	}

	if ( !texture->Create( data ) )
	{
		return ~0;
	}

	unsigned int id = _id_generator.GetId();

	_texture2d_map[id] = std::unique_ptr<Texture2D>(texture);

	return id;
}

unsigned int AssetManager::LoadModel( const AssetData::Model& model_desc )
{
	Logger::Logger::GetInstance().Log( LogMessage( "Loading model \"" + model_desc.name + "\" from \"" + model_desc.filename +"\"." ) );
	Model* model = _game->GetGraphics()->GetNewModel();

	if ( !model )
	{
		Logger::Logger::GetInstance().Log( LogError( "Failed to load \"" + model_desc.name + "\"; failed to get model from Graphics component." ) );
		return ~0;
	}

	model->SetName(model_desc.name);

	ModelData data;

	if ( !ModelLoader::ModelLoader::LoadModel( model_desc.filename, model_desc.scale, 0, data ) )
	{
		Logger::Logger::GetInstance().Log( LogError( "Failed to load \"" + model_desc.name + "\"; failed to load data from file." ) );
		return ~0;
	}
	
	if ( !model->Create( data ) )
	{
		Logger::Logger::GetInstance().Log( LogError( "Failed to load \"" + model_desc.name + "\"; failed to create model from data." ) );
		return ~0;
	}

	unsigned int id = _id_generator.GetId();

	_model_map[id] = std::unique_ptr<Model>(model);

	_model_data[id] = data;

	Logger::Logger::GetInstance().Log( LogMessage( "Loaded \"" + model_desc.name + "\"." ) );

	return id;
}

Model* AssetManager::GetModel( unsigned int id )
{
	auto iter = _model_map.find(id);
	
	return iter == _model_map.end() ? nullptr : &(*iter->second);
}

unsigned int AssetManager::GetAssetByName( const std::string& name )
{
	// TODO: must also search other asset types
	for ( auto iter = _model_map.begin(); iter != _model_map.end(); ++iter )
	{
		if ( iter->second->GetName() == name )
		{
			return iter->first;
		}
	}

	return ~0;
}

const ModelData& AssetManager::GetModelData( unsigned int id )
{
	auto found_iter = _model_data.find(id);

	if ( found_iter != _model_data.end() )
	{
		return found_iter->second;
	}
	else
	{
		return _model_data.find(~0)->second;
	}
}