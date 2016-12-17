/*****************************************************************************/
/*                                                                           */
/* File: QuatConstructor.cpp                                                 */
/*                                                                           */
/* Primative Quat Constructor Class testbed                                  */
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
/* Quat Constructor:                                                       */
/*****************************************************************************/

TEST( QuatConstructor, QuatConstructorTests )
{
	
	CHECK( 1 );
}

  
TEST( Quat_Default_Constructor, QuatConstructorTests )
{
	// Default Constructor:
	
	Quat q1;


	CHECK( ( 0.0f == q1[x] ) );
	CHECK( ( 0.0f == q1[y] ) );
	CHECK( ( 0.0f == q1[z] ) );
	CHECK( ( 1.0f == q1[w] ) );
	CHECK( sizeof(q1) == sizeof(Quat) );
}


TEST( Quat_Constructor_Set_Every_Component, QuatConstructorTests )
{
	// Set every element constructor

	Quat q10(2.0f,3.0f,4.0f,5.0f);

	CHECK( ( 2.0f == q10[x] ) );
	CHECK( ( 3.0f == q10[y] ) );
	CHECK( ( 4.0f == q10[z] ) );
	CHECK( ( 5.0f == q10[w] ) );
}


TEST( Quat_Copy_Constructor, QuatConstructorTests )
{
	// Copy Constructor

	Quat q11(2.0f,3.0f,4.0f,5.0f);
	Quat q12(q11);

	CHECK( ( 2.0f == q11[x] ) );
	CHECK( ( 3.0f == q11[y] ) );
	CHECK( ( 4.0f == q11[z] ) );
	CHECK( ( 5.0f == q11[w] ) );
	CHECK( ( q12[x] == q11[x] ) );
	CHECK( ( q12[y] == q11[y] ) );
	CHECK( ( q12[z] == q11[z] ) );
	CHECK( ( q12[w] == q11[w] ) );
}


TEST( Quat_Vect_Component_Real_Component_Constructor, QuatConstructorTests )
{
	// Vector component, Real component Constructor

	Vect v10(12.0f,13.0f,14.0f,15.0f);
	Quat q13(v10,20.0f);

	CHECK( ( 12.0f == q13[x] ) );
	CHECK( ( 13.0f == q13[y] ) );
	CHECK( ( 14.0f == q13[z] ) );
	CHECK( ( 20.0f == q13[w] ) );
}


TEST( Quat_From_Matrix_Constructor, QuatConstructorTests )
{
	// Quaternion from a Matrix Constructor

	Matrix m40;
	Matrix Rx(ROT_X,MATH_PI2);
	Matrix Ry(ROT_Y,-MATH_PI3);
	Matrix Rz(ROT_Z,-MATH_7PI8);

	m40 = Rx*Ry*Rz;

	Quat q14(m40);
	
	CHECK( eq(0.2274f,q14[x],MATH_TOLERANCE) );
	CHECK( eq(0.6693f,q14[y],MATH_TOLERANCE) );
	CHECK( eq(0.5318f,q14[z],MATH_TOLERANCE) );
	CHECK( eq(-0.4661f,q14[w],MATH_TOLERANCE) );

	Matrix M3;
	M3.set(q14);

	CHECK( eq(m40[m0],M3[m0],MATH_TOLERANCE) );
	CHECK( eq(m40[m1],M3[m1],MATH_TOLERANCE) );
	CHECK( eq(m40[m2],M3[m2],MATH_TOLERANCE) );
	CHECK( eq(m40[m3],M3[m3],MATH_TOLERANCE) );
	CHECK( eq(m40[m4],M3[m4],MATH_TOLERANCE) );
	CHECK( eq(m40[m5],M3[m5],MATH_TOLERANCE) );
	CHECK( eq(m40[m6],M3[m6],MATH_TOLERANCE) );
	CHECK( eq(m40[m7],M3[m7],MATH_TOLERANCE) );
	CHECK( eq(m40[m8],M3[m8],MATH_TOLERANCE) );
	CHECK( eq(m40[m9],M3[m9],MATH_TOLERANCE) );
	CHECK( eq(m40[m10],M3[m10],MATH_TOLERANCE) );
	CHECK( eq(m40[m11],M3[m11],MATH_TOLERANCE) );
	CHECK( eq(m40[m12],M3[m12],MATH_TOLERANCE) );
	CHECK( eq(m40[m13],M3[m13],MATH_TOLERANCE) );
	CHECK( eq(m40[m14],M3[m14],MATH_TOLERANCE) );
	CHECK( eq(m40[m15],M3[m15],MATH_TOLERANCE) );
}



