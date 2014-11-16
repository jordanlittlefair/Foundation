#include "../Include/ShaderIncluder.hpp"

#include <fstream>

using namespace Fnd::DirectX11ShaderCompiler;

ShaderIncluder::ShaderIncluder( const std::string& shader ):
	_shader_dir(GetShaderFolder(shader))
{
}

HRESULT ShaderIncluder::Open(	D3D_INCLUDE_TYPE IncludeType,
											LPCSTR pFileName, 
											LPCVOID pParentData, 
											LPCVOID *ppData, 
											UINT *pBytes )
{
    try
	{
        std::string file_name;

        switch(IncludeType)
		{
			case D3D_INCLUDE_LOCAL:
				file_name = _shader_dir + pFileName;
				break;

			default:
				return E_FAIL;
        }

        std::ifstream include_file( file_name.c_str(), std::ios::in | std::ios::binary | std::ios::ate );
 
        if ( include_file.is_open() ) 
		{
            unsigned int file_size = (unsigned int)include_file.tellg();
            char* buf = new char[file_size];
            include_file.seekg (0, std::ios::beg);
            include_file.read (buf, file_size);
            include_file.close();
            *ppData = buf;
            *pBytes = file_size;
        } 
		else 
		{
            return E_FAIL;
        }

        return S_OK;
    }
    catch( std::exception& )
	{
        return E_FAIL;
    }
}
 
HRESULT ShaderIncluder::Close( LPCVOID pData )
{
    char* buf = (char*)pData;
    delete[] buf;
    return S_OK;
}

std::string ShaderIncluder::GetShaderFolder( const std::string& file_name )
{
	std::string to_return = file_name;

	while (
		to_return.back() != '/' && 
		to_return.back() != '\\' &&
		!to_return.empty() )
	{
		to_return.pop_back();
	}

	return to_return;
}