/*****************************************************************************/
/*                                                                           */
/* File: QuatSetGet.cpp                                                      */
/*                                                                           */
/* Primative Quat set/get Class testbed                                      */
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
/* Quat Set:                                                                 */
/*****************************************************************************/

TEST( QuatSetGet, QuatSetGetTests )
{
	CHECK( 1 );
}


TEST( Quat_Set_everyElement, QuatSetGetTests )
{
	Quat q1;
	// Set every element
	q1.set(2.0f,3.0f,4.0f,5.0f);

	CHECK( 2.0f == q1[x] );
	CHECK( 3.0f == q1[y] );
	CHECK( 4.0f == q1[z] );
	CHECK( 5.0f == q1[w] );
}



TEST( Vect_set_3_elements, QuatSetGetTests )
{
	Vect A(2.0f, 3.0f, 4.0f, 5.0f);

	CHECK( A[x] == 2.0f );
	CHECK( A[y] == 3.0f );
	CHECK( A[z] == 4.0f );
	CHECK( A[w] == 5.0f );

	A.set(10.0f, 20.0f, 30.0f);

	CHECK( A[x] == 10.0f );
	CHECK( A[y] == 20.0f );
	CHECK( A[z] == 30.0f );
	CHECK( A[w] == 1.0f );
}



TEST( Quat_Set_Vect_Real, QuatSetGetTests )
{
	Quat q1;
	Vect v1;

	// Set Vector component, Real component
	v1.set(12.0f,13.0f,14.0f,15.0f);
	q1.set(v1,20.0f);

	CHECK( ( 12.0f == q1[x] ) );
	CHECK( ( 13.0f == q1[y] ) );
	CHECK( ( 14.0f == q1[z] ) );
	CHECK( ( 20.0f == q1[w] ) );
}


TEST( Quat_Set_Quat_From_Matrix, QuatSetGetTests )
{
	Quat q1;
	Matrix M2,M3;
	// Set Quaternion from a Matrix

	
	Matrix Rx(ROT_X,MATH_PI2);
	Matrix Ry(ROT_Y,-MATH_PI3);
	Matrix Rz(ROT_Z,-MATH_7PI8);
	M2 = Rx * Ry * Rz;
	
	q1.set(M2);
	
	
	CHECK( eq(0.2274f,q1[x],MATH_TOLERANCE) );
	CHECK( eq(0.6693f,q1[y],MATH_TOLERANCE) );
	CHECK( eq(0.5318f,q1[z],MATH_TOLERANCE) );
	CHECK( eq(-0.4661f,q1[w],MATH_TOLERANCE) );

	M3.set(q1);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}






