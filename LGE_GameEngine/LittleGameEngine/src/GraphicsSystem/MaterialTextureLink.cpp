#include "MaterialTextureLink.h"
#include <cassert>

namespace lge
{
	MaterialTextureLink::MaterialTextureLink(const UniformName textureNameInShader) :
		linkedTexture(nullptr),
		nameInShader(textureNameInShader)
	{
	}

	MaterialTextureLink::~MaterialTextureLink()
	{
		linkedTexture = nullptr;
	}





	void MaterialTextureLink::SetTexture(Texture* const newLinkedTexture)
	{
		assert(newLinkedTexture != nullptr);
		this->linkedTexture = newLinkedTexture;
	}


	const UniformName MaterialTextureLink::GetNameInShader() const
	{
		return this->nameInShader;
	}


	const TextureUnit MaterialTextureLink::GetTextureUnit() const
	{
		assert(this->linkedTexture != nullptr);
		return this->linkedTexture->GetTextureUnit();
	}


	// Get the engine ID of this link (for GenericList)
	const unsigned int MaterialTextureLink::GetId() const
	{
		return static_cast<unsigned int>(this->nameInShader);
	}


	void MaterialTextureLink::ActivateTexture()
	{
		// TEMP: Find a way to gurantee that linked texture is not null!
		if (this->linkedTexture != nullptr)
		{
			this->linkedTexture->MakeActive();
		}
	}


}