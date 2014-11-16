#include "../Include/OculusRift.hpp"

#include "../../Utility/Include/Utility.hpp"

#include <OVR.h>

#define OVR_D3D_VERSION 11
#include <../Src/OVR_CAPI_D3D.h>

using namespace Fnd::OculusRift;

struct Fnd::OculusRift::OculusData
{
	OculusData():
		hmd(nullptr),
		eye_texture_width(0),
		eye_texture_height(0),
		right_eye_texture_width(0),
		right_eye_texture_height(0),
		left_eye_texture_width(0),
		left_eye_texture_height(0)
	{
		memset( this, 0, sizeof(OculusData) );
	}

	ovrHmd hmd;

	unsigned int eye_texture_width;
	unsigned int eye_texture_height;
	unsigned int right_eye_texture_width;
	unsigned int right_eye_texture_height;
	unsigned int left_eye_texture_width;
	unsigned int left_eye_texture_height;

	ovrRecti		eyerender_viewport[2];
	ovrD3D11Texture	eyetexture[2];
	ovrD3D11Config d3d11cfg;
	ovrEyeRenderDesc   eyerender_desc[2];
	ovrPosef eyerender_pose[2];
};

OculusRift::OculusRift():
	_window(nullptr),
	_graphics(nullptr),
	_oculus_data(new OculusData())
{
}

void OculusRift::SetWindow( Fnd::GameComponentInterfaces::IWindow* window )
{
	_window = window;
}

void OculusRift::SetGraphics( Fnd::GameComponentInterfaces::IGraphics* graphics )
{
	_graphics = graphics;
}

bool OculusRift::InitialiseStart()
{
	auto a = ovr_Initialize();
	if ( !a )
	{
		return false;
	}
	_oculus_data->hmd = ovrHmd_Create(0);
	if ( !_oculus_data->hmd )
	{
		return false;
	}
		
	auto b = ovrHmd_AttachToWindow( _oculus_data->hmd, _window->GetHWND(), nullptr, nullptr );
	if ( !b )
	{
		return false;
	}	

	return true;
}

