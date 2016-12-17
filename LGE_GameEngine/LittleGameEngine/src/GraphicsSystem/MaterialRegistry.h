#ifndef LGE_MATERIAL_MANAGER_H
#define LGE_MATERIAL_MANAGER_H

#include "..\EngineFoundation\ResourseRegistry.h"
#include "..\AbstractDataTypes\GenericList.h"
#include "Material.h"
#include "Shader.h"	// Only needed for "ShaderName"
#include "..\YamlSystem\enumUseYamlType.h"

namespace lge
{
	// Serves as a container for every Material loaded into the game
	class MaterialRegistry final : public ResourceRegistry
	{
	public:

		//
		// Ctor / Dtor
		//

		MaterialRegistry();
		~MaterialRegistry();


		//
		// Contracts
		//

		virtual void Load() override;
		virtual void Unload() override;
		virtual void Update() override;


		//
		// Methods
		//

		// Factory for Material. Automatically added
		Material* const Create(LgeUseYaml_t useYaml, const char* const materialFileName);



		//
		// Static Methods
		//

		// Find any Shader
		static Material& Find(MaterialName name);

		// Factory for Material. Automatically added
		static Material* const Create(MaterialName newName, ShaderName shaderName, PolygonModeType polygonMode);
		// Factory for Material. Automatically added. Also adds a color map texture
		static Material* const Create(MaterialName newName, ShaderName shaderName, PolygonModeType polygonMode, TextureName textureName);




	private:

		//
		// Data
		//

		GenericList<Material> materialList;


		//
		// Static Data
		//

		static MaterialRegistry* singletonInstance;



		//
		// Private Routines
		//

		// Must be dynamically allocated, for it will be deleted by this manager later
		static void Add(Material* newObject);



		//
		// Deleted Methods
		//

		// No copy ctor
		MaterialRegistry(const MaterialRegistry& other) = delete;

		// No copy assignment
		MaterialRegistry& operator=(const MaterialRegistry& other) = delete;

		// No move ctor
		MaterialRegistry(MaterialRegistry&& other) = delete;

		// No move assignment
		MaterialRegistry& operator=(MaterialRegistry&& other) = delete;
	};

	
}
#endif