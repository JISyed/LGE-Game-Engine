#ifndef H_LGE_YAML_CONVERTER_SHADER_NAME
#define H_LGE_YAML_CONVERTER_SHADER_NAME

#include "yaml-cpp\node\convert.h"
#include "..\GraphicsSystem\Shader.h"
#include "YamlUtilities.h"
#include <string>

namespace YAML
{
	template<>
	struct convert<lge::ShaderName>
	{
		static Node encode(const lge::ShaderName& rhs)
		{
			Node node;
			std::string enumStr;

			switch (rhs)
			{
				case lge::ShaderName::BlinnPhong:
					enumStr = "BlinnPhong";
					break;
				case lge::ShaderName::ConstantColor:
					enumStr = "ConstantColor";
					break;
				case lge::ShaderName::ConstantTexture:
					enumStr = "ConstantTexture";
					break;
				case lge::ShaderName::DiffuseTexture:
					enumStr = "DiffuseTexture";
					break;
				case lge::ShaderName::VertexRainbow:
					enumStr = "VertexRainbow";
					break;
				case lge::ShaderName::NormalDiffuseTexture:
					enumStr = "NormalDiffuseTexture";
					break;
				case lge::ShaderName::NormalSpecularTexture:
					enumStr = "NormalSpecularTexture";
					break;
				case lge::ShaderName::SkinnedDiffuseTexture:
					enumStr = "SkinnedDiffuseTexture";
					break;
				default:
					// New ShaderName needs to be added!
					lge::YamlUtilities::YamlSystemAssertion(false);
					break;
			}

			node = enumStr;

			return node;
		}

		static bool decode(const Node& node, lge::ShaderName& rhs)
		{
			if (!node.IsScalar())
			{
				return false;
			}

			const std::string enumStr = node.as<std::string>();


			if (enumStr == "BlinnPhong")
			{
				rhs = lge::ShaderName::BlinnPhong;
			}
			else if (enumStr == "ConstantColor")
			{
				rhs = lge::ShaderName::ConstantColor;
			}
			else if (enumStr == "ConstantTexture")
			{
				rhs = lge::ShaderName::ConstantTexture;
			}
			else if (enumStr == "DiffuseTexture")
			{
				rhs = lge::ShaderName::DiffuseTexture;
			}
			else if (enumStr == "VertexRainbow")
			{
				rhs = lge::ShaderName::VertexRainbow;
			}
			else if (enumStr == "NormalDiffuseTexture")
			{
				rhs = lge::ShaderName::NormalDiffuseTexture;
			}
			else if (enumStr == "NormalSpecularTexture")
			{
				rhs = lge::ShaderName::NormalSpecularTexture;
			}
			else if (enumStr == "SkinnedDiffuseTexture")
			{
				rhs = lge::ShaderName::SkinnedDiffuseTexture;
			}
			else
			{
				// New PolygonModeType needs to be added!
				lge::YamlUtilities::YamlSystemAssertion(false);
				rhs = lge::ShaderName::ConstantColor;
				return false;
			}


			// Success
			return true;
		}
	};
}
#endif