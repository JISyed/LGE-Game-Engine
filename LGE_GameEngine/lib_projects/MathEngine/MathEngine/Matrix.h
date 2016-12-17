#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

// SIMD includes
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Enum.h"
#include "Vect.h"

namespace lge
{
	class Quat;

	// A row-major 4x4 Matrix (note that OpenGL is column-major)
	class Matrix final : public Align16
	{
	public:

		//
		// Big Four
		//

		// Default Ctor (all zeros)
		explicit Matrix();

		// Destructor
		~Matrix();

		// Copy Ctor
		Matrix(const Matrix& rhs);

		// Assignment Overload
		Matrix& operator=(const Matrix& rhs);



		//
		// Other Constructors
		//


		// Multi-Vector Constructor
		Matrix(const Vect& v0, const Vect& v1, const Vect& v2, const Vect& v3);

		// Ctor for either Identity or Zero matrix
		explicit Matrix(const MatrixSpecialType specialType);

		// Multi-__m128's constructor
		Matrix(const __m128& vm0, const __m128& vm1, const __m128& vm2, const __m128& vm3);

		// Translation Matrix ctor (floats)
		Matrix(const MatrixTransType tr, const float x, const float y, const float z);

		// Translation Matrix ctor (Vect)
		Matrix(const MatrixTransType tr, const Vect& translation);

		// Scale Matrix ctor
		Matrix(const MatrixScaleType sc, const float x, const float y, const float z);
		// Scale Matrix ctor
		Matrix(const MatrixScaleType sc, const Vect& scaling);

		// Rotation Matrix ctor (angle in radians)
		Matrix(const RotType axis, const float angle);

		// Angle-Axis Ctor
		Matrix(const RotAxisAngleType type, const Vect& rotationAxis, const float angle);

		// Orientation Ctor
		Matrix(const RotOrientType orientation, const Vect& dofForward, const Vect& up);

		// All Euler Angles Ctor
		Matrix(const Rot3AxisType type, const float xRot, const float yRot, const float zRot);

		// Quaternion Ctor (to make a rotation matrix)
		explicit Matrix(const Quat& rotation);




		//
		// Getters
		//


		// Square bracket getter
		const float operator[](const m0_enum m) const;
		// Square bracket getter
		const float operator[](const m1_enum m) const;
		// Square bracket getter
		const float operator[](const m2_enum m) const;
		// Square bracket getter
		const float operator[](const m3_enum m) const;
		// Square bracket getter
		const float operator[](const m4_enum m) const;
		// Square bracket getter
		const float operator[](const m5_enum m) const;
		// Square bracket getter
		const float operator[](const m6_enum m) const;
		// Square bracket getter
		const float operator[](const m7_enum m) const;
		// Square bracket getter
		const float operator[](const m8_enum m) const;
		// Square bracket getter
		const float operator[](const m9_enum m) const;
		// Square bracket getter
		const float operator[](const m10_enum m) const;
		// Square bracket getter
		const float operator[](const m11_enum m) const;
		// Square bracket getter
		const float operator[](const m12_enum m) const;
		// Square bracket getter
		const float operator[](const m13_enum m) const;
		// Square bracket getter
		const float operator[](const m14_enum m) const;
		// Square bracket getter
		const float operator[](const m15_enum m) const;


		// Get a row from the matrix as a vector
		const Vect get(const MatrixRowType row) const;


		// Function based getter
		const float m0() const;
		// Function based getter
		const float m1() const;
		// Function based getter
		const float m2() const;
		// Function based getter
		const float m3() const;
		// Function based getter
		const float m4() const;
		// Function based getter
		const float m5() const;
		// Function based getter
		const float m6() const;
		// Function based getter
		const float m7() const;
		// Function based getter
		const float m8() const;
		// Function based getter
		const float m9() const;
		// Function based getter
		const float m10() const;
		// Function based getter
		const float m11() const;
		// Function based getter
		const float m12() const;
		// Function based getter
		const float m13() const;
		// Function based getter
		const float m14() const;
		// Function based getter
		const float m15() const;





		//
		// Setters
		//

		// Square bracker setter
		float& operator[](const m0_enum m);
		// Square bracker setter
		float& operator[](const m1_enum m);
		// Square bracker setter
		float& operator[](const m2_enum m);
		// Square bracker setter
		float& operator[](const m3_enum m);
		// Square bracker setter
		float& operator[](const m4_enum m);
		// Square bracker setter
		float& operator[](const m5_enum m);
		// Square bracker setter
		float& operator[](const m6_enum m);
		// Square bracker setter
		float& operator[](const m7_enum m);
		// Square bracker setter
		float& operator[](const m8_enum m);
		// Square bracker setter
		float& operator[](const m9_enum m);
		// Square bracker setter
		float& operator[](const m10_enum m);
		// Square bracker setter
		float& operator[](const m11_enum m);
		// Square bracker setter
		float& operator[](const m12_enum m);
		// Square bracker setter
		float& operator[](const m13_enum m);
		// Square bracker setter
		float& operator[](const m14_enum m);
		// Square bracker setter
		float& operator[](const m15_enum m);


