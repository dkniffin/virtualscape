//////////////////////////////////////////////////////////////////////////////////////////
//	EXT_texture_env_combine_extension.cpp
//	EXT_texture_env_combine extension setup
//	You may use this code as you see fit, provided this header is kept intact.
//	Downloaded from: users.ox.ac.uk/~univ1234
//	Created:	20th July 2002
//////////////////////////////////////////////////////////////////////////////////////////	
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL\glext.h>
#include <GL\wglext.h>
#include "EXT_texture_env_combine_extension.h"

bool EXT_texture_env_combine_supported=false;

bool SetUpEXT_texture_env_combine()
{
	//Check for support
	EXT_texture_env_combine_supported=glutExtensionSupported("GL_EXT_texture_env_combine")!=0;
	
	if(!EXT_texture_env_combine_supported)
	{
		printf("EXT_texture_env_combine unsupported!\n");
		return false;
	}

	printf("EXT_texture_env_combine supported!\n");

	//get function pointers
	//none specified

	return true;
}
