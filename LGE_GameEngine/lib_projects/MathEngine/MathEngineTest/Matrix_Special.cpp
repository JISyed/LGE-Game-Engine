
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
TEST( Matrix_Identity, matrix_tests )
{

	Matrix A(IDENTITY);

	CHECK( A[m0] == 1.0f );
	CHECK( A[m1] == 0.0f );
	CHECK( A[m2] == 0.0f );
	CHECK( A[m3] == 0.0f );
	CHECK( A[m4] == 0.0f );
	CHECK( A[m5] == 1.0f );
	CHECK( A[m6] == 0.0f );	
	CHECK( A[m7] == 0.0f );
	CHECK( A[m8] == 0.0f );
	CHECK( A[m9] == 0.0f );
	CHECK( A[m10] == 1.0f );
	CHECK( A[m11] == 0.0f );
	CHECK( A[m12] == 0.0f );
	CHECK( A[m13] == 0.0f );
	CHECK( A[m14] == 0.0f );
	CHECK( A[m15] == 1.0f );
}

TEST( Matrix_Zero, matrix_tests )
{

	Matrix A(ZERO);

	CHECK( A[m0] == 0.0f );
	CHECK( A[m1] == 0.0f );
	CHECK( A[m2] == 0.0f );
	CHECK( A[m3] == 0.0f );
	CHECK( A[m4] == 0.0f );
	CHECK( A[m5] == 0.0f );
	CHECK( A[m6] == 0.0f );	
	CHECK( A[m7] == 0.0f );
	CHECK( A[m8] == 0.0f );
	CHECK( A[m9] == 0.0f );
	CHECK( A[m10] == 0.0f );
	CHECK( A[m11] == 0.0f );
	CHECK( A[m12] == 0.0f );
	CHECK( A[m13] == 0.0f );
	CHECK( A[m14] == 0.0f );
	CHECK( A[m15] == 0.0f );
}

TEST( Matrix_Trans, matrix_tests )
{

	Matrix A(TRANS, 2.0f, 3.0f, 4.0f);

	CHECK( A[m0] == 1.0f );
	CHECK( A[m1] == 0.0f );
	CHECK( A[m2] == 0.0f );
	CHECK( A[m3] == 0.0f );
	CHECK( A[m4] == 0.0f );
	CHECK( A[m5] == 1.0f );
	CHECK( A[m6] == 0.0f );	
	CHECK( A[m7] == 0.0f );
	CHECK( A[m8] == 0.0f );
	CHECK( A[m9] == 0.0f );
	CHECK( A[m10] == 1.0f );
	CHECK( A[m11] == 0.0f );
	CHECK( A[m12] == 2.0f );
	CHECK( A[m13] == 3.0f );
	CHECK( A[m14] == 4.0f );
	CHECK( A[m15] == 1.0f );
}


TEST(Matrix_Trans_Vect, matrix_tests)
{
	Vect vTrans(2.0f, 3.0f, 4.0f);
	Matrix A(TRANS, vTrans);

	CHECK( A[m0] == 1.0f );
	CHECK( A[m1] == 0.0f );
	CHECK( A[m2] == 0.0f );
	CHECK( A[m3] == 0.0f );
	CHECK( A[m4] == 0.0f );
	CHECK( A[m5] == 1.0f );
	CHECK( A[m6] == 0.0f );	
	CHECK( A[m7] == 0.0f );
	CHECK( A[m8] == 0.0f );
	CHECK( A[m9] == 0.0f );
	CHECK( A[m10] == 1.0f );
	CHECK( A[m11] == 0.0f );
	CHECK( A[m12] == 2.0f );
	CHECK( A[m13] == 3.0f );
	CHECK( A[m14] == 4.0f );
	CHECK( A[m15] == 1.0f );
}

