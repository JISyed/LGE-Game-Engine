#include "Mesh.h"
#include <cassert>

#include "File.h"

#include "SpheroidGenerator.h"
#include "MeshFileHeader.h"
#include "VertexData.h"
#include "TriangleData.h"
#include "Camera.h"
#include "CameraProjectionData.h"
#include "CameraTransformAdapter.h"

// No skinning support
struct OldVertexData
{
	float x;	// X position
	float y;	// Y postion
	float z;	// Z position
	float u;	// Horizontal texture coordinate
	float v;	// Vertical texture coordinate
	float nx;	// Vertex normal (X component)
	float ny;	// Vertex normal (Y component)
	float nz;	// Vertex normal (Z component)
};

namespace lge
{
	/*
	// Cube

	TriangleData triangeIndices[] =
	{
		{0, 1, 2},
		{2, 4-1, 0},

		{6 - 2, 7 - 2, 8 - 2},
		{7 - 2, 6 - 2, 11 - 4},

		{12 - 4, 13 - 4, 14 - 4},
		{13 - 4, 12 - 4, 17 - 6},


		{18 - 6, 19 - 6, 20 - 6},
		{20 - 6, 22 - 7, 18 - 6},

		{24 - 8, 25 - 8, 26 - 8},
		{25 - 8, 24 - 8, 29 - 10},


		{30 - 10, 31 - 10, 32 - 10},
		{32 - 10, 34 - 11, 30 - 10}
	};
	static OldVertexData cubeVerts[] = 
	{
		// X     Y      Z     U      V    NX     NY      NZ
		// Back face
		{-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f}, // Bottom-left  0
		{0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f}, // bottom-right  1  
		{0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f}, // top-right      2

		//{0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f}, // top-right      2=3
		{-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f}, // top-left       4-1
		//{-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f}, // bottom-left  0=5 


		// Front face
		{-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}, // bottom-left     6-2
		{0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}, // top-right         7-2
		{0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}, // bottom-right      8-2

		//{0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}, // top-right         7=9
		//{-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}, // bottom-left     6=10
		{-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f}, // top-left        11 -4


		// Left face
		{-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f}, // top-right        12 - 4
		{-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f}, // bottom-left     13 -4
		{-0.5f, 0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f}, // top-left         14-4

		//{-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f}, // bottom-left    13=15
		//{-0.5f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f}, // top-right       12=16
		{-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f}, // bottom-right    17 -6



		// Right face
		{0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, // top-left         18-6
		{0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f}, // top-right       19-6
		{0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f}, // bottom-right   20-6

		//{0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f}, // bottom-right   20=21
		{0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}, // bottom-left     22-7
		//{0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}, // top-left         18=23


		// Bottom face          
		{-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f}, // top-right    24 -8
		{0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f}, // bottom-left    25-8
		{0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f}, // top-left      26-8

		//{0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f}, // bottom-left     25=27
		//{-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f}, // top-right     24=28
		{-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f}, // bottom-right     29-10


		// Top face
		{-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}, // top-left      30-10
		{0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f}, // top-right     31-10
		{0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f}, // bottom-right    32  -10 

		//{0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f}, // bottom-right     32=33
		{-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f}, // bottom-left     34-11
		//{-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}  // top-left      30=25          
	};
	//*/



	// Tetrahedron Mesh
	/*

	TriangleData triangeIndices[] =
	{
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{9, 10, 11}
	};

	static OldVertexData cubeVerts[] =
	{
		{-0.5f, -0.3f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f},	// L     0
		{0.5f, -0.3f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f},	// R     1
		{0.0f, 0.3f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f},	    // T     2      
		 
		{-0.5f, -0.3f, -0.5f, 0.0f, 0.0f, -0.7f, 0.5f, 0.2f},	// L     3       
		{0.0f, 0.3f, -0.5f, 0.0f, 1.0f, -0.7f, 0.5f, 0.2f},	// T         4     
		{0.0f, 0.0f, 0.5f, 1.0f, 0.5f, -0.7f, 0.5f, 0.2f},	// F         5    

		{0.0f, 0.0f, 0.5f, 1.0f, 0.5f, 0.7f, 0.5f, 0.2f},	// F         6       
		{0.0f, 0.3f, -0.5f, 0.0f, 1.0f, 0.7f, 0.5f, 0.2f},	// T         7       
		{0.5f, -0.3f, -0.5f, 0.0f, 0.0f, 0.7f, 0.5f, 0.2f},	// R         8     

		{-0.5f, -0.3f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f},// L        9     
		{0.0f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, -1.0f, 0.0f},// F           10      
		{0.5f, -0.3f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f}	// R         11    
	};
	//*/


