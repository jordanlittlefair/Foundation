#include "../Include/OpenGLShaderCompiler.hpp"

#include "../../Utility/Include/String.hpp"
#include "../../Utility/Include/FileSystem.hpp"

#ifdef _WIN32
#include <Windows.h>
#include <wingdi.h>
#else
#endif

#include <iostream>

using namespace Fnd::OpenGLShaderCompiler;

#ifdef _WIN32
LRESULT WINAPI wndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc(wnd,msg,wParam,lParam);
}
#endif

OpenGLShaderCompiler::OpenGLShaderCompiler():
	_initialised_successfully(false)
{
#ifdef _WIN32
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
	window_class.lpszClassName = "OpenGLShaderCompilerWindow";
	window_class.hIconSm = nullptr;

	if ( !RegisterClassEx( &window_class ) )
	{
		std::cout << "Failed to register window class." << std::endl;
		return;
	}

	// Create the window.
	auto _window = CreateWindowEx(	0,
								"OpenGLShaderCompilerWindow",
								"window",
								WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
								CW_USEDEFAULT,
								CW_USEDEFAULT,
								0,
								0,
								nullptr,
								nullptr,
								nullptr,
								nullptr );

	HDC hdc = GetDC(_window);
	PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    // set the pixel format for the DC
    memset( &pfd, sizeof( pfd ), 0 );
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                  PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat( hdc, &pfd );
    SetPixelFormat( hdc, iFormat, &pfd );

	auto _hglrc = wglCreateContext(hdc);

	wglMakeCurrent(hdc,(HGLRC)_hglrc);

	GLenum err = glewInit();
	if ( err == GLEW_OK )
	{
		_initialised_successfully = true;
	}
	else
	{
		std::cout << "Failed to initialise glew, error code: " << err << std::endl;
	}
#else
#endif
}

GLuint OpenGLShaderCompiler::CompileShader( const std::string& input_filename, const std::string& output_filename, const std::string& debug_output_filename, GLuint type, std::string& error )
{
	std::cout << "----\nCompiling \"" << input_filename << "\"....\n" << std::endl;
	GLint compile_status = 0;

	GLuint shader = glCreateShader( type );

	std::string shader_string;
	Fnd::Utility::LoadFileIntoString( input_filename, shader_string );

	const char* shader_source_code = shader_string.c_str();

	glShaderSource( shader, 1, &shader_source_code, 0 );
	
	glCompileShader( shader );

	glGetShaderiv( shader, GL_COMPILE_STATUS, &compile_status );

	if ( compile_status == GL_TRUE )
	{
		std::cout << "Successfully compiled \" " << input_filename << "\"." << std::endl;

		Fnd::Utility::FileSystem::CopyFile_( input_filename, output_filename );
		Fnd::Utility::FileSystem::CopyFile_( input_filename, debug_output_filename );

		return shader;
	}
	else
	{
		const int length = 1024;
		GLchar log[length] = "";
		glGetShaderInfoLog( shader, length, nullptr, log );
		error = log;

		std::cout << "Failed to compile \" " << input_filename << "\"." << std::endl;
		std::cout << log << std::endl;

		return 0;
	}
}

bool OpenGLShaderCompiler::CompileShaders( const Fnd::GraphicsResources::ShaderCompilerConfig::ShaderData& shader_data )
{
	bool ret = _initialised_successfully;

	unsigned int shader_count = 0;
	unsigned int success_count = 0;

	if ( !ret )
	{
        std::cout << "Failed to initialise OpenGL graphics." << std::endl;
		return false;
	}
    
	for ( auto iter = shader_data.pipelines.begin(); iter != shader_data.pipelines.end(); ++iter )
	{
		/*
			VS
		*/
		if ( !iter->second.vertex_shader.empty() )
		{
			++shader_count;

			std::string error;
			if ( CompileShader(	shader_data.source_directory + iter->second.vertex_shader,
								shader_data.output_directory + iter->second.vertex_shader + shader_data.compiled_extension,
								shader_data.output_directory_debug + iter->second.vertex_shader + shader_data.compiled_extension,
								GL_VERTEX_SHADER,
								error ) )
			{
				++success_count;
			}
			else
			{
				std::cout << error << std::endl;
				ret = false;
			}
		}

		/*
			HS
		*/
		if ( !iter->second.hull_shader.empty() )
		{
			ret = false;
		}

		/*
			DS
		*/
		if ( !iter->second.domain_shader.empty() )
		{
			ret = false;
		}

		/*
			GS
		*/
		if ( !iter->second.geometry_shader.empty() )
		{
			++shader_count;

			std::string error;
			if ( CompileShader(	shader_data.source_directory + iter->second.geometry_shader,
								shader_data.output_directory + iter->second.geometry_shader + shader_data.compiled_extension,
								shader_data.output_directory_debug + iter->second.geometry_shader + shader_data.compiled_extension,
								GL_GEOMETRY_SHADER,
								error ) )
			{
				++success_count;
			}
			else
			{
				std::cout << error << std::endl;
				ret = false;
			}
		}

		/*
			PS
		*/
		if ( !iter->second.pixel_shader.empty() )
		{
			++shader_count;

			std::string error;
			if ( CompileShader(	shader_data.source_directory + iter->second.pixel_shader,
								shader_data.output_directory + iter->second.pixel_shader + shader_data.compiled_extension,
								shader_data.output_directory_debug + iter->second.pixel_shader + shader_data.compiled_extension,
								GL_FRAGMENT_SHADER,
								error ) )
			{
				++success_count;
			}
			else
			{
				std::cout << error << std::endl;
				ret = false;
			}
		}
	}

	std::cout << "----\n\nSuccessfully compiled " << success_count << "/" << shader_count << " shaders.\n----\n" << std::endl;

	return ret;
}