TEST( Matrix_SCALE, matrix_tests )
{

	Matrix A(SCALE, 2.0f, 3.0f, 4.0f);

	CHECK( A[m0] == 2.0f );
	CHECK( A[m1] == 0.0f );
	CHECK( A[m2] == 0.0f );
	CHECK( A[m3] == 0.0f );
	CHECK( A[m4] == 0.0f );
	CHECK( A[m5] == 3.0f );
	CHECK( A[m6] == 0.0f );	
	CHECK( A[m7] == 0.0f );
	CHECK( A[m8] == 0.0f );
	CHECK( A[m9] == 0.0f );
	CHECK( A[m10] == 4.0f );
	CHECK( A[m11] == 0.0f );
	CHECK( A[m12] == 0.0f );
	CHECK( A[m13] == 0.0f );
	CHECK( A[m14] == 0.0f );
	CHECK( A[m15] == 1.0f );
}


TEST(Matrix_SCALE_Vect, matrix_tests)
{
	Vect vScale(2.0f, 3.0f, 4.0f);
	Matrix A(SCALE, vScale);

	CHECK( A[m0] == 2.0f );
	CHECK( A[m1] == 0.0f );
	CHECK( A[m2] == 0.0f );
	CHECK( A[m3] == 0.0f );
	CHECK( A[m4] == 0.0f );
	CHECK( A[m5] == 3.0f );
	CHECK( A[m6] == 0.0f );	
	CHECK( A[m7] == 0.0f );
	CHECK( A[m8] == 0.0f );
	CHECK( A[m9] == 0.0f );
	CHECK( A[m10] == 4.0f );
	CHECK( A[m11] == 0.0f );
	CHECK( A[m12] == 0.0f );
	CHECK( A[m13] == 0.0f );
	CHECK( A[m14] == 0.0f );
	CHECK( A[m15] == 1.0f );
}


TEST( RotX, matrix_tests )
{
	// Rot_X Type Constructor:
	Matrix Rx(ROT_X, 1.0471975512f );	

	CHECK( Rx[m0] ==  1.0f );
	CHECK( Rx[m1] ==  0.0f );
	CHECK( Rx[m2] ==  0.0f );
	CHECK( Rx[m3] ==  0.0f );
	CHECK( Rx[m4] ==  0.0f );
	CHECK( eq(Rx[m5],  0.5f,  MATH_TOLERANCE) );
	CHECK( eq(Rx[m6], 0.866f, MATH_TOLERANCE) );
	CHECK( Rx[m7] == 0.0f );
	CHECK( Rx[m8] == 0.0f );
	CHECK( eq(Rx[m9],-0.866f, MATH_TOLERANCE) );
	CHECK( eq(Rx[m10],0.5f  , MATH_TOLERANCE) );
	CHECK( Rx[m11] == 0.0f );
	CHECK( Rx[m12] == 0.0f );
	CHECK( Rx[m13] == 0.0f );
	CHECK( Rx[m14] == 0.0f );
	CHECK( Rx[m15] == 1.0f );
}


TEST( RotY, matrix_tests )
{
	Matrix Ry(ROT_Y,  1.0471975512f );	

	CHECK( eq(Ry[m0],0.5f,  MATH_TOLERANCE) );
	CHECK( Ry[m1] ==  0.0f );
	CHECK( eq(Ry[m2],-0.866f,MATH_TOLERANCE) );
	CHECK( Ry[m3] == 0.0f );
	CHECK( Ry[m4] == 0.0f );
	CHECK( Ry[m5] == 1.0f );
	CHECK( Ry[m6] == 0.0f );
	CHECK( Ry[m7] == 0.0f );
	CHECK( eq(Ry[m8],0.866f,MATH_TOLERANCE) );
	CHECK( Ry[m9] ==  0.0f );
	CHECK( eq(Ry[m10],0.5f,   MATH_TOLERANCE) );
	CHECK( Ry[m11] == 0.0f );
	CHECK( Ry[m12] == 0.0f );
	CHECK( Ry[m13] == 0.0f );
	CHECK( Ry[m14] == 0.0f );
	CHECK( Ry[m15] == 1.0f );
}


