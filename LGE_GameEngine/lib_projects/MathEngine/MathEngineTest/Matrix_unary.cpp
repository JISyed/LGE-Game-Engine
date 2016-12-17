

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
TEST( Matrix_UnaryPlus, matix_tests )
{
	Vect V0(30.0f,29.0f,28.0f,27.0f);
	Vect V1(26.0f,25.0f,24.0f,23.0f);
	Vect V2(22.0f,21.0f,20.0f,19.0f);
	Vect V3(18.0f,17.0f,16.0f,15.0f);

	Matrix A(V0,V1,V2,V3);

	CHECK( A[m0] == 30.0f );
	CHECK( A[m1] == 29.0f );
	CHECK( A[m2] == 28.0f );
	CHECK( A[m3] == 27.0f );
	CHECK( A[m4] == 26.0f );
	CHECK( A[m5] == 25.0f );
	CHECK( A[m6] == 24.0f );	
	CHECK( A[m7] == 23.0f );
	CHECK( A[m8] == 22.0f );
	CHECK( A[m9] == 21.0f );
	CHECK( A[m10] == 20.0f );
	CHECK( A[m11] == 19.0f );
	CHECK( A[m12] == 18.0f );
	CHECK( A[m13] == 17.0f );
	CHECK( A[m14] == 16.0f );
	CHECK( A[m15] == 15.0f );

	+A;

	CHECK( A[m0] == 30.0f );
	CHECK( A[m1] == 29.0f );
	CHECK( A[m2] == 28.0f );
	CHECK( A[m3] == 27.0f );
	CHECK( A[m4] == 26.0f );
	CHECK( A[m5] == 25.0f );
	CHECK( A[m6] == 24.0f );	
	CHECK( A[m7] == 23.0f );
	CHECK( A[m8] == 22.0f );
	CHECK( A[m9] == 21.0f );
	CHECK( A[m10] == 20.0f );
	CHECK( A[m11] == 19.0f );
	CHECK( A[m12] == 18.0f );
	CHECK( A[m13] == 17.0f );
	CHECK( A[m14] == 16.0f );
	CHECK( A[m15] == 15.0f );

}


TEST( unary_equal_Plus, matrix_tests )
{
	Vect V0(30.0f,29.0f,28.0f,27.0f);
	Vect V1(26.0f,25.0f,24.0f,23.0f);
	Vect V2(22.0f,21.0f,20.0f,19.0f);
	Vect V3(18.0f,17.0f,16.0f,15.0f);

	Matrix A(V0,V1,V2,V3);

	CHECK( A[m0] == 30.0f );
	CHECK( A[m1] == 29.0f );
	CHECK( A[m2] == 28.0f );
	CHECK( A[m3] == 27.0f );
	CHECK( A[m4] == 26.0f );
	CHECK( A[m5] == 25.0f );
	CHECK( A[m6] == 24.0f );	
	CHECK( A[m7] == 23.0f );
	CHECK( A[m8] == 22.0f );
	CHECK( A[m9] == 21.0f );
	CHECK( A[m10] == 20.0f );
	CHECK( A[m11] == 19.0f );
	CHECK( A[m12] == 18.0f );
	CHECK( A[m13] == 17.0f );
	CHECK( A[m14] == 16.0f );
	CHECK( A[m15] == 15.0f );

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

	 B = +A;

	CHECK( A[m0] == 30.0f );
	CHECK( A[m1] == 29.0f );
	CHECK( A[m2] == 28.0f );
	CHECK( A[m3] == 27.0f );
	CHECK( A[m4] == 26.0f );
	CHECK( A[m5] == 25.0f );
	CHECK( A[m6] == 24.0f );	
	CHECK( A[m7] == 23.0f );
	CHECK( A[m8] == 22.0f );
	CHECK( A[m9] == 21.0f );
	CHECK( A[m10] == 20.0f );
	CHECK( A[m11] == 19.0f );
	CHECK( A[m12] == 18.0f );
	CHECK( A[m13] == 17.0f );
	CHECK( A[m14] == 16.0f );
	CHECK( A[m15] == 15.0f );

	CHECK( B[m0] == 30.0f );
	CHECK( B[m1] == 29.0f );
	CHECK( B[m2] == 28.0f );
	CHECK( B[m3] == 27.0f );
	CHECK( B[m4] == 26.0f );
	CHECK( B[m5] == 25.0f );
	CHECK( B[m6] == 24.0f );	
	CHECK( B[m7] == 23.0f );
	CHECK( B[m8] == 22.0f );
	CHECK( B[m9] == 21.0f );
	CHECK( B[m10] == 20.0f );
	CHECK( B[m11] == 19.0f );
	CHECK( B[m12] == 18.0f );
	CHECK( B[m13] == 17.0f );
	CHECK( B[m14] == 16.0f );
	CHECK( B[m15] == 15.0f );

}

