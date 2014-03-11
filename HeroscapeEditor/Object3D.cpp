// Object3D.cpp: implementation of the CObject3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
// Pour les sorties ecran
#include <io.h>
#include <iostream>

#include "Object3D.h"
#include "StaticGraphicalLib.h"

// Le constructeur
//
CObject3D::CObject3D()
{
	// The object is at the placement 0,0,0
	m_Translation.Reset();
	// No subObject now
	m_i_NbrObject=0;
	// No scale
	m_ScaleHeight = 1;
	// No rotation
	m_Rotate = 0;
	// No scale
	m_Scale = 1;
	// The bounding Box
	m_XMin = m_YMin = m_ZMin = 1e100;
	m_XMax = m_YMax = m_ZMax = -1e100;
	// The size
	m_Width = m_Height = m_Depth = 0;
}

// Le destructeur
//
CObject3D::~CObject3D()
{
	int i;

	// Liberate the object
	for( i=0; i<m_i_NbrObject; i++ )
	{
		if( m_GlVtx[i] )
			delete []m_GlVtx[i];
		if( m_GlNormal[i] )
			delete []m_GlNormal[i];
		if( m_GlTexture[i] )
			delete []m_GlTexture[i];
	}
}

// charge un fichier sgl
//
void CObject3D::LoadSgl( CString FileName )
{
	int			i,j;
	BOOL		ObjectAlpha[MAX_SUBOBJECT];
	CString		FilePath;

	// Extract the name
	m_Name = FileName.Right( FileName.GetLength()-FileName.ReverseFind('\\')-1 );
	m_Name = m_Name.Left( m_Name.GetLength()-4 );

	FilePath = FileName.Left( FileName.ReverseFind('\\') );
	//FilePath = FilePath.Left( FilePath.ReverseFind('\\') );

	// Read the landscape from the file
	CStdioFile f( FileName, CFile::modeRead | CFile::shareDenyNone | CFile::typeBinary );
	CArchive ar( &f, CArchive::load );

	// On lit le nombre d'objet
	ar >> m_i_NbrObject;
	// puis on lit tous les objects 1 a 1
	for( i=0; i<m_i_NbrObject; i++ )
	{
		char s[255];
		// Le nom de l'objet
		memset( s, 0, 255 );
		ar.Read( s, 255 );
		m_ObjectName[i]=s;
		m_ObjectRealName[i]=m_ObjectName[i];
		// Le nombre de facette de l'objet
		ar >> m_i_NbrVtx[i];
		// Les donnees sur les vertex
		m_GlVtx[i] = new GLfloat[m_i_NbrVtx[i]*3];
		ar.Read( m_GlVtx[i], sizeof(GLfloat)*3*m_i_NbrVtx[i] );
		// Les donnees sur les normals
		m_GlNormal[i] = new GLfloat[m_i_NbrVtx[i]*3];
		ar.Read( m_GlNormal[i], sizeof(GLfloat)*3*m_i_NbrVtx[i] );
		// Les donnees sur les textures
		m_GlTexture[i] = new GLfloat[m_i_NbrVtx[i]*2];
		ar.Read( m_GlTexture[i], sizeof(GLfloat)*2*m_i_NbrVtx[i] );
		// Reverse z and y
		for( j=0; j<m_i_NbrVtx[i]; j++ )
		{
			GLfloat Tampon;
			Tampon = m_GlVtx[i][j*3+1];
			m_GlVtx[i][j*3+1] = m_GlVtx[i][j*3+2];
			m_GlVtx[i][j*3+2] = Tampon;

			Tampon = m_GlNormal[i][j*3+1];
			m_GlNormal[i][j*3+1] = m_GlNormal[i][j*3+2];
			m_GlNormal[i][j*3+2] = Tampon;
			//m_GlNormal[i][j*3] *= -1;
			//m_GlNormal[i][j*3+1] *= -1;
			//m_GlNormal[i][j*3+2] *= -1;
			if( m_GlVtx[i][j*3]>m_XMax )
				m_XMax = m_GlVtx[i][j*3];
			if( m_GlVtx[i][j*3]<m_XMin )
				m_XMin = m_GlVtx[i][j*3];
			if( m_GlVtx[i][j*3+1]>m_YMax )
				m_YMax = m_GlVtx[i][j*3+1];
			if( m_GlVtx[i][j*3+1]<m_YMin )
				m_YMin = m_GlVtx[i][j*3+1];
			if( m_GlVtx[i][j*3+2]>m_ZMax )
				m_ZMax = m_GlVtx[i][j*3+2];
			if( m_GlVtx[i][j*3+2]<m_ZMin )
				m_ZMin = m_GlVtx[i][j*3+2];
		}
	}

	// Compute size
	m_Width = m_XMax-m_XMin;
	m_Depth = m_YMax-m_YMin;
	m_Height = m_ZMax-m_ZMin;

	ar.Close();
	f.Close();
	// Fin de chargement du fichier

	// positionne les elements
	for( i=0; i<m_i_NbrObject; i++ )
	{
		// Selon le nom on positionne le chrome
		if( m_ObjectName[i].Find(_T(" (C"))!=-1 )
			m_f_ObjectChrome[i]=1.0f;
		else
			m_f_ObjectChrome[i]=0;

		// Selon le nom on positionne le reflet
		if( m_ObjectName[i].Find(_T(" (R"))!=-1 )
			m_f_ObjectReflect[i]=1.0f;
		else
			m_f_ObjectReflect[i]=0;

		// Selon le nom on positionne la transparence
		if( m_ObjectName[i].Find(_T(" (T"))!=-1 )
			m_f_ObjectTransparency[i]=_wtoi(m_ObjectName[i].Mid(m_ObjectName[i].Find(_T(" (T"))+3))/100.0f;
		else
			m_f_ObjectTransparency[i]=0;

		// Selon le nom on positionne le fait que c'est un alpha ou pas
		if( m_ObjectName[i].Find(_T(" (A"))!=-1 )
			ObjectAlpha[i]=true;
		else
			ObjectAlpha[i]=false;

		// Selon le nom on positionne la Specialite
		if( m_ObjectName[i].Find(_T(" (Z"))!=-1 )
			m_i_Speciality[i]=_wtoi(m_ObjectName[i].Mid(m_ObjectName[i].Find(_T(" (Z"))+3));
		else
			m_i_Speciality[i]=0;

		// On extrait le vrai nom de l'object
		if( m_ObjectName[i].Find(_T(" ("))!=-1 )
			m_ObjectName[i] = m_ObjectName[i].Left(m_ObjectName[i].Find(_T(" (")));
	}

	// Create the textures
	CString TextureFileName;
	for( i=0; i<m_i_NbrObject; i++ )
	{
		TextureFileName.Format( _T("%s\\Textures\\%s.BMP"), FilePath, m_ObjectName[i] );
		if( ObjectAlpha[i] )
			m_TextureId[i] = CStaticGraphicalLib::LoadTexture( TextureFileName, CStaticGraphicalLib::ALPHA_ZERO_ON_BLACK );
		else
			m_TextureId[i] = CStaticGraphicalLib::LoadTexture( TextureFileName );
	}

	for( i=0; i<m_i_NbrObject; i++ )
		m_GeomListe[i]=-1;
}

