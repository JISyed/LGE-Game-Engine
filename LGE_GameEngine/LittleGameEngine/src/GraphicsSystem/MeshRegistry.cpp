#include "MeshRegistry.h"
#include <cassert>
#include "Camera.h"
#include "CameraManager.h"

namespace lge
{

	//
	// Static Data
	//

	MeshRegistry* MeshRegistry::singletonInstance = nullptr;



	//
	// Methods
	//

	MeshRegistry::MeshRegistry() :
		meshList()
	{
		assert(MeshRegistry::singletonInstance == nullptr);
		MeshRegistry::singletonInstance = this;
	}


	// VIRTUAL
	MeshRegistry::~MeshRegistry()
	{
		// List must be emptied before destroying manager!
		assert(this->meshList.GetNumberOfElements() == 0);

		// Manager must exist in singleton link!
		assert(MeshRegistry::singletonInstance != nullptr);
		MeshRegistry::singletonInstance = this;
	}




	// VIRTUAL
	void MeshRegistry::Load()
	{
		MeshRegistry::Create(MeshName::Cube, "res/meshes/cube.mesh");
		MeshRegistry::Create(MeshName::Tetrahedron, "res/meshes/tetrahedron.mesh");
		MeshRegistry::Create(MeshName::Octahedron, "res/meshes/octahedron.mesh");
		MeshRegistry::Create(MeshName::TrianglePrism, "res/meshes/trianglePrism.mesh");
		MeshRegistry::Create(MeshName::Sphere, "res/meshes/sphere.mesh");
		MeshRegistry::Create(MeshName::BoundingSphere, "res/meshes/boundingSphere.mesh");
		MeshRegistry::Create(UseUnpacker, MeshName::SpaceFrigate, "space_frigate");
		MeshRegistry::Create(UseUnpacker, MeshName::Astroboy, "astroboy");
		MeshRegistry::Create(UseUnpacker, MeshName::Buggy, "buggy");
		MeshRegistry::Create(UseUnpacker, MeshName::WarBear, "warbear");
		MeshRegistry::Create(UseUnpacker, MeshName::Pyramid, "pyramid");
		MeshRegistry::Create(UseUnpacker, MeshName::SkinnedTeddyBear, "teddy_tga");
		MeshRegistry::Create(UseUnpacker, MeshName::SkinnedHumanoid, "humanoid");
	}


	// VIRTUAL
	void MeshRegistry::Unload()
	{
		while (this->meshList.GetNumberOfElements() != 0)
		{
			Mesh* oldObject = this->meshList.RemoveFront();
			delete oldObject;
		}
	}


	// VIRTUAL
	void MeshRegistry::Update()
	{
		// Intentionally does nothing
	}






	// STATIC
	// Must be dynamically allocated, for it will be deleted by this manager later
	void MeshRegistry::Add(Mesh* newObject)
	{
		assert(newObject != nullptr);
		MeshRegistry::singletonInstance->meshList.AddFront(newObject);
	}

	// STATIC
	// Find any Mesh
	Mesh& MeshRegistry::Find(MeshName name)
	{
		return *(MeshRegistry::singletonInstance->meshList.FindById(static_cast<unsigned int>(name)));
	}


	// STATIC
	// Factory for Meshes. Automatically added
	Mesh* const MeshRegistry::Create(MeshName name, const char * const filePath)
	{
		assert(MeshRegistry::singletonInstance != nullptr);
		assert(filePath != nullptr);

		Mesh* newMesh = new Mesh(filePath, name);

		MeshRegistry::Add(newMesh);

		return newMesh;
	}

	// STATIC
	// Factory for Meshes. Automatically added
	Mesh* const MeshRegistry::Create(UseUnpacker_t useUnpacker, MeshName name, const char* const nameInPackage)
	{
		assert(MeshRegistry::singletonInstance != nullptr);
		assert(nameInPackage != nullptr);

		Mesh* newMesh = new Mesh(useUnpacker, nameInPackage, name);

		MeshRegistry::Add(newMesh);

		return newMesh;
	}

	// STATIC
	// Create a camera fustrum mesh, given the camera
	/*Mesh* const MeshRegistry::Create(Camera * const camera, MeshName newName)
	{
		assert(MeshRegistry::singletonInstance != nullptr);
		assert(camera != nullptr);
		assert(newName == MeshName::CameraFustrum);

		Mesh* newMesh = new Mesh(camera, newName);

		MeshRegistry::Add(newMesh);

		return newMesh;
	}*/
}