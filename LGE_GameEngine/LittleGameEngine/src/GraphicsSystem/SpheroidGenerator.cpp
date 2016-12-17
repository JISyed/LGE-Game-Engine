#include "SpheroidGenerator.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <cassert>

namespace lge
{
	SpheroidGenerator::SpheroidGenerator(float radius, unsigned int rings, unsigned int sectors)
	{
		assert(rings > 2);
		assert(sectors > 3);

		float const R = 1.0f / (float)(rings - 1);
		float const S = 1.0f / (float)(sectors - 1);
		unsigned int r, s;
		this->nRings = rings;
		this->nSectors = sectors;



		vertices.resize(rings * sectors * 3);
		normals.resize(rings * sectors * 3);
		texcoords.resize(rings * sectors * 2);
		std::vector<GLfloat>::iterator v = vertices.begin();
		std::vector<GLfloat>::iterator n = normals.begin();
		std::vector<GLfloat>::iterator t = texcoords.begin();
		for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++)
		{
			/*
			float const z = sinf((float)-M_PI_2 + (float) M_PI * r * R);
			float const x = cosf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);
			float const y = sinf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);
			//*/

			//*
			float const y = sinf((float)-M_PI_2 + (float)M_PI * r * R);
			float const x = cosf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);
			float const z = sinf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);
			//*/

			*t++ = 1 - (s*S);
			const float vCoord = 1 - (r*R);
			*t++ = vCoord;

			*v++ = x * radius;
			*v++ = y * radius;
			*v++ = z * radius;

			//*
			*n++ = x;
			*n++ = y;
			*n++ = z;
			//*/


			/*
			*n++ = -x;
			*n++ = -y;
			*n++ = -z;
			//*/
		}

		//indices.resize(rings * sectors * 6);
		//std::vector<GLuint>::iterator i = indices.begin();
		for (r = 0; r < rings - 1; r++) for (s = 0; s < sectors - 1; s++)
		{

			int curRow = r * sectors;
			int nextRow = (r + 1) * sectors;

			/*
			indices.push_back(curRow + s);
			indices.push_back(nextRow + s);
			indices.push_back(nextRow + (s + 1));

			indices.push_back(curRow + s);
			indices.push_back(nextRow + (s + 1));
			indices.push_back(curRow + (s + 1));
			//*/

			//*
			indices.push_back(nextRow + s);
			indices.push_back(curRow + s);
			indices.push_back(nextRow + (s + 1));


			indices.push_back(nextRow + (s + 1));
			indices.push_back(curRow + s);
			indices.push_back(curRow + (s + 1));
			//*/

		}
	}


	std::vector<GLfloat> SpheroidGenerator::GetMixedBuffer()
	{
		using ::std::vector;

		vector<GLfloat> mixedBuffer;
		//mixedBuffer.resize(nRings * nSectors * 8);

		unsigned int pi = 0;
		unsigned int ti = 0;
		unsigned int ni = 0;
		for (unsigned int i = 0; i < nRings * nSectors; i++)
		{
			mixedBuffer.push_back(vertices[pi + 0]);
			mixedBuffer.push_back(vertices[pi + 1]);
			mixedBuffer.push_back(vertices[pi + 2]);

			pi += 3;

			mixedBuffer.push_back(texcoords[ti + 0]);
			mixedBuffer.push_back(texcoords[ti + 1]);

			ti += 2;

			mixedBuffer.push_back(normals[ni + 0]);
			mixedBuffer.push_back(normals[ni + 1]);
			mixedBuffer.push_back(normals[ni + 2]);

			ni += 3;
		}

		return mixedBuffer;
	}
}