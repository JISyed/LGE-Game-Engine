/** @file */ 
/*****************************************************************************/
/*                                                                           */
/* file: Quat.h                                                              */
/*                                                                           */
/*****************************************************************************/

#ifndef ENGINE_MATH_QUAT_H
#define ENGINE_MATH_QUAT_H

/*****************************************************************************/
/* Includes:                                                                 */
/*****************************************************************************/
#include "Matrix.h"
#include "Enum.h"


	/*************************************************************************
	*
	* This class contains functions and data structure for a 4-dimensional 
	* Quaternions.  The quaternions are internally stored interms of the 
	* imaginary components (qx,qy,qz) and the real components (qw).
	*
	* In the Math library, quaternions can be thought of as "rotational"
	* matrices, everything that you can represent with rotational matrices
	* you can use with quaternions.  Such as quaternion concatenation,
	* inverses, transpose, normalize, multiplying with matrices, and with
	* vectors.
	*  
	*  
	**************************************************************************/

namespace lge
{
	// 4D complex number used for rotations in 3D
	class Quat final : public Align16
	{
	public:

		//
		// Big 4
		//

		// Default Ctor (0,0,0,1)
		explicit Quat();

		// Destructor
		~Quat();

		// Copy Ctor
		Quat(const Quat& rhs);

		// Assignment Overload
		Quat& operator=(const Quat& rhs);



		//
		// Other constructors
		//

		// All Elements Ctor
		Quat(const float qx, const float qy, const float qz, const float qw);

		// The __m128 Ctor
		explicit Quat(const __m128& m);

		// Imaginary Vector + Real Scalar Ctor
		Quat(const Vect& qv, const float qs);

		// Rotation Matrix Ctor (must be rotation matrix)
		explicit Quat(const Matrix& matRot);

		// Special Type Ctor (Identity or Zero)
		explicit Quat(const MatrixSpecialType type);

		// All Euler Angles Ctor
		Quat(const Rot3AxisType type, const float xRot, const float yRot, const float zRot);

		// One Euler Angle Ctor
		Quat(const RotType axis, const float rotation);

		// Angle-Axis Ctor
		Quat(const RotAxisAngleType type, const Vect& rotationAxis, const float angle);

		// Orientation Ctor
		Quat(const RotOrientType orientation, const Vect& dofForward, const Vect& up);



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

		// Get the imaginary vectory portion of this Quaternion (v[4] becomes 1)
		void getVect(Vect& v) const;

		// Get the angle of this Quaternion
		const float getAngle() const;

		// Get the axis of rotation for this Quaternion
		void getAxis(Vect& axis) const;



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

		// Imaginary Vector + Real Scalar setter
		void set(const Vect& qv, const float qs);

		// Rotation Matrix setter (must be Rotation matrix)
		void set(const Matrix& matRot);

		// Special Type setter (Identity or Zero)
		void set(const MatrixSpecialType type);

		// One Euler Angle setter
		void set(const RotType axis, const float rotation);

		// All Euler Angles setter
		void set(const Rot3AxisType type, const float xRot, const float yRot, const float zRot);

		// Angle-Axis setter
		void set(const RotAxisAngleType type, const Vect& rotationAxis, const float angle);

		// Orientation setter
		void set(const RotOrientType orientation, const Vect& dofForward, const Vect& up);

		// Set the imaginary vector portion of this Quaternion
		void setVect(const Vect& qv);




		//
		// Operator Overloads
		//


		// Convert a Rotational Matrix into a Quaternion
		Quat& operator=(const Matrix& rhs);

		// Quaternion x Matrix
		const Quat operator*(const Matrix& rhs) const;

		// Quaternion x Matrix
		Quat& operator*=(const Matrix& rhs);



		// Unary + operator overload
		const Quat operator+() const;

		// Add two Quaternions together
		const Quat operator+(const Quat& rhs) const;

		// Add two Quaternions together
		Quat& operator+=(const Quat& rhs);

		// Scalar addition across every element of the Quat
		const Quat operator+(const float rhs) const;

		// Scalar addition across every element of the Quat
		Quat& operator+=(const float rhs);

		// Scalar addition across every element of the Quat
		friend const Quat operator+(const float scalarLhs, const Quat& quatRhs);



		// Negation operator overload
		const Quat operator-() const;

