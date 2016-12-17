#include "GpuBufferVao.h"
#include "GL\gl3w.h"
#include <cassert>

namespace lge
{
	namespace GpuBufferVao
	{
		static GLuint theVAO = 0;			// VAO for every GPU Buffer
		static bool isInitialized = false;	// Flag for initialization to prevent reinit

		void Init()
		{
			if (GpuBufferVao::isInitialized == false)
			{
				glGenVertexArrays(1, &GpuBufferVao::theVAO);
				assert(GpuBufferVao::theVAO != 0);
				glBindVertexArray(GpuBufferVao::theVAO);
				GpuBufferVao::isInitialized = true;
			}
		}

		void Activate()
		{
			assert(GpuBufferVao::isInitialized);
			glBindVertexArray(GpuBufferVao::theVAO);
		}

		void Unactivate()
		{
			assert(GpuBufferVao::isInitialized);
			glBindVertexArray(0);
		}

		void Destroy(const Engine* const theEngine)
		{
			if (theEngine != nullptr)
			{
				if (GpuBufferVao::isInitialized)
				{
					glDeleteVertexArrays(1, &GpuBufferVao::theVAO);
					GpuBufferVao::isInitialized = false;
				}
			}
		}

		const bool IsInit()
		{
			return GpuBufferVao::isInitialized;
		}
	}
}