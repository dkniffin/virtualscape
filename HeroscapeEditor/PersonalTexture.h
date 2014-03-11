#pragma once

#include "GL/gl.h" 

class CPersonalTexture
{
//************
// The members
//************
public:
	CString FileName;
	GLuint	Id;

//************
// The methods
//************
public:
	// The constructor
	CPersonalTexture(void);
	// The destructor
	~CPersonalTexture(void);
};
