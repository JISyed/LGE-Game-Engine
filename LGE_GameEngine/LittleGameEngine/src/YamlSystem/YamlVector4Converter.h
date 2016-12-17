#ifndef H_LGE_YAML_CONVERTER_VECTOR
#define H_LGE_YAML_CONVERTER_VECTOR

#include "yaml-cpp\node\convert.h"
#include "Vect.h"

namespace YAML
{
	template<>
	struct convert<lge::Vect>
	{
		static Node encode(const lge::Vect& rhs)
		{
			// Don't need the encoder, because we aren't making
			// the game generate YAML files, but for completion,
			// write out entire vector like: [x, y, z, w]

			Node node;
			node.push_back(rhs.x());
			node.push_back(rhs.y());
			node.push_back(rhs.z());
			node.push_back(rhs.w());
			return node;
		}

		static bool decode(const Node& node, lge::Vect& rhs)
		{
			if (!node.IsSequence() || node.size() <= 0)
			{
				return false;
			}

			// Flexible decoding, depending on how many vector components were provided

			if (node.size() == 4)
			{
				rhs.x() = node[0].as<float>();
				rhs.y() = node[1].as<float>();
				rhs.z() = node[2].as<float>();
				rhs.w() = node[3].as<float>();
			}
			else if (node.size() == 3)
			{
				rhs.x() = node[0].as<float>();
				rhs.y() = node[1].as<float>();
				rhs.z() = node[2].as<float>();
				rhs.w() = 1.0f;
			}
			else if (node.size() == 2)
			{
				rhs.x() = node[0].as<float>();
				rhs.y() = node[1].as<float>();
				rhs.z() = 0.0f;
				rhs.w() = 1.0f;
			}
			else if (node.size() == 1)
			{
				rhs.x() = node[0].as<float>();
				rhs.y() = 0.0f;
				rhs.z() = 0.0f;
				rhs.w() = 1.0f;
			}
			else
			{
				return false;
			}

			// Success
			return true;
		}
	};
}
#endif