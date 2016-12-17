
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
TEST( Matrix_inverse, matix_tests )
{
	Matrix Rx(ROT_X, 0.23f);
	Matrix Ry(ROT_Y, -1.23f);
	Matrix T( TRANS, 3.4f, 2.9f, -9.0f);

	Matrix M = Rx*Ry * T;
	Matrix N(M);

	M.inv();

	Matrix C;
	C = N * M;

	// verify C is identity
	
	bool flag=C.isIdentity( MATH_TOLERANCE );

	CHECK( flag == true );
}

TEST( Matrix_getinverse, matix_tests )
{
	Matrix Rx(ROT_X, 0.23f);
	Matrix Ry(ROT_Y, -1.23f);
	Matrix S( SCALE, 4.0f, 5.0f, 2.0f);
	Matrix T( TRANS, -2.3f, 7.9f, 9.03f);

	Matrix M = S*T*Rx*Ry*S;
	Matrix N;

	N = M.getInv();

	Matrix C;
	C = N * M;

	// verify C is identity
	
	bool flag=C.isIdentity( MATH_TOLERANCE );

	CHECK( flag == true );
}


