#ifndef THE_GAME_H
#define THE_GAME_H

#include "Engine.h"
#include "..\GraphicsSystem\CameraController.h"

namespace lge
{
	//
	// Forward Delcares
	//

	namespace Input
	{
		class Keyboard;
		class Mouse;
	}

	class GameObjectManager;
	class CameraManager;
	class ShaderRegistry;
	class TextureRegistry;
	class MeshRegistry;
	class MaterialRegistry;
	class AnimationSetRegistry;


	///////////////////////////////////////////
	//   Game Class
	///////////////////////////////////////////

	// The game application that actually runs your game
	class Game final : public Engine
	{
	public:

		//
		// Ctor / Dtor
		//

		// Constuctor
		Game(const char* const newWindowName, const int newWidth, const int newHeight);

		// Destructor
		virtual ~Game();




		//
		// App Lifetime Methods
		//

		// Construct nessesary system objects for the game
		virtual void Initialize() override;

		// Create objects for external resources used in the game
		virtual void LoadContent() override;

		// The logic loop of the game that is called multiple times per second
		virtual void Update() override;

		// The draw loop of the game that is called multiple times per second
		virtual void Draw() override;

		// Unload objects and resources used by the game
		virtual void Shutdown() override;



		//
		// Event Methods
		//

		// Called when the game window is resized
		virtual void onResize(const int w, const int h) override;


	private:

		//
		// Data
		//

		Input::Keyboard*		keyboard;
		Input::Mouse*			mouse;
		GameObjectManager*		gameObjectManager;
		CameraManager*			cameraManager;
		ShaderRegistry*			shaderRegistry;
		TextureRegistry*		textureRegistry;
		MeshRegistry*			meshRegistry;
		MaterialRegistry*		materialRegistry;
		AnimationSetRegistry*	animSetRegistry;
		CameraController		camCtrlr;


		//
		// Deleted Methods
		//

		// No default ctor allowed
		Game() = delete;

		// No Copy ctor allowed
		Game(const Game& other) = delete;

		// No assignment overload allowed (pointers don't count)
		Game& operator=(const Game& other) = delete;

		// No move ctor
		Game(Game&& other) = delete;

		// No move assignment
		Game& operator=(Game&& other) = delete;
	};

}

#endif