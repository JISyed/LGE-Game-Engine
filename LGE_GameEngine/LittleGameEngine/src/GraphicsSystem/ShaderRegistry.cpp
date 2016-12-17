#include "ShaderRegistry.h"
#include <cassert>

namespace lge
{
	//
	// Static Data
	//

	ShaderRegistry* ShaderRegistry::singletonInstance = nullptr;



	//
	// Methods
	//

	ShaderRegistry::ShaderRegistry() :
		shaderList()
	{
		assert(ShaderRegistry::singletonInstance == nullptr);
		ShaderRegistry::singletonInstance = this;
	}

	// VIRTUAL
	ShaderRegistry::~ShaderRegistry()
	{
		// List must be emptied before destroying manager!
		assert(this->shaderList.GetNumberOfElements() == 0);

		// Manager must exist in singleton link!
		assert(ShaderRegistry::singletonInstance != nullptr);
		ShaderRegistry::singletonInstance = this;
	}





	// VIRTUAL
	void ShaderRegistry::Load()
	{
		ShaderRegistry::Create(ShaderName::DiffuseTexture,
							   "res/shaders/diffuseTexturePointLight.vs.glsl",
							   "res/shaders/diffuseTexturePointLight.fs.glsl");

		ShaderRegistry::Create(ShaderName::BlinnPhong,
							   "res/shaders/blinnPhongColor.vs.glsl",
							   "res/shaders/blinnPhongColor.fs.glsl");

		ShaderRegistry::Create(ShaderName::ConstantColor,
							   "res/shaders/constantColor.vs.glsl",
							   "res/shaders/constantColor.fs.glsl");

		ShaderRegistry::Create(ShaderName::ConstantTexture,
							   "res/shaders/constantTexture.vs.glsl",
							   "res/shaders/constantTexture.fs.glsl");

		ShaderRegistry::Create(ShaderName::VertexRainbow,
							   "res/shaders/vertRainbow.vs.glsl",
							   "res/shaders/vertRainbow.fs.glsl");

		ShaderRegistry::Create(ShaderName::NormalDiffuseTexture,
							   "res/shaders/normalTextureDiffuse.vs.glsl",
							   "res/shaders/normalTextureDiffuse.fs.glsl");

		ShaderRegistry::Create(ShaderName::NormalSpecularTexture,
							   "res/shaders/normalTextureSpecular.vs.glsl",
							   "res/shaders/normalTextureSpecular.fs.glsl");

		ShaderRegistry::Create(ShaderName::SkinnedDiffuseTexture,
							   "res/shaders/skinnedTextureLight.vs.glsl",
							   "res/shaders/skinnedTextureLight.fs.glsl");
	}


	// VIRTUAL
	void ShaderRegistry::Unload()
	{
		while (this->shaderList.GetNumberOfElements() != 0)
		{
			Shader* oldObject = this->shaderList.RemoveFront();
			delete oldObject;
		}
	}


	// VIRTUAL
	void ShaderRegistry::Update()
	{
		// Intentionally does nothing
	}






	// STATIC
	// Must be dynamically allocated, for it will be deleted by this manager later
	void ShaderRegistry::Add(Shader* newObject)
	{
		assert(newObject != nullptr);
		ShaderRegistry::singletonInstance->shaderList.AddFront(newObject);
	}

	// STATIC
	// Find any Shader
	Shader& ShaderRegistry::Find(ShaderName name)
	{
		return *( ShaderRegistry::singletonInstance->shaderList.FindById(static_cast<unsigned int>(name)) );
	}



	// STATIC
	// Factory for Shaders. Automatically added
	Shader* const ShaderRegistry::Create(ShaderName name, const char* const vertFilePath, const char* const fragFilePath)
	{
		assert(ShaderRegistry::singletonInstance != nullptr);

		Shader* newShader = new Shader(vertFilePath, fragFilePath, name);

		ShaderRegistry::Add(newShader);

		return newShader;
	}



}