	/*
	// Octohedron

	TriangleData triangeIndices[] =
	{
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{9, 10, 11},
		{12, 13, 14},
		{15, 16, 17},
		{18, 19, 20},
		{21, 22, 23}
	};

	static OldVertexData cubeVerts[] =
	{
		{0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.7f, 0.3f, 0.7f},	//A       0               
		{0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.7f, 0.3f, 0.7f},	//B        1            
		{0.0f, 0.8f, 0.0f, 0.25f, 1.0f, 0.7f, 0.3f, 0.7f},	//C       2             
		

		{-0.5f, 0.0f, 0.0f, 0.5f, 0.0f, -0.7f, 0.3f, 0.7f},//D       3             
		{0.0f, 0.8f, 0.0f, 0.25f, 1.0f, -0.7f, 0.3f, 0.7f},//C      4              
		{0.0f, 0.0f, 0.5f, 0.0f, 0.0f, -0.7f, 0.3f, 0.7f},	//B     5               
		

		{0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.7f, 0.3f, -0.7f},//A       6             
		{0.0f, 0.8f, 0.0f, 0.25f, 1.0f, 0.7f, 0.3f, -0.7f},//C      7              
		{0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 0.7f, 0.3f, -0.7f},	//E     8               
		

		{-0.5f, 0.0f, 0.0f, 0.5f, 0.0f, -0.7f, 0.3f, -0.7f},//D     9               
		{0.0f, 0.0f, -0.5f, 0.0f, 0.0f, -0.7f, 0.3f, -0.7f},//E     10               
		{0.0f, 0.8f, 0.0f, 0.25f, 1.0f, -0.7f, 0.3f, -0.7f},//C     11               
		

		{0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.7f, -0.3f, 0.7f},	//A      12              
		{0.0f, -0.8f, 0.0f, 0.25f, 1.0f, 0.7f, -0.3f, 0.7f},//F      13              
		{0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 0.7f, -0.3f, 0.7f},//B        14            
		

		{-0.5f, 0.0f, 0.0f, 0.5f, 0.0f, -0.7f, -0.3f, 0.7f},//D      15              
		{0.0f, 0.0f, 0.5f, 0.0f, 0.0f, -0.7f, -0.3f, 0.7f},	//B      16              
		{0.0f, -0.8f, 0.0f, 0.25f, 1.0f, -0.7f, -0.3f, 0.7f},//F    17                
		

		{0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.7f, -0.3f, -0.7f},//A        18            
		{0.0f, 0.0f, -0.5f, 0.5f, 0.0f, 0.7f, -0.3f, -0.7f},//E       19             
		{0.0f, -0.8f, 0.0f, 0.25f, 1.0f, 0.7f, -0.3f, -0.7f},//F       20             
		

		{-0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -0.7f, -0.3f, -0.7f},	//D     21               
		{0.0f, -0.8f, 0.0f, 0.25f, 1.0f, -0.7f, -0.3f, -0.7f},//F       22             
		{0.0f, 0.0f, -0.5f, 0.5f, 0.0f, -0.7f, -0.3f, -0.7f}	//E     23               
	};
	//*/


