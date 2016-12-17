
//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "UnitTest.h"
#include "MathEngine.h"

using namespace lge;
//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------
TEST( IsEqualFalse, vector_tests )
{
	Vect v1(1.0f,2.0f,3.0f);
	Vect v2(9.0f,-3.0f,5.0f);
	bool bvalue1;

	bvalue1 = v1.isEqual(v2, 0.1f);

	CHECK( bvalue1 == false );
}


TEST( IsEqualTrue, vector_tests  )
{	
	bool bvalue1;
	Vect v1(1.0f,2.0f,3.0f);
	Vect v2(1.0f,2.0f,3.05f);

	bvalue1 = v1.isEqual(v2, 0.1f);

	CHECK( bvalue1 == true );
}


TEST( IsZeroFalse, vector_tests  )
{
	bool bvalue1;	
	Vect v1(0.023f, 0.0f, 0.0f, 1.05f);

	bvalue1 = v1.isZero(0.0f);

	CHECK( bvalue1 == false );
}


TEST( IsZeroTrue, vector_tests  )
{
	bool bvalue1;	
	Vect v1(0.0f, 0.0f, 0.0f, 1.05f);

	bvalue1 = v1.isZero(0.1f);

	CHECK( bvalue1 == true );
}



TEST( IsEqualFalse_default, vector_tests )
{
	Vect v1(1.0f,2.0f,3.0f);
	Vect v2(9.0f,-3.0f,5.0f);
	bool bvalue1;

	bvalue1 = v1.isEqual(v2);

	CHECK( bvalue1 == false );
}


TEST( IsEqualTrue_default, vector_tests  )
{	
	bool bvalue1;
	Vect v1(1.0f,2.0f,3.0f);
	Vect v2(1.0f,2.0f,3.05f);

	bvalue1 = v1.isEqual(v2);

	CHECK( bvalue1 == false );
}


TEST( IsZeroFalse_default, vector_tests  )
{
	bool bvalue1;	
	Vect v1(0.023f, 0.0f, 0.0f, 1.05f);

	bvalue1 = v1.isZero();

	CHECK( bvalue1 == false );
}


TEST( IsZeroTrue_default, vector_tests  )
{
	bool bvalue1;	
	Vect v1(0.0f, 0.0f, 0.0f, 1.05f);

	bvalue1 = v1.isZero();

	CHECK( bvalue1 == false );
}

