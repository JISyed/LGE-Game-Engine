#ifndef ENGINE_MATH_VECT_H
#define ENGINE_MATH_VECT_H

// Includes to handle SIMD register types
#include <xmmintrin.h>
#include <smmintrin.h> 
#include "Constants.h"
#include "Align16.h"
#include "Enum.h"


namespace lge
{
	// forward declare
	class Matrix;


	// Row-major 4 element Vector
	class Vect final : public Align16
	{
	public:


		//
		// Big Four
		//

		// Default Ctor (0,0,0,1)
		explicit Vect();

		// Destructor
		~Vect();

		// Copy Ctor
		Vect(const Vect& rhs);

		// Assignment Overload
		Vect& operator=(const Vect& rhs);




		//
		// Other Constructors
		//

		// Multi-float Ctor
		Vect(const float x, const float y, const float z, const float w = 1.0f);

		// Ctor for setting all elements to the same value
		explicit Vect(const float xyzw);

		// Ctor for __m128
		explicit Vect(const __m128 m);



		//
		// Getters
		//


		// Square bracket getter
		const float operator[](const x_enum x) const;
		// Square bracket getter
		const float operator[](const y_enum y) const;
		// Square bracket getter
		const float operator[](const z_enum z) const;
		// Square bracket getter
		const float operator[](const w_enum w) const;


		// Function-based getter for x
		const float x() const;
		// Function-based getter for y
		const float y() const;
		// Function-based getter for z
		const float z() const;
		// Function-based getter for w
		const float w() const;




		//
		// Setters
		//

		// Square bracker setter
		float& operator[](const x_enum x);
		// Square bracker setter
		float& operator[](const y_enum y);
		// Square bracker setter
		float& operator[](const z_enum z);
		// Square bracker setter
		float& operator[](const w_enum w);


		// Function-based setter for x
		float& x();
		// Function-based setter for y
		float& y();
		// Function-based setter for z
		float& z();
		// Function-based setter for w
		float& w();


		// Multi-float setter
		void set(const float x, const float y, const float z, const float w = 1.0f);

		// Vector based setter
		void set(const Vect& other);





		//
		// Vector exclusive operations
		//


		// Dot product
		const float dot(const Vect& rhs) const;

		// Cross product
		const Vect cross(const Vect& rhs) const;

		// Normalize yourself
		void norm();

		// Get a normalized version of this vector
		const Vect getNorm() const;

		// Get the absolute length of the vector
		const float mag() const;

		// Get the squared-length of the vector (faster than Vect::mag())
		const float magSqr() const;

		// Get the angle (in radians) between this vector and the rhs vector
		const float getAngle(const Vect& rhs) const;



		//
		// Vector comparison
		//

		// Is this vector equal to the other?
		const bool isEqual(const Vect& other, const float floatTolerance = MATH_TOLERANCE) const;

		// Is this vector a Zero vector?
		const bool isZero(const float floatTolerance = MATH_TOLERANCE) const;



		//
		// Unary operators
		//

		// Unary + operator overload
		const Vect operator+() const;

		// Unary - operator overload
		const Vect operator-() const;




		//
		// Vector addition
		//

		// Add two vectors together
		const Vect operator+(const Vect& rhs) const;

		// Add two vectors together
		Vect& operator+=(const Vect& rhs);




		//
		// Vector subtraction
		//

		// Subtract two vectors together
		const Vect operator-(const Vect& rhs) const;

		// Subtract two vectors together
		Vect& operator-=(const Vect& rhs);




		//
		// Scalar multiplication
		//

		// Scalar multiplication
		const Vect operator*(const float scalarRhs) const;

		// Scalar multiplication
		Vect& operator*=(const float scalarRhs);

		// Scalar multiplication
		friend const Vect operator*(const float scalarLhs, const Vect& vectRhs);


		//
		// Scalar division
		//

		// Scalar division
		const Vect operator/(const float scalarRhs) const;

		// Scalar division
		Vect& operator/=(const float scalarRhs);




		//
		// __m128 Accessors
		//

		// Get the __m128 member
		const __m128 getM() const;

		// Setter for the __m128 member
		__m128& getMRef();

		// Ref getter for __m128 member
		const __m128& getConstM() const;




		//
		// Matrix multiplication (v*M)
		//

		// Vect by Matrix multiplication
		const Vect operator*(const Matrix& matRhs) const;

		// Vect by Matrix multiplication
		Vect& operator*=(const Matrix& matRhs);




		//
		// Full Vector Scaling
		//

		// Scale every element of the vector, even W
		const Vect getScaled(const float scalar) const;

		// Scale every element of the vector, even W
		Vect& scale(const float scalar);



		//
		// Full Vector Addition
		// 

		// Add every element of one vector upon another, even W
		const Vect add(const Vect& other) const;

		// Add every element of one vector upon another, even W
		Vect& increment(const Vect& other);





	private:

		//
		// Data
		//

		// Level 4 complains nameless struct/union ...
		#pragma warning( disable : 4201)
		// anonymous union
		union
		{
			__m128	_m;

			// anonymous struct
			struct
			{
				float _x;
				float _y;
				float _z;
				float _w;
			};
		};

	};	// end of Vect
}
#endif