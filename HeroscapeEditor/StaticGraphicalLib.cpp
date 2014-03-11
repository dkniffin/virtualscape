// StaticGraphicalLib.cpp: implementation of the CStaticGraphicalLib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

// Pour acces aux fichiers
#include <io.h>
// Pour les sorties ecran
#include <iostream>
// pour les calculs mathematiques bien sur
#include <Math.h>

#include "StaticGraphicalLib.h"

CStaticGraphicalLib::CStaticGraphicalLib()
{

}

CStaticGraphicalLib::~CStaticGraphicalLib()
{

}

// Supprime une texture
//
void CStaticGraphicalLib::DeleteTexture( GLint TextureId )
{
	if( TextureId==-1 )
		return;

	glDeleteTextures( 1, (const GLuint*) (&TextureId) );
}

// Charge une texture et retourne l'id ou -1 si pas trouve
// Si alpha > 0 et <= 255 On charge l'image avec un alpha egale au parametre/255
// Si alpha = 0 Il n'y a pas d'alpha dans la texture de l'image
// Si alpha = AlphaOnLoad voir l'enum
//
GLint CStaticGraphicalLib::LoadTexture( CString FileName, int Alpha )
{
	// Pour le chargement de textures
	AUX_RGBImageRec*	Texture;
	GLuint				TextureId;			

	USES_CONVERSION;

	char* cFileName = GetAsciiString( FileName );
	if( _access( cFileName, 0 )!=0 )
	{
		free( cFileName );
		//cerr << "Fichier " << FileName <<" non trouve" << endl;
		return -1;
	}
	else
	{
		free( cFileName );
		Texture=auxDIBImageLoad( FileName );
		if( Texture == NULL )
		{
			//TRACE(_T("Erreur chargement texture\n"));
			return -1;
		}
		else
		{
			glGenTextures( 1, &TextureId );
			glBindTexture( GL_TEXTURE_2D, TextureId );
			glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
			if( Alpha==ALPHA_MIDDLE )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=0;
					p[a*4+1]=0;
					p[a*4+2]=0;
					p[a*4+3]=(Texture->data[a*3]+Texture->data[a*3+1]+Texture->data[a*3+2])/3;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==ALPHA_LUMINOSITY )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=Texture->data[a*3];
					p[a*4+1]=Texture->data[a*3+1];
					p[a*4+2]=Texture->data[a*3+2];
					p[a*4+3]=(Texture->data[a*3]+Texture->data[a*3+1]+Texture->data[a*3+2])/3;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==BLACK_ALPHA_LUMINOSITY )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=0;
					p[a*4+1]=0;
					p[a*4+2]=0;
					p[a*4+3]=(Texture->data[a*3]+Texture->data[a*3+1]+Texture->data[a*3+2])/3;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==WHITE_ALPHA_LUMINOSITY )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=(char)255;
					p[a*4+1]=(char)255;
					p[a*4+2]=(char)255;
					p[a*4+3]=(Texture->data[a*3]+Texture->data[a*3+1]+Texture->data[a*3+2])/3;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==RED_ALPHA_LUMINOSITY )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=(char)255;
					p[a*4+1]=0;
					p[a*4+2]=0;
					p[a*4+3]=(Texture->data[a*3]+Texture->data[a*3+1]+Texture->data[a*3+2])/3;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==BLUE_ALPHA_LUMINOSITY )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=0;
					p[a*4+1]=0;
					p[a*4+2]=(char)255;
					p[a*4+3]=(Texture->data[a*3]+Texture->data[a*3+1]+Texture->data[a*3+2])/3;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==GREEN_ALPHA_LUMINOSITY )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=0;
					p[a*4+1]=(char)255;
					p[a*4+2]=0;
					p[a*4+3]=(Texture->data[a*3]+Texture->data[a*3+1]+Texture->data[a*3+2])/3;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==REDBLUE_ALPHA_LUMINOSITY )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=(char)255;
					p[a*4+1]=0;
					p[a*4+2]=(char)255;
					p[a*4+3]=(Texture->data[a*3]+Texture->data[a*3+1]+Texture->data[a*3+2])/3;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==ALPHA_ZERO_ON_BLACK )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=Texture->data[a*3];
					p[a*4+1]=Texture->data[a*3+1];
					p[a*4+2]=Texture->data[a*3+2];
					if( Texture->data[a*3]==0 && Texture->data[a*3+1]==0 && Texture->data[a*3+2]==0 )
						p[a*4+3]=0;
					else
						p[a*4+3]=(unsigned char) 255;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==ALPHA_ZERO_ON_MAGENTA )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=Texture->data[a*3];
					p[a*4+1]=Texture->data[a*3+1];
					p[a*4+2]=Texture->data[a*3+2];
					if( Texture->data[a*3]==255 && Texture->data[a*3+1]==211 && Texture->data[a*3+2]==255 )
						p[a*4+3]=0;
					else
						p[a*4+3]=(unsigned char) 255;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha==ALPHA_ZERO_ON_BLACK_HALF_ELSE )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=Texture->data[a*3];
					p[a*4+1]=Texture->data[a*3+1];
					p[a*4+2]=Texture->data[a*3+2];
					if( Texture->data[a*3]==0 && Texture->data[a*3+1]==0 && Texture->data[a*3+2]==0 )
						p[a*4+3]=0;
					else
						p[a*4+3]=(unsigned char) 128;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else if( Alpha>=0 )
			{
				// Convertit l'image car il la charge mal
				char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*4);
				for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
				{
					p[a*4]=Texture->data[a*3];
					p[a*4+1]=Texture->data[a*3+1];
					p[a*4+2]=Texture->data[a*3+2];
					p[a*4+3]=Alpha;
				}
				glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->sizeX, Texture->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, p );
				free(p);
			}
			else
				glTexImage2D( GL_TEXTURE_2D, 0, 3, Texture->sizeX, Texture->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Texture->data );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR  );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
			glMatrixMode(GL_TEXTURE); 
			glLoadIdentity(); 
			free(Texture->data);
			free(Texture);

			//CString StrLoadTexture;
			//TRACE(_T("  -> Load Texture : %s\n"), FileName );
			return TextureId;
		}
	}
}