// Compute the vectorial product
//
void CObject3D::ComputeVectorialProduct( double Vx1, double Vy1, double Vz1, double Vx2, double Vy2, double Vz2, double& Vx, double& Vy, double& Vz )
{
	Vx = Vy1*Vz2-Vz1*Vy2;
	Vy = Vz1*Vx2-Vx1*Vz2;
	Vz = Vx1*Vy2-Vy1*Vx2;
}

// Cree la liste OpenGL
//
void CObject3D::CreateList()
{
	int	i;

	// Creation des listes
	for( i=0; i<m_i_NbrObject; i++ )
	{
		if( m_GeomListe[i]>=0 )
			glDeleteLists( m_GeomListe[i], 1 );
		m_GeomListe[i] = glGenLists( 1 );;
		glNewList( m_GeomListe[i] , GL_COMPILE );

		int NbrTexture=0;
		glBegin(GL_TRIANGLES); 
		for( int j=0; j<m_i_NbrVtx[i]*3 ; j+=9 )
		{
			// Une facette = 3 points
			glNormal3fv( &(m_GlNormal[i][j]) );
			glTexCoord2fv( &(m_GlTexture[i][NbrTexture]) );
			NbrTexture += 2;
			glVertex3fv( &(m_GlVtx[i][j]) );
			glNormal3fv( &(m_GlNormal[i][j+3]) );
			glTexCoord2fv( &(m_GlTexture[i][NbrTexture]) );
			NbrTexture += 2;
			glVertex3fv( &(m_GlVtx[i][j+3]) );
			glNormal3fv( &(m_GlNormal[i][j+6]) );
			glTexCoord2fv( &(m_GlTexture[i][NbrTexture]) );
			NbrTexture += 2;
			glVertex3fv( &(m_GlVtx[i][j+6]) );
		}
		glEnd();
		
		glEndList();
	}
}

// set the translation
//
void CObject3D::SetTranslation( double x, double y, double z )
{
	m_Translation = Point3D((float) x, (float) y, (float) z);
}

