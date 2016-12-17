#ifndef ENGINE_MATH_ENUM_H
#define ENGINE_MATH_ENUM_H

namespace lge
{
	// Get the X component of a Vect
	enum x_enum
	{
		x = 0,
		X = 0,
		vect_x = 0,
		VECT_X = 0
	};

	// Get the Y component of a Vect
	enum y_enum
	{
		y = 0,
		Y = 0,
		vect_y = 0,
		VECT_Y = 0
	};

	// Get the Z component of a Vect
	enum z_enum
	{
		z = 0,
		Z = 0,
		vect_z = 0,
		VECT_Z = 0
	};

	// Get the W component of a Vect
	enum w_enum
	{
		w = 0,
		W = 0,
		real = 0,
		REAL = 0

	};

	// Get index 0 of a Matrix
	enum m0_enum
	{
		m0
	};

	// Get index 1 of a Matrix
	enum m1_enum
	{
		m1
	};

	// Get index 2 of a Matrix
	enum m2_enum
	{
		m2
	};

	// Get index 3 of a Matrix
	enum m3_enum
	{
		m3
	};

	// Get index 4 of a Matrix
	enum m4_enum
	{
		m4
	};

	// Get index 5 of a Matrix
	enum m5_enum
	{
		m5
	};

	// Get index 6 of a Matrix
	enum m6_enum
	{
		m6
	};

	// Get index 7 of a Matrix
	enum m7_enum
	{
		m7
	};

	// Get index 8 of a Matrix
	enum m8_enum
	{
		m8
	};

	// Get index 9 of a Matrix
	enum m9_enum
	{
		m9
	};

	// Get index 10 of a Matrix
	enum m10_enum
	{
		m10
	};

	// Get index 11 of a Matrix
	enum m11_enum
	{
		m11
	};

	// Get index 12 of a Matrix
	enum m12_enum
	{
		m12
	};

	// Get index 13 of a Matrix
	enum m13_enum
	{
		m13
	};

	// Get index 14 of a Matrix
	enum m14_enum
	{
		m14
	};

	// Get index 15 of a Matrix
	enum m15_enum
	{
		m15
	};

	// Can either be Zero matrix or Identity matrix
	enum MatrixSpecialType
	{
		ZERO,
		IDENTITY
	};

	// Can be X rotation, Y rotation, or Z rotation
	enum RotType
	{
		ROT_X,
		ROT_Y,
		ROT_Z
	};

	// Needs all three X, Y, and Z rotations
	enum Rot3AxisType
	{
		ROT_XYZ
	};

	// Calls for a rotation of a certian angle along a certain axis
	enum RotAxisAngleType
	{
		ROT_AXIS_ANGLE
	};

	// Can be normal orientation or inverse orinetation
	enum RotOrientType
	{
		ROT_ORIENT,
		ROT_INVERSE_ORIENT
	};

	// Get the translation matrix
	enum MatrixTransType
	{
		TRANS
	};

	// Get the scale matrix
	enum MatrixScaleType
	{
		SCALE
	};

	// Get one of 4 rows from a Matrix
	enum MatrixRowType
	{
		ROW_0,
		ROW_1,
		ROW_2,
		ROW_3
	};
}

#endif