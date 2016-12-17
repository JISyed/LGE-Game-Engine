#include "MathEngine.h"
#include <math.h>
#include <cassert>

namespace lge
{
	// Big four

	// Default Ctor (all zeros)
	Matrix::Matrix() :
		_v0(0.0f),
		_v1(0.0f),
		_v2(0.0f),
		_v3(0.0f)
	{
	}

	// Destructor
	Matrix::~Matrix()
	{
	}

	// Copy Ctor
	Matrix::Matrix(const Matrix& rhs) :
		_v0(rhs._v0),
		_v1(rhs._v1),
		_v2(rhs._v2),
		_v3(rhs._v3)
	{
	}

	// Assignment Overload
	Matrix& Matrix::operator=(const Matrix& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->_v0 = rhs._v0;
		this->_v1 = rhs._v1;
		this->_v2 = rhs._v2;
		this->_v3 = rhs._v3;

		return *this;
	}

	// Multi-Vector Constructor
	Matrix::Matrix(const Vect& v0, const Vect& v1, const Vect& v2, const Vect& v3) :
		_v0(v0),
		_v1(v1),
		_v2(v2),
		_v3(v3)
	{
	}

	// Ctor for either Identity or Zero matrix
	Matrix::Matrix(const MatrixSpecialType specialType) :
		_v0(0.0f),
		_v1(0.0f),
		_v2(0.0f),
		_v3(0.0f)
	{
		// "specialType" only assumes Identity matrix or Zero matrix

		// Always make a zero matrix, but alter 4 members if it's an identity matrix
		if (specialType == MatrixSpecialType::IDENTITY)
		{
			// Set diagonal
			this->_m0 = 1.0f;
			this->_m5 = 1.0f;
			this->_m10 = 1.0f;
			this->_m15 = 1.0f;
		}
	}

	// Multi-__m128's constructor
	Matrix::Matrix(const __m128& vm0, const __m128& vm1, const __m128& vm2, const __m128& vm3) :
		_v0(vm0),
		_v1(vm1),
		_v2(vm2),
		_v3(vm3)
	{
	}


	// Translation Matrix ctor
	Matrix::Matrix(const MatrixTransType tr, const float x, const float y, const float z) :
		_v0(1.0f, 0.0f, 0.0f, 0.0f),
		_v1(0.0f, 1.0f, 0.0f, 0.0f),
		_v2(0.0f, 0.0f, 1.0f, 0.0f),
		_v3(x, y, z, 1.0f)
	{
		tr;
	}

	Matrix::Matrix(const MatrixTransType tr, const Vect& translation) :
		_v0(1.0f, 0.0f, 0.0f, 0.0f),
		_v1(0.0f, 1.0f, 0.0f, 0.0f),
		_v2(0.0f, 0.0f, 1.0f, 0.0f),
		_v3(translation)
	{
		tr;
	}


	// Scale Matrix ctor
	Matrix::Matrix(const MatrixScaleType sc, const float x, const float y, const float z) :
		_v0(x, 0.0f, 0.0f, 0.0f),
		_v1(0.0f, y, 0.0f, 0.0f),
		_v2(0.0f, 0.0f, z, 0.0f),
		_v3(0.0f, 0.0f, 0.0f, 1.0f)
	{
		sc;
	}

	Matrix::Matrix(const MatrixScaleType sc, const Vect& scaling) :
		_v0(scaling.x(), 0.0f, 0.0f, 0.0f),
		_v1(0.0f, scaling.y(), 0.0f, 0.0f),
		_v2(0.0f, 0.0f, scaling.z(), 0.0f),
		_v3(0.0f, 0.0f, 0.0f, 1.0f)
	{
		sc;
	}


	// Rotation Matrix ctor (angle in radians)
	Matrix::Matrix(const RotType axis, const float angle)
	{
		this->set(axis, angle);
	}


	// Angle-Axis Ctor
	Matrix::Matrix(const RotAxisAngleType type, const Vect& rotationAxis, const float angle) :
		Matrix(Quat(type, rotationAxis.getNorm(), angle))
	{
	}

	// Orientation Ctor
	Matrix::Matrix(const RotOrientType orientation, const Vect& dofForward, const Vect& up)
	{
		this->set(orientation, dofForward, up);
	}