// Draw the object
//
void CObject3D::Render( bool BindTexture )
{
	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW ); 
	glPushMatrix();

	glTranslated( m_Translation.x(), m_Translation.y(), m_Translation.z() );
	glScalef( 1, 1, (GLfloat) m_ScaleHeight );
	glScalef( (GLfloat) m_Scale, (GLfloat) m_Scale, (GLfloat) m_Scale );
	glRotated( m_Rotate, 0, 0, 1 );

	for( int i=0; i<m_i_NbrObject; i++ )
	{
		if( BindTexture )
		{
			// On selectionne la texture si on doit l'afficher
			if( m_TextureId[i]!=-1 )
				glBindTexture( GL_TEXTURE_2D, m_TextureId[i] );
		}
		glCallList( m_GeomListe[i] );
	}

	glPopMatrix();
}

// Draw the object as exploded point
//
void CObject3D::RenderAsExplodedPoint( double ExplodedSize )
{
	//TRACE( _T("Explodedsize : %f\n"), ExplodedSize );
	glMatrixMode( GL_MODELVIEW ); 
	glPushMatrix();

	glTranslated( m_Translation.x(), m_Translation.y(), m_Translation.z() );
	glScalef( 1, 1, (GLfloat) m_ScaleHeight );
	glScalef( (GLfloat) m_Scale, (GLfloat) m_Scale, (GLfloat) m_Scale );
	glScalef( (GLfloat) ExplodedSize, (GLfloat) ExplodedSize, (GLfloat) ExplodedSize );
	glRotated( m_Rotate, 0, 0, 1 );

	GLboolean Texture;
	glGetBooleanv( GL_TEXTURE_2D, &Texture );
	if( Texture )
		glDisable( GL_TEXTURE_2D );

	// Display points
	for( int i=0; i<m_i_NbrObject; i++ )
	{
		glBegin(GL_POINTS); 
		for( int j=0; j<m_i_NbrVtx[i]*3 ; j+=9 )
		{
			// Une facette = 3 points
			glNormal3fv( &(m_GlNormal[i][j]) );
			glVertex3fv( &(m_GlVtx[i][j]) );
			glNormal3fv( &(m_GlNormal[i][j+3]) );
			glVertex3fv( &(m_GlVtx[i][j+3]) );
			glNormal3fv( &(m_GlNormal[i][j+6]) );
			glVertex3fv( &(m_GlVtx[i][j+6]) );
		}
		glEnd();
	}

	if( Texture )
		glEnable( GL_TEXTURE_2D );

	glPopMatrix();
}

// Render the selected state
//
void CObject3D::RenderSelected()
{
	glLineWidth(2);
	glMatrixMode( GL_MODELVIEW ); 
	glPushMatrix();

	glTranslated( m_Translation.x(), m_Translation.y(), m_Translation.z() );
	glScalef( 1, 1, (GLfloat) m_ScaleHeight );
	glScalef( (GLfloat) m_Scale, (GLfloat) m_Scale, (GLfloat) m_Scale );
	glRotated( m_Rotate, 0, 0, 1 );

	GLdouble CurrentColor[4];
	glGetDoublev( GL_CURRENT_COLOR, CurrentColor );
	GLboolean Lighting;
	glGetBooleanv( GL_LIGHTING, &Lighting );
	glColor3f( 1, 1, 1 );
	GLboolean Texture;
	glGetBooleanv( GL_TEXTURE_2D, &Texture );
	glDisable( GL_LIGHTING );
	glDisable( GL_TEXTURE_2D );

	// Display surround
	glBegin(GL_LINE_STRIP); 
	glVertex3d( m_XMin, m_YMin, m_ZMin );
	glVertex3d( m_XMax, m_YMin, m_ZMin );
	glVertex3d( m_XMax, m_YMax, m_ZMin );
	glVertex3d( m_XMin, m_YMax, m_ZMin );
	glVertex3d( m_XMin, m_YMin, m_ZMin );
	glEnd();

	glBegin(GL_LINE_STRIP); 
	glVertex3d( m_XMin, m_YMin, m_ZMax );
	glVertex3d( m_XMax, m_YMin, m_ZMax );
	glVertex3d( m_XMax, m_YMax, m_ZMax );
	glVertex3d( m_XMin, m_YMax, m_ZMax );
	glVertex3d( m_XMin, m_YMin, m_ZMax );
	glEnd();

	glBegin(GL_LINES); 
	glVertex3d( m_XMin, m_YMin, m_ZMin );
	glVertex3d( m_XMin, m_YMin, m_ZMax );
	glVertex3d( m_XMax, m_YMin, m_ZMin );
	glVertex3d( m_XMax, m_YMin, m_ZMax );
	glVertex3d( m_XMin, m_YMax, m_ZMin );
	glVertex3d( m_XMin, m_YMax, m_ZMax );
	glVertex3d( m_XMax, m_YMax, m_ZMin );
	glVertex3d( m_XMax, m_YMax, m_ZMax );
	glEnd();

	if( Texture )
		glEnable( GL_TEXTURE_2D );
	if( Lighting )
		glEnable( GL_LIGHTING );
	glColor3dv( CurrentColor );

	glPopMatrix();
}
