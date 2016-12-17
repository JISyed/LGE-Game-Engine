#ifndef LGE_IRENDERABLE_H
#define LGE_IRENDERABLE_H

namespace lge
{
	// A contract for any class that wants to render anything
	class IRenderable
	{
	public:
		
		// Performs consistent procedure for drawing something
		void Draw()
		{
			this->SetState();
			this->SetGpuData();
			this->Render();
			this->RestoreState();
		}


	protected:

		// Setting states in OpenGL
		virtual void SetState() = 0;

		// Sending data to the GPU if needed
		virtual void SetGpuData() = 0;

		// Actual draw call
		virtual void Render() = 0;

		// Restoring states back to prevent unexpected rendering behavior
		virtual void RestoreState() = 0;

	};

}

#endif