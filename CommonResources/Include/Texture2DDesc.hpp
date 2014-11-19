#pragma once

#ifndef _COMMONRESOURCES_TEXTURE2DDESC_HPP_
#define _COMMONRESOURCES_TEXTURE2DDESC_HPP_

#include <string>

namespace Fnd
{
namespace CommonResources
{

struct Texture2DDesc
{
	std::string filename;

	bool generate_mips;

	enum Format
	{
		FormatUnknown = 0,
		FormatR,
		FormatRG,
		FormatRGB,
		FormatRGBA
	};

	Format format;
};

}
}

#endif