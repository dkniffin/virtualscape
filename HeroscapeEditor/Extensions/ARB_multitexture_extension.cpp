//////////////////////////////////////////////////////////////////////////////////////////
//	ARB_multitexture_extension.cpp
//	ARB_multitexture extension setup
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
#include "ARB_multitexture_extension.h"

bool ARB_multitexture_supported=false;

bool SetUpARB_multitexture()
{
	//Check for support
	ARB_multitexture_supported=glutExtensionSupported("GL_ARB_multitexture")!=0;
	
	if(!ARB_multitexture_supported)
	{
		printf("ARB_multitexture unsupported!\n");
		return false;
	}

	printf("ARB_multitexture supported!\n");

	//get function pointers
	glActiveTextureARB			=	(PFNGLACTIVETEXTUREARBPROC)
									wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB	=	(PFNGLCLIENTACTIVETEXTUREARBPROC)
									wglGetProcAddress("glClientActiveTextureARB");
	glMultiTexCoord1dARB		=	(PFNGLMULTITEXCOORD1DARBPROC)
									wglGetProcAddress("glMultiTexCoord1dARB");
	glMultiTexCoord1dvARB		=	(PFNGLMULTITEXCOORD1DVARBPROC)
									wglGetProcAddress("glMultiTexCoord1dvARB");
	glMultiTexCoord1fARB		=	(PFNGLMULTITEXCOORD1FARBPROC)
									wglGetProcAddress("glMultiTexCoord1fARB");
	glMultiTexCoord1fvARB		=	(PFNGLMULTITEXCOORD1FVARBPROC)
									wglGetProcAddress("glMultiTexCoord1fvARB");
	glMultiTexCoord1iARB		=	(PFNGLMULTITEXCOORD1IARBPROC)
									wglGetProcAddress("glMultiTexCoord1iARB");
	glMultiTexCoord1ivARB		=	(PFNGLMULTITEXCOORD1IVARBPROC)
									wglGetProcAddress("glMultiTexCoord1ivARB");
	glMultiTexCoord1sARB		=	(PFNGLMULTITEXCOORD1SARBPROC)
									wglGetProcAddress("glMultiTexCoord1sARB");
	glMultiTexCoord1svARB		=	(PFNGLMULTITEXCOORD1SVARBPROC)
									wglGetProcAddress("glMultiTexCoord1svARB");
	glMultiTexCoord2dARB		=	(PFNGLMULTITEXCOORD2DARBPROC)
									wglGetProcAddress("glMultiTexCoord2dARB");
	glMultiTexCoord2dvARB		=	(PFNGLMULTITEXCOORD2DVARBPROC)
									wglGetProcAddress("glMultiTexCoord2dvARB");
	glMultiTexCoord2fARB		=	(PFNGLMULTITEXCOORD2FARBPROC)
									wglGetProcAddress("glMultiTexCoord2fARB");
	glMultiTexCoord2fvARB		=	(PFNGLMULTITEXCOORD2FVARBPROC)
									wglGetProcAddress("glMultiTexCoord2fvARB");
	glMultiTexCoord2iARB		=	(PFNGLMULTITEXCOORD2IARBPROC)
									wglGetProcAddress("glMultiTexCoord2iARB");
	glMultiTexCoord2ivARB		=	(PFNGLMULTITEXCOORD2IVARBPROC)
									wglGetProcAddress("glMultiTexCoord2ivARB");
	glMultiTexCoord2sARB		=	(PFNGLMULTITEXCOORD2SARBPROC)
									wglGetProcAddress("glMultiTexCoord2sARB");
	glMultiTexCoord2svARB		=	(PFNGLMULTITEXCOORD2SVARBPROC)
									wglGetProcAddress("glMultiTexCoord2svARB");
	glMultiTexCoord3dARB		=	(PFNGLMULTITEXCOORD3DARBPROC)
									wglGetProcAddress("glMultiTexCoord3dARB");
	glMultiTexCoord3dvARB		=	(PFNGLMULTITEXCOORD3DVARBPROC)
									wglGetProcAddress("glMultiTexCoord3dvARB");
	glMultiTexCoord3fARB		=	(PFNGLMULTITEXCOORD3FARBPROC)
									wglGetProcAddress("glMultiTexCoord3fARB");
	glMultiTexCoord3fvARB		=	(PFNGLMULTITEXCOORD3FVARBPROC)
									wglGetProcAddress("glMultiTexCoord3fvARB");
	glMultiTexCoord3iARB		=	(PFNGLMULTITEXCOORD3IARBPROC)
									wglGetProcAddress("glMultiTexCoord3iARB");
	glMultiTexCoord3ivARB		=	(PFNGLMULTITEXCOORD3IVARBPROC)
									wglGetProcAddress("glMultiTexCoord3ivARB");
	glMultiTexCoord3sARB		=	(PFNGLMULTITEXCOORD3SARBPROC)
									wglGetProcAddress("glMultiTexCoord3sARB");
	glMultiTexCoord3svARB		=	(PFNGLMULTITEXCOORD3SVARBPROC)
									wglGetProcAddress("glMultiTexCoord3svARB");
	glMultiTexCoord4dARB		=	(PFNGLMULTITEXCOORD4DARBPROC)
									wglGetProcAddress("glMultiTexCoord4dARB");
	glMultiTexCoord4dvARB		=	(PFNGLMULTITEXCOORD4DVARBPROC)
									wglGetProcAddress("glMultiTexCoord4dvARB");
	glMultiTexCoord4fARB		=	(PFNGLMULTITEXCOORD4FARBPROC)
									wglGetProcAddress("glMultiTexCoord4fARB");
	glMultiTexCoord4fvARB		=	(PFNGLMULTITEXCOORD4FVARBPROC)
									wglGetProcAddress("glMultiTexCoord4fvARB");
	glMultiTexCoord4iARB		=	(PFNGLMULTITEXCOORD4IARBPROC)
									wglGetProcAddress("glMultiTexCoord4iARB");
	glMultiTexCoord4ivARB		=	(PFNGLMULTITEXCOORD4IVARBPROC)
									wglGetProcAddress("glMultiTexCoord4ivARB");
	glMultiTexCoord4sARB		=	(PFNGLMULTITEXCOORD4SARBPROC)
									wglGetProcAddress("glMultiTexCoord4sARB");
	glMultiTexCoord4svARB		=	(PFNGLMULTITEXCOORD4SVARBPROC)
									wglGetProcAddress("glMultiTexCoord4svARB");

	return true;
}

