#ifndef H_LGE_YAML_CONVERTER_MATERIAL_NAME
#define H_LGE_YAML_CONVERTER_MATERIAL_NAME

#include "yaml-cpp\node\convert.h"
#include "..\GraphicsSystem\Material.h"
#include "YamlUtilities.h"
#include <string>

namespace YAML
{
	template<>
	struct convert<lge::MaterialName>
	{
		static Node encode(const lge::MaterialName& rhs)
		{
			Node node;
			std::string enumStr;

			switch (rhs)
			{
				case lge::MaterialName::Material1:
					enumStr = "Material1";
					break;
				case lge::MaterialName::Material2:
					enumStr = "Material2";
					break;
				case lge::MaterialName::Material3:
					enumStr = "Material3";
					break;
				case lge::MaterialName::Material4:
					enumStr = "Material4";
					break;
				case lge::MaterialName::Material5:
					enumStr = "Material5";
					break;
				case lge::MaterialName::SpaceFrigate:
					enumStr = "SpaceFrigate";
					break;
				case lge::MaterialName::Astroboy:
					enumStr = "Astroboy";
					break;
				case lge::MaterialName::Buggy:
					enumStr = "Buggy";
					break;
				case lge::MaterialName::WarbearBrown:
					enumStr = "WarbearBrown";
					break;
				case lge::MaterialName::WarbearPolar:
					enumStr = "WarbearPolar";
					break;
				case lge::MaterialName::SkinnedTextureDiffuseBear:
					enumStr = "SkinnedTextureDiffuseBear";
					break;
				case lge::MaterialName::SkinnedTextureDiffueseHumanoid:
					enumStr = "SkinnedTextureDiffueseHumanoid";
					break;
				default:
					// On purposely not supported:
					//		- Default
					//		- CameraOrbitTarget
					//		- BoundingSphereInside
					//		- BoundingSphereOutside
					// But otherwise, needs to be added!
					lge::YamlUtilities::YamlSystemAssertion(false);
					break;
			}

			node = enumStr;

			return node;
		}

		static bool decode(const Node& node, lge::MaterialName& rhs)
		{
			if (!node.IsScalar())
			{
				return false;
			}

			const std::string enumStr = node.as<std::string>();


			if (enumStr == "Material1")
			{
				rhs = lge::MaterialName::Material1;
			}
			else if (enumStr == "Material2")
			{
				rhs = lge::MaterialName::Material2;
			}
			else if (enumStr == "Material3")
			{
				rhs = lge::MaterialName::Material3;
			}
			else if (enumStr == "Material4")
			{
				rhs = lge::MaterialName::Material4;
			}
			else if (enumStr == "Material5")
			{
				rhs = lge::MaterialName::Material5;
			}
			else if (enumStr == "SpaceFrigate")
			{
				rhs = lge::MaterialName::SpaceFrigate;
			}
			else if (enumStr == "Astroboy")
			{
				rhs = lge::MaterialName::Astroboy;
			}
			else if (enumStr == "Buggy")
			{
				rhs = lge::MaterialName::Buggy;
			}
			else if (enumStr == "WarbearBrown")
			{
				rhs = lge::MaterialName::WarbearBrown;
			}
			else if (enumStr == "WarbearPolar")
			{
				rhs = lge::MaterialName::WarbearPolar;
			}
			else if (enumStr == "SkinnedTextureDiffuseBear")
			{
				rhs = lge::MaterialName::SkinnedTextureDiffuseBear;
			}
			else if (enumStr == "SkinnedTextureDiffueseHumanoid")
			{
				rhs = lge::MaterialName::SkinnedTextureDiffueseHumanoid;
			}
			else
			{
				// On purposely not supported:
				//		- Default
				//		- CameraOrbitTarget
				//		- BoundingSphereInside
				//		- BoundingSphereOutside
				// But otherwise, needs to be added!
				lge::YamlUtilities::YamlSystemAssertion(false);
				rhs = lge::MaterialName::Material1;
				return false;
			}


			// Success
			return true;
		}
	};
}
#endif