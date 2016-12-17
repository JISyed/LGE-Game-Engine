#ifndef LGE_UNIFORM_NAME_HELPER_H
#define LGE_UNIFORM_NAME_HELPER_H

#include <cstring>
#include <cassert>
#include "GL\gl3w.h"


// Define the maximum length of a uniform name here
#define LGE_MAX_UNIFORM_NAME_LEN 100


namespace lge
{
	// All the uniform names supported in the engine. Add more if needed.
	// The name scheme should be "Name" followed by "Type".
	enum class UniformName : unsigned int
	{
		ModelMatrix = 0xA0A00000,
		ViewMatrix,
		ProjectionMatrix,
		TintColor,
		ColorMapTexture2d,
		NormalMapTexture2d,
		LightPosition,
		LightDirection,
		LightColor,
		TimeFloat,
		SpecularColor,
		SpecularPowerFloat,
		InverseBindPoses,	// For skinning
		JointsInWorldSpace	// For skinning
	};

	// The data type of the Uniform
	enum class UniformType
	{
		Matrix4x4,
		Vector4,
		Float,
		SignedInt,
		TextureUnit,	// The texture unit for all kinds of samplers (2D, 3D, etc.)
		Matrix4x4Array	// For skinning
	};

	// Define uniform string names from the shaders here:
	namespace UniformStrings
	{
		const char* const MODEL_MATRIX = "model_matrix";
		const char* const VIEW_MATRIX = "view_matrix";
		const char* const PROJ_MATRIX = "proj_matrix";
		const char* const TINT_COLOR = "tint_color";
		const char* const LIGHT_POSITON = "light_pos";
		const char* const LIGHT_DIRECTION = "light_dir";
		const char* const LIGHT_COLOR = "light_color";
		const char* const TIME_FLOAT = "time_value";
		const char* const COLOR_MAP_TEXTURE2D = "color_map";
		const char* const NORMAL_MAP_TEXTURE2D = "normal_map";
		const char* const SPECULAR_COLOR = "specular_color";
		const char* const SPECULAR_POWER = "specular_power";
		const char* const INV_BIND_POSE = "inverse_bind_poses[0]";
		const char* const JOINTS_WORLD = "BoneTransforms.m[0]";//"joints_world[0]";
	}

	// Utility class for enum UniformName
	class UniformNameHelper
	{
	public:

		// Converts a uniform string name into the engine's UnifromName enum.
		// Define new string-to-enum conversions here:
		static UniformName GetUniformNameFromString(const char* const nameInShader)
		{
			assert(nameInShader != nullptr);

			if (!std::strcmp(UniformStrings::MODEL_MATRIX, nameInShader))
				return UniformName::ModelMatrix;

			if (!std::strcmp(UniformStrings::VIEW_MATRIX, nameInShader)) 
				return UniformName::ViewMatrix;

			if (!std::strcmp(UniformStrings::PROJ_MATRIX, nameInShader)) 
				return UniformName::ProjectionMatrix;

			if (!std::strcmp(UniformStrings::TINT_COLOR, nameInShader)) 
				return UniformName::TintColor;

			if (!std::strcmp(UniformStrings::COLOR_MAP_TEXTURE2D, nameInShader))
				return UniformName::ColorMapTexture2d;

			if (!std::strcmp(UniformStrings::NORMAL_MAP_TEXTURE2D, nameInShader))
				return UniformName::NormalMapTexture2d;

			if (!std::strcmp(UniformStrings::LIGHT_POSITON, nameInShader)) 
				return UniformName::LightPosition;

			if (!std::strcmp(UniformStrings::LIGHT_DIRECTION, nameInShader)) 
				return UniformName::LightDirection;

			if (!std::strcmp(UniformStrings::LIGHT_COLOR, nameInShader)) 
				return UniformName::LightColor;

			if (!std::strcmp(UniformStrings::TIME_FLOAT, nameInShader)) 
				return UniformName::TimeFloat;

			if (!std::strcmp(UniformStrings::SPECULAR_COLOR, nameInShader))
				return UniformName::SpecularColor;

			if (!std::strcmp(UniformStrings::SPECULAR_POWER, nameInShader))
				return UniformName::SpecularPowerFloat;

			if (!std::strcmp(UniformStrings::INV_BIND_POSE, nameInShader))
				return UniformName::InverseBindPoses;

			if (!std::strcmp(UniformStrings::JOINTS_WORLD, nameInShader))
				return UniformName::JointsInWorldSpace;


			// If you're here, you should add a new uniform in UniformStrings, UniformName, and this function.
			// The nameInShader was not recognized by the loopup conditionals above.
			// You shouldn't end up here in release!
			assert(false);
			return UniformName::TimeFloat;	// Doesn't matter what this value is
		}


		// Convert OpenGL type-unsafe enums into our type-safe UniformType enum.
		// This only concerns the data type of an OpenGL uniform
		static UniformType GetUniformTypeFromGlenum(const GLenum uniformDataType)
		{
			UniformType uniformType = UniformType::Float;	// Initialize with whatever value

			switch (uniformDataType)
			{
				case GL_FLOAT_MAT4:
					uniformType = UniformType::Matrix4x4;
					break;
				case GL_FLOAT_VEC4:
					uniformType = UniformType::Vector4;
					break;
				case GL_FLOAT:
					uniformType = UniformType::Float;
					break;
				case GL_INT:
					uniformType = UniformType::SignedInt;
					break;
				case GL_SAMPLER_2D:
					uniformType = UniformType::TextureUnit;
					break;
				default:
					// If you are here, your shader has a uniform type that 
					// isn't supported in the engine, yet.
					// Add it to enum UniformType and make a new case.
					// You shouldn't be here in release!
					assert(false);
					break;
			}

			return uniformType;
		}


		// Check for which UniformNames correspond to textures.
		// Must add more cases here when a uniform texture is added to UniformName
		// because this function WILL NEVER ASSERT!
		static const bool UniformNameIsTexture(UniformName uniformName)
		{
			bool isTexture = false;

			switch (uniformName)
			{
				case UniformName::ColorMapTexture2d:
					isTexture = true;
					break;
				case UniformName::NormalMapTexture2d:
					isTexture = true;
					break;
				default:
					// Do nothing; the uniform is obviously not a texture
					break;
			}

			return isTexture;
		}


	private:

		UniformNameHelper() = delete;
		~UniformNameHelper() = delete;
		UniformNameHelper(const UniformNameHelper& other) = delete;
		UniformNameHelper& operator=(const UniformNameHelper& other) = delete;
		UniformNameHelper(UniformNameHelper&& other) = delete;
		UniformNameHelper& operator=(UniformNameHelper&& other) = delete;
	};

	
}
#endif