TEST( RotZ, matrix_tests )
{
	Matrix Rz(ROT_Z, 1.0471975512f);	

	CHECK( eq(Rz[m0],0.5f,   MATH_TOLERANCE) );
	CHECK( eq(Rz[m1],0.866f,MATH_TOLERANCE) );
	CHECK( Rz[m2] == 0.0f );
	CHECK( Rz[m3] == 0.0f );
	CHECK( eq(Rz[m4],-0.866f,MATH_TOLERANCE) );
	CHECK( eq(Rz[m5],0.5f,  MATH_TOLERANCE) );
	CHECK( Rz[m6] == 0.0f );
	CHECK( Rz[m7] == 0.0f );
	CHECK( Rz[m8] == 0.0f );
	CHECK( Rz[m9] == 0.0f );
	CHECK( Rz[m10] == 1.0f );
	CHECK( Rz[m11] == 0.0f );
	CHECK( Rz[m12] == 0.0f );
	CHECK( Rz[m13] == 0.0f );
	CHECK( Rz[m14] == 0.0f );
	CHECK( Rz[m15] == 1.0f );
}

TEST( RotXYZ_Constructor, matrix_tests )
{
	Matrix Rx;
	Matrix Ry;
	Matrix Rz;

	// Rot_X Type Constructor:
	Rx.set(	ROT_X, MATH_PI3);

	CHECK( Rx[m0] ==  1.0f );
	CHECK( Rx[m1] ==  0.0f );
	CHECK( Rx[m2] ==  0.0f );
	CHECK( Rx[m3] ==  0.0f );
	CHECK( Rx[m4] ==  0.0f );
	CHECK( eq(Rx[m5],  0.5f,  MATH_TOLERANCE) );
	CHECK( eq(Rx[m6], 0.866f, MATH_TOLERANCE) );
	CHECK( Rx[m7] == 0.0f );
	CHECK( Rx[m8] == 0.0f );
	CHECK( eq(Rx[m9],-0.866f, MATH_TOLERANCE) );
	CHECK( eq(Rx[m10],0.5f  , MATH_TOLERANCE) );
	CHECK( Rx[m11] == 0.0f );
	CHECK( Rx[m12] == 0.0f );
	CHECK( Rx[m13] == 0.0f );
	CHECK( Rx[m14] == 0.0f );
	CHECK( Rx[m15] == 1.0f );

	Ry.set(ROT_Y, MATH_7PI8);

	CHECK( eq(Ry[m0],-0.9238f,  MATH_TOLERANCE) );
	CHECK( Ry[m1] ==  0.0f );
	CHECK( eq(Ry[m2],-0.3826f,MATH_TOLERANCE) );
	CHECK( Ry[m3] == 0.0f );
	CHECK( Ry[m4] == 0.0f );
	CHECK( Ry[m5] == 1.0f );
	CHECK( Ry[m6] == 0.0f );
	CHECK( Ry[m7] == 0.0f );
	CHECK( eq(Ry[m8],0.3826f,MATH_TOLERANCE) );
	CHECK( Ry[m9] ==  0.0f );
	CHECK( eq(Ry[m10],-0.9238f,   MATH_TOLERANCE) );
	CHECK( Ry[m11] == 0.0f );
	CHECK( Ry[m12] == 0.0f );
	CHECK( Ry[m13] == 0.0f );
	CHECK( Ry[m14] == 0.0f );
	CHECK( Ry[m15] == 1.0f );

	Rz.set(ROT_Z, MATH_PI2);

	CHECK( eq(Rz[m0],0.0f, MATH_TOLERANCE) );
	CHECK( eq(Rz[m1],1.0f, MATH_TOLERANCE) );
	CHECK( Rz[m2] == 0.0f );
	CHECK( Rz[m3] == 0.0f );
	CHECK( eq(Rz[m4],-1.0f, MATH_TOLERANCE) );
	CHECK( eq(Rz[m5], 0.0f,  MATH_TOLERANCE) );
	CHECK( Rz[m6] == 0.0f );
	CHECK( Rz[m7] == 0.0f );
	CHECK( Rz[m8] == 0.0f );
	CHECK( Rz[m9] == 0.0f );
	CHECK( Rz[m10] == 1.0f );
	CHECK( Rz[m11] == 0.0f );
	CHECK( Rz[m12] == 0.0f );
	CHECK( Rz[m13] == 0.0f );
	CHECK( Rz[m14] == 0.0f );
	CHECK( Rz[m15] == 1.0f );

	Matrix Rxyz;

	Rxyz = Rx * Ry * Rz;

	Matrix mTmp(ROT_XYZ, MATH_PI3,MATH_7PI8, MATH_PI2);

	CHECK( eq( Rxyz[m0], mTmp[m0], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m1], mTmp[m1], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m2], mTmp[m2], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m3], mTmp[m3], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m4], mTmp[m4], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m5], mTmp[m5], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m6], mTmp[m6], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m7], mTmp[m7], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m8], mTmp[m8], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m9], mTmp[m9], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m10], mTmp[m10], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m11], mTmp[m11], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m12], mTmp[m12], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m13], mTmp[m13], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m14], mTmp[m14], MATH_TOLERANCE) );
	CHECK( eq( Rxyz[m15], mTmp[m15], MATH_TOLERANCE) );

}


