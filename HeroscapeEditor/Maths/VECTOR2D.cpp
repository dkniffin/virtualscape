//////////////////////////////////////////////////////////////////////////////////////////
//	VECTOR2D.cpp
//	Function definitions for 2d vector class
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	8th November 2002
//////////////////////////////////////////////////////////////////////////////////////////	

#include "StdAfx.h"

#include "Maths.h"

void VECTOR2D::Normalize()
{
	float length;
	float scalefactor;
	length=GetLength();

	if(length==1 || length==0)			//return if length is 1 or 0
		return;

	scalefactor = 1.0f/length;
	x *= scalefactor;
	y *= scalefactor;
}

VECTOR2D VECTOR2D::GetNormalized() const
{
	VECTOR2D result(*this);

	result.Normalize();

	return result;
}

VECTOR2D operator*(float scaleFactor, const VECTOR2D & rhs)
{
	return rhs*scaleFactor;
}

bool VECTOR2D::operator==(const VECTOR2D & rhs) const
{
	if(x==rhs.x && y==rhs.y)
		return true;

	return false;
}



