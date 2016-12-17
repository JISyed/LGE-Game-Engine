#ifndef H_LGE_YAML_CONVERTER_POLYGON_MODE_TYPE
#define H_LGE_YAML_CONVERTER_POLYGON_MODE_TYPE

#include "yaml-cpp\node\convert.h"
#include "..\GraphicsSystem\PolygonMode.h"
#include "YamlUtilities.h"
#include <string>


namespace YAML
{
	template<>
	struct convert<lge::PolygonModeType>
	{
		static Node encode(const lge::PolygonModeType& rhs)
		{
			Node node;
			std::string enumStr;

			switch (rhs)
			{
				case lge::PolygonModeType::FullFace:
					enumStr = "FullFace";
					break;
				case lge::PolygonModeType::Wireframe:
					enumStr = "Wireframe";
					break;
				default:
					// New PolygonModeType needs to be added!
					lge::YamlUtilities::YamlSystemAssertion(false);
					break;
			}

			node = enumStr;

			return node;
		}

		static bool decode(const Node& node, lge::PolygonModeType& rhs)
		{
			if (!node.IsScalar())
			{
				return false;
			}

			const std::string enumStr = node.as<std::string>();


			if (enumStr == "FullFace")
			{
				rhs = lge::PolygonModeType::FullFace;
			}
			else if (enumStr == "Wireframe")
			{
				rhs = lge::PolygonModeType::Wireframe;
			}
			else
			{
				// New PolygonModeType needs to be added!
				lge::YamlUtilities::YamlSystemAssertion(false);
				rhs = lge::PolygonModeType::FullFace;
				return false;
			}


			// Success
			return true;
		}
	};
}
#endif