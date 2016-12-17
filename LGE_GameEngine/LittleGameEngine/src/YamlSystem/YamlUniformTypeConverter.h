#ifndef H_LGE_YAML_CONVERTER_UNIFORM_TYPE
#define H_LGE_YAML_CONVERTER_UNIFORM_TYPE

#include "yaml-cpp\node\convert.h"
#include "..\GraphicsSystem\UniformNameHelper.h"
#include "YamlUtilities.h"
#include <string>

namespace YAML
{
	template<>
	struct convert<lge::UniformType>
	{
		static Node encode(const lge::UniformType& rhs)
		{
			Node node;
			std::string enumStr;

			switch (rhs)
			{
				case lge::UniformType::Vector4:
					enumStr = "Vector4";
					break;
				case lge::UniformType::Float:
					enumStr = "Float";
					break;
				case lge::UniformType::SignedInt:
					enumStr = "SignedInt";
					break;
				default:
					// New UniformType needs to be added!
					// But following were on purposely not supported:
					//		- Matrix4x4
					//		- TextureUnit
					//		- Matrix4x4Array
					lge::YamlUtilities::YamlSystemAssertion(false);
					break;
			}

			node = enumStr;

			return node;
		}

		static bool decode(const Node& node, lge::UniformType& rhs)
		{
			if (!node.IsScalar())
			{
				return false;
			}

			const std::string enumStr = node.as<std::string>();


			if (enumStr == "Vector4")
			{
				rhs = lge::UniformType::Vector4;
			}
			else if (enumStr == "Float")
			{
				rhs = lge::UniformType::Float;
			}
			else if (enumStr == "SignedInt")
			{
				rhs = lge::UniformType::SignedInt;
			}
			else
			{
				// New UniformType needs to be added!
				// But following were on purposely not supported:
				//		- Matrix4x4
				//		- TextureUnit
				//		- Matrix4x4Array
				lge::YamlUtilities::YamlSystemAssertion(false);
				rhs = lge::UniformType::Vector4;
				return false;
			}


			// Success
			return true;
		}
	};
}
#endif