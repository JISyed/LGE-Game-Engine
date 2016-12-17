#ifndef LGE_TEXTURE_MANAGER_H
#define LGE_TEXTURE_MANAGER_H

#include "..\EngineFoundation\ResourseRegistry.h"
#include "..\AbstractDataTypes\GenericList.h"
#include "Texture.h"

namespace lge
{
	// Serves as a container for holding every Texture loaded into the game
	class TextureRegistry final : public ResourceRegistry
	{
	public:

		//
		// Ctor / Dtor
		//

		TextureRegistry();
		~TextureRegistry();


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
		static Texture& Find(TextureName name);

		// Factory for Textures. Automatically added
		static Texture* const Create(TextureName name, TextureMapType mapType, const char * const filePath, TextureFilterType filtering, TextureWrapType wrapping);

		// Factory for Textures. Automatically added
		static Texture* const Create(TextureName name, TextureMapType mapType, const ImageBuffer& image, TextureFilterType filtering, TextureWrapType wrapping);

		// Factory for Textures. Automatically added
		static Texture* const Create(UseUnpacker_t use, TextureName name, TextureMapType mapType, const char * const nameInPackage, TextureFilterType filtering, TextureWrapType wrapping);


	private:

		//
		// Data
		//

		GenericList<Texture> textureList;


		//
		// Static Data
		//

		static TextureRegistry* singletonInstance;



		//
		// Private Routines
		//

		// Must be dynamically allocated, for it will be deleted by this manager later
		static void Add(Texture* newObject);



		//
		// Deleted Methods
		//

		// No copy ctor
		TextureRegistry(const TextureRegistry& other) = delete;

		// No copy assignment
		TextureRegistry& operator=(const TextureRegistry& other) = delete;

		// No move ctor
		TextureRegistry(TextureRegistry&& other) = delete;

		// No move assignment
		TextureRegistry& operator=(TextureRegistry&& other) = delete;

	};

	
}
#endif