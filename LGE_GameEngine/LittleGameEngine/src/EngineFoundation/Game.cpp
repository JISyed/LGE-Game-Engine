#include "Game.h"
#include <cassert>

#include "..\AbstractDataTypes\CString.h"
#include "..\InputSystem\Keyboard.h"
#include "..\InputSystem\Mouse.h"
#include "..\GraphicsSystem\Camera.h"
#include "..\GraphicsSystem\CameraManager.h"
#include "..\GraphicsSystem\ShaderRegistry.h"
#include "..\GraphicsSystem\TextureRegistry.h"
#include "..\GraphicsSystem\MeshRegistry.h"
#include "..\GraphicsSystem\MaterialRegistry.h"
#include "..\GameObjectSystem\GameObjectManager.h"
#include "..\AnimationSystem\AnimationSetRegistry.h"


namespace lge
{
	//
	// Ctor/ Dtor
	//

	// Constructor
	Game::Game(const char* const newWindowName, const int newWidth, const int newHeight) : 
		Engine(newWindowName, newWidth, newHeight),
		camCtrlr()
	{
		this->cameraManager = new CameraManager();
		this->shaderRegistry = new ShaderRegistry();
		this->textureRegistry = new TextureRegistry();
		this->meshRegistry = new MeshRegistry();
		this->materialRegistry = new MaterialRegistry();
		this->animSetRegistry = new AnimationSetRegistry();

		// Change clear color
		//Engine::SetClearColor(Color(0.4f, 0.4f, 0.4f));
	}

	// VIRTUAL
	// Destructor
	Game::~Game()
	{
		delete this->animSetRegistry;
		delete this->materialRegistry;
		delete this->meshRegistry;
		delete this->textureRegistry;
		delete this->shaderRegistry;
		delete this->cameraManager;
	}



	//
	// App Lifetime Methods
	//

	// VIRTUAL
	// Construct nessesary system objects for the game
	void Game::Initialize()
	{
		this->keyboard = new Input::Keyboard();
		this->mouse = new Input::Mouse();
		this->camCtrlr.Init();
	}

	// VIRTUAL
	// Create objects for external resources used in the game
	void Game::LoadContent()
	{
		this->shaderRegistry->Load();
		this->textureRegistry->Load();
		this->meshRegistry->Load();
		this->materialRegistry->Load();
		this->cameraManager->Load();
		this->animSetRegistry->Load();

		// Create the GameObjectManager & create all the GameObjects needed at the moment
		this->gameObjectManager = new GameObjectManager();
		this->gameObjectManager->Load();
	}


	// VIRTUAL
	// The logic loop of the game that is called multiple times per second
	void Game::Update()
	{
		/*
		*   Controls:
		*
		*   1 = Play   
		*   2 = Pause
		*   3 = Stop
		*   
		*   6 = Normal Speed
		*   7 = Fast Speed
		*
		*   0 = Change Animation Clips
		*
		*/

		/////////////////////////////////////////////
		// Temporary code only for the animation demo

		static GameObject* teddyGameObj = GameObjectManager::Find("teddy");
		static GameObject* humanGameObj = GameObjectManager::Find("humanoid");
		static GameObject* teddyGameObj2 = GameObjectManager::Find("teddy2");
		static GameObject* humanGameObj2 = GameObjectManager::Find("humanoid2");
		static const char* const teddyClipNames[3] = {"idle", "walk", "Take 003"};
		static const char* const humanClipNames[3] = {"punch", "run", "shot"};
		static const char* const teddyClipNames2[3] = {"idle_compressed", "walk_compressed", "Take 003_compressed"};
		static const char* const humanClipNames2[3] = {"punch_compressed", "run_compressed", "shot_compressed"};
		static unsigned int clipIndex = 0;


		if (Input::Keyboard::GetKeyDown(Input::Key::Number1))
		{
			teddyGameObj->GetAnimationController()->Play();
			humanGameObj->GetAnimationController()->Play();

			teddyGameObj2->GetAnimationController()->Play();
			humanGameObj2->GetAnimationController()->Play();
		}
		else if (Input::Keyboard::GetKeyDown(Input::Key::Number2))
		{
			teddyGameObj->GetAnimationController()->Pause();
			humanGameObj->GetAnimationController()->Pause();

			teddyGameObj2->GetAnimationController()->Pause();
			humanGameObj2->GetAnimationController()->Pause();
		}
		else if (Input::Keyboard::GetKeyDown(Input::Key::Number3))
		{
			teddyGameObj->GetAnimationController()->Stop();
			humanGameObj->GetAnimationController()->Stop();

			teddyGameObj2->GetAnimationController()->Stop();
			humanGameObj2->GetAnimationController()->Stop();
		}

		if (Input::Keyboard::GetKeyDown(Input::Key::Number6))
		{
			teddyGameObj->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(1.0f);
			humanGameObj->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(1.0f);

			teddyGameObj2->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(1.0f);
			humanGameObj2->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(1.0f);
		}
		else if (Input::Keyboard::GetKeyDown(Input::Key::Number7))
		{
			teddyGameObj->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(4.0f);
			humanGameObj->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(4.0f);

			teddyGameObj2->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(4.0f);
			humanGameObj2->GetAnimationController()->GetCurrentPlayback()->SetPlaybackSpeedScale(4.0f);
		}

		if (Input::Keyboard::GetKeyDown(Input::Key::Number0))
		{
			clipIndex++;

			teddyGameObj->GetAnimationController()->SetCurrentPlayback(teddyClipNames[clipIndex % 3]);
			humanGameObj->GetAnimationController()->SetCurrentPlayback(humanClipNames[clipIndex % 3]);

			teddyGameObj2->GetAnimationController()->SetCurrentPlayback(teddyClipNames2[clipIndex % 3]);
			humanGameObj2->GetAnimationController()->SetCurrentPlayback(humanClipNames2[clipIndex % 3]);
		}


		// END ANIMATION DEMO ALTERATIONS
		/////////////////////////////////////////////


		// Camera Controls (not Manager)
		this->camCtrlr.Update();

		this->gameObjectManager->Update();

		this->cameraManager->Update();

		this->keyboard->UpdateStates();
		this->mouse->UpdateStates();
	}


	// VIRTUAL
	// The draw loop of the game that is called multiple times per second
	void Game::Draw()
	{
		this->gameObjectManager->Draw();
		this->cameraManager->DrawCameraGizmos();
	}


	// VIRTUAL
	// Unload objects and resources used by the game
	void Game::Shutdown()
	{
		this->gameObjectManager->Unload();
		delete this->gameObjectManager;

		this->animSetRegistry->Unload();
		this->materialRegistry->Unload();
		this->meshRegistry->Unload();
		this->textureRegistry->Unload();
		this->shaderRegistry->Unload();

		this->cameraManager->Unload();

		delete this->keyboard;
		delete this->mouse;
	}



	//
	// Event Methods
	//

	// VIRTUAL
	// Called when the game window is resized
	void Game::onResize(const int w, const int h)
	{
		// Super method
		Engine::onResize(w, h);

		this->cameraManager->SetAllProjections(50.0f, Screen::GetAspectRatio(), 0.1f, 2000.0f);
	}





}