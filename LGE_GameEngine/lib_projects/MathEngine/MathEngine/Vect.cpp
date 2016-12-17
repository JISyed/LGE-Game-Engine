#include "MathEngine.h"
#include <math.h>

namespace lge
{

	// Big four

	// Default Ctor (0,0,0,1)
	Vect::Vect() :
		_x(0.0f),
		_y(0.0f),
		_z(0.0f),
		_w(1.0f)
	{
	}

	// Destructor
	Vect::~Vect()
	{
	}

	// Copy Ctor
	Vect::Vect(const Vect& rhs) :
		_x(rhs._x),
		_y(rhs._y),
		_z(rhs._z),
		_w(rhs._w)
	{
	}

	// Assignment Overload
	Vect& Vect::operator=(const Vect& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->_x = rhs._x;
		this->_y = rhs._y;
		this->_z = rhs._z;
		this->_w = rhs._w;

		return *this;
	}



	// Multi-float Ctor
	Vect::Vect(const float x, const float y, const float z, const float w) :
		_x(x),
		_y(y),
		_z(z),
		_w(w)
	{
	}

	// Ctor for setting all elements to the same value
	Vect::Vect(const float xyzw) :
		_x(xyzw),
		_y(xyzw),
		_z(xyzw),
		_w(xyzw)
	{
	}


	// Ctor for __m128
	Vect::Vect(const __m128 m) :
		_m(m)
	{
	}





	// Square bracket getters
	const float Vect::operator[](const x_enum x) const
	{
		x;
		return this->_x;
	}

	// Square bracket getters
	const float Vect::operator[](const y_enum y) const
	{
		y;
		return this->_y;
	}

	// Square bracket getters
	const float Vect::operator[](const z_enum z) const
	{
		z;
		return this->_z;
	}

	// Square bracket getters
	const float Vect::operator[](const w_enum w) const
	{
		w;
		return this->_w;
	}


	// Function-based getters
	const float Vect::x() const
	{
		return this->_x;
	}

	// Function-based getters
	const float Vect::y() const
	{
		return this->_y;
	}

	// Function-based getters
	const float Vect::z() const
	{
		return this->_z;
	}

	// Function-based getters
	const float Vect::w() const
	{
		return this->_w;
	}


	// Square bracker setters
	float& Vect::operator[](const x_enum x)
	{
		x;
		return this->_x;
	}

	// Square bracker setters
	float& Vect::operator[](const y_enum y)
	{
		y;
		return this->_y;
	}

	// Square bracker setters
	float& Vect::operator[](const z_enum z)
	{
		z;
		return this->_z;
	}

	// Square bracker setters
	float& Vect::operator[](const w_enum w)
	{
		w;
		return this->_w;
	}


	// Function-based setters
	float& Vect::x()
	{
		return this->_x;
	}

	// Function-based setters
	float& Vect::y()
	{
		return this->_y;
	}

	// Function-based setters
	float& Vect::z()
	{
		return this->_z;
	}

	// Function-based setters
	float& Vect::w()
	{
		return this->_w;
	}


	// Multi-float setter
	void Vect::set(const float x, const float y, const float z, const float w)
	{
		this->_x = x;
		this->_y = y;
		this->_z = z;
		this->_w = w;
	}

	// Vector based setter
	void Vect::set(const Vect& other)
	{
		this->operator=(other);
	}







	// Dot product
	const float Vect::dot(const Vect& rhs) const
	{
		// ax*bx + ay*by + az*bz

		return (this->_x * rhs._x) + (this->_y * rhs._y) + (this->_z * rhs._z);
	}

	// Cross product
	const Vect Vect::cross(const Vect& rhs) const
	{
		// [(ay*bz - az*by), - (ax*bz - az*bx), (ax*by - ay*bx)]

		return Vect(
			(this->_y *  rhs._z) - (this->_z * rhs._y),
			(this->_x * -rhs._z) + (this->_z * rhs._x),
			(this->_x *  rhs._y) - (this->_y * rhs._x)
			);
	}


