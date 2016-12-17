#ifndef LGE_MATERIAL_TEXTURE_LINK_H
#define LGE_MATERIAL_TEXTURE_LINK_H

#include "Texture.h"
#include "UniformNameHelper.h"
#include "enumTextureUnit.h"

namespace lge
{
	// Allows the material to know what textures it supports
	class MaterialTextureLink
	{
	public:

		//
		// Ctor / Dtor
		//

		MaterialTextureLink(const UniformName textureNameInShader);
		~MaterialTextureLink();


		//
		// Setters
		//

		// Set the texture to be linked to this material
		void SetTexture(Texture* const newLinkedTexture);


		//
		// Getters
		//

		// Get the texture's name from the shader of this material
		const UniformName GetNameInShader() const;

		// Get the texture unit of the linked texture
		const TextureUnit GetTextureUnit() const;

		// Get the engine ID of this link (for GenericList)
		const unsigned int GetId() const;



		//
		// Methods
		//

		// Make the currently linked texture the active texture in OpenGL
		void ActivateTexture();




	private:

		//
		// Data
		//

		Texture* linkedTexture;
		const UniformName nameInShader;



		//
		// Deleted Methods
		//

		// No default ctor
		MaterialTextureLink() = delete;

		// No copy ctor
		MaterialTextureLink(const MaterialTextureLink& other) = delete;

		// No copy assignment
		MaterialTextureLink& operator=(const MaterialTextureLink& other) = delete;

		// No move ctor
		MaterialTextureLink(MaterialTextureLink&& other) = delete;

		// No move assignment
		MaterialTextureLink& operator=(MaterialTextureLink&& other) = delete;
	};

	
}

#endif