	/*
	// Triangular Prism

	TriangleData triangeIndices[] =
	{
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{8, 7, 11 - 2},
		{12 - 2, 13 - 2, 14 - 2},
		{12 - 2, 14 - 2, 17 - 4},
		{18 - 4, 19 - 4, 20 - 4},
		{19 - 4, 18 - 4, 23 - 6}
	};

	static VertexData cubeVerts[] = {
		{-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f}, // LO      0 
		{0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}, // RO       1      
		{0.0f, -0.6f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f}, // BO      2       
		

		{-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f}, // LI    3          
		{0.0f, -0.6f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f}, // BI    4          
		{0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f}, // RI      5          
		

		{-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, -0.7f, -0.3f, 0.0f}, // LO    6            
		{0.0f, -0.6f, 0.5f, 0.0f, 0.0f, -0.7f, -0.3f, 0.0f}, // BO    7            
		{-0.5f, 0.5f, -0.5f, 0.7f, 1.0f, -0.7f, -0.3f, 0.0f}, // LI   8            
		

		//{-0.5f, 0.5f, -0.5f, 0.7f, 1.0f, -0.7f, -0.3f, 0.0f}, // LI    9=8            
		//{0.0f, -0.6f, 0.5f, 0.0f, 0.0f, -0.7f, -0.3f, 0.0f}, // BO     10=7      
		{0.0f, -0.6f, -0.5f, 0.7f, 0.0f, -0.7f, -0.3f, 0.0f}, // BI    11 -2              
		

		{0.0f, -0.6f, 0.5f, 0.0f, 0.0f, 0.7f, -0.3f, 0.0f}, // BO      12 -2          
		{0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.7f, -0.3f, 0.0f}, // RO       13 -2            
		{0.5f, 0.5f, -0.5f, 0.7f, 1.0f, 0.7f, -0.3f, 0.0f}, // RI       14 -2     
		

		//{0.0f, -0.6f, 0.5f, 0.0f, 0.0f, 0.7f, -0.3f, 0.0f}, // BO      15=12-2       
		//{0.5f, 0.5f, -0.5f, 0.7f, 1.0f, 0.7f, -0.3f, 0.0f}, // RI      16=14-2        
		{0.0f, -0.6f, -0.5f, 0.7f, 0.0f, 0.7f, -0.3f, 0.0f}, // BI     17-4       
		

		{-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f}, // LO      18 -4         
		{0.5f, 0.5f, -0.5f, 1.0f, 0.7f, 0.0f, 1.0f, 0.0f}, // RI      19 -4       
		{0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f}, // RO       20 -4        
		

		//{0.5f, 0.5f, -0.5f, 1.0f, 0.7f, 0.0f, 1.0f, 0.0f}, // RI      21=19-4         
		//{-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f},  // LO      22=18-4          
		{-0.5f, 0.5f, -0.5f, 0.0f, 0.7f, 0.0f, 1.0f, 0.0f} // LI       23-6            
		
	};
	//*/
	
	//
	// C Helpers
	//
	
	bool SaveMesh(const char* const meshFilePath, 
				  const int sizeInBytes, 
				  const int numberOfVerts, 
				  const int numberOfTris,
				  const OldVertexData* const vertexArray,
				  const TriangleData* const triangleArray)
	{
		FileHandle fh;
		FileError  ferror;

		//----------- WRITE ------------------------------------------
		ferror = File::open(fh, meshFilePath, FileMode::FILE_WRITE);
		assert(ferror == FileError::FILE_SUCCESS);

		// Setup the header
		MeshFileHeader headerToWrite;
		headerToWrite.sizeOnBytes = sizeInBytes;
		headerToWrite.numVertices = numberOfVerts;
		headerToWrite.numTriangles = numberOfTris;

		// Write header
		ferror = File::write(fh, &headerToWrite, sizeof(MeshFileHeader));
		assert(ferror == FileError::FILE_SUCCESS);

		// write the vert buffer data
		ferror = File::write(fh, vertexArray, sizeof(OldVertexData) * headerToWrite.numVertices);
		assert(ferror == FileError::FILE_SUCCESS);

		// write the index buffer
		ferror = File::write(fh, triangleArray, sizeof(TriangleData) * headerToWrite.numTriangles);
		assert(ferror == FileError::FILE_SUCCESS);

		ferror = File::close(fh);
		assert(ferror == FileError::FILE_SUCCESS);
		
		// Always false because the mesh was NOT loaded from file (saving is not loading)
		return false;
	}

