#ifndef LGE_SHADER_MANAGER_H
#define LGE_SHADER_MANAGER_H

#include "..\EngineFoundation\ResourseRegistry.h"
#include "..\AbstractDataTypes\GenericList.h"
#include "Shader.h"

namespace lge
{
	// Serves as a container for holding all the loaded Shaders in the game
	class ShaderRegistry final : public ResourceRegistry
	{
	public:

		//
		// Ctor / Dtor
		//

		ShaderRegistry();
		virtual ~ShaderRegistry();



		//
		// Contracts
		//

		virtual void Load() override;
		virtual void Unload() override;
		virtual void Update() override;



		//
		// Static Methods
		//

		// Find any Shader
		static Shader& Find(ShaderName name);

		// Factory for Shaders. Automatically added
		static Shader* const Create(ShaderName name, const char* const vertFilePath, const char* const fragFilePath);




	private:

		//
		// Data
		//

		GenericList<Shader> shaderList;



		//
		// Static Data
		//

		static ShaderRegistry* singletonInstance;



		//
		// Private Routines
		//

		// Must be dynamically allocated, for it will be deleted by this manager later
		static void Add(Shader* newObject);



		//
		// Deleted Methods
		//

		// No copy ctor
		ShaderRegistry(const ShaderRegistry& other) = delete;

		// No copy assignment
		ShaderRegistry& operator=(const ShaderRegistry& other) = delete;

		// No move ctor
		ShaderRegistry(ShaderRegistry&& other) = delete;

		// No move assignment
		ShaderRegistry& operator=(ShaderRegistry&& other) = delete;
	};

	
}
#endif
