#include "ResourceUnpacker.h"
#include <cassert>
#include <utility>
#include "..\AbstractDataTypes\CString.h"

#include "PackageHeader.h"
#include "PackageChunkHeader.h"
#include "AnimationHeader.h"
#include "ClipHeader.h"


#define LGE_RESOURCE_FILE_PATH "res/packages/game_resources.lgepkg"

namespace lge
{
	//
	// Public Routines
	//

	// STATIC
	// Read a vertex buffer from the resource package given a name. Returns true if found and loaded properly
	const bool ResourceUnpacker::ReadVertices(const char* const ResourceName, VboHeader& vertDataHeader, float*& vertBuffer)
	{
		FileHandle file;
		bool success = true;
		success = ResourceUnpacker::OpenPackageFile(file, LGE_RESOURCE_FILE_PATH);
		if (success)
		{
			PackageHeader packageHeader;
			success = ResourceUnpacker::ReadPackageHeader(file, packageHeader);
			if (success)
			{
				PackageChunkHeader chunkHeader;
				success = ResourceUnpacker::FindPackageChunk(file,
															 chunkHeader,
															 packageHeader.numChunks,
															 PackageChunkType::Vertices,
															 ResourceName
															 );
				if (success)
				{
					// Now get the custom specified data
					FileError fileError = File::read(file, &vertDataHeader, sizeof(VboHeader));
					assert(fileError != FileError::FILE_READ_FAIL);
					if (fileError == FileError::FILE_SUCCESS)
					{
						// The chunk's size without the custom data header must be the same as the data payload
						assert(vertDataHeader.rawSizeInBytes == (chunkHeader.chunkSize - (int)sizeof(VboHeader)));
						vertBuffer = nullptr;
						vertBuffer = new float[vertDataHeader.numberOfElement];
						assert(vertBuffer != nullptr);
						if (vertBuffer != nullptr)
						{
							fileError = File::read(file, vertBuffer, vertDataHeader.rawSizeInBytes);
							assert(fileError != FileError::FILE_READ_FAIL);
							if (fileError == FileError::FILE_SUCCESS)
							{
								// Finally done
								success = true;
								ResourceUnpacker::ClosePackageFile(file);
							}
						}
					}
				}
			}
		}

		//ResourceUnpacker::ClosePackageFile(file);
		return success;
	}

	// STATIC
	// Read a triangle buffer from the resource package given a name. Returns true if found and loaded properly
	const bool ResourceUnpacker::ReadTriangles(const char* const ResourceName, EboHeader& triDataHeader, unsigned int*& triBuffer)
	{
		FileHandle file;
		bool success = true;
		success = ResourceUnpacker::OpenPackageFile(file, LGE_RESOURCE_FILE_PATH);
		if (success)
		{
			PackageHeader packageHeader;
			success = ResourceUnpacker::ReadPackageHeader(file, packageHeader);
			if (success)
			{
				PackageChunkHeader chunkHeader;
				success = ResourceUnpacker::FindPackageChunk(file,
															 chunkHeader,
															 packageHeader.numChunks,
															 PackageChunkType::Trianges,
															 ResourceName
															 );
				if (success)
				{
					// Now get the custom specified data
					FileError fileError = File::read(file, &triDataHeader, sizeof(EboHeader));
					assert(fileError != FileError::FILE_READ_FAIL);
					if (fileError == FileError::FILE_SUCCESS)
					{
						// The chunk's size without the custom data header must be the same as the data payload
						assert(triDataHeader.rawSizeInBytes == (chunkHeader.chunkSize - (int)sizeof(EboHeader)));
						triBuffer = nullptr;
						triBuffer = new unsigned int[triDataHeader.numberOfElement];
						assert(triBuffer != nullptr);
						if (triBuffer != nullptr)
						{
							fileError = File::read(file, triBuffer, triDataHeader.rawSizeInBytes);
							assert(fileError != FileError::FILE_READ_FAIL);
							if (fileError == FileError::FILE_SUCCESS)
							{
								// Finally done
								success = true;
								ResourceUnpacker::ClosePackageFile(file);
							}
						}
					}
				}
			}
		}

		return success;
	}

