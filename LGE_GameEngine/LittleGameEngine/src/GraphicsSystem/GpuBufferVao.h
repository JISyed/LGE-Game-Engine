#ifndef H_LGE_GPU_BUFFER_VAO
#define H_LGE_GPU_BUFFER_VAO

namespace lge
{
	class Engine;

	// Utility to manage the global VAO of all GpuBuffers
	namespace GpuBufferVao
	{
		void Init();

		void Activate();

		void Unactivate();

		void Destroy(const Engine* const theEngine);

		const bool IsInit();
	}
}
#endif