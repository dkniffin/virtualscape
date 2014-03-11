#include "StdAfx.h"

#include "GL/gl.h" 
#include "GL/glu.h" 

#include "Smoke.h"
#include "StaticGraphicalLib.h"

// The constructor
//
CSmoke::CSmoke( double PositionX, double PositionY, double PositionZ, SmokeColor aSmokeColor, CHeroscapeEditor3DView* pView )
{
	m_Position.x = PositionX;
	m_Position.y = PositionY;
	m_Position.z = PositionZ;
	m_Rotate = ((double) rand()/(double) RAND_MAX)*0.2-0.1;
	m_MoveX = ((double) rand()/(double) RAND_MAX)*0.001-0.0005;
	m_MoveY = ((double) rand()/(double) RAND_MAX)*0.001-0.0005;
	m_MoveZ = ((double) rand()/(double) RAND_MAX)*0.0001+0.001;
	switch( aSmokeColor )
	{
	case SC_BLACK:
		m_SmokeTextureId = pView->GetTextureId( _T("SmokeBlack.bmp"), CStaticGraphicalLib::BLACK_ALPHA_LUMINOSITY );
		break;
/*	case SC_WHITE:
		m_SmokeTextureId = World.m_SmokeTextureWhiteId;
		break;*/
	case SC_RED:
		m_SmokeTextureId = pView->GetTextureId( _T("SmokeRed.bmp"), CStaticGraphicalLib::RED_ALPHA_LUMINOSITY );
		break;
	case SC_BLUE:
		m_SmokeTextureId = pView->GetTextureId( _T("SmokeBlue.bmp"), CStaticGraphicalLib::BLUE_ALPHA_LUMINOSITY );
		break;
/*	case SC_GREEN:
		m_SmokeTextureId = World.m_SmokeTextureGreenId;
		break;
	case SC_REDBLUE:
		m_SmokeTextureId = World.m_SmokeTextureVioletId;
		break;*/
	}
}

// The destructor
//
CSmoke::~CSmoke(void)
{
}

// Render the object
//
void CSmoke::Render( int ExplodeTime, CHeroscapeEditor3DView* pView, bool BindTexture )
{
	glMatrixMode(GL_MODELVIEW );
	glPushMatrix();
	if( BindTexture )
		glBindTexture( GL_TEXTURE_2D, m_SmokeTextureId );
	glTranslated( m_Position.x + ExplodeTime*m_MoveX, m_Position.y + ExplodeTime*m_MoveY, -0.3+m_Position.z+ExplodeTime*m_MoveZ );
	double Scale = (1-pow((1-ExplodeTime/1000.0),4))*2+.3;
	glScaled( Scale, Scale, Scale );
	CStaticGraphicalLib::BilboardMatrix( (float) (pView->m_CameraLookAt.x-pView->m_CameraPosition.x), (float) (pView->m_CameraLookAt.y-pView->m_CameraPosition.y) );
	//glRotated( ExplodeTime*m_Rotate, 0, 1, 0 );
	GLfloat Color[4];
	glGetFloatv( GL_CURRENT_COLOR, Color );
	glColor4d( 1, 1, 1, (1-ExplodeTime/1000.0)*0.5 );
	glBegin( GL_QUADS );
	glTexCoord2f( 0, 0 );
	glVertex3d( -.5, 0, 0 );
	glTexCoord2f( 1, 0 );
	glVertex3d( .5, 0, 0 );
	glTexCoord2f( 1, 1 );
	glVertex3d( .5, 0, 1 );
	glTexCoord2f( 0, 1 );
	glVertex3d( -.5, 0, 1 );
	glEnd();
	glColor4fv( Color );
	glPopMatrix();
}
