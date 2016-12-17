#include "Color.h"

namespace lge
{
	Color::Color() :
		_r(0.0f),
		_g(0.0f),
		_b(0.0f),
		_a(1.0f)
	{
	}


	Color::Color(float red, float green, float blue, float alpha) :
		_r(red),
		_g(green),
		_b(blue),
		_a(alpha)
	{
	}


	Color::Color(const Color& rhs) :
		_r(rhs._r),
		_g(rhs._g),
		_b(rhs._b),
		_a(rhs._a)
	{
	}


	Color::~Color()
	{
	}


	Color& Color::operator=(const Color& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->_r = rhs._r;
		this->_g = rhs._g;
		this->_b = rhs._b;
		this->_a = rhs._a;

		return *this;
	}






	const float Color::r() const
	{
		return this->_r;
	}

	const float Color::g() const
	{
		return this->_g;
	}

	const float Color::b() const
	{
		return this->_b;
	}

	const float Color::a() const
	{
		return this->_a;
	}







	void Color::SetRed(const float red)
	{
		this->_r = red;
	}

	void Color::SetGreen(const float green)
	{
		this->_g = green;
	}

	void Color::SetBlue(const float blue)
	{
		this->_b = blue;
	}

	void Color::SetAlpha(const float alpha)
	{
		this->_a = alpha;
	}






	const float* const Color::GetRawData() const
	{
		return (float*) this;
	}
}