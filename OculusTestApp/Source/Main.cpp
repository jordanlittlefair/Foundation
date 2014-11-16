#include <Windows.h>
#include <d3d11.h>

#include <cstdlib>

#include <OVR.h>

#define OVR_D3D_VERSION 11
#include <../src/OVR_CAPI_D3D.h>

HWND g_hWnd = nullptr;
bool g_windowIsOpen = false;
ovrHmd g_hmd = nullptr;

unsigned int left_tex_width = 0;
unsigned int left_tex_height = 0;
unsigned int right_tex_width = 0;
unsigned int right_tex_height = 0;
unsigned int eye_tex_width = 0;
unsigned int eye_tex_height = 0;

IDXGIFactory* g_dxgi_factory = nullptr;
IDXGIAdapter* g_dxgi_adapter = nullptr;

ID3D11Device* g_device = nullptr;
ID3D11DeviceContext* g_context = nullptr;
IDXGISwapChain* g_swapchain = nullptr;
ID3D11Texture2D* g_backbuffer = nullptr;
ID3D11RenderTargetView* g_backbuffer_rt = nullptr;

ID3D11Texture2D* g_eye_texture = nullptr;
ID3D11ShaderResourceView* g_eye_texture_sr = nullptr;
ID3D11RenderTargetView* g_eye_texture_rt = nullptr;

ovrRecti           g_eyerender_viewport[2];
ovrD3D11Texture    g_eye_tex[2];
ovrEyeRenderDesc g_eyerender_desc[2];

template <typename T>
void Release( T* t )
{
	if ( t )
	{
		t->Release();
		t = nullptr;
	}
}

static LRESULT WINAPI wndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam );
bool InitialiseWindow( unsigned int width, unsigned int height );
bool InitialiseGraphics();
bool RecreateSwapChain();

bool InitialiseWindow( unsigned int width, unsigned int height )
{
	// Register window class
	WNDCLASSEX window_class;

	window_class.cbSize = sizeof(WNDCLASSEX);
	window_class.style = 0;
	window_class.lpfnWndProc = wndProc;
	window_class.cbClsExtra = 0;
	window_class.cbWndExtra = 0;
	window_class.hInstance = nullptr;
	window_class.hIcon = nullptr;
	window_class.hCursor = LoadCursor( 0, IDC_ARROW );
	window_class.hbrBackground = nullptr;
	window_class.lpszMenuName = nullptr;
	window_class.lpszClassName = "Window";
	window_class.hIconSm = nullptr;

	if ( !RegisterClassEx( &window_class ) )
	{
		//LogError( "Initialisation failed; Cannot register window_class." );
		return false;
	}

	auto style = WS_OVERLAPPED | WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

	// Adjust the size of the window (by adding the size of the borders).
	RECT client_rectangle = { 0, 0, (int)width, (int)height };
	AdjustWindowRect( &client_rectangle, style, false );

	const unsigned int adjusted_width = client_rectangle.right - client_rectangle.left;
	const unsigned int adjusted_height = client_rectangle.bottom - client_rectangle.top;

	// Create the window.
	g_hWnd = CreateWindowEx(	0,
								"Window",
								"OculusTestApp",
								style,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								adjusted_width,
								adjusted_height,
								nullptr,
								nullptr,
								nullptr,
								nullptr );

	if ( !g_hWnd )
	{
		//LogError( "Initialisation failed; Cannot create window." );
		return false;
	}

	//SetWindowLongPtr( g_hWnd, GWL_USERDATA, (LONG_PTR)this );

	return true;
}

bool InitialiseGraphics()
{
	CreateDXGIFactory( __uuidof(IDXGIFactory), (void**)&g_dxgi_factory );

	g_dxgi_factory->EnumAdapters( 0, &g_dxgi_adapter );

	D3D11CreateDevice( g_dxgi_adapter, g_dxgi_adapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE,
		nullptr,0, nullptr, 0, D3D11_SDK_VERSION, 
		&g_device, nullptr, &g_context );

	if ( !RecreateSwapChain() )
		return false;

	if ( g_swapchain )
	g_swapchain->SetFullscreenState( 1, nullptr );

	return true;
}