TEST( Matrix_UnaryMinus, matix_tests )
{
	Vect V0(30.0f,29.0f,28.0f,27.0f);
	Vect V1(26.0f,25.0f,24.0f,23.0f);
	Vect V2(22.0f,21.0f,20.0f,19.0f);
	Vect V3(18.0f,17.0f,16.0f,15.0f);

	Matrix A(V0,V1,V2,V3);

	CHECK( A[m0] == 30.0f );
	CHECK( A[m1] == 29.0f );
	CHECK( A[m2] == 28.0f );
	CHECK( A[m3] == 27.0f );
	CHECK( A[m4] == 26.0f );
	CHECK( A[m5] == 25.0f );
	CHECK( A[m6] == 24.0f );	
	CHECK( A[m7] == 23.0f );
	CHECK( A[m8] == 22.0f );
	CHECK( A[m9] == 21.0f );
	CHECK( A[m10] == 20.0f );
	CHECK( A[m11] == 19.0f );
	CHECK( A[m12] == 18.0f );
	CHECK( A[m13] == 17.0f );
	CHECK( A[m14] == 16.0f );
	CHECK( A[m15] == 15.0f );

	-A;

	CHECK( A[m0] == 30.0f );
	CHECK( A[m1] == 29.0f );
	CHECK( A[m2] == 28.0f );
	CHECK( A[m3] == 27.0f );
	CHECK( A[m4] == 26.0f );
	CHECK( A[m5] == 25.0f );
	CHECK( A[m6] == 24.0f );	
	CHECK( A[m7] == 23.0f );
	CHECK( A[m8] == 22.0f );
	CHECK( A[m9] == 21.0f );
	CHECK( A[m10] == 20.0f );
	CHECK( A[m11] == 19.0f );
	CHECK( A[m12] == 18.0f );
	CHECK( A[m13] == 17.0f );
	CHECK( A[m14] == 16.0f );
	CHECK( A[m15] == 15.0f );

}


TEST( unary_equal_Minus, Matrix_tests )
{
	Vect V0(30.0f,29.0f,28.0f,27.0f);
	Vect V1(26.0f,25.0f,24.0f,23.0f);
	Vect V2(22.0f,21.0f,20.0f,19.0f);
	Vect V3(18.0f,17.0f,16.0f,15.0f);

	Matrix A(V0,V1,V2,V3);

	CHECK( A[m0] == 30.0f );
	CHECK( A[m1] == 29.0f );
	CHECK( A[m2] == 28.0f );
	CHECK( A[m3] == 27.0f );
	CHECK( A[m4] == 26.0f );
	CHECK( A[m5] == 25.0f );
	CHECK( A[m6] == 24.0f );	
	CHECK( A[m7] == 23.0f );
	CHECK( A[m8] == 22.0f );
	CHECK( A[m9] == 21.0f );
	CHECK( A[m10] == 20.0f );
	CHECK( A[m11] == 19.0f );
	CHECK( A[m12] == 18.0f );
	CHECK( A[m13] == 17.0f );
	CHECK( A[m14] == 16.0f );
	CHECK( A[m15] == 15.0f );

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

	 B = -A;

	CHECK( A[m0] == 30.0f );
	CHECK( A[m1] == 29.0f );
	CHECK( A[m2] == 28.0f );
	CHECK( A[m3] == 27.0f );
	CHECK( A[m4] == 26.0f );
	CHECK( A[m5] == 25.0f );
	CHECK( A[m6] == 24.0f );	
	CHECK( A[m7] == 23.0f );
	CHECK( A[m8] == 22.0f );
	CHECK( A[m9] == 21.0f );
	CHECK( A[m10] == 20.0f );
	CHECK( A[m11] == 19.0f );
	CHECK( A[m12] == 18.0f );
	CHECK( A[m13] == 17.0f );
	CHECK( A[m14] == 16.0f );
	CHECK( A[m15] == 15.0f );

	CHECK( B[m0] == -30.0f );
	CHECK( B[m1] == -29.0f );
	CHECK( B[m2] == -28.0f );
	CHECK( B[m3] == -27.0f );
	CHECK( B[m4] == -26.0f );
	CHECK( B[m5] == -25.0f );
	CHECK( B[m6] == -24.0f );	
	CHECK( B[m7] == -23.0f );
	CHECK( B[m8] == -22.0f );
	CHECK( B[m9] == -21.0f );
	CHECK( B[m10] == -20.0f );
	CHECK( B[m11] == -19.0f );
	CHECK( B[m12] == -18.0f );
	CHECK( B[m13] == -17.0f );
	CHECK( B[m14] == -16.0f );
	CHECK( B[m15] == -15.0f );

}

