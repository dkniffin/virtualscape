//////////////////////////////////////////////////////////////////////////////////////////
//	Maths.h
//	Include maths headers
//	You may use this code however you wish, but if you do, please credit me and
//	provide a link to my website in a readme file or similar
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//	Modified:	17th December 2002	-	Removed QUATERNION
//////////////////////////////////////////////////////////////////////////////////////////	
#include <math.h>

//VC++ math.h (and others) do not define M_PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//An epsilon value for comparisons
#ifndef EPSILON
#define EPSILON 0.01f
#endif

#include "VECTOR2D.h"
#include "VECTOR3D.h"
#include "VECTOR4D.h"
#include "MATRIX4X4.h"
#include "PLANE.h"

#include "COLOR.h"