#ifndef LGE_TIME_H
#define LGE_TIME_H
#include "..\TimeSystem\TimeUnit.h"
#include "..\TimeSystem\Timer.h"

namespace lge
{
	// Keeps track of time data for the engine
	class Time
	{
	public:

		//
		// Ctor / Dtor
		//

		Time();
		~Time();



		//
		// Methods
		//

		// Only to be called by Engine class!
		void Update();


		//
		// Static Methods
		//

		// Get the time since the game started (in seconds)
		static const float GetTimeFromStartInSeconds();

		// Get the time between frames (in seconds)
		static const float GetDeltaTimeInSeconds();

		// Get the time since the game started
		static const TimeUnit GetTimeFromStart();

		// Get the time between frames
		static const TimeUnit GetDeltaTime();


	private:

		//
		// Data
		//

		TimeUnit deltaTime;		// The time between frames
		Timer frameTimer;		// The timer for a frame's duration
		Timer startupTimer;		// The timer for the program's duration



		//
		// Static Data
		//

		static Time* singletonInstance;


		//
		// Deleted Methods
		//

		// No Copy ctor
		Time(const Time& other) = delete;

		// No copy assignment
		Time& operator=(const Time& other) = delete;

		// No move ctor
		Time(Time&& other) = delete;

		// No move assignment
		Time& operator=(Time&& other) = delete;
	};

}

#endif