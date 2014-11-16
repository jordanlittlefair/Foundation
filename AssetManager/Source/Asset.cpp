#include "../Include/Asset.hpp"

using namespace Fnd::AssetManager;

Asset::Asset()
{
}

void Asset::SetName( const std::string& name )
{
	_name = name;
}

std::string Asset::GetName() const
{
	return _name;
}

Asset::~Asset()
{
}