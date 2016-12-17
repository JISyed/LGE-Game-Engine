#ifndef H_LGE_YAML_CONVERTER_UNIFORM_NAME
#define H_LGE_YAML_CONVERTER_UNIFORM_NAME

#include "yaml-cpp\node\convert.h"
#include "..\GraphicsSystem\UniformNameHelper.h"
#include "YamlUtilities.h"
#include <string>

namespace YAML
{
	template<>
	struct convert<lge::UniformName>
	{
		static Node encode(const lge::UniformName& rhs)
		{
			Node node;
			std::string enumStr;

			switch (rhs)
			{
				case lge::UniformName::TintColor:
					enumStr = "TintColor";
					break;
				case lge::UniformName::LightPosition:
					enumStr = "LightPosition";
					break;
				case lge::UniformName::LightDirection:
					enumStr = "LightDirection";
					break;
				case lge::UniformName::LightColor:
					enumStr = "LightColor";
					break;
				case lge::UniformName::TimeFloat:
					enumStr = "TimeFloat";
					break;
				case lge::UniformName::SpecularColor:
					enumStr = "SpecularColor";
					break;
				case lge::UniformName::SpecularPowerFloat:
					enumStr = "SpecularPowerFloat";
					break;
				default:
					// New UniformName needs to be added!
					// But following were on purposely not supported:
					//		- ModelMatrix
					//		- ViewMatrix
					//		- ProjectionMatrix
					//		- ColorMapTexture2d
					//		- NormalMapTexture2d
					//		- InverseBindPoses
					//		- JointsInWorldSpace
					lge::YamlUtilities::YamlSystemAssertion(false);
					break;
			}

			node = enumStr;

			return node;
		}

		static bool decode(const Node& node, lge::UniformName& rhs)
		{
			if (!node.IsScalar())
			{
				return false;
			}

			const std::string enumStr = node.as<std::string>();


			if (enumStr == "TintColor")
			{
				rhs = lge::UniformName::TintColor;
			}
			else if (enumStr == "LightPosition")
			{
				rhs = lge::UniformName::LightPosition;
			}
			else if (enumStr == "LightDirection")
			{
				rhs = lge::UniformName::LightDirection;
			}
			else if (enumStr == "LightColor")
			{
				rhs = lge::UniformName::LightColor;
			}
			else if (enumStr == "TimeFloat")
			{
				rhs = lge::UniformName::TimeFloat;
			}
			else if (enumStr == "SpecularColor")
			{
				rhs = lge::UniformName::SpecularColor;
			}
			else if (enumStr == "SpecularPowerFloat")
			{
				rhs = lge::UniformName::SpecularPowerFloat;
			}
			else
			{
				// New UniformName needs to be added!
				// But following were on purposely not supported:
				//		- ModelMatrix
				//		- ViewMatrix
				//		- ProjectionMatrix
				//		- ColorMapTexture2d
				//		- NormalMapTexture2d
				//		- InverseBindPoses
				//		- JointsInWorldSpace
				lge::YamlUtilities::YamlSystemAssertion(false);
				rhs = lge::UniformName::TimeFloat;
				return false;
			}


			// Success
			return true;
		}
	};
}
#endif