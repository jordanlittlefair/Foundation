#pragma once

#ifndef _UTILITY_IDGENERATOR_HPP_
#define _UTILITY_IDGENERATOR_HPP_

namespace Fnd
{
namespace Utility
{

class IdGenerator
{
	public:
		
		IdGenerator();

		unsigned int GetId();

	private:

		unsigned int _id;
};

}
}

#endif