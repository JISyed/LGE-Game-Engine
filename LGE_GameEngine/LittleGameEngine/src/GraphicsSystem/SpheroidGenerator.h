#ifndef LGE_SPHEREOID_GENERATOR_H
#define LGE_SPHEREOID_GENERATOR_H

#include <vector>
#include "GL\gl3w.h"

namespace lge
{
	// Stolen from StackOverflow. Only for new mesh creation use!!!
	// http://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c/5989676#5989676
	class SpheroidGenerator
	{
	public:
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> normals;
		std::vector<GLfloat> texcoords;
		std::vector<GLuint> indices;
		unsigned int nRings;
		unsigned int nSectors;

	public:
		SpheroidGenerator(float radius, unsigned int rings, unsigned int sectors);

		std::vector<GLfloat> GetMixedBuffer();

		SpheroidGenerator() = delete;
	};
}
#endif