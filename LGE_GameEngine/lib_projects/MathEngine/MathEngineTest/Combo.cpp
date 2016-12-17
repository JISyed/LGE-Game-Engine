
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
TEST( VectLine, combo_tests )
{
	Vect A(0.0f, 50.0f, 300.0f, 5.0f);
	Vect B(10.0f, 100.0f, 1000.0f, 51.0f);
	Vect C;

	CHECK( A[x] == 0.0f );
	CHECK( A[y] == 50.0f );
	CHECK( A[z] == 300.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 100.0f );
	CHECK( B[z] == 1000.0f );
	CHECK( B[w] == 51.0f );

	Vect Line;
	float t;

	t = 0.0f;
	Line = A + t * ( B - A);


	CHECK( Line[x] == 0.0f );
	CHECK( Line[y] == 50.0f );
	CHECK( Line[z] == 300.0f );
	CHECK( Line[w] == 1.0f );

	CHECK( A[x] == 0.0f );
	CHECK( A[y] == 50.0f );
	CHECK( A[z] == 300.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 100.0f );
	CHECK( B[z] == 1000.0f );
	CHECK( B[w] == 51.0f );

	t = 1.0f;
	Line = A + t * ( B - A);


	CHECK( Line[x] == 10.0f );
	CHECK( Line[y] == 100.0f );
	CHECK( Line[z] == 1000.0f );
	CHECK( Line[w] == 1.0f );

	CHECK( A[x] == 0.0f );
	CHECK( A[y] == 50.0f );
	CHECK( A[z] == 300.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 100.0f );
	CHECK( B[z] == 1000.0f );
	CHECK( B[w] == 51.0f );

	t = 0.5f;
	Line = A + t * ( B - A);


	CHECK( Line[x] == 5.0f );
	CHECK( Line[y] == 75.0f );
	CHECK( Line[z] == 650.0f );
	CHECK( Line[w] == 1.0f );

	CHECK( A[x] == 0.0f );
	CHECK( A[y] == 50.0f );
	CHECK( A[z] == 300.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 100.0f );
	CHECK( B[z] == 1000.0f );
	CHECK( B[w] == 51.0f );

}


TEST( VectCrossAddSub, combo_tests )
{
	Vect A(1.0f, 2.0f, 3.0f, 5.0f);
	Vect B(10.0f, 11.0f, 12.0f, 13.0f);
	Vect C;

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

	
	C = A + (A-B).cross(B);


	CHECK( C[x] == -8.0f );
	CHECK( C[y] == 20.0f );
	CHECK( C[z] == -6.0f );
	CHECK( C[w] == 1.0f );

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );
}


TEST( VectCrossAddSubMatrixMult, combo_tests )
{
	Vect A(1.0f, 2.0f, 3.0f, 5.0f);
	Vect B(10.0f, 11.0f, 12.0f, 13.0f);
	Vect C;

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

	
	C = A + (A-B).cross(B);
	Vect D = C.dot(A) * B;

	CHECK( D[x] == 140.0f );
	CHECK( D[y] == 154.0f );
	CHECK( D[z] == 168.0f );
	CHECK( D[w] == 1.0f );

	CHECK( C[x] == -8.0f );
	CHECK( C[y] == 20.0f );
	CHECK( C[z] == -6.0f );
	CHECK( C[w] == 1.0f );

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

	Matrix M(A,B,C,D);

	A = B * M;

	CHECK( A[x] == 1844.0f );
	CHECK( A[y] == 2383.0f );
	CHECK( A[z] == 2274.0f );
	CHECK( A[w] == 218.0f );
}

TEST( VectCrossAddSubMatrixMultCross, combo_tests )
{
	Vect A(1.0f, 2.0f, 3.0f, 5.0f);
	Vect B(10.0f, 11.0f, 12.0f, 13.0f);
	Vect C;

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

	
	C = A + (A-B).cross(B);
	Vect D = C.dot(A) * B;

	CHECK( D[x] == 140.0f );
	CHECK( D[y] == 154.0f );
	CHECK( D[z] == 168.0f );
	CHECK( D[w] == 1.0f );

	CHECK( C[x] == -8.0f );
	CHECK( C[y] == 20.0f );
	CHECK( C[z] == -6.0f );
	CHECK( C[w] == 1.0f );

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

	Matrix M(A,B,C,D);

	A = Vect(1.0f, 0.0f, 4.0f,1.0f).cross(B * M);

	CHECK( A[x] == -9532.0f );
	CHECK( A[y] == 5102.0f );
	CHECK( A[z] == 2383.0f );
	CHECK( A[w] == 1.0f );
}


TEST( VectCrossCrossNorm, combo_tests )
{
	Vect A(1.0f, 2.0f, 3.0f, 5.0f);
	Vect B(10.0f, 11.0f, 12.0f, 13.0f);
	Vect C;

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

	
	C = (A-B).cross(B);
	Vect D = C.cross(B);
	D.norm();

	CHECK( eq( D[x], 0.74790420f, MATH_TOLERANCE) );
	CHECK( eq( D[y], 0.04273730f, MATH_TOLERANCE) );
	CHECK( eq( D[z], -0.6624290f, MATH_TOLERANCE) );
	CHECK( D[w] == 1.0f );

	CHECK( C[x] == -9.0f );
	CHECK( C[y] == 18.0f );
	CHECK( C[z] == -9.0f );
	CHECK( C[w] == 1.0f );

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

}


TEST( junkfood, combo_tests )
{
	Vect A(1.0f, 2.0f, 3.0f, 5.0f);
	Vect B(10.0f, 11.0f, 12.0f, 13.0f);
	Vect C;

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );

	
	float junk = A.dot((A-B).cross(B))+5.0f;

	CHECK( junk == 5.0f );

	CHECK( A[x] == 1.0f );
	CHECK( A[y] == 2.0f );
	CHECK( A[z] == 3.0f );
	CHECK( A[w] == 5.0f );

	CHECK( B[x] == 10.0f );
	CHECK( B[y] == 11.0f );
	CHECK( B[z] == 12.0f );
	CHECK( B[w] == 13.0f );


}



