#include "../Include/System.hpp"

using namespace Fnd::EntitySystem;

System::System( const std::string& system_name ):
	_system_name(system_name),
	_entity_system(nullptr),
	_asset_manager(nullptr)
{
}

void System::SetEntitySystem( EntitySystem* entity_system )
{
	_entity_system = entity_system;
}

void System::SetAssetManager( Fnd::AssetManager::AssetManager* asset_manager )
{
	_asset_manager = asset_manager;
}

std::string System::GetSystemName() const
{
	return _system_name;
}

void System::Update( const Fnd::CommonResources::FrameData& frame_data )
{
	OnUpdate( frame_data );
}

void System::AddNode( SystemNode* node )
{
	// Default implementation does nothing
}

std::vector<std::string> System::GetRegisteredNodes()
{
	return std::vector<std::string>();
}

System::~System()
{
}

EntitySystem& System::GetEntitySystem()
{
	return *_entity_system;
}

Fnd::AssetManager::AssetManager& System::GetAssetManager()
{
	return *_asset_manager;
}