	bool LoadMesh(const char* const meshFilePath,
				  int& sizeInBytes,
				  int& numberOfVerts,
				  int& numberOfTris,
				  OldVertexData*& vertexArray,
				  TriangleData*& triangleArray)
	{
		// Read the data from a file ---------------------------------------------
		FileHandle fh2;
		FileError  ferror;

		//----------- READ ------------------------------------------
		ferror = File::open(fh2, meshFilePath, FileMode::FILE_READ, true);
		assert(ferror == FileError::FILE_SUCCESS);

		// Read header
		MeshFileHeader headerToRead;
		ferror = File::read(fh2, &headerToRead, sizeof(MeshFileHeader));
		assert(ferror == FileError::FILE_SUCCESS);

		sizeInBytes = headerToRead.sizeOnBytes;
		numberOfVerts = headerToRead.numVertices;
		numberOfTris = headerToRead.numTriangles;

		vertexArray = new OldVertexData[headerToRead.numVertices];
		ferror = File::read(fh2, (void*)vertexArray, sizeof(OldVertexData) * headerToRead.numVertices);
		assert(ferror == FileError::FILE_SUCCESS);

		triangleArray = new TriangleData[headerToRead.numTriangles];
		ferror = File::read(fh2, (void*)triangleArray, sizeof(TriangleData) * headerToRead.numTriangles);
		assert(ferror == FileError::FILE_SUCCESS);

		ferror = File::close(fh2);
		assert(ferror == FileError::FILE_SUCCESS);

		// Always true because the mesh was loaded from file
		return true;
	}
	


	// ======================================================================
	// ======================================================================
	// Mesh class starts here:
	//=======================================================================
	// ======================================================================


	//
	// Static Data
	//

	IdGenerator Mesh::s_idGen;


	//
	// Methods
	//
	