TEST( isEqual_false , matrix_tests )
{
	Vect V0(1.0f,2.0f,3.0f,4.0f);
	Vect V1(5.0f,6.0f,7.0f,8.0f);
	Vect V2(9.0f,10.0f,11.0f,12.0f);
	Vect V3(13.0f,14.0f,15.0f,16.0f);

	Matrix A(V0,V1,V2,V3);

	CHECK( A[m0] == 1.0f );
	CHECK( A[m1] == 2.0f );
	CHECK( A[m2] == 3.0f );
	CHECK( A[m3] == 4.0f );
	CHECK( A[m4] == 5.0f );
	CHECK( A[m5] == 6.0f );
	CHECK( A[m6] == 7.0f );	
	CHECK( A[m7] == 8.0f );
	CHECK( A[m8] == 9.0f );
	CHECK( A[m9] == 10.0f );
	CHECK( A[m10] == 11.0f );
	CHECK( A[m11] == 12.0f );
	CHECK( A[m12] == 13.0f );
	CHECK( A[m13] == 14.0f );
	CHECK( A[m14] == 15.0f );
	CHECK( A[m15] == 16.0f );

	Vect V4(20.0f,21.0f,22.0f,23.0f);
	Vect V5(24.0f,25.0f,26.0f,27.0f);
	Vect V6(28.0f,29.0f,30.0f,31.0f);
	Vect V7(32.0f,33.0f,34.0f,35.0f);

	Matrix B(V4,V5,V6,V7);

	CHECK( B[m0] == 20.0f );
	CHECK( B[m1] == 21.0f );
	CHECK( B[m2] == 22.0f );
	CHECK( B[m3] == 23.0f );
	CHECK( B[m4] == 24.0f );
	CHECK( B[m5] == 25.0f );
	CHECK( B[m6] == 26.0f );	
	CHECK( B[m7] == 27.0f );
	CHECK( B[m8] == 28.0f );
	CHECK( B[m9] == 29.0f );
	CHECK( B[m10] == 30.0f );
	CHECK( B[m11] == 31.0f );
	CHECK( B[m12] == 32.0f );
	CHECK( B[m13] == 33.0f );
	CHECK( B[m14] == 34.0f );
	CHECK( B[m15] == 35.0f );

	bool value = A.isEqual(B);

	CHECK( value == false );

}


