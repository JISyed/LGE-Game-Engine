#include "Material.h"
#include <cassert>

#include "PolygonModeFullFace.h"
#include "PolygonModeWireframe.h"

#include "Shader.h"
#include "ShaderUniformHandle.h"


namespace lge
{
	IdGenerator Material::s_idGen;


	Material::Material(Shader* const shader, const PolygonModeType polygonMode, MaterialName newName) :
		targetShader(shader),
		uniformList(),
		textureList(),
		name(newName)
	{
		assert(shader != nullptr);

		// Setup the Polygon Rendering Mode
		if (polygonMode == PolygonModeType::FullFace)
		{
			this->polygonRenderingMode = new PolygonModeFullFace();
		}
		else if (polygonMode == PolygonModeType::Wireframe)
		{
			this->polygonRenderingMode = new PolygonModeWireframe();
		}


		// Setup material uniforms from the shader
		const unsigned int totalUniforms = this->targetShader->GetNumberOfUniforms();
		ShaderUniformHandle* const uniformArray = this->targetShader->GetUniforms();
		for (unsigned int i = 0u; i < totalUniforms; i++)
		{
			MaterialUniform* newUniform = new MaterialUniform(&uniformArray[i]);
			this->uniformList.AddFront(newUniform);
		}

		// After the uniforms are setup, scan those uniforms for any textures
		GenericListIterator<MaterialUniform> itr = this->uniformList.GetIterator();
		while (!itr.IsDone())
		{
			MaterialUniform* const currUniform = itr.CurrentItem();
			if (UniformNameHelper::UniformNameIsTexture(currUniform->GetName()))
			{
				MaterialTextureLink* newLink = new MaterialTextureLink(currUniform->GetName());
				this->textureList.AddFront(newLink);
			}

			// Next uniform
			itr.Next();
		}
	}

	Material::~Material()
	{
		this->targetShader = nullptr;
		delete this->polygonRenderingMode;

		while (this->uniformList.GetNumberOfElements() != 0)
		{
			MaterialUniform* oldUniform = this->uniformList.RemoveFront();
			delete oldUniform;
		}

		while (this->textureList.GetNumberOfElements() != 0)
		{
			MaterialTextureLink* oldLink = this->textureList.RemoveFront();
			delete oldLink;
		}

		this->uniformList.Clear();
	}






	// Makes this Material the active material. Also makes its Shader active.
	void Material::MakeActive()
	{
		// Activate the shader
		this->ActivateOnlyShader();


		// Activate any textures this material might have
		if (this->textureList.GetNumberOfElements() != 0)
		{
			GenericListIterator<MaterialTextureLink> lnkItr = this->textureList.GetIterator();
			MaterialTextureLink* currTextureLink = lnkItr.First();
			while (!lnkItr.IsDone())
			{
				assert(currTextureLink != nullptr);
				currTextureLink->ActivateTexture();
				currTextureLink = lnkItr.Next();
			}
		}

		// Update all uniforms into the GPU
		if (this->uniformList.GetNumberOfElements() != 0)
		{
			GenericListIterator<MaterialUniform> uniItr = this->uniformList.GetIterator();
			MaterialUniform* currUniform = uniItr.First();
			while (!uniItr.IsDone())
			{
				assert(currUniform != nullptr);
				currUniform->SendUniformIntoGpu();
				currUniform = uniItr.Next();
			}
		}
	}



	// Sets the polygon render state for OpenGL
	void Material::SetPolygonRenderState()
	{
		this->polygonRenderingMode->SetState();
	}


	// Restores the polygon render state for OpenGL
	void Material::RestorePolygonRenderState()
	{
		this->polygonRenderingMode->RestoreState();
	}


	// Change into a different polygon mode given a type
	void Material::ChangePolygonMode(const PolygonModeType newPolygonMode)
	{
		PolygonModeType currentType = this->polygonRenderingMode->GetType();

		// If the types are not the same...
		if (newPolygonMode != currentType)
		{
			//... Delete the old mode
			delete this->polygonRenderingMode;

			// Make the new mode
			if (newPolygonMode == PolygonModeType::FullFace)
			{
				this->polygonRenderingMode = new PolygonModeFullFace();
			}
			else if (newPolygonMode == PolygonModeType::Wireframe)
			{
				this->polygonRenderingMode = new PolygonModeWireframe();
			}
		}

		// If the types were the same, do nothing.
	}







