
//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "UnitTest.h"
#include "MathEngine.h"
using namespace lge;
#define eq	Util::isEqual 


//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------
TEST( Matrix_default_constructor, matix_tests )
{
	Matrix M;

	CHECK( M[m0] == 0.0f );
	CHECK( M[m1] == 0.0f );
	CHECK( M[m2] == 0.0f );
	CHECK( M[m3] == 0.0f );
	CHECK( M[m4] == 0.0f );
	CHECK( M[m5] == 0.0f );
	CHECK( M[m6] == 0.0f );	
	CHECK( M[m7] == 0.0f );
	CHECK( M[m8] == 0.0f );
	CHECK( M[m9] == 0.0f );
	CHECK( M[m10] == 0.0f );
	CHECK( M[m11] == 0.0f );
	CHECK( M[m12] == 0.0f );
	CHECK( M[m13] == 0.0f );
	CHECK( M[m14] == 0.0f );
	CHECK( M[m15] == 0.0f );

}

TEST( Matrix_vector_constructor, matix_tests )
{
	Vect V0(1.0f,2.0f,3.0f,4.0f);
	Vect V1(7.0f,6.0f,5.0f,3.0f);
	Vect V2(-4.0f,-2.0f,-1.0f,-4.0f);
	Vect V3(9.0f,-7.0f,-2.0f,5.0f);

	CHECK( V0[x] == 1.0f );
	CHECK( V0[y] == 2.0f );
	CHECK( V0[z] == 3.0f );
	CHECK( V0[w] == 4.0f );
	CHECK( V1[x] == 7.0f );
	CHECK( V1[y] == 6.0f );
	CHECK( V1[z] == 5.0f );	
	CHECK( V1[w] == 3.0f );
	CHECK( V2[x] == -4.0f );
	CHECK( V2[y] == -2.0f );
	CHECK( V2[z] == -1.0f );
	CHECK( V2[w] == -4.0f );
	CHECK( V3[x] == 9.0f );
	CHECK( V3[y] == -7.0f );
	CHECK( V3[z] == -2.0f );
	CHECK( V3[w] == 5.0f );

	Matrix M(V0,V1,V2,V3);

	CHECK( M[m0] == 1.0f );
	CHECK( M[m1] == 2.0f );
	CHECK( M[m2] == 3.0f );
	CHECK( M[m3] == 4.0f );
	CHECK( M[m4] == 7.0f );
	CHECK( M[m5] == 6.0f );
	CHECK( M[m6] == 5.0f );	
	CHECK( M[m7] == 3.0f );
	CHECK( M[m8] == -4.0f );
	CHECK( M[m9] == -2.0f );
	CHECK( M[m10] == -1.0f );
	CHECK( M[m11] == -4.0f );
	CHECK( M[m12] == 9.0f );
	CHECK( M[m13] == -7.0f );
	CHECK( M[m14] == -2.0f );
	CHECK( M[m15] == 5.0f );
}