TEST( isEqual_true , matrix_tests )
{
	Vect V0(1.0f,2.0f,3.0f,4.0f);
	Vect V1(5.0f,6.0f,7.0f,8.0f);
	Vect V2(9.0f,10.0f,11.0f,12.0f);
	Vect V3(13.0f,14.0f,15.0f,16.0f);

	Matrix A(V0,V1,V2,V3);

	CHECK( A[m0] == 1.0f );
	CHECK( A[m1] == 2.0f );
	CHECK( A[m2] == 3.0f );
	CHECK( A[m3] == 4.0f );
	CHECK( A[m4] == 5.0f );
	CHECK( A[m5] == 6.0f );
	CHECK( A[m6] == 7.0f );	
	CHECK( A[m7] == 8.0f );
	CHECK( A[m8] == 9.0f );
	CHECK( A[m9] == 10.0f );
	CHECK( A[m10] == 11.0f );
	CHECK( A[m11] == 12.0f );
	CHECK( A[m12] == 13.0f );
	CHECK( A[m13] == 14.0f );
	CHECK( A[m14] == 15.0f );
	CHECK( A[m15] == 16.0f );

	Vect V4(1.0f,2.0f,3.0f,4.0f);
	Vect V5(5.0f,6.0f,7.0f,8.0f);
	Vect V6(9.0f,10.0f,11.0f,12.0f);
	Vect V7(13.0f,14.0f,15.0f,16.0f);

	Matrix B(V4,V5,V6,V7);

	CHECK( B[m0] == 1.0f );
	CHECK( B[m1] == 2.0f );
	CHECK( B[m2] == 3.0f );
	CHECK( B[m3] == 4.0f );
	CHECK( B[m4] == 5.0f );
	CHECK( B[m5] == 6.0f );
	CHECK( B[m6] == 7.0f );	
	CHECK( B[m7] == 8.0f );
	CHECK( B[m8] == 9.0f );
	CHECK( B[m9] == 10.0f );
	CHECK( B[m10] == 11.0f );
	CHECK( B[m11] == 12.0f );
	CHECK( B[m12] == 13.0f );
	CHECK( B[m13] == 14.0f );
	CHECK( B[m14] == 15.0f );
	CHECK( B[m15] == 16.0f );

	bool value = A.isEqual(B);

	CHECK( value == true );

}


TEST( isIdentity_false , matrix_tests )
{
	Vect V0(1.0f,2.0f,3.0f,4.0f);
	Vect V1(5.0f,6.0f,7.0f,8.0f);
	Vect V2(9.0f,10.0f,11.0f,12.0f);
	Vect V3(13.0f,14.0f,15.0f,16.0f);

	Matrix A(V0,V1,V2,V3);

	CHECK( A[m0] == 1.0f );
	CHECK( A[m1] == 2.0f );
	CHECK( A[m2] == 3.0f );
	CHECK( A[m3] == 4.0f );
	CHECK( A[m4] == 5.0f );
	CHECK( A[m5] == 6.0f );
	CHECK( A[m6] == 7.0f );	
	CHECK( A[m7] == 8.0f );
	CHECK( A[m8] == 9.0f );
	CHECK( A[m9] == 10.0f );
	CHECK( A[m10] == 11.0f );
	CHECK( A[m11] == 12.0f );
	CHECK( A[m12] == 13.0f );
	CHECK( A[m13] == 14.0f );
	CHECK( A[m14] == 15.0f );
	CHECK( A[m15] == 16.0f );

	bool value = A.isIdentity();

	CHECK( value == false );

}


TEST( isIdentity_true , matrix_tests )
{
	Vect V0(1.0f,0.0f,0.0f,0.0f);
	Vect V1(0.0f,1.0f,0.0f,0.0f);
	Vect V2(0.0f,0.0f,1.0f,0.0f);
	Vect V3(0.0f,0.0f,0.0f,1.0f);

	Matrix A(V0,V1,V2,V3);

	CHECK( A[m0] == 1.0f );
	CHECK( A[m1] == 0.0f );
	CHECK( A[m2] == 0.0f );
	CHECK( A[m3] == 0.0f );
	CHECK( A[m4] == 0.0f );
	CHECK( A[m5] == 1.0f );
	CHECK( A[m6] == 0.0f );	
	CHECK( A[m7] == 0.0f );
	CHECK( A[m8] == 0.0f );
	CHECK( A[m9] == 0.0f );
	CHECK( A[m10] == 1.0f );
	CHECK( A[m11] == 0.0f );
	CHECK( A[m12] == 0.0f );
	CHECK( A[m13] == 0.0f );
	CHECK( A[m14] == 0.0f );
	CHECK( A[m15] == 1.0f );

	bool value = A.isIdentity();

	CHECK( value == true );

}

