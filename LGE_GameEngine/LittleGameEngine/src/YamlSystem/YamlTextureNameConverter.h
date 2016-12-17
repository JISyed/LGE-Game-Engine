#ifndef H_LGE_YAML_CONVERTER_TEXTURE_NAME
#define H_LGE_YAML_CONVERTER_TEXTURE_NAME

#include "yaml-cpp\node\convert.h"
#include "..\GraphicsSystem\Texture.h"
#include "YamlUtilities.h"
#include <string>

namespace YAML
{
	template<>
	struct convert<lge::TextureName>
	{
		static Node encode(const lge::TextureName& rhs)
		{
			Node node;
			std::string enumStr;

			switch (rhs)
			{
				case lge::TextureName::Duckweed:
					enumStr = "Duckweed";
					break;
				case lge::TextureName::DuckweedUp:
					enumStr = "DuckweedUp";
					break;
				case lge::TextureName::DuckweedFlip:
					enumStr = "DuckweedFlip";
					break;
				case lge::TextureName::MarioGround:
					enumStr = "MarioGround";
					break;
				case lge::TextureName::Rocks:
					enumStr = "Rocks";
					break;
				case lge::TextureName::ExampleNormalMap:
					enumStr = "ExampleNormalMap";
					break;
				case lge::TextureName::SpaceFrigate:
					enumStr = "SpaceFrigate";
					break;
				case lge::TextureName::Astroboy:
					enumStr = "Astroboy";
					break;
				case lge::TextureName::BuggyDiffuse:
					enumStr = "BuggyDiffuse";
					break;
				case lge::TextureName::WarbearBrown:
					enumStr = "WarbearBrown";
					break;
				case lge::TextureName::WarbearPolar:
					enumStr = "WarbearPolar";
					break;
				case lge::TextureName::Default:
					enumStr = "Default";
					break;
				case lge::TextureName::TeddyBear:
					enumStr = "TeddyBear";
					break;
				default:
					// New TextureName needs to be added!
					lge::YamlUtilities::YamlSystemAssertion(false);
					break;
			}

			node = enumStr;

			return node;
		}

		static bool decode(const Node& node, lge::TextureName& rhs)
		{
			if (!node.IsScalar())
			{
				return false;
			}

			const std::string enumStr = node.as<std::string>();


			if (enumStr == "Duckweed")
			{
				rhs = lge::TextureName::Duckweed;
			}
			else if (enumStr == "DuckweedUp")
			{
				rhs = lge::TextureName::DuckweedUp;
			}
			else if (enumStr == "DuckweedFlip")
			{
				rhs = lge::TextureName::DuckweedFlip;
			}
			else if (enumStr == "MarioGround")
			{
				rhs = lge::TextureName::MarioGround;
			}
			else if (enumStr == "Rocks")
			{
				rhs = lge::TextureName::Rocks;
			}
			else if (enumStr == "ExampleNormalMap")
			{
				rhs = lge::TextureName::ExampleNormalMap;
			}
			else if (enumStr == "SpaceFrigate")
			{
				rhs = lge::TextureName::SpaceFrigate;
			}
			else if (enumStr == "Astroboy")
			{
				rhs = lge::TextureName::Astroboy;
			}
			else if (enumStr == "BuggyDiffuse")
			{
				rhs = lge::TextureName::BuggyDiffuse;
			}
			else if (enumStr == "WarbearBrown")
			{
				rhs = lge::TextureName::WarbearBrown;
			}
			else if (enumStr == "WarbearPolar")
			{
				rhs = lge::TextureName::WarbearPolar;
			}
			else if (enumStr == "Default")
			{
				rhs = lge::TextureName::Default;
			}
			else if (enumStr == "TeddyBear")
			{
				rhs = lge::TextureName::TeddyBear;
			}
			else
			{
				// New TextureName needs to be added!
				lge::YamlUtilities::YamlSystemAssertion(false);
				rhs = lge::TextureName::Default;
				return false;
			}


			// Success
			return true;
		}
	};
}
#endif