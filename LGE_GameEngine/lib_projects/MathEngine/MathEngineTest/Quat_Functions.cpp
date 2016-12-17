/*****************************************************************************/
/*                                                                           */
/* File: TestQuat.cpp                                                        */
/*                                                                           */
/* Primative Quat Class testbed                                              */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* system includes:                                                          */
/*****************************************************************************/

/*****************************************************************************/
/* user includes:                                                            */
/*****************************************************************************/
#include "UnitTest.h"
#include "MathEngine.h"
using namespace lge;
#define eq  		Util::isEqual 


/*****************************************************************************/
/* prototypes:                                                               */
/*****************************************************************************/

void verifyRot2Angle( float a1, float a2, bool &result );
void verifyRot3Angle( float a1, float a2, float a3, bool &result );

/*****************************************************************************/
/* Quat Test:                                                              */
/*****************************************************************************/


/*****************************************************************************/
/* QuatFunctions:                                                          */
/*****************************************************************************/


TEST( QuatFunctions, QuatFunctionsTests )
{
	// Quat Functions tests:
	CHECK( 1 );
}


TEST( getConjugate, QuatFunctionsTests )
{
	Matrix	mm2,mm3;
	Quat	q1,q2,q3,qtmp;
	Vect	v1,v2,v3,v4;
	
	// Conjugate

	//q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);
	Quat qx( ROT_X, MATH_2PI3);
	Quat qy(ROT_Y,MATH_3PI8);
	Quat qz(ROT_Z,MATH_3PI4);

	// => q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4
	q1 = qx*qy*qz;
	
	
	CHECK( eq(q1[x],0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],0.6035f,MATH_TOLERANCE) );
	
	q2 = q1.getConj();
	// => q2 = q1.getConj();\n"););

	
	CHECK( eq(q2[x],-0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q2[y],-0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q2[z],-0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q2[w],0.6035f,MATH_TOLERANCE) );


	// Matrix to Quat
	//m2.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);
	Matrix mx(ROT_X, MATH_2PI3);
	Matrix my(ROT_Y, MATH_3PI8);
	Matrix mz(ROT_Z, MATH_3PI4);

	mm2 = mx * my * mz;

	qtmp.set( mm2 );
	
	CHECK( eq(q1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	mm3.set(q1);

	CHECK( eq(mm2[m0],mm3[m0],MATH_TOLERANCE) );
	CHECK( eq(mm2[m1],mm3[m1],MATH_TOLERANCE) );
	CHECK( eq(mm2[m2],mm3[m2],MATH_TOLERANCE) );
	CHECK( eq(mm2[m3],mm3[m3],MATH_TOLERANCE) );
	CHECK( eq(mm2[m4],mm3[m4],MATH_TOLERANCE) );
	CHECK( eq(mm2[m5],mm3[m5],MATH_TOLERANCE) );
	CHECK( eq(mm2[m6],mm3[m6],MATH_TOLERANCE) );
	CHECK( eq(mm2[m7],mm3[m7],MATH_TOLERANCE) );
	CHECK( eq(mm2[m8],mm3[m8],MATH_TOLERANCE) );
	CHECK( eq(mm2[m9],mm3[m9],MATH_TOLERANCE) );
	CHECK( eq(mm2[m10],mm3[m10],MATH_TOLERANCE) );
	CHECK( eq(mm2[m11],mm3[m11],MATH_TOLERANCE) );
	CHECK( eq(mm2[m12],mm3[m12],MATH_TOLERANCE) );
	CHECK( eq(mm2[m13],mm3[m13],MATH_TOLERANCE) );
	CHECK( eq(mm2[m14],mm3[m14],MATH_TOLERANCE) );
	CHECK( eq(mm2[m15],mm3[m15],MATH_TOLERANCE) );
				
}



TEST( QuatConjugateInPlace, QuatFunctionsTests )
{
	Quat q1;
	
	// Conjugate in place 

	//q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);
	// => q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);
	Quat qx( ROT_X, MATH_2PI3);
	Quat qy(ROT_Y,MATH_3PI8);
	Quat qz(ROT_Z,MATH_3PI4);

	// => q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4
	q1 = qx*qy*qz;
	
	CHECK( eq(q1[x],0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],0.6035f,MATH_TOLERANCE) );
	
	q1.conj();
	// => q1.conj()

	
	CHECK( eq(q1[x],-0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],-0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],-0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],0.6035f,MATH_TOLERANCE) );

}


