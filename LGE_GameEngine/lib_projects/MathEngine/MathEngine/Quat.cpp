/*****************************************************************************/
/*                                                                           */
/* File: Quat.cpp                                                            */
/*                                                                           */
/* Quaterion Class                                                           */
/*                                                                           */
/*****************************************************************************/

#include "MathEngine.h"
#include <math.h>
#include <assert.h>

namespace lge
{
	//
	// Big 4
	//

	// Default Ctor (0,0,0,1)
	Quat::Quat() :
		_qx(0.0f),
		_qy(0.0f),
		_qz(0.0f),
		_qw(1.0f)
	{
	}

	// Destructor
	Quat::~Quat()
	{
	}

	// Copy Ctor
	Quat::Quat(const Quat& rhs) :
		_m(rhs._m)
	{
	}

	// Assignment Overload
	Quat& Quat::operator=(const Quat& rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}

		this->_m = rhs._m;

		return *this;
	}


	// All Elements Ctor
	Quat::Quat(const float qx, const float qy, const float qz, const float qw) :
		_qx(qx),
		_qy(qy),
		_qz(qz),
		_qw(qw)
	{
	}


	// The __m128 Ctor
	Quat::Quat(const __m128& m) :
		_m(m)
	{
	}

	// Imaginary Vector + Real Scalar Ctor
	Quat::Quat(const Vect& qv, const float qs) :
		_qx(qv.x()),
		_qy(qv.y()),
		_qz(qv.z()),
		_qw(qs)
	{
	}

	// Rotation Matrix Ctor (must be rotation matrix)
	Quat::Quat(const Matrix& matRot)
	{
		this->set(matRot);
	}

	// Special Type Ctor (Identity or Zero)
	Quat::Quat(const MatrixSpecialType type) :
		_qx(0.0f),
		_qy(0.0f),
		_qz(0.0f),
		_qw(1.0f)
	{
		// Initialize IDENTITY orientation by default.
		// Only change one value if asking for ZERO orientation
		if (type == MatrixSpecialType::ZERO)
		{
			this->_qw = 0.0f;
		}
	}


	// All Euler Angles Ctor
	Quat::Quat(const Rot3AxisType type, const float xRot, const float yRot, const float zRot)
	{
		type;

		const Quat hx(RotType::ROT_X, xRot);
		const Quat hy(RotType::ROT_Y, yRot);
		const Quat hz(RotType::ROT_Z, zRot);

		this->operator=(hx * hy * hz);
	}


	// One Euler Angle Ctor
	Quat::Quat(const RotType axis, const float rotation)
	{
		this->set(axis, rotation);
	}

	// Angle-Axis Ctor
	Quat::Quat(const RotAxisAngleType type, const Vect& rotationAxis, const float angle)
	{
		this->set(type, rotationAxis, angle);
	}

	// Orientation Ctor
	Quat::Quat(const RotOrientType orientation, const Vect& dofForward, const Vect& up) :
		Quat(Matrix(orientation, dofForward, up))
	{
	}








	// Square bracket getters
	const float Quat::operator[](const x_enum x) const
	{
		x;
		return this->_qx;
	}

	// Square bracket getters
	const float Quat::operator[](const y_enum y) const
	{
		y;
		return this->_qy;
	}

	// Square bracket getters
	const float Quat::operator[](const z_enum z) const
	{
		z;
		return this->_qz;
	}

	// Square bracket getters
	const float Quat::operator[](const w_enum w) const
	{
		w;
		return this->_qw;
	}


	// Function-based getters
	const float Quat::x() const
	{
		return this->_qx;
	}

	// Function-based getters
	const float Quat::y() const
	{
		return this->_qy;
	}

	// Function-based getters
	const float Quat::z() const
	{
		return this->_qz;
	}

	// Function-based getters
	const float Quat::w() const
	{
		return this->_qw;
	}

	// Get the imaginary vectory portion of this Quaternion (v[4] becomes 1)
	void Quat::getVect(Vect& v) const
	{
		v.x() = this->_qx;
		v.y() = this->_qy;
		v.z() = this->_qz;
		v.w() = 1.0f;
	}

	// Get the angle of this Quaternion
	const float Quat::getAngle() const
	{
		return 2.0f * acosf(this->_qw);
	}

	// Get the axis of rotation for this Quaternion
	void Quat::getAxis(Vect& axis) const
	{
		this->getVect(axis);
		//axis /= sinf(acosf(this->_qw));
	}






	// Square bracker setters
	float& Quat::operator[](const x_enum x)
	{
		x;
		return this->_qx;
	}

	// Square bracker setters
	float& Quat::operator[](const y_enum y)
	{
		y;
		return this->_qy;
	}

	// Square bracker setters
	float& Quat::operator[](const z_enum z)
	{
		z;
		return this->_qz;
	}

	// Square bracker setters
	float& Quat::operator[](const w_enum w)
	{
		w;
		return this->_qw;
	}


	// Function-based setters
	float& Quat::x()
	{
		return this->_qx;
	}

	// Function-based setters
	float& Quat::y()
	{
		return this->_qy;
	}

	// Function-based setters
	float& Quat::z()
	{
		return this->_qz;
	}

	// Function-based setters
	float& Quat::w()
	{
		return this->_qw;
	}


	// Multi-float setter
	void Quat::set(const float x, const float y, const float z, const float w)
	{
		this->_qx = x;
		this->_qy = y;
		this->_qz = z;
		this->_qw = w;
	}


	// Imaginary Vector + Real Scalar setter
	void Quat::set(const Vect& qv, const float qs)
	{
		this->_qx = qv.x();
		this->_qy = qv.y();
		this->_qz = qv.z();
		this->_qw = qs;
	}


	// Rotation Matrix setter (must be Rotation matrix)
	void Quat::set(const Matrix& M)
	{
		float tr = M.m0() + M.m5() + M.m10();
		float S;
		if (tr > 0.0f)
		{
			S = 2 * sqrtf(tr + 1.0f);
			this->_qw = 0.25f * S;
			this->_qx = -(M.m9() - M.m6()) / S;
			this->_qy = -(M.m2() - M.m8()) / S;
			this->_qz = -(M.m4() - M.m1()) / S;
		}
		else if ((M.m0() > M.m5()) && (M.m0() > M.m10()))
		{
			S = 2 * sqrtf(1.0f + M.m0() - M.m5() - M.m10());
			this->_qw = -(M.m9() - M.m6()) / S;
			this->_qx = 0.25f * S;
			this->_qy = (M.m1() + M.m4()) / S;
			this->_qz = (M.m2() + M.m8()) / S;
		}
		else if (M.m5() > M.m10())
		{
			S = 2 * sqrtf(1.0f + M.m5() - M.m0() - M.m10());
			this->_qw = -(M.m2() - M.m8()) / S;
			this->_qx = (M.m1() + M.m4()) / S;
			this->_qy = 0.25f * S;
			this->_qz = (M.m6() + M.m9()) / S;
		}
		else
		{
			S = 2 * sqrtf(1.0f + M.m10() - M.m0() - M.m5());
			this->_qw = -(M.m4() - M.m1()) / S;
			this->_qx = (M.m2() + M.m8()) / S;
			this->_qy = (M.m6() + M.m9()) / S;
			this->_qz = 0.25f * S;
		}
	}


	// Special Type setter (Identity or Zero)
	void Quat::set(const MatrixSpecialType type)
	{
		this->_qx = 0.0f;
		this->_qy = 0.0f;
		this->_qz = 0.0f;
		this->_qw = 1.0f;

		if (type == MatrixSpecialType::ZERO)
		{
			this->_qw = 0.0f;
		}
	}


	// One Euler Angle setter
	void Quat::set(const RotType axis, const float rotation)
	{
		Vect rotAxis;

		switch (axis)
		{
			case RotType::ROT_X:
				rotAxis = Vect(1.0f, 0.0f, 0.0f);
				break;
			case RotType::ROT_Y:
				rotAxis = Vect(0.0f, 1.0f, 0.0f);
				break;
			case RotType::ROT_Z:
				rotAxis = Vect(0.0f, 0.0f, 1.0f);
				break;
			default:
				assert(false);
				break;
		}

		this->set(RotAxisAngleType::ROT_AXIS_ANGLE, rotAxis, rotation);
	}


	// All Euler Angles Setter
	void Quat::set(const Rot3AxisType type, const float xRot, const float yRot, const float zRot)
	{
		type;

		const Quat hx(RotType::ROT_X, xRot);
		const Quat hy(RotType::ROT_Y, yRot);
		const Quat hz(RotType::ROT_Z, zRot);

		this->operator=(hx * hy * hz);
	}

	// Angle-Axis setter
	void Quat::set(const RotAxisAngleType type, const Vect& rotationAxis, const float angle)
	{
		type;

		const Vect axisNormalized = rotationAxis.getNorm();
		const float halfTheta = angle / 2.0f;
		const float sinHalfTheta = sinf(halfTheta);

		this->_qx = axisNormalized.x() * sinHalfTheta;
		this->_qy = axisNormalized.y() * sinHalfTheta;
		this->_qz = axisNormalized.z() * sinHalfTheta;
		this->_qw = cosf(halfTheta);
	}

	// Orientation setter
	void Quat::set(const RotOrientType orientation, const Vect& dofForward, const Vect& up)
	{
		// WARNING: Slow!
		this->set(Matrix(orientation, dofForward, up));
	}

	// Set the imaginary vector portion of this Quaternion
	void Quat::setVect(const Vect& qv)
	{
		this->_qx = qv.x();
		this->_qy = qv.y();
		this->_qz = qv.z();
	}





	//
	// Operator Overloads
	//


	// Convert a Rotational Matrix into a Quaternion
	Quat& Quat::operator=(const Matrix& rhs)
	{
		this->set(rhs);
		return *this;
	}

	// Quaternion x Matrix
	const Quat Quat::operator*(const Matrix& rhs) const
	{
		return this->operator*(Quat(rhs));
	}

	// Quaternion x Matrix
	Quat& Quat::operator*=(const Matrix& rhs)
	{
		this->operator*=(Quat(rhs));
		return *this;
	}



	// Unary + operator overload
	const Quat Quat::operator+() const
	{
		return *this;
	}

	// Add two Quaternions together
	const Quat Quat::operator+(const Quat& rhs) const
	{
		return Quat(_mm_add_ps(this->_m, rhs._m));
	}

	// Add two Quaternions together
	Quat& Quat::operator+=(const Quat& rhs)
	{
		this->_qx += rhs._qx;
		this->_qy += rhs._qy;
		this->_qz += rhs._qz;
		this->_qw += rhs._qw;

		return *this;
	}

	// Scalar addition across every element of the Quat
	const Quat Quat::operator+(const float rhs) const
	{
		return Quat(_mm_add_ps(this->_m, _mm_set1_ps(rhs)));
	}

	// Scalar addition across every element of the Quat
	Quat& Quat::operator+=(const float rhs)
	{
		this->_qx += rhs;
		this->_qy += rhs;
		this->_qz += rhs;
		this->_qw += rhs;

		return *this;
	}

	// FRIEND
	// Scalar addition across every element of the Quat
	const Quat operator+(const float scalarLhs, const Quat& quatRhs)
	{
		return Quat(_mm_add_ps(quatRhs._m, _mm_set1_ps(scalarLhs)));
	}



	// Negation operator overload
	const Quat Quat::operator-() const
	{
		return Quat(_mm_mul_ps(this->_m, _mm_set1_ps(-1.0f)));
	}

	// Subtract two Quaternions together
	const Quat Quat::operator-(const Quat& rhs) const
	{
		return Quat(_mm_sub_ps(this->_m, rhs._m));
	}

	// Subtract two Quaternions together
	Quat& Quat::operator-=(const Quat& rhs)
	{
		this->_qx -= rhs._qx;
		this->_qy -= rhs._qy;
		this->_qz -= rhs._qz;
		this->_qw -= rhs._qw;

		return *this;
	}

	// Scalar subtraction across every element of the Quat
	const Quat Quat::operator-(const float rhs) const
	{
		return Quat(_mm_sub_ps(this->_m, _mm_set1_ps(rhs)));
	}

	// Scalar subtraction across every element of the Quat
	Quat& Quat::operator-=(const float rhs)
	{
		this->_qx -= rhs;
		this->_qy -= rhs;
		this->_qz -= rhs;
		this->_qw -= rhs;

		return *this;
	}

	// FRIEND
	// Scalar subtraction across every element of the Quat
	const Quat operator-(const float scalarLhs, const Quat& quatRhs)
	{
		return Quat(_mm_sub_ps(_mm_set1_ps(scalarLhs), quatRhs._m));
	}



	// Quaternion product (NOT dot product)
	const Quat Quat::operator*(const Quat& rhs) const
	{
		// q      ==  Vect qv + float qs
		// qs     ==  q.w()
		// q * p  ==  qv.cross(pv) + (qs * pv) + (ps * qv) + (ps * qs) - pv.dot(qv) 

		const Vect qv(rhs._m);
		const Vect pv(this->_m);
		const float qs = rhs._qw;
		const float ps = this->_qw;

		return Quat(qv.cross(pv) + pv.getScaled(qs) + qv.getScaled(ps), (ps*qs) - pv.dot(qv));
	}

	// Quaternion product (NOT dot product)
	Quat& Quat::operator*=(const Quat& rhs)
	{
		const Vect qv(rhs._m);
		const Vect pv(this->_m);
		const float qs = rhs._qw;
		const float ps = this->_qw;

		this->set(qv.cross(pv) + pv.getScaled(qs) + qv.getScaled(ps), (ps*qs) - pv.dot(qv));

		return *this;
	}

	// Scalar multiplication across every element of the Quat
	const Quat Quat::operator*(const float rhs) const
	{
		return Quat(_mm_mul_ps(this->_m, _mm_set1_ps(rhs)));
	}

	// Scalar multiplication across every element of the Quat
	Quat& Quat::operator*=(const float rhs)
	{
		this->_qx *= rhs;
		this->_qy *= rhs;
		this->_qz *= rhs;
		this->_qw *= rhs;

		return *this;
	}

	// FRIEND
	// Scalar multiplication across every element of the Quat
	const Quat operator*(const float scalarLhs, const Quat& quatRhs)
	{
		return Quat(_mm_mul_ps(quatRhs._m, _mm_set1_ps(scalarLhs)));
	}



	// Divide the elements of two Quaternions together
	const Quat Quat::operator/(const Quat& rhs) const
	{
		return Quat(_mm_div_ps(this->_m, rhs._m));
	}

	// Divide the elements two Quaternions together
	Quat& Quat::operator/=(const Quat& rhs)
	{
		this->_qx /= rhs._qx;
		this->_qy /= rhs._qy;
		this->_qz /= rhs._qz;
		this->_qw /= rhs._qw;

		return *this;
	}

	// Scalar division across every element of the Quat
	const Quat Quat::operator/(const float rhs) const
	{
		return Quat(_mm_div_ps(this->_m, _mm_set1_ps(rhs)));
	}

	// Scalar division across every element of the Quat
	Quat& Quat::operator/=(const float rhs)
	{
		this->_qx /= rhs;
		this->_qy /= rhs;
		this->_qz /= rhs;
		this->_qw /= rhs;

		return *this;
	}

	// FRIEND
	// Scalar division across every element of the Quat
	const Quat operator/(const float scalarLhs, const Quat& quatRhs)
	{
		return Quat(_mm_div_ps(_mm_set1_ps(scalarLhs), quatRhs._m));
	}





	//
	// Other Math Operators
	//

	// Calculate the conjugate of this Quaternion
	const Quat Quat::getConj() const
	{
		return Quat(-_qx, -_qy, -_qz, _qw);
	}

	// Conjugate yourself
	void Quat::conj()
	{
		this->_qx *= -1.0f;
		this->_qy *= -1.0f;
		this->_qz *= -1.0f;
	}

	// Calculate the transpose of this Quaternion (same as conjugate)
	const Quat Quat::getT() const
	{
		return Quat(-_qx, -_qy, -_qz, _qw);
	}

	// Transpose yourself
	void Quat::T()
	{
		this->_qx *= -1.0f;
		this->_qy *= -1.0f;
		this->_qz *= -1.0f;
	}

	// Calculate the length of this Quaternion
	const float Quat::mag() const
	{
		return sqrtf(this->magSquared());
	}

	// Calculate the squared-length of this Quaternion (faster than mag())
	const float Quat::magSquared() const
	{
		return this->dot(*this);
	}

	// Calculate 1 over the length of this Quaternion
	const float Quat::invMag() const
	{
		return 1.0f / this->mag();
	}

	// Calculate the normalized version of this Quaternion AND normalize yourself
	const Quat Quat::norm()
	{
		this->operator/=(this->mag());
		return *this;
	}

	// Only calculate the normalized version of this Quaternion without normalizing this Quaternion
	const Quat Quat::getNorm() const
	{
		return Quat(this->operator/(this->mag()));
	}

	// Get the inverse Quaternion of this Quaternion
	const Quat Quat::getInv() const
	{
		return this->getConj() / this->magSquared();
	}

	// Invert yourself
	void Quat::inv()
	{
		this->conj();
		this->operator/=(this->magSquared());
	}

	// Do linear operation of vector with this quaternion q (as in "q*vq", where q* is the conjugate)
	void Quat::Lqcvq(const Vect& v, Vect& answer) const
	{
		const Vect qv(this->_qx, this->_qy, this->_qz, 1.0f);

		answer = (2.0f*_qw)*(qv.cross(v)) + ((_qw*_qw - qv.dot(qv)) * v) + (2.0f * qv.dot(v))*qv;
	}

	// Do linear operation of vector with this quaternion q (as in "qvq*", where q* is the conjugate)
	void Quat::Lqvqc(const Vect& v, Vect& answer) const
	{
		const Vect qv(this->_qx, this->_qy, this->_qz, 1.0f);

		answer = (2.0f*_qw)*(v.cross(qv)) + ((_qw*_qw - qv.dot(qv)) * v) + (2.0f * qv.dot(v))*qv;
	}

	// Quaternion Dot Multiplication (q1 dot q2)
	const float Quat::dot(const Quat& rhs) const
	{
		return this->_qx * rhs._qx + this->_qy * rhs._qy + this->_qz * rhs._qz + this->_qw * rhs._qw;
	}

	// Multiply the each element of one Quat by each corresponding element of the other Quat (NOT quat product)
	const Quat Quat::multByElement(const Quat& rhs) const
	{
		return Quat(_mm_mul_ps(this->_m, rhs._m));
	}

	// Get the euler angle representation of this Quaternion
	const Vect Quat::convertToEulerAngles() const
	{
		return Vect(atan2(2.0f * (_qw * _qx + _qy * _qz), 1 - (2.0f *(_qx*_qx + _qy*_qy))),
					asin( 2.0f * (_qw * _qy - _qz * _qx) ),
					atan2(2.0f * (_qw * _qz + _qx * _qy), 1 - (2.0f *(_qy*_qy + _qz*_qz))) 
				);
	}



	//
	// Boolean Operators
	//

	// Is this Quaternion normalized?
	const bool Quat::isNormalized(const float epsilon) const
	{
		return Util::isEqual(this->mag(), 1.0f, epsilon);
	}

	// Are the Quaterinions the same?
	const bool Quat::isEqual(const Quat& other, const float epsilon) const
	{
		if (Util::isEqual(this->_qx, other._qx, epsilon))
		{
			if (Util::isEqual(this->_qy, other._qy, epsilon))
			{
				if (Util::isEqual(this->_qz, other._qz, epsilon))
				{
					if (Util::isEqual(this->_qw, other._qw, epsilon))
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	// If the other Quat were made negative, would that negative equal this Quaternion?
	const bool Quat::isNegEqual(const Quat& other, const float epsilon) const
	{
		const Quat neg(-other);
		return this->isEqual(neg, epsilon);
	}

	// Can this Quat rotate by theta and the other Quat rotate by -theta and they both performed the same rotation?
	const bool Quat::isEquivalent(const Quat& other, const float epsilon) const
	{
		const bool isEquiv = this->isEqual(other, epsilon) || this->isNegEqual(other, epsilon);
		return isEquiv;
	}

	// If the other Quat were made into its conjugate, would that conjugate equal this Quaternion?
	const bool Quat::isConjugateEqual(const Quat& other, const float epsilon) const
	{
		const Quat conju(other.getConj());
		return this->isEqual(conju, epsilon);
	}

	// Is this Quaternion an identity quaternion? (similar to identity matrix)
	const bool Quat::isIdentity(const float epsilon)
	{
		const Quat identity(IDENTITY);
		return this->isEqual(identity, epsilon);
	}

	// Is this Quaternion zero-ed out?
	const bool Quat::isZero(const float epsilon)
	{
		const Quat zero(ZERO);
		return this->isEqual(zero, epsilon);
	}

}