	// STATIC
	// Read a texture buffer from the resource package given a name. Returns true if found and loaded properly
	const bool ResourceUnpacker::ReadTexture(const char* const ResourceName, TextureHeader& texDataHeader, unsigned char*& texBuffer)
	{
		FileHandle file;
		bool success = true;
		success = ResourceUnpacker::OpenPackageFile(file, LGE_RESOURCE_FILE_PATH);
		if (success)
		{
			PackageHeader packageHeader;
			success = ResourceUnpacker::ReadPackageHeader(file, packageHeader);
			if (success)
			{
				PackageChunkHeader chunkHeader;
				success = ResourceUnpacker::FindPackageChunk(file,
															 chunkHeader,
															 packageHeader.numChunks,
															 PackageChunkType::Texture,
															 ResourceName
															 );
				if (success)
				{
					// Now get the custom specified data
					FileError fileError = File::read(file, &texDataHeader, sizeof(TextureHeader));
					assert(fileError != FileError::FILE_READ_FAIL);
					if (fileError == FileError::FILE_SUCCESS)
					{
						// The chunk's size without the custom data header must be the same as the data payload
						const size_t textureBufferSize = texDataHeader.height * texDataHeader.width * texDataHeader.depth;
						assert(textureBufferSize == (chunkHeader.chunkSize - sizeof(TextureHeader)));
						texBuffer = nullptr;
						texBuffer = new unsigned char[textureBufferSize];
						assert(texBuffer != nullptr);
						if (texBuffer != nullptr)
						{
							fileError = File::read(file, texBuffer, textureBufferSize);
							assert(fileError != FileError::FILE_READ_FAIL);
							if (fileError == FileError::FILE_SUCCESS)
							{
								// Finally done
								success = true;
								ResourceUnpacker::ClosePackageFile(file);
							}
						}
					}
				}
			}
		}

		return success;
	}

	// STATIC
	// Read a bounding sphere from the resource package given a name. Returns true if found and loaded properly
	const bool ResourceUnpacker::ReadBoundingSphere(const char* const ResourceName, BoundingSphere& sphere)
	{
		FileHandle file;
		bool success = true;
		success = ResourceUnpacker::OpenPackageFile(file, LGE_RESOURCE_FILE_PATH);
		if (success)
		{
			PackageHeader packageHeader;
			success = ResourceUnpacker::ReadPackageHeader(file, packageHeader);
			if (success)
			{
				PackageChunkHeader chunkHeader;
				success = ResourceUnpacker::FindPackageChunk(file,
															 chunkHeader,
															 packageHeader.numChunks,
															 PackageChunkType::BoundingSphere,
															 ResourceName
															 );
				if (success)
				{
					// Now get the custom specified data
					FileError fileError = File::read(file, &sphere, chunkHeader.chunkSize);
					assert(fileError != FileError::FILE_READ_FAIL);
					if (fileError == FileError::FILE_SUCCESS)
					{
						// Finally done
						success = true;
						ResourceUnpacker::ClosePackageFile(file);
					}
				}
			}
		}

		return success;
	}

	// STATIC
	// Read an entire animation set from the resource package given a name. Returns true if found and loaded properly.
	const bool ResourceUnpacker::ReadAnimationSet(const char* const ResourceName, AnimationSet*& animationSet)
	{
		FileHandle file;
		bool success = true;
		success = ResourceUnpacker::OpenPackageFile(file, LGE_RESOURCE_FILE_PATH);
		if (success)
		{
			PackageHeader packageHeader;
			success = ResourceUnpacker::ReadPackageHeader(file, packageHeader);
			if (success)
			{
				PackageChunkHeader chunkHeader;
				success = ResourceUnpacker::FindPackageChunk(file,
															 chunkHeader,
															 packageHeader.numChunks,
															 PackageChunkType::Animation,
															 ResourceName
															 );
				if (success)
				{
					// Delegate the complexity of animation deserialzation elsewhere
					ResourceUnpacker::DeserializeAnimationData(file, animationSet);
					ResourceUnpacker::ClosePackageFile(file);

					// The pointer becoming null indicates that something wrong happened
					if (animationSet == nullptr)
					{
						success = false;
					}
				}
			}
		}

		return success;
	}