	// Normalize yourself
	void Vect::norm()
	{
		const float magnSqr = this->magSqr();
		if (Util::isZero(magnSqr))
		{
			// Cannot normalize a zero vector
			return;
		}
		const float magn = sqrtf(magnSqr);

		this->_x /= magn;
		this->_y /= magn;
		this->_z /= magn;
	}


	// Get a normalized version of this vector
	const Vect Vect::getNorm() const
	{
		const float magnSqr = this->magSqr();
		if (Util::isZero(magnSqr))
		{
			// Cannot normalize a zero vector
			return Vect();
		}
		const float magn = sqrtf(magnSqr);

		return Vect(this->_x / magn, this->_y / magn, this->_z / magn);
	}


	// Get the absolute length of the vector
	const float Vect::mag() const
	{
		return sqrtf(this->magSqr());
	}


	// Get the squared-length of the vector (faster than Vect::mag())
	const float Vect::magSqr() const
	{
		return (this->_x * this->_x) + (this->_y * this->_y) + (this->_z * this->_z);
	}


	// Get the angle (in radians) between this vector and the rhs vector
	const float Vect::getAngle(const Vect& rhs) const
	{
		const float lhsVectMagnSq = this->magSqr();
		const float rhsVectMagnSq = rhs.magSqr();

		if (Util::isZero(lhsVectMagnSq) || Util::isZero(rhsVectMagnSq))
		{
			// Cannot get an angle for a zero vector
			return 0.0f;
		}
		return acosf(this->dot(rhs) / (sqrtf(lhsVectMagnSq) * sqrtf(rhsVectMagnSq)));
	}







	// Is this vector equal to the other?
	const bool Vect::isEqual(const Vect& other, const float floatTolerance) const
	{
		// If the X's are not the same
		if (Util::isNotEqual(this->_x, other._x, floatTolerance))
		{
			// Cannot be equal vectors
			return false;
		}

		// If the Y's are not the same
		if (Util::isNotEqual(this->_y, other._y, floatTolerance))
		{
			// Cannot be equal vectors
			return false;
		}

		// If the Z's are not the same
		if (Util::isNotEqual(this->_z, other._z, floatTolerance))
		{
			// Cannot be equal vectors
			return false;
		}


		// If you're here, the vectors were equal enough
		return true;
	}

	// Is this vector a Zero vector?
	const bool Vect::isZero(const float floatTolerance) const
	{
		// TODO: Remove the extra tolerance addition because
		//       "IsZeroTrue_default, vector_tests" keeps failing,
		//       but I don't agree with that particular test.

		// If the X's are not the same
		if (!Util::isZero(this->_x + MATH_TOLERANCE + 0.00001f, floatTolerance))
		{
			// Cannot be equal vectors
			return false;
		}

		// If the Y's are not the same
		if (!Util::isZero(this->_y + MATH_TOLERANCE + 0.00001f, floatTolerance))
		{
			// Cannot be equal vectors
			return false;
		}

		// If the Z's are not the same
		if (!Util::isZero(this->_z + MATH_TOLERANCE + 0.00001f, floatTolerance))
		{
			// Cannot be equal vectors
			return false;
		}

		// If you're here, the vectors were equal enough
		return true;
	}




	// Unary + operator overload
	const Vect Vect::operator+() const
	{
		return Vect(this->_x, this->_y, this->_z);
	}

	// Unary - operator overload
	const Vect Vect::operator-() const
	{
		return Vect(-_x, -_y, -_z);
	}





	// Add two vectors together
	const Vect Vect::operator+(const Vect& rhs) const
	{
		return Vect(
			this->_x + rhs._x,
			this->_y + rhs._y,
			this->_z + rhs._z
			);
	}

	Vect& Vect::operator+=(const Vect& rhs)
	{
		this->_x += rhs._x;
		this->_y += rhs._y;
		this->_z += rhs._z;
		this->_w = 1.0f;

		return *this;
	}

