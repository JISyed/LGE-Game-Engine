#include "MaterialRegistry.h"
#include <cassert>

#include "ShaderRegistry.h"
#include "TextureRegistry.h"
#include "..\YamlSystem\YamlMaterialLoader.h"
#include <string>


#define LGE_MATERIAL_DATA_PATH	"res/materials/"

namespace lge
{
	//
	// Static Data
	//

	MaterialRegistry* MaterialRegistry::singletonInstance = nullptr;



	//
	// Methods
	//

	MaterialRegistry::MaterialRegistry() :
		materialList()
	{
		assert(MaterialRegistry::singletonInstance == nullptr);
		MaterialRegistry::singletonInstance = this;
	}

	// VIRTUAL
	MaterialRegistry::~MaterialRegistry()
	{
		// List must be emptied before destroying manager!
		assert(this->materialList.GetNumberOfElements() == 0);

		// Manager must exist in singleton link!
		assert(MaterialRegistry::singletonInstance != nullptr);
		MaterialRegistry::singletonInstance = this;
	}






	// VIRTUAL
	void MaterialRegistry::Load()
	{
		// Load the following materials from file

		this->Create(UseYaml, "mat_duckweed.yml");
		this->Create(UseYaml, "mat_shiny_phong.yml");
		this->Create(UseYaml, "mat_rocks.yml");
		this->Create(UseYaml, "mat_mario_ground.yml");
		this->Create(UseYaml, "mat_vertex_rainbow.yml");
		this->Create(UseYaml, "mat_space_frigate.yml");
		this->Create(UseYaml, "mat_astroboy.yml");
		this->Create(UseYaml, "mat_buggy.yml");
		this->Create(UseYaml, "mat_warbear_brown.yml");
		this->Create(UseYaml, "mat_warbear_polar.yml");
		this->Create(UseYaml, "mat_teddy_bear.yml");
		this->Create(UseYaml, "mat_humanoid.yml");




		// The following materials are critical to the engine
		// and thus will not be loaded from YAML

		MaterialRegistry::Create(MaterialName::Default,
								 ShaderName::ConstantTexture,
								 PolygonModeType::FullFace,
								 TextureName::Default);

		Material* camOrbitTarget = MaterialRegistry::Create(MaterialName::CameraOrbitTarget,
															ShaderName::ConstantColor,
															PolygonModeType::Wireframe);
		camOrbitTarget->SetUniform(UniformName::TintColor, Vect(0.5f, 0.3f, 0.0f));

		Material* matBounSphereIn = MaterialRegistry::Create(MaterialName::BoundingSphereInside,
															 ShaderName::ConstantColor,
															 PolygonModeType::Wireframe);
		matBounSphereIn->SetUniform(UniformName::TintColor, Vect(0.0f, 1.0f, 0.0f));

		Material* matBounSphereOut = MaterialRegistry::Create(MaterialName::BoundingSphereOutside,
															  ShaderName::ConstantColor,
															  PolygonModeType::Wireframe);
		matBounSphereOut->SetUniform(UniformName::TintColor, Vect(1.0f, 0.0f, 0.0f));
	}








	// VIRTUAL
	void MaterialRegistry::Unload()
	{
		while (this->materialList.GetNumberOfElements() != 0)
		{
			Material* oldObject = this->materialList.RemoveFront();
			delete oldObject;
		}
	}


	// VIRTUAL
	void MaterialRegistry::Update()
	{
		// Intentionally does nothing
	}



	// Factory for Material. Automatically added
	Material* const MaterialRegistry::Create(LgeUseYaml_t useYaml, const char* const materialFileName)
	{
		useYaml;
		assert(useYaml == UseYaml);

		const std::string fullPath = std::string(LGE_MATERIAL_DATA_PATH) + std::string(materialFileName);

		Material* const newMaterial = YamlLoader::LoadMaterial(fullPath.c_str());
		MaterialRegistry::Add(newMaterial);

		return newMaterial;
	}




	// STATIC
	// Must be dynamically allocated, for it will be deleted by this manager later
	void MaterialRegistry::Add(Material* newObject)
	{
		assert(newObject != nullptr);
		MaterialRegistry::singletonInstance->materialList.AddFront(newObject);
	}

	// STATIC
	// Find any Material
	Material& MaterialRegistry::Find(MaterialName name)
	{
		return *(MaterialRegistry::singletonInstance->materialList.FindById(static_cast<unsigned int>(name)));
	}



	// STATIC
	// Factory for Material. Automatically added
	Material* const MaterialRegistry::Create(MaterialName newName, ShaderName shaderName, PolygonModeType polygonMode)
	{
		assert(MaterialRegistry::singletonInstance != nullptr);

		Material* newMaterial = new Material(&ShaderRegistry::Find(shaderName),
											 polygonMode,
											 newName);

		MaterialRegistry::Add(newMaterial);

		return newMaterial;

	}
	
	// STATIC
	// Factory for Material. Automatically added. Also adds a color map texture
	Material* const MaterialRegistry::Create(MaterialName newName, ShaderName shaderName, PolygonModeType polygonMode, TextureName textureName)
	{
		Material* newMaterial = MaterialRegistry::Create(newName, shaderName, polygonMode);

		newMaterial->SetTexture(&TextureRegistry::Find(textureName));

		return newMaterial;
	}



}