TEST( Quat_IDENTITY_Constructor, QuatConstructorTests )
{
	// Special Type Constructor:
	
	Quat q2(IDENTITY);

	CHECK( (q2[x] == 0.0f) );
	CHECK( (q2[y] == 0.0f) );
	CHECK( (q2[z] == 0.0f) );
	CHECK( (q2[w] == 1.0f) );


	Matrix 	M2;
	M2.set(IDENTITY);
	Quat qtmp;
	qtmp.set( M2 );
	CHECK( eq(q2[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q2[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q2[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q2[w],qtmp[w],MATH_TOLERANCE) );
	
	Matrix M3;
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




TEST( Quat_ROTXYZ_Constructor, QuatConstructorTests )
{
	// Special Type Constructor:
	Quat qxyz(ROT_XYZ, 0.345f, -1.234f, 0.832f);

   Quat qx( ROT_X, 0.345f);
   Quat qy( ROT_Y, -1.234f);
   Quat qz( ROT_Z,  0.832f);


   Quat qtmp;

   qtmp = qx * qy * qz;

	CHECK( eq(qxyz[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(qxyz[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(qxyz[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(qxyz[w],qtmp[w],MATH_TOLERANCE) );

}


TEST( Quat_SET_ROTXYZ_Constructor, QuatConstructorTests )
{
	// Special Type Constructor:
	Quat qxyz;
   
   qxyz.set(ROT_XYZ, 0.345f, -1.234f, 0.832f);

   Quat qx( ROT_X, 0.345f);
   Quat qy( ROT_Y, -1.234f);
   Quat qz( ROT_Z,  0.832f);


   Quat qtmp;

   qtmp = qx * qy * qz;

	CHECK( eq(qxyz[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(qxyz[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(qxyz[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(qxyz[w],qtmp[w],MATH_TOLERANCE) );

}

TEST( Quat_X_PI2_Constructor, QuatConstructorTests )
{
	// Special Type Constructor:
	Quat q4(ROT_X, MATH_PI2);

	// Matrix to Quaternion
	Matrix M2;
	M2.set(ROT_X, MATH_PI2);

	Quat qtmp;
	qtmp.set( M2);
	CHECK( eq(q4[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q4[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q4[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q4[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	Matrix M3;
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



TEST( Quat_X_PI_Constructor, QuatConstructorTests )
{
	// Special Type Constructor:

	Quat q5(ROT_X, MATH_PI);


	// Matrix to Quaternion
	Matrix M2, M3;
	Quat qtmp;
	M2.set(ROT_X, MATH_PI);
	qtmp.set( M2 );

	CHECK( eq(q5[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q5[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q5[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q5[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q5);

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


TEST( Quat_Y_PI2_Constructor, QuatConstructorTests )
{
	// Special Type Constructor:

	Quat q6(ROT_Y, MATH_PI2);


	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;
	M2.set(ROT_Y, MATH_PI2);
	qtmp.set( M2 );
	CHECK( eq(q6[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q6[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q6[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q6[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q6);

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

TEST( Quat_Y_PI_Constructor, QuatConstructorTests )
{

	// Special Type Constructor:
	Quat q7(ROT_Y, MATH_PI);

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;
	M2.set(ROT_Y, MATH_PI);
	qtmp.set( M2 );
	CHECK( eq(q7[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q7[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q7[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q7[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q7);

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

TEST( Quat_Z_PI2_Constructor, QuatConstructorTests )
{
	// Special Type Constructor:
	Quat q8(ROT_Z, MATH_PI2);

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;
	M2.set(ROT_Z, MATH_PI2);
	qtmp.set( M2 );
	CHECK( eq(q8[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q8[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q8[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q8[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q8);

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

TEST( Quat_Z_PI_Constructor, QuatConstructorTests )
{
	// Special Type Constructor:

	Quat q9(ROT_Z,MATH_PI);


	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;
	M2.set(ROT_Z,MATH_PI);
	qtmp.set( M2 );
	CHECK( eq(q9[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(q9[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(q9[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(q9[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(q9);

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


TEST( Quat_X_Constructor, QuatConstructorTests )
{
	// Rot_X Type Constructor:
	Quat Qx(ROT_X, MATH_PI3);	

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;
	M2.set(ROT_X, MATH_PI3);	
	qtmp.set( M2 );
	CHECK( eq(Qx[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qx[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qx[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qx[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qx);

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


TEST( Quat_Y_Constructor, QuatConstructorTests )
{
	// Rot_Y Type Constructor:
	Quat Qy(ROT_Y, MATH_PI3);	


	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;
	M2.set(ROT_Y, MATH_PI3);	
	qtmp.set( M2 );
	CHECK( eq(Qy[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qy[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qy[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qy[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qy);

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


TEST( Quat_Z_Constructor, QuatConstructorTests )
{
	// Rot_Z Type Constructor:
	Quat Qz(ROT_Z, MATH_PI3);	

	// Matrix to Quaternion
	Matrix M2,M3;
	Quat qtmp;
	M2.set(ROT_Z, MATH_PI3);	
	qtmp.set( M2 );
	CHECK( eq(Qz[x],qtmp[x],MATH_TOLERANCE) );
	CHECK( eq(Qz[y],qtmp[y],MATH_TOLERANCE) );
	CHECK( eq(Qz[z],qtmp[z],MATH_TOLERANCE) );
	CHECK( eq(Qz[w],qtmp[w],MATH_TOLERANCE) );

	// Quaternion to Matrix
	M3.set(Qz);

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


TEST( Quat_XY_Constructor, QuatConstructorTests )
{
	// Rot_XY Type Constructor:
	Quat Qx(ROT_X, MATH_PI3);
	Quat Qy(ROT_Y, MATH_PI4);

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




TEST( Quat_XZ_Constructor, QuatConstructorTests )
{
	// Rot_XZ Type Constructor:
	Quat Qx(ROT_X, MATH_PI3);
	Quat Qz(ROT_Z, MATH_PI4);
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


TEST( Quat_YX_Constructor, QuatConstructorTests )
{
	// Rot_YX Type Constructor:
	Quat Qy(ROT_Y, MATH_PI3);
	Quat Qx(ROT_X, MATH_PI4);
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


TEST( Quat_YZ_Constructor, QuatConstructorTests )
{
	// Rot_YZ Type Constructor:
	Quat Qy(ROT_Y, MATH_PI3);
	Quat Qz(ROT_Z, MATH_PI4);
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



TEST( Quat_ZX_Constructor, QuatConstructorTests )
{
	// Rot_ZX Type Constructor:
	Quat Qz(ROT_Z, MATH_PI3);
	Quat Qx(ROT_X, MATH_PI4);
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


TEST( Quat_ZY_Constructor, QuatConstructorTests )
{
	// Rot_ZY Type Constructor:

	Quat Qz(ROT_Z, MATH_PI3);
	Quat Qy(ROT_Y, MATH_PI4);
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



TEST( Quat_XYZ_Constructor, QuatConstructorTests )
{
	// Rot_XYZ Type Constructor:
	Quat Qx(ROT_X, MATH_PI3 );
	Quat Qy(ROT_Y, MATH_5PI8);
	Quat Qz(ROT_Z, MATH_PI4 );
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


TEST( Quat_XZY_Constructor, QuatConstructorTests )
{
	// Rot_XZY Type Constructor:
	Quat Qx(ROT_X, MATH_PI3 );
	Quat Qz(ROT_Z, MATH_5PI8);
	Quat Qy(ROT_Y, MATH_PI4 );
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



TEST( Quat_YXZ_Constructor, QuatConstructorTests )
{
	// Rot_YXZ Type Constructor:


	Quat Qy(ROT_Y, MATH_PI3 );
	Quat Qx(ROT_X, MATH_5PI8);
	Quat Qz(ROT_Z, MATH_PI4 );
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


TEST( Quat_YZX_Constructor, QuatConstructorTests )
{
	// Rot_YZX Type Constructor:

	Quat Qy(ROT_Y, MATH_PI3 );
	Quat Qz(ROT_Z, MATH_5PI8);
	Quat Qx(ROT_X, MATH_PI4 );
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


TEST( Quat_ZXY_Constructor, QuatConstructorTests )
{
	// Rot_ZXY Type Constructor:
	Quat Qz(ROT_Z, MATH_PI3 );
	Quat Qx(ROT_X, MATH_5PI8);
	Quat Qy(ROT_Y, MATH_PI4 );
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


TEST( Quat_ZYX_Constructor, QuatConstructorTests )
{
	// Rot_ZYX Type Constructor:
	Quat Qz(ROT_Z, MATH_PI3 );
	Quat Qy(ROT_Y, MATH_5PI8);
	Quat Qx(ROT_X, MATH_PI4 );
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





TEST( Quat_AXIS_ANGLE_Constructor, QuatConstructorTests )
{
	// Axis and Angle Type Constructor:
	Vect  v11( 2.0f, 53.0f, 24.0f);
	Quat Qa1(ROT_AXIS_ANGLE, v11, MATH_PI3 );

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



TEST( Quat_ROT_ORIENT_Constructor, QuatConstructorTests )
{
	// Orientation Type Constructor:

	Vect  v15( 2.0f, 53.0f, 24.0f);
	Vect  v16( 0.0f, -24.0f, 53.0f);
	Quat q56(ROT_ORIENT, v15, v16 );

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


TEST( Quat_ROT_INVERSE_ORIENT_Constructor, QuatConstructorTests )
{
	// Orientation Type Constructor:
	Vect  v17( 2.0f, 53.0f, 24.0f);
	Vect  v18( 0.0f, -24.0f, 53.0f);
	Quat q57(ROT_INVERSE_ORIENT, v17, v18 );

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



TEST( Quat_Destructor, QuatConstructorTests )
{
	// Destructor

	Quat qDstr( IDENTITY );

	Quat *pMdstr = &qDstr;

	pMdstr->~Quat();

	CHECK(1);
} 





/***** END of File QuatConstructor.cpp **************************************/