		// Subtract two Quaternions together
		const Quat operator-(const Quat& rhs) const;

		// Subtract two Quaternions together
		Quat& operator-=(const Quat& rhs);

		// Scalar subtraction across every element of the Quat
		const Quat operator-(const float rhs) const;

		// Scalar subtraction across every element of the Quat
		Quat& operator-=(const float rhs);

		// Scalar subtraction across every element of the Quat
		friend const Quat operator-(const float scalarLhs, const Quat& quatRhs);



		// Quaternion product (NOT dot product)
		const Quat operator*(const Quat& rhs) const;

		// Quaternion product (NOT dot product)
		Quat& operator*=(const Quat& rhs);

		// Scalar multiplication across every element of the Quat
		const Quat operator*(const float rhs) const;

		// Scalar multiplication across every element of the Quat
		Quat& operator*=(const float rhs);

		// Scalar multiplication across every element of the Quat
		friend const Quat operator*(const float scalarLhs, const Quat& quatRhs);



		// Divide the elements of two Quaternions together
		const Quat operator/(const Quat& rhs) const;

		// Divide the elements two Quaternions together
		Quat& operator/=(const Quat& rhs);

		// Scalar division across every element of the Quat
		const Quat operator/(const float rhs) const;

		// Scalar division across every element of the Quat
		Quat& operator/=(const float rhs);

		// Scalar division across every element of the Quat
		friend const Quat operator/(const float scalarLhs, const Quat& quatRhs);





		//
		// Other Math Operators
		//

		// Calculate the conjugate of this Quaternion
		const Quat getConj() const;

		// Conjugate yourself
		void conj();

		// Calculate the transpose of this Quaternion
		const Quat getT() const;

		// Transpose yourself
		void T();

		// Calculate the length of this Quaternion
		const float mag() const;

		// Calculate the squared-length of this Quaternion (faster than mag())
		const float magSquared() const;

		// Calculate 1 over the length of this Quaternion
		const float invMag() const;

		// Calculate the normalized version of this Quaternion AND normalize yourself
		const Quat norm();

		// Only calculate the normalized version of this Quaternion without normalizing this Quaternion
		const Quat getNorm() const;

		// Get the inverse Quaternion of this Quaternion
		const Quat getInv() const;

		// Invert yourself
		void inv();

		// Do linear operation of vector with this quaternion q (as in "q*vq", where q* is the conjugate)
		void Lqcvq(const Vect& v, Vect& answer) const;

		// Do linear operation of vector with this quaternion q (as in "qvq*", where q* is the conjugate)
		void Lqvqc(const Vect& v, Vect& answer) const;

		// Quaternion Dot Multiplication (q1 dot q2)
		const float dot(const Quat& rhs) const;

		// Multiply the each element of one Quat by each corresponding element of the other Quat (NOT quat product)
		const Quat multByElement(const Quat& rhs) const;

		// Get the euler angle representation of this Quaternion
		const Vect convertToEulerAngles() const;



		//
		// Boolean Operators
		//

		// Is this Quaternion normalized?
		const bool isNormalized(const float epsilon = MATH_TOLERANCE) const;

		// Are the Quaterinions the same?
		const bool isEqual(const Quat& other, const float epsilon = MATH_TOLERANCE) const;

		// If the other Quat were made negative, would that negative equal this Quaternion?
		const bool isNegEqual(const Quat& other, const float epsilon = MATH_TOLERANCE) const;

		// Can this Quat rotate by theta and the other Quat rotate by -theta and they both performed the same rotation?
		const bool isEquivalent(const Quat& other, const float epsilon = MATH_TOLERANCE) const;

		// If the other Quat were made into its conjugate, would that conjugate equal this Quaternion?
		const bool isConjugateEqual(const Quat& other, const float epsilon = MATH_TOLERANCE) const;

		// Is this Quaternion an identity quaternion? (similar to identity matrix)
		const bool isIdentity(const float epsilon = MATH_TOLERANCE);

		// Is this Quaternion zero-ed out?
		const bool isZero(const float epsilon = MATH_TOLERANCE);




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
				float _qx;
				float _qy;
				float _qz;
				float _qw;
			};
		};


	};// end of Quat
}
#endif // #ifndef QUAT_H
/**** END of Quat.h ********************************************************/