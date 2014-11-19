#pragma once

#ifndef _COMMONRESOURCES_PIPELINEDESC_HPP_
#define _COMMONRESOURCES_PIPELINEDESC_HPP_

#include <string>

namespace Fnd
{
namespace CommonResources
{

struct PipelineDesc
{
	std::string vertex_shader;
	std::string hull_shader;
	std::string domain_shader;
	std::string geometry_shader;
	std::string pixel_shader;		// aka fragment shader in opengl

	std::string compute_shader;
};

}
}

#endif