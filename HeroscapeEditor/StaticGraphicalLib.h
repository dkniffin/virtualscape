// StaticGraphicalLib.h: interface for the CStaticGraphicalLib class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _STATICGRAPHICALLIB_H_
#define _STATICGRAPHICALLIB_H_

// Open GL
#include <GL/gl.h> 
#include <GL/glaux.h> 

#define GL_TEXTURE_2D_BINDING 0x8069

class CStaticGraphicalLib  
{
//************
// The defines
//************
public:

//**********
// The enums
//**********
public:

// The alpha for loading texture
enum AlphaOnLoad
{
	ALPHA_MIDDLE=256,				// On charge l'image avec un alpha egale a la moyenne des trois couleurs et la couleur est forcé a noire
	ALPHA_ZERO_ON_BLACK,			// On charge l'image avec un alpha egale a 0 quand c'est noir
	ALPHA_ZERO_ON_BLACK_HALF_ELSE,	// On charge l'image avec un alpha egale a 0 quand c'est noir et 0.5 sinon
	ALPHA_ZERO_ON_MAGENTA,			// On charge l'image avec un alpha egale a 0 quand c'est 255 211 255 et 1 sinon
	ALPHA_LUMINOSITY,				// On charge l'image avec un alpha egale a la moyenne des trois couleurs
	BLACK_ALPHA_LUMINOSITY,
	WHITE_ALPHA_LUMINOSITY,
	RED_ALPHA_LUMINOSITY,
	BLUE_ALPHA_LUMINOSITY,
	GREEN_ALPHA_LUMINOSITY,
	REDBLUE_ALPHA_LUMINOSITY,
	ALPHA_FROM_IMAGE=-1				// On charge l'image avec l'alpha dans l'image (fichiers tif, png)
};

// Les differents types d'alignement
#define	AL_GAUCHE					0
#define	AL_DROITE					1
#define	AL_CENTRE					2

//************
// The methods
//************
public:
	// The constructor
	CStaticGraphicalLib();
	// The destructor
	virtual			~CStaticGraphicalLib();
	// Supprime une texture
	static void		DeleteTexture( GLint TextureId );
	// Charge une texture et retourne l'id ou -1 si pas trouve
	static GLint	LoadTexture( CString FileName, int Alpha=0 );
	// Construct matrix for bilboarding
	static void		BilboardMatrix( float vx, float vy );
	// Construct matrix for bilboarding
	static void		buildRot(float theta, float x, float y, float z, float m[16]);
	// Create a char* from a unicode CString
	static char*	GetAsciiString( CString Str );
	// Load a Bitmap and return a pointer about data
	static void*	LoadBitmap( CString FileName );
	// Draw a cube
	static void		DrawCube();
};


#endif // #ifndef _STATICGRAPHICALLIB_H_