//function pointers

PFNGLACTIVETEXTUREARBPROC				glActiveTextureARB				=NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC			glClientActiveTextureARB		=NULL;
PFNGLMULTITEXCOORD1DARBPROC				glMultiTexCoord1dARB			=NULL;
PFNGLMULTITEXCOORD1DVARBPROC			glMultiTexCoord1dvARB			=NULL;
PFNGLMULTITEXCOORD1FARBPROC				glMultiTexCoord1fARB			=NULL;
PFNGLMULTITEXCOORD1FVARBPROC			glMultiTexCoord1fvARB			=NULL;
PFNGLMULTITEXCOORD1IARBPROC				glMultiTexCoord1iARB			=NULL;
PFNGLMULTITEXCOORD1IVARBPROC			glMultiTexCoord1ivARB			=NULL;
PFNGLMULTITEXCOORD1SARBPROC				glMultiTexCoord1sARB			=NULL;
PFNGLMULTITEXCOORD1SVARBPROC			glMultiTexCoord1svARB			=NULL;
PFNGLMULTITEXCOORD2DARBPROC				glMultiTexCoord2dARB			=NULL;
PFNGLMULTITEXCOORD2DVARBPROC			glMultiTexCoord2dvARB			=NULL;
PFNGLMULTITEXCOORD2FARBPROC				glMultiTexCoord2fARB			=NULL;
PFNGLMULTITEXCOORD2FVARBPROC			glMultiTexCoord2fvARB			=NULL;
PFNGLMULTITEXCOORD2IARBPROC				glMultiTexCoord2iARB			=NULL;
PFNGLMULTITEXCOORD2IVARBPROC			glMultiTexCoord2ivARB			=NULL;
PFNGLMULTITEXCOORD2SARBPROC				glMultiTexCoord2sARB			=NULL;
PFNGLMULTITEXCOORD2SVARBPROC			glMultiTexCoord2svARB			=NULL;
PFNGLMULTITEXCOORD3DARBPROC				glMultiTexCoord3dARB			=NULL;
PFNGLMULTITEXCOORD3DVARBPROC			glMultiTexCoord3dvARB			=NULL;
PFNGLMULTITEXCOORD3FARBPROC				glMultiTexCoord3fARB			=NULL;
PFNGLMULTITEXCOORD3FVARBPROC			glMultiTexCoord3fvARB			=NULL;
PFNGLMULTITEXCOORD3IARBPROC				glMultiTexCoord3iARB			=NULL;
PFNGLMULTITEXCOORD3IVARBPROC			glMultiTexCoord3ivARB			=NULL;
PFNGLMULTITEXCOORD3SARBPROC				glMultiTexCoord3sARB			=NULL;
PFNGLMULTITEXCOORD3SVARBPROC			glMultiTexCoord3svARB			=NULL;
PFNGLMULTITEXCOORD4DARBPROC				glMultiTexCoord4dARB			=NULL;
PFNGLMULTITEXCOORD4DVARBPROC			glMultiTexCoord4dvARB			=NULL;
PFNGLMULTITEXCOORD4FARBPROC				glMultiTexCoord4fARB			=NULL;
PFNGLMULTITEXCOORD4FVARBPROC			glMultiTexCoord4fvARB			=NULL;
PFNGLMULTITEXCOORD4IARBPROC				glMultiTexCoord4iARB			=NULL;
PFNGLMULTITEXCOORD4IVARBPROC			glMultiTexCoord4ivARB			=NULL;
PFNGLMULTITEXCOORD4SARBPROC				glMultiTexCoord4sARB			=NULL;
PFNGLMULTITEXCOORD4SVARBPROC			glMultiTexCoord4svARB			=NULL;

