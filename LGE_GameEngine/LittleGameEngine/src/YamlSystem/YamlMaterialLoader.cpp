#include "YamlMaterialLoader.h"
#include "..\GraphicsSystem\Material.h"
#include "yaml-cpp\yaml.h"
#include "MathEngine.h"
#include "YamlUtilities.h"
#include <cassert>

#include "YamlVector4Converter.h"
#include "YamlMaterialNameConverter.h"
#include "YamlPolygonModeTypeConverter.h"
#include "YamlShaderNameConverter.h"
#include "YamlUniformNameConverter.h"
#include "YamlUniformTypeConverter.h"
#include "YamlTextureNameConverter.h"

#include "..\GraphicsSystem\ShaderRegistry.h"
#include "..\GraphicsSystem\TextureRegistry.h"
#include "..\GraphicsSystem\UniformNameHelper.h"


namespace lge
{
	namespace YamlLoader
	{
		// Load a material from file. Will be returned only 1 Material
		Material* const LoadMaterial(const char* const yamlFilePath)
		{
			Material* newMaterial = nullptr;

			// Check if the YAML file exists. Needed to evade exceptions in yaml-cpp
			const bool fileExists = YamlUtilities::DoesFileExist(yamlFilePath);
			assert(fileExists);

			if (fileExists)
			{
				YAML::Node fileRoot = YAML::LoadFile(std::string(yamlFilePath));

				// There should be a key node under the document root called "LGE-Material"
				const YAML::Node& materialNode = fileRoot["LGE-Material"];

				// Node is mispelled either in YAML or here
				assert(materialNode.IsDefined());

				// Get the needed data to construct a Material (name, polygonMode, shader)
				const MaterialName materialName = materialNode["Name"].as<MaterialName>();
				const PolygonModeType polygonMode = materialNode["PolygonMode"].as<PolygonModeType>();
				const ShaderName shaderName = materialNode["Shader"].as<ShaderName>();

				// Construct a new material from the retrieved data
				newMaterial = new Material(&ShaderRegistry::Find(shaderName),
										   polygonMode,
										   materialName);

				// Go through any uniforms, if any
				const YAML::Node& uniformNodeList = materialNode["Uniforms"];
				if (uniformNodeList.IsDefined() && uniformNodeList.IsSequence())
				{
					// Loop through the list of uniforms
					const size_t NumberOfUniforms = uniformNodeList.size();
					for (size_t uniformIdx = 0; uniformIdx < NumberOfUniforms; uniformIdx++)
					{
						// Get the uniform node holding the map of uniform properties
						const YAML::Node& uniformNode = uniformNodeList[uniformIdx]["Uniform"];
							
						if (uniformNode.IsDefined())
						{
							// Get the name and type of uniform
							const UniformName uniformName = uniformNode["Name"].as<UniformName>();
							const UniformType uniformType = uniformNode["Type"].as<UniformType>();
								
							// Set the uniform value defending on the uniform data type
							const YAML::Node& uniformValueNode = uniformNode["Value"];
							switch (uniformType)
							{
								case UniformType::Vector4:
								{
									assert(uniformValueNode.IsSequence());
									const Vect uniformValue = uniformValueNode.as<Vect>();
									newMaterial->SetUniform(uniformName, uniformValue);
									break;
								}
								case UniformType::Float:
								{
									assert(uniformValueNode.IsScalar());
									const float uniformValue = uniformValueNode.as<float>();
									newMaterial->SetUniform(uniformName, uniformValue);
									break;
								}
								case UniformType::SignedInt:
								{
									assert(uniformValueNode.IsScalar());
									const int uniformValue = uniformValueNode.as<int>();
									newMaterial->SetUniform(uniformName, uniformValue);
									break;
								}
								default:
								{
									break;
								}	
							}	// switch UniformType
						}	// uniform node is valid
					}	// For every uniform defined
				} // If uniform list node is valid

				// Go through any textures, if any
				const YAML::Node& textureListNode = materialNode["Textures"];
				if (textureListNode.IsDefined() && textureListNode.IsSequence())
				{
					// Loop through the list of uniforms
					const size_t NumberOfTextures = textureListNode.size();
					for (size_t textureIdx = 0; textureIdx < NumberOfTextures; textureIdx++)
					{
						// Get the current texture node
						const YAML::Node& textureNode = textureListNode[textureIdx]["Texture"];
						assert(textureNode.IsDefined());

						// Get the name of texture to look up
						const TextureName textureName = textureNode["Name"].as<TextureName>();

						// Set the texture on this material
						newMaterial->SetTexture(&TextureRegistry::Find(textureName));

					} // For every texture defined
				} // If texture list if valid

			}

			return newMaterial;
		}
	}
}