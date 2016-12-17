#ifndef LGE_MATERIAL_H
#define LGE_MATERIAL_H

#include "MathEngine.h"
#include "PolygonMode.h"
#include "..\EngineUtilities\IdGenerator.h"
#include "..\AbstractDataTypes\GenericList.h"
#include "MaterialUniform.h"
#include "MaterialTextureLink.h"


namespace lge
{
	// Forward declare
	class Shader;


	// TEMP: Need a better way to name Materials
	enum class MaterialName : unsigned int
	{
		// For lack of better names
		Material1,
		Material2,
		Material3,
		Material4,
		Material5,
		SpaceFrigate,
		Astroboy,
		Buggy,
		WarbearBrown,
		WarbearPolar,
		Default,
		CameraOrbitTarget,
		BoundingSphereInside,
		BoundingSphereOutside,
		SkinnedTextureDiffuseBear,
		SkinnedTextureDiffueseHumanoid
	};


	// Represents a usable collection of rendering properties that can be applied onto any mesh.
	// Will compose of a shader that could have textures and/or uniforms
	class Material
	{
	public:

		//
		// Ctor / Dtor
		//

		Material(Shader* const shader, const PolygonModeType polygonMode, MaterialName newName);
		~Material();


		//
		// Methods
		//

		// Makes this Material the active material. Also makes its Shader active.
		void MakeActive();

		// Sets the polygon render state for OpenGL
		void SetPolygonRenderState();

		// Restores the polygon render state for OpenGL
		void RestorePolygonRenderState();



		//
		// Setters
		//

		// Change into a different polygon mode given a type
		void ChangePolygonMode(const PolygonModeType newPolygonMode);

		// Set a uniform in this Material (that's a Matrix)
		bool SetUniform(UniformName uniformName, const Matrix& newValue);
		// Set a uniform in this Material (that's a Vect)
		bool SetUniform(UniformName uniformName, const Vect& newValue);
		// Set a uniform in this Material (that's a float)
		bool SetUniform(UniformName uniformName, float newValue);
		// Set a uniform in this Material (that's an int)
		bool SetUniform(UniformName uniformName, int newValue);
		// Set a uniform in this Material (that's a TextureUnit)
		bool SetUniform(UniformName uniformName, TextureUnit newValue);
		// Set a uniform in this Material (that's a Matrix array) (must be 100 matrices)
		bool SetUniform(UniformName uniformName, const Matrix* const newValueArray);


		// Set a texture in the Material (can have support multiple textures if the TextureMapType is different)
		bool SetTexture(Texture* const texture);



		//
		// Getters
		//

		// Get the ID of this material
		const unsigned int GetId() const;

		// Set the shader (better know what you're doing)
		Shader* const GetShader() const;



	private:

		//
		// Data
		//

		Shader* targetShader;
		PolygonMode* polygonRenderingMode;
		GenericList<MaterialUniform> uniformList;
		GenericList<MaterialTextureLink> textureList;
		MaterialName name;



		//
		// Static Data
		//

		static IdGenerator s_idGen;





		//
		// Private Routines
		//

		// Make the shader the only active shader, without making every other aspect of this Material active
		void ActivateOnlyShader();





		//
		// Deleted Methods
		//

		// No default ctor
		Material() = delete;

		// No copy ctor
		Material(const Material& other) = delete;

		// No copy assignment
		Material& operator=(const Material& other) = delete;

		// No move ctor
		Material(Material&& other) = delete;

		// No move assignment
		Material& operator=(Material&& other) = delete;
	};
}
#endif