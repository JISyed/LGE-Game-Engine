#include "Time.h"
#include "GL\glfw.h"
#include <cassert>

namespace lge
{
	//
	// Static data
	//

	static const TimeUnit ONE_SECOND(DurationBasis::OneSecond);
	Time* Time::singletonInstance = nullptr;
	

	//
	// Methods
	//

	Time::Time() :
		//previousTime(0.0f),
		deltaTime(DurationBasis::Ntsc60Frame),
		frameTimer(),
		startupTimer()
	{
		// Singeton must not exist yet
		assert(Time::singletonInstance == nullptr);
		Time::singletonInstance = this;

		frameTimer.tic();
		startupTimer.tic();
	}

	Time::~Time()
	{
		assert(Time::singletonInstance != nullptr);
		Time::singletonInstance = nullptr;
	}



	// Only to be called by Engine class!
	void Time::Update()
	{
		// Get current delta time
		this->deltaTime = this->frameTimer.toc();
		
		// Reset frame timer
		this->frameTimer.tic();
	}




	// STATIC
	// Get the time since the game started
	const float Time::GetTimeFromStartInSeconds()
	{
		return Time::singletonInstance->startupTimer.toc() / ONE_SECOND;
	}


	// STATIC
	// Get the time between frames
	const float Time::GetDeltaTimeInSeconds()
	{
		return Time::singletonInstance->deltaTime / ONE_SECOND;
	}


	// STATIC
	// Get the time since the game started
	const TimeUnit Time::GetTimeFromStart()
	{
		return Time::singletonInstance->startupTimer.toc();
	}

	// STATIC
	// Get the time between frames
	const TimeUnit Time::GetDeltaTime()
	{
		return Time::singletonInstance->deltaTime;
	}




}