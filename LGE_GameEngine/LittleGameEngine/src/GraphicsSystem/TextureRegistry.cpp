#include "TextureRegistry.h"
#include <cassert>
#include <random>	// C++ 11 random

namespace lge
{
	//
	// Static Data
	//
	TextureRegistry* TextureRegistry::singletonInstance = nullptr;



	//
	// Methods
	//

	TextureRegistry::TextureRegistry() :
		textureList()
	{
		assert(TextureRegistry::singletonInstance == nullptr);
		TextureRegistry::singletonInstance = this;
	}

	// VIRTUAL
	TextureRegistry::~TextureRegistry()
	{
		// List must be emptied before destroying manager!
		assert(this->textureList.GetNumberOfElements() == 0);

		// Manager must exist in singleton link!
		assert(TextureRegistry::singletonInstance != nullptr);
		TextureRegistry::singletonInstance = this;
	}







	// VIRTUAL
	void TextureRegistry::Load()
	{
		TextureRegistry::Create(TextureName::Duckweed,
								TextureMapType::Color,
								"res/textures/duckweed.tga",
								TextureFilterType::Bilinear,
								TextureWrapType::EdgeClamp);

		TextureRegistry::Create(TextureName::MarioGround,
								TextureMapType::Color,
								"res/textures/marioGround.tga",
								TextureFilterType::PointDistanceBlend,
								TextureWrapType::EdgeClamp);

		TextureRegistry::Create(TextureName::Rocks,
								TextureMapType::Color,
								"res/textures/rocks.tga",
								TextureFilterType::Bilinear,
								TextureWrapType::EdgeClamp);

		TextureRegistry::Create(TextureName::ExampleNormalMap,
								TextureMapType::Normal,
								"res/textures/weirdNormalMap.tga",
								TextureFilterType::Bilinear,
								TextureWrapType::EdgeClamp);


		TextureRegistry::Create(TextureName::WarbearPolar,
								TextureMapType::Color,
								"res/textures/polarbear.tga",
								TextureFilterType::Bilinear,
								TextureWrapType::EdgeClamp);

		TextureRegistry::Create(TextureName::Default,
								TextureMapType::Color,
								"BAD PATH ON PURPOSE",
								TextureFilterType::PointDistanceBlend,
								TextureWrapType::Repeat);

		TextureRegistry::Create(TextureName::TeddyBear,
								TextureMapType::Color,
								"res/textures/teddyTex.tga",
								TextureFilterType::Bilinear,
								TextureWrapType::EdgeClamp);

		TextureRegistry::Create(UseUnpacker, 
								TextureName::SpaceFrigate,
								TextureMapType::Color,
								"space_frigate",
								TextureFilterType::Bilinear,
								TextureWrapType::EdgeClamp);

		TextureRegistry::Create(UseUnpacker, 
								TextureName::Astroboy,
								TextureMapType::Color,
								"astroboy",
								TextureFilterType::Bilinear,
								TextureWrapType::EdgeClamp);

		TextureRegistry::Create(UseUnpacker, 
								TextureName::BuggyDiffuse,
								TextureMapType::Color,
								"buggy",
								TextureFilterType::Bilinear,
								TextureWrapType::EdgeClamp);

		TextureRegistry::Create(UseUnpacker, 
								TextureName::WarbearBrown,
								TextureMapType::Color,
								"warbear",
								TextureFilterType::Bilinear,
								TextureWrapType::EdgeClamp);
	}

	// VIRTUAL
	void TextureRegistry::Unload()
	{
		while (this->textureList.GetNumberOfElements() != 0)
		{
			Texture* oldObject = this->textureList.RemoveFront();
			delete oldObject;
		}
	}

	// VIRTUAL
	void TextureRegistry::Update()
	{
		// Intentionally does nothing
	}





	// STATIC
	// Must be dynamically allocated, for it will be deleted by this manager later
	void TextureRegistry::Add(Texture* newObject)
	{
		assert(newObject != nullptr);
		TextureRegistry::singletonInstance->textureList.AddFront(newObject);
	}

	// STATIC
	// Find any Texture
	Texture& TextureRegistry::Find(TextureName name)
	{
		return *(TextureRegistry::singletonInstance->textureList.FindById(static_cast<unsigned int>(name)));
	}

	// STATIC
	// Factory for Textures. Automatically added
	Texture* const TextureRegistry::Create(TextureName name, TextureMapType mapType, const char * const filePath, TextureFilterType filtering, TextureWrapType wrapping)
	{
		assert(TextureRegistry::singletonInstance != nullptr);

		Texture* newTexture = new Texture(filePath, mapType, name);
		newTexture->SetFiltering(filtering);
		newTexture->SetWrapping(wrapping);

		TextureRegistry::Add(newTexture);

		return newTexture;
	}

	// STATIC
	// Factory for Textures. Automatically added
	Texture* const TextureRegistry::Create(TextureName name, TextureMapType mapType, const ImageBuffer& image, TextureFilterType filtering, TextureWrapType wrapping)
	{
		assert(TextureRegistry::singletonInstance != nullptr);

		Texture* newTexture = new Texture(image, mapType, name);
		newTexture->SetFiltering(filtering);
		newTexture->SetWrapping(wrapping);

		TextureRegistry::Add(newTexture);

		return newTexture;
	}

	// STATIC
	// Factory for Textures. Automatically added
	Texture* const TextureRegistry::Create(UseUnpacker_t use, TextureName name, TextureMapType mapType, const char * const nameInPackage, TextureFilterType filtering, TextureWrapType wrapping)
	{
		assert(TextureRegistry::singletonInstance != nullptr);

		Texture* newTexture = new Texture(use, nameInPackage, mapType, name);
		newTexture->SetFiltering(filtering);
		newTexture->SetWrapping(wrapping);

		TextureRegistry::Add(newTexture);

		return newTexture;
	}


}