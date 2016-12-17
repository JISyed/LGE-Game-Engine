#include "Screen.h"
#include <cassert>

namespace lge
{
	//
	// Static Data
	//

	Screen* Screen::singletonInstance = nullptr;



	//
	// Mehtods
	//


	Screen::Screen(const int newWidth, const int newHeight) :
		width(newWidth),
		height(newHeight),
		aspectRatio((float)newWidth / (float)newHeight)
	{
		assert(Screen::singletonInstance == nullptr);
		Screen::singletonInstance = this;
	}

	Screen::~Screen()
	{
		assert(Screen::singletonInstance != nullptr);
		Screen::singletonInstance = nullptr;
	}




	// Only the Game class should call this method
	void Screen::SetWidthAndHeight(const int w, const int h)
	{
		this->width = w;
		this->height = h;
		this->aspectRatio = (float)w / (float)h;
	}



	// STATIC
	const int Screen::GetWidth()
	{
		return Screen::singletonInstance->width;
	}

	// STATIC
	const int Screen::GetHeight()
	{
		return Screen::singletonInstance->height;
	}

	// STATIC
	const float Screen::GetAspectRatio()
	{
		return Screen::singletonInstance->aspectRatio;
	}

}