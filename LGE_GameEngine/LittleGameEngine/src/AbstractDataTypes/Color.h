#ifndef LGE_COLOR_FLOAT_H
#define LGE_COLOR_FLOAT_H

namespace lge
{
	// Represents normalized color values in the RBGA format
	class Color
	{
	public:

		//
		// Big Four
		//

		Color();
		Color(float red, float green, float blue, float alpha = 1.0f);
		Color(const Color& rhs);
		~Color();
		Color& operator=(const Color& rhs);


		//
		// Getters
		//

		// Get the red value
		const float r() const;
		// Get the green value
		const float g() const;
		// Get the blue value
		const float b() const;
		// Get the alpha value
		const float a() const;

		// Get raw color data starting at red. Used with OpenGL calls
		const float* const GetRawData() const;


		//
		// Setters
		//

		// Set the red value
		void SetRed(const float red);
		// Set the green value
		void SetGreen(const float green);
		// Set the blue value
		void SetBlue(const float blue);
		// Set the alpha value
		void SetAlpha(const float alpha);


	private:

		//
		// Data
		//

		float _r;
		float _g;
		float _b;
		float _a;



		//
		// Deleted Methods
		//

		// No move ctor
		Color(Color&& other) = delete;

		// No move assignment
		Color& operator=(Color&& other) = delete;
	};
}
#endif