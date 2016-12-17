#ifndef LGE_SCREEN_H
#define LGE_SCREEN_H

namespace lge
{
	// Stores properties of the game's screen (window)
	class Screen
	{
	public:

		//
		// Ctor / Dtor
		//

		// Only the Engine class should call this constructor
		Screen(const int newWidth, const int newHeight);
		~Screen();


		//
		// Methods
		//

		// Only the Engine class should call this method
		void SetWidthAndHeight(const int w, const int h);



		//
		// Static Methods (for use by anyone)
		//

		// Get current width of the screen in pixels
		static const int GetWidth();

		// Get current height of the screen in pixels
		static const int GetHeight();

		// Get the screen's current aspect ratio
		static const float GetAspectRatio();


	private:

		//
		// Data
		//

		int width;
		int height;
		float aspectRatio;


		
		//
		// Static Data
		//

		static Screen* singletonInstance;


		
		//
		// Deleted Methods
		//

		// No copy ctor
		Screen(const Screen& other) = delete;
		
		// No copy assignment
		Screen& operator=(const Screen& other) = delete;

		// No default ctor
		Screen() = delete;

		// No move ctor
		Screen(Screen&& other) = delete;

		// No move assignment
		Screen& operator=(Screen&& other) = delete;
	};

	
}

#endif