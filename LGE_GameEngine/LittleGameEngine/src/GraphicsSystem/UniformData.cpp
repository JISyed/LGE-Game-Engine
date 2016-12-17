#include "UniformData.h"
#include <cassert>

namespace lge
{
	// Ctor
	UniformData::UniformData(ShaderUniformHandle* const newHandle) :
		handle(newHandle)
	{
		assert(newHandle != nullptr);
	}

	// VIRTUAL
	// Dtor
	UniformData::~UniformData()
	{
	}
}