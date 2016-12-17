
//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "UnitTest.h"
#include "MathEngine.h"
using namespace lge;
//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------

TEST( default_constuctor, vector_tests )
{
	Vect A;

	CHECK( A[x] == 0.0f );
	CHECK( A[y] == 0.0f );
	CHECK( A[z] == 0.0f );
	CHECK( A[w] == 1.0f );
}


TEST( individual_defaultW_constuctor, vector_tests )
{
	Vect A(2.0f, 3.0f, 4.0f);

	CHECK( A[x] == 2.0f );
	CHECK( A[y] == 3.0f );
	CHECK( A[z] == 4.0f );
	CHECK( A[w] == 1.0f );
}

TEST( individual_constuctor, vector_tests )
{
	Vect A(2.0f, 3.0f, 4.0f, 5.0f);

	CHECK( A[x] == 2.0f );
	CHECK( A[y] == 3.0f );
	CHECK( A[z] == 4.0f );
	CHECK( A[w] == 5.0f );
}


TEST( assignment_operator, vector_tests )
{
	Vect A(2.0f, 3.0f, 4.0f, 5.0f);
	Vect B(10.0f, 11.0f, 12.0f, 13.0f);

	CHECK( A[x] == 2.0f );
	CHECK( A[y] == 3.0f );
	CHECK( A[z] == 4.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

	B = A;

	CHECK( A[x] == 2.0f );
	CHECK( A[y] == 3.0f );
	CHECK( A[z] == 4.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == A[x] );
	CHECK( B[y] == A[y] );
	CHECK( B[z] == A[z] );
	CHECK( B[w] == A[w] );	
}

TEST( Copy_constuctor, vector_tests )
{
	Vect A(2.0f, 3.0f, 4.0f, 5.0f);
	Vect B(A);

	CHECK( A[x] == 2.0f );
	CHECK( A[y] == 3.0f );
	CHECK( A[z] == 4.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == A[x] );
	CHECK( B[y] == A[y] );
	CHECK( B[z] == A[z] );
	CHECK( B[w] == A[w] );	
}

TEST( Destructor_constuctor, vector_tests )
{
	Vect v2(5.0f, 6.0f, 7.0f, 8.0f);
	Vect *pV2 = &v2;
	pV2->~Vect();
	CHECK(1);
}

