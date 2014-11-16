#include "../Include/IdGenerator.hpp"
#include "../Include/BitReverse.hpp"

using namespace Fnd::Utility;

IdGenerator::IdGenerator():
	_id(0)
{
}

unsigned int IdGenerator::GetId()
{
	//return GetBitReverse(_id++);
	return _id++;
}