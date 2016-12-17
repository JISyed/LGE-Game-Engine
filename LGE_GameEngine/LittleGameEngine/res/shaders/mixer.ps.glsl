#version 400 core

uniform float t;

layout (location = 0) in vec4 translationA;
layout (location = 1) in vec4 rotationA;
layout (location = 2) in vec4 scaleA;
layout (location = 3) in vec4 translationB;
layout (location = 4) in vec4 rotationB;
layout (location = 5) in vec4 scaleB;

out vec4 mixedTranslation;
out vec4 mixedRotation;
out vec4 mixedScale;

// Keenan's Slerp
/** 
 * Mutates result to be a slerp between the source and target by the
 * specified factor.
 * For a factor of 0.0, result == source.
 * For a factor of 1.0, result == target.
 */
vec4 Slerp( vec4 A, vec4 B, float t )
{
	vec4 target = B;

	// Constants.
	const float QUAT_EPSILON = 0.001f;

	float cosom = dot(A, B);
	if( cosom >= 1.0f)
	{
		// do nothing
		return A;
	}
	else
	{
	// adjust signs if necessary
	if ( cosom < 0.0f )
	{
		cosom = -cosom;
		target = -B;
    }

	// If the the source and target are close, we can do a lerp.
	float tarFactor = t;
	float srcFactor = 1.0f - t;

	// calculate coefficients
	if ( cosom < (1.0f - QUAT_EPSILON) )
	{
		// Quats are not close enough for a lerp.
		// Calculating coefficients for a slerp.
		float omega = acos( cosom );
		float sinom = 1.0f / sin( omega );

		srcFactor = sin( srcFactor * omega ) * sinom;
		tarFactor = sin( tarFactor * omega ) * sinom;
	}

	return vec4(A.x * srcFactor + target.x * tarFactor,
				A.y * srcFactor + target.y * tarFactor,
				A.z * srcFactor + target.z * tarFactor,
				A.w * srcFactor + target.w * tarFactor);
	}

};

void main(void)
{
	mixedTranslation = mix(translationA, translationB, t);
	mixedRotation = Slerp(rotationA, rotationB, t);
	mixedScale = mix(scaleA, scaleB, t);
}
