#include "../Include/DirectX11ShaderCompiler.hpp"

#include "../Include/ShaderIncluder.hpp"

#include <iostream>
#include <fstream>
#include <d3dcompiler.h>

using namespace Fnd::DirectX11ShaderCompiler;

std::wstring DirectX11ShaderCompiler::GetWString( const char char_array[] )
{
	size_t array_length = 0;

	// Get the length of the char_array
	mbstowcs_s( &array_length, nullptr, 0, char_array, 0 );

	// Array to store the wchar_t characters
	wchar_t* wchar_array = new wchar_t[array_length+1];

	// Convert to wchar_t
	mbstowcs_s( &array_length, wchar_array, array_length + 1, char_array, array_length );

	std::wstring to_return( wchar_array );

	delete[] wchar_array;

	return to_return;
}

bool DirectX11ShaderCompiler::CompileShaders( const Fnd::GraphicsResources::ShaderCompilerConfig::ShaderData& shader_data )
{
	bool ret = true;

	unsigned int shader_count = 0;
	unsigned int success_count = 0;

	const std::string vs_target = "vs_" + shader_data.shader_model;
	const std::string hs_target = "hs_" + shader_data.shader_model;
	const std::string ds_target = "ds_" + shader_data.shader_model;
	const std::string gs_target = "gs_" + shader_data.shader_model;
	const std::string ps_target = "ps_" + shader_data.shader_model;
	const std::string cs_target = "cs_" + shader_data.shader_model;

	unsigned int debug_flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_WARNINGS_ARE_ERRORS;
	unsigned int release_flags = D3DCOMPILE_AVOID_FLOW_CONTROL | D3DCOMPILE_OPTIMIZATION_LEVEL3 | D3DCOMPILE_WARNINGS_ARE_ERRORS;

	for ( auto iter = shader_data.pipelines.begin(); iter != shader_data.pipelines.end(); ++iter )
	{
		/*
			VS
		*/
		if ( !iter->second.vertex_shader.empty() )
		{
			++shader_count;

			if ( CompileShader(	shader_data.source_directory + iter->second.vertex_shader, 
								shader_data.output_directory_debug + iter->second.vertex_shader + shader_data.compiled_extension, 
								vs_target, 
								debug_flags )
				&&
				CompileShader(	shader_data.source_directory + iter->second.vertex_shader,
								shader_data.output_directory + iter->second.vertex_shader + shader_data.compiled_extension,
								vs_target,
								release_flags ) )
			{
				++success_count;
			}
			else
			{
				ret = false;
			}
		}
		/*
			HS
		*/
		if ( !iter->second.hull_shader.empty() )
		{
			++shader_count;

			if ( CompileShader(	shader_data.source_directory + iter->second.hull_shader, 
								shader_data.output_directory_debug + iter->second.hull_shader + shader_data.compiled_extension, 
								hs_target, 
								debug_flags )
				&&
				CompileShader(	shader_data.source_directory + iter->second.hull_shader,
								shader_data.output_directory + iter->second.hull_shader + shader_data.compiled_extension,
								hs_target,
								release_flags ) )
			{
				++success_count;
			}
			else
			{
				ret = false;
			}
		}

		/*
			DS
		*/
		if ( !iter->second.domain_shader.empty() )
		{
			++shader_count;

			if ( CompileShader(	shader_data.source_directory + iter->second.domain_shader, 
								shader_data.output_directory_debug + iter->second.domain_shader + shader_data.compiled_extension, 
								ds_target, 
								debug_flags )
				&&
				CompileShader(	shader_data.source_directory + iter->second.domain_shader,
								shader_data.output_directory + iter->second.domain_shader + shader_data.compiled_extension,
								ds_target,
								release_flags ) )
			{
				++success_count;
			}
			else
			{
				ret = false;
			}
		}

		/*
			GS
		*/
		if ( !iter->second.geometry_shader.empty() )
		{
			++shader_count;

			if ( CompileShader(	shader_data.source_directory + iter->second.geometry_shader, 
								shader_data.output_directory_debug + iter->second.geometry_shader + shader_data.compiled_extension, 
								gs_target, 
								debug_flags )
				&&
				CompileShader(	shader_data.source_directory + iter->second.geometry_shader,
								shader_data.output_directory + iter->second.geometry_shader + shader_data.compiled_extension,
								gs_target,
								release_flags ) )
			{
				++success_count;
			}
			else
			{
				ret = false;
			}
		}

		/*
			PS
		*/
		if ( !iter->second.pixel_shader.empty() )
		{
			++shader_count;

			if ( CompileShader(	shader_data.source_directory + iter->second.pixel_shader, 
								shader_data.output_directory_debug + iter->second.pixel_shader + shader_data.compiled_extension, 
								ps_target, 
								debug_flags )
				&&
				CompileShader(	shader_data.source_directory + iter->second.pixel_shader,
								shader_data.output_directory + iter->second.pixel_shader + shader_data.compiled_extension,
								ps_target,
								release_flags ) )
			{
				++success_count;
			}
			else
			{
				ret = false;
			}
		}

		/*
			CS
		*/
		if ( !iter->second.compute_shader.empty() )
		{
			++shader_count;

			if ( CompileShader(	shader_data.source_directory + iter->second.compute_shader, 
								shader_data.output_directory_debug + iter->second.compute_shader + shader_data.compiled_extension, 
								cs_target, 
								debug_flags )
				&&
				CompileShader(	shader_data.source_directory + iter->second.compute_shader,
								shader_data.output_directory + iter->second.compute_shader + shader_data.compiled_extension,
								cs_target,
								release_flags ) )
			{
				++success_count;
			}
			else
			{
				ret = false;
			}
		}

	}

	std::cout << "----\n\nSuccessfully compiled " << success_count << "/" << shader_count << " shaders.\n----\n" << std::endl;

	return ret;
}

bool DirectX11ShaderCompiler::CompileShader( const std::string& input_filename, const std::string& output_filename, const std::string& target, unsigned int flags )
{
	std::cout << "----\nCompiling \"" << input_filename << "\"....\n" << std::endl;

	ID3DBlob* shader_bytecode = nullptr;
	ID3DBlob* errors = nullptr;

	ShaderIncluder shader_includer(input_filename);

	if ( SUCCEEDED( D3DCompileFromFile(	GetWString(input_filename.c_str()).c_str(),
										nullptr,
										&shader_includer,
										"main",
										target.c_str(),
										flags,
										0,
										&shader_bytecode,
										&errors ) ) )
	{
		std::cout << "Successfully compiled \" " << input_filename << "\"." << std::endl;

		std::ofstream out_file( output_filename, std::ios::out | std::ios::trunc | std::ios::binary );

		bool succeeded = true;
		if ( out_file.is_open() )
		{
			out_file.write( (const char*)shader_bytecode->GetBufferPointer(), shader_bytecode->GetBufferSize() );

			out_file.close();
		}
		else 
		{
			succeeded = false;

			std::cout << "Failed to write output to file \" " << output_filename << "\"." << std::endl;
		}

		shader_bytecode->Release();

		return succeeded;
	}
	else
	{
		std::cout << "Failed to compile \" " << input_filename << "\"." << std::endl;

		if ( errors )
		{
			std::cout << (const char*)errors->GetBufferPointer() << std::endl;
			errors->Release();
		}

		return false;
	}
}