	//
	// Private Routines
	//


	// STATIC
	// Open the package file with all the game resources in it ( must close with ClosePackageFile() )
	const bool ResourceUnpacker::OpenPackageFile(FileHandle& file, const char* const packagePath)
	{
		FileError errorCode = FileError::FILE_SUCCESS;
		errorCode = File::open(file, packagePath, FileMode::FILE_READ, true);
		if (errorCode != FileError::FILE_SUCCESS)
		{
			assert(errorCode == FileError::FILE_SUCCESS);
			return false;
		}
		return true;
	}


	// STATIC
	// Close the package file
	const bool ResourceUnpacker::ClosePackageFile(FileHandle& file)
	{
		FileError errorCode = File::close(file);
		if (errorCode != FileError::FILE_SUCCESS)
		{
			assert(errorCode != FileError::FILE_CLOSE_FAIL);
			return false;
		}
		return true;
	}


	// STATIC
	// Read the .lgepkg Package Header. Returns true if reading is successful
	const bool ResourceUnpacker::ReadPackageHeader(FileHandle& file, PackageHeader& pkgHdr)
	{
		FileError errorCode = File::read(file, &pkgHdr, sizeof(PackageHeader));
		if (errorCode != FileError::FILE_SUCCESS)
		{
			assert(errorCode != FileError::FILE_READ_FAIL);
			errorCode = File::close(file);
			assert(errorCode == FileError::FILE_SUCCESS);
			return false;
		}
		return true;
	}


	// STATIC
	// Find the package chunk holding the inqured dat given a chunk name and chunk type. Returns true if the chunk was found.
	const bool ResourceUnpacker::FindPackageChunk(FileHandle& file, PackageChunkHeader& chunkHdr, const int TotalChunks, const PackageChunkType InquiredType, const char* const InquredName)
	{
		// Search for the specified chunk in the file without loading the whole file
		bool chunkFound = false;
		for (int i = 0; i < TotalChunks; i++)
		{
			FileError errorCode = File::read(file, &chunkHdr, sizeof(PackageChunkHeader));
			if (errorCode != FileError::FILE_SUCCESS)
			{
				assert(errorCode != FileError::FILE_READ_FAIL);
				errorCode = File::close(file);
				assert(errorCode == FileError::FILE_SUCCESS);
				return false;
			}

			// Check if the chunk type is what we are looking for (faster check than name)
			if (InquiredType == chunkHdr.type)
			{
				// Now check if the name matches (slower check)
				if (!strncmp(InquredName, chunkHdr.chunkName, LGE_PKG_CHUNK_NAME_SIZE))
				{
					// Found it!
					chunkFound = true;
					break;
				}
			}

			// If you're here, the chunk wasn't found yet

			// Jump to the next chunk header
			errorCode = File::seek(file, FileSeek::FILE_SEEK_CURRENT, chunkHdr.chunkSize);
			if (errorCode != FileError::FILE_SUCCESS)
			{
				assert(errorCode != FileError::FILE_SEEK_FAIL);
				errorCode = File::close(file);
				assert(errorCode == FileError::FILE_SUCCESS);
				return false;
			}
		}

		return chunkFound;
	}