bool OculusRift::Initialise()
{
	//_window->SetWindowSize( 1920, 1080 );
	//_graphics->Resize(1920,1080);
	
	float pixelsPerDisplayPixel = 1;	// TODO: make this a user settings variable


	_oculus_data->right_eye_texture_width = ovrHmd_GetFovTextureSize(_oculus_data->hmd, ovrEye_Right,  _oculus_data->hmd->DefaultEyeFov[0], pixelsPerDisplayPixel ).w;
	_oculus_data->right_eye_texture_height = ovrHmd_GetFovTextureSize(_oculus_data->hmd, ovrEye_Right,  _oculus_data->hmd->DefaultEyeFov[0], pixelsPerDisplayPixel ).h;
	_oculus_data->left_eye_texture_width = ovrHmd_GetFovTextureSize(_oculus_data->hmd, ovrEye_Left,  _oculus_data->hmd->DefaultEyeFov[0], pixelsPerDisplayPixel ).w;
	_oculus_data->left_eye_texture_height = ovrHmd_GetFovTextureSize(_oculus_data->hmd, ovrEye_Left,  _oculus_data->hmd->DefaultEyeFov[0], pixelsPerDisplayPixel ).h;

	_oculus_data->eye_texture_width = _oculus_data->right_eye_texture_width + _oculus_data->left_eye_texture_width;
	_oculus_data->eye_texture_height = Fnd::Utility::Max( _oculus_data->right_eye_texture_height, _oculus_data->left_eye_texture_height );

	Fnd::GameComponentInterfaces::IGraphics::OculusData oculus_data;
	oculus_data.hmd_width = _oculus_data->eye_texture_width;
	oculus_data.hmd_height = _oculus_data->eye_texture_height;
	oculus_data.lefteye_width = _oculus_data->left_eye_texture_width;
	oculus_data.lefteye_height = _oculus_data->left_eye_texture_height;
	oculus_data.righteye_width = _oculus_data->right_eye_texture_width;
	oculus_data.righteye_height = _oculus_data->right_eye_texture_height;
	oculus_data.lefteye_fov_v = atan(max(_oculus_data->hmd->DefaultEyeFov[0].UpTan,_oculus_data->hmd->DefaultEyeFov[0].DownTan)) * 2;
	oculus_data.righteye_fov_v = atan(max(_oculus_data->hmd->DefaultEyeFov[1].UpTan,_oculus_data->hmd->DefaultEyeFov[1].DownTan)) * 2;
	
	_graphics->Resize( _oculus_data->hmd->Resolution.w, _oculus_data->hmd->Resolution.h );

	_graphics->SetOculusData( oculus_data );

	ovrFovPort eyeFov[2] = { _oculus_data->hmd->DefaultEyeFov[0], _oculus_data->hmd->DefaultEyeFov[1] } ;
	
	_oculus_data->eyerender_viewport[0].Pos.x = 0;
	_oculus_data->eyerender_viewport[0].Pos.y = 0;
    _oculus_data->eyerender_viewport[0].Size.w = _oculus_data->left_eye_texture_width;
	_oculus_data->eyerender_viewport[0].Size.h = _oculus_data->left_eye_texture_height;;
    _oculus_data->eyerender_viewport[1].Pos.x  = _oculus_data->left_eye_texture_width;
	_oculus_data->eyerender_viewport[1].Pos.y = 0;
    _oculus_data->eyerender_viewport[1].Size = _oculus_data->eyerender_viewport[0].Size;

	auto d3d_data = _graphics->GetOculusDataD3D11();

	// Query D3D texture data.
    _oculus_data->eyetexture[0].D3D11.Header.API            = ovrRenderAPI_D3D11;
    _oculus_data->eyetexture[0].D3D11.Header.TextureSize.w    = _oculus_data->eye_texture_width;
	_oculus_data->eyetexture[0].D3D11.Header.TextureSize.h    = _oculus_data->eye_texture_height;
    _oculus_data->eyetexture[0].D3D11.Header.RenderViewport = _oculus_data->eyerender_viewport[0];
    _oculus_data->eyetexture[0].D3D11.pTexture              = (ID3D11Texture2D*)d3d_data.eye_tex;
    _oculus_data->eyetexture[0].D3D11.pSRView               = (ID3D11ShaderResourceView*)d3d_data.eye_srv;

	_oculus_data->eyetexture[1] = _oculus_data->eyetexture[0];
	_oculus_data->eyetexture[1].D3D11.Header.RenderViewport = _oculus_data->eyerender_viewport[1];

    // Configure d3d11.
    
	_oculus_data->d3d11cfg.D3D11.Header.API         = ovrRenderAPI_D3D11;
    _oculus_data->d3d11cfg.D3D11.Header.RTSize.w      =  _oculus_data->hmd->Resolution.w;
	_oculus_data->d3d11cfg.D3D11.Header.RTSize.h		= _oculus_data->hmd->Resolution.h;
    _oculus_data->d3d11cfg.D3D11.Header.Multisample = 1;
    _oculus_data->d3d11cfg.D3D11.pDevice            = (ID3D11Device*)d3d_data.device;
	_oculus_data-> d3d11cfg.D3D11.pDeviceContext     = (ID3D11DeviceContext*)d3d_data.device_context;
	_oculus_data-> d3d11cfg.D3D11.pBackBufferRT      = (ID3D11RenderTargetView*)d3d_data.back_buffer_rt;
	_oculus_data->d3d11cfg.D3D11.pSwapChain         = (IDXGISwapChain*)d3d_data.swap_chain;

	

    if (!ovrHmd_ConfigureRendering( _oculus_data->hmd, &_oculus_data->d3d11cfg.Config,
		                           ovrDistortionCap_Chromatic | ovrDistortionCap_TimeWarp | ovrDistortionCap_Vignette |
                                    ovrDistortionCap_Overdrive | ovrDistortionCap_HqDistortion,
								   eyeFov, _oculus_data->eyerender_desc ))
	{
		return false;
	}

	ovrHmd_SetEnabledCaps( _oculus_data->hmd, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

	// Start the sensor which informs of the Rift's pose and motion
    ovrHmd_ConfigureTracking(_oculus_data->hmd,   ovrTrackingCap_Orientation |
                                    ovrTrackingCap_MagYawCorrection |
                                    ovrTrackingCap_Position, 0);

	_graphics;

 	return true;
}
bool first = true;

void OculusRift::BeginRender( unsigned int frame_index )
{
	if ( first )
	{
		_oculus_data->d3d11cfg.D3D11.pSwapChain->SetFullscreenState( true, 0 );
		first = false;
	}
	/*auto d3d_data = _graphics->GetOculusDataD3D11();

	_oculus_data->d3d11cfg.D3D11.Header.API         = ovrRenderAPI_D3D11;
    _oculus_data->d3d11cfg.D3D11.Header.RTSize.w      =  _oculus_data->eye_texture_width;
	_oculus_data->d3d11cfg.D3D11.Header.RTSize.h		= _oculus_data->eye_texture_height;
    _oculus_data->d3d11cfg.D3D11.Header.Multisample = 1;
    _oculus_data->d3d11cfg.D3D11.pDevice            = (ID3D11Device*)d3d_data.device;
	_oculus_data-> d3d11cfg.D3D11.pDeviceContext     = (ID3D11DeviceContext*)d3d_data.device_context;
	_oculus_data-> d3d11cfg.D3D11.pBackBufferRT      = (ID3D11RenderTargetView*)d3d_data.back_buffer_rt;
	_oculus_data->d3d11cfg.D3D11.pSwapChain         = (IDXGISwapChain*)d3d_data.swap_chain;
	*/
	
	ovrHmd_BeginFrame( _oculus_data->hmd, 0); 

	_oculus_data->eyerender_pose[0] = ovrHmd_GetEyePose( _oculus_data->hmd, ovrEye_Left );
	_oculus_data->eyerender_pose[1] = ovrHmd_GetEyePose( _oculus_data->hmd, ovrEye_Right );

	Fnd::GameComponentInterfaces::IGraphics::CameraOffsets camera_offsets;

	auto toFndVector = [] (const ovrVector3f& vec) { return Fnd::Math::Vector3( vec.x, vec.y, -vec.z ); };
	auto toFndQuaternion = [] (const ovrQuatf& quat) { return Fnd::Math::Quaternion( -quat.x, -quat.y, quat.z, quat.w ).GetNormalised(); };

	camera_offsets.lefteye_position_offset = toFndVector( _oculus_data->eyerender_pose[0].Position );
	camera_offsets.lefteye_rotation_offset = toFndQuaternion( _oculus_data->eyerender_pose[0].Orientation );
	camera_offsets.righteye_position_offset = toFndVector( _oculus_data->eyerender_pose[1].Position );
	camera_offsets.righteye_rotation_offset = toFndQuaternion( _oculus_data->eyerender_pose[1].Orientation );



	_graphics->UpdateVRCameraOffsets( camera_offsets );
}

void OculusRift::FinishRender()
{
	_oculus_data->d3d11cfg.D3D11.pDeviceContext->ClearState();
	ovrHmd_EndFrame( _oculus_data->hmd, _oculus_data->eyerender_pose, &_oculus_data->eyetexture[0].Texture);
}

OculusRift::~OculusRift()
{
	if ( _oculus_data->hmd )
	{
		ovrHmd_Destroy(_oculus_data->hmd);
	}

	ovr_Shutdown(); 
}

unsigned int OculusRift::GetTextureWidth()
{
	return _oculus_data->eye_texture_width;
}

unsigned int OculusRift::GetTextureHeight()
{
	return _oculus_data->eye_texture_height;
}

unsigned int OculusRift::GetRightEyeTextureWidth()
{	
	return _oculus_data->right_eye_texture_width;
}

unsigned int OculusRift::GetRightEyeTextureHeight()
{
	return _oculus_data->right_eye_texture_height;
}

unsigned int OculusRift::GetLeftEyeTextureWidth()
{
	return _oculus_data->left_eye_texture_width;
}

unsigned int OculusRift::GetLeftEyeTextureHeight()
{
	return _oculus_data->left_eye_texture_height;
}