	bool Material::SetUniform(UniformName uniformName, const Matrix& newValue)
	{
		const unsigned int idFromName = static_cast<unsigned int>(uniformName);

		MaterialUniform* foundUniform = this->uniformList.FindById(idFromName);

		// If the uniform was found
		if (foundUniform != nullptr)
		{
			// This will assert somewhere inside if the data type is incorrect
			foundUniform->SetUniformValue(newValue);
			return true;
		}

		return false;
	}

	bool Material::SetUniform(UniformName uniformName, const Vect& newValue)
	{
		const unsigned int idFromName = static_cast<unsigned int>(uniformName);

		MaterialUniform* foundUniform = this->uniformList.FindById(idFromName);

		// If the uniform was found
		if (foundUniform != nullptr)
		{
			// This will assert somewhere inside if the data type is incorrect
			foundUniform->SetUniformValue(newValue);
			return true;
		}

		return false;
	}

	bool Material::SetUniform(UniformName uniformName, float newValue)
	{
		const unsigned int idFromName = static_cast<unsigned int>(uniformName);

		MaterialUniform* foundUniform = this->uniformList.FindById(idFromName);

		// If the uniform was found
		if (foundUniform != nullptr)
		{
			// This will assert somewhere inside if the data type is incorrect
			foundUniform->SetUniformValue(newValue);
			return true;
		}

		return false;
	}

	bool Material::SetUniform(UniformName uniformName, int newValue)
	{
		const unsigned int idFromName = static_cast<unsigned int>(uniformName);

		MaterialUniform* foundUniform = this->uniformList.FindById(idFromName);

		// If the uniform was found
		if (foundUniform != nullptr)
		{
			// This will assert somewhere inside if the data type is incorrect
			foundUniform->SetUniformValue(newValue);
			return true;
		}

		return false;
	}

	bool Material::SetUniform(UniformName uniformName, TextureUnit newValue)
	{
		const unsigned int idFromName = static_cast<unsigned int>(uniformName);

		MaterialUniform* foundUniform = this->uniformList.FindById(idFromName);

		// If the uniform was found
		if (foundUniform != nullptr)
		{
			// This will assert somewhere inside if the data type is incorrect
			foundUniform->SetUniformValue(newValue);
			return true;
		}

		return false;
	}

	// Set a uniform in this Material (that's a Matrix array) (must be 100 matrices)
	bool Material::SetUniform(UniformName uniformName, const Matrix* const newValueArray)
	{
		const unsigned int idFromName = static_cast<unsigned int>(uniformName);

		MaterialUniform* foundUniform = this->uniformList.FindById(idFromName);

		// If the uniform was found
		if (foundUniform != nullptr)
		{
			// This will assert somewhere inside if the data type is incorrect
			foundUniform->SetUniformValue(newValueArray);
			return true;
		}

		return false;
	}




	bool Material::SetTexture(Texture* const texture)
	{
		bool success = false;

		if (this->textureList.GetNumberOfElements() == 0)
		{
			return false;
		}

		const UniformName nameInShader = texture->GetNameInShader();

		// Find out if the given texture would be supported in this material
		GenericListIterator<MaterialTextureLink> itr = this->textureList.GetIterator();
		MaterialTextureLink* currentLink = itr.CurrentItem();
		while (!itr.IsDone())
		{
			if (currentLink->GetNameInShader() == nameInShader)
			{
				// Found! The texture will be set
				success = true;
				currentLink->SetTexture(texture);
				break;
			}

			currentLink = itr.Next();
		}

		if (currentLink != nullptr)
		{
			// Set the texture unit of this material
			this->ActivateOnlyShader();
			this->SetUniform(nameInShader, currentLink->GetTextureUnit());
		}

		return success;
	}



	const unsigned int Material::GetId() const
	{
		return static_cast<unsigned int>(this->name);
	}


	// Set the shader (better know what you're doing)
	Shader* const Material::GetShader() const
	{
		return this->targetShader;
	}




	//
	// Private Routines
	//

	// Make the shader the only active shader, 
	// without making every other aspect of this Material active
	void Material::ActivateOnlyShader()
	{
		this->targetShader->MakeActive();
	}

}