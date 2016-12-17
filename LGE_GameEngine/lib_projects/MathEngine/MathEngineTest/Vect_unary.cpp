
//---------------------------------------------------------------------------
// HEADER FILES:
//---------------------------------------------------------------------------
#include "UnitTest.h"
#include "MathEngine.h"

using namespace lge;
//---------------------------------------------------------------------------
// TESTS:
//---------------------------------------------------------------------------
TEST( unary_Plus, vector_tests )
{
	Vect A(-2.0f, -3.0f, -4.0f, -5.0f);

	CHECK( A[x] == -2.0f );
	CHECK( A[y] == -3.0f );
	CHECK( A[z] == -4.0f );
	CHECK( A[w] == -5.0f );

	+A;

	CHECK( A[x] == -2.0f );
	CHECK( A[y] == -3.0f );
	CHECK( A[z] == -4.0f );
	CHECK( A[w] == -5.0f );

}

TEST( unary_equal_Plus, vector_tests )
{
	Vect A(-2.0f, -3.0f, -4.0f, -5.0f);
	Vect B(21.0f, 31.0f, 41.0f, 51.0f);

	CHECK( A[x] == -2.0f );
	CHECK( A[y] == -3.0f );
	CHECK( A[z] == -4.0f );
	CHECK( A[w] == -5.0f );

	CHECK( B[x] == 21.0f );
	CHECK( B[y] == 31.0f );
	CHECK( B[z] == 41.0f );
	CHECK( B[w] == 51.0f );

	 B = +A;

	CHECK( A[x] == -2.0f );
	CHECK( A[y] == -3.0f );
	CHECK( A[z] == -4.0f );
	CHECK( A[w] == -5.0f );

	CHECK( B[x] == -2.0f );
	CHECK( B[y] == -3.0f );
	CHECK( B[z] == -4.0f );
	CHECK( B[w] == 1.0f );

}

TEST( unary_Minus, vector_tests )
{
	Vect A(-2.0f, -3.0f, -4.0f, -5.0f);

	CHECK( A[x] == -2.0f );
	CHECK( A[y] == -3.0f );
	CHECK( A[z] == -4.0f );
	CHECK( A[w] == -5.0f );

	-A;

	CHECK( A[x] == -2.0f );
	CHECK( A[y] == -3.0f );
	CHECK( A[z] == -4.0f );
	CHECK( A[w] == -5.0f );



}

TEST( unary_equal_Minus, vector_tests )
{
	Vect A(-2.0f, -3.0f, -4.0f, -5.0f);
	Vect B(21.0f, 31.0f, 41.0f, 51.0f);

	CHECK( A[x] == -2.0f );
	CHECK( A[y] == -3.0f );
	CHECK( A[z] == -4.0f );
	CHECK( A[w] == -5.0f );

	CHECK( B[x] == 21.0f );
	CHECK( B[y] == 31.0f );
	CHECK( B[z] == 41.0f );
	CHECK( B[w] == 51.0f );

	 B = -A;

	CHECK( A[x] == -2.0f );
	CHECK( A[y] == -3.0f );
	CHECK( A[z] == -4.0f );
	CHECK( A[w] == -5.0f );

	CHECK( B[x] == 2.0f );
	CHECK( B[y] == 3.0f );
	CHECK( B[z] == 4.0f );
	CHECK( B[w] == 1.0f );

}