TEST( Matrix_copy_constructor, matix_tests )
{
	Vect V0(1.0f,2.0f,3.0f,4.0f);
	Vect V1(7.0f,6.0f,5.0f,3.0f);
	Vect V2(-4.0f,-2.0f,-1.0f,-4.0f);
	Vect V3(9.0f,-7.0f,-2.0f,5.0f);

	CHECK( V0[x] == 1.0f );
	CHECK( V0[y] == 2.0f );
	CHECK( V0[z] == 3.0f );
	CHECK( V0[w] == 4.0f );
	CHECK( V1[x] == 7.0f );
	CHECK( V1[y] == 6.0f );
	CHECK( V1[z] == 5.0f );	
	CHECK( V1[w] == 3.0f );
	CHECK( V2[x] == -4.0f );
	CHECK( V2[y] == -2.0f );
	CHECK( V2[z] == -1.0f );
	CHECK( V2[w] == -4.0f );
	CHECK( V3[x] == 9.0f );
	CHECK( V3[y] == -7.0f );
	CHECK( V3[z] == -2.0f );
	CHECK( V3[w] == 5.0f );

	Matrix M(V0,V1,V2,V3);

	Matrix N( M );

	CHECK( N[m0] == 1.0f );
	CHECK( N[m1] == 2.0f );
	CHECK( N[m2] == 3.0f );
	CHECK( N[m3] == 4.0f );
	CHECK( N[m4] == 7.0f );
	CHECK( N[m5] == 6.0f );
	CHECK( N[m6] == 5.0f );	
	CHECK( N[m7] == 3.0f );
	CHECK( N[m8] == -4.0f );
	CHECK( N[m9] == -2.0f );
	CHECK( N[m10] == -1.0f );
	CHECK( N[m11] == -4.0f );
	CHECK( N[m12] == 9.0f );
	CHECK( N[m13] == -7.0f );
	CHECK( N[m14] == -2.0f );
	CHECK( N[m15] == 5.0f );

	CHECK( M[m0] == 1.0f );
	CHECK( M[m1] == 2.0f );
	CHECK( M[m2] == 3.0f );
	CHECK( M[m3] == 4.0f );
	CHECK( M[m4] == 7.0f );
	CHECK( M[m5] == 6.0f );
	CHECK( M[m6] == 5.0f );	
	CHECK( M[m7] == 3.0f );
	CHECK( M[m8] == -4.0f );
	CHECK( M[m9] == -2.0f );
	CHECK( M[m10] == -1.0f );
	CHECK( M[m11] == -4.0f );
	CHECK( M[m12] == 9.0f );
	CHECK( M[m13] == -7.0f );
	CHECK( M[m14] == -2.0f );
	CHECK( M[m15] == 5.0f );
}

TEST( Destructor_constuctor, matrix_tests )
{
	Vect V0(1.0f,2.0f,3.0f,4.0f);
	Vect V1(7.0f,6.0f,5.0f,3.0f);
	Vect V2(-4.0f,-2.0f,-1.0f,-4.0f);
	Vect V3(9.0f,-7.0f,-2.0f,5.0f);

	Matrix M(V0,V1,V2,V3);

	Matrix *pM = &M;
	pM->~Matrix();
	CHECK(1);
}





TEST( MatrixRotAxisAngle, matrix_tests )
{
	// Axis and Angle Type Constructor:
	Vect  v11( 2.0f, 53.0f, 24.0f);
	Matrix m54( ROT_AXIS_ANGLE, v11, MATH_PI3 );
			
	// => Vect  v11( 2.0f, 53.0f, 24.0f); \n"););
	// => Matrix m54(ROT_AXIS_ANGLE, v11, MATH_PI3 );\n"););
	CHECK( eq(m54[m0], 0.5005f, MATH_TOLERANCE) );
	CHECK( eq(m54[m1], 0.3726f, MATH_TOLERANCE) );
	CHECK( eq(m54[m2],-0.7813f, MATH_TOLERANCE) );
	CHECK( m54[m3] == 0.0f );
	CHECK( eq(m54[m4],-0.3413f, MATH_TOLERANCE) );
	CHECK( eq(m54[m5], 0.9144f, MATH_TOLERANCE) );
	CHECK( eq(m54[m6], 0.2174f, MATH_TOLERANCE) );
	CHECK( (m54[m7] == 0.0f) );
	CHECK( eq(m54[m8], 0.7955f, MATH_TOLERANCE) );
	CHECK( eq(m54[m9], 0.1579f, MATH_TOLERANCE) );
	CHECK( eq(m54[m10], 0.5849f, MATH_TOLERANCE) );
	CHECK( (m54[m11] == 0.0f) );
	CHECK( (m54[m12] == 0.0f) );
	CHECK( (m54[m13] == 0.0f) );
	CHECK( (m54[m14] == 0.0f) );
	CHECK( (m54[m15] == 1.0f) );
}