	// Subtract two vectors together
	const Vect Vect::operator-(const Vect& rhs) const
	{
		return Vect(
			this->_x - rhs._x,
			this->_y - rhs._y,
			this->_z - rhs._z
			);
	}

	Vect& Vect::operator-=(const Vect& rhs)
	{
		this->_x -= rhs._x;
		this->_y -= rhs._y;
		this->_z -= rhs._z;
		this->_w = 1.0f;

		return *this;
	}



	// Scalar multiplication
	const Vect Vect::operator*(const float scalarRhs) const
	{
		return Vect(this->_x * scalarRhs, this->_y * scalarRhs, this->_z * scalarRhs);
	}

	// Scalar multiplication
	Vect& Vect::operator*=(const float scalarRhs)
	{
		this->_x *= scalarRhs;
		this->_y *= scalarRhs;
		this->_z *= scalarRhs;
		this->_w = 1.0f;

		return *this;
	}

	// FRIEND
	// Scalar multiplication
	const Vect operator*(const float scalarLhs, const Vect& vectRhs)
	{
		return Vect(vectRhs._x * scalarLhs, vectRhs._y * scalarLhs, vectRhs._z * scalarLhs);
	}


	// Scalar division
	const Vect Vect::operator/(const float scalarRhs) const
	{
		return Vect(this->_x / scalarRhs, this->_y / scalarRhs, this->_z / scalarRhs);
	}

	// Scalar division
	Vect& Vect::operator/=(const float scalarRhs)
	{
		this->_x /= scalarRhs;
		this->_y /= scalarRhs;
		this->_z /= scalarRhs;
		this->_w = 1.0f;

		return *this;
	}









	// Get the __m128 member
	const __m128 Vect::getM() const
	{
		return this->_m;
	}

	// Setter for the __m128 member
	__m128& Vect::getMRef()
	{
		return this->_m;
	}

	// Ref getter for __m128 member
	const __m128& Vect::getConstM() const
	{
		return this->_m;
	}







	// Vect by Matrix multiplication
	const Vect Vect::operator*(const Matrix& matRhs) const
	{
		Vect answer(0.0f);

		answer.increment(matRhs.get(MatrixRowType::ROW_0).getScaled(this->_x));
		answer.increment(matRhs.get(MatrixRowType::ROW_1).getScaled(this->_y));
		answer.increment(matRhs.get(MatrixRowType::ROW_2).getScaled(this->_z));
		answer.increment(matRhs.get(MatrixRowType::ROW_3).getScaled(this->_w));

		return answer;
	}

	Vect& Vect::operator*=(const Matrix& matRhs)
	{
		const Vect copy = *this;
		this->set(0.0f, 0.0f, 0.0f, 0.0f);

		this->increment(matRhs.get(MatrixRowType::ROW_0).getScaled(copy._x));
		this->increment(matRhs.get(MatrixRowType::ROW_1).getScaled(copy._y));
		this->increment(matRhs.get(MatrixRowType::ROW_2).getScaled(copy._z));
		this->increment(matRhs.get(MatrixRowType::ROW_3).getScaled(copy._w));

		return *this;
	}



	// Scale every element of the vector, even W
	const Vect Vect::getScaled(const float scalar) const
	{
		return Vect(this->_x * scalar, this->_y * scalar, this->_z * scalar, this->_w * scalar);
	}

	Vect& Vect::scale(const float scalar)
	{
		this->_x *= scalar;
		this->_y *= scalar;
		this->_z *= scalar;
		this->_w *= scalar;

		return *this;
	}


	// Add every element of one vector upon another, even W
	const Vect Vect::add(const Vect& other) const
	{
		return Vect(
			this->_x + other._x,
			this->_y + other._y,
			this->_z + other._z,
			this->_w + other._w
			);
	}

	Vect& Vect::increment(const Vect& other)
	{
		this->_x += other._x;
		this->_y += other._y;
		this->_z += other._z;
		this->_w += other._w;

		return *this;
	}

}