bool RecreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC scDesc;
    memset(&scDesc, 0, sizeof(scDesc));
    scDesc.BufferCount          = 2;
    scDesc.BufferDesc.Width     = g_hmd->Resolution.w;
    scDesc.BufferDesc.Height    = g_hmd->Resolution.h;
    scDesc.BufferDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferDesc.RefreshRate.Numerator   = 0;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.BufferUsage          = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.OutputWindow         = g_hWnd;
    scDesc.SampleDesc.Count     = 1;
    scDesc.SampleDesc.Quality   = 0;
    scDesc.Windowed             = true;
    scDesc.Flags                = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scDesc.SwapEffect			= DXGI_SWAP_EFFECT_SEQUENTIAL;

	if (g_swapchain)
	{
		g_swapchain->SetFullscreenState(FALSE, NULL);
		g_swapchain->Release();
		g_swapchain = nullptr;
	}

    if (FAILED(g_dxgi_factory->CreateSwapChain(g_device, &scDesc, &g_swapchain)))
        return false;   

    g_backbuffer = nullptr;
    g_backbuffer_rt = nullptr;
    HRESULT hr = g_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&g_backbuffer);
    if (FAILED(hr))
        return false;

    hr = g_device->CreateRenderTargetView(g_backbuffer, nullptr, &g_backbuffer_rt);
    if (FAILED(hr))
        return false;

    return true;
}



static LRESULT WINAPI wndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
	{
		case WM_CLOSE:
			{
				g_windowIsOpen = false;
				break;
			}
		default:
			break;
	}

	return DefWindowProc( wnd, msg, wParam, lParam );
}