TEST( QuatConjugateByValue, QuatFunctionsTests )
{
	Quat q1,q2,qtmp;
	Matrix mm2, mm3;
	
	// Conjugate by value
	// q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);
	Quat qx( ROT_X, MATH_2PI3);
	Quat qy(ROT_Y,MATH_3PI8);
	Quat qz(ROT_Z,MATH_3PI4);

	// => q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4
	q1 = qx*qy*qz;
	
	CHECK( eq(q1[x],0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],0.6035f,MATH_TOLERANCE) );
	
	q2 = q1.getConj();
	// => q2 = q1.getConj();
	
	CHECK( eq(q2[x],-0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q2[y],-0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q2[z],-0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q2[w],0.6035f,MATH_TOLERANCE) );

	// Matrix to Quat
	//m2.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);

	Matrix mx(ROT_X, MATH_2PI3);
	Matrix my(ROT_Y, MATH_3PI8);
	Matrix mz(ROT_Z, MATH_3PI4);

	mm2 = mx * my * mz;




	qtmp.set( mm2 );
	
	CHECK( eq(q1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	mm3.set(q1);
	CHECK( eq(mm2[m0],mm3[m0],MATH_TOLERANCE) );
	CHECK( eq(mm2[m1],mm3[m1],MATH_TOLERANCE) );
	CHECK( eq(mm2[m2],mm3[m2],MATH_TOLERANCE) );
	CHECK( eq(mm2[m3],mm3[m3],MATH_TOLERANCE) );
	CHECK( eq(mm2[m4],mm3[m4],MATH_TOLERANCE) );
	CHECK( eq(mm2[m5],mm3[m5],MATH_TOLERANCE) );
	CHECK( eq(mm2[m6],mm3[m6],MATH_TOLERANCE) );
	CHECK( eq(mm2[m7],mm3[m7],MATH_TOLERANCE) );
	CHECK( eq(mm2[m8],mm3[m8],MATH_TOLERANCE) );
	CHECK( eq(mm2[m9],mm3[m9],MATH_TOLERANCE) );
	CHECK( eq(mm2[m10],mm3[m10],MATH_TOLERANCE) );
	CHECK( eq(mm2[m11],mm3[m11],MATH_TOLERANCE) );
	CHECK( eq(mm2[m12],mm3[m12],MATH_TOLERANCE) );
	CHECK( eq(mm2[m13],mm3[m13],MATH_TOLERANCE) );
	CHECK( eq(mm2[m14],mm3[m14],MATH_TOLERANCE) );
	CHECK( eq(mm2[m15],mm3[m15],MATH_TOLERANCE) );
}




TEST( QuatTransposeToDest, QuatFunctionsTests )
{
	// transpose
	// transpose to destination
	Quat q1,q2,q3,qtmp;
	//q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);

	Quat qx( ROT_X, MATH_2PI3);
	Quat qy(ROT_Y,MATH_3PI8);
	Quat qz(ROT_Z,MATH_3PI4);

	// => q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4
	q1 = qx*qy*qz;

	CHECK( eq(q1[x],0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],0.6035f,MATH_TOLERANCE) );
	
	q2 = q1.getT();

	// => q2 = q1.getT()
	
	CHECK( eq(q2[x],-0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q2[y],-0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q2[z],-0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q2[w],0.6035f,MATH_TOLERANCE) );

	// Matrix to Quat
	Matrix mm2, mm3;
	//mm2.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);
	Matrix mx(ROT_X, MATH_2PI3);
	Matrix my(ROT_Y, MATH_3PI8);
	Matrix mz(ROT_Z, MATH_3PI4);

	mm2 = mx * my * mz;

	qtmp.set( mm2 );
	CHECK( eq(q1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	mm3.set(q1);

	CHECK( eq(mm2[m0],mm3[m0],MATH_TOLERANCE) );
	CHECK( eq(mm2[m1],mm3[m1],MATH_TOLERANCE) );
	CHECK( eq(mm2[m2],mm3[m2],MATH_TOLERANCE) );
	CHECK( eq(mm2[m3],mm3[m3],MATH_TOLERANCE) );
	CHECK( eq(mm2[m4],mm3[m4],MATH_TOLERANCE) );
	CHECK( eq(mm2[m5],mm3[m5],MATH_TOLERANCE) );
	CHECK( eq(mm2[m6],mm3[m6],MATH_TOLERANCE) );
	CHECK( eq(mm2[m7],mm3[m7],MATH_TOLERANCE) );
	CHECK( eq(mm2[m8],mm3[m8],MATH_TOLERANCE) );
	CHECK( eq(mm2[m9],mm3[m9],MATH_TOLERANCE) );
	CHECK( eq(mm2[m10],mm3[m10],MATH_TOLERANCE) );
	CHECK( eq(mm2[m11],mm3[m11],MATH_TOLERANCE) );
	CHECK( eq(mm2[m12],mm3[m12],MATH_TOLERANCE) );
	CHECK( eq(mm2[m13],mm3[m13],MATH_TOLERANCE) );
	CHECK( eq(mm2[m14],mm3[m14],MATH_TOLERANCE) );
	CHECK( eq(mm2[m15],mm3[m15],MATH_TOLERANCE) );

	// Matrix to Quat
	mm2.T();
	qtmp.set( mm2 );
	CHECK( eq(q2[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q2[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q2[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q2[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	mm3.set(q2);

	CHECK( eq(mm2[m0],mm3[m0],MATH_TOLERANCE) );
	CHECK( eq(mm2[m1],mm3[m1],MATH_TOLERANCE) );
	CHECK( eq(mm2[m2],mm3[m2],MATH_TOLERANCE) );
	CHECK( eq(mm2[m3],mm3[m3],MATH_TOLERANCE) );
	CHECK( eq(mm2[m4],mm3[m4],MATH_TOLERANCE) );
	CHECK( eq(mm2[m5],mm3[m5],MATH_TOLERANCE) );
	CHECK( eq(mm2[m6],mm3[m6],MATH_TOLERANCE) );
	CHECK( eq(mm2[m7],mm3[m7],MATH_TOLERANCE) );
	CHECK( eq(mm2[m8],mm3[m8],MATH_TOLERANCE) );
	CHECK( eq(mm2[m9],mm3[m9],MATH_TOLERANCE) );
	CHECK( eq(mm2[m10],mm3[m10],MATH_TOLERANCE) );
	CHECK( eq(mm2[m11],mm3[m11],MATH_TOLERANCE) );
	CHECK( eq(mm2[m12],mm3[m12],MATH_TOLERANCE) );
	CHECK( eq(mm2[m13],mm3[m13],MATH_TOLERANCE) );
	CHECK( eq(mm2[m14],mm3[m14],MATH_TOLERANCE) );
	CHECK( eq(mm2[m15],mm3[m15],MATH_TOLERANCE) );


	q3 = q2 * q1;
	CHECK( eq(q3[x],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[y],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[z],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[w],1.0f,MATH_TOLERANCE) );
	q3 = q1 * q2;
	CHECK( eq(q3[x],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[y],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[z],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[w],1.0f,MATH_TOLERANCE) );

}



TEST( QuatTransposeByValue, QuatFunctionsTests )
{
	// "transpose by value
	Quat q1,q2,q3,qtmp;
	Matrix mm1,mm2,mm3;
	//q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);
	Quat qx( ROT_X, MATH_2PI3);
	Quat qy(ROT_Y,MATH_3PI8);
	Quat qz(ROT_Z,MATH_3PI4);

	// => q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4
	q1 = qx*qy*qz;

	CHECK( eq(q1[x],0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],0.6035f,MATH_TOLERANCE) );

	q2 = q1.getT();

	// => q2 = q1.getT()

	CHECK( eq(q2[x],-0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q2[y],-0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q2[z],-0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q2[w],0.6035f,MATH_TOLERANCE) );

	// Matrix to Quat
	//m2.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);
	Matrix mx(ROT_X, MATH_2PI3);
	Matrix my(ROT_Y, MATH_3PI8);
	Matrix mz(ROT_Z, MATH_3PI4);

	mm2 = mx * my * mz;

	qtmp.set( mm2 );
	CHECK( eq(q1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	mm3.set(q1);

	CHECK( eq(mm2[m0],mm3[m0],MATH_TOLERANCE) );
	CHECK( eq(mm2[m1],mm3[m1],MATH_TOLERANCE) );
	CHECK( eq(mm2[m2],mm3[m2],MATH_TOLERANCE) );
	CHECK( eq(mm2[m3],mm3[m3],MATH_TOLERANCE) );
	CHECK( eq(mm2[m4],mm3[m4],MATH_TOLERANCE) );
	CHECK( eq(mm2[m5],mm3[m5],MATH_TOLERANCE) );
	CHECK( eq(mm2[m6],mm3[m6],MATH_TOLERANCE) );
	CHECK( eq(mm2[m7],mm3[m7],MATH_TOLERANCE) );
	CHECK( eq(mm2[m8],mm3[m8],MATH_TOLERANCE) );
	CHECK( eq(mm2[m9],mm3[m9],MATH_TOLERANCE) );
	CHECK( eq(mm2[m10],mm3[m10],MATH_TOLERANCE) );
	CHECK( eq(mm2[m11],mm3[m11],MATH_TOLERANCE) );
	CHECK( eq(mm2[m12],mm3[m12],MATH_TOLERANCE) );
	CHECK( eq(mm2[m13],mm3[m13],MATH_TOLERANCE) );
	CHECK( eq(mm2[m14],mm3[m14],MATH_TOLERANCE) );
	CHECK( eq(mm2[m15],mm3[m15],MATH_TOLERANCE) );

	// Matrix to Quat
	mm2.T();
	qtmp.set( mm2 );
	CHECK( eq(q2[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q2[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q2[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q2[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	mm3.set(q2);

	CHECK( eq(mm2[m0],mm3[m0],MATH_TOLERANCE) );
	CHECK( eq(mm2[m1],mm3[m1],MATH_TOLERANCE) );
	CHECK( eq(mm2[m2],mm3[m2],MATH_TOLERANCE) );
	CHECK( eq(mm2[m3],mm3[m3],MATH_TOLERANCE) );
	CHECK( eq(mm2[m4],mm3[m4],MATH_TOLERANCE) );
	CHECK( eq(mm2[m5],mm3[m5],MATH_TOLERANCE) );
	CHECK( eq(mm2[m6],mm3[m6],MATH_TOLERANCE) );
	CHECK( eq(mm2[m7],mm3[m7],MATH_TOLERANCE) );
	CHECK( eq(mm2[m8],mm3[m8],MATH_TOLERANCE) );
	CHECK( eq(mm2[m9],mm3[m9],MATH_TOLERANCE) );
	CHECK( eq(mm2[m10],mm3[m10],MATH_TOLERANCE) );
	CHECK( eq(mm2[m11],mm3[m11],MATH_TOLERANCE) );
	CHECK( eq(mm2[m12],mm3[m12],MATH_TOLERANCE) );
	CHECK( eq(mm2[m13],mm3[m13],MATH_TOLERANCE) );
	CHECK( eq(mm2[m14],mm3[m14],MATH_TOLERANCE) );
	CHECK( eq(mm2[m15],mm3[m15],MATH_TOLERANCE) );

}



TEST( QuatTransposeInplace, QuatFunctionsTests )
{
	// transpose inplace
	Quat q1;
	//q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4);
	Quat qx( ROT_X, MATH_2PI3);
	Quat qy(ROT_Y,MATH_3PI8);
	Quat qz(ROT_Z,MATH_3PI4);

	// => q1.set(ROT_XYZ,MATH_2PI3,MATH_3PI8,MATH_3PI4
	q1 = qx*qy*qz;

	
	CHECK( eq(q1[x],0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],0.6035f,MATH_TOLERANCE) );

	q1.T();
	// => q1.T();

	CHECK( eq(q1[x],-0.01887f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],-0.7715f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],-0.1999f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],0.6035f,MATH_TOLERANCE) );
}



TEST( QuatMag, QuatFunctionsTests )
{
	// magnitude()
	Quat q1;
	float value;
	q1.set(1.0f,2.0f,3.0f,4.0f);

	// => mag = q1.mag() 
	value = q1.mag();
	
	CHECK( eq(value,5.477225f,MATH_TOLERANCE));
}

TEST( QuatMagSquared, QuatFunctionsTests )
{
	// magnitude Squared()
	
	Quat q1;
	float value;
	q1.set(1.0f,2.0f,3.0f,4.0f);
	
	// => value = q1.magSquared() 
	value = q1.magSquared();

	CHECK( eq(value,30.0f,MATH_TOLERANCE));
}

TEST( QuatInvMag, QuatFunctionsTests )
{
	// inverse magnitude()
	Quat q1;
	float value;

	q1.set(1.0f,2.0f,3.0f,4.0f);
	// => invMag = q1.invMag() 
	value = q1.invMag();

	CHECK( eq(value,0.1825742f,MATH_TOLERANCE) );
}



TEST( Norm, QuatFunctionsTests )
{
	Quat q1,q2;
	// norm()

	q1.set(1.0f,2.0f,3.0f,4.0f);
	// => q2 = q1.norm() 
	q2 = q1.norm();

	CHECK( eq(q2.mag(),1.0f,MATH_TOLERANCE) );
	CHECK( eq(q1[x],0.18257418f,MATH_TOLERANCE));
	CHECK( eq(q1[y],0.36514837f,MATH_TOLERANCE));
	CHECK( eq(q1[z],0.54772258f,MATH_TOLERANCE));
	CHECK( eq(q1[w],0.73029673f,MATH_TOLERANCE));
	
	CHECK( q1.isNormalized(MATH_TOLERANCE) );
	
	CHECK( eq(q1.magSquared(),1.0f, MATH_TOLERANCE));
	
	CHECK( eq(q2[x],0.18257418f,MATH_TOLERANCE));
	CHECK( eq(q2[y],0.36514837f,MATH_TOLERANCE));
	CHECK( eq(q2[z],0.54772258f,MATH_TOLERANCE));
	CHECK( eq(q2[w],0.73029673f,MATH_TOLERANCE));
	
	CHECK( q2.isNormalized(MATH_TOLERANCE) );
	CHECK( eq(q2.magSquared(),1.0f, MATH_TOLERANCE));
	
}



TEST( getNorm, QuatFunctionsTests )
{
	Quat q1,q2;
	// getNorm()
	q1.set(1.0f,2.0f,3.0f,4.0f);
	// => q2 = q1.getNorm(); 
	q2 = q1.getNorm();


	CHECK( eq(q2.mag(),1.0f,MATH_TOLERANCE) );
	CHECK( eq(q2[x],0.18257418f,MATH_TOLERANCE));
	CHECK( eq(q2[y],0.36514837f,MATH_TOLERANCE));
	CHECK( eq(q2[z],0.54772258f,MATH_TOLERANCE));
	CHECK( eq(q2[w],0.73029673f,MATH_TOLERANCE));
	
	CHECK( (q1[x] == 1.0f) );
	CHECK( (q1[y] == 2.0f) );
	CHECK( (q1[z] == 3.0f) );
	CHECK( (q1[w] == 4.0f));
	
}


TEST( getInverse, QuatFunctionsTests )
{
	Quat q1,q2,q3;
	// getInv()\n");
	q1.set(1.0f,2.0f,3.0f,4.0f);
	// => q2 = q1.getInv() 
	q2 = q1.getInv();
	
	CHECK( eq(q1[x],1.0f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],2.0f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],3.0f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],4.0f,MATH_TOLERANCE));
	
	CHECK( eq(q2[x],-0.0333333f,MATH_TOLERANCE));
	CHECK( eq(q2[y],-0.0666666f,MATH_TOLERANCE));
	CHECK( eq(q2[z],-0.1000000f,MATH_TOLERANCE));
	CHECK( eq(q2[w],0.1333333f,MATH_TOLERANCE));
	
	q3 = q1 * q2;
	
	CHECK( eq(q3[x],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[y],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[z],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[w],1.0f,MATH_TOLERANCE) );
	
	q3 = q2 * q1;
	
	CHECK( eq(q3[x],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[y],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[z],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[w],1.0f,MATH_TOLERANCE));

}



TEST( Inverse, QuatFunctionsTests )
{
	Quat q1,q2,q3;
	// inverse()
	
	q1.set(1.0f,2.0f,3.0f,4.0f);
	// => q1.inv() 
	q2 = q1;
	q1.inv();

	
	CHECK( eq(q1[x],-0.0333333f,MATH_TOLERANCE) );
	CHECK( eq(q1[y],-0.0666666f,MATH_TOLERANCE) );
	CHECK( eq(q1[z],-0.1000000f,MATH_TOLERANCE) );
	CHECK( eq(q1[w],0.1333333f,MATH_TOLERANCE));
	
	q3 = q1 * q2;
	
	CHECK( eq(q3[x],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[y],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[z],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[w],1.0f,MATH_TOLERANCE) );
	
	q3 = q2 * q1;
	
	CHECK( eq(q3[x],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[y],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[z],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[w],1.0f,MATH_TOLERANCE));
	
}



TEST( QuatInverse_3, QuatFunctionsTests )
{
	Quat q1,q2,q3;
	// inverse()
	
	q1.set(1.0f,2.0f,3.0f,4.0f);
	// => q1.inv(q1) 
	q2 = q1;
	q1.inv();
	
	CHECK( eq(q2[x],1.0f,MATH_TOLERANCE) );
	CHECK( eq(q2[y],2.0f,MATH_TOLERANCE) );
	CHECK( eq(q2[z],3.0f,MATH_TOLERANCE) );
	CHECK( eq(q2[w],4.0f,MATH_TOLERANCE));
	
	CHECK( eq(q1[x],-0.033333335f,MATH_TOLERANCE));
	CHECK( eq(q1[y],-0.066666670f,MATH_TOLERANCE));
	CHECK( eq(q1[z],-0.10000001f,MATH_TOLERANCE));
	CHECK( eq(q1[w], 0.13333334f,MATH_TOLERANCE));
	
	
	q3 = q1 * q2;
	
	CHECK( eq(q3[x],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[y],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[z],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[w],1.0f,MATH_TOLERANCE) );
	
	q3 = q2 * q1;
	
	CHECK( eq(q3[x],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[y],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[z],0.0f,MATH_TOLERANCE) );
	CHECK( eq(q3[w],1.0f,MATH_TOLERANCE));
	
}


TEST( Inverse_Transpose_Test, QuatFunctionsTests )
{
	Quat q1,q2,q3;
	// inverse()
	
	q1.set(1.0f,2.0f,3.0f,4.0f);
	// => q1.inv(q1) 
	q2 = q1.norm();
	q2.inv();
	
	CHECK( eq(q1.mag(), 1.0f, MATH_TOLERANCE));
	CHECK( eq(q1[x], 0.18257418f,MATH_TOLERANCE));
	CHECK( eq(q1[y], 0.36514837f,MATH_TOLERANCE));
	CHECK( eq(q1[z], 0.54772258f,MATH_TOLERANCE));
	CHECK( eq(q1[w], 0.73029673f,MATH_TOLERANCE));
	
	CHECK( eq(q2[x], -0.18257418f,MATH_TOLERANCE));
	CHECK( eq(q2[y], -0.36514837f,MATH_TOLERANCE));
	CHECK( eq(q2[z], -0.54772258f,MATH_TOLERANCE));
	CHECK( eq(q2[w], 0.73029673f,MATH_TOLERANCE));
	
	q3 = q1 * q2;
	
	CHECK( eq(q3[x], 0.0f,MATH_TOLERANCE));
	CHECK( eq(q3[y], 0.0f,MATH_TOLERANCE));
	CHECK( eq(q3[z], 0.0f,MATH_TOLERANCE));
	CHECK( eq(q3[w], 1.0f,MATH_TOLERANCE));
	
}



TEST( QuatLqcvq_Lqvqc_1, QuatFunctionsTests )
{
	// Lqcvq() and Lqvqc() operator
	
	//Matrix Mxyz(ROT_XYZ,MATH_PI3,MATH_3PI4,MATH_PI2);
	Matrix mx(ROT_X,MATH_PI3);
	Matrix my(ROT_Y,MATH_3PI4);
	Matrix mz(ROT_Z,MATH_PI2);
	Matrix Mxyz = mx*my*mz;

	Matrix MTxyz(Mxyz.getT());
	//Quat   Qxyz(ROT_XYZ,MATH_PI3,MATH_3PI4,MATH_PI2);
	Quat qx(ROT_X,MATH_PI3);
	Quat qy(ROT_Y,MATH_3PI4);
	Quat qz(ROT_Z,MATH_PI2);
	Quat Qxyz = qx*qy*qz;

	Quat   QTxyz(Qxyz.getT());

	Vect vx(1.0f, 0.0f, 0.0f, 1.0f);
	Vect vy(0.0f, 1.0f, 0.0f, 1.0f);
	Vect vz(0.0f, 0.0f, 1.0f, 1.0f);
	Vect vo(1.0f,2.0f,3.0f);
	Vect Vout1_x,Vout1_y,Vout1_z,Vout1_o;
	Vect Vout2_x,Vout2_y,Vout2_z,Vout2_o;

	Vout1_x = vx * Mxyz;
	Vout1_y = vy * Mxyz;
	Vout1_z = vz * Mxyz;
	Vout1_o = vo * Mxyz;

	// Vout = vIn * Quat
	Qxyz.Lqcvq(vx, Vout2_x);
	Qxyz.Lqcvq(vy, Vout2_y);
	Qxyz.Lqcvq(vz, Vout2_z);
	Qxyz.Lqcvq(vo, Vout2_o);

	// => Vout1_x = vx * Mxyz;
	// => Vout1_y = vy * Mxyz;
	// => Vout1_z = vz * Mxyz;
	// => Vout1_o = vo * Mxyz;
	// => Qxyz.Lqcvq(vx, Vout2_x);
	// => Qxyz.Lqcvq(vy, Vout2_y);
	// => Qxyz.Lqcvq(vz, Vout2_z);  
	// => Qxyz.Lqcvq(vo, Vout2_o);  

	CHECK( eq(Vout1_x[x],Vout2_x[x],MATH_TOLERANCE) );
	CHECK( eq(Vout1_x[y],Vout2_x[y],MATH_TOLERANCE) );
	CHECK( eq(Vout1_x[z],Vout2_x[z],MATH_TOLERANCE) );
	CHECK( eq(Vout1_x[w],Vout2_x[w],MATH_TOLERANCE) );

	CHECK( eq(Vout1_y[x],Vout2_y[x],MATH_TOLERANCE) );
	CHECK( eq(Vout1_y[y],Vout2_y[y],MATH_TOLERANCE) );
	CHECK( eq(Vout1_y[z],Vout2_y[z],MATH_TOLERANCE) );
	CHECK( eq(Vout1_y[w],Vout2_y[w],MATH_TOLERANCE) );

	CHECK( eq(Vout1_z[x],Vout2_z[x],MATH_TOLERANCE) );
	CHECK( eq(Vout1_z[y],Vout2_z[y],MATH_TOLERANCE) );
	CHECK( eq(Vout1_z[z],Vout2_z[z],MATH_TOLERANCE) );
	CHECK( eq(Vout1_z[w],Vout2_z[w],MATH_TOLERANCE) );

	CHECK( eq(Vout1_o[x],Vout2_o[x],MATH_TOLERANCE) );
	CHECK( eq(Vout1_o[y],Vout2_o[y],MATH_TOLERANCE) );
	CHECK( eq(Vout1_o[z],Vout2_o[z],MATH_TOLERANCE) );
	CHECK( eq(Vout1_o[w],Vout2_o[w],MATH_TOLERANCE) );

	Vout1_x = vx * Mxyz.getT();
	Vout1_y = vy * Mxyz.getT();
	Vout1_z = vz * Mxyz.getT();
	Vout1_o = vo * Mxyz.getT();

	// Vout = vIn * Quat.T()
	Qxyz.Lqvqc(vx, Vout2_x);
	Qxyz.Lqvqc(vy, Vout2_y);
	Qxyz.Lqvqc(vz, Vout2_z);
	Qxyz.Lqvqc(vo, Vout2_o);

	// => Vout1_x = vx * Mxyz.T();
	// => Vout1_y = vy * Mxyz.T();
	// => Vout1_z = vz * Mxyz.T();
	// => Vout1_o = vo * Mxyz.T();
	// => Qxyz.Lqvqc(vx, Vout2_x);
	// => Qxyz.Lqvqc(vy, Vout2_y);
	// => Qxyz.Lqvqc(vz, Vout2_z); 
	// => Qxyz.Lqvqc(vo, Vout2_o);  


	CHECK( eq(Vout1_x[x],Vout2_x[x],MATH_TOLERANCE) );
	CHECK( eq(Vout1_x[y],Vout2_x[y],MATH_TOLERANCE) );
	CHECK( eq(Vout1_x[z],Vout2_x[z],MATH_TOLERANCE) );
	CHECK( eq(Vout1_x[w],Vout2_x[w],MATH_TOLERANCE) );

	CHECK( eq(Vout1_y[x],Vout2_y[x],MATH_TOLERANCE) );
	CHECK( eq(Vout1_y[y],Vout2_y[y],MATH_TOLERANCE) );
	CHECK( eq(Vout1_y[z],Vout2_y[z],MATH_TOLERANCE) );
	CHECK( eq(Vout1_y[w],Vout2_y[w],MATH_TOLERANCE) );

	CHECK( eq(Vout1_z[x],Vout2_z[x],MATH_TOLERANCE) );
	CHECK( eq(Vout1_z[y],Vout2_z[y],MATH_TOLERANCE) );
	CHECK( eq(Vout1_z[z],Vout2_z[z],MATH_TOLERANCE) );
	CHECK( eq(Vout1_z[w],Vout2_z[w],MATH_TOLERANCE) );

	CHECK( eq(Vout1_o[x],Vout2_o[x],MATH_TOLERANCE) );
	CHECK( eq(Vout1_o[y],Vout2_o[y],MATH_TOLERANCE) );
	CHECK( eq(Vout1_o[z],Vout2_o[z],MATH_TOLERANCE) );
	CHECK( eq(Vout1_o[w],Vout2_o[w],MATH_TOLERANCE) );

}



TEST( dot_Test, QuatFunctionsTests )
{
	Quat q1;
	
	q1.set(1.0f,2.0f,3.0f,4.0f);

	// 4D dot product
	float value = q1.dot(q1);

	CHECK( eq(value, 30.0f, MATH_TOLERANCE));
	CHECK( eq(q1[x],1.0f,MATH_TOLERANCE));
	CHECK( eq(q1[y], 2.0f,MATH_TOLERANCE));
	CHECK( eq(q1[z], 3.0f,MATH_TOLERANCE));
	CHECK( eq(q1[w], 4.0f,MATH_TOLERANCE));
}


TEST( Assignment_Matrix_Test, QuatFunctionsTests )
{
	Quat q1;
	Matrix A(ROT_XYZ, 0.34f, -2.3f, 1.2f);
	
	Quat q2(A);

	q1 = A;

	Matrix B(q1);

	CHECK( eq(A[m0], B[m0], MATH_TOLERANCE));
	CHECK( eq(A[m1], B[m1], MATH_TOLERANCE));
	CHECK( eq(A[m2], B[m2], MATH_TOLERANCE));
	CHECK( eq(A[m3], B[m3], MATH_TOLERANCE));
	CHECK( eq(A[m4], B[m4], MATH_TOLERANCE));
	CHECK( eq(A[m5], B[m5], MATH_TOLERANCE));
	CHECK( eq(A[m6], B[m6], MATH_TOLERANCE));
	CHECK( eq(A[m7], B[m7], MATH_TOLERANCE));
	CHECK( eq(A[m8], B[m8], MATH_TOLERANCE));
	CHECK( eq(A[m9], B[m9], MATH_TOLERANCE));
	CHECK( eq(A[m10], B[m10], MATH_TOLERANCE));
	CHECK( eq(A[m11], B[m11], MATH_TOLERANCE));
	CHECK( eq(A[m12], B[m12], MATH_TOLERANCE));
	CHECK( eq(A[m13], B[m13], MATH_TOLERANCE));
	CHECK( eq(A[m14], B[m14], MATH_TOLERANCE));
	CHECK( eq(A[m15], B[m15], MATH_TOLERANCE));



}

/***** END of TESTQUAT.CPP *****************************************************************/