TEST( Quat_Set_IDENTITY, QuatSetGetTests )
{
	Quat q2,qtmp;
	Matrix M2,M3;
	// Set Special Type:
	q2.set(IDENTITY);

	CHECK( (q2[x] == 0.0f) );
	CHECK( (q2[y] == 0.0f) );
	CHECK( (q2[z] == 0.0f) );
	CHECK( (q2[w] == 1.0f) );


	M2.set(IDENTITY);
	qtmp.set( M2 );
	CHECK( eq(q2[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q2[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q2[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q2[w],qtmp[w],MATH_TOLERANCE) );
	
	M3.set(q2);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}






TEST( Quat_Set_ZERO, QuatSetGetTests )
{
	Quat q3,qtmp;
	Matrix m2,m3;

	// Set Special Type:
	q3.set(ZERO);

	CHECK( (q3[x] == 0.0f) );
	CHECK( (q3[y] == 0.0f) );
	CHECK( (q3[z] == 0.0f) );
	CHECK( (q3[w] == 0.0f) );

}



TEST( Quat_Set_ROT_X_PI2, QuatSetGetTests )
{
	Quat q1,qtmp;
	Matrix M2,M3;
	// set Special Type:
	q1.set(ROT_X, MATH_PI2);

	// Matrix to Quaternion
	M2.set(ROT_X,MATH_PI2);
	qtmp.set( M2);
	CHECK( eq(q1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q1);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}



TEST( Quat_Set_ROT_X_PI, QuatSetGetTests )
{
	Quat q2,qtmp;
	Matrix M2,M3;
	// set Special Type:

	q2.set(ROT_X,MATH_PI);


	// Matrix to Quaternion
	M2.set(ROT_X,MATH_PI);
	qtmp.set( M2 );
	CHECK( eq(q2[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q2[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q2[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q2[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q2);


	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_Set_ROT_Y_PI2, QuatSetGetTests )
{
	Quat q3,qtmp;
	Matrix M2,M3;

	// set Special Type:
	q3.set(ROT_Y, MATH_PI2);

	// Matrix to Quaternion
	M2.set(ROT_Y,MATH_PI2);
	qtmp.set( M2 );
	CHECK( eq(q3[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q3[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q3[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q3[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q3);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_Set_ROT_Y_PI, QuatSetGetTests )
{
	Quat q4,qtmp;
	Matrix M2,M3;

	// set Special Type:

	q4.set(ROT_Y,MATH_PI);


	// Matrix to Quaternion
	M2.set(ROT_Y,MATH_PI);
	qtmp.set( M2 );
	CHECK( eq(q4[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q4[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q4[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q4[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q4);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_Set_ROT_Z_PI2, QuatSetGetTests )
{
	Quat q1,qtmp;
	Matrix M2,M3;
	// set Special Type:

	q1.set(ROT_Z,MATH_PI2);

	// Matrix to Quaternion
	M2.set(ROT_Z, MATH_PI2);
	qtmp.set( M2 );
	CHECK( eq(q1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q1);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_Set_ROT_Z_PI, QuatSetGetTests )
{
	Quat q2,qtmp;
	Matrix M2,M3;
	// set Special Type:

	q2.set(ROT_Z,MATH_PI);


	// Matrix to Quaternion
	M2.set(ROT_Z,MATH_PI);
	qtmp.set( M2 );
	CHECK( eq(q2[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q2[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q2[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q2[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q2);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_Set_ROT_X, QuatSetGetTests )
{
	Quat q1,qtmp;
	Matrix M2,M3;

	// set Rot_X Type  :
	q1.set(ROT_X, MATH_PI3);	


	// Matrix to Quaternion
	M2.set(ROT_X, MATH_PI3);	
	qtmp.set( M2 );
	CHECK( eq(q1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q1);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_Set_ROT_Y, QuatSetGetTests )
{
	Quat q2,qtmp;
	Matrix M2,M3;

	// set Rot_Y Type  :

	q2.set(ROT_Y, MATH_PI3);	


	// Matrix to Quaternion
	M2.set(ROT_Y, MATH_PI3);	
	qtmp.set( M2 );
	CHECK( eq(q2[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q2[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q2[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q2[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q2);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}



TEST( Quat_Set_ROT_Z, QuatSetGetTests )
{
	Quat q3,qtmp;
	Matrix M2,M3;
	// set Rot_Z Type  :

	q3.set(ROT_Z, MATH_PI3);	


	// Matrix to Quaternion
	M2.set(ROT_Z, MATH_PI3);	
	qtmp.set( M2 );
	CHECK( eq(q3[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q3[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q3[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q3[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q3);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}




TEST( Quat_XY_set, QuatSetGetTests )
{
	// Rot_XY Type Constructor:
	Quat Qx;
	Qx.set(ROT_X, MATH_PI3);
	Quat Qy;
	Qy.set(ROT_Y, MATH_PI4);

	Quat Qxy;
	Qxy = Qx * Qy;

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;

	Matrix Mx(ROT_X, MATH_PI3);
	Matrix My(ROT_Y, MATH_PI4);
	M2 = Mx * My;

	qtmp.set( M2 );
	CHECK( eq(Qxy[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qxy[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qxy[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qxy[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qxy);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_XZ_set, QuatSetGetTests )
{
	// Rot_XZ Type Constructor:
	Quat Qx;
	Qx.set(ROT_X, MATH_PI3);
	Quat Qz;
	Qz.set(ROT_Z, MATH_PI4);
	Quat Qxz;
	
	Qxz = Qx * Qz;

	// Matrix to Quaternion
	Matrix M2, M3;
	Quat qtmp;
	Matrix Mx(ROT_X, MATH_PI3);
	Matrix Mz(ROT_Z, MATH_PI4);	
	M2 = Mx * Mz;

	qtmp.set( M2 );
	CHECK( eq(Qxz[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qxz[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qxz[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qxz[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qxz);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_YX_set, QuatSetGetTests )
{
	// Rot_YX Type Constructor:
	Quat Qy;
	Qy.set(ROT_Y, MATH_PI3);
	Quat Qx;
	Qx.set(ROT_X, MATH_PI4);
	Quat Qyx = Qy * Qx;

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;

	Matrix My(ROT_Y, MATH_PI3);
	Matrix Mx(ROT_X, MATH_PI4);	
	M2 = My * Mx;

	qtmp.set( M2 );
	CHECK( eq(Qyx[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qyx[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qyx[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qyx[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qyx);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_YZ_set, QuatSetGetTests )
{
	// Rot_YZ Type Constructor:
	Quat Qy;
	Qy.set(ROT_Y, MATH_PI3);
	Quat Qz;
	Qz.set(ROT_Z, MATH_PI4);
	Quat Qyz = Qy * Qz;

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;


	Matrix My(ROT_Y, MATH_PI3);
	Matrix Mz(ROT_Z, MATH_PI4);	
	M2 = My * Mz;


	qtmp.set( M2 );
	CHECK( eq(Qyz[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qyz[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qyz[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qyz[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qyz);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}



TEST( Quat_ZX_set, QuatSetGetTests )
{
	// Rot_ZX Type Constructor:
	Quat Qz;
	Qz.set(ROT_Z, MATH_PI3);
	Quat Qx;
	Qx.set(ROT_X, MATH_PI4);
	Quat Qzx =Qz * Qx;


	 // Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;
	

	Matrix Mz(ROT_Z, MATH_PI3);
	Matrix Mx(ROT_X, MATH_PI4);	
	M2 = Mz * Mx;

	qtmp.set( M2 );
	CHECK( eq(Qzx[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qzx[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qzx[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qzx[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qzx);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_ZY_set, QuatSetGetTests )
{
	// Rot_ZY Type Constructor:

	Quat Qz;
	Qz.set(ROT_Z, MATH_PI3);
	Quat Qy;
	Qy.set(ROT_Y, MATH_PI4);
	Quat Qzy =Qz * Qy;

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;


	Matrix Mz(ROT_Z, MATH_PI3);
	Matrix My(ROT_Y, MATH_PI4);	
	M2 = Mz * My;

	qtmp.set( M2 );
	CHECK( eq(Qzy[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qzy[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qzy[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qzy[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qzy);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}



TEST( Quat_XYZ_set, QuatSetGetTests )
{
	// Rot_XYZ Type Constructor:
	Quat Qx;
	Qx.set(ROT_X, MATH_PI3 );
	Quat Qy;
	Qy.set(ROT_Y, MATH_5PI8);
	Quat Qz;
	Qz.set(ROT_Z, MATH_PI4 );
	Quat Qxyz = Qx * Qy * Qz;


	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;

	Matrix Mx(ROT_X, MATH_PI3);
	Matrix My(ROT_Y,  MATH_5PI8);
	Matrix Mz(ROT_Z,  MATH_PI4 );
	M2 = Mx * My * Mz;


	qtmp.set( M2 );
	CHECK( eq(Qxyz[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qxyz[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qxyz[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qxyz[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qxyz);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_XZY_set, QuatSetGetTests )
{
	// Rot_XZY Type Constructor:
	Quat Qx;
	Qx.set(ROT_X, MATH_PI3 );
	Quat Qz;
	Qz.set(ROT_Z, MATH_5PI8);
	Quat Qy;
	Qy.set(ROT_Y, MATH_PI4 );
	Quat Qxzy = Qx * Qz * Qy;

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;

	Matrix Mx(ROT_X, MATH_PI3);
	Matrix Mz(ROT_Z,  MATH_5PI8);
	Matrix My(ROT_Y,  MATH_PI4 );
	M2 = Mx * Mz * My;


	qtmp.set( M2 );
	CHECK( eq(Qxzy[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qxzy[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qxzy[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qxzy[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qxzy);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}



TEST( Quat_YXZ_set, QuatSetGetTests )
{
	// Rot_YXZ Type Constructor:


	Quat Qy;
	Qy.set(ROT_Y, MATH_PI3 );
	Quat Qx;
	Qx.set(ROT_X, MATH_5PI8);
	Quat Qz;
	Qz.set(ROT_Z, MATH_PI4 );
	Quat Qyxz = Qy * Qx * Qz;


	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;


	Matrix My(ROT_Y, MATH_PI3);
	Matrix Mx(ROT_X,  MATH_5PI8);
	Matrix Mz(ROT_Z,  MATH_PI4 );
	M2 = My * Mx * Mz;


	qtmp.set( M2 );
	CHECK( eq(Qyxz[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qyxz[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qyxz[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qyxz[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qyxz);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_YZX_set, QuatSetGetTests )
{
	// Rot_YZX Type Constructor:

	Quat Qy;
	Qy.set(ROT_Y, MATH_PI3 );
	Quat Qz;
	Qz.set(ROT_Z, MATH_5PI8);
	Quat Qx;
	Qx.set(ROT_X, MATH_PI4 );
	Quat Qyzx = Qy * Qz * Qx;

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;

	Matrix My(ROT_Y, MATH_PI3);
	Matrix Mz(ROT_Z,  MATH_5PI8);
	Matrix Mx(ROT_X,  MATH_PI4 );
	M2 = My * Mz * Mx;


	qtmp.set( M2 );
	CHECK( eq(Qyzx[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qyzx[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qyzx[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qyzx[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qyzx);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_ZXY_set, QuatSetGetTests )
{
	// Rot_ZXY Type Constructor:
	Quat Qz;
	Qz.set(ROT_Z, MATH_PI3 );
	Quat Qx;
	Qx.set(ROT_X, MATH_5PI8);
	Quat Qy;
	Qy.set(ROT_Y, MATH_PI4 );
	Quat Qzxy = Qz * Qx * Qy;

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;

	Matrix Mz(ROT_Z, MATH_PI3);
	Matrix Mx(ROT_X,  MATH_5PI8);
	Matrix My(ROT_Y,  MATH_PI4 );
	M2 = Mz * Mx * My;


	qtmp.set( M2 );
	CHECK( eq(Qzxy[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qzxy[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qzxy[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qzxy[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qzxy);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_ZYX_set, QuatSetGetTests )
{
	// Rot_ZYX Type Constructor:
	Quat Qz;
	Qz.set(ROT_Z, MATH_PI3 );
	Quat Qy;
	Qy.set(ROT_Y, MATH_5PI8);
	Quat Qx;
	Qx.set(ROT_X, MATH_PI4 );
	Quat Qzyx = Qz * Qy * Qx;

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;

	Matrix Mz(ROT_Z, MATH_PI3);
	Matrix My(ROT_Y,  MATH_5PI8);
	Matrix Mx(ROT_X,  MATH_PI4 );
	M2 = Mz * My * Mx;

	qtmp.set( M2 );
	CHECK( eq(Qzyx[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qzyx[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qzyx[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qzyx[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qzyx);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}





TEST( Quat_AXIS_ANGLE_set, QuatSetGetTests )
{
	// Axis and Angle Type Constructor:
	Vect  v11( 2.0f, 53.0f, 24.0f);
	Quat Qa1;
	Qa1.set(ROT_AXIS_ANGLE, v11, MATH_PI3 );

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;

	M2.set(ROT_AXIS_ANGLE, v11, MATH_PI3 );

	qtmp.set( M2 );
	CHECK( eq(Qa1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qa1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qa1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qa1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qa1);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );

}



TEST( Quat_ROT_ORIENT_set, QuatSetGetTests )
{
	// Orientation Type Constructor:

	Vect  v15( 2.0f, 53.0f, 24.0f);
	Vect  v16( 0.0f, -24.0f, 53.0f);
	Quat q56;
	q56.set(ROT_ORIENT, v15, v16 );

	Matrix M2,M3;
	Quat qtmp;

	M2.set(ROT_ORIENT, v15, v16 );
	qtmp.set( M2 );
	CHECK( eq(q56[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q56[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q56[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q56[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q56);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}


TEST( Quat_ROT_INVERSE_ORIENT_set, QuatSetGetTests )
{
	// Orientation Type Constructor:
	Vect  v17( 2.0f, 53.0f, 24.0f);
	Vect  v18( 0.0f, -24.0f, 53.0f);
	Quat q57;
	q57.set(ROT_INVERSE_ORIENT, v17, v18 );

	Matrix M2,M3;
	Quat qtmp;

	M2.set(ROT_INVERSE_ORIENT, v17, v18 );
	qtmp.set( M2 );
	CHECK( eq(q57[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q57[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q57[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q57[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q57);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );
}




TEST( Quat_Set_Each_ELEMENT, QuatSetGetTests )
{
	Quat q2;
	// set Quat each Element:
	q2.set( ZERO );

	q2[x] = 11.0f;
	q2[y] = 12.0f;
	q2[z] = 13.0f;
	q2[real] = 14.0f;

	CHECK( (q2[x] == 11.0f) );
	CHECK( (q2[y] == 12.0f) );
	CHECK( (q2[z] == 13.0f) );
	CHECK( (q2[w] == 14.0f) );
}

TEST( Quat_Set_From_VECT, QuatSetGetTests )
{
	Vect v1;
	Quat q2;
	// set Quat Vector Element:

	v1.set(3.0f,4.0f,5.0f,6.0f);

	q2.set( ZERO );

	q2.setVect(v1);

	CHECK( (q2[x] == 3.0f) );
	CHECK( (q2[y] == 4.0f) );
	CHECK( (q2[z] == 5.0f) );
	CHECK( (q2[w] == 0.0f) );
}
		

TEST( Quat_Get_Vect_elements, QuatSetGetTests )
{
	Quat q1;
	float tmp_x,tmp_y,tmp_z,tmp_real;

	// get Quat Vector Elements:

	q1.set(3.0f,4.0f,5.0f,6.0f);

	tmp_x = q1[x];
	tmp_y = q1[y];
	tmp_z = q1[z];
	tmp_real = q1[real];

	CHECK( (q1[x] == 3.0f) );
	CHECK( (q1[y] == 4.0f) );
	CHECK( (q1[z] == 5.0f) );
	CHECK( (q1[w] == 6.0f) );
	CHECK( (tmp_x == 3.0f) );
	CHECK( (tmp_y == 4.0f) );
	CHECK( (tmp_z == 5.0f) );
	CHECK( (tmp_real == 6.0f) );
}


TEST( Quat_Get_Vect, QuatSetGetTests )
{
	Quat q1;
	Vect v1;

	//  get Vector:
	q1.set(7.0f,8.0f,9.0f,10.0f);

	q1.getVect(v1);

	CHECK( (v1[x] == 7.0f) );
	CHECK( (v1[y] == 8.0f) );
	CHECK( (v1[z] == 9.0f) );
	CHECK( (v1[w] == 1.0f) );
	CHECK( (q1[x] == 7.0f) );
	CHECK( (q1[y] == 8.0f) );
	CHECK( (q1[z] == 9.0f) );
	CHECK( (q1[w] == 10.0f) );
}





TEST( Quat_Get_Angle_of_rotation, QuatSetGetTests )
{
	Quat q1,qtmp;
	Vect v1;
	Matrix M2, M3;

	//  get Angle of rotattion about the axis of rotation
	v1.set( 2.0f, 53.0f, 24.0f);
	q1.set(ROT_AXIS_ANGLE, v1, MATH_PI3 );

	// Matrix to Quaternion
	M2.set(ROT_AXIS_ANGLE, v1, MATH_PI3 );
	qtmp.set( M2 );
	CHECK( eq(q1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q1);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );

	float value;
	value = q1.getAngle();
	CHECK( eq(value,MATH_PI3,0.02f) );

}



TEST( Quat_Get_Axis_of_rotation, QuatSetGetTests )
{
	Quat q1,qtmp;
	Vect v1;
	Matrix M2, M3;

	//  get Axis of rotattion about the axis of rotation

	v1.set( 2.0f, 53.0f, 24.0f);

	q1.set(ROT_AXIS_ANGLE, v1, MATH_PI3 );


	// Matrix to Quaternion
	M2.set(ROT_AXIS_ANGLE, v1, MATH_PI3 );
	qtmp.set( M2 );
	CHECK( eq(q1[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q1[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q1[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q1[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q1);

	CHECK( eq(M2[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(M2[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(M2[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(M2[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(M2[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(M2[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(M2[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(M2[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(M2[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(M2[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(M2[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(M2[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(M2[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(M2[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(M2[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(M2[m15],M3[m15],MATH_TOLERANCE) );

	//  get axis of rotation:
	q1.set(7.0f,8.0f,9.0f,10.0f);

	q1.getAxis(v1);

	CHECK( (v1[x] == 7.0f) );
	CHECK( (v1[y] == 8.0f) );
	CHECK( (v1[z] == 9.0f) );
	CHECK( (v1[w] == 1.0f) );
	CHECK( (q1[x] == 7.0f) );
	CHECK( (q1[y] == 8.0f) );
	CHECK( (q1[z] == 9.0f) );
	CHECK( (q1[w] == 10.0f) );
}



TEST( Quat_Get_bracket1, QuatSetGetTests )
{
	Quat q1;
    float tmp_x, tmp_y, tmp_z, tmp_real;

	//  [] operator:
	q1.set(7.0f,8.0f,9.0f,10.0f);

	tmp_x = q1[x];
	tmp_y = q1[y];
	tmp_z = q1[z];
	tmp_real = q1[w];

	CHECK( (q1[x] == 7.0f) );
	CHECK( (q1[y] == 8.0f) );
	CHECK( (q1[z] == 9.0f) );
	CHECK( (q1[w] == 10.0f) );
	CHECK( (tmp_x == 7.0f) );
	CHECK( (tmp_y == 8.0f) );
	CHECK( (tmp_z == 9.0f) );
	CHECK( (tmp_real == 10.0f) );
}



TEST( Quat_Get_bracket2, QuatSetGetTests )
{
	Quat q1;
	float tmp_x, tmp_y, tmp_z, tmp_real;

	//  [] operator:
	q1.set(1.0f,2.0f,3.0f,4.0f);

	tmp_x = q1[X];
	tmp_y = q1[Y];
	tmp_z = q1[Z];
	tmp_real = q1[W];

	CHECK( (q1[x] == 1.0f) );
	CHECK( (q1[y] == 2.0f) );
	CHECK( (q1[z] == 3.0f) );
	CHECK( (q1[w] == 4.0f) );
	CHECK( (tmp_x == 1.0f) );
	CHECK( (tmp_y == 2.0f) );
	CHECK( (tmp_z == 3.0f) );
	CHECK( (tmp_real == 4.0f) );
}


TEST( Quat_Get_bracket3, QuatSetGetTests )
{
	Quat q1,qtmp;
	float tmp_x, tmp_y, tmp_z, tmp_real;

	//  [] operator:
	q1.set(7.0f,8.0f,9.0f,10.0f);

	tmp_x = q1[vect_x];
	tmp_y = q1[vect_y];
	tmp_z = q1[vect_z];
	tmp_real = q1[real];

	CHECK( (q1[x] == 7.0f) );
	CHECK( (q1[y] == 8.0f) );
	CHECK( (q1[z] == 9.0f) );
	CHECK( (q1[w] == 10.0f) );
	CHECK( (tmp_x == 7.0f) );
	CHECK( (tmp_y == 8.0f) );
	CHECK( (tmp_z == 9.0f) );
	CHECK( (tmp_real == 10.0f) );
}



TEST( Quat_Get_bracket4, QuatSetGetTests )
{
	Quat q1;
	float tmp_x, tmp_y, tmp_z, tmp_real;

	//  [] operator:
	q1.set(1.0f,2.0f,3.0f,4.0f);

	tmp_x = q1[VECT_X];
	tmp_y = q1[VECT_Y];
	tmp_z = q1[VECT_Z];
	tmp_real = q1[REAL];

	CHECK( (q1[x] == 1.0f) );
	CHECK( (q1[y] == 2.0f) );
	CHECK( (q1[z] == 3.0f) );
	CHECK( (q1[w] == 4.0f) );
	CHECK( (tmp_x == 1.0f) );
	CHECK( (tmp_y == 2.0f) );
	CHECK( (tmp_z == 3.0f) );
	CHECK( (tmp_real == 4.0f) );
}





/***** END of QuatSetGet.CPP *****************************************************************/