int _stdcall
WinMain (	_In_ struct HINSTANCE__* hIinstance,
			_In_opt_ struct HINSTANCE__* hPrevInstance,
			_In_ char* lpszCmdLine,
			_In_ int nCmdShow )
{
	if ( !InitialiseWindow( 1280, 720 ) )
	{
		return 1;
	}

	ovr_Initialize();

	g_hmd = ovrHmd_Create(0);
	if ( !g_hmd )
	{
		return 1;
	}

	if ( !InitialiseGraphics() )
	{
		return 2;
	}

	ovrHmd_AttachToWindow( g_hmd, g_hWnd, nullptr, nullptr );

	left_tex_width = ovrHmd_GetFovTextureSize( g_hmd, ovrEye_Left,  g_hmd->DefaultEyeFov[0], 1.0f).w;
	left_tex_height = ovrHmd_GetFovTextureSize( g_hmd, ovrEye_Left,  g_hmd->DefaultEyeFov[0], 1.0f).h;
	right_tex_width = ovrHmd_GetFovTextureSize( g_hmd, ovrEye_Right,  g_hmd->DefaultEyeFov[0], 1.0f).w;
	right_tex_height = ovrHmd_GetFovTextureSize( g_hmd, ovrEye_Right,  g_hmd->DefaultEyeFov[0], 1.0f).h;

	eye_tex_width = left_tex_width + right_tex_width;
	eye_tex_height = max( left_tex_height, right_tex_height );

	D3D11_TEXTURE2D_DESC dsDesc;
    dsDesc.Width     = eye_tex_width;
    dsDesc.Height    = eye_tex_height;
    dsDesc.MipLevels = 1;
    dsDesc.ArraySize = 1;
    dsDesc.Format    = DXGI_FORMAT_R8G8B8A8_UNORM;
    dsDesc.SampleDesc.Count = 1;
    dsDesc.SampleDesc.Quality = 0;
    dsDesc.Usage     = D3D11_USAGE_DEFAULT;
    dsDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
    dsDesc.CPUAccessFlags = 0;
    dsDesc.MiscFlags      = 0;

	g_device->CreateTexture2D( &dsDesc, NULL, &g_eye_texture );

	g_device->CreateShaderResourceView( g_eye_texture, NULL, &g_eye_texture_sr );

	g_device->CreateRenderTargetView( g_eye_texture, NULL, &g_eye_texture_rt );

	ovrFovPort eyeFov[2] = { g_hmd->DefaultEyeFov[0], g_hmd->DefaultEyeFov[1] } ;

	g_eyerender_viewport[0].Pos.x = 0;
	g_eyerender_viewport[0].Pos.y = 0;
    g_eyerender_viewport[0].Size.w = left_tex_width;
	g_eyerender_viewport[0].Size.h = left_tex_height;
    g_eyerender_viewport[1].Pos.x = left_tex_width;
	g_eyerender_viewport[1].Pos.y = 0;
    g_eyerender_viewport[1].Size = g_eyerender_viewport[0].Size;

	g_eye_tex[0].D3D11.Header.API            = ovrRenderAPI_D3D11;
    g_eye_tex[0].D3D11.Header.TextureSize.w    = eye_tex_width;
	g_eye_tex[0].D3D11.Header.TextureSize.h    = eye_tex_height;
    g_eye_tex[0].D3D11.Header.RenderViewport = g_eyerender_viewport[0];
    g_eye_tex[0].D3D11.pTexture              = g_eye_texture;
    g_eye_tex[0].D3D11.pSRView               = g_eye_texture_sr;

	g_eye_tex[1] = g_eye_tex[0];
	g_eye_tex[1].D3D11.Header.RenderViewport = g_eyerender_viewport[1];

	ovrD3D11Config d3d11cfg;
    d3d11cfg.D3D11.Header.API         = ovrRenderAPI_D3D11;
    d3d11cfg.D3D11.Header.RTSize.w    = g_hmd->Resolution.w;
    d3d11cfg.D3D11.Header.RTSize.h    = g_hmd->Resolution.h;
    d3d11cfg.D3D11.Header.Multisample = 1;
    d3d11cfg.D3D11.pDevice            = g_device;
    d3d11cfg.D3D11.pDeviceContext     = g_context;
    d3d11cfg.D3D11.pBackBufferRT      = g_backbuffer_rt;
    d3d11cfg.D3D11.pSwapChain         = g_swapchain;

	if (!ovrHmd_ConfigureRendering( g_hmd, &d3d11cfg.Config,
		                           ovrDistortionCap_Chromatic | ovrDistortionCap_Vignette |
                                   ovrDistortionCap_TimeWarp | ovrDistortionCap_Overdrive,
								   eyeFov, g_eyerender_desc))
	{
		return(3);
	}

	ovrHmd_SetEnabledCaps( g_hmd, ovrHmdCap_LowPersistence | ovrHmdCap_DynamicPrediction);

	// Start the sensor which informs of the Rift's pose and motion
    ovrHmd_ConfigureTracking( g_hmd,   ovrTrackingCap_Orientation |
                                    ovrTrackingCap_MagYawCorrection |
                                    ovrTrackingCap_Position, 0);



	ShowWindow( g_hWnd, SW_SHOW );
	g_windowIsOpen = true;

	while ( g_windowIsOpen )
	{
		// Process messages
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}



		
		ovrHmd_BeginFrame( g_hmd, 0); 

		ovrPosef eyeRenderPose[2] =  { ovrHmd_GetEyePose( g_hmd, ovrEye_Right ), ovrHmd_GetEyePose( g_hmd, ovrEye_Right ) };

		float r = 1;//rand()/((float)RAND_MAX);
		float g = 1;//rand()/((float)RAND_MAX);
		float b = 1;//rand()/((float)RAND_MAX);

		float col[4] = { r, g, b, 1 };
		g_context->ClearRenderTargetView( g_eye_texture_rt, col );

		ovrHmd_EndFrame( g_hmd, eyeRenderPose, &g_eye_tex[0].Texture);




	}

	

	
	Release( g_swapchain );
	Release( g_backbuffer );
	Release( g_backbuffer_rt );

	Release( g_eye_texture );
	Release( g_eye_texture_sr );
	Release( g_eye_texture_rt );
	
	Release( g_context );
	Release( g_device );
	Release( g_dxgi_adapter );
Release( g_dxgi_factory );
	if ( g_hmd )
		ovrHmd_Destroy(g_hmd);

	ovr_Shutdown();

	return 0;
}