#pragma once

#ifndef _IDGENERATOR_HPP_
#define _IDGENERATOR_HPP_

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