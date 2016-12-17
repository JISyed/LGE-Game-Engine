#include "MaterialUniform.h"
#include <cassert>

#include "MathEngine.h"
#include "ShaderUniformHandle.h"
#include "UniformData.h"
#include "UniformDataFloat.h"
#include "UniformDataInt.h"
#include "UniformDataMatrix.h"
#include "UniformDataTextureUnit.h"
#include "UniformDataVect.h"
#include "UniformDataMatrixArray.h"

namespace lge
{
	//
	// Methods
	//

	MaterialUniform::MaterialUniform(ShaderUniformHandle* const shaderUniform) :
		name(shaderUniform->GetName()),
		type(shaderUniform->GetDataType()),
		data(nullptr)
	{
		switch (this->type)
		{
			case UniformType::Float:
				this->data = new UniformDataFloat(shaderUniform);
				break;
			case UniformType::Matrix4x4:
				this->data = new UniformDataMatrix(shaderUniform);
				break;
			case UniformType::SignedInt:
				this->data = new UniformDataInt(shaderUniform);
				break;
			case UniformType::TextureUnit:
				this->data = new UniformDataTextureUnit(shaderUniform);
				break;
			case UniformType::Vector4:
				this->data = new UniformDataVect(shaderUniform);
				break;
			case UniformType::Matrix4x4Array:
				this->data = new UniformDataMatrixArray(shaderUniform);
				break;
			default:
				// Unknown data type in UniformType!
				assert(false);
				break;
		}
	}

	MaterialUniform::~MaterialUniform()
	{
		delete this->data;
	}






	const unsigned int MaterialUniform::GetId() const
	{
		return static_cast<unsigned int>(this->name);
	}





	const UniformName MaterialUniform::GetName() const
	{
		return this->name;
	}

	const UniformType MaterialUniform::GetDataType() const
	{
		return this->type;
	}





	void MaterialUniform::SetUniformValue(const Matrix& newValue)
	{
		assert(this->type == UniformType::Matrix4x4);
		this->data->SetUniform(newValue);
	}

	void MaterialUniform::SetUniformValue(const Vect& newValue)
	{
		assert(this->type == UniformType::Vector4);
		this->data->SetUniform(newValue);
	}

	void MaterialUniform::SetUniformValue(const float newValue)
	{
		assert(this->type == UniformType::Float);
		this->data->SetUniform(newValue);
	}

	void MaterialUniform::SetUniformValue(const int newValue)
	{
		assert(this->type == UniformType::SignedInt);
		this->data->SetUniform(newValue);
	}

	void MaterialUniform::SetUniformValue(const TextureUnit newValue)
	{
		assert(this->type == UniformType::TextureUnit);
		this->data->SetUniform(newValue);
	}

	void MaterialUniform::SetUniformValue(const Matrix* const newValue)
	{
		assert(this->type == UniformType::Matrix4x4Array);
		this->data->SetUniform(newValue);
	}




	void MaterialUniform::SendUniformIntoGpu()
	{
		this->data->UpdateUniform();
	}
}