	Mesh::Mesh(const char* const meshFilePath, MeshName newName) :
		name(newName),
		isSkinned(false)
	{
		this->vao = 0;
		this->vbo[0] = 0;
		this->vbo[1] = 0;
		
		
		OldVertexData* vertexArray = nullptr;
		TriangleData* triangleArray = nullptr;

		bool meshCameFromFile = false;

		/*
		SpheroidGenerator sphere = SpheroidGenerator(1.0f, 8, 8);
		auto sphereData = sphere.GetMixedBuffer();

		if (newName == MeshName::BoundingSphere)
		{
			// 0 if reading mesh data, 1 if writing mesh data
			#if 1
				// Write the data to a file ---------------------------------------------
				this->numberOfVerts = sphereData.size() / 8;
				this->sizeInBytes = sphereData.size() * sizeof(float);
				this->numberOfTriangles = sphere.indices.size() / 3;
				vertexArray = (OldVertexData*)sphereData.data();
				triangleArray = (TriangleData*)sphere.indices.data();

				meshCameFromFile = SaveMesh(meshFilePath,
											this->sizeInBytes,
											this->numberOfVerts,
											this->numberOfTriangles,
											vertexArray,
											triangleArray);

			#else
				// Read the data from a file ---------------------------------------------
				
				this->numberOfVerts = sphereData.size() / 8;
				this->sizeInBytes = sphereData.size() * sizeof(float);
				this->numberOfTriangles = sphere.indices.size() / 3;
				vertexArray = (OldVertexData*) sphereData.data();
				triangleArray = (TriangleData*) sphere.indices.data();
			#endif
		}
		else
		//*/
		{
			// 0 if reading mesh data, 1 if writing mesh data
			#if 0
				// Write the data to a file ---------------------------------------------
				this->sizeInBytes = sizeof(cubeVerts);
				this->numberOfVerts = sizeof(cubeVerts) / sizeof(OldVertexData);
				this->numberOfTriangles = sizeof(triangeIndices) / sizeof(TriangleData);

				vertexArray = cubeVerts;
				triangleArray = triangeIndices;

				meshCameFromFile = SaveMesh(meshFilePath,
											this->sizeInBytes,
											this->numberOfVerts,
											this->numberOfTriangles,
											vertexArray,
											triangleArray);

			#else
				// Read the data from a file ---------------------------------------------
				meshCameFromFile = LoadMesh(meshFilePath,
											this->sizeInBytes,
											this->numberOfVerts,
											this->numberOfTriangles,
											vertexArray,
											triangleArray);
			#endif
		}


		// Create the Vertex Array Object
		glGenVertexArrays(1, &this->vao);
		assert(this->vao != 0);
		glBindVertexArray(this->vao);

		// Create the Vertex Buffer Object
		glGenBuffers(2, this->vbo);
		assert(this->vbo[0] != 0);
		assert(this->vbo[1] != 0);
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

		// Load data into the GPU
		glBufferData(GL_ARRAY_BUFFER,
					 this->sizeInBytes,
					 (float*) vertexArray,
					 GL_STATIC_DRAW);


		// Format data ...

		// Vertex position data is located at 0 (in vertex shader)
		void *startingOffsetVert = (void *)((unsigned int)&vertexArray[0].x - (unsigned int)vertexArray);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OldVertexData), startingOffsetVert);
		glEnableVertexAttribArray(0);



		// Texture UV data is location: 1  (used in vertex shader)
		void *startingOffsetTex = (void *)((unsigned int)&vertexArray[0].u - (unsigned int)vertexArray);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(OldVertexData), startingOffsetTex);
		glEnableVertexAttribArray(1);


		// normals data in location 2 (used in vertex shader)
		void *startingOffsetNorm = (void *)((unsigned int)&vertexArray[0].nx - (unsigned int)vertexArray);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(OldVertexData), startingOffsetNorm);
		glEnableVertexAttribArray(2);



		// Load the index data: ---------------------------------------------------------

		// Bind our 2nd VBO as being the active buffer and storing triangle indices (which OpenGL called "elements")
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

		// Copy the index data to our buffer
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TriangleData) * this->numberOfTriangles, triangleArray, GL_STATIC_DRAW);



		// Delete mesh data on CPU
		if (meshCameFromFile)
		{
			delete[] vertexArray;
			vertexArray = nullptr;
			delete[] triangleArray;
			triangleArray = nullptr;
		}
	}


	// USING THE UNPACKER
	Mesh::Mesh(UseUnpacker_t useUnpacker, const char* const meshNameInPackage, MeshName newName) :
		name(newName),
		isSkinned(true)
	{
		useUnpacker;
		bool bufferLoaded = true;
		this->vao = 0;
		this->vbo[0] = 0;
		this->vbo[1] = 0;


		// OpenGL Setup

		// Create the Vertex Array Object
		glGenVertexArrays(1, &this->vao);
		assert(this->vao != 0);
		glBindVertexArray(this->vao);

		// Create the Vertex Buffer Object
		glGenBuffers(2, this->vbo);
		assert(this->vbo[0] != 0);
		assert(this->vbo[1] != 0);
		
		


		// Vertex Setup
		
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);

		{
			// Load vertex buffer from package
			VboHeader vboHdr;
			float* vertexBuffer = nullptr;
			bufferLoaded = ResourceUnpacker::ReadVertices(meshNameInPackage, vboHdr, vertexBuffer);
			assert(bufferLoaded == true);
			assert(vertexBuffer != nullptr);
			if (bufferLoaded == false)
			{
				// Leave in release mode. We don't want to blow up the computer.
				return;
			}


			this->sizeInBytes = vboHdr.rawSizeInBytes;
			this->numberOfVerts = vboHdr.rawSizeInBytes / sizeof(VertexData);


			// Load data into the GPU
			glBufferData(GL_ARRAY_BUFFER,
						 this->sizeInBytes,
						 vertexBuffer,
						 GL_STATIC_DRAW);


			// Format Vertex data

			// Vertex position data is located at attirbute 0
			void* startingOffsetVert = (void *)((unsigned int)&vertexBuffer[0] - (unsigned int)vertexBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), startingOffsetVert);
			glEnableVertexAttribArray(0);



			// Texture UV data is location: attirbute 1 
			void* startingOffsetTex = (void *)((unsigned int)&vertexBuffer[3] - (unsigned int)vertexBuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), startingOffsetTex);
			glEnableVertexAttribArray(1);


			// normals data in location 2
			void* startingOffsetNorm = (void *)((unsigned int)&vertexBuffer[5] - (unsigned int)vertexBuffer);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), startingOffsetNorm);
			glEnableVertexAttribArray(2);


			// Joint Weights for skinning in location attirbute 3 
			void* startingOffsetWeight = (void*)((unsigned int)&vertexBuffer[8] - (unsigned int)vertexBuffer);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), startingOffsetWeight);
			glEnableVertexAttribArray(3);

			// Joint indices for skinning in location sttirbute 4
			void* startingOffsetJointIdx = (void*)((unsigned int)&vertexBuffer[12] - (unsigned int)vertexBuffer);
			glVertexAttribIPointer(4, 4, GL_UNSIGNED_INT, sizeof(VertexData), startingOffsetJointIdx);
			glEnableVertexAttribArray(4);


			// Done with vertices
			delete[] vertexBuffer;
			vertexBuffer = nullptr;
		}



		// Triangle Setup
		{
			EboHeader eboHdr;
			unsigned int* triangleBuffer = nullptr;
			bufferLoaded = ResourceUnpacker::ReadTriangles(meshNameInPackage, eboHdr, triangleBuffer);
			assert(bufferLoaded == true);
			assert(triangleBuffer != nullptr);
			if (bufferLoaded == false)
			{
				// Leave in release mode. We don't want to blow up the computer.
				return;
			}

			this->numberOfTriangles = eboHdr.rawSizeInBytes / sizeof(TriangleData);

			// Load the index data: ---------------------------------------------------------

			// Bind our 2nd VBO as being the active buffer and storing triangle indices (which OpenGL called "elements")
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

			// Copy the index data to our buffer
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, eboHdr.rawSizeInBytes, triangleBuffer, GL_STATIC_DRAW);


			delete[] triangleBuffer;
			triangleBuffer = nullptr;
		}
	}


	//Mesh::Mesh(Camera * const camera, MeshName newName) :
	//	name(newName),
	//	isSkinned(false)
	//{
	//	OldVertexData pVerts[9];
	//	TriangleData triList[8];

	//	const size_t TRILIST_NUM_TRIANGLES = (sizeof(triList) / sizeof(TriangleData));
	//	const size_t MESH_DATA_NUM_VERTS = (sizeof(pVerts) / sizeof(OldVertexData));


	//	triList[0].vertex0 = 0;
	//	triList[0].vertex1 = 1;
	//	triList[0].vertex2 = 2;
	//	
	//	triList[1].vertex0 = 0;
	//	triList[1].vertex1 = 2;
	//	triList[1].vertex2 = 3;
	//	
	//	triList[2].vertex0 = 0;
	//	triList[2].vertex1 = 3;
	//	triList[2].vertex2 = 4;
	//	
	//	triList[3].vertex0 = 0;
	//	triList[3].vertex1 = 4;
	//	triList[3].vertex2 = 1;
	//	
	//	// far
	//	triList[4].vertex0 = 1;
	//	triList[4].vertex1 = 2;
	//	triList[4].vertex2 = 3;
	//	
	//	// far
	//	triList[5].vertex0 = 3;
	//	triList[5].vertex1 = 4;
	//	triList[5].vertex2 = 1;
	//	
	//	// near
	//	triList[6].vertex0 = 5;
	//	triList[6].vertex1 = 6;
	//	triList[6].vertex2 = 7;
	//	
	//	// near
	//	triList[7].vertex0 = 7;
	//	triList[7].vertex1 = 8;
	//	triList[7].vertex2 = 5;

	//	Vect vTmp;

	//	camera->Update();

	//	vTmp = camera->GetTransform().GetPosition();
	//	pVerts[0].x = vTmp[x];
	//	pVerts[0].y = vTmp[y];
	//	pVerts[0].z = vTmp[z];
	//	pVerts[0].nx = 0.000000f;
	//	pVerts[0].ny = 0.000000f;
	//	pVerts[0].nz = 0.000000f;
	//	pVerts[0].u = 0.000000f;
	//	pVerts[0].v = 0.000000f;

	//	vTmp = camera->GetProjectionData()->farTopRight; //getFarTopRight(vTmp);
	//	pVerts[1].x = vTmp[x];
	//	pVerts[1].y = vTmp[y];
	//	pVerts[1].z = vTmp[z];
	//	pVerts[1].nx = 0.000000f;
	//	pVerts[1].ny = 0.000000f;
	//	pVerts[1].nz = 0.000000f;
	//	pVerts[1].u = 0.000000f;
	//	pVerts[1].v = 0.000000f;

	//	vTmp = camera->GetProjectionData()->farTopLeft; //getFarTopLeft(vTmp);
	//	pVerts[2].x = vTmp[x];
	//	pVerts[2].y = vTmp[y];
	//	pVerts[2].z = vTmp[z];
	//	pVerts[2].nx = 0.000000f;
	//	pVerts[2].ny = 0.000000f;
	//	pVerts[2].nz = 0.000000f;
	//	pVerts[2].u = 0.000000f;
	//	pVerts[2].v = 0.000000f;

	//	vTmp = camera->GetProjectionData()->farBottomLeft; //getFarBottomLeft(vTmp);
	//	pVerts[3].x = vTmp[x];
	//	pVerts[3].y = vTmp[y];
	//	pVerts[3].z = vTmp[z];
	//	pVerts[3].nx = 0.000000f;
	//	pVerts[3].ny = 0.000000f;
	//	pVerts[3].nz = 0.000000f;
	//	pVerts[3].u = 0.000000f;
	//	pVerts[3].v = 0.000000f;

	//	vTmp = camera->GetProjectionData()->farBottomRight; //getFarBottomRight(vTmp);
	//	pVerts[4].x = vTmp[x];
	//	pVerts[4].y = vTmp[y];
	//	pVerts[4].z = vTmp[z];
	//	pVerts[4].nx = 0.000000f;
	//	pVerts[4].ny = 0.000000f;
	//	pVerts[4].nz = 0.000000f;
	//	pVerts[4].u = 0.000000f;
	//	pVerts[4].v = 0.000000f;

	//	vTmp = camera->GetProjectionData()->nearTopRight; //getNearTopRight(vTmp);
	//	pVerts[5].x = vTmp[x];
	//	pVerts[5].y = vTmp[y];
	//	pVerts[5].z = vTmp[z];
	//	pVerts[5].nx = 0.000000f;
	//	pVerts[5].ny = 0.000000f;
	//	pVerts[5].nz = 0.000000f;
	//	pVerts[5].u = 0.000000f;
	//	pVerts[5].v = 0.000000f;

	//	vTmp = camera->GetProjectionData()->nearTopLeft; //getNearTopLeft(vTmp);
	//	pVerts[6].x = vTmp[x];
	//	pVerts[6].y = vTmp[y];
	//	pVerts[6].z = vTmp[z];
	//	pVerts[6].nx = 0.000000f;
	//	pVerts[6].ny = 0.000000f;
	//	pVerts[6].nz = 0.000000f;
	//	pVerts[6].u = 0.000000f;
	//	pVerts[6].v = 0.000000f;

	//	vTmp = camera->GetProjectionData()->nearBottomLeft; //getNearBottomLeft(vTmp);
	//	pVerts[7].x = vTmp[x];
	//	pVerts[7].y = vTmp[y];
	//	pVerts[7].z = vTmp[z];
	//	pVerts[7].nx = 0.000000f;
	//	pVerts[7].ny = 0.000000f;
	//	pVerts[7].nz = 0.000000f;
	//	pVerts[7].u = 0.000000f;
	//	pVerts[7].v = 0.000000f;

	//	vTmp = camera->GetProjectionData()->nearBottomRight; //getNearBottomRight(vTmp);
	//	pVerts[8].x = vTmp[x];
	//	pVerts[8].y = vTmp[y];
	//	pVerts[8].z = vTmp[z];
	//	pVerts[8].nx = 0.000000f;
	//	pVerts[8].ny = 0.000000f;
	//	pVerts[8].nz = 0.000000f;
	//	pVerts[8].u = 0.000000f;
	//	pVerts[8].v = 0.000000f;


	//	this->vao = 0;
	//	this->vbo[0] = 0;
	//	this->vbo[1] = 0;


	//	// OpenGL Setup

	//	// Create the Vertex Array Object
	//	glGenVertexArrays(1, &this->vao);
	//	assert(this->vao != 0);
	//	glBindVertexArray(this->vao);

	//	// Create the Vertex Buffer Object
	//	glGenBuffers(2, this->vbo);
	//	assert(this->vbo[0] != 0);
	//	assert(this->vbo[1] != 0);




	//	// Vertex Setup

	//	glBindBuffer(GL_ARRAY_BUFFER, this->vbo[0]);
	//	{
	//		this->sizeInBytes = sizeof(pVerts);
	//		this->numberOfVerts = MESH_DATA_NUM_VERTS;


	//		// Load data into the GPU
	//		glBufferData(GL_ARRAY_BUFFER,
	//					 this->sizeInBytes,
	//					 pVerts,
	//					 GL_STATIC_DRAW);


	//		// Format Vertex data

	//		// Vertex position data is located at 0 (in vertex shader)
	//		void *startingOffsetVert = (void *)((unsigned int)&pVerts[0].x - (unsigned int)pVerts);
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OldVertexData), startingOffsetVert);
	//		glEnableVertexAttribArray(0);



	//		// Texture UV data is location: 1  (used in vertex shader)
	//		void *startingOffsetTex = (void *)((unsigned int)&pVerts[0].u - (unsigned int)pVerts);
	//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(OldVertexData), startingOffsetTex);
	//		glEnableVertexAttribArray(1);


	//		// normals data in location 2 (used in vertex shader)
	//		void *startingOffsetNorm = (void *)((unsigned int)&pVerts[0].nx - (unsigned int)pVerts);
	//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(OldVertexData), startingOffsetNorm);
	//		glEnableVertexAttribArray(2);
	//	}



	//	// Triangle Setup
	//	{
	//		this->numberOfTriangles = TRILIST_NUM_TRIANGLES;

	//		// Load the index data: ---------------------------------------------------------

	//		// Bind our 2nd VBO as being the active buffer and storing triangle indices (which OpenGL called "elements")
	//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);

	//		// Copy the index data to our buffer
	//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numberOfTriangles * sizeof(TriangleData), triList, GL_STATIC_DRAW);
	//	}
	//}


	Mesh::~Mesh()
	{
		glBindVertexArray(this->vao);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		if (this->isSkinned)
		{
			glDisableVertexAttribArray(3);
			glDisableVertexAttribArray(4);
		}

		glDeleteBuffers(2, this->vbo);
		glDeleteVertexArrays(1, &this->vao);
		
	}





	const int Mesh::GetNumberOfVerts()
	{
		return this->numberOfVerts;
	}

	const int Mesh::GetNumberOfTriangles()
	{
		return this->numberOfTriangles;
	}



	const unsigned int Mesh::GetId() const
	{
		return static_cast<unsigned int>(this->name);
	}



	void Mesh::MakeActiveMesh()
	{
		glBindVertexArray(this->vao);
	}


	

}