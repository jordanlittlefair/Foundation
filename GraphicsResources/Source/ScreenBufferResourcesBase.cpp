#include "../Include/ScreenBufferResourcesBase.hpp"

using namespace Fnd::GraphicsResources;

ScreenBufferResourcesBase::ScreenBufferResourcesBase():
	_width(0),
	_height(0)
{
}

bool ScreenBufferResourcesBase::Initialise( unsigned int w, unsigned int h )
{
	_width = w;
	_height = h;

	if ( !CreateResources() )
	{
		return false;
	}

	PositionReconstruction_cbuffer data;
	data.screen_size = Fnd::Math::Vector2( (float)w, (float)h );
	data.aspect_ratio = ((float)w) / ((float)h);
	data.tan_half_fov_y = 0;	// requires the first CameraManagerSystem::Update() to get the correct value

	UpdatePositionReconstructionData(data);

	return true;
}

unsigned int ScreenBufferResourcesBase::GetWidth() const
{
	return _width;
}

unsigned int ScreenBufferResourcesBase::GetHeight() const
{
	return _height;
}

bool ScreenBufferResourcesBase::Resize( unsigned int w, unsigned int h )
{
	_width = w;
	_height = h;

	ReleaseResources();
	
	if ( !CreateResources() )
	{
		return false;
	}

	auto data = GetPositionReconstructionData();
	data.screen_size = Fnd::Math::Vector2( (float)w, (float)h );
	data.aspect_ratio = ((float)w) / ((float)h);

	UpdatePositionReconstructionData(data);

	return true;
}

ScreenBufferResourcesBase::PositionReconstruction_cbuffer ScreenBufferResourcesBase::GetPositionReconstructionData() const
{
	return _position_reconstruction_data;
}

bool ScreenBufferResourcesBase::UpdatePositionReconstructionData( const ScreenBufferResourcesBase::PositionReconstruction_cbuffer& data )
{
	bool equal = 
		( data.screen_size.x == _position_reconstruction_data.screen_size.x ) &&
		( data.screen_size.y == _position_reconstruction_data.screen_size.y ) &&
		( data.aspect_ratio == _position_reconstruction_data.aspect_ratio ) &&
		( data.tan_half_fov_y == _position_reconstruction_data.tan_half_fov_y );

	if ( !equal )
	{
		_position_reconstruction_data = data;

		OnUpdatePositionReconstructionData(_position_reconstruction_data);
	}

	return !equal;
}

ScreenBufferResourcesBase::~ScreenBufferResourcesBase()
{
}