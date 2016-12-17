/*****************************************************************************/
/*                                                                           */
/* File: QuatBoolean.cpp                                                      */
/*                                                                           */
/* Primative Quat set/get Class testbed                                      */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* user includes:                                                            */
/*****************************************************************************/
#include "UnitTest.h"
#include "MathEngine.h"
using namespace lge;
#define eq  		Util::isEqual 


/*****************************************************************************/
/* Quat Set:                                                                 */
/*****************************************************************************/

TEST( QuatBoolean, QuatBooleanTests )
{
	// Quat Boolean tests 

	CHECK( 1 );
}


TEST( QuatIsEqual, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// IsEqual()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(9.0f,-3.0f,5.0f,4.0f);

	// => q1.isEqual(q2, 0.1f) 
	bvalue1 = q1.isEqual(q2, 0.1f);
	CHECK( bvalue1 == false );
}


TEST( QuatIsEqual1, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// IsEqual()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(1.0f,2.0f,3.05f,4.0f);

	// q1.isEqual(q2, 0.1f) 
	bvalue1 = q1.isEqual(q2, 0.1f);

	CHECK( bvalue1 == true );
}


TEST( QuatIsNegEqual, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// IsNegEqual()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(9.0f,-3.0f,5.0f,4.0f);

	// q1.isNegEqual(q2, 0.1f) 
	bvalue1 = q1.isNegEqual(q2, 0.1f);

	CHECK( bvalue1 == false );
}

TEST( QuatIsNegEqual2, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// IsNegEqual()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(-1.0f,-2.0f,-3.05f,-4.0f);
	
	// q1.isNegEqual(q2, 0.1f)
	bvalue1 = q1.isNegEqual(q2, 0.1f);

	CHECK( bvalue1 == true );
}


TEST( QuatIsEquivalent, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isEquivalent()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(-1.0f,-2.0f,-3.05f,-4.0f);

	// q1.isEquivalent(q2, 0.1f) 
	bvalue1 = q1.isEquivalent(q2, 0.1f);

	CHECK( bvalue1 == true );
}

TEST( QuatIsEquivalent2, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isEquivalent()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(1.0f,2.0f,3.05f,4.0f);
	
	// q1.isEquivalent(q2, 0.1f) 
	bvalue1 = q1.isEquivalent(q2, 0.1f);

	CHECK( bvalue1 == true );
}

TEST( QuatIsEquivalent3, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isEquivalent()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(1.0f,2.0f,3.05f,-4.0f);
	
	// q1.isEquivalent(q2, 0.1f) 
	bvalue1 = q1.isEquivalent(q2, 0.1f);

	CHECK( bvalue1 == false );
}

TEST( QuatIsConjugateEqual, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isConjugateEqual()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(-1.0f,-2.0f,-3.05f,4.0f);

	// q1.isConjugateEqual(q2, 0.1f)
	bvalue1 = q1.isConjugateEqual(q2, 0.1f);
	
	CHECK( bvalue1 == true );
}

TEST( QuatIsConjugateEqual2, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isConjugateEqual()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	q2.set(-1.0f,-2.0f,-3.05f,-4.0f);

	// q1.isConjugateEqual(q2, 0.1f) 
	bvalue1 = q1.isConjugateEqual(q2, 0.1f);
;
	CHECK( bvalue1 == false );
}

TEST( QuatIsIdentity, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isIdentity()
	q1.set(0.0f,0.0f,0.0f,1.0f);

	// q1.isIdentity(0.1f) 
	bvalue1 = q1.isIdentity(0.1f);
	
	CHECK( bvalue1 == true );
}

TEST( QuatIsIdentity2, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isIdentity()
	q1.set(0.0f,0.0f,0.0f,4.0f);

	// q1.isIdentity(0.1f) 
	bvalue1 = q1.isIdentity(0.1f);
	CHECK( bvalue1 == false );
}

TEST( QuatIsNormalized, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isNormalized()
	q1.set( 0.182574f,0.365148f,0.547723f,0.730297f);
	
	// q1.isNormalized(0.1f) 
	bvalue1 = q1.isNormalized(0.1f);
	CHECK( bvalue1 == true );
}

TEST( QuatIsNormalized2, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isNormalized()
	q1.set( 0.2174f,0.465148f,0.647723f,0.730297f);
	
	// q1.isNormalized(0.1f) 
	bvalue1 = q1.isNormalized(0.1f);
	CHECK( bvalue1 == false );
}

TEST( QuatIsZero, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isZero()
	q1.set(0.023f, 0.0f, 0.0f, 1.05f);
	
	// q1.isZero(0.0f) 
	bvalue1 = q1.isZero(0.0f);
	
	CHECK( bvalue1 == false );
}

TEST( QuatIsZero2, QuatBooleanTests )
{
	Quat  q1,q2;
	bool bvalue1;

	// isZero()
	q1.set(0.0f, 0.0f, 0.0f, 0.05f);
	
	// q1.isZero(0.1f) 
	bvalue1 = q1.isZero(0.1f);
	CHECK( bvalue1 == true );
}



/***** END of QuatBoolean.CPP *****************************************************************/