#include "AnimationJoint.h"

namespace lge
{
	// Default Ctor
	AnimationJoint::AnimationJoint() :
		Translation(),
		Rotation(),
		Scale()
	{
	}

	// Copy Ctor
	AnimationJoint::AnimationJoint(const AnimationJoint& other) :
		Translation(other.Translation),
		Rotation(other.Rotation),
		Scale(other.Scale)
	{
	}

	// Copy Assignment
	AnimationJoint& AnimationJoint::operator=(const AnimationJoint& other)
	{
		if (this == &other)
		{
			return *this;
		}

		this->Translation = other.Translation;
		this->Rotation = other.Rotation;
		this->Scale = other.Scale;

		return *this;
	}

	// Dtor
	AnimationJoint::~AnimationJoint()
	{
	}







}