	// STATIC
	// Handle complicated logic behind deserializing animation data
	void ResourceUnpacker::DeserializeAnimationData(FileHandle& file, AnimationSet*& animationSet)
	{
		// Read the animation header
		AnimationHdr animHdr;
		FileError fileError = File::read(file, &animHdr, sizeof(AnimationHdr));
		assert(fileError != FileError::FILE_READ_FAIL);
		CString animSetName = std::move(animHdr.name.ToCString());


		// Read the skeleton hierarchy
		unsigned int* hierarchyData = new unsigned int[animHdr.numOfJoints];
		fileError = File::read(file, hierarchyData, sizeof(unsigned int) * animHdr.numOfJoints);
		assert(fileError != FileError::FILE_READ_FAIL);

		// Create the hierarchy table
		JointHierarchyTable* hierarchyTable = new JointHierarchyTable(animHdr.numOfJoints, hierarchyData);


		// Create and read the joint hierachy level table
		unsigned int* hierarchyLevels = new unsigned int[animHdr.numOfJoints];
		fileError = File::read(file, hierarchyLevels, sizeof(unsigned int) * animHdr.numOfJoints);
		assert(fileError != FileError::FILE_READ_FAIL);


		// Read the joint names
		Str64* jointNameData = new Str64[animHdr.numOfJoints];
		fileError = File::read(file, jointNameData, sizeof(Str64) * animHdr.numOfJoints);
		assert(fileError != FileError::FILE_READ_FAIL);
		
		// Convert Str64[] to CString[]
		CString* jointNameStrings = new CString[animHdr.numOfJoints];
		for (unsigned int i = 0; i < animHdr.numOfJoints; i++)
		{
			jointNameStrings[i] = std::move(jointNameData[i].ToCString());
		}
		delete[] jointNameData;
		jointNameData = nullptr;

		// Create the name table
		JointNameTable* nameTable = new JointNameTable(animHdr.numOfJoints, jointNameStrings);



		// Create the inverse bind pose table
		Matrix* invBindPoseTable = new Matrix[animHdr.numOfJoints];

		// Read the inverse bind poses
		fileError = File::read(file, invBindPoseTable, sizeof(Matrix) * animHdr.numOfJoints);



		// Send the three tables into a new skeleton
		AnimationSkeleton* newSkeleton = new AnimationSkeleton(animHdr.nameHash,
															   animHdr.numOfJoints,
															   hierarchyTable,
															   nameTable,
															   invBindPoseTable,
															   hierarchyLevels,
															   animSetName.GetString());
		animationSet->AddSkeletonOnce(newSkeleton);

		delete[] hierarchyLevels;

		
		// Now deserialize every animation clip in this set
		ClipHdr clipHdr;
		for (unsigned int i = 0; i < animHdr.numOfClips; i++)
		{
			// Read the clip header
			fileError = File::read(file, &clipHdr, sizeof(ClipHdr));
			assert(fileError != FileError::FILE_READ_FAIL);

			// Set clip metadata
			AnimationClipSetter clipSetter;
			clipSetter.SetMaxTime(clipHdr.maxTime);
			clipSetter.SetId(clipHdr.nameHash);
			clipSetter.SetLooping(clipHdr.DoesLoop());
			clipSetter.SetName( std::move( clipHdr.name.ToCString() ) );

			// Allocate memory for all the keyframes
			KeyFrame* const keyframes = new KeyFrame[clipHdr.numKeyFrames];
			clipSetter.SetKeyframes(clipHdr.numKeyFrames, keyframes);

			// Extract every keyframe of the i'th clip
			for (unsigned int k = 0; k < clipHdr.numKeyFrames; k++)
			{
				// Get the keyframe's time
				TimeUnit frameTime;
				fileError = File::read(file, &frameTime, sizeof(TimeUnit));
				assert(fileError != FileError::FILE_READ_FAIL);

				// Allocate and read all the joints of the k'th keyframe
				AnimationJoint* keyframeJoints = new AnimationJoint[animHdr.numOfJoints];
				fileError = File::read(file, keyframeJoints, sizeof(AnimationJoint) * animHdr.numOfJoints);
				assert(fileError != FileError::FILE_READ_FAIL);

				// Get the keyframe data into the k'th index of the keyframe array
				KeyFrame currentKeyframe(frameTime, keyframeJoints, animHdr.numOfJoints);
				keyframes[k] = std::move(currentKeyframe);
			}

			// Finally create an AnimationClip and add it to the set
			AnimationClip* clip = new AnimationClip(&clipSetter);
			animationSet->AddClip(clip);
		}

	}




}