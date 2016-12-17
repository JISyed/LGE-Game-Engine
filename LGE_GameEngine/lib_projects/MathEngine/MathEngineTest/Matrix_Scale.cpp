
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
TEST( Matrix_Scale, matix_tests )
{
	Vect V0(1.0f,2.0f,3.0f,4.0f);
	Vect V1(5.0f,6.0f,7.0f,8.0f);
	Vect V2(9.0f,10.0f,11.0f,12.0f);
	Vect V3(13.0f,14.0f,15.0f,16.0f);

	Matrix A(V0,V1,V2,V3);
	Matrix C;
	float scale = 10.0f;

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

	C = scale * A;

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

	CHECK( C[m0] == 10.0f );
	CHECK( C[m1] == 20.0f );
	CHECK( C[m2] == 30.0f );
	CHECK( C[m3] == 40.0f );
	CHECK( C[m4] == 50.0f );
	CHECK( C[m5] == 60.0f );
	CHECK( C[m6] == 70.0f );	
	CHECK( C[m7] == 80.0f );
	CHECK( C[m8] == 90.0f );
	CHECK( C[m9] == 100.0f );
	CHECK( C[m10] == 110.0f );
	CHECK( C[m11] == 120.0f );
	CHECK( C[m12] == 130.0f );
	CHECK( C[m13] == 140.0f );
	CHECK( C[m14] == 150.0f );
	CHECK( C[m15] == 160.0f );
}



TEST( Matrix_times_Scale, Matrix_tests )
{
	Vect V0(1.0f,2.0f,3.0f,4.0f);
	Vect V1(5.0f,6.0f,7.0f,8.0f);
	Vect V2(9.0f,10.0f,11.0f,12.0f);
	Vect V3(13.0f,14.0f,15.0f,16.0f);

	Matrix A(V0,V1,V2,V3);
	Matrix C;
	float scale = 10.0f;

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

	C = A * scale;

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

	CHECK( C[m0] == 10.0f );
	CHECK( C[m1] == 20.0f );
	CHECK( C[m2] == 30.0f );
	CHECK( C[m3] == 40.0f );
	CHECK( C[m4] == 50.0f );
	CHECK( C[m5] == 60.0f );
	CHECK( C[m6] == 70.0f );	
	CHECK( C[m7] == 80.0f );
	CHECK( C[m8] == 90.0f );
	CHECK( C[m9] == 100.0f );
	CHECK( C[m10] == 110.0f );
	CHECK( C[m11] == 120.0f );
	CHECK( C[m12] == 130.0f );
	CHECK( C[m13] == 140.0f );
	CHECK( C[m14] == 150.0f );
	CHECK( C[m15] == 160.0f );

}


TEST( Matrix_ScaleEquals, Matrix_tests )
{

	Vect V0(1.0f,2.0f,3.0f,4.0f);
	Vect V1(5.0f,6.0f,7.0f,8.0f);
	Vect V2(9.0f,10.0f,11.0f,12.0f);
	Vect V3(13.0f,14.0f,15.0f,16.0f);

	Matrix A(V0,V1,V2,V3);
	float scale = 10.0f;

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

	A *= scale;

	CHECK( A[m0] == 10.0f );
	CHECK( A[m1] == 20.0f );
	CHECK( A[m2] == 30.0f );
	CHECK( A[m3] == 40.0f );
	CHECK( A[m4] == 50.0f );
	CHECK( A[m5] == 60.0f );
	CHECK( A[m6] == 70.0f );	
	CHECK( A[m7] == 80.0f );
	CHECK( A[m8] == 90.0f );
	CHECK( A[m9] == 100.0f );
	CHECK( A[m10] == 110.0f );
	CHECK( A[m11] == 120.0f );
	CHECK( A[m12] == 130.0f );
	CHECK( A[m13] == 140.0f );
	CHECK( A[m14] == 150.0f );
	CHECK( A[m15] == 160.0f );


}