		// Multi-vector setter
		void set(const Vect& v0, const Vect& v1, const Vect& v2, const Vect& v3);

		// Row setter
		void set(const MatrixRowType row, const Vect& rowValues);

		// Set to identity matrix or zero matrix
		void set(const MatrixSpecialType specialType);

		// Translation matrix setter (three floats)
		void set(const MatrixTransType trans, const float x, const float y, const float z);

		// Translation matrix setter (one Vect)
		void set(const MatrixTransType trans, const Vect& translation);

		// Scale matrix setter (three floats)
		void set(const MatrixScaleType sc, const float x, const float y, const float z);

		// Scale matrix setter (one Vect)
		void set(const MatrixScaleType sc, const Vect& scaling);

		// Rotation matrix (angle in radians)
		void set(const RotType rotationAxis, const float angle);

		// Quaternion setter
		void set(const Quat& rotation);

		// Angle-Axis setter
		void set(const RotAxisAngleType type, const Vect& rotationAxis, const float angle);

		// Orientation setter
		void set(const RotOrientType orientation, const Vect& dofForward, const Vect& up);

		// All Euler Angles setter
		void set(const Rot3AxisType type, const float xRot, const float yRot, const float zRot);




		// Function based setter
		float& m0();
		// Function based setter
		float& m1();
		// Function based setter
		float& m2();
		// Function based setter
		float& m3();
		// Function based setter
		float& m4();
		// Function based setter
		float& m5();
		// Function based setter
		float& m6();
		// Function based setter
		float& m7();
		// Function based setter
		float& m8();
		// Function based setter
		float& m9();
		// Function based setter
		float& m10();
		// Function based setter
		float& m11();
		// Function based setter
		float& m12();
		// Function based setter
		float& m13();
		// Function based setter
		float& m14();
		// Function based setter
		float& m15();





		//
		// Unary operators
		//

		// Unary + operator
		const Matrix operator+() const;

		// Unary - operator
		const Matrix operator-() const;





		//
		// Scalar multiplication
		//

		// Scalar multiplication
		const Matrix operator*(const float scalarRhs) const;
		// Scalar multiplication
		Matrix& operator*=(const float scalarRhs);
		// Scalar multiplication
		friend const Matrix operator*(const float scalarLhs, const Matrix& matRhs);



		//
		// Matrix addition
		//

		// Matrix addition
		const Matrix operator+(const Matrix& rhs) const;
		// Matrix addition
		Matrix& operator+=(const Matrix& rhs);



		//
		// Matrix subtraction
		//

		// Matrix subtraction
		const Matrix operator-(const Matrix& rhs) const;
		// Matrix subtraction
		Matrix& operator-=(const Matrix& rhs);




		//
		// Matrix comparison
		//

		// Check if the matrix is equal to another matrix
		const bool isEqual(const Matrix& other, float floatTolerance = MATH_TOLERANCE) const;
		// Check if the matrix is an identity matrix
		const bool isIdentity(float floatTolerance = MATH_TOLERANCE) const;



		//
		// Matrix by Matrix multipication
		//

		// Matrix Multiplication
		const Matrix operator*(const Matrix& rhs) const;
		// Matrix Multiplication
		Matrix& operator*=(const Matrix& rhs);



		//
		// Matrix exclusive operations
		//

		// Calculate the determinant of the Matrix
		const float det() const;

		// Transpose yourself
		Matrix& T();

		// Get the Transpose of this matrix
		const Matrix getT() const;

		// Inverse yourself
		Matrix& inv();

		// Get the inverse of this matrix
		const Matrix getInv() const;



	private:

		//
		// Private helper routines
		//

		// SIMD inverse implementation from:
		// ftp://download.intel.com/design/PentiumIII/sml/24504301.pdf
		void sse_inverse_mat4x4(float* sourceMatrix);



		//
		// Data
		//

		// Level 4 complains nameless struct/union ...
		#pragma warning( disable : 4201)
		union
		{
			struct
			{
				Vect _v0;	// First row
				Vect _v1;	// Second row
				Vect _v2;	// Third row
				Vect _v3;	// Fourth row
			};

			struct
			{
				float _m0;
				float _m1;
				float _m2;
				float _m3;
				float _m4;
				float _m5;
				float _m6;
				float _m7;
				float _m8;
				float _m9;
				float _m10;
				float _m11;
				float _m12;
				float _m13;
				float _m14;
				float _m15;
			};
		};

	};// end of Matrix
}
#endif