	// All Euler Angles Ctor
	Matrix::Matrix(const Rot3AxisType type, const float xRot, const float yRot, const float zRot) :
		Matrix(Quat(type, xRot, yRot, zRot))
	{
	}

	// Quaternion Ctor (to make a rotation matrix)
	Matrix::Matrix(const Quat& rotation)
	{
		const float xx = rotation.x() * rotation.x();
		const float yy = rotation.y() * rotation.y();
		const float zz = rotation.z() * rotation.z();
		const float xy = rotation.x() * rotation.y();
		const float yz = rotation.y() * rotation.z();
		const float xz = rotation.x() * rotation.z();
		const float wx = rotation.w() * rotation.x();
		const float wy = rotation.w() * rotation.y();
		const float wz = rotation.w() * rotation.z();

		this->_v0 = Vect(1.0f - 2.0f*(yy + zz), 2.0f*(xy + wz), 2.0f*(xz - wy), 0.0f);
		this->_v1 = Vect(2.0f*(xy - wz), 1.0f - 2.0f*(xx + zz), 2.0f*(yz + wx), 0.0f);
		this->_v2 = Vect(2.0f*(xz + wy), 2.0f*(yz - wx), 1.0f - 2.0f*(xx + yy), 0.0f);
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
	}








	// Square bracket getters
	const float Matrix::operator[](const m0_enum m) const
	{
		m;
		return this->_m0;
	}

	const float Matrix::operator[](const m1_enum m) const
	{
		m;
		return this->_m1;
	}

	const float Matrix::operator[](const m2_enum m) const
	{
		m;
		return this->_m2;
	}

	const float Matrix::operator[](const m3_enum m) const
	{
		m;
		return this->_m3;
	}

	const float Matrix::operator[](const m4_enum m) const
	{
		m;
		return this->_m4;
	}

	const float Matrix::operator[](const m5_enum m) const
	{
		m;
		return this->_m5;
	}

	const float Matrix::operator[](const m6_enum m) const
	{
		m;
		return this->_m6;
	}

	const float Matrix::operator[](const m7_enum m) const
	{
		m;
		return this->_m7;
	}

	const float Matrix::operator[](const m8_enum m) const
	{
		m;
		return this->_m8;
	}

	const float Matrix::operator[](const m9_enum m) const
	{
		m;
		return this->_m9;
	}

	const float Matrix::operator[](const m10_enum m) const
	{
		m;
		return this->_m10;
	}

	const float Matrix::operator[](const m11_enum m) const
	{
		m;
		return this->_m11;
	}

	const float Matrix::operator[](const m12_enum m) const
	{
		m;
		return this->_m12;
	}

	const float Matrix::operator[](const m13_enum m) const
	{
		m;
		return this->_m13;
	}

	const float Matrix::operator[](const m14_enum m) const
	{
		m;
		return this->_m14;
	}

	const float Matrix::operator[](const m15_enum m) const
	{
		m;
		return this->_m15;
	}


	// Square bracker setters
	float& Matrix::operator[](const m0_enum m)
	{
		m;
		return this->_m0;
	}

	float& Matrix::operator[](const m1_enum m)
	{
		m;
		return this->_m1;
	}

	float& Matrix::operator[](const m2_enum m)
	{
		m;
		return this->_m2;
	}

	float& Matrix::operator[](const m3_enum m)
	{
		m;
		return this->_m3;
	}

	float& Matrix::operator[](const m4_enum m)
	{
		m;
		return this->_m4;
	}

	float& Matrix::operator[](const m5_enum m)
	{
		m;
		return this->_m5;
	}

	float& Matrix::operator[](const m6_enum m)
	{
		m;
		return this->_m6;
	}

	float& Matrix::operator[](const m7_enum m)
	{
		m;
		return this->_m7;
	}

	float& Matrix::operator[](const m8_enum m)
	{
		m;
		return this->_m8;
	}

	float& Matrix::operator[](const m9_enum m)
	{
		m;
		return this->_m9;
	}

	float& Matrix::operator[](const m10_enum m)
	{
		m;
		return this->_m10;
	}

	float& Matrix::operator[](const m11_enum m)
	{
		m;
		return this->_m11;
	}

	float& Matrix::operator[](const m12_enum m)
	{
		m;
		return this->_m12;
	}

	float& Matrix::operator[](const m13_enum m)
	{
		m;
		return this->_m13;
	}

	float& Matrix::operator[](const m14_enum m)
	{
		m;
		return this->_m14;
	}

	float& Matrix::operator[](const m15_enum m)
	{
		m;
		return this->_m15;
	}

	// Get a row from the matrix as a vector
	const Vect Matrix::get(const MatrixRowType row) const
	{
		//Vect* vPtr = (Vect*) this;
		//vPtr = vPtr + (unsigned int)row;
		//return *vPtr;

		return *(((Vect*)this) + ((unsigned int)row));
	}

	// Multi-vector setter
	void Matrix::set(const Vect& v0, const Vect& v1, const Vect& v2, const Vect& v3)
	{
		this->_v0 = v0;
		this->_v1 = v1;
		this->_v2 = v2;
		this->_v3 = v3;
	}


	// Row setter
	void Matrix::set(const MatrixRowType row, const Vect& rowValues)
	{
		//Vect* vPtr = (Vect*) this;
		//vPtr = vPtr + (unsigned int)row;
		//*vPtr = rowValues;

		*(((Vect*)this) + ((unsigned int)row)) = rowValues;
	}


	// Set to identity matrix or zero matrix
	void Matrix::set(const MatrixSpecialType specialType)
	{
		// There are only two special types, so if it's not one, it's the other
		if (specialType == MatrixSpecialType::ZERO)
		{
			this->_v0 = Vect(0.0f);
			this->_v1 = Vect(0.0f);
			this->_v2 = Vect(0.0f);
			this->_v3 = Vect(0.0f);
		}
		// Assumes MatrixSpecialType::IDENTITY
		else
		{
			this->_v0 = Vect(1.0f, 0.0f, 0.0f, 0.0f);
			this->_v1 = Vect(0.0f, 1.0f, 0.0f, 0.0f);
			this->_v2 = Vect(0.0f, 0.0f, 1.0f, 0.0f);
			this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
		}
	}

	// Translation matrix setter (three floats)
	void Matrix::set(const MatrixTransType trans, const float x, const float y, const float z)
	{
		trans;
		this->_v0 = Vect(1.0f, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vect(0.0f, 1.0f, 0.0f, 0.0f);
		this->_v2 = Vect(0.0f, 0.0f, 1.0f, 0.0f);
		this->_v3 = Vect(x, y, z, 1.0f);
	}

	// Translation matrix setter (one Vect)
	void Matrix::set(const MatrixTransType trans, const Vect& translation)
	{
		trans;
		this->_v0 = Vect(1.0f, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vect(0.0f, 1.0f, 0.0f, 0.0f);
		this->_v2 = Vect(0.0f, 0.0f, 1.0f, 0.0f);
		this->_v3 = translation;
	}

	// Scale matrix setter (three floats)
	void Matrix::set(const MatrixScaleType sc, const float x, const float y, const float z)
	{
		sc;
		this->_v0 = Vect(x, 0.0f, 0.0f, 0.0f);
		this->_v1 = Vect(0.0f, y, 0.0f, 0.0f);
		this->_v2 = Vect(0.0f, 0.0f, z, 0.0f);
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// Scale matrix setter (one Vect)
	void Matrix::set(const MatrixScaleType sc, const Vect& scaling)
	{
		sc;
		this->_v0 = Vect(scaling.x(), 0.0f, 0.0f, 0.0f);
		this->_v1 = Vect(0.0f, scaling.y(), 0.0f, 0.0f);
		this->_v2 = Vect(0.0f, 0.0f, scaling.z(), 0.0f);
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// Rotation matrix (angle in radians)
	void Matrix::set(const RotType rotationAxis, const float angle)
	{
		const float cosAngle = cosf(angle);
		const float sinAngle = sinf(angle);

		switch (rotationAxis)
		{
			case RotType::ROT_X:
				this->_v0 = Vect(1.0f, 0.0f, 0.0f, 0.0f);
				this->_v1 = Vect(0.0f, cosAngle, sinAngle, 0.0f);
				this->_v2 = Vect(0.0f, -sinAngle, cosAngle, 0.0f);
				this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
				break;
			case RotType::ROT_Y:
				this->_v0 = Vect(cosAngle, 0.0f, -sinAngle, 0.0f);
				this->_v1 = Vect(0.0f, 1.0f, 0.0f, 0.0f);
				this->_v2 = Vect(sinAngle, 0.0f, cosAngle, 0.0f);
				this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
				break;
			case RotType::ROT_Z:
				this->_v0 = Vect(cosAngle, sinAngle, 0.0f, 0.0f);
				this->_v1 = Vect(-sinAngle, cosAngle, 0.0f, 0.0f);
				this->_v2 = Vect(0.0f, 0.0f, 1.0f, 0.0f);
				this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
				break;
			default:
				assert(rotationAxis != rotationAxis);
				break;
		}
	}


	// Quaternion setter
	void Matrix::set(const Quat& rotation)
	{
		const float xx = rotation.x() * rotation.x();
		const float yy = rotation.y() * rotation.y();
		const float zz = rotation.z() * rotation.z();
		const float xy = rotation.x() * rotation.y();
		const float yz = rotation.y() * rotation.z();
		const float xz = rotation.x() * rotation.z();
		const float wx = rotation.w() * rotation.x();
		const float wy = rotation.w() * rotation.y();
		const float wz = rotation.w() * rotation.z();

		this->_v0 = Vect(1.0f - 2.0f*(yy + zz), 2.0f*(xy + wz), 2.0f*(xz - wy), 0.0f);
		this->_v1 = Vect(2.0f*(xy - wz), 1.0f - 2.0f*(xx + zz), 2.0f*(yz + wx), 0.0f);
		this->_v2 = Vect(2.0f*(xz + wy), 2.0f*(yz - wx), 1.0f - 2.0f*(xx + yy), 0.0f);
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// Angle-Axis setter
	void Matrix::set(const RotAxisAngleType type, const Vect& rotationAxis, const float angle)
	{
		this->set(Quat(type, rotationAxis, angle));
	}

	// Orientation setter
	void Matrix::set(const RotOrientType orientation, const Vect& dofForward, const Vect& oldUp)
	{


		// Calculate the corrected up
		const Vect up((dofForward.cross(oldUp.cross(dofForward))));
		const Vect upNorm = up.getNorm();

		Vect orientX(up.cross(dofForward));
		orientX.norm();
		orientX[W] = 0.0f;

		Vect orientY(upNorm);
		orientY[W] = 0.0f;

		Vect orientZ(dofForward);
		orientZ.norm();
		orientZ[W] = 0.0f;

		this->_v0 = orientX;
		this->_v1 = orientY;
		this->_v2 = orientZ;
		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);

		if (orientation == RotOrientType::ROT_INVERSE_ORIENT)
		{
			this->T();
		}
	}

	// All Euler Angles setter
	void Matrix::set(const Rot3AxisType type, const float xRot, const float yRot, const float zRot)
	{
		this->set(Quat(type, xRot, yRot, zRot));
	}










	// Function based getters
	const float Matrix::m0() const
	{
		return this->_m0;
	}

	const float Matrix::m1() const
	{
		return this->_m1;
	}

	const float Matrix::m2() const
	{
		return this->_m2;
	}

	const float Matrix::m3() const
	{
		return this->_m3;
	}

	const float Matrix::m4() const
	{
		return this->_m4;
	}

	const float Matrix::m5() const
	{
		return this->_m5;
	}

	const float Matrix::m6() const
	{
		return this->_m6;
	}

	const float Matrix::m7() const
	{
		return this->_m7;
	}

	const float Matrix::m8() const
	{
		return this->_m8;
	}

	const float Matrix::m9() const
	{
		return this->_m9;
	}

	const float Matrix::m10() const
	{
		return this->_m10;
	}

	const float Matrix::m11() const
	{
		return this->_m11;
	}

	const float Matrix::m12() const
	{
		return this->_m12;
	}

	const float Matrix::m13() const
	{
		return this->_m13;
	}

	const float Matrix::m14() const
	{
		return this->_m14;
	}

	const float Matrix::m15() const
	{
		return this->_m15;
	}



	// Function based setters
	float& Matrix::m0()
	{
		return this->_m0;
	}

	float& Matrix::m1()
	{
		return this->_m1;
	}

	float& Matrix::m2()
	{
		return this->_m2;
	}

	float& Matrix::m3()
	{
		return this->_m3;
	}

	float& Matrix::m4()
	{
		return this->_m4;
	}

	float& Matrix::m5()
	{
		return this->_m5;
	}

	float& Matrix::m6()
	{
		return this->_m6;
	}

	float& Matrix::m7()
	{
		return this->_m7;
	}

	float& Matrix::m8()
	{
		return this->_m8;
	}

	float& Matrix::m9()
	{
		return this->_m9;
	}

	float& Matrix::m10()
	{
		return this->_m10;
	}

	float& Matrix::m11()
	{
		return this->_m11;
	}

	float& Matrix::m12()
	{
		return this->_m12;
	}

	float& Matrix::m13()
	{
		return this->_m13;
	}

	float& Matrix::m14()
	{
		return this->_m14;
	}

	float& Matrix::m15()
	{
		return this->_m15;
	}




	// Unary + operator
	const Matrix Matrix::operator+() const
	{
		return *this;
	}

	// Unary - operator
	const Matrix Matrix::operator-() const
	{
		return Matrix(*this * -1.0f);
	}




	// Scalar multiplication
	const Matrix Matrix::operator*(const float scalarRhs) const
	{
		//return Matrix(this->_v0 * scalarRhs, this->_v1 * scalarRhs, this->_v2 * scalarRhs, this->_v3 * scalarRhs);
		const __m128 scalarBlock = _mm_set_ps1(scalarRhs);
		return Matrix(
			_mm_mul_ps(this->_v0.getConstM(), scalarBlock),
			_mm_mul_ps(this->_v1.getConstM(), scalarBlock),
			_mm_mul_ps(this->_v2.getConstM(), scalarBlock),
			_mm_mul_ps(this->_v3.getConstM(), scalarBlock)
			);
	}

	// Scalar multiplication
	Matrix& Matrix::operator*=(const float scalarRhs)
	{
		const __m128 scalarBlock = _mm_set_ps1(scalarRhs);

		//__m128 result = _mm_mul_ps(vector, scalar);
		this->_v0.getMRef() = _mm_mul_ps(this->_v0.getConstM(), scalarBlock);
		this->_v1.getMRef() = _mm_mul_ps(this->_v1.getConstM(), scalarBlock);
		this->_v2.getMRef() = _mm_mul_ps(this->_v2.getConstM(), scalarBlock);
		this->_v3.getMRef() = _mm_mul_ps(this->_v3.getConstM(), scalarBlock);

		/*
		this->_v0 *= scalarRhs;
		this->_v1 *= scalarRhs;
		this->_v2 *= scalarRhs;
		this->_v3 *= scalarRhs;
		//*/

		return *this;
	}

	// FRIEND
	// Scalar multiplication
	const Matrix operator*(const float scalarLhs, const Matrix& matRhs)
	{
		//return Matrix(matRhs._v0 * scalarLhs, matRhs._v1 * scalarLhs, matRhs._v2 * scalarLhs, matRhs._v3 * scalarLhs);
		const __m128 scalarBlock = _mm_set_ps1(scalarLhs);
		return Matrix(
			_mm_mul_ps(matRhs._v0.getConstM(), scalarBlock),
			_mm_mul_ps(matRhs._v1.getConstM(), scalarBlock),
			_mm_mul_ps(matRhs._v2.getConstM(), scalarBlock),
			_mm_mul_ps(matRhs._v3.getConstM(), scalarBlock)
			);
	}



	// Matrix addition
	const Matrix Matrix::operator+(const Matrix& rhs) const
	{
		return Matrix(
			_mm_add_ps(this->_v0.getConstM(), rhs._v0.getConstM()),
			_mm_add_ps(this->_v1.getConstM(), rhs._v1.getConstM()),
			_mm_add_ps(this->_v2.getConstM(), rhs._v2.getConstM()),
			_mm_add_ps(this->_v3.getConstM(), rhs._v3.getConstM())
			);
	}

	Matrix& Matrix::operator+=(const Matrix& rhs)
	{
		this->_v0.getMRef() = _mm_add_ps(this->_v0.getConstM(), rhs._v0.getConstM());
		this->_v1.getMRef() = _mm_add_ps(this->_v1.getConstM(), rhs._v1.getConstM());
		this->_v2.getMRef() = _mm_add_ps(this->_v2.getConstM(), rhs._v2.getConstM());
		this->_v3.getMRef() = _mm_add_ps(this->_v3.getConstM(), rhs._v3.getConstM());

		return *this;
	}

	// Matrix subtraction
	const Matrix Matrix::operator-(const Matrix& rhs) const
	{
		return Matrix(
			_mm_sub_ps(this->_v0.getConstM(), rhs._v0.getConstM()),
			_mm_sub_ps(this->_v1.getConstM(), rhs._v1.getConstM()),
			_mm_sub_ps(this->_v2.getConstM(), rhs._v2.getConstM()),
			_mm_sub_ps(this->_v3.getConstM(), rhs._v3.getConstM())
			);
	}

	Matrix& Matrix::operator-=(const Matrix& rhs)
	{
		this->_v0.getMRef() = _mm_sub_ps(this->_v0.getConstM(), rhs._v0.getConstM());
		this->_v1.getMRef() = _mm_sub_ps(this->_v1.getConstM(), rhs._v1.getConstM());
		this->_v2.getMRef() = _mm_sub_ps(this->_v2.getConstM(), rhs._v2.getConstM());
		this->_v3.getMRef() = _mm_sub_ps(this->_v3.getConstM(), rhs._v3.getConstM());

		return *this;
	}





	// Check if the matrix is equal to another matrix
	const bool Matrix::isEqual(const Matrix& other, float floatTolerance) const
	{
		// Leave if Row0 is not equal
		if (!this->_v0.isEqual(other._v0, floatTolerance))
		{
			return false;
		}

		// Leave if Row1 is not equal
		if (!this->_v1.isEqual(other._v1, floatTolerance))
		{
			return false;
		}

		// Leave if Row2 is not equal
		if (!this->_v2.isEqual(other._v2, floatTolerance))
		{
			return false;
		}

		// Leave if Row3 is not equal
		if (!this->_v3.isEqual(other._v3, floatTolerance))
		{
			return false;
		}

		// If you're here, all the rows are equal
		return true;
	}

	const bool Matrix::isIdentity(float floatTolerance) const
	{
		return this->isEqual(Matrix(IDENTITY), floatTolerance);
	}





	// Matrix Multiplication
	const Matrix Matrix::operator*(const Matrix& rhs) const
	{
		return Matrix(
			this->_v0 * rhs,
			this->_v1 * rhs,
			this->_v2 * rhs,
			this->_v3 * rhs
			);
	}

	Matrix& Matrix::operator*=(const Matrix& rhs)
	{
		this->_v0 *= rhs;
		this->_v1 *= rhs;
		this->_v2 *= rhs;
		this->_v3 *= rhs;

		return *this;
	}






	// Calculate the determinant of the Matrix
	const float Matrix::det() const
	{
		// Old fashioned way :(
		return (_m0*_m5*_m10*_m15) + (_m0*_m6*_m11*_m13) + (_m0*_m7*_m9*_m14)
			+ (_m1*_m4*_m11*_m14) + (_m1*_m6*_m8*_m15) + (_m1*_m7*_m10*_m12)
			+ (_m2*_m4*_m9*_m15) + (_m2*_m5*_m11*_m12) + (_m2*_m7*_m8*_m13)
			+ (_m3*_m4*_m10*_m13) + (_m3*_m5*_m8*_m14) + (_m3*_m6*_m9*_m12)
			- (_m0*_m5*_m11*_m14) - (_m0*_m6*_m9*_m15) - (_m0*_m7*_m10*_m13)
			- (_m1*_m4*_m10*_m15) - (_m1*_m6*_m11*_m12) - (_m1*_m7*_m8*_m14)
			- (_m2*_m4*_m11*_m13) - (_m2*_m5*_m8*_m15) - (_m2*_m7*_m9*_m12)
			- (_m3*_m4*_m9*_m14) - (_m3*_m5*_m10*_m12) - (_m3*_m6*_m8*_m13)
			;
	}

	// Transpose yourself
	Matrix& Matrix::T()
	{
		_MM_TRANSPOSE4_PS(this->_v0.getMRef(),
						  this->_v1.getMRef(),
						  this->_v2.getMRef(),
						  this->_v3.getMRef()
						  );

		return *this;
	}

	// Get the Transpose of this matrix
	const Matrix Matrix::getT() const
	{
		Matrix transposedCopy(*this);

		_MM_TRANSPOSE4_PS(transposedCopy._v0.getMRef(),
						  transposedCopy._v1.getMRef(),
						  transposedCopy._v2.getMRef(),
						  transposedCopy._v3.getMRef()
						  );

		return transposedCopy;
	}




	// Inverse yourself
	Matrix& Matrix::inv()
	{
		// Leave if the determinant is 0
		const float determinent = this->det();
		if (Util::isZero(determinent))
		{
			assert(!Util::isZero(determinent));
			return *this;
		}

		// Using SIMD version of inverse
		this->sse_inverse_mat4x4((float*)this);

		return *this;
	}

	// Get the inverse of this matrix
	const Matrix Matrix::getInv() const
	{
		// Leave if the determinant is 0
		const float determinent = this->det();
		if (Util::isZero(determinent))
		{
			assert(!Util::isZero(determinent));
			return Matrix(*this);
		}


		// Using SIMD version of inverse
		Matrix inverseCopy(*this);
		inverseCopy.sse_inverse_mat4x4((float*)&inverseCopy);

		return inverseCopy;
	}


	// SIMD inverse implementation from:
	// ftp://download.intel.com/design/PentiumIII/sml/24504301.pdf
	void Matrix::sse_inverse_mat4x4(float* src)
	{
		__m128 minor0, minor1, minor2, minor3;
		__m128 row0, row1, row2, row3;
		__m128 det, tmp1;

		// These 4 lines were added to prevent uninitialize warnings
		const __m128 zeroM = _mm_set_ps1(0.0f);
		tmp1 = zeroM;
		row1 = zeroM;
		row3 = zeroM;

		tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src)), (__m64*)(src + 4));
		row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src + 8)), (__m64*)(src + 12));
		row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
		row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);
		tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src + 2)), (__m64*)(src + 6));
		row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src + 10)), (__m64*)(src + 14));
		row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
		row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row2, row3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor0 = _mm_mul_ps(row1, tmp1);
		minor1 = _mm_mul_ps(row0, tmp1);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
		minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
		minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row1, row2);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
		minor3 = _mm_mul_ps(row0, tmp1);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
		minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
		minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		row2 = _mm_shuffle_ps(row2, row2, 0x4E);
		minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
		minor2 = _mm_mul_ps(row0, tmp1);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
		minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
		minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row0, row1);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
		minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row0, row3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
		minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
		minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));
		// -----------------------------------------------
		tmp1 = _mm_mul_ps(row0, row2);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
		minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);
		// -----------------------------------------------
		det = _mm_mul_ps(row0, minor0);
		det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
		det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
		tmp1 = _mm_rcp_ss(det);
		det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
		det = _mm_shuffle_ps(det, det, 0x00);
		minor0 = _mm_mul_ps(det, minor0);
		_mm_storel_pi((__m64*)(src), minor0);
		_mm_storeh_pi((__m64*)(src + 2), minor0);
		minor1 = _mm_mul_ps(det, minor1);
		_mm_storel_pi((__m64*)(src + 4), minor1);
		_mm_storeh_pi((__m64*)(src + 6), minor1);
		minor2 = _mm_mul_ps(det, minor2);
		_mm_storel_pi((__m64*)(src + 8), minor2);
		_mm_storeh_pi((__m64*)(src + 10), minor2);
		minor3 = _mm_mul_ps(det, minor3);
		_mm_storel_pi((__m64*)(src + 12), minor3);
		_mm_storeh_pi((__m64*)(src + 14), minor3);
	}

}