// Load a Bitmap and return a pointer about data
//
void* CStaticGraphicalLib::LoadBitmap( CString FileName )
{
	// Pour le chargement de textures
	AUX_RGBImageRec*	Texture;

	char* pStr = GetAsciiString( FileName );
	if( _access( pStr, 0 )!=0 )
	{
		free( pStr );
		TRACE(_T("Fichier %s non trouve\n"), FileName );
		return NULL;
	}
	else
	{
		free( pStr );
		Texture=auxDIBImageLoad( FileName );
		if( Texture == NULL )
		{
			TRACE(_T("Erreur chargement bitmap\n"));
			return NULL;
		}
		else
		{
			char* p = (char*) malloc(Texture->sizeX*Texture->sizeY*3);
			for( int a=0; a<Texture->sizeX*Texture->sizeY; a++ )
			{
				p[a*3]=Texture->data[a*3+2];
				p[a*3+1]=Texture->data[a*3+1];
				p[a*3+2]=Texture->data[a*3];
			}

			free(Texture->data);
			free(Texture);

			return p;
		}
	}
}

// Construct matrix for bilboarding
//
void CStaticGraphicalLib::BilboardMatrix( float vx, float vy )
{
    float mat[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    buildRot((float) (-180*atan2f( vx, vy)/3.14159265358979323846), 0, 0, 1, mat);
    glMultMatrixf(mat);
}

// Construct matrix for bilboarding
//
void CStaticGraphicalLib::buildRot(float theta, float x, float y, float z, float m[16])
{
    float d = x*x + y*y + z*z;
    float ct = cosf((float) (theta/180*3.14159265358979323846));
	float st = sinf((float) (theta/180*3.14159265358979323846));

    /* normalize */
    if (d > 0) {
	d = 1/d;
	x *= d;
	y *= d;
	z *= d;
    }

    m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
    m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = 0;
    m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;

    /* R = uu' + cos(theta)*(I-uu') + sin(theta)*S
     *
     * S =  0  -z   y    u' = (x, y, z)
     *	    z   0  -x
     *	   -y   x   0
     */

     m[0] = x*x + ct*(1-x*x) + st*0;
     m[4] = x*y + ct*(0-x*y) + st*-z;
     m[8] = x*z + ct*(0-x*z) + st*y;

     m[1] = y*x + ct*(0-y*x) + st*z;
     m[5] = y*y + ct*(1-y*y) + st*0;
     m[9] = y*z + ct*(0-y*z) + st*-x;

     m[2] = z*x + ct*(0-z*x) + st*-y;
     m[6] = z*y + ct*(0-z*y) + st*x;
     m[10]= z*z + ct*(1-z*z) + st*0;
}

// Create a char* from a unicode CString
//
char* CStaticGraphicalLib::GetAsciiString( CString Str )
{
	
	char* NewStr = (char*) malloc(Str.GetLength()+1);

	CT2CA CharStr(Str);
	memcpy( NewStr, CharStr, Str.GetLength() );

/*	for( int i=0; i<Str.GetLength(); i++ )
	{
		unsigned short us = _mbbtombc( Str.GetAt(i) );
		if( us<256 )
			NewStr[i] = (char) us;
		else
			NewStr[i] = ' ';
	} */
	NewStr[Str.GetLength()] = 0;

	return NewStr;
}

// Draw a cube
//
void CStaticGraphicalLib::DrawCube()
{
	glBegin( GL_QUADS );
	glNormal3d( 0, -1, 0 );
	glTexCoord2d( 0, 0 );
	glVertex3d( -0.5, -0.5, -0.5 );
	glTexCoord2d( 1, 0 );
	glVertex3d( 0.5, -0.5, -0.5 );
	glTexCoord2d( 1, 1 );
	glVertex3d( 0.5, -0.5, 0.5 );
	glTexCoord2d( 0, 1 );
	glVertex3d( -0.5, -0.5, 0.5 );

	glNormal3d( 0, 1, 0 );
	glTexCoord2d( 0, 0 );
	glVertex3d( 0.5, 0.5, -0.5 );
	glTexCoord2d( 1, 0 );
	glVertex3d( -0.5, 0.5, -0.5 );
	glTexCoord2d( 1, 1 );
	glVertex3d( -0.5, 0.5, 0.5 );
	glTexCoord2d( 0, 1 );
	glVertex3d( 0.5, 0.5, 0.5 );

	glNormal3d( 1, 0, 0 );
	glTexCoord2d( 0, 0 );
	glVertex3d( 0.5, -0.5, -0.5 );
	glTexCoord2d( 1, 0 );
	glVertex3d( 0.5, 0.5, -0.5 );
	glTexCoord2d( 1, 1 );
	glVertex3d( 0.5, 0.5, 0.5 );
	glTexCoord2d( 0, 1 );
	glVertex3d( 0.5, -0.5, 0.5 );

	glNormal3d( -1, 0, 0 );
	glTexCoord2d( 0, 0 );
	glVertex3d( -0.5, 0.5, -0.5 );
	glTexCoord2d( 1, 0 );
	glVertex3d( -0.5, -0.5, -0.5 );
	glTexCoord2d( 1, 1 );
	glVertex3d( -0.5, -0.5, 0.5 );
	glTexCoord2d( 0, 1 );
	glVertex3d( -0.5, 0.5, 0.5 );

	glNormal3d( 0, 0, 1 );
	glTexCoord2d( 0, 0 );
	glVertex3d( 0.5, -0.5, 0.5 );
	glTexCoord2d( 1, 0 );
	glVertex3d( 0.5, 0.5, 0.5 );
	glTexCoord2d( 1, 1 );
	glVertex3d( -0.5, 0.5, 0.5 );
	glTexCoord2d( 0, 1 );
	glVertex3d( -0.5, -0.5, 0.5 );

	glNormal3d( 0, 0, -1 );
	glTexCoord2d( 0, 0 );
	glVertex3d( -0.5, -0.5, -0.5 );
	glTexCoord2d( 1, 0 );
	glVertex3d( -0.5, 0.5, -0.5 );
	glTexCoord2d( 1, 1 );
	glVertex3d( 0.5, 0.5, -0.5 );
	glTexCoord2d( 0, 1 );
	glVertex3d( 0.5, -0.5, -0.5 );

	glEnd();
}