TEST( MatrixRotOrient, matrix_tests )
{
	// Orientation Type Constructor:
	Vect  v15( 2.0f, 53.0f, 24.0f);
	Vect  v16( 0.0f, -24.0f, 53.0f);
	Matrix m56(ROT_ORIENT, v15, v16 );

	CHECK( eq(m56[m0],-0.9994f, MATH_TOLERANCE) );
	CHECK( eq(m56[m1], 0.0313f, MATH_TOLERANCE) );
	CHECK( eq(m56[m2], 0.0142f, MATH_TOLERANCE) );
	CHECK( (m56[m3] == 0.0f) );
	CHECK( eq(m56[m4], 0.0000f, MATH_TOLERANCE) );
	CHECK( eq(m56[m5],-0.4125f, MATH_TOLERANCE) );
	CHECK( eq(m56[m6], 0.9110f, MATH_TOLERANCE) );
	CHECK( (m56[m7] == 0.0f) );
	CHECK( eq(m56[m8], 0.0344f, MATH_TOLERANCE) );
	CHECK( eq(m56[m9], 0.9104f, MATH_TOLERANCE) );
	CHECK( eq(m56[m10], 0.4123f, MATH_TOLERANCE) );
	CHECK( (m56[m11] == 0.0f) );
	CHECK( (m56[m12] == 0.0f) );
	CHECK( (m56[m13] == 0.0f) );
	CHECK( (m56[m14] == 0.0f) );
	CHECK( (m56[m15] == 1.0f) );
}

TEST( MatrixRotInverseOrient, matrix_tests)
{
	// Orientation Type Constructor:
	Vect  v17( 2.0f, 53.0f, 24.0f);
	Vect  v18( 0.0f, -24.0f, 53.0f);
	Matrix m57(ROT_INVERSE_ORIENT, v17, v18 );

	CHECK( eq(m57[m0],-0.9994f, MATH_TOLERANCE) );
	CHECK( eq(m57[m1], 0.0000f, MATH_TOLERANCE) );
	CHECK( eq(m57[m2], 0.0344f, MATH_TOLERANCE) );
	CHECK( (m57[m3] == 0.0f) );
	CHECK( eq(m57[m4], 0.0313f, MATH_TOLERANCE) );
	CHECK( eq(m57[m5],-0.4125f, MATH_TOLERANCE) );
	CHECK( eq(m57[m6], 0.9104f, MATH_TOLERANCE) );
	CHECK( (m57[m7] == 0.0f) );
	CHECK( eq(m57[m8], 0.0142f, MATH_TOLERANCE) );
	CHECK( eq(m57[m9], 0.9110f, MATH_TOLERANCE) );
	CHECK( eq(m57[m10], 0.4123f, MATH_TOLERANCE) );
	CHECK( (m57[m11] == 0.0f) );
	CHECK( (m57[m12] == 0.0f) );
	CHECK( (m57[m13] == 0.0f) );
	CHECK( (m57[m14] == 0.0f) );
	CHECK( (m57[m15] == 1.0f) );
}


TEST( MatrixQuaternion, matrix_tests)
{
	// Quaternion Type Constructor:
	Matrix Rxyz1(ROT_XYZ, MATH_PI3, MATH_5PI8, MATH_PI4 );

	Quat	Qxyz1(Rxyz1);
	Matrix Mxyz1( Qxyz1 );

	CHECK( eq(Mxyz1[m0],-0.2705f,MATH_TOLERANCE) );
	CHECK( eq(Mxyz1[m1],-0.2705f,MATH_TOLERANCE) );
	CHECK( eq(Mxyz1[m2],-0.9238f,MATH_TOLERANCE) );
	CHECK( (Mxyz1[m3] == 0.0f) );
	CHECK( eq(Mxyz1[m4], 0.2122f,MATH_TOLERANCE) );
	CHECK( eq(Mxyz1[m5], 0.9193f,MATH_TOLERANCE) );
	CHECK( eq(Mxyz1[m6],-0.3314f,MATH_TOLERANCE) );
	CHECK( (Mxyz1[m7] == 0.0f) );
	CHECK( eq(Mxyz1[m8], 0.9390f,MATH_TOLERANCE) );
	CHECK( eq(Mxyz1[m9],-0.2857f,MATH_TOLERANCE) );
	CHECK( eq(Mxyz1[m10],-0.1913f,MATH_TOLERANCE) );
	CHECK( (Mxyz1[m11] == 0.0f) );
	CHECK( (Mxyz1[m12] == 0.0f) );
	CHECK( (Mxyz1[m13] == 0.0f) );
	CHECK( (Mxyz1[m14] == 0.0f) );
	CHECK( (Mxyz1[m15] == 1.0f) );
}