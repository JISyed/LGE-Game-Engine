/*****************************************************************************/
/*                                                                           */
/* File: VectLERP.cpp                                                        */
/*                                                                           */
/* Primative Vect LERP testbed                                               */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* user includes:                                                            */
/*****************************************************************************/
#include "UnitTest.h"
#include "MathEngine.h"
#include "MathApp.h"
using namespace lge;
#define eq  		Util::isEqual 


/*****************************************************************************/
/* Vect Test:                                                                */
/*****************************************************************************/
TEST( VectLERPFunction, VectLerpTests )
{
	// Vect Lerp Functions()
	CHECK(1);
}

TEST( LERP_Array, VectLerpTests )
{
	//Vect Lerp Array()

	Vect vSource[] =
	{   Vect(  1.00f, 2.0f,   3.0f,  4.0f),
		Vect( 21.00f, 12.0f, 23.0f, 40.0f), 
		Vect( 13.00f, 24.0f, 33.0f, 40.0f), 		
		Vect(  0.50f, 22.0f, 43.0f, 40.0f),
		Vect(  1.30f, 23.0f, 35.0f, 40.0f), 	
		Vect( 15.00f, 72.0f, 35.0f, 40.0f), 	
		Vect( 21.00f, 92.0f, 33.0f, 40.0f), 	
	
	};

	Vect vTarget[] =
	{   
      Vect(  -1.00f, 12.0f,   13.0f,  41.0f),
		Vect( 213.00f, -12.0f, 263.0f, 140.0f), 
		Vect( 133.00f, -24.0f, 363.0f, 240.0f), 		
		Vect(  3.50f, -22.0f, 453.0f, 340.0f), 	
		Vect(  13.30f, -23.0f, 365.0f, 440.0f), 	
		Vect( 153.00f, -72.0f, 735.0f, 540.0f), 	
		Vect( 231.00f, -92.0f, 733.0f, 340.0f), 	
	
	};
	
	#define numVects  ((sizeof(vSource))/(sizeof(vSource[0])) )

	Vect vResult[ numVects ];
	Vect vOut;

	VectApp::LerpArray(vResult,vSource,vTarget,0.65f,numVects);

	
	for(int i = 0; i<numVects; i++)
		{
		
		VectApp::Lerp(vOut,vSource[i],vTarget[i],0.65f);
		
		CHECK( eq(vOut[x],vResult[i][x],MATH_TOLERANCE) );
		CHECK( eq(vOut[y],vResult[i][y],MATH_TOLERANCE) );
		CHECK( eq(vOut[z],vResult[i][z],MATH_TOLERANCE) );
		CHECK( eq(vOut[w],vResult[i][w],MATH_TOLERANCE) );
	
		}


}



TEST( VectAppLerp, VectAppTests )
{
	Vect va(0.0f,0.0f,0.0f);
	Vect vb(10.0f,20.0f,30.0f);
	Vect vout;	
	// VectApp::Lerp(vout, va, vb, 0.0f); 
	VectApp::Lerp(vout,va,vb,0.0f);

	CHECK( (vout[x] == 0.0f) );
	CHECK( (vout[y] == 0.0f) );
	CHECK( (vout[z] == 0.0f) );
	CHECK( (vout[w] == 1.0f) );

}


TEST( VectAppLerp2, VectAppTests )
{

	Vect va(0.0f,0.0f,0.0f);
	Vect vb(10.0f,20.0f,30.0f);
	Vect vout;

	//" => VectApp::Lerp(vout, va, vb, 0.5f)
	VectApp::Lerp(vout, va, vb, 0.5f);

	CHECK( (vout[x] == 5.0f) );
	CHECK( (vout[y] == 10.0f) );
	CHECK( (vout[z] == 15.0f) );
	CHECK( (vout[w] == 1.0f) );

}


TEST( VectAppLerp3, VectAppTests )
{

	Vect va(0.0f,0.0f,0.0f);
	Vect vb(10.0f,20.0f,30.0f);
	Vect vout;

	// => VectApp::Lerp(vout, va, vb, 0.25f)
	VectApp::Lerp(vout, va, vb, 0.25f);

	CHECK( (vout[x] == 2.5f) );
	CHECK( (vout[y] == 5.0f) );
	CHECK( (vout[z] == 7.50f) );
	CHECK( (vout[w] == 1.0f) );

}


TEST( VectAppLerp4, VectAppTests )
{
	Vect va(0.0f,0.0f,0.0f);
	Vect vb(10.0f,20.0f,30.0f);
	Vect vout;

	//VectApp::Lerp(vout, va, vb, 1.0f); 
	VectApp::Lerp(vout, va, vb, 1.0f);

	CHECK( (vout[x] == 10.0f) );
	CHECK( (vout[y] == 20.0f) );
	CHECK( (vout[z] == 30.0f) );
	CHECK( (vout[w] == 1.0f) );

}	

		

/***** END of File VectLERP.cpp ********************************************/
