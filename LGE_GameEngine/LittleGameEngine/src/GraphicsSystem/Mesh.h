#ifndef LGE_MESH_H
#define LGE_MESH_H

#include "GL\gl3w.h"
#include "..\EngineUtilities\IdGenerator.h"
#include "..\UnpackagerSystem\ResourceUnpacker.h"

namespace lge
{
	class Camera;

	////////////////////////////////
	//  Enums
	////////////////////////////////

	// TEMP: Find a more dynamic way to name meshes
	enum class MeshName : unsigned int
	{
		Cube,
		Tetrahedron,
		Octahedron,
		TrianglePrism,
		Sphere,
		BoundingSphere,	// Less fidelity than regular Sphere
		SpaceFrigate,
		Astroboy,
		Buggy,
		WarBear,
		//CameraFustrum,
		Pyramid,
		SkinnedTeddyBear,
		SkinnedHumanoid
	};

	////////////////////////////////
	//  The Mesh class
	////////////////////////////////

	// Represents a collection of vertices that compose of a renderable 3D shape
	class Mesh
	{
	public:

		//
		// Ctor / Dtor
		//

		Mesh(const char* const meshFilePath, MeshName newName);
		Mesh(UseUnpacker_t useUnpacker, const char* const meshNameInPackage, MeshName newName);
		//Mesh(Camera * const camera, MeshName newName);
		~Mesh();


		//
		// Getters
		//

		// Get the number of vertices in this Mesh
		const int GetNumberOfVerts();

		// Get the number of triangles in this Mesh
		const int GetNumberOfTriangles();
		
		// Get the ID of this Mesh
		const unsigned int GetId() const;


		//
		// Methods
		//

		// Make this mesh the current active mesh for vertex rendering
		void MakeActiveMesh();

		


	private:

		//
		// Data
		//

		MeshName name;
		int numberOfVerts;
		int numberOfTriangles;
		int sizeInBytes;
		GLuint vao;
		GLuint vbo[2];	//First is vertex data, and second is triangle indices
		bool isSkinned;


		//
		// Static Data
		//

		static IdGenerator s_idGen;




		//
		// Deleted Methods
		//

		// No default ctor
		Mesh() = delete;

		// No copy ctor
		Mesh(const Mesh& other) = delete;

		// No copy assignment
		Mesh& operator=(const Mesh& other) = delete;

		// No move ctor
		Mesh(Mesh&& other) = delete;

		// No move assignment
		Mesh& operator=(Mesh&& other) = delete;
	};

	
}

#endif