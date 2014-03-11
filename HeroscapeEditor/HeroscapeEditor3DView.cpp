// Implementation de la classe CHeroscapeEditor3DView
//

#include "StdAfx.h"

#include "GL/gl.h" 
#include "GL/glu.h" 
#include "glh/glh_extensions.h"
#include "glh/glh_obs.h"
#include <Math.h>
#include "shared/pbuffer.h"

#include "FigureObject.h"
#include "HeroscapeEditor.h"
#include "HeroscapeEditor3DView.h"
#include "MainFrm.h"
#include "Maths/Color.h"
#include "MyListCtrl.h"
#include "PersonalTexture.h"
#include "ProgressDlg.h"
#include "RenderOptionDlg.h"
#include "StaticGraphicalLib.h"
#include "Tile.h"

#define REQUIRED_EXTENSIONS "GL_ARB_multitexture " \
                            "GL_ARB_depth_texture " \
                            "GL_ARB_shadow " \
                            "WGL_ARB_pbuffer " \
                            "WGL_ARB_pixel_format " 
unsigned char threeto8[8] =
{
	0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};

unsigned char twoto8[4] =
{
	0, 0x55, 0xaa, 0xff
};

unsigned char oneto8[2] =
{
	0, 255
};

static int defaultOverride[13] =
{
	0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

static PALETTEENTRY defaultPalEntry[20] =
{
	{ 0,   0,   0,    0 },
	{ 0x80,0,   0,    0 },
	{ 0,   0x80,0,    0 },
	{ 0x80,0x80,0,    0 },
	{ 0,   0,   0x80, 0 },
	{ 0x80,0,   0x80, 0 },
	{ 0,   0x80,0x80, 0 },
	{ 0xC0,0xC0,0xC0, 0 },

	{ 192, 220, 192,  0 },
	{ 166, 202, 240,  0 },
	{ 255, 251, 240,  0 },
	{ 160, 160, 164,  0 },

	{ 0x80,0x80,0x80, 0 },
	{ 0xFF,0,   0,    0 },
	{ 0,   0xFF,0,    0 },
	{ 0xFF,0xFF,0,    0 },
	{ 0,   0,   0xFF, 0 },
	{ 0xFF,0,   0xFF, 0 },
	{ 0,   0xFF,0xFF, 0 },
	{ 0xFF,0xFF,0xFF, 0 }
};

IMPLEMENT_DYNCREATE(CHeroscapeEditor3DView, CView)

BEGIN_MESSAGE_MAP(CHeroscapeEditor3DView, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	//{{AFX_MSG_MAP(CHeroscapeEditor3DView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDR_TOOLBAR3D_DISPLAYSHADOW, &CHeroscapeEditor3DView::OnToolbar3dDisplayshadow)
	ON_UPDATE_COMMAND_UI(IDR_TOOLBAR3D_DISPLAYSHADOW, &CHeroscapeEditor3DView::OnUpdateToolbar3dDisplayshadow)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_OUTILS_VUEHAUTEQUALITE, &CHeroscapeEditor3DView::OnOutilsVuehautequalite)
	ON_COMMAND(ID_CAMERA_GO_HOME, &CHeroscapeEditor3DView::OnCameraGoHome)
	ON_COMMAND(ID_OUTILS_TOURNEAUTOUR, &CHeroscapeEditor3DView::OnOutilsTourneautour)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_TOURNEAUTOUR, &CHeroscapeEditor3DView::OnUpdateOutilsTourneautour)
	ON_COMMAND(ID_OUTILS_VOIRLACONSTRUCTION, &CHeroscapeEditor3DView::OnOutilsVoirlaconstruction)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_VOIRLACONSTRUCTION, &CHeroscapeEditor3DView::OnUpdateOutilsVoirlaconstruction)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_VUEHAUTEQUALITE, &CHeroscapeEditor3DView::OnUpdateOutilsVuehautequalite)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_OUTILS_SAVEIMAGE, &CHeroscapeEditor3DView::OnOutilsSaveimage)
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_VIDEO_ERASE_ALL_POSITION, &CHeroscapeEditor3DView::OnUpdateVideoEraseAllPosition)
	ON_COMMAND(ID_VIDEO_ERASE_ALL_POSITION, &CHeroscapeEditor3DView::OnVideoEraseAllPosition)
	ON_COMMAND(ID_VIDEO_ADD_CURRENT_POSITION, &CHeroscapeEditor3DView::OnVideoAddCurrentPosition)
	ON_UPDATE_COMMAND_UI(ID_VIDEO_ADD_CURRENT_POSITION, &CHeroscapeEditor3DView::OnUpdateVideoAddCurrentPosition)
	ON_UPDATE_COMMAND_UI(ID_VIDEO_MOVE_REALTIME, &CHeroscapeEditor3DView::OnUpdateVideoMoveRealtime)
	ON_COMMAND(ID_VIDEO_MOVE_REALTIME, &CHeroscapeEditor3DView::OnVideoMoveRealtime)
	ON_UPDATE_COMMAND_UI(ID_VIDEO_CREATE_FILE, &CHeroscapeEditor3DView::OnUpdateVideoCreateFile)
	ON_COMMAND(ID_VIDEO_CREATE_FILE, &CHeroscapeEditor3DView::OnVideoCreateFile)
	ON_UPDATE_COMMAND_UI(ID_VIDEO_SAVE_POSITION, &CHeroscapeEditor3DView::OnUpdateVideoSavePosition)
	ON_COMMAND(ID_VIDEO_SAVE_POSITION, &CHeroscapeEditor3DView::OnVideoSavePosition)
	ON_COMMAND(ID_VIDEO_LOAD_POSITION, &CHeroscapeEditor3DView::OnVideoLoadPosition)
	ON_UPDATE_COMMAND_UI(ID_VIDEO_LOAD_POSITION, &CHeroscapeEditor3DView::OnUpdateVideoLoadPosition)
	ON_COMMAND(ID_OUTILS_VUETOPOGRAPHIQUE, &CHeroscapeEditor3DView::OnOutilsVuetopographique)
	ON_COMMAND(ID_OUTILS_VUESTEREO, &CHeroscapeEditor3DView::OnOutilsVuestereo)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_VUESTEREO, &CHeroscapeEditor3DView::OnUpdateOutilsVuestereo)
	ON_COMMAND(ID_OUTILS_VUESTEREOINTERLACED, &CHeroscapeEditor3DView::OnOutilsVuestereointerlaced)
	ON_UPDATE_COMMAND_UI(ID_OUTILS_VUESTEREOINTERLACED, &CHeroscapeEditor3DView::OnUpdateOutilsVuestereointerlaced)
	ON_UPDATE_COMMAND_UI(ID_PLACE_FIGURE_ON_MAP, &CHeroscapeEditor3DView::OnUpdatePlaceFigureOnMap)
	ON_UPDATE_COMMAND_UI(ID_REMOVE_FIGURE_FROM_MAP, &CHeroscapeEditor3DView::OnUpdateRemoveFigureFromMap)
	ON_UPDATE_COMMAND_UI(ID_MOVE_FIGURE, &CHeroscapeEditor3DView::OnUpdateMoveFigure)
	ON_UPDATE_COMMAND_UI(ID_ATTACK_CHOOSE_FIGURE, &CHeroscapeEditor3DView::OnUpdateAttackChooseFigure)
	ON_UPDATE_COMMAND_UI(ID_DEFENSE_DICE, &CHeroscapeEditor3DView::OnUpdateDefenseDice)
	ON_UPDATE_COMMAND_UI(ID_NEXT_TURN, &CHeroscapeEditor3DView::OnUpdateNextTurn)
	ON_UPDATE_COMMAND_UI(ID_ATTACK_DICE, &CHeroscapeEditor3DView::OnUpdateAttackDice)
	ON_UPDATE_COMMAND_UI(ID_REPLAY_GAME, &CHeroscapeEditor3DView::OnUpdateReplayGame)
	ON_UPDATE_COMMAND_UI(ID_REPLAY_TO_FILE, &CHeroscapeEditor3DView::OnUpdateReplayToFile)
	ON_UPDATE_COMMAND_UI(ID_CAMERA_GO_HOME, &CHeroscapeEditor3DView::OnUpdateCameraGoHome)
	ON_UPDATE_COMMAND_UI(ID_DIE_20, &CHeroscapeEditor3DView::OnUpdateDie20Faces)
END_MESSAGE_MAP()

// Le constructeur
//
CHeroscapeEditor3DView::CHeroscapeEditor3DView()
{
	m_pDC = NULL;
	m_hRC = NULL;
	m_pOldPalette = NULL;
	// The original camera position
	m_CameraPosition.x = -20.5f;
	m_CameraPosition.y = -30.5f;
	m_CameraPosition.z = 20.0f;
	// The current angle of camera
	m_CameraAngleH = 80;
	m_CameraAngleV = -30;
	// Set the frequency counter
	LARGE_INTEGER	Ret;
	QueryPerformanceFrequency( &Ret );
	m_frequency = Ret.QuadPart;
	// the default shadow map
	m_ShadowMapSize = (int) (256*pow(2.0,(double)theApp.m_ShadowQuality));
	m_DisplayShadow = theApp.m_DisplayShadow;
	m_ShadowMapTexture = -1;
	// Compute Shadow is not initialise
	m_ComputeShadowIsInitialise = false;
	// Don't move now
	m_IsMove = false;
	m_pBuffer=NULL;
	// No mode now
	m_Mode = MODE3D_NULL;
	// No level limit
	m_LastLevelToDisplay = 999;
	// No view point
	m_pViewPoint = NULL;
	// The scene need to be redraw
	m_IsModified = true;
	// Normal camera (no topographic camera)
	m_CameraForTopography = false;
	// No stereoscopic rendering
	m_StereoscopicView = false;
	// No stereoscopic interlaced rendering
	m_RenderInterlacedStereoscopic = false;
	// Distance for stereoscopic camera focus
	m_CameraStereoFocusDistance = 50;
	// For select position (in game mode for exemple to place a figure)
	m_DisplayPositionX = m_DisplayPositionY = m_DisplayPositionZ = -1;
	m_DisplayPositionTwoCase = false;
	m_pSelectedFigure = NULL;
	// No replay mode now
	m_IsReplayMode = false;
}

// Apres que la fenetre soit cree
//
void CHeroscapeEditor3DView::AfterCreate()
{
	SetTimer( 1, 15, NULL );
}

// Le destructeur
//
CHeroscapeEditor3DView::~CHeroscapeEditor3DView()
{
	if( m_pTree10!=NULL )
		delete m_pTree10;
	if( m_pTree11!=NULL )
		delete m_pTree11;
	if( m_pTree12!=NULL )
		delete m_pTree12;
	if( m_pTree15!=NULL )
		delete m_pTree15;
	if( m_pRuin2!=NULL )
		delete m_pRuin2;
	if( m_pRuin3!=NULL )
		delete m_pRuin3;
	if( m_pGlacier1!=NULL )
		delete m_pGlacier1;
	if( m_pGlacier3!=NULL )
		delete m_pGlacier3;
	if( m_pGlacier4!=NULL )
		delete m_pGlacier4;
	if( m_pGlacier6!=NULL )
		delete m_pGlacier6;
	if( m_pHive6!=NULL )
		delete m_pHive6;
	if( m_pWall4!=NULL )
		delete m_pWall4;
	if( m_pCastleBaseEnd!=NULL )
		delete m_pCastleBaseEnd;
	if( m_pCastleBaseStraight!=NULL )
		delete m_pCastleBaseStraight;
	if( m_pCastleBaseCorner!=NULL )
		delete m_pCastleBaseCorner;
	if( m_pCastleWallCorner!=NULL )
		delete m_pCastleWallCorner;
	if( m_pCastleWallStraight!=NULL )
		delete m_pCastleWallStraight;
	if( m_pCastleWallEnd!=NULL )
		delete m_pCastleWallEnd;
	if( m_pCastleBattlement!=NULL )
		delete m_pCastleBattlement;
	if( m_pCastleDoor!=NULL )
		delete m_pCastleDoor;
	if( m_pCastleLadder!=NULL )
		delete m_pCastleLadder;
	if( m_pCastleFlag!=NULL )
		delete m_pCastleFlag;
	if( m_pMarvelRuin6!=NULL )
		delete m_pMarvelRuin6;
	if( m_pMarvelRuin6Breaked!=NULL )
		delete m_pMarvelRuin6Breaked;
	if( m_pPalm1!=NULL )
		delete m_pPalm1;
	if( m_pTicallaGrass1!=NULL )
		delete m_pTicallaGrass1;
	if( m_pOutcrop1!=NULL )
		delete m_pOutcrop1;
	if( m_pOutcrop3!=NULL )
		delete m_pOutcrop3;

	if (::wglGetCurrentContext())
		::wglMakeCurrent(NULL, NULL);
	
	if (m_hRC != NULL)
	{
		::wglDeleteContext(m_hRC);
		m_hRC = NULL;
	}

	if( m_pBuffer!=NULL )
	{
		m_pBuffer->Destroy();
		delete m_pBuffer;
	}

	FreeViewPoint();

	FreeAnimatedPath();
	FreeAnimatedPosition();
}

// Avant la creation de la vue
//
BOOL CHeroscapeEditor3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// An OpenGL window must be created with the following flags and must not
	// include CS_PARENTDC for the class style. Refer to SetPixelFormat
	// documentation in the "Comments" section for further information.
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// Dessine la vue
//
void CHeroscapeEditor3DView::OnDraw(CDC* pDC)
{
	// Swap the buffer
	if( pDC )
		wglMakeCurrent( m_pDC->GetSafeHdc() ,m_hRC);

	if( m_StereoscopicView )
		RenderStereoView();
	else if( m_pViewPoint!=NULL && !m_IsModified )
	{
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		glRasterPos4d( -1, -1, 0, 1 );
		glPixelStorei( GL_PACK_ALIGNMENT, 4 );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
		glDisable(GL_TEXTURE_2D);
		glDisable( GL_BLEND );
		glDisable(GL_LIGHTING);
		glDrawPixels( m_i_Width, m_i_Heigth, GL_BGR_EXT, GL_UNSIGNED_BYTE, m_pViewPoint );
	}
	else
		RenderScene();

	// Swap the buffer
	if( pDC )
	{
		SwapBuffers(pDC->GetSafeHdc());
	}
}

// Save image in memory
//
void CHeroscapeEditor3DView::SaveImageInMemory()
{
	if( m_pViewPoint!=NULL )
	{
		glPixelStorei( GL_PACK_ALIGNMENT, 4 );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );
		// Copy from OpenGL
		glFlush();
		glReadBuffer( GL_FRONT );
		::glReadPixels(0,0,m_i_Width,m_i_Heigth,GL_BGR_EXT,GL_UNSIGNED_BYTE,(GLvoid*) m_pViewPoint); 
	}
}

// Start rendering.
//
void CHeroscapeEditor3DView::RenderScene( bool ForHighQuality )
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	glViewport(0, 0, m_i_Width, m_i_Heigth);

	ViewMatrix();

	glClearColor( (GLclampf) (GetRValue(theApp.m_BackgroundColor3D)/255.0), (GLclampf) (GetGValue(theApp.m_BackgroundColor3D)/255.0), (GLclampf) (GetBValue(theApp.m_BackgroundColor3D)/255.0), 0 );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode( GL_TEXTURE );
	glLoadIdentity();

	if( m_DisplayShadow )
	{
		if( pDoc->m_TileList.GetCount()>0 )
		{
			//restore states
			glCullFace(GL_BACK);
			glShadeModel(GL_SMOOTH);

			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(m_CameraProjectionMatrix);

			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(m_CameraViewMatrix);

			//Use dim light to represent shadowed areas
			glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(m_LightPosition));
			if( ForHighQuality )
			{
				glLightfv(GL_LIGHT1, GL_AMBIENT, black);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, black);
				glColor4f( 0, 0, 0, 0);
			}
			else
			{
				glLightfv(GL_LIGHT1, GL_AMBIENT, white*(0.3f-theApp.m_ShadowContrast/100.0f));
				glLightfv(GL_LIGHT1, GL_DIFFUSE, white*(0.3f-theApp.m_ShadowContrast/100.0f));
				glColor4f( 1, 1, 1, 1);
			}
			glLightfv(GL_LIGHT1, GL_SPECULAR, black);
			glEnable(GL_LIGHT1);
			//glDisable(GL_LIGHT0);
			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);

			for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
			{
				CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

				if( (pTile->m_Type/1000)!=TYPE_STARTAREA && pTile->m_PosZ<=m_LastLevelToDisplay )
					pTile->Render( this );
			}
			if( theApp.m_DisplayTable )
				RenderBox( false );

			//RenderMoveArrow( false );

			//3rd pass
			//Draw with bright light
			if( ForHighQuality )
				glColor4f( 10.0f, 10.0f, 10.0f, 10.0f);
			else
				glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
			glLightfv(GL_LIGHT1, GL_SPECULAR, white);

			//Calculate texture matrix for projection
			//This matrix takes us from eye space to the light's clip space
			//It is postmultiplied by the inverse of the current view matrix when specifying texgen
			static MATRIX4X4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,	0.0f, 0.5f, 0.0f, 0.0f,	0.0f, 0.0f, 0.5f, 0.0f,	0.5f, 0.5f, 0.5f, 1.0f); //bias from [-1, 1] to [0, 1]
			MATRIX4X4 textureMatrix=biasMatrix*m_LightProjectionMatrix*m_LightViewMatrix;

			//Set up texture coordinate generation.
			glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
			glEnable(GL_TEXTURE_GEN_S);

			glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
			glEnable(GL_TEXTURE_GEN_T);

			glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
			glEnable(GL_TEXTURE_GEN_R);

			glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
			glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
			glEnable(GL_TEXTURE_GEN_Q);

			//Bind & enable shadow map texture
			glBindTexture(GL_TEXTURE_2D, m_ShadowMapTexture);
			glEnable(GL_TEXTURE_2D);

			//Enable shadow comparison
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

			//Shadow comparison should be true (ie not in shadow) if r<=texture
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

			//Shadow comparison should generate an INTENSITY result
			if( ForHighQuality )
				glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_LUMINANCE);
			else
				glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

			//Set alpha test to discard false comparisons
			glAlphaFunc(GL_GEQUAL, 0.99f);
			glEnable(GL_ALPHA_TEST);

			for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
			{
				CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

				if( (pTile->m_Type/1000)!=TYPE_STARTAREA && pTile->m_PosZ<=m_LastLevelToDisplay )
					pTile->Render( this );
			}
			if( theApp.m_DisplayTable )
				RenderBox( false );

			//RenderMoveArrow( false );

			glDisable(GL_TEXTURE_GEN_S);
			glDisable(GL_TEXTURE_GEN_T);
			glDisable(GL_TEXTURE_GEN_R);
			glDisable(GL_TEXTURE_GEN_Q);

			//Restore other states
			glDisable(GL_ALPHA_TEST);

			if( ForHighQuality )
			{
				glEnable( GL_LIGHTING );
				glLightfv(GL_LIGHT1, GL_AMBIENT, black);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, white*1000);
				glLightfv(GL_LIGHT1, GL_SPECULAR, white*1000);
			}
			glColor4f( 1, 1, 1, 1);
			glEnable( GL_BLEND );
			glBlendFunc( GL_DST_COLOR, GL_ZERO );
			
			for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
			{
				CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

				if( (pTile->m_Type/1000)!=TYPE_STARTAREA && pTile->m_PosZ<=m_LastLevelToDisplay )
					pTile->Render( this, false, true );
			}
			
			if( theApp.m_DisplayTable )
				RenderBox( true);

			RenderMoveArrow( false );

			for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
			{
				CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

				if( (pTile->m_Type/1000)==TYPE_STARTAREA && pTile->m_PosZ<=m_LastLevelToDisplay )
					pTile->Render( this, false, true );
			}

			//Disable textures and texgen
			glDisable(GL_TEXTURE_2D);
			glDisable( GL_BLEND );
			glDisable(GL_LIGHTING);

			if( m_RenderInterlacedStereoscopic )
			{
				glReadBuffer(GL_BACK);
				glPixelStorei( GL_PACK_ROW_LENGTH, 0 );
				glPixelStorei(GL_PACK_SKIP_ROWS, 0);
				glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
				glPixelStorei( GL_PACK_ALIGNMENT, 1 );
				glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
				glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
				glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
				glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

				unsigned char* LeftImage = (unsigned char*) malloc( sizeof(unsigned char)*3*m_i_Width*m_i_Heigth );
				unsigned char* RightImage = (unsigned char*) malloc( sizeof(unsigned char)*3*m_i_Width*m_i_Heigth );
					
				glReadPixels( 0, 0, m_i_Width, m_i_Heigth, GL_RGB, GL_UNSIGNED_BYTE, LeftImage );

				glClearColor( (GLclampf) (GetRValue(theApp.m_BackgroundColor3D)/255.0), (GLclampf) (GetGValue(theApp.m_BackgroundColor3D)/255.0), (GLclampf) (GetBValue(theApp.m_BackgroundColor3D)/255.0), 0 );
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				ViewMatrixStereoRight();

				glMatrixMode( GL_TEXTURE );
				glLoadIdentity();

				if( pDoc->m_TileList.GetCount()>0 )
				{
					//restore states
					glCullFace(GL_BACK);
					glShadeModel(GL_SMOOTH);

					glMatrixMode(GL_PROJECTION);
					glLoadMatrixf(m_CameraProjectionMatrix);

					glMatrixMode(GL_MODELVIEW);
					glLoadMatrixf(m_CameraViewMatrix);

					//Use dim light to represent shadowed areas
					glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(m_LightPosition));
					if( ForHighQuality )
					{
						glLightfv(GL_LIGHT1, GL_AMBIENT, black);
						glLightfv(GL_LIGHT1, GL_DIFFUSE, black);
						glColor4f( 0, 0, 0, 0);
					}
					else
					{
						glLightfv(GL_LIGHT1, GL_AMBIENT, white*(0.3f-theApp.m_ShadowContrast/100.0f));
						glLightfv(GL_LIGHT1, GL_DIFFUSE, white*(0.3f-theApp.m_ShadowContrast/100.0f));
						glColor4f( 1, 1, 1, 1);
					}
					glLightfv(GL_LIGHT1, GL_SPECULAR, black);
					glEnable(GL_LIGHT1);
					//glDisable(GL_LIGHT0);
					glEnable(GL_LIGHTING);
					glDisable(GL_TEXTURE_2D);

					for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
					{
						CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

						if( (pTile->m_Type/1000)!=TYPE_STARTAREA && pTile->m_PosZ<=m_LastLevelToDisplay )
							pTile->Render( this );
					}
					if( theApp.m_DisplayTable )
						RenderBox( false );

					RenderMoveArrow( false );

					//3rd pass
					//Draw with bright light
					if( ForHighQuality )
						glColor4f( 10.0f, 10.0f, 10.0f, 10.0f);
					else
						glColor4f( 1.0f, 1.0f, 1.0f, 1.0f);
					glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
					glLightfv(GL_LIGHT1, GL_SPECULAR, white);

					//Calculate texture matrix for projection
					//This matrix takes us from eye space to the light's clip space
					//It is postmultiplied by the inverse of the current view matrix when specifying texgen
					static MATRIX4X4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,	0.0f, 0.5f, 0.0f, 0.0f,	0.0f, 0.0f, 0.5f, 0.0f,	0.5f, 0.5f, 0.5f, 1.0f); //bias from [-1, 1] to [0, 1]
					MATRIX4X4 textureMatrix=biasMatrix*m_LightProjectionMatrix*m_LightViewMatrix;

					//Set up texture coordinate generation.
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
					glTexGenfv(GL_S, GL_EYE_PLANE, textureMatrix.GetRow(0));
					glEnable(GL_TEXTURE_GEN_S);

					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
					glTexGenfv(GL_T, GL_EYE_PLANE, textureMatrix.GetRow(1));
					glEnable(GL_TEXTURE_GEN_T);

					glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
					glTexGenfv(GL_R, GL_EYE_PLANE, textureMatrix.GetRow(2));
					glEnable(GL_TEXTURE_GEN_R);

					glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
					glTexGenfv(GL_Q, GL_EYE_PLANE, textureMatrix.GetRow(3));
					glEnable(GL_TEXTURE_GEN_Q);

					//Bind & enable shadow map texture
					glBindTexture(GL_TEXTURE_2D, m_ShadowMapTexture);
					glEnable(GL_TEXTURE_2D);

					//Enable shadow comparison
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

					//Shadow comparison should be true (ie not in shadow) if r<=texture
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

					//Shadow comparison should generate an INTENSITY result
					if( ForHighQuality )
						glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_LUMINANCE);
					else
						glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

					//Set alpha test to discard false comparisons
					glAlphaFunc(GL_GEQUAL, 0.99f);
					glEnable(GL_ALPHA_TEST);

					for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
					{
						CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

						if( (pTile->m_Type/1000)!=TYPE_STARTAREA && pTile->m_PosZ<=m_LastLevelToDisplay )
							pTile->Render( this );
					}
					if( theApp.m_DisplayTable )
						RenderBox( false );

					RenderMoveArrow( false );

					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);
					glDisable(GL_TEXTURE_GEN_R);
					glDisable(GL_TEXTURE_GEN_Q);

					//Restore other states
					glDisable(GL_ALPHA_TEST);

					if( ForHighQuality )
					{
						glEnable( GL_LIGHTING );
						glLightfv(GL_LIGHT1, GL_AMBIENT, black);
						glLightfv(GL_LIGHT1, GL_DIFFUSE, white*1000);
						glLightfv(GL_LIGHT1, GL_SPECULAR, white*1000);
					}
					glColor4f( 1, 1, 1, 1);
					glEnable( GL_BLEND );
					glBlendFunc( GL_DST_COLOR, GL_ZERO );
					
					for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
					{
						CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

						if( (pTile->m_Type/1000)!=TYPE_STARTAREA && pTile->m_PosZ<=m_LastLevelToDisplay )
							pTile->Render( this, false, true );
					}
					
					if( theApp.m_DisplayTable )
						RenderBox( true);

					RenderMoveArrow( true );

					for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
					{
						CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

						if( (pTile->m_Type/1000)==TYPE_STARTAREA && pTile->m_PosZ<=m_LastLevelToDisplay )
							pTile->Render( this, false, true );
					}

					//Disable textures and texgen
					glDisable(GL_TEXTURE_2D);
					glDisable( GL_BLEND );
					glDisable(GL_LIGHTING);
				}

				glReadPixels( 0, 0, m_i_Width, m_i_Heigth, GL_RGB, GL_UNSIGNED_BYTE, RightImage );

				CRect Rect;
				GetClientRect( &Rect );
				ClientToScreen( &Rect );
				if( (Rect.bottom%2)==0 )
				{
					for( int y=0; y<m_i_Heigth; y+=2 )
						memcpy( LeftImage+m_i_Width*3*y, RightImage+m_i_Width*3*y, m_i_Width*3 );
				}
				else
				{
					for( int y=1; y<m_i_Heigth; y+=2 )
						memcpy( LeftImage+m_i_Width*3*y, RightImage+m_i_Width*3*y, m_i_Width*3 );
				}

				glDrawBuffer( GL_BACK );
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				glRasterPos4d( -1, -1, 0, 1 );
				glDrawPixels( m_i_Width, m_i_Heigth, GL_RGB, GL_UNSIGNED_BYTE, LeftImage );

				free( LeftImage );
				free( RightImage );
			}

			// Render explode
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glDepthMask( 0 );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
			{
				CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

				if( pTile->m_PosZ<=m_LastLevelToDisplay )
					pTile->RenderExplode( this, true );
			}
			glDepthMask( 1 );
			glDisable(GL_TEXTURE_2D);
			glDisable( GL_BLEND );
			glDisable(GL_LIGHTING);

			DisplayPosition();
		}
	}
	else
	{
		if( pDoc->m_TileList.GetCount()>0 )
		{
			glMatrixMode(GL_PROJECTION);
			glLoadMatrixf(m_CameraProjectionMatrix);

			glMatrixMode(GL_MODELVIEW);
			glLoadMatrixf(m_CameraViewMatrix);

			glEnable(GL_TEXTURE_2D);
			glLightfv(GL_LIGHT1, GL_POSITION, VECTOR4D(m_LightPosition));
			glLightfv(GL_LIGHT1, GL_AMBIENT, white*0.2f);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, white*0.8f);
			glLightfv(GL_LIGHT1, GL_SPECULAR, white);
			glEnable(GL_LIGHT1);
			glEnable(GL_LIGHTING);
			glDisable( GL_BLEND );

			//DrawScene( (float) m_Angle );
			for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
			{
				CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

				if( pTile->m_PosZ<=m_LastLevelToDisplay )
					pTile->Render( this, false, true );
			}
			if( theApp.m_DisplayTable )
				RenderBox( true );

			RenderMoveArrow( true );

			// Render explode
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glDepthMask( 0 );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
			{
				CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

				if( pTile->m_PosZ<=m_LastLevelToDisplay )
					pTile->RenderExplode( this, true );
			}
			glDepthMask( 1 );

			DisplayPosition();
		}
	}

	// Draw animated path
/*	glColor3f( 1, 0, 0 );
	glBegin( GL_LINE_STRIP );
	for( int i=0; i<m_AnimatedPositionList.GetCount(); i++ )
	{
		AnimatedPosition* pPosition = (AnimatedPosition*) m_AnimatedPositionList.GetAt(i);
		glVertex3d( pPosition->pCameraPoint->x, pPosition->pCameraPoint->y, pPosition->pCameraPoint->z );
	}
	glEnd();

	glColor3f( 1, 1, 0 );
	glBegin( GL_LINE_STRIP );
	for( int i=0; i<m_AnimatedPath.GetCount(); i++ )
	{
		AnimatedPosition* pPosition = (AnimatedPosition*) m_AnimatedPath.GetAt(i);
		glVertex3d( pPosition->pCameraPoint->x, pPosition->pCameraPoint->y, pPosition->pCameraPoint->z );
	}
	glEnd();

	glColor3f( 1, 0, 0 );
	glBegin( GL_LINE_STRIP );
	for( int i=0; i<m_AnimatedPositionList.GetCount(); i++ )
	{
		AnimatedPosition* pPosition = (AnimatedPosition*) m_AnimatedPositionList.GetAt(i);
		glVertex3d( pPosition->pLookAt->x, pPosition->pLookAt->y, pPosition->pLookAt->z );
	}
	glEnd();

	glColor3f( 1, 1, 0 );
	glBegin( GL_LINE_STRIP );
	for( int i=0; i<m_AnimatedPath.GetCount(); i++ )
	{
		AnimatedPosition* pPosition = (AnimatedPosition*) m_AnimatedPath.GetAt(i);
		glVertex3d( pPosition->pLookAt->x, pPosition->pLookAt->y, pPosition->pLookAt->z );
	}
	glEnd();*/
}

// Display a position
//
void CHeroscapeEditor3DView::DisplayPosition()
{
	if( m_DisplayPositionX<0 )
		return;
	if( m_Mode!=MODE3D_SELECT_POSITION )
		return;

	glMatrixMode( GL_MODELVIEW );
	/*glPushMatrix();

	glLoadName( 999999999 );

	if( m_DisplayPositionY%2==1 )
		glTranslated( m_DisplayPositionX*TILE3D_WIDTH+TILE3D_X3, -m_DisplayPositionY*TILE3D_HEIGHT, (m_DisplayPositionZ+1.1)*TILE3D_ZHEIGHT );
	else
		glTranslated( (m_DisplayPositionX)*TILE3D_WIDTH, -m_DisplayPositionY*TILE3D_HEIGHT, (m_DisplayPositionZ+1.1)*TILE3D_ZHEIGHT );

	TRACE("position x %i\n", m_DisplayPositionX );

	if( m_DisplayPositionTwoCase )
	{
		switch( m_DisplayPositionRotation )
		{
		case 0:
		case 1:
		case 2:
			break;
		case 3:
			glTranslated( TILE3D_WIDTH, 0, 0 );
			break;
		case 4:
			glTranslated( TILE3D_WIDTH/2.0, -TILE3D_HEIGHT, 0 );
			break;
		case 5:
			glTranslated( -TILE3D_WIDTH/2.0, -TILE3D_HEIGHT, 0 );
			break;
		}
	}

	glRotated( -m_DisplayPositionRotation*60, 0, 0, 1 );

	GLUquadricObj* pQuadric = gluNewQuadric();

	gluPartialDisk( pQuadric, 0, TILE3D_WIDTH/2, 6, 1, 0, 360 );

	if( m_DisplayPositionTwoCase )
	{
		glTranslated( TILE3D_WIDTH, 0, 0 );

		gluPartialDisk( pQuadric, 0, TILE3D_WIDTH/2, 10, 1, 0, 360 );
	}

	glPopMatrix();*/

	int OldPosX = theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_PosX;
	int OldPosY = theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_PosY;
	int OldPosZ = theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_PosZ;
	int OldRotation = theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_CurrentRotation;
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_PosX = m_DisplayPositionX;
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_PosY = m_DisplayPositionY;
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_PosZ = m_DisplayPositionZ+1;
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_CurrentRotation = m_DisplayPositionRotation;
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_CreationTime = 0.5;
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->Render1( this, false, false );
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_PosX = OldPosX;
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_PosY = OldPosY;
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_PosZ = OldPosZ;
	theApp.m_pGameDoc->m_pCurrentFigure->m_pTileFigure->m_CurrentRotation = OldRotation;
}

// Render box under battlefield
//
void CHeroscapeEditor3DView::RenderBox( bool BindTexture )
{
	if( BindTexture )
		glBindTexture( GL_TEXTURE_2D, m_TextureIdBox );

	glLoadName( 999999999 );

	glBegin(GL_QUADS);

	// Up
	glNormal3d( 0, 0, 1 );
	glTexCoord2f( 10, 10 );
	glVertex3d( m_Box1.x, m_Box2.y, m_Box1.z );
	glTexCoord2f( 0, 10 );
	glVertex3d( m_Box2.x, m_Box2.y, m_Box1.z );
	glTexCoord2f( 0, 0 );
	glVertex3d( m_Box2.x, m_Box1.y, m_Box1.z );
	glTexCoord2f( 10, 0 );
	glVertex3d( m_Box1.x, m_Box1.y, m_Box1.z );

	// Left
	glNormal3d( -1, 0, 0 );
	glTexCoord2f( 0, 0 );
	glVertex3d( m_Box1.x, m_Box1.y, m_Box1.z );
	glTexCoord2f( 1, 0 );
	glVertex3d( m_Box1.x, m_Box1.y, m_Box2.z );
	glTexCoord2f( 1, 10 );
	glVertex3d( m_Box1.x, m_Box2.y, m_Box2.z );
	glTexCoord2f( 0, 10 );
	glVertex3d( m_Box1.x, m_Box2.y, m_Box1.z );

	// right
	glNormal3d( 1, 0, 0 );
	glTexCoord2f( 0, 0 );
	glVertex3d( m_Box2.x, m_Box1.y, m_Box2.z );
	glTexCoord2f( 1, 0 );
	glVertex3d( m_Box2.x, m_Box1.y, m_Box1.z );
	glTexCoord2f( 1, 10 );
	glVertex3d( m_Box2.x, m_Box2.y, m_Box1.z );
	glTexCoord2f( 0, 10 );
	glVertex3d( m_Box2.x, m_Box2.y, m_Box2.z );
	
	// Front
	glNormal3d( 0, -1, 0 );
	glTexCoord2f( 0, 0 );
	glVertex3d( m_Box1.x, m_Box2.y, m_Box1.z );
	glTexCoord2f( 1, 0 );
	glVertex3d( m_Box1.x, m_Box2.y, m_Box2.z );
	glTexCoord2f( 1, 10 );
	glVertex3d( m_Box2.x, m_Box2.y, m_Box2.z );
	glTexCoord2f( 0, 10 );
	glVertex3d( m_Box2.x, m_Box2.y, m_Box1.z );

	// Back
	glNormal3d( 0, 1, 0 );
	glTexCoord2f( 0, 0 );
	glVertex3d( m_Box1.x, m_Box1.y, m_Box2.z );
	glTexCoord2f( 1, 0 );
	glVertex3d( m_Box1.x, m_Box1.y, m_Box1.z );
	glTexCoord2f( 1, 10 );
	glVertex3d( m_Box2.x, m_Box1.y, m_Box1.z );
	glTexCoord2f( 0, 10 );
	glVertex3d( m_Box2.x, m_Box1.y, m_Box2.z );

	glEnd();
}

// On n'efface pas le fond
//
BOOL CHeroscapeEditor3DView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

// When the window is created
//
int CHeroscapeEditor3DView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	Init(); // initialise OpenGL

	return 0;
}

// Initialise OpenGl
//
void CHeroscapeEditor3DView::Init()
{
	PIXELFORMATDESCRIPTOR pfd;
	int         n;

	m_pDC = new CClientDC(this);

	ASSERT(m_pDC != NULL);

	if (!bSetupPixelFormat())
		return;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	CreateRGBPalette();

	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	ASSERT(m_hRC);
	if(!::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC))
		return;

	GetClientRect(&m_oldRect);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.8f, 0.8f, 1.0f, 0.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glEnable( GL_COLOR_MATERIAL );

	CHeroscapeEditorDoc* pDoc = GetDocument();
	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		pTile->ResetTextureId();
	}

	UpdateData1();

	LoadTextures();
	LoadObjects();
	CreateList();

	UpdateData2();
	OnCameraGoHome();
}

void CHeroscapeEditor3DView::UpdateData1()
{
	// Set the battlefield area
	CHeroscapeEditorDoc* pDoc = GetDocument();
	pDoc->ComputeArea(false);
	pDoc->ComputeLevelMax();
	m_CenterOfBattleField.x = (pDoc->m_XOffset+pDoc->m_XWidth/2)*TILE3D_WIDTH;
	m_CenterOfBattleField.y = (pDoc->m_YOffset+pDoc->m_YHeight/2)*(-TILE3D_HEIGHT);
	m_CenterOfBattleField.z = pDoc->m_LevelMax*TILE3D_ZHEIGHT;
	double dist = 1000;
	double AngleVertical = 50;
	double AngleHorizontal = 30;
	m_LightPosition.x = (float) (m_CenterOfBattleField.x-cos(AngleVertical*PI/180)*cos(AngleHorizontal*PI/180)*dist);
	m_LightPosition.y = (float) (m_CenterOfBattleField.y+cos(AngleVertical*PI/180)*sin(AngleHorizontal*PI/180)*dist);
	m_LightPosition.z = (float) (m_CenterOfBattleField.z+sin(AngleVertical*PI/180)*dist);
	double Angle;
	//Angle = 1.3*max(asin( ((pDoc->m_XWidth+1)*TILE3D_WIDTH)/1000.0 )*180/PI,asin( ((pDoc->m_YHeight+1)*(TILE3D_HEIGHT))/1000.0 )*180/PI );
	Angle = 1.2*asin( sqrt(((pDoc->m_XWidth+1)*TILE3D_WIDTH)*((pDoc->m_XWidth+1)*TILE3D_WIDTH)+((pDoc->m_YHeight+1)*(TILE3D_HEIGHT))*((pDoc->m_YHeight+1)*(TILE3D_HEIGHT)))/1000.0 )*180/PI;

	m_Box1.x = (pDoc->m_XOffset-2)*TILE3D_WIDTH;
	m_Box1.y = (pDoc->m_YOffset-2)*(-TILE3D_HEIGHT);
	m_Box1.z = 0;

	m_Box2.x = (pDoc->m_XOffset+pDoc->m_XWidth+2)*TILE3D_WIDTH;
	m_Box2.y = (pDoc->m_YOffset+pDoc->m_YHeight+2)*(-TILE3D_HEIGHT);
	m_Box2.z = -3;

	//Calculate & save matrices
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();

	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_CameraProjectionMatrix);

	glLoadIdentity();
	gluLookAt(m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z, m_CenterOfBattleField.x, m_CenterOfBattleField.y, m_CenterOfBattleField.z, 0.0f, 0.0f, 1.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_CameraViewMatrix);

	glLoadIdentity();
	gluPerspective(Angle, 1.0f, 800.0f, 1200.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_LightProjectionMatrix);

	glLoadIdentity();
	gluLookAt( m_LightPosition.x, m_LightPosition.y, m_LightPosition.z, m_CenterOfBattleField.x, m_CenterOfBattleField.y, m_CenterOfBattleField.z, 0.0f, 0.0f, 1.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_LightViewMatrix);

	glPopMatrix();
}

void CHeroscapeEditor3DView::UpdateData2()
{
	if( m_DisplayShadow )
	{
		GetDocument()->LoadNecessaryObjects( this );
		if( !ComputeShadow() )
		{
			m_DisplayShadow = false;
			theApp.m_DisplayShadow = false;
		}
	}
}

// Compute shadow
//
bool CHeroscapeEditor3DView::ComputeShadow()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	CDC* pDC = GetDC();
	if( pDC )
		wglMakeCurrent( m_pDC->GetSafeHdc() ,m_hRC);

	if( !m_ComputeShadowIsInitialise )
	{
		if( pDoc->m_TileList.GetCount()==0 )
			return true;

		if( !theApp.m_GlExtensionAlreadyInit )
		{
			if(! glh_init_extensions(REQUIRED_EXTENSIONS) )
			{
				glh_shutdown_extensions();
				AfxMessageBox( IDS_OPENGLEXT_REQUIREMENT );
				return false;
			}
			theApp.m_GlExtensionAlreadyInit = true;
		}

		m_pBuffer = new PBuffer(NULL);

		GLenum depth_format;

		glEnable(GL_DEPTH_TEST);
		// init pbuffer
		m_pBuffer->Initialize( m_ShadowMapSize, m_ShadowMapSize, false, true);
		m_pBuffer->Activate();
		glEnable(GL_DEPTH_TEST);
		
		GLint depth_bits;
		glGetIntegerv(GL_DEPTH_BITS, &depth_bits);
        
		if(depth_bits == 16)
			depth_format = GL_DEPTH_COMPONENT16_ARB;
		else
			depth_format = GL_DEPTH_COMPONENT24_ARB;
		m_pBuffer->Deactivate();

		if( m_ShadowMapTexture==-1 )
			glGenTextures(1, &m_ShadowMapTexture);
		if( m_ShadowMapTexture==0 )
		{
			return false;
		}
		glBindTexture(GL_TEXTURE_2D, m_ShadowMapTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, depth_format, m_ShadowMapSize, m_ShadowMapSize, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

		m_ComputeShadowIsInitialise = true;
	}

	m_pBuffer->Activate();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor4f( 1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(m_LightProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(m_LightViewMatrix);

	//Draw back faces into the shadow map
	glCullFace(GL_FRONT);
	glDisable(GL_CULL_FACE);

	//use flat shading for speed
	glShadeModel(GL_FLAT);
	glDisable( GL_LIGHTING );
	//glColorMask(1, 1, 1, 1);

    glPolygonOffset(3,1);
    glEnable(GL_POLYGON_OFFSET_FILL);
	glDisable( GL_TEXTURE_2D );

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->m_PosZ<=m_LastLevelToDisplay )
			pTile->Render( this, true );
	}
	//RenderBox( false );

	RenderMoveArrow( true );

    glDisable(GL_POLYGON_OFFSET_FILL);

	glBindTexture(GL_TEXTURE_2D, m_ShadowMapTexture);

	//glFlush();
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0,   0, 0,   0, 0,  m_ShadowMapSize, m_ShadowMapSize);
	m_pBuffer->Deactivate();

	ReleaseDC( pDC );

	return true;
}

void CHeroscapeEditor3DView::DisplayError()
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		0, // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.
	MessageBox( (LPCTSTR)lpMsgBuf, _T("Error"), MB_OK | MB_ICONINFORMATION );
	// Free the buffer.
	LocalFree( lpMsgBuf );
}

// positionne le Pixel Format
//
BOOL CHeroscapeEditor3DView::bSetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
		1,                              // version number
		PFD_DRAW_TO_WINDOW |            // support window
		  PFD_SUPPORT_OPENGL |          // support OpenGL
		  PFD_DOUBLEBUFFER,             // double buffered
		PFD_TYPE_RGBA,                  // RGBA type
		32,                             // 24-bit color depth
		0, 0, 0, 0, 0, 0,               // color bits ignored
		0,                              // no alpha buffer
		0,                              // shift bit ignored
		0,                              // no accumulation buffer
		0, 0, 0, 0,                     // accum bits ignored
		32,                             // 32-bit z-buffer
		0,                              // no stencil buffer
		0,                              // no auxiliary buffer
		PFD_MAIN_PLANE,                 // main layer
		0,                              // reserved
		0, 0, 0                         // layer masks ignored
	};
	int pixelformat;

	if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0 )
	{
		MessageBox( _T("ChoosePixelFormat failed") );
		return FALSE;
	}

	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox( _T("SetPixelFormat failed") );
		return FALSE;
	}

	return TRUE;
}

// Creer la palette
//
void CHeroscapeEditor3DView::CreateRGBPalette()
{
	PIXELFORMATDESCRIPTOR pfd;
	LOGPALETTE *pPal;
	int n, i;

	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	if (pfd.dwFlags & PFD_NEED_PALETTE)
	{
		n = 1 << pfd.cColorBits;
		pPal = (PLOGPALETTE) new char[sizeof(LOGPALETTE) + n * sizeof(PALETTEENTRY)];

		ASSERT(pPal != NULL);

		pPal->palVersion = 0x300;
		pPal->palNumEntries = n;
		for (i=0; i<n; i++)
		{
			pPal->palPalEntry[i].peRed = ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
			pPal->palPalEntry[i].peGreen = ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
			pPal->palPalEntry[i].peBlue = ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
			pPal->palPalEntry[i].peFlags = 0;
		}

		/* fix up the palette to include the default GDI palette */
		if ((pfd.cColorBits == 8)                           &&
			(pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
			(pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
			(pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6)
		   )
		{
			for (i = 1 ; i <= 12 ; i++)
				pPal->palPalEntry[defaultOverride[i]] = defaultPalEntry[i];
		}

		m_cPalette.CreatePalette(pPal);
		delete pPal;

		m_pOldPalette = m_pDC->SelectPalette(&m_cPalette, FALSE);
		m_pDC->RealizePalette();
	}
}

// Utilise pour la creation du pixel descriptor/palette
//
unsigned char CHeroscapeEditor3DView::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
	unsigned char val;

	val = (unsigned char) (i >> shift);
	switch (nbits)
	{

	case 1:
		val &= 0x1;
		return oneto8[val];
	case 2:
		val &= 0x3;
		return twoto8[val];
	case 3:
		val &= 0x7;
		return threeto8[val];

	default:
		return 0;
	}
}

// When the window is destroy
//
void CHeroscapeEditor3DView::OnDestroy() 
{
	HGLRC   hrc;

	hrc = ::wglGetCurrentContext();

	::wglMakeCurrent(NULL,  NULL);

	if (hrc)
		::wglDeleteContext(hrc);

	if (m_pOldPalette)
		m_pDC->SelectPalette(m_pOldPalette, FALSE);

	if (m_pDC)
		delete m_pDC;

	// Free memory about personal texture
	for( int i=0; i<m_PersonalTextureList.GetCount(); i++ )
	{
		CPersonalTexture* pPersonalTexture = (CPersonalTexture*) m_PersonalTextureList.GetAt(i);
		delete pPersonalTexture;
	}
	m_PersonalTextureList.RemoveAll();

	// Free memory about figure
	for( int i=0; i<m_FigureObjectList.GetCount(); i++ )
	{
		CFigureObject* pFigureObject = (CFigureObject*) m_FigureObjectList.GetAt(i);
		delete pFigureObject->m_pObject;
		delete pFigureObject;
	}
	m_FigureObjectList.RemoveAll();

	// Call the base class
	CView::OnDestroy();
}

// The window size change
//
void CHeroscapeEditor3DView::OnSize(UINT nType, int cx, int cy) 
{
	// Call the base class
	CView::OnSize(nType, cx, cy);
	
    if(!cy)
		return; 

	wglMakeCurrent( m_pDC->GetSafeHdc(), m_hRC );

    glViewport(0, 0, cx, cy);

	m_i_Width = cx;
	m_i_Heigth = cy;

	// Save the information inside a array because we can use it to render on print preview
	FreeViewPoint();
	// Alloc pixel bytes 
	int WidthAlignement = (m_i_Width*3+3)-((m_i_Width*3+3)%4);
	int NbBytes = WidthAlignement * m_i_Heigth; 
	m_pViewPoint = (unsigned char*) malloc(NbBytes); 

	m_IsModified = true;
	RedrawWindow();

	CString Str;
	Str.Format( _T("%ix%i"), cx, cy );
	((CMainFrame*) theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText( 0, Str );
}

// Compute and set the view matrix
//
void CHeroscapeEditor3DView::ViewMatrix()
{
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
	GLint IsSelectMode;
	glGetIntegerv(GL_RENDER_MODE,&IsSelectMode);
	if( IsSelectMode==GL_SELECT )
	{
		GLint view[4];

		glGetIntegerv(GL_VIEWPORT, view);

 		gluPickMatrix( m_CurrentMousePosition.x, view[3]-m_CurrentMousePosition.y, 1.0, 1.0, view);
	}
	if( m_CameraForTopography )
	{
		CHeroscapeEditorDoc* pDoc = GetDocument();

		double width = fabs(pDoc->m_XWidth*1.2);
		double height = fabs(pDoc->m_YHeight*1.2);
		if( width/m_i_Width>height/m_i_Heigth )
			glOrtho( -pDoc->m_XWidth*1.1, pDoc->m_XWidth*1.1, -pDoc->m_XWidth*1.1*m_i_Heigth/m_i_Width, pDoc->m_XWidth*1.1*m_i_Heigth/m_i_Width, 0, 1000 );
		else
			glOrtho( -pDoc->m_YHeight*1.1*m_i_Width/m_i_Heigth, pDoc->m_YHeight*1.1*m_i_Width/m_i_Heigth, -pDoc->m_YHeight*1.1, pDoc->m_YHeight*1.1, 0, 1000 );
		glGetFloatv(GL_PROJECTION_MATRIX, m_CameraProjectionMatrix);

		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity();
		gluLookAt( (pDoc->m_XOffset+pDoc->m_XWidth/2.0)*TILE3D_WIDTH, (-pDoc->m_YOffset-pDoc->m_YHeight/2.0)*TILE3D_HEIGHT, 900, (pDoc->m_XOffset+pDoc->m_XWidth/2.0)*TILE3D_WIDTH, (-pDoc->m_YOffset-pDoc->m_YHeight/2.0)*TILE3D_HEIGHT, 0, 0, 1, 0 );
	}
	else if( m_StereoscopicView )
	{
		gluPerspective( 40.0, (GLfloat) m_i_Width / (GLfloat) m_i_Heigth, 1, 500 ); 
		glGetFloatv(GL_PROJECTION_MATRIX, m_CameraProjectionMatrix);

		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity();
		m_CameraLookAt.x = m_CameraPosition.x+m_CameraStereoFocusDistance*((0*cos(m_CameraAngleH/180.0*PI)+1*sin(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI));
		m_CameraLookAt.y = m_CameraPosition.y+m_CameraStereoFocusDistance*((0*sin(m_CameraAngleH/180.0*PI)+1*cos(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI));
		m_CameraLookAt.z = m_CameraPosition.z+m_CameraStereoFocusDistance*(1*sin(m_CameraAngleV/180.0*PI));
		if( m_CameraStereoIsLeft )
			gluLookAt( m_CameraPosition.x+1*cos(m_CameraAngleH/180.0*PI), m_CameraPosition.y-1*sin(m_CameraAngleH/180.0*PI), m_CameraPosition.z, m_CameraLookAt.x, m_CameraLookAt.y, m_CameraLookAt.z, 0, 0, 1 );
		else
			gluLookAt( m_CameraPosition.x-1*cos(m_CameraAngleH/180.0*PI), m_CameraPosition.y+1*sin(m_CameraAngleH/180.0*PI), m_CameraPosition.z, m_CameraLookAt.x, m_CameraLookAt.y, m_CameraLookAt.z, 0, 0, 1 );
	}
	else
	{
		gluPerspective( 40.0, (GLfloat) m_i_Width / (GLfloat) m_i_Heigth, 1, 500 ); 
		glGetFloatv(GL_PROJECTION_MATRIX, m_CameraProjectionMatrix);

		if( IsSelectMode!=GL_SELECT )
		{
			glMatrixMode(GL_MODELVIEW); 
			glLoadIdentity();
		}
		if( m_Mode!=MODE3D_FREE_ANIMATION && m_Mode!=MODE3D_CREATE_ANIMATION && m_Mode!=MODE3D_FIGURE_PLACED_ANIMATION && m_Mode!=MODE3D_FIGURE_REMOVED_ANIMATION && m_Mode!=MODE3D_FIGURE_MOVED_ANIMATION && m_Mode!=MODE3D_ATTACK_ANIMATION && m_Mode!=MODE3D_DEFENSE_ANIMATION && m_IsReplayMode==false)
		{
			m_CameraLookAt.x = m_CameraPosition.x+20*((0*cos(m_CameraAngleH/180.0*PI)+1*sin(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI));
			m_CameraLookAt.y = m_CameraPosition.y+20*((0*sin(m_CameraAngleH/180.0*PI)+1*cos(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI));
			m_CameraLookAt.z = m_CameraPosition.z+20*(1*sin(m_CameraAngleV/180.0*PI));
		}
		gluLookAt( m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z, m_CameraLookAt.x, m_CameraLookAt.y, m_CameraLookAt.z, 0, 0, 1 );
	}
	glGetFloatv(GL_MODELVIEW_MATRIX, m_CameraViewMatrix);
}

// Compute and set the view matrix for right stereo eye
//
void CHeroscapeEditor3DView::ViewMatrixStereoRight()
{
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
	if( m_CameraForTopography )
	{
		CHeroscapeEditorDoc* pDoc = GetDocument();

		double width = fabs(pDoc->m_XWidth*1.2);
		double height = fabs(pDoc->m_YHeight*1.2);
		if( width/m_i_Width>height/m_i_Heigth )
			glOrtho( -pDoc->m_XWidth*1.1, pDoc->m_XWidth*1.1, -pDoc->m_XWidth*1.1*m_i_Heigth/m_i_Width, pDoc->m_XWidth*1.1*m_i_Heigth/m_i_Width, 0, 1000 );
		else
			glOrtho( -pDoc->m_YHeight*1.1*m_i_Width/m_i_Heigth, pDoc->m_YHeight*1.1*m_i_Width/m_i_Heigth, -pDoc->m_YHeight*1.1, pDoc->m_YHeight*1.1, 0, 1000 );
		glGetFloatv(GL_PROJECTION_MATRIX, m_CameraProjectionMatrix);

		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity();
		gluLookAt( (pDoc->m_XOffset+pDoc->m_XWidth/2.0)*TILE3D_WIDTH, (-pDoc->m_YOffset-pDoc->m_YHeight/2.0)*TILE3D_HEIGHT, 900, (pDoc->m_XOffset+pDoc->m_XWidth/2.0)*TILE3D_WIDTH, (-pDoc->m_YOffset-pDoc->m_YHeight/2.0)*TILE3D_HEIGHT, 0, 0, 1, 0 );
	}

		gluPerspective( 40.0, (GLfloat) m_i_Width / (GLfloat) m_i_Heigth, 1, 500 ); 
		glGetFloatv(GL_PROJECTION_MATRIX, m_CameraProjectionMatrix);

		glMatrixMode(GL_MODELVIEW); 
		glLoadIdentity();
		m_CameraLookAt.x = m_CameraPosition.x+m_CameraStereoFocusDistance*((0*cos(m_CameraAngleH/180.0*PI)+1*sin(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI));
		m_CameraLookAt.y = m_CameraPosition.y+m_CameraStereoFocusDistance*((0*sin(m_CameraAngleH/180.0*PI)+1*cos(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI));
		m_CameraLookAt.z = m_CameraPosition.z+m_CameraStereoFocusDistance*(1*sin(m_CameraAngleV/180.0*PI));

		gluLookAt( m_CameraPosition.x-1*cos(m_CameraAngleH/180.0*PI), m_CameraPosition.y+1*sin(m_CameraAngleH/180.0*PI), m_CameraPosition.z, m_CameraLookAt.x, m_CameraLookAt.y, m_CameraLookAt.z, 0, 0, 1 );

		glGetFloatv(GL_MODELVIEW_MATRIX, m_CameraViewMatrix);
}

// The lightening
//
void CHeroscapeEditor3DView::Lightening()
{
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0 };
	GLfloat light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0 };
	GLfloat light_specular[] = { 1, 1, 0.0, 1.0 };
	glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular );

	GLfloat light_position[] = { -50, 0, 100, 1.0 };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
	GLfloat light_shininess[] = { 127.0f };
	glMaterialfv( GL_FRONT_AND_BACK, GL_SHININESS, light_shininess );
	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, light_specular );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, light_ambient );
	glColor3f( 0,0,0 );
}

// Load all the texture useful for the 3D View
//
void CHeroscapeEditor3DView::LoadTextures()
{
	CString TextureType;
	switch( theApp.m_TextureType )
	{
	case 0:
		TextureType = _T("Normal");
		break;
	case 1:
		TextureType = _T("Srmalloy");
		break;
	}

	m_TextureIdGroundSide = CStaticGraphicalLib::LoadTexture( theApp.m_CurrentDir+_T("\\Images\\")+TextureType+_T("\\GroundSide.bmp"), 255 );
	m_TextureIdBox = CStaticGraphicalLib::LoadTexture( theApp.m_CurrentDir+_T("\\Images\\")+TextureType+_T("\\Box.bmp"), 255 );
	m_TextureIdAttack = CStaticGraphicalLib::LoadTexture( theApp.m_CurrentDir+_T("\\Misc\\Attack.bmp"), 255 );
	m_TextureIdDefense = CStaticGraphicalLib::LoadTexture( theApp.m_CurrentDir+_T("\\Misc\\Defense.bmp"), 255 );
}

// Load all the 3d objects
//
void CHeroscapeEditor3DView::LoadObjects()
{
	m_pTree10 = new CObject3D;
	m_pTree10->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Arbre1_10\\Arbre1_10.sgl") );
	m_pTree10->CreateList();
	m_pTree11 = new CObject3D;
	m_pTree11->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Arbre1_11\\Arbre1_11.sgl") );
	m_pTree11->CreateList();
	m_pTree12 = new CObject3D;
	m_pTree12->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Arbre1_12\\Arbre1_12.sgl") );
	m_pTree12->CreateList();
	m_pTree15 = new CObject3D;
	m_pTree15->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Arbre4_15\\Arbre4_15.sgl") );
	m_pTree15->CreateList();
	m_pRuin2 = new CObject3D;
	m_pRuin2->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Ruine2\\Ruine2.sgl") );
	m_pRuin2->CreateList();
	m_pRuin3 = new CObject3D;
	m_pRuin3->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Ruine3\\Ruine3.sgl") );
	m_pRuin3->CreateList();
	m_pGlacier1 = new CObject3D;
	m_pGlacier1->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Glacier1\\Glacier1.sgl") );
	m_pGlacier1->CreateList();
	m_pGlacier3 = new CObject3D;
	m_pGlacier3->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Glacier3\\Glacier3.sgl") );
	m_pGlacier3->CreateList();
	m_pGlacier4 = new CObject3D;
	m_pGlacier4->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Glacier4\\Glacier4.sgl") );
	m_pGlacier4->CreateList();
	m_pGlacier6 = new CObject3D;
	m_pGlacier6->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Glacier6\\Glacier6.sgl") );
	m_pGlacier6->CreateList();
	m_pHive6 = new CObject3D;
	m_pHive6->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Hive6\\Hive6.sgl") );
	m_pHive6->CreateList();
	m_pWall4 = new CObject3D;
	m_pWall4->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Mur4\\Mur4.sgl") );
	m_pWall4->CreateList();
	m_pCastleBaseEnd = new CObject3D;
	m_pCastleBaseEnd->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauBaseFin\\ChateauBaseFin.sgl") );
	m_pCastleBaseEnd->CreateList();
	m_pCastleBaseStraight = new CObject3D;
	m_pCastleBaseStraight->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauBaseDroit\\ChateauBaseDroit.sgl") );
	m_pCastleBaseStraight->CreateList();
	m_pCastleBaseCorner = new CObject3D;
	m_pCastleBaseCorner->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauBaseAngle\\ChateauBaseAngle.sgl") );
	m_pCastleBaseCorner->CreateList();
	m_pCastleWallCorner = new CObject3D;
	m_pCastleWallCorner->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauMurAngle\\ChateauMurAngle.sgl") );
	m_pCastleWallCorner->CreateList();
	m_pCastleWallStraight = new CObject3D;
	m_pCastleWallStraight->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauMurDroit\\ChateauMurDroit.sgl") );
	m_pCastleWallStraight->CreateList();
	m_pCastleWallEnd = new CObject3D;
	m_pCastleWallEnd->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauMurFin\\ChateauMurFin.sgl") );
	m_pCastleWallEnd->CreateList();
	m_pCastleBattlement = new CObject3D;
	m_pCastleBattlement->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauMeurtriere\\ChateauMeurtriere.sgl") );
	m_pCastleBattlement->CreateList();
	m_pCastleDoor = new CObject3D;
	m_pCastleDoor->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauPorte\\ChateauPorte.sgl") );
	m_pCastleDoor->CreateList();
	m_pCastleArch = new CObject3D;
	m_pCastleArch->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauArche\\ChateauArche.sgl") );
	m_pCastleArch->CreateList();
	m_pCastleLadder = new CObject3D;
	m_pCastleLadder->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauEchelle\\ChateauEchelle.sgl") );
	m_pCastleLadder->CreateList();
	m_pCastleFlag = new CObject3D;
	m_pCastleFlag->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\ChateauDrapeau\\ChateauDrapeau.sgl") );
	m_pCastleFlag->CreateList();
	m_pMarvelRuin6 = new CObject3D;
	m_pMarvelRuin6->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\MarvelRuine6\\MarvelRuine6.sgl") );
	m_pMarvelRuin6->CreateList();
	m_pMarvelRuin6Breaked = new CObject3D;
	m_pMarvelRuin6Breaked->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\MarvelRuine6Breaked\\MarvelRuine6Breaked.sgl") );
	m_pMarvelRuin6Breaked->CreateList();
	m_pPalm1 = new CObject3D;
	m_pPalm1->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Palmier\\Palmier.sgl") );
	m_pPalm1->CreateList();
	m_pTicallaGrass1 = new CObject3D;
	m_pTicallaGrass1->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\TicallaGrass\\TicallaGrass.sgl") );
	m_pTicallaGrass1->CreateList();
	m_pOutcrop1 = new CObject3D;
	m_pOutcrop1->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Outcrop1\\Outcrop1.sgl") );
	m_pOutcrop1->CreateList();
	m_pOutcrop3 = new CObject3D;
	m_pOutcrop3->LoadSgl( theApp.m_CurrentDir+_T("\\Objets 3D\\Outcrop3\\Outcrop3.sgl") );
	m_pOutcrop3->CreateList();
}

// Verify if we move the view with key
//
bool CHeroscapeEditor3DView::VerifyKey( __int64 TimeDif )
{
	bool Move = false;

	double CoefDep = 0.1/20;

	if( TimeDif>5000 )
		TimeDif = 5000;
	if( TimeDif==0 ) 
		TimeDif = 1;

	if( m_Mode==MODE3D_TURN_AROUND )
		return false;

	if( GetAsyncKeyState(VK_UP)&0x8000 )
	{
		// Forward
		MyPoint3D Deplacement;
		Deplacement.x = (m_CameraLookAt.x-m_CameraPosition.x)*TimeDif*CoefDep/5.0;
		Deplacement.y = (m_CameraLookAt.y-m_CameraPosition.y)*TimeDif*CoefDep/5.0;
		if( GetAsyncKeyState(VK_SHIFT)&0x8000 )
			Deplacement.z = 0;
		else
			Deplacement.z = (m_CameraLookAt.z-m_CameraPosition.z)/5.0*TimeDif*CoefDep;

		m_CameraPosition.x += Deplacement.x;
		m_CameraPosition.y += Deplacement.y;
		m_CameraPosition.z += Deplacement.z;
		Move = true;
	}
	else if( GetAsyncKeyState(VK_DOWN)&0x8000 )
	{
		// Backward
		MyPoint3D Deplacement;
		Deplacement.x = -(m_CameraLookAt.x-m_CameraPosition.x)/5.0*TimeDif*CoefDep;
		Deplacement.y = -(m_CameraLookAt.y-m_CameraPosition.y)/5.0*TimeDif*CoefDep;
		if( GetAsyncKeyState(VK_SHIFT)&0x8000 )
			Deplacement.z = 0;
		else
			Deplacement.z = -(m_CameraLookAt.z-m_CameraPosition.z)/5.0*TimeDif*CoefDep;

		m_CameraPosition.x += Deplacement.x;
		m_CameraPosition.y += Deplacement.y;
		m_CameraPosition.z += Deplacement.z;
		Move = true;
	}
	if( GetAsyncKeyState(VK_LEFT)&0x8000 )
	{
		// To the left
		MyPoint3D Deplacement;
		Deplacement.x = (-1*cos(m_CameraAngleH/180.0*PI)+0*sin(m_CameraAngleH/180.0*PI))/5.0*TimeDif*CoefDep*20;
		Deplacement.y = (1*sin(m_CameraAngleH/180.0*PI)+0*cos(m_CameraAngleH/180.0*PI))/5.0*TimeDif*CoefDep*20;
		Deplacement.z = 0;

		m_CameraPosition.x += Deplacement.x;
		m_CameraPosition.y += Deplacement.y;
		m_CameraPosition.z += Deplacement.z;
		Move = true;
	}
	if( GetAsyncKeyState(VK_RIGHT)&0x8000 )
	{
		// To the right
		MyPoint3D Deplacement;
		Deplacement.x = (1*cos(m_CameraAngleH/180.0*PI)+0*sin(m_CameraAngleH/180.0*PI))/5.0*TimeDif*CoefDep*20;
		Deplacement.y = (-1*sin(m_CameraAngleH/180.0*PI)+0*cos(m_CameraAngleH/180.0*PI))/5.0*TimeDif*CoefDep*20;
		Deplacement.z = 0;

		m_CameraPosition.x += Deplacement.x;
		m_CameraPosition.y += Deplacement.y;
		m_CameraPosition.z += Deplacement.z;
		Move = true;
	}
	if( GetAsyncKeyState(VK_PRIOR)&0x8000 )
	{
		// Up
		double DeplacementZ = 0.1*TimeDif*CoefDep*20;

		m_CameraPosition.z += DeplacementZ;
		Move = true;
	}
	if( GetAsyncKeyState(VK_NEXT)&0x8000 )
	{
		// Down
		double DeplacementZ = -0.1*TimeDif*CoefDep*20;

		m_CameraPosition.z += DeplacementZ;
		Move = true;
	}

	POINT Point;
	GetCursorPos( &Point );
	ScreenToClient( &Point );

	// If the left button was pressed
	if( (GetAsyncKeyState(VK_LBUTTON)&0x8000)!=0 )
	{
		if( theApp.m_MoveSolidscape )
		{
			CRect Rect;
			GetClientRect( &Rect );
			if( Point.x>=0 && Point.x<=Rect.Width() && Point.y>=0 && Point.y<=Rect.Height() )
			{
				if( m_OldMousePosition.x>=0 && m_OldMousePosition.x<=Rect.Width() && m_OldMousePosition.y>=0 && m_OldMousePosition.y<=Rect.Height() )
				{
					if( Point.x!=m_OldMousePosition.x || Point.y!=m_OldMousePosition.y )
					{
						Move = true;
						m_CameraAngleH -= (m_OldMousePosition.x-Point.x)/6.0;
						m_CameraAngleV += (m_OldMousePosition.y-Point.y)/6.0;
						if( m_CameraAngleV>89 )
							m_CameraAngleV = 89;
						if( m_CameraAngleV<-89 )
							m_CameraAngleV = -89;
						
						CPoint point2=m_OldMousePosition;
						ClientToScreen( &point2 );
						SetCursorPos( point2.x, point2.y );
					}
				}
			}
		}
		else
		{
			CRect Rect;
			GetClientRect( &Rect );
			if( Point.x>=0 && Point.x<=Rect.Width() && Point.y>=0 && Point.y<=Rect.Height() )
			{
				if( m_OldMousePosition.x>=0 && m_OldMousePosition.x<=Rect.Width() && m_OldMousePosition.y>=0 && m_OldMousePosition.y<=Rect.Height() )
				{
					if( Point.x!=m_OldMousePosition.x || Point.y!=m_OldMousePosition.y )
					{
						Move = true;
						m_CameraAngleH -= (m_OldMousePosition.x-Point.x)/6.0;
						m_CameraAngleV += (m_OldMousePosition.y-Point.y)/6.0;
						if( m_CameraAngleV>89 )
							m_CameraAngleV = 89;
						if( m_CameraAngleV<-89 )
							m_CameraAngleV = -89;
						
						CPoint point2=m_OldMousePosition;
						ClientToScreen( &point2 );
						SetCursorPos( point2.x, point2.y );
					}
				}
			}
		}
	}
	else
		m_OldMousePosition = Point;

	if( m_CameraPosition.z<0 )
		m_CameraPosition.z=0;

	if( Move )
	{
		m_IsModified = true;
		RedrawWindow();
		// Get z
		//GLfloat Depth;
		//glReadPixels(m_i_Width/2, m_i_Heigth/2,1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &Depth );
		//TRACE("Intersection : %f\n", Depth );
	}

	return Move;
}

// When I receive a timer
//
void CHeroscapeEditor3DView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);

	if( m_IsReplayMode )
	{
		KillTimer( 1 );
		theApp.m_pGameDoc->m_ToServerSocket.NextReplay();
		SetTimer( 1, 10, NULL );
	}
	else
	{
		if( GetActiveWindow()==theApp.m_pMainWnd )
		{
			if( ((CMDIFrameWnd*) theApp.m_pMainWnd)->GetActiveFrame()==GetParentFrame() )
			{
				KillTimer( 1 );

				// Read the current time
				LARGE_INTEGER	CurrentTimer;
				QueryPerformanceCounter( &CurrentTimer );

				__int64 TimeDif;
				TimeDif = (__int64) (((CurrentTimer.QuadPart - m_LastKeyTime) / (double) m_frequency ) * 1000);
				m_LastKeyTime = CurrentTimer.QuadPart;

				while( VerifyKey( TimeDif ) )
				{
					ComputeMoveAuto();
					QueryPerformanceCounter( &CurrentTimer );
					TimeDif = (__int64) (((CurrentTimer.QuadPart - m_LastKeyTime) / (double) m_frequency ) * 1000);
					m_LastKeyTime = CurrentTimer.QuadPart;
				}

				SetTimer( 1, 10, NULL );
			}
		}

		// Read the current time
		LARGE_INTEGER	CurrentTimer;
		QueryPerformanceCounter( &CurrentTimer );

		m_LastKeyTime = CurrentTimer.QuadPart;

		if( ComputeMoveAuto() )
		{
			m_IsModified = true;
			RedrawWindow();
		}
	}
}

// When the mouse move
//
void CHeroscapeEditor3DView::OnMouseMove(UINT nFlags, CPoint point)
{
	m_CurrentMousePosition = point;

	if( m_IsMove )
	{
		m_MouseMoveUntilLButtonDown = true;
		// If the left button was not pressed
		if( (nFlags & MK_LBUTTON)==0 )
			m_OldMousePosition = point;
	}

	// If right button is pressed
	if( (nFlags & MK_RBUTTON)!=0 )
	{
		GLfloat	FieldDistance;
		GLfloat DepthRange[2];
		glReadPixels( point.x, m_i_Heigth-point.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &FieldDistance );
		glGetFloatv( GL_DEPTH_RANGE, DepthRange );
		//TRACE( _T("Profondeur : %f\n"), FieldDistance );
	}

	// If mode is select position
	if( m_Mode==MODE3D_SELECT_POSITION && ( (nFlags & MK_LBUTTON)==0 ) )
	{
		wglMakeCurrent( m_pDC->GetSafeHdc() ,m_hRC);

		GLuint SelectBuffer[200];

		glSelectBuffer(200,SelectBuffer);
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(999999999);

		RenderScene();
		GLint Hits = glRenderMode(GL_RENDER);
		if( Hits>0 )
		{
			GLuint MinZ = UINT_MAX;
			GLuint Position = 999999999;
			for( int i=0; i<Hits; i++ )
			{
				if( SelectBuffer[i*4+1]<MinZ && SelectBuffer[i*4+3]!=999999999 )
				{
					MinZ = SelectBuffer[i*4+1];
					Position = SelectBuffer[i*4+3];
				}
			}
			if( MinZ==UINT_MAX )
			{
				if( m_DisplayPositionX==-1 )
					return;
				else
				{
					m_DisplayPositionX = -1;
					m_IsModified = true;
					RedrawWindow();
				}
			}
			int PositionX = Position/1000000;
			int PositionY = (Position-PositionX*1000000)/1000;
			int PositionZ = Position%1000;

			if( PositionX<999 )
			{
				if( PositionX!=m_DisplayPositionX || PositionY!=m_DisplayPositionY || PositionZ!=m_DisplayPositionZ )
				{
					m_DisplayPositionX = PositionX;
					m_DisplayPositionY = PositionY;
					m_DisplayPositionZ = PositionZ;
					m_IsModified = true;
					RedrawWindow();
				}
			}
			else
				m_DisplayPositionX = -1;
		}
	}
	// If mode is select figure
	else if( m_Mode==MODE3D_SELECT_FIGURE && ( (nFlags & MK_LBUTTON)==0 ) )
	{
		wglMakeCurrent( m_pDC->GetSafeHdc() ,m_hRC);

		GLuint SelectBuffer[200];

		glSelectBuffer(200,SelectBuffer);
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(999999999);

		RenderScene();
		GLint Hits = glRenderMode(GL_RENDER);
		if( Hits>0 )
		{
			GLuint MinZ = UINT_MAX;
			GLuint Position = 0;
			for( int i=0; i<Hits; i++ )
			{
				if( SelectBuffer[i*4+1]<MinZ && SelectBuffer[i*4+3]!=999999999 )
				{
					MinZ = SelectBuffer[i*4+1];
					Position = SelectBuffer[i*4+3];
				}
			}
			if( MinZ==UINT_MAX )
			{
				if( m_pSelectedFigure!=NULL )
				{
					m_pSelectedFigure->m_pTileFigure->SetSelectedState( false );
					m_IsModified = true;
					RedrawWindow();
					m_pSelectedFigure = NULL;
				}
				return;
			}

			int PositionX = Position/1000000;
			int PositionY = (Position-PositionX*1000000)/1000;
			int PositionZ = Position%1000;

			// now search the figure at this place
			CGameDoc* pDoc = (CGameDoc*) GetDocument();
			CFigureObject* NewSelectedFigure = pDoc->GetFigureAtPos( PositionX, PositionY, PositionZ );
			if( NewSelectedFigure!=m_pSelectedFigure )
			{
				if( m_pSelectedFigure!=NULL )
					m_pSelectedFigure->m_pTileFigure->SetSelectedState( false );
				m_pSelectedFigure = NewSelectedFigure;
				if( m_pSelectedFigure!=NULL )
					m_pSelectedFigure->m_pTileFigure->SetSelectedState( true );
				m_IsModified = true;
				RedrawWindow();
			}
		}
		else
			m_pSelectedFigure = NULL;
	}

	// Call the base class
	CView::OnMouseMove(nFlags, point);
}

// When the left button is down
//
void CHeroscapeEditor3DView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetCapture();
	::SetCursor(NULL);
	m_OldMousePosition = point;
	m_IsMove = true;
	m_MouseMoveUntilLButtonDown = false;
	// Call the base class
	CView::OnLButtonDown(nFlags, point);
}

// Prepare the printing job
//
BOOL CHeroscapeEditor3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	if( !GetDocument()->OnPreparePrinting( pInfo ) )
		return FALSE;

	// préparation par défaut
	return DoPreparePrinting(pInfo);
}

// Begin printing job
//
void CHeroscapeEditor3DView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	GetDocument()->OnBeginPrinting( pDC, pInfo );
}

// End printing job
//
void CHeroscapeEditor3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO : ajoutez un nettoyage après l'impression
}

// Print the document
//
void CHeroscapeEditor3DView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	GetDocument()->OnPrint( pDC, pInfo );

	// Don't call the base class
	//CView::OnPrint(pDC, pInfo);
}

// Change the display shadow state
//
void CHeroscapeEditor3DView::OnToolbar3dDisplayshadow()
{
	m_DisplayShadow = !m_DisplayShadow;
	theApp.m_DisplayShadow = m_DisplayShadow;

	UpdateData2();
	m_IsModified = true;
	RedrawWindow();
}

// To know the display shadow state
//
void CHeroscapeEditor3DView::OnUpdateToolbar3dDisplayshadow(CCmdUI *pCmdUI)
{
	if( m_DisplayShadow )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// The user release the button
//
void CHeroscapeEditor3DView::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	m_IsMove = false;

	// Call the base class
	CView::OnLButtonUp(nFlags, point);
}

// Compute a high quality view
//
void CHeroscapeEditor3DView::OnOutilsVuehautequalite()
{
	int		Quality = theApp.m_PhotoQuality;
	int		NumberPass = 0;
	bool	BreakUser=false;

	CWaitCursor cwc;

	double CoefLuminosity = 1+theApp.m_Luminosity/100.0;

	if( !m_DisplayShadow )
	{
		AfxMessageBox( IDS_MUST_ACTIVATE_SHADOW_FOR_HIGH_QUALITY );
		return;
	}

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	GLint Viewport[4];
	glGetIntegerv( GL_VIEWPORT, Viewport );

	// Memory Array
	long* pPointsR = (long*) malloc(Viewport[2]*Viewport[3]*4); 
	long* pPointsG = (long*) malloc(Viewport[2]*Viewport[3]*4); 
	long* pPointsB = (long*) malloc(Viewport[2]*Viewport[3]*4); 

	memset( pPointsR, 0, Viewport[2]*Viewport[3]*4 );
	memset( pPointsG, 0, Viewport[2]*Viewport[3]*4 );
	memset( pPointsB, 0, Viewport[2]*Viewport[3]*4 );

	// Compute number of pass
	for( double AngleVertical=5; AngleVertical<90; AngleVertical+=(90.0/Quality) )
		for( double AngleHorizontal=0; AngleHorizontal<360; AngleHorizontal+=(360.0/Quality/cos(AngleVertical*PI/180)) )
			NumberPass++;
	NumberPass++;

	if( theApp.m_IsDepthField )
		NumberPass *= theApp.m_DepthField_Quality*theApp.m_DepthField_Quality;

	// Create progress dlg
	CProgressCtrl pCtrl;
	CRect Rect;
	((CMainFrame*) theApp.m_pMainWnd)->m_wndStatusBar.GetItemRect( 1, &Rect );
	pCtrl.Create( 0, Rect, &(((CMainFrame*) theApp.m_pMainWnd)->m_wndStatusBar), 2345 );
	pCtrl.SetRange(0,NumberPass);
	pCtrl.ShowWindow( SW_SHOW );

	CDC* pDC = GetDC();
	CHeroscapeEditorDoc* pDoc = GetDocument();

	int DepthFieldQuality = theApp.m_DepthField_Quality;
	if( !theApp.m_IsDepthField )
		DepthFieldQuality=1;

	int NbProgress = 0;
	int	NbPassGlobal = 0;
	// Memory of old camera position
	double OldCameraAngleV = m_CameraAngleV;
	double OldCameraAngleH = m_CameraAngleH;
	MyPoint3D OldCameraPosition = m_CameraPosition;
	// Compute View Point
	MyPoint3D ViewPoint;
	ViewPoint.x = m_CameraPosition.x+(0*cos(m_CameraAngleH/180.0*PI)+1*sin(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI)*theApp.m_DepthField_Distance;
	ViewPoint.y = m_CameraPosition.y+(0*sin(m_CameraAngleH/180.0*PI)+1*cos(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI)*theApp.m_DepthField_Distance;
	ViewPoint.z = m_CameraPosition.z+1*sin(m_CameraAngleV/180.0*PI)*theApp.m_DepthField_Distance;
	for( double AngleDFVertical=-(DepthFieldQuality-1)/2.0*theApp.m_DepthField_Aperture/100.0; AngleDFVertical<=(DepthFieldQuality-1)/2.0*theApp.m_DepthField_Aperture/100.0 && !BreakUser; AngleDFVertical+=theApp.m_DepthField_Aperture/100.0 )
	{
		for( double AngleDFHorizontal=-(DepthFieldQuality-1)/2.0*theApp.m_DepthField_Aperture/100.0; AngleDFHorizontal<=(DepthFieldQuality-1)/2.0*theApp.m_DepthField_Aperture/100.0 && !BreakUser ; AngleDFHorizontal+=theApp.m_DepthField_Aperture/100.0 )
		{
			// Compute New camera position
			m_CameraAngleV = OldCameraAngleV+AngleDFVertical;
			m_CameraAngleH = OldCameraAngleH+AngleDFHorizontal;
			m_CameraPosition.x = ViewPoint.x-(0*cos(m_CameraAngleH/180.0*PI)+1*sin(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI)*theApp.m_DepthField_Distance;
			m_CameraPosition.y = ViewPoint.y-(0*sin(m_CameraAngleH/180.0*PI)+1*cos(m_CameraAngleH/180.0*PI))*cos(m_CameraAngleV/180.0*PI)*theApp.m_DepthField_Distance;
			m_CameraPosition.z = ViewPoint.z-1*sin(m_CameraAngleV/180.0*PI)*theApp.m_DepthField_Distance;

			NumberPass = 0;
			for( double AngleVertical=5; AngleVertical<90 && !BreakUser; AngleVertical+=(90.0/Quality) )
			{
				for( double AngleHorizontal=0; AngleHorizontal<360 && !BreakUser; AngleHorizontal+=(360.0/Quality/cos(AngleVertical*PI/180)) )
				{
					// Compute light position
					double dist = 1000;
					m_LightPosition.x = (float) (m_CenterOfBattleField.x-cos(AngleVertical*PI/180)*cos(AngleHorizontal*PI/180)*dist);
					m_LightPosition.y = (float) (m_CenterOfBattleField.y+cos(AngleVertical*PI/180)*sin(AngleHorizontal*PI/180)*dist);
					m_LightPosition.z = (float) (m_CenterOfBattleField.z+sin(AngleVertical*PI/180)*dist);
					double Angle;
					Angle = 1.2*asin( sqrt(((pDoc->m_XWidth+1)*TILE3D_WIDTH)*((pDoc->m_XWidth+1)*TILE3D_WIDTH)+((pDoc->m_YHeight+1)*(TILE3D_HEIGHT))*((pDoc->m_YHeight+1)*(TILE3D_HEIGHT)))/1000.0 )*180/PI;

					glMatrixMode( GL_MODELVIEW_MATRIX );
					glLoadIdentity();
					gluPerspective(Angle, 1.0f, 800.0f, 1200.0f);
					glGetFloatv(GL_MODELVIEW_MATRIX, m_LightProjectionMatrix);

					glLoadIdentity();
					gluLookAt( m_LightPosition.x, m_LightPosition.y, m_LightPosition.z, m_CenterOfBattleField.x, m_CenterOfBattleField.y, m_CenterOfBattleField.z, 0.0f, 0.0f, 1.0f);
					glGetFloatv(GL_MODELVIEW_MATRIX, m_LightViewMatrix);

					ComputeShadow();
					RenderScene( true );

					glReadPixels( 0, 0, Viewport[2], Viewport[3], GL_RGB, GL_UNSIGNED_BYTE, m_pViewPoint );
					for( register int y=0; y<Viewport[3]; y++ )
					{
						for( register int x=0; x<Viewport[2]; x++ )
						{
							pPointsR[(y*Viewport[2]+x)] += m_pViewPoint[(y*Viewport[2]+x)*3];
							pPointsG[(y*Viewport[2]+x)] += m_pViewPoint[(y*Viewport[2]+x)*3+1];
							pPointsB[(y*Viewport[2]+x)] += m_pViewPoint[(y*Viewport[2]+x)*3+2];
						}
					}

					SwapBuffers(pDC->GetSafeHdc());
					NumberPass++;
					NbProgress++;
					NbPassGlobal++;
					pCtrl.SetPos(NbProgress);
					pCtrl.RedrawWindow();
					if( GetAsyncKeyState(VK_ESCAPE)&0x8000 )
						BreakUser=true;
				}
			}

			// now render with normal light
			double dist = 1000;
			double AngleVertical = 50;
			double AngleHorizontal = 30;
			m_LightPosition.x = (float) (m_CenterOfBattleField.x-cos(AngleVertical*PI/180)*cos(AngleHorizontal*PI/180)*dist);
			m_LightPosition.y = (float) (m_CenterOfBattleField.y+cos(AngleVertical*PI/180)*sin(AngleHorizontal*PI/180)*dist);
			m_LightPosition.z = (float) (m_CenterOfBattleField.z+sin(AngleVertical*PI/180)*dist);
			double Angle;
			Angle = 1.2*asin( sqrt(((pDoc->m_XWidth+1)*TILE3D_WIDTH)*((pDoc->m_XWidth+1)*TILE3D_WIDTH)+((pDoc->m_YHeight+1)*(TILE3D_HEIGHT))*((pDoc->m_YHeight+1)*(TILE3D_HEIGHT)))/1000.0 )*180/PI;

			glMatrixMode( GL_MODELVIEW_MATRIX );
			glLoadIdentity();
			gluPerspective(Angle, 1.0f, 800.0f, 1200.0f);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_LightProjectionMatrix);

			glLoadIdentity();
			gluLookAt( m_LightPosition.x, m_LightPosition.y, m_LightPosition.z, m_CenterOfBattleField.x, m_CenterOfBattleField.y, m_CenterOfBattleField.z, 0.0f, 0.0f, 1.0f);
			glGetFloatv(GL_MODELVIEW_MATRIX, m_LightViewMatrix);

			ComputeShadow();

			RenderScene( true );

			glReadBuffer( GL_BACK );
			glReadPixels( 0, 0, Viewport[2], Viewport[3], GL_RGB, GL_UNSIGNED_BYTE, m_pViewPoint );
			int NumberShadow = (int) (NumberPass/(1+5*(1-theApp.m_ShadowContrast/30.0)));
			for( register int y=0; y<Viewport[3]; y++ )
			{
				for( register int x=0; x<Viewport[2]; x++ )
				{
					pPointsR[(y*Viewport[2]+x)] += m_pViewPoint[(y*Viewport[2]+x)*3]*NumberShadow;
					pPointsG[(y*Viewport[2]+x)] += m_pViewPoint[(y*Viewport[2]+x)*3+1]*NumberShadow;
					pPointsB[(y*Viewport[2]+x)] += m_pViewPoint[(y*Viewport[2]+x)*3+2]*NumberShadow;
				}
			}

			NumberPass += NumberShadow;
			NbPassGlobal += NumberShadow;
		}
	}

	NumberPass = NbPassGlobal;

	for( register int y=0; y<Viewport[3]; y++ )
	{
		for( int register x=0; x<Viewport[2]; x++ )
		{
			m_pViewPoint[(y*Viewport[2]+x)*3] = (UCHAR) min(255, (pPointsR[(y*Viewport[2]+x)]/NumberPass*CoefLuminosity));
			m_pViewPoint[(y*Viewport[2]+x)*3+1] = (UCHAR) min(255, (pPointsG[(y*Viewport[2]+x)]/NumberPass*CoefLuminosity));
			m_pViewPoint[(y*Viewport[2]+x)*3+2] = (UCHAR) min(255, (pPointsB[(y*Viewport[2]+x)]/NumberPass*CoefLuminosity));
		}
	}

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glRasterPos4d( -1, -1, 0, 1 );
	glDrawBuffer( GL_BACK );
	glDrawPixels( Viewport[2], Viewport[3], GL_RGB, GL_UNSIGNED_BYTE, m_pViewPoint );

	SwapBuffers(pDC->GetSafeHdc());
	ReleaseDC( pDC );

	m_CameraAngleV = OldCameraAngleV;
	m_CameraAngleH = OldCameraAngleH;
	m_CameraPosition = OldCameraPosition;

	free( pPointsR );
	free( pPointsG );
	free( pPointsB );

	SaveImageInMemory();
	m_IsModified=false;
}

// Free memory used by array for view
//
void CHeroscapeEditor3DView::FreeViewPoint()
{
	if( m_pViewPoint!=NULL )
	{
		free( m_pViewPoint );
		m_pViewPoint = NULL;
	}
}

// The user want that the camera go at home (like in the 3D creation)
//
void CHeroscapeEditor3DView::OnCameraGoHome()
{
	CHeroscapeEditorDoc* pDoc = GetDocument();

	m_CameraAngleV = -30;
	m_CameraAngleH = 30;

	double dist = sqrt(((pDoc->m_XWidth+1)*TILE3D_WIDTH)*((pDoc->m_XWidth+1)*TILE3D_WIDTH)+((pDoc->m_YHeight+1)*(TILE3D_HEIGHT))*((pDoc->m_YHeight+1)*(TILE3D_HEIGHT)))*1.1;
	m_CameraPosition.x = (float) (m_CenterOfBattleField.x-cos(m_CameraAngleV*PI/180)*sin(m_CameraAngleH*PI/180)*dist);
	m_CameraPosition.y = (float) (m_CenterOfBattleField.y-cos(m_CameraAngleV*PI/180)*cos(m_CameraAngleH*PI/180)*dist);
	m_CameraPosition.z = (float) (m_CenterOfBattleField.z-sin(m_CameraAngleV*PI/180)*dist);

	glMatrixMode( GL_MODELVIEW_MATRIX );
	glLoadIdentity();
	gluLookAt(m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z, m_CenterOfBattleField.x, m_CenterOfBattleField.y, m_CenterOfBattleField.z, 0.0f, 0.0f, 1.0f);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_CameraViewMatrix);

	if( m_Mode==MODE3D_CONSTRUCTION )
	{
		m_LastLevelToDisplay = 999;
		ComputeShadow();
	}
	m_Mode = MODE3D_NULL;

	m_IsModified = true;
	RedrawWindow();
}

// The user want turn around the map
//
void CHeroscapeEditor3DView::OnOutilsTourneautour()
{
	if( m_Mode==MODE3D_TURN_AROUND )
	{
		m_Mode=MODE3D_NULL;
	}
	else
	{
		if( m_Mode==MODE3D_CONSTRUCTION )
		{
			m_LastLevelToDisplay = 999;
			ComputeShadow();
		}

		m_FirstKeyTime = m_LastKeyTime;
		m_FirstAngleTurnArround = m_CameraAngleH;
		m_Mode = MODE3D_TURN_AROUND;
		m_ModeTurnAround = MTA_PLAY;

		m_IsModified = true;
		RedrawWindow();
	}
}

// Compute auto move
//
bool CHeroscapeEditor3DView::ComputeMoveAuto(  )
{
	double SpeedAnimation = 4.0;

	CHeroscapeEditorDoc* pDoc = GetDocument();

	switch( m_Mode )
	{
	case MODE3D_TURN_AROUND:
		{
			switch( m_ModeTurnAround )
			{
			case MTA_PLAY:
				{
					m_CameraAngleV = -30;
					m_CameraAngleH = m_FirstAngleTurnArround+((m_LastKeyTime-m_FirstKeyTime) / (double) m_frequency)*20;
					double dist = sqrt(((pDoc->m_XWidth+1)*TILE3D_WIDTH)*((pDoc->m_XWidth+1)*TILE3D_WIDTH)+((pDoc->m_YHeight+1)*(TILE3D_HEIGHT))*((pDoc->m_YHeight+1)*(TILE3D_HEIGHT)))*1.1;
					m_CameraPosition.x = (float) (m_CenterOfBattleField.x-cos(m_CameraAngleV*PI/180)*sin(m_CameraAngleH*PI/180)*dist);
					m_CameraPosition.y = (float) (m_CenterOfBattleField.y-cos(m_CameraAngleV*PI/180)*cos(m_CameraAngleH*PI/180)*dist);
					m_CameraPosition.z = (float) (m_CenterOfBattleField.z-sin(m_CameraAngleV*PI/180)*dist);
					return true;
				}
				break;
			case MTA_REVERSE:
				{
					m_CameraAngleV = -30;
					m_CameraAngleH = m_FirstAngleTurnArround-((m_LastKeyTime-m_FirstKeyTime) / (double) m_frequency)*20;
					double dist = sqrt(((pDoc->m_XWidth+1)*TILE3D_WIDTH)*((pDoc->m_XWidth+1)*TILE3D_WIDTH)+((pDoc->m_YHeight+1)*(TILE3D_HEIGHT))*((pDoc->m_YHeight+1)*(TILE3D_HEIGHT)))*1.1;
					m_CameraPosition.x = (float) (m_CenterOfBattleField.x-cos(m_CameraAngleV*PI/180)*sin(m_CameraAngleH*PI/180)*dist);
					m_CameraPosition.y = (float) (m_CenterOfBattleField.y-cos(m_CameraAngleV*PI/180)*cos(m_CameraAngleH*PI/180)*dist);
					m_CameraPosition.z = (float) (m_CenterOfBattleField.z-sin(m_CameraAngleV*PI/180)*dist);
					return true;
				}
				break;
			case MTA_PAUSE:
				return false;
			}
			return true;
		}
		break;
	case MODE3D_CONSTRUCTION:
		{
			pDoc->ComputeLevelMax();
			int LastLevelToDisplay = ((int) (m_LastKeyTime / (double) m_frequency *2))%(pDoc->m_LevelMax*2);
			if( LastLevelToDisplay!=m_LastLevelToDisplay )
			{
				if( LastLevelToDisplay<=pDoc->m_LevelMax )
					m_LastLevelToDisplay = LastLevelToDisplay;
				else
					m_LastLevelToDisplay = pDoc->m_LevelMax*2-LastLevelToDisplay;

				if( m_DisplayShadow )
					ComputeShadow();

				return true;
			}
		}
		break;
	case MODE3D_FREE_ANIMATION:
		{
			double Time = ((m_LastKeyTime-m_FirstKeyTime) / (double) m_frequency)/10;
			if( Time>1 )
			{
				Time = 1;
				m_FirstKeyTime = m_LastKeyTime;
			}
			GetFreeAnimatedPosAtTime( Time, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
			return true;
		}
		break;
	case MODE3D_FIGURE_PLACED_ANIMATION:
		{
			double Time = ((m_LastKeyTime-m_FirstKeyTime) / (double) m_frequency)/SpeedAnimation;
			if( Time>1 )
			{
				GetFreeAnimatedPosAtTime( 1, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
				m_Mode = MODE3D_NULL;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_CreationTime = -1;
				ComputeShadow();
				m_IsModified = true;
				RedrawWindow();
				return false;
			}
			else
			{
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_CreationTime = Time;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
				/*if( Time>0.7 )
				{
					if( ((int) (Time*100))%10<5 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==false )
					{
						((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
					}
					else if( ((int) (Time*100))%10>=5 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==true )
					{
						((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = false;
					}
				}*/
			}
			ComputeShadow();
			GetFreeAnimatedPosAtTime( Time, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
			return true;
		}
		break;
	case MODE3D_FIGURE_MOVED_ANIMATION:
		{
			double Time = ((m_LastKeyTime-m_FirstKeyTime) / (double) m_frequency)/SpeedAnimation;
			if( Time>1 )
			{
				GetFreeAnimatedPosAtTime( 1, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
				m_Mode = MODE3D_NULL;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_CreationTime = -1;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_PosX = m_FigureMoveEndPosXi;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_PosY = m_FigureMoveEndPosYi;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_PosZ = m_FigureMoveEndPosZi;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_CurrentRotation = m_FigureMoveEndRotation;
				ComputeShadow();
				m_IsModified = true;
				RedrawWindow();
				return false;
			}
			else
			{
				// The 
				if( ((int) (Time*40))%4<2 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==false )
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
				else if( ((int) (Time*40))%4>=2 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==true )
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = false;
				if( Time>0.5 )
				{
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_PosX = m_FigureMoveEndPosXi;
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_PosY = m_FigureMoveEndPosYi;
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_PosZ = m_FigureMoveEndPosZi;
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_CurrentRotation = m_FigureMoveEndRotation;
				}
				ComputeShadow();
			}
			GetFreeAnimatedPosAtTime( Time, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
			return true;
		}
		break;
	case MODE3D_FIGURE_REMOVED_ANIMATION:
		{
			double Time = ((m_LastKeyTime-m_FirstKeyTime) / (double) m_frequency)/SpeedAnimation;
			((CGameDoc*) pDoc)->m_pCurrentFigure->m_pTileFigure->m_ExplodeTime = Time;
			if( Time>1 )
			{
				GetFreeAnimatedPosAtTime( 1, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
				m_Mode = MODE3D_NULL;
				((CGameDoc*) pDoc)->RemoveFigureFromMap( ((CGameDoc*) pDoc)->m_pCurrentFigure );
				((CGameDoc*) pDoc)->m_pCurrentFigure->m_pTileFigure->DeleteSmokeObjects();
				ComputeShadow();
				m_IsModified = true;
				RedrawWindow();
				return false;
			}
			else
			{
				// The blinking
				if( ((int) (Time*40))%4<2 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==false )
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
				else if( ((int) (Time*40))%4>=2 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==true )
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = false;
				ComputeShadow();
			}
			GetFreeAnimatedPosAtTime( Time, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
			return true;
		}
		break;
	case MODE3D_ATTACK_ANIMATION:
		{
			double Time = ((m_LastKeyTime-m_FirstKeyTime) / (double) m_frequency)/SpeedAnimation;
			if( Time>1 )
			{
				GetFreeAnimatedPosAtTime( 1, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
				m_Mode = MODE3D_NULL;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_AttackTime = -1;
				ComputeShadow();
				m_IsModified = true;
				RedrawWindow();
				return false;
			}
			else
			{
				if( ((int) (Time*100))%10<5 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==false )
				{
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
					ComputeShadow();
				}
				else if( ((int) (Time*100))%10>=5 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==true )
				{
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = false;
					ComputeShadow();
				}
			}
			GetFreeAnimatedPosAtTime( Time, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
			return true;
		}
		break;
	case MODE3D_DEFENSE_ANIMATION:
		{
			double Time = ((m_LastKeyTime-m_FirstKeyTime) / (double) m_frequency)/SpeedAnimation;
			((CGameDoc*) pDoc)->m_pCurrentFigureAttack->m_pTileFigure->m_AttackTime = Time;
			((CGameDoc*) pDoc)->m_pCurrentFigureDefense->m_pTileFigure->m_AttackTime = Time;
			if( Time>1 )
			{
				GetFreeAnimatedPosAtTime( 1, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
				m_Mode = MODE3D_NULL;
				((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
				((CGameDoc*) pDoc)->m_pCurrentFigureAttack->m_pTileFigure->m_AttackTime = -1;
				((CGameDoc*) pDoc)->m_pCurrentFigureAttack->m_pTileFigure->DeleteSmokeDice();
				((CGameDoc*) pDoc)->m_pCurrentFigureDefense->m_pTileFigure->m_AttackTime = -1;
				((CGameDoc*) pDoc)->m_pCurrentFigureDefense->m_pTileFigure->DeleteSmokeDice();
				ComputeShadow();
				m_IsModified = true;
				RedrawWindow();
				return false;
			}
			else
			{
				// The 
				/*if( ((int) (Time*100))%10<5 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==false )
				{
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = true;
					ComputeShadow();
				}
				else if( ((int) (Time*100))%10>=5 && ((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay==true )
				{
					((CGameDoc*) pDoc)->m_pCurrentFigureTile->m_ToDisplay = false;
					ComputeShadow();
				}*/
				ComputeShadow();
				m_IsModified = true;
			}
			GetFreeAnimatedPosAtTime( Time, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );
			return true;
		}
		break;
	}

	if( ComputeWeapons() )
	{
		if( m_DisplayShadow )
			ComputeShadow();
		return true;
	}

	return false;
}

// Compute the weapons position
//
bool CHeroscapeEditor3DView::ComputeWeapons()
{
	bool Find = false;

	CHeroscapeEditorDoc* pDoc = GetDocument();

	for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
	{
		CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

		if( pTile->ComputeWeapons() )
			Find = true;
	}

	return Find;
}

// To know if the mode is the turn around mode
//
void CHeroscapeEditor3DView::OnUpdateOutilsTourneautour(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_TURN_AROUND )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// Display tile level by level
//
void CHeroscapeEditor3DView::OnOutilsVoirlaconstruction()
{
	if( m_Mode==MODE3D_CONSTRUCTION )
	{
		m_Mode=MODE3D_NULL;

		m_LastLevelToDisplay = 999;
		if( m_DisplayShadow )
			ComputeShadow();

		m_IsModified = true;
		RedrawWindow();
	}
	else
	{
		m_Mode = MODE3D_CONSTRUCTION;
	}

	m_LastLevelToDisplay = 999;
}

// To know if the mode is level by level
//
void CHeroscapeEditor3DView::OnUpdateOutilsVoirlaconstruction(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_CONSTRUCTION )
		pCmdUI->SetCheck( 1 );
	else
		pCmdUI->SetCheck( 0 );
}

// Available only if no other mode selected
//
void CHeroscapeEditor3DView::OnUpdateOutilsVuehautequalite(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL )
	{
		if( m_DisplayShadow )
			pCmdUI->Enable();
		else
			pCmdUI->Enable(FALSE);
	}
	else
		pCmdUI->Enable(FALSE);
}

// When the user press a key
//
void CHeroscapeEditor3DView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if( m_Mode==MODE3D_TURN_AROUND )
	{
		switch( nChar )
		{
		case ' ':
			if( m_ModeTurnAround==MTA_PAUSE )
			{
				m_FirstKeyTime = m_LastKeyTime;
				m_FirstAngleTurnArround = m_CameraAngleH;
				m_ModeTurnAround = MTA_PLAY;
			}
			else
			{
				m_ModeTurnAround = MTA_PAUSE;
			}
			break;
		case VK_BACK:
			m_FirstKeyTime = m_LastKeyTime;
			m_FirstAngleTurnArround = m_CameraAngleH;
			m_ModeTurnAround = MTA_REVERSE;
			break;
		case VK_RIGHT:
			if( m_ModeTurnAround==MTA_PAUSE )
			{
				m_FirstKeyTime = m_LastKeyTime;
				m_FirstAngleTurnArround += 1;
				m_CameraAngleV = -30;
				if( GetAsyncKeyState(VK_SHIFT)&0x8000 )
					m_CameraAngleH -= 0.1;
				else
					m_CameraAngleH -= 1;
				double dist = sqrt(((GetDocument()->m_XWidth+1)*TILE3D_WIDTH)*((GetDocument()->m_XWidth+1)*TILE3D_WIDTH)+((GetDocument()->m_YHeight+1)*(TILE3D_HEIGHT))*((GetDocument()->m_YHeight+1)*(TILE3D_HEIGHT)))*1.1;
				m_CameraPosition.x = (float) (m_CenterOfBattleField.x-cos(m_CameraAngleV*PI/180)*sin(m_CameraAngleH*PI/180)*dist);
				m_CameraPosition.y = (float) (m_CenterOfBattleField.y-cos(m_CameraAngleV*PI/180)*cos(m_CameraAngleH*PI/180)*dist);
				m_CameraPosition.z = (float) (m_CenterOfBattleField.z-sin(m_CameraAngleV*PI/180)*dist);
				RedrawWindow();
			}
			break;
		case VK_LEFT:
			if( m_ModeTurnAround==MTA_PAUSE )
			{
				m_FirstKeyTime = m_LastKeyTime;
				m_FirstAngleTurnArround -= 1;
				m_CameraAngleV = -30;
				if( GetAsyncKeyState(VK_SHIFT)&0x8000 )
					m_CameraAngleH += 0.1;
				else
					m_CameraAngleH += 1;
				double dist = sqrt(((GetDocument()->m_XWidth+1)*TILE3D_WIDTH)*((GetDocument()->m_XWidth+1)*TILE3D_WIDTH)+((GetDocument()->m_YHeight+1)*(TILE3D_HEIGHT))*((GetDocument()->m_YHeight+1)*(TILE3D_HEIGHT)))*1.1;
				m_CameraPosition.x = (float) (m_CenterOfBattleField.x-cos(m_CameraAngleV*PI/180)*sin(m_CameraAngleH*PI/180)*dist);
				m_CameraPosition.y = (float) (m_CenterOfBattleField.y-cos(m_CameraAngleV*PI/180)*cos(m_CameraAngleH*PI/180)*dist);
				m_CameraPosition.z = (float) (m_CenterOfBattleField.z-sin(m_CameraAngleV*PI/180)*dist);
				RedrawWindow();
			}
			break;
		}
	}
	if( nChar=='F' || nChar=='f' )
	{
		// add some target
		CHeroscapeEditorDoc* pDoc = GetDocument();

		for( int i=0; i<pDoc->m_TileList.GetCount(); i++ )
		{
			CTile* pTile = (CTile*) pDoc->m_TileList.GetAt(i);

			if( pTile->m_Type/1000==TYPE_FIGURE )
			{
				pTile->BeginTargetPoint(0,0,0);
				double x,y,z;
				for( int k=0; k<5; k++ )
				{
					x=pTile->m_AttackSource.x;
					y=pTile->m_AttackSource.y;
					z=pTile->m_AttackSource.z;
					// Move random to 20 cases
					for( int j=0; j<20; j++ )
					{
						int r = rand()%6;
						switch( r )
						{
						case 0:
							x += -TILE3D_WIDTH;
							break;
						case 1:
							x += -TILE3D_WIDTH/2;
							y += TILE3D_HEIGHT;
							break;
						case 2:
							x += TILE3D_WIDTH/2;
							y += TILE3D_HEIGHT;
							break;
						case 3:
							x += TILE3D_WIDTH;
							break;
						case 4:
							x += TILE3D_WIDTH/2;
							y += -TILE3D_HEIGHT;
							break;
						case 5:
							x += -TILE3D_WIDTH/2;
							y += -TILE3D_HEIGHT;
							break;
						}
					}
					pTile->AddTargetPoint( x, y, z );
				}
				pTile->EndTargetPoint();
			}
		}
	}
	else if( nChar=='k' || nChar=='K' )
	{
		m_CameraStereoFocusDistance += 1.0;
		RenderStereoView();
	}
	else if( nChar=='l' || nChar=='L' )
	{
		m_CameraStereoFocusDistance -= 1.0;
		if( m_CameraStereoFocusDistance<2 )
			m_CameraStereoFocusDistance = 2;
		RenderStereoView();
	}

	// Call the base class
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

// The view begin active or inactive
//
void CHeroscapeEditor3DView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	if( bActivate==TRUE )
	{
		((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.SetCurrentDoc( GetDocument() );
		((CMyListCtrl*) ((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl())->m_pView = NULL;
	}
	else
	{
		if(pActivateView==pDeactiveView)
		{
			((CMainFrame*) theApp.m_pMainWnd)->m_wndObjectBar.SetCurrentDoc( NULL );
			((CMyListCtrl*) ((CMainFrame*) theApp.m_pMainWnd)->m_wndInfoBar.GetListCtrl())->m_pView = NULL;
		}
	}

	// Call the base class
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

// The user want save the 3D image
//
void CHeroscapeEditor3DView::OnOutilsSaveimage()
{
	int NbBytes = 3 * m_i_Width * m_i_Heigth; 

	// Copy from OpenGL 
	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	// Copy from OpenGL
	::glReadPixels(0,0,m_i_Width,m_i_Heigth,GL_RGB,GL_UNSIGNED_BYTE,(GLvoid*) m_pViewPoint); 

	CFileDialog Dlg( FALSE, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("BMP Files (*.bmp)|*.bmp||"), this );

	if( Dlg.DoModal()==IDOK )
	{
		char FileName[1000];
		size_t i;
		wcstombs_s( &i, FileName, 1000, Dlg.GetPathName().GetBuffer(0), 1000 );

		SaveImage( FileName );
	}

	// Resave image at correct format
	SaveImageInMemory();
}

// Save the frame buffer in an image
//
void CHeroscapeEditor3DView::SaveImage( char* FileName )
{
	short res1=0;
	short res2=0;
	long pixoff=54;
	long compression=0;
	long cmpsize=0;
	long colors=0;
	long impcol=0;
	char m1='B';
	char m2='M';

	DWORD widthDW = ((m_i_Width*3+3)&0xfffc);

	long bmfsize=sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
							widthDW * m_i_Heigth;	
	long byteswritten=0;

	BITMAPINFOHEADER header;
	header.biSize=40; 						// header size
	header.biWidth=m_i_Width;
	header.biHeight=m_i_Heigth;
	header.biPlanes=1;
	header.biBitCount=24;					// RGB encoded, 24 bit
	header.biCompression=BI_RGB;			// no compression
	header.biSizeImage=0;
	header.biXPelsPerMeter=0;
	header.biYPelsPerMeter=0;
	header.biClrUsed=0;
	header.biClrImportant=0;

	FILE *fp;
	fopen_s(&fp, FileName,"wb");
	if (fp!=NULL) 
	{
		// should probably check for write errors here...
		
		fwrite((BYTE  *)&(m1),1,1,fp); byteswritten+=1;
		fwrite((BYTE  *)&(m2),1,1,fp); byteswritten+=1;
		fwrite((long  *)&(bmfsize),4,1,fp);	byteswritten+=4;
		fwrite((int  *)&(res1),2,1,fp); byteswritten+=2;
		fwrite((int  *)&(res2),2,1,fp); byteswritten+=2;
		fwrite((long  *)&(pixoff),4,1,fp); byteswritten+=4;

		fwrite((BITMAPINFOHEADER *)&header,sizeof(BITMAPINFOHEADER),1,fp);
		byteswritten+=sizeof(BITMAPINFOHEADER);
		
		long row=0;
		long rowidx;
		long row_size;
		row_size=header.biWidth*3;
		long rc;
		for (row=0;row<header.biHeight;row++) {
			rowidx=(long unsigned)row*row_size;						      

			// write a row
			for( int col=0; col<header.biWidth; col++ )
			{
				rc=(long) fwrite((void  *)(m_pViewPoint+rowidx+col*3+2),1,1,fp);
				if (rc!=1) 
					break;
				rc=(long) fwrite((void  *)(m_pViewPoint+rowidx+col*3+1),1,1,fp);
				if (rc!=1) 
					break;
				rc=(long) fwrite((void  *)(m_pViewPoint+rowidx+col*3),1,1,fp);
				if (rc!=1) 
					break;
			}

			byteswritten+=row_size;	

			// pad to DWORD
			for (DWORD count=row_size;count<widthDW;count++) {
				char dummy=0;
				fwrite(&dummy,1,1,fp);
				byteswritten++;							  
			}

		}
	           
		fclose(fp);
	}
}

// Create the tile list
//
void CHeroscapeEditor3DView::CreateList()
{
	m_TileUpDownGLList = glGenLists( 1 );;
	glNewList( m_TileUpDownGLList , GL_COMPILE );

	// The down side
	glBegin(GL_POLYGON);
	glNormal3d( 0, 0, -1 );
	glTexCoord2f( 1, 0.25f );
	glVertex3d( TILE3D_X1, TILE3D_Y2, 0 );
	glTexCoord2f( 0.5f, 0 );
	glVertex3d( TILE3D_X2, TILE3D_Y1, 0 );
	glTexCoord2f( 0, 0.25f );
	glVertex3d( TILE3D_X3, TILE3D_Y2, 0 );
	glTexCoord2f( 0, 0.75f );
	glVertex3d( TILE3D_X3, TILE3D_Y3, 0 );
	glTexCoord2f( 0.5f, 1 );
	glVertex3d( TILE3D_X2, TILE3D_Y4, 0 );
	glTexCoord2f( 1, 0.75f );
	glVertex3d( TILE3D_X1, TILE3D_Y3, 0 );
	glEnd();
	
	// The up side
	glBegin(GL_POLYGON);
	glNormal3d( 0, 0, 1 );
	glTexCoord2f( 0, 0.25f );
	glVertex3d( TILE3D_X1, TILE3D_Y3, TILE3D_ZHEIGHT );
	glTexCoord2f( 0.5f, 0 );
	glVertex3d( TILE3D_X2, TILE3D_Y4, TILE3D_ZHEIGHT );
	glTexCoord2f( 1, 0.25f );
	glVertex3d( TILE3D_X3, TILE3D_Y3, TILE3D_ZHEIGHT );
	glTexCoord2f( 1, 0.75f );
	glVertex3d( TILE3D_X3, TILE3D_Y2, TILE3D_ZHEIGHT );
	glTexCoord2f( 0.5f, 1 );
	glVertex3d( TILE3D_X2, TILE3D_Y1, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 0.75f );
	glVertex3d( TILE3D_X1, TILE3D_Y2, TILE3D_ZHEIGHT );
	glEnd();
	glEndList();

	// The sides
	m_TileSideGLList = glGenLists( 1 );;
	glNewList( m_TileSideGLList , GL_COMPILE );
	glBegin(GL_QUADS);
	glNormal3d( TILE3D_NX1, TILE3D_NY1, 0 );
	glTexCoord2f( 1, 1 );
	glVertex3d( TILE3D_X1, TILE3D_Y2, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 1 );
	glVertex3d( TILE3D_X2, TILE3D_Y1, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 0 );
	glVertex3d( TILE3D_X2, TILE3D_Y1, 0 );
	glTexCoord2f( 1, 0 );
	glVertex3d( TILE3D_X1, TILE3D_Y2, 0 );

	glNormal3d( TILE3D_NX2, TILE3D_NY2, 0 );
	glTexCoord2f( 1, 1 );
	glVertex3d( TILE3D_X2, TILE3D_Y1, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 1 );
	glVertex3d( TILE3D_X3, TILE3D_Y2, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 0 );
	glVertex3d( TILE3D_X3, TILE3D_Y2, 0 );
	glTexCoord2f( 1, 0 );
	glVertex3d( TILE3D_X2, TILE3D_Y1, 0 );

	glNormal3d( TILE3D_NX3, TILE3D_NY3, 0 );
	glTexCoord2f( 1, 1 );
	glVertex3d( TILE3D_X3, TILE3D_Y2, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 1 );
	glVertex3d( TILE3D_X3, TILE3D_Y3, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 0 );
	glVertex3d( TILE3D_X3, TILE3D_Y3, 0 );
	glTexCoord2f( 1, 0 );
	glVertex3d( TILE3D_X3, TILE3D_Y2, 0 );

	glNormal3d( TILE3D_NX4, TILE3D_NY4, 0 );
	glTexCoord2f( 1, 1 );
	glVertex3d( TILE3D_X3, TILE3D_Y3, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 1 );
	glVertex3d( TILE3D_X2, TILE3D_Y4, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 0 );
	glVertex3d( TILE3D_X2, TILE3D_Y4, 0 );
	glTexCoord2f( 1, 0 );
	glVertex3d( TILE3D_X3, TILE3D_Y3, 0 );

	glNormal3d( TILE3D_NX5, TILE3D_NY5, 0 );
	glTexCoord2f( 1, 1 );
	glVertex3d( TILE3D_X2, TILE3D_Y4, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 1 );
	glVertex3d( TILE3D_X1, TILE3D_Y3, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 0 );
	glVertex3d( TILE3D_X1, TILE3D_Y3, 0 );
	glTexCoord2f( 1, 0 );
	glVertex3d( TILE3D_X2, TILE3D_Y4, 0 );

	glNormal3d( TILE3D_NX6, TILE3D_NY6, 0 );
	glTexCoord2f( 1, 1 );
	glVertex3d( TILE3D_X1, TILE3D_Y3, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 1 );
	glVertex3d( TILE3D_X1, TILE3D_Y2, TILE3D_ZHEIGHT );
	glTexCoord2f( 0, 0 );
	glVertex3d( TILE3D_X1, TILE3D_Y2, 0 );
	glTexCoord2f( 1, 0 );
	glVertex3d( TILE3D_X1, TILE3D_Y3, 0 );
	glEnd();
	glEndList();
}

// Get the Id of the personal texture (or -1 if file not found)
//
GLuint CHeroscapeEditor3DView::GetPersonalTextureId( CString FileName )
{
	// Search if the texture is already loaded
	for( int i=0; i<m_PersonalTextureList.GetCount(); i++ )
	{
		CPersonalTexture* pPersonalTexture = (CPersonalTexture*) m_PersonalTextureList.GetAt(i);
		if( pPersonalTexture->FileName==FileName )
			return pPersonalTexture->Id;
	}

	// This texture is not found so try to load it
	GLuint TextureId = CStaticGraphicalLib::LoadTexture( theApp.m_CurrentDir+_T("\\Images\\Personal\\")+FileName, 255 );

	// Add this texture to the list
	CPersonalTexture* pPersonalTexture = new CPersonalTexture;
	pPersonalTexture->FileName = FileName;
	pPersonalTexture->Id = TextureId;
	m_PersonalTextureList.Add( pPersonalTexture );

	return TextureId;
}

// Get the Id of the texture (or -1 if file not found)
//
GLuint CHeroscapeEditor3DView::GetTextureId( CString FileName, int Alpha )
{
	// Search if the texture is already loaded
	for( int i=0; i<m_TextureList.GetCount(); i++ )
	{
		CPersonalTexture* pPersonalTexture = (CPersonalTexture*) m_TextureList.GetAt(i);
		if( pPersonalTexture->FileName==FileName )
			return pPersonalTexture->Id;
	}

	CString TextureType;
	switch( theApp.m_TextureType )
	{
	case 0:
		TextureType = _T("Normal");
		break;
	case 1:
		TextureType = _T("Srmalloy");
		break;
	}

	// This texture is not found so try to load it
	GLuint TextureId = CStaticGraphicalLib::LoadTexture( theApp.m_CurrentDir+_T("\\Images\\")+TextureType+_T("\\")+FileName, Alpha );

	// Add this texture to the list
	CPersonalTexture* pPersonalTexture = new CPersonalTexture;
	pPersonalTexture->FileName = FileName;
	pPersonalTexture->Id = TextureId;
	m_TextureList.Add( pPersonalTexture );

	return TextureId;
}

// Get the Id of the glyph texture (or -1 if file not found)
//
GLuint CHeroscapeEditor3DView::GetGlyphTextureId( CString FileName )
{
	// Search if the texture is already loaded
	for( int i=0; i<m_GlyphTextureList.GetCount(); i++ )
	{
		CPersonalTexture* pPersonalTexture = (CPersonalTexture*) m_GlyphTextureList.GetAt(i);
		if( pPersonalTexture->FileName==FileName )
			return pPersonalTexture->Id;
	}

	CString TextureType;
	switch( theApp.m_TextureType )
	{
	case 0:
		TextureType = _T("Normal");
		break;
	case 1:
		TextureType = _T("Srmalloy");
		break;
	}

	CString Language;
	Language.LoadStringW( IDS_LANGUAGE );

	// This texture is not found so try to load it
	GLuint TextureId = CStaticGraphicalLib::LoadTexture( theApp.m_CurrentDir+_T("\\Images\\")+TextureType+_T("\\")+Language+_T("\\")+FileName, 255 );

	// Add this texture to the list
	CPersonalTexture* pPersonalTexture = new CPersonalTexture;
	pPersonalTexture->FileName = FileName;
	pPersonalTexture->Id = TextureId;
	m_GlyphTextureList.Add( pPersonalTexture );

	return TextureId;
}

// Get the Object3D for a particular figure
//
CObject3D* CHeroscapeEditor3DView::GetFigureObject( CString FigureFile )
{
	// Search if the object is already loaded
	for( int i=0; i<m_FigureObjectList.GetCount(); i++ )
	{
		CFigureObject* pFigureObject = (CFigureObject*) m_FigureObjectList.GetAt(i);
		if( pFigureObject->m_FigureFile==FigureFile )
			return pFigureObject->m_pObject;
	}

	// This object is not found so try to load it
	CObject3D* pObject3D = new CObject3D;
	CString Str;
	Str.Format( _T("%s\\Objets 3D\\Figures\\%s\\Figure.sgl"), theApp.m_CurrentDir, FigureFile );
	pObject3D->LoadSgl( Str );
	pObject3D->CreateList();

	CFigureObject* pFigureObject = new CFigureObject( false, FigureFile, FigureFile, NULL );
	pFigureObject->m_FigureFile = FigureFile;
	pFigureObject->m_pObject = pObject3D;

	m_FigureObjectList.Add( pFigureObject );

	return pObject3D;
}

// The user want know the field at this position
//
void CHeroscapeEditor3DView::OnRButtonDown(UINT nFlags, CPoint point)
{
	GLfloat	FieldDistance;

	glReadPixels( point.x, m_i_Heigth-point.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &FieldDistance );

	TRACE( _T("Profondeur : %f\n"), FieldDistance );

	// Call the base class
	CView::OnRButtonDown(nFlags, point);
}

// To refresh the erase position item
//
void CHeroscapeEditor3DView::OnUpdateVideoEraseAllPosition(CCmdUI *pCmdUI)
{
	if( m_AnimatedPositionList.GetCount()==0 )
		pCmdUI->Enable( false );
	else
		pCmdUI->Enable( true );
}

// To erase all the camera position
//
void CHeroscapeEditor3DView::OnVideoEraseAllPosition()
{
	FreeAnimatedPosition();
}

// Add a new position for the camera
//
void CHeroscapeEditor3DView::OnVideoAddCurrentPosition()
{
	MyPoint3D* pNewCameraPoint = new MyPoint3D( m_CameraPosition );
	MyPoint3D* pNewLookAtPoint = new MyPoint3D( m_CameraLookAt );
	AnimatedPosition* pNewAnimatedPosition = new AnimatedPosition();
	pNewAnimatedPosition->pCameraPoint = pNewCameraPoint;
	pNewAnimatedPosition->pLookAt = pNewLookAtPoint;
	pNewAnimatedPosition->DepthField_Aperture = theApp.m_DepthField_Aperture;
	pNewAnimatedPosition->DepthField_Distance = theApp.m_DepthField_Distance;

	m_AnimatedPositionList.Add( pNewAnimatedPosition );
}

// To know if we can add a current position or not
//
void CHeroscapeEditor3DView::OnUpdateVideoAddCurrentPosition(CCmdUI *pCmdUI)
{
	if( m_AnimatedPositionList.GetCount()==0 )
		pCmdUI->Enable( true );
	else
	{
		//AnimatedPosition* pAnimatedPosition = (AnimatedPosition*) m_AnimatedPositionList.GetAt(m_AnimatedPositionList.GetCount()-1);
		//if( (m_CameraPosition.x==pAnimatedPosition->pCameraPoint->x && m_CameraPosition.y==pAnimatedPosition->pCameraPoint->y && m_CameraPosition.z==pAnimatedPosition->pCameraPoint->z ) || (m_CameraLookAt.x==pAnimatedPosition->pLookAt->x && m_CameraLookAt.y==pAnimatedPosition->pLookAt->y && m_CameraLookAt.z==pAnimatedPosition->pLookAt->z) )
		//	pCmdUI->Enable( false );
		//else
			pCmdUI->Enable( true );
	}
}

// To know if we can make an animation or not
//
void CHeroscapeEditor3DView::OnUpdateVideoMoveRealtime(CCmdUI *pCmdUI)
{
	if( m_AnimatedPositionList.GetCount()>=2 )
		pCmdUI->Enable( true );
	else
		pCmdUI->Enable( false );
}

// Play animation
//
void CHeroscapeEditor3DView::OnVideoMoveRealtime()
{
	if( m_AnimatedPositionList.GetCount()>=2 )
	{
		if( m_Mode==MODE3D_FREE_ANIMATION )
		{
			m_Mode=MODE3D_NULL;
			OnCameraGoHome();
			theApp.m_DepthField_Aperture = m_Backup_DepthField_Aperture;
			theApp.m_DepthField_Distance = m_Backup_DepthField_Distance;
		}
		else
		{
			m_Backup_DepthField_Aperture = theApp.m_DepthField_Aperture;
			m_Backup_DepthField_Distance = theApp.m_DepthField_Distance;
			m_Mode=MODE3D_FREE_ANIMATION;
			m_FirstKeyTime = m_LastKeyTime;
			ComputeAnimatedPath();
		}
	}
}

// Play animation
//
void CHeroscapeEditor3DView::MoveFigurePlacedRealtime()
{
	if( m_AnimatedPositionList.GetCount()>=2 )
	{
		m_Backup_DepthField_Aperture = theApp.m_DepthField_Aperture;
		m_Backup_DepthField_Distance = theApp.m_DepthField_Distance;
		m_Mode=MODE3D_FIGURE_PLACED_ANIMATION;
		LARGE_INTEGER	CurrentTimer;
		QueryPerformanceCounter( &CurrentTimer );
		m_LastKeyTime = CurrentTimer.QuadPart;
		m_FirstKeyTime = m_LastKeyTime;
		ComputeAnimatedPath( false );
	}
}

// Play animation
//
void CHeroscapeEditor3DView::MoveFigureMovedRealtime()
{
	if( m_AnimatedPositionList.GetCount()>=2 )
	{
		m_Backup_DepthField_Aperture = theApp.m_DepthField_Aperture;
		m_Backup_DepthField_Distance = theApp.m_DepthField_Distance;
		m_Mode=MODE3D_FIGURE_MOVED_ANIMATION;
		LARGE_INTEGER	CurrentTimer;
		QueryPerformanceCounter( &CurrentTimer );
		m_LastKeyTime = CurrentTimer.QuadPart;
		m_FirstKeyTime = m_LastKeyTime;
		ComputeAnimatedPath( false );
	}
}

// Play animation
//
void CHeroscapeEditor3DView::AttackRealtime()
{
	if( m_AnimatedPositionList.GetCount()>=2 )
	{
		m_Backup_DepthField_Aperture = theApp.m_DepthField_Aperture;
		m_Backup_DepthField_Distance = theApp.m_DepthField_Distance;
		m_Mode=MODE3D_ATTACK_ANIMATION;
		LARGE_INTEGER	CurrentTimer;
		QueryPerformanceCounter( &CurrentTimer );
		m_LastKeyTime = CurrentTimer.QuadPart;
		m_FirstKeyTime = m_LastKeyTime;
		ComputeAnimatedPath( false );
	}
}

// Play animation
//
void CHeroscapeEditor3DView::DefenseRealtime()
{
	if( m_AnimatedPositionList.GetCount()>=2 )
	{
		m_Backup_DepthField_Aperture = theApp.m_DepthField_Aperture;
		m_Backup_DepthField_Distance = theApp.m_DepthField_Distance;
		m_Mode=MODE3D_DEFENSE_ANIMATION;
		LARGE_INTEGER	CurrentTimer;
		QueryPerformanceCounter( &CurrentTimer );
		m_LastKeyTime = CurrentTimer.QuadPart;
		m_FirstKeyTime = m_LastKeyTime;
		ComputeAnimatedPath( false );
	}
}

// Play animation
//
void CHeroscapeEditor3DView::MoveFigureRemovedRealtime()
{
	if( m_AnimatedPositionList.GetCount()>=2 )
	{
		m_Backup_DepthField_Aperture = theApp.m_DepthField_Aperture;
		m_Backup_DepthField_Distance = theApp.m_DepthField_Distance;
		m_Mode=MODE3D_FIGURE_REMOVED_ANIMATION;
		LARGE_INTEGER	CurrentTimer;
		QueryPerformanceCounter( &CurrentTimer );
		m_LastKeyTime = CurrentTimer.QuadPart;
		m_FirstKeyTime = m_LastKeyTime;
		ComputeAnimatedPath( false );
	}
}

// Compute the animated path for free animation
//
void CHeroscapeEditor3DView::ComputeAnimatedPath( bool Closed )
{
	FreeAnimatedPath();

	int NbPoint = m_AnimatedPositionList.GetCount();

	if( NbPoint<3 )
		Closed = false;

	if( NbPoint<2 )
		return;

	// Calcul les points de control
	if( Closed )
	{
		AnimatedPosition* pNewAnimatedPosition = new AnimatedPosition;
		pNewAnimatedPosition->pCameraPoint = new MyPoint3D( *((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint );
		pNewAnimatedPosition->pLookAt = new MyPoint3D( *((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt );
		pNewAnimatedPosition->DepthField_Aperture = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->DepthField_Aperture;
		pNewAnimatedPosition->DepthField_Distance = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->DepthField_Distance;
		m_AnimatedPositionList.Add( pNewAnimatedPosition );
		NbPoint++;
	}

	AnimatedPosition* pNewAnimatedPosition = new AnimatedPosition;
	pNewAnimatedPosition->pCameraPoint = new MyPoint3D( *((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint );
	pNewAnimatedPosition->pLookAt = new MyPoint3D( *((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt );
	pNewAnimatedPosition->DepthField_Aperture = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->DepthField_Aperture;
	pNewAnimatedPosition->DepthField_Distance = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->DepthField_Distance;
	m_AnimatedPath.Add( pNewAnimatedPosition );

	// This second point will be set later
	pNewAnimatedPosition = new AnimatedPosition;
	pNewAnimatedPosition->pCameraPoint = new MyPoint3D( *((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint );
	pNewAnimatedPosition->pLookAt = new MyPoint3D( *((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt );
	m_AnimatedPath.Add( pNewAnimatedPosition );

	int i=1;
	for( ; i<NbPoint-1; i++ )
	{
		// Compute vector for control point
		MyPoint3D Vector,Vector1,Vector2;
		Vector1.x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pCameraPoint->x;
		Vector1.y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pCameraPoint->y;
		Vector1.z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pCameraPoint->z;
		double k1 = sqrt(Vector1.x*Vector1.x+Vector1.y*Vector1.y+Vector1.z*Vector1.z);
		if( k1>0 )
		{
			Vector1.x /= k1;
			Vector1.y /= k1;
			Vector1.z /= k1;
		}

		Vector2.x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i+1))->pCameraPoint->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x;
		Vector2.y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i+1))->pCameraPoint->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y;
		Vector2.z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i+1))->pCameraPoint->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z;
		double k2 = sqrt(Vector2.x*Vector2.x+Vector2.y*Vector2.y+Vector2.z*Vector2.z);
		if( k2>0 )
		{
			Vector2.x /= k2;
			Vector2.y /= k2;
			Vector2.z /= k2;
		}

		Vector.x = Vector1.x+Vector2.x;
		Vector.y = Vector1.y+Vector2.y;
		Vector.z = Vector1.z+Vector2.z;
		double k = sqrt(Vector.x*Vector.x+Vector.y*Vector.y+Vector.z*Vector.z);
		if( k>0 )
		{
			Vector.x /= k;
			Vector.y /= k;
			Vector.z /= k;
		}

		// Compute vector for control point
		MyPoint3D LVector,LVector1,LVector2;
		LVector1.x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pLookAt->x;
		LVector1.y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pLookAt->y;
		LVector1.z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pLookAt->z;
		double Lk1 = sqrt(LVector1.x*LVector1.x+LVector1.y*LVector1.y+LVector1.z*LVector1.z);
		if( Lk1>0 )
		{
			LVector1.x /= Lk1;
			LVector1.y /= Lk1;
			LVector1.z /= Lk1;
		}

		LVector2.x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i+1))->pLookAt->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x;
		LVector2.y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i+1))->pLookAt->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y;
		LVector2.z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i+1))->pLookAt->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z;
		double Lk2 = sqrt(LVector2.x*LVector2.x+LVector2.y*LVector2.y+LVector2.z*LVector2.z);
		if( Lk2>0 )
		{
			LVector2.x /= Lk2;
			LVector2.y /= Lk2;
			LVector2.z /= Lk2;
		}

		LVector.x = LVector1.x+LVector2.x;
		LVector.y = LVector1.y+LVector2.y;
		LVector.z = LVector1.z+LVector2.z;
		double Lk = sqrt(LVector.x*LVector.x+LVector.y*LVector.y+LVector.z*LVector.z);
		if( Lk>0 )
		{
			LVector.x /= Lk;
			LVector.y /= Lk;
			LVector.z /= Lk;
		}

		pNewAnimatedPosition = new AnimatedPosition;
		pNewAnimatedPosition->pCameraPoint = new MyPoint3D();
		pNewAnimatedPosition->pLookAt = new MyPoint3D();
		m_AnimatedPath.Add( pNewAnimatedPosition );
		pNewAnimatedPosition->pCameraPoint->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x-Vector.x*0.25*k1;
		pNewAnimatedPosition->pCameraPoint->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y-Vector.y*0.25*k1;
		pNewAnimatedPosition->pCameraPoint->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z-Vector.z*0.25*k1;
		pNewAnimatedPosition->pLookAt->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x-LVector.x*0.25*Lk1;
		pNewAnimatedPosition->pLookAt->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y-LVector.y*0.25*Lk1;
		pNewAnimatedPosition->pLookAt->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z-LVector.z*0.25*Lk1;

		pNewAnimatedPosition = new AnimatedPosition;
		pNewAnimatedPosition->pCameraPoint = new MyPoint3D();
		pNewAnimatedPosition->pLookAt = new MyPoint3D();
		m_AnimatedPath.Add( pNewAnimatedPosition );
		pNewAnimatedPosition->pCameraPoint->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x;
		pNewAnimatedPosition->pCameraPoint->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y;
		pNewAnimatedPosition->pCameraPoint->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z;
		pNewAnimatedPosition->pLookAt->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x;
		pNewAnimatedPosition->pLookAt->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y;
		pNewAnimatedPosition->pLookAt->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z;
		pNewAnimatedPosition->DepthField_Aperture = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->DepthField_Aperture;
		pNewAnimatedPosition->DepthField_Distance = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->DepthField_Distance;

		pNewAnimatedPosition = new AnimatedPosition;
		pNewAnimatedPosition->pCameraPoint = new MyPoint3D();
		pNewAnimatedPosition->pLookAt = new MyPoint3D();
		m_AnimatedPath.Add( pNewAnimatedPosition );
		pNewAnimatedPosition->pCameraPoint->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x+Vector.x*0.25*k1;
		pNewAnimatedPosition->pCameraPoint->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y+Vector.y*0.25*k1;
		pNewAnimatedPosition->pCameraPoint->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z+Vector.z*0.25*k1;
		pNewAnimatedPosition->pLookAt->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x+LVector.x*0.25*Lk1;
		pNewAnimatedPosition->pLookAt->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y+LVector.y*0.25*Lk1;
		pNewAnimatedPosition->pLookAt->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z+LVector.z*0.25*Lk1;
	}

	if( Closed )
	{
		// Compute vector for control point
		MyPoint3D Vector,Vector1,Vector2;
		Vector1.x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pCameraPoint->x;
		Vector1.y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pCameraPoint->y;
		Vector1.z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pCameraPoint->z;
		double k1 = sqrt(Vector1.x*Vector1.x+Vector1.y*Vector1.y+Vector1.z*Vector1.z);
		if( k1>0 )
		{
			Vector1.x /= k1;
			Vector1.y /= k1;
			Vector1.z /= k1;
		}

		Vector2.x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pCameraPoint->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->x;
		Vector2.y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pCameraPoint->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->y;
		Vector2.z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pCameraPoint->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->z;
		double k2 = sqrt(Vector2.x*Vector2.x+Vector2.y*Vector2.y+Vector2.z*Vector2.z);
		if( k2>0 )
		{
			Vector2.x /= k2;
			Vector2.y /= k2;
			Vector2.z /= k2;
		}

		Vector.x = Vector1.x+Vector2.x;
		Vector.y = Vector1.y+Vector2.y;
		Vector.z = Vector1.z+Vector2.z;
		double k = sqrt(Vector.x*Vector.x+Vector.y*Vector.y+Vector.z*Vector.z);
		if( k>0 )
		{
			Vector.x /= k;
			Vector.y /= k;
			Vector.z /= k;
		}

		MyPoint3D LVector,LVector1,LVector2;
		LVector1.x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pLookAt->x;
		LVector1.y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pLookAt->y;
		LVector1.z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pLookAt->z;
		double Lk1 = sqrt(LVector1.x*LVector1.x+LVector1.y*LVector1.y+LVector1.z*LVector1.z);
		if( Lk1>0 )
		{
			LVector1.x /= Lk1;
			LVector1.y /= Lk1;
			LVector1.z /= Lk1;
		}

		LVector2.x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pLookAt->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->x;
		LVector2.y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pLookAt->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->y;
		LVector2.z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pLookAt->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->z;
		double Lk2 = sqrt(LVector2.x*LVector2.x+LVector2.y*LVector2.y+LVector2.z*LVector2.z);
		if( Lk2>0 )
		{
			LVector2.x /= Lk2;
			LVector2.y /= Lk2;
			LVector2.z /= Lk2;
		}

		LVector.x = LVector1.x+LVector2.x;
		LVector.y = LVector1.y+LVector2.y;
		LVector.z = LVector1.z+LVector2.z;
		double Lk = sqrt(LVector.x*LVector.x+LVector.y*LVector.y+LVector.z*LVector.z);
		if( Lk>0 )
		{
			LVector.x /= Lk;
			LVector.y /= Lk;
			LVector.z /= Lk;
		}

		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pCameraPoint->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->x+Vector.x*0.25*k2;
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pCameraPoint->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->y+Vector.y*0.25*k2;
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pCameraPoint->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->z+Vector.z*0.25*k2;
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pLookAt->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->x+LVector.x*0.25*Lk2;
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pLookAt->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->y+LVector.y*0.25*Lk2;
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pLookAt->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->z+LVector.z*0.25*Lk2;

		pNewAnimatedPosition = new AnimatedPosition;
		pNewAnimatedPosition->pCameraPoint = new MyPoint3D();
		pNewAnimatedPosition->pLookAt = new MyPoint3D();
		m_AnimatedPath.Add( pNewAnimatedPosition );
		pNewAnimatedPosition->pCameraPoint->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x-Vector.x*0.25*k2;
		pNewAnimatedPosition->pCameraPoint->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y-Vector.y*0.25*k2;
		pNewAnimatedPosition->pCameraPoint->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z-Vector.z*0.25*k2;
		pNewAnimatedPosition->pLookAt->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x-LVector.x*0.25*Lk2;
		pNewAnimatedPosition->pLookAt->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y-LVector.y*0.25*Lk2;
		pNewAnimatedPosition->pLookAt->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z-LVector.z*0.25*Lk2;
	}
	else
	{
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pCameraPoint->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->x+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pCameraPoint->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->x);
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pCameraPoint->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->y+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pCameraPoint->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->y);
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pCameraPoint->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->z+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pCameraPoint->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pCameraPoint->z);
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pLookAt->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->x+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pLookAt->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->x);
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pLookAt->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->y+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pLookAt->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->y);
		((AnimatedPosition*) m_AnimatedPath.GetAt(1))->pLookAt->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->z+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(1))->pLookAt->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(0))->pLookAt->z);

		pNewAnimatedPosition = new AnimatedPosition;
		pNewAnimatedPosition->pCameraPoint = new MyPoint3D();
		pNewAnimatedPosition->pLookAt = new MyPoint3D();
		m_AnimatedPath.Add( pNewAnimatedPosition );
		pNewAnimatedPosition->pCameraPoint->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pCameraPoint->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x);
		pNewAnimatedPosition->pCameraPoint->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pCameraPoint->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y);
		pNewAnimatedPosition->pCameraPoint->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pCameraPoint->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z);
		pNewAnimatedPosition->pLookAt->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pLookAt->x-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x);
		pNewAnimatedPosition->pLookAt->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pLookAt->y-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y);
		pNewAnimatedPosition->pLookAt->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z+0.25*(((AnimatedPosition*) m_AnimatedPositionList.GetAt(i-1))->pLookAt->z-((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z);
	}

	pNewAnimatedPosition = new AnimatedPosition;
	pNewAnimatedPosition->pCameraPoint = new MyPoint3D();
	pNewAnimatedPosition->pLookAt = new MyPoint3D();
	m_AnimatedPath.Add( pNewAnimatedPosition );
	pNewAnimatedPosition->pCameraPoint->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->x;
	pNewAnimatedPosition->pCameraPoint->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->y;
	pNewAnimatedPosition->pCameraPoint->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pCameraPoint->z;
	pNewAnimatedPosition->pLookAt->x = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->x;
	pNewAnimatedPosition->pLookAt->y = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->y;
	pNewAnimatedPosition->pLookAt->z = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->pLookAt->z;
	pNewAnimatedPosition->DepthField_Aperture = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->DepthField_Aperture;
	pNewAnimatedPosition->DepthField_Distance = ((AnimatedPosition*) m_AnimatedPositionList.GetAt(i))->DepthField_Distance;

	if( Closed )
	{
		AnimatedPosition* pAnimatedPosition = (AnimatedPosition*) m_AnimatedPositionList.GetAt(m_AnimatedPositionList.GetCount()-1);
		delete pAnimatedPosition->pCameraPoint;
		delete pAnimatedPosition->pLookAt;
		delete pAnimatedPosition;

		m_AnimatedPositionList.RemoveAt(m_AnimatedPositionList.GetCount()-1);
	}
}

// Free memory for animated path
//
void CHeroscapeEditor3DView::FreeAnimatedPath()
{
	for( int i=0; i<m_AnimatedPath.GetCount(); i++ )
	{
		AnimatedPosition* pAnimatedPosition = (AnimatedPosition*) m_AnimatedPath.GetAt(i);
		delete pAnimatedPosition->pCameraPoint;
		delete pAnimatedPosition->pLookAt;
		delete pAnimatedPosition;
	}

	m_AnimatedPath.RemoveAll();
}

// Free memory for animated position
//
void CHeroscapeEditor3DView::FreeAnimatedPosition()
{
	for( int i=0; i<m_AnimatedPositionList.GetCount(); i++ )
	{
		AnimatedPosition* pAnimatedPosition = (AnimatedPosition*) m_AnimatedPositionList.GetAt(i);
		delete pAnimatedPosition->pCameraPoint;
		delete pAnimatedPosition->pLookAt;
		delete pAnimatedPosition;
	}
	m_AnimatedPositionList.RemoveAll();
}

// Obtient la position de la camera et de la vue a un temps donné
//
void CHeroscapeEditor3DView::GetFreeAnimatedPosAtTime( double myTime, MyPoint3D* pCamera, MyPoint3D* pLookAt, double* DepthField_Aperture, double* DepthField_Distance )
{
	if( myTime>=1 )
	{
		pCamera->x = ((AnimatedPosition*) m_AnimatedPath.GetAt(m_AnimatedPath.GetCount()-1))->pCameraPoint->x;
		pCamera->y = ((AnimatedPosition*) m_AnimatedPath.GetAt(m_AnimatedPath.GetCount()-1))->pCameraPoint->y;
		pCamera->z = ((AnimatedPosition*) m_AnimatedPath.GetAt(m_AnimatedPath.GetCount()-1))->pCameraPoint->z;
		pLookAt->x = ((AnimatedPosition*) m_AnimatedPath.GetAt(m_AnimatedPath.GetCount()-1))->pLookAt->x;
		pLookAt->y = ((AnimatedPosition*) m_AnimatedPath.GetAt(m_AnimatedPath.GetCount()-1))->pLookAt->y;
		pLookAt->z = ((AnimatedPosition*) m_AnimatedPath.GetAt(m_AnimatedPath.GetCount()-1))->pLookAt->z;
		TRACE( _T("Position fin : %f %f %f %f %f %f\n"), pCamera->x, pCamera->y, pCamera->z, pLookAt->x, pLookAt->y, pLookAt->z );
		return;
	}
	if( myTime<=0 )
	{
		pCamera->x = ((AnimatedPosition*) m_AnimatedPath.GetAt(0))->pCameraPoint->x;
		pCamera->y = ((AnimatedPosition*) m_AnimatedPath.GetAt(0))->pCameraPoint->y;
		pCamera->z = ((AnimatedPosition*) m_AnimatedPath.GetAt(0))->pCameraPoint->z;
		pLookAt->x = ((AnimatedPosition*) m_AnimatedPath.GetAt(0))->pLookAt->x;
		pLookAt->y = ((AnimatedPosition*) m_AnimatedPath.GetAt(0))->pLookAt->y;
		pLookAt->z = ((AnimatedPosition*) m_AnimatedPath.GetAt(0))->pLookAt->z;
		TRACE( _T("Position fin : %f %f %f %f %f %f\n"), pCamera->x, pCamera->y, pCamera->z, pLookAt->x, pLookAt->y, pLookAt->z );
		return;
	}

	int NbSegment = (m_AnimatedPath.GetCount()-4)/3+1;

	int Point1 = ((int) (NbSegment*myTime))*3;

	double t = ((NbSegment*myTime*3)-Point1)/3;

	//TRACE("Time : %f     Nb Segment : %i     Point1 %i    t : %f\n",myTime,NbSegment,Point1,t);

	MyPoint3D* p1 = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1))->pCameraPoint;
	MyPoint3D* p2 = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1+1))->pCameraPoint;
	MyPoint3D* p3 = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1+2))->pCameraPoint;
	MyPoint3D* p4 = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1+3))->pCameraPoint;
	pCamera->x = pow((1-t),3)*p1->x + 3*pow((1-t),2)*t*p2->x + 3*(1-t)*pow(t,2)*p3->x + pow(t,3)*p4->x;
	pCamera->y = pow((1-t),3)*p1->y + 3*pow((1-t),2)*t*p2->y + 3*(1-t)*pow(t,2)*p3->y + pow(t,3)*p4->y;
	pCamera->z = pow((1-t),3)*p1->z + 3*pow((1-t),2)*t*p2->z + 3*(1-t)*pow(t,2)*p3->z + pow(t,3)*p4->z;
	p1 = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1))->pLookAt;
	p2 = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1+1))->pLookAt;
	p3 = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1+2))->pLookAt;
	p4 = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1+3))->pLookAt;
	pLookAt->x = pow((1-t),3)*p1->x + 3*pow((1-t),2)*t*p2->x + 3*(1-t)*pow(t,2)*p3->x + pow(t,3)*p4->x;
	pLookAt->y = pow((1-t),3)*p1->y + 3*pow((1-t),2)*t*p2->y + 3*(1-t)*pow(t,2)*p3->y + pow(t,3)*p4->y;
	pLookAt->z = pow((1-t),3)*p1->z + 3*pow((1-t),2)*t*p2->z + 3*(1-t)*pow(t,2)*p3->z + pow(t,3)*p4->z;

	*DepthField_Aperture = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1))->DepthField_Aperture+t*(((AnimatedPosition*) m_AnimatedPath.GetAt(Point1+3))->DepthField_Aperture-((AnimatedPosition*) m_AnimatedPath.GetAt(Point1))->DepthField_Aperture);
	*DepthField_Distance = ((AnimatedPosition*) m_AnimatedPath.GetAt(Point1))->DepthField_Distance+t*(((AnimatedPosition*) m_AnimatedPath.GetAt(Point1+3))->DepthField_Distance-((AnimatedPosition*) m_AnimatedPath.GetAt(Point1))->DepthField_Distance);

	TRACE( _T("Position : %f %f %f %f %f %f\n"), pCamera->x, pCamera->y, pCamera->z, pLookAt->x, pLookAt->y, pLookAt->z );
}

// Create animation from path
//
void CHeroscapeEditor3DView::CreateAnimation( int NbFrame, int FirstFrame, int LastFrame, CString FileName, bool HighQuality )
{
	m_Mode = MODE3D_CREATE_ANIMATION;

	int EstimedRemainingTime;

	LARGE_INTEGER	CurrentTimer;
	QueryPerformanceCounter( &CurrentTimer );
	m_LastKeyTime = CurrentTimer.QuadPart;
	m_FirstKeyTime = m_LastKeyTime;

	for( int f=FirstFrame-1; f<LastFrame; f++ )
	{
		if( GetAsyncKeyState(VK_ESCAPE)&0x8000 )
			break;

		double t = ((double) f)/NbFrame;

		GetFreeAnimatedPosAtTime( t, &m_CameraPosition, &m_CameraLookAt, &(theApp.m_DepthField_Aperture), &(theApp.m_DepthField_Distance) );

		if( HighQuality )
			OnOutilsVuehautequalite();
		else
		{
			CDC* pDC = GetDC();
			RenderScene();
			SwapBuffers(pDC->GetSafeHdc());
			ReleaseDC( pDC );
		}
		// Copy from OpenGL 
		glPixelStorei( GL_PACK_ALIGNMENT, 1 );
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

		// Copy from OpenGL
		glReadBuffer( GL_FRONT );
		::glReadPixels(0,0,m_i_Width,m_i_Heigth,GL_RGB,GL_UNSIGNED_BYTE,(GLvoid*) m_pViewPoint); 
		glReadBuffer( GL_BACK );

		// Save the computed image
		CString myFileName;
		myFileName.Format( _T("%s%06i.bmp"), FileName , f+1 );

		char FileName[1000];
		size_t i;
		wcstombs_s( &i, FileName, 1000, myFileName.GetBuffer(0), 1000 );

		SaveImage( FileName );

		// Display Information

		QueryPerformanceCounter( &CurrentTimer );
		m_LastKeyTime = CurrentTimer.QuadPart;
		double ElapsedTime = (m_LastKeyTime-m_FirstKeyTime) / ((double) m_frequency);

		EstimedRemainingTime = (int) ( ElapsedTime/((double) (f-FirstFrame+2))*(LastFrame-f) );
		int PercentElapsed = (f-FirstFrame)*100/(LastFrame-FirstFrame);
		int Hour = EstimedRemainingTime/3600;
		int Minute = (EstimedRemainingTime%3600)/60;
		int Second = EstimedRemainingTime%60;
		CString InfoStr;
		CString Str;
		if( Hour>0 )
		{
			Str.LoadString( IDS_REMAINING1 );
			InfoStr.Format( Str, PercentElapsed, 37, Hour, Minute, Second );
		}
		else if( Minute>0 )
		{
			Str.LoadString( IDS_REMAINING2 );
			InfoStr.Format( Str, PercentElapsed, 37, Minute, Second );
		}
		else
		{
			Str.LoadString( IDS_REMAINING3 );
			InfoStr.Format( Str, PercentElapsed, 37, Second );
		}

		TRACE( _T("%s\n"), InfoStr );
		((CMainFrame*) theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText( 0, InfoStr );
	}
	m_Mode = MODE3D_NULL;
	CString Ready;
	Ready.LoadStringW( AFX_IDS_IDLEMESSAGE );
	((CMainFrame*) theApp.m_pMainWnd)->m_wndStatusBar.SetPaneText( 0, Ready );
}

// To know if we can create the file
//
void CHeroscapeEditor3DView::OnUpdateVideoCreateFile(CCmdUI *pCmdUI)
{
	if( m_AnimatedPositionList.GetCount()>=2 )
		pCmdUI->Enable( true );
	else
		pCmdUI->Enable( false );
}

// Create the video file
//
void CHeroscapeEditor3DView::OnVideoCreateFile()
{
	int NbFrame = 1000;
	bool HighQuality = true;

	CRenderOptionDlg Dlg;

	Dlg.m_ImageCount = theApp.m_RenderVideo_FrameCount;
	Dlg.m_FirstFrame = theApp.m_RenderVideo_FirstFrame;
	Dlg.m_LastFrame = theApp.m_RenderVideo_LastFrame;
	Dlg.m_FileName = theApp.m_RenderVideo_FileName;
	Dlg.m_HighQuality = theApp.m_RenderVideo_HighQuality;

	if( Dlg.DoModal()==IDOK )
	{
		theApp.m_RenderVideo_FrameCount = Dlg.m_ImageCount;
		theApp.m_RenderVideo_FirstFrame = Dlg.m_FirstFrame;
		theApp.m_RenderVideo_LastFrame = Dlg.m_LastFrame;
		theApp.m_RenderVideo_FileName = Dlg.m_FileName;
		theApp.m_RenderVideo_HighQuality = Dlg.m_HighQuality?true:false;

		if( Dlg.m_FirstFrame<=Dlg.m_LastFrame && Dlg.m_LastFrame<=Dlg.m_ImageCount )
		{
			ComputeAnimatedPath();
			CreateAnimation( Dlg.m_ImageCount, Dlg.m_FirstFrame, Dlg.m_LastFrame, Dlg.m_FileName, Dlg.m_HighQuality?true:false );
		}
	}
}

// To know if we can save theses positions
//
void CHeroscapeEditor3DView::OnUpdateVideoSavePosition(CCmdUI *pCmdUI)
{
	if( m_AnimatedPositionList.GetCount()>=2 )
		pCmdUI->Enable( true );
	else
		pCmdUI->Enable( false );
}

// Save the animated positions
//
void CHeroscapeEditor3DView::OnVideoSavePosition()
{
	CString Str;

	CFileDialog fd( FALSE, _T("*.ani"), 0, 4|2, _T("Animation VirtualScape (*.ani)|*.ani||") );

	if( fd.DoModal()==IDOK )
 	{
		CStdioFile f(fd.GetPathName(),CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive);
		f.Close();
		Str.Format( _T("%i"), m_AnimatedPositionList.GetCount() );
		WritePrivateProfileString( _T("General"), _T("NbKey"), Str, fd.GetPathName());
		for( int i=0; i<m_AnimatedPositionList.GetCount(); i++ )
		{
			CString KeyStr;

			AnimatedPosition* pAnimatedPosition = (AnimatedPosition*) m_AnimatedPositionList.GetAt(i);
			KeyStr.Format( _T("Key%i"), i );
			Str.Format( _T("%f"), pAnimatedPosition->pCameraPoint->x );
			WritePrivateProfileString( KeyStr, _T("Camera Position X"), Str, fd.GetPathName());
			Str.Format( _T("%f"), pAnimatedPosition->pCameraPoint->y );
			WritePrivateProfileString( KeyStr, _T("Camera Position Y"), Str, fd.GetPathName());
			Str.Format( _T("%f"), pAnimatedPosition->pCameraPoint->z );
			WritePrivateProfileString( KeyStr, _T("Camera Position Z"), Str, fd.GetPathName());
			Str.Format( _T("%f"), pAnimatedPosition->pLookAt->x );
			WritePrivateProfileString( KeyStr, _T("LookAt Position X"), Str, fd.GetPathName());
			Str.Format( _T("%f"), pAnimatedPosition->pLookAt->y );
			WritePrivateProfileString( KeyStr, _T("LookAt Position Y"), Str, fd.GetPathName());
			Str.Format( _T("%f"), pAnimatedPosition->pLookAt->z );
			WritePrivateProfileString( KeyStr, _T("LookAt Position Z"), Str, fd.GetPathName());
			Str.Format( _T("%f"), pAnimatedPosition->DepthField_Aperture );
			WritePrivateProfileString( KeyStr, _T("Depth field aperture"), Str, fd.GetPathName());
			Str.Format( _T("%f"), pAnimatedPosition->DepthField_Distance );
			WritePrivateProfileString( KeyStr, _T("Depth field distance"), Str, fd.GetPathName());
		}
	}	
}

// Load an animated file
//
void CHeroscapeEditor3DView::OnVideoLoadPosition()
{
	wchar_t Str[1000];

	CFileDialog fd( TRUE, _T("*.ani"), 0, 4|2, _T("Animation VirtualScape (*.ani)|*.ani||") );

	if( fd.DoModal()==IDOK )
	{
		FreeAnimatedPosition();

		int NbPoint = GetPrivateProfileInt( _T("General"), _T("NbKey"), 0, fd.GetPathName());
		for( int i=0; i<NbPoint; i++ )
		{
			CString KeyStr;
			KeyStr.Format( _T("Key%i"), i );

			MyPoint3D* pNewCameraPoint = new MyPoint3D();
			MyPoint3D* pNewLookAtPoint = new MyPoint3D();
			AnimatedPosition* pNewAnimatedPosition = new AnimatedPosition();

			pNewAnimatedPosition->pCameraPoint = pNewCameraPoint;
			pNewAnimatedPosition->pLookAt = pNewLookAtPoint;

			GetPrivateProfileString( KeyStr, _T("Camera Position X"), _T(""), Str, 1000, fd.GetPathName());
			pNewCameraPoint->x = _wtof(Str);
			GetPrivateProfileString( KeyStr, _T("Camera Position Y"), _T(""), Str, 1000, fd.GetPathName());
			pNewCameraPoint->y = _wtof(Str);
			GetPrivateProfileString( KeyStr, _T("Camera Position Z"), _T(""), Str, 1000, fd.GetPathName());
			pNewCameraPoint->z = _wtof(Str);
			GetPrivateProfileString( KeyStr, _T("LookAt Position X"), _T(""), Str, 1000, fd.GetPathName());
			pNewLookAtPoint->x = _wtof(Str);
			GetPrivateProfileString( KeyStr, _T("LookAt Position Y"), _T(""), Str, 1000, fd.GetPathName());
			pNewLookAtPoint->y = _wtof(Str);
			GetPrivateProfileString( KeyStr, _T("LookAt Position Z"), _T(""), Str, 1000, fd.GetPathName());
			pNewLookAtPoint->z = _wtof(Str);
			GetPrivateProfileString( KeyStr, _T("Depth field aperture"), _T(""), Str, 1000, fd.GetPathName());
			pNewAnimatedPosition->DepthField_Aperture = _wtof(Str);
			GetPrivateProfileString( KeyStr, _T("Depth field distance"), _T(""), Str, 1000, fd.GetPathName());
			pNewAnimatedPosition->DepthField_Distance = _wtof(Str);

			m_AnimatedPositionList.Add( pNewAnimatedPosition );
		}
	}
}

// To know if we can load an animated position file
//
void CHeroscapeEditor3DView::OnUpdateVideoLoadPosition(CCmdUI *pCmdUI)
{
	if( m_Mode!=MODE3D_FREE_ANIMATION && m_Mode!=MODE3D_CREATE_ANIMATION )
		pCmdUI->Enable( true );
	else
		pCmdUI->Enable( false );
}

// The user want display a topographique view
//
void CHeroscapeEditor3DView::OnOutilsVuetopographique()
{
	m_CameraForTopography = true;
	BOOL DisplayTable = theApp.m_DisplayTable;
	theApp.m_DisplayTable = false;
	RenderScene();
	theApp.m_DisplayTable = DisplayTable;
	m_CameraForTopography = false;

	double LowColorR = GetRValue(theApp.m_TopographicColorLow)/255.0;
	double LowColorG = GetGValue(theApp.m_TopographicColorLow)/255.0;
	double LowColorB = GetBValue(theApp.m_TopographicColorLow)/255.0;
	double HighColorR = GetRValue(theApp.m_TopographicColorHigh)/255.0;
	double HighColorG = GetGValue(theApp.m_TopographicColorHigh)/255.0;
	double HighColorB = GetBValue(theApp.m_TopographicColorHigh)/255.0;
	
	GLint params[4];
	glGetIntegerv( GL_VIEWPORT, params );

	GLfloat* DepthComponent = (GLfloat*) malloc( sizeof(GLfloat)*params[2]*params[3] );
	GLfloat* ColorComponent = (GLfloat*) malloc( sizeof(GLfloat)*3*params[2]*params[3] );

	glReadBuffer(GL_BACK);
	glPixelStorei( GL_PACK_ROW_LENGTH, 0 );
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	// Read all the depth component
	glReadPixels( 0, 0, params[2], params[3], GL_DEPTH_COMPONENT, GL_FLOAT, DepthComponent );
	// Read all the color component
	glReadPixels( 0, 0, params[2], params[3], GL_RGB, GL_FLOAT, ColorComponent );

	GLfloat ZMin = 1;
	GLfloat ZMax = 0;
	// Now, compute value min and max
	for( int y=0; y<params[3]; y++ )
	{
		for( int x=0; x<params[2]; x++ )
		{
			if( DepthComponent[(y*params[2]+x)]<ZMin )
				ZMin = DepthComponent[(y*params[2]+x)];
			if( DepthComponent[(y*params[2]+x)]>ZMax && DepthComponent[(y*params[2]+x)]<1.0 )
				ZMax = DepthComponent[(y*params[2]+x)];
		}
	}

	if( ZMax>ZMin || true )
	{
		double DiffColorR = LowColorR-HighColorR;
		double DiffColorG = LowColorG-HighColorG;
		double DiffColorB = LowColorB-HighColorB;

		// Now, create the frame buffer
		for( int y=0; y<params[3]; y++ )
		{
			for( int x=0; x<params[2]; x++ )
			{
				// If this is not a background point
				if( DepthComponent[(y*params[2]+x)]<1 )
				{
					double Diff = (DepthComponent[(y*params[2]+x)]-ZMin)/(ZMax-ZMin);

					// Set the component value
					ColorComponent[3*(y*params[2]+x)] = (GLfloat) (HighColorR+DiffColorR*Diff);
					ColorComponent[3*(y*params[2]+x)+1] = (GLfloat) (HighColorG+DiffColorG*Diff);
					ColorComponent[3*(y*params[2]+x)+2] = (GLfloat) (HighColorB+DiffColorB*Diff);
				}
			}
		}

		// Draw all the color component
		glDrawPixels( params[2], params[3], GL_RGB, GL_FLOAT, ColorComponent );

		SwapBuffers(m_pDC->GetSafeHdc());
	}

	free(DepthComponent);
	free(ColorComponent);
}

// L'utilisateur veut voir en stereo
//
void CHeroscapeEditor3DView::RenderStereoView()
{
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	
	GLint params[4];
	glGetIntegerv( GL_VIEWPORT, params );

	unsigned char* Component = (unsigned char*) malloc( sizeof(unsigned char)*3*params[2]*params[3] );
	GLfloat* LeftLuminance = (GLfloat*) malloc( sizeof(GLfloat)*params[2]*params[3] );
	GLfloat* RightLuminance = (GLfloat*) malloc( sizeof(GLfloat)*params[2]*params[3] );

	glPixelStorei( GL_PACK_ROW_LENGTH, 0 );
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	// Rendu de l'image gauche
	m_CameraStereoIsLeft = true;
	RenderScene();
	// Read all the color component
	glReadBuffer(GL_BACK);
	glReadPixels( 0, 0, params[2], params[3], GL_RGB, GL_UNSIGNED_BYTE, Component );
	for( int y=0; y<params[3]; y++ )
		for( int x=0; x<params[2]; x++ )
			LeftLuminance[y*params[2]+x] = (Component[(y*params[2]+x)*3]+Component[(y*params[2]+x)*3+1]+Component[(y*params[2]+x)*3+2])/3.0f/256.0f;

	// Rendu de l'image droite
	m_CameraStereoIsLeft = false;
	RenderScene();
	// Read all the color component
	glReadBuffer(GL_BACK);
	glReadPixels( 0, 0, params[2], params[3], GL_RGB, GL_UNSIGNED_BYTE, Component );
	for( int y=0; y<params[3]; y++ )
		for( int x=0; x<params[2]; x++ )
			RightLuminance[y*params[2]+x] = (Component[(y*params[2]+x)*3]+Component[(y*params[2]+x)*3+1]+Component[(y*params[2]+x)*3+2])/3.0f/256.0f;

	// Combinaison des images
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glRasterPos4d( -1, -1, 0, 1 );
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_BLEND );
	glPixelTransferf( GL_RED_SCALE, 1.0 );
	glPixelTransferf( GL_GREEN_SCALE, 0 );
	glPixelTransferf( GL_BLUE_SCALE, 0 );
	glDrawBuffer( GL_BACK );
	glDrawPixels( params[2], params[3], GL_LUMINANCE, GL_FLOAT, LeftLuminance );
	switch( theApp.m_AnaglyphiqueMode )
	{
	case 0: // red blue
		glPixelTransferf( GL_RED_SCALE, 0 );
		glPixelTransferf( GL_GREEN_SCALE, 0.0 );
		glPixelTransferf( GL_BLUE_SCALE, 1.0 );
		break;
	case 1: // red green
		glPixelTransferf( GL_RED_SCALE, 0 );
		glPixelTransferf( GL_GREEN_SCALE, 1.0 );
		glPixelTransferf( GL_BLUE_SCALE, 0.0 );
		break;
	case 2: // red cyan
		glPixelTransferf( GL_RED_SCALE, 0 );
		glPixelTransferf( GL_GREEN_SCALE, 1.0 );
		glPixelTransferf( GL_BLUE_SCALE, 1.0 );
		break;
	}
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_COLOR, GL_DST_COLOR );
	glDrawPixels( params[2], params[3], GL_LUMINANCE, GL_FLOAT, RightLuminance );
	glEnable( GL_DEPTH_TEST );
	glDisable( GL_BLEND );
	glPixelTransferf( GL_RED_SCALE, 1.0 );
	glPixelTransferf( GL_GREEN_SCALE, 1.0 );
	glPixelTransferf( GL_BLUE_SCALE, 1.0 );

	free( Component );
	free( LeftLuminance );
	free( RightLuminance );
}

// The user want chang stereoscopic display flag
//
void CHeroscapeEditor3DView::OnOutilsVuestereo()
{
	m_StereoscopicView = !m_StereoscopicView;
	if( m_StereoscopicView )
		m_RenderInterlacedStereoscopic = false;
	m_IsModified = true;
	RedrawWindow();
}

// To know if this is a stereoscopic rendering or not
//
void CHeroscapeEditor3DView::OnUpdateOutilsVuestereo(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_StereoscopicView );
}

// The user want use stereoscopic interlaced displaying
//
void CHeroscapeEditor3DView::OnOutilsVuestereointerlaced()
{
	if( m_RenderInterlacedStereoscopic )
	{
		m_RenderInterlacedStereoscopic = false;
	}
	else
	{
		m_RenderInterlacedStereoscopic = true;
		m_StereoscopicView = false;
	}
	m_IsModified = true;
	RedrawWindow();
}

// To know if this is a stereoscopic interlaced rendering or not
//
void CHeroscapeEditor3DView::OnUpdateOutilsVuestereointerlaced(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck( m_RenderInterlacedStereoscopic );
}

// Set the move position to display arrow
//
void CHeroscapeEditor3DView::SetMoveFigurePosition( int OldPosX, int OldPosY, int OldPosZ, int OldRotation, int x, int y, int z, int Rotation )
{
	m_FigureMoveBeginPosXi = OldPosX;
	m_FigureMoveBeginPosYi = OldPosY;
	m_FigureMoveBeginPosZi = OldPosZ;
	m_FigureMoveBeginRotation = OldRotation;
	m_FigureMoveEndPosXi = x;
	m_FigureMoveEndPosYi = y;
	m_FigureMoveEndPosZi = z;
	m_FigureMoveEndRotation = Rotation;

	if( OldPosY%2==1 )
	{
		m_FigureMoveBeginPosX = OldPosX*TILE3D_WIDTH+TILE3D_X3;
		m_FigureMoveBeginPosY = -OldPosY*TILE3D_HEIGHT;
		m_FigureMoveBeginPosZ = (OldPosZ+1)*TILE3D_ZHEIGHT;
	}
	else
	{
		m_FigureMoveBeginPosX = OldPosX*TILE3D_WIDTH;
		m_FigureMoveBeginPosY = -OldPosY*TILE3D_HEIGHT;
		m_FigureMoveBeginPosZ = (OldPosZ+1)*TILE3D_ZHEIGHT;
	}

	if( y%2==1 )
	{
		m_FigureMoveEndPosX = x*TILE3D_WIDTH+TILE3D_X3;
		m_FigureMoveEndPosY = -y*TILE3D_HEIGHT;
		m_FigureMoveEndPosZ = (z+1)*TILE3D_ZHEIGHT;
	}
	else
	{
		m_FigureMoveEndPosX = x*TILE3D_WIDTH;
		m_FigureMoveEndPosY = -y*TILE3D_HEIGHT;
		m_FigureMoveEndPosZ = (z+1)*TILE3D_ZHEIGHT;
	}

	m_FigureMoveArrowDistancePart1 = max(0,m_FigureMoveEndPosZ-m_FigureMoveBeginPosZ);
	m_FigureMoveArrowDistancePart2 = sqrt(pow(m_FigureMoveBeginPosX-m_FigureMoveEndPosX,2)+pow(m_FigureMoveBeginPosY-m_FigureMoveEndPosY,2))*PI/2.0;
	m_FigureMoveArrowDistancePart3 = max(0,m_FigureMoveBeginPosZ-m_FigureMoveEndPosZ);
	m_FigureMoveArrowDistance = m_FigureMoveArrowDistancePart1+m_FigureMoveArrowDistancePart2+m_FigureMoveArrowDistancePart3;
}

// Get the point at time t (between 0 and 1)
//
void CHeroscapeEditor3DView::GetPointMoveArrow( double Time, double& x, double& y, double& z )
{
	// The first part
	if( m_FigureMoveArrowDistancePart1>0 )
	{
		// The first part is a vertical part
		if( Time<=m_FigureMoveArrowDistancePart1/m_FigureMoveArrowDistance )
		{
			// We are in this part
			x = m_FigureMoveBeginPosX;
			y = m_FigureMoveBeginPosY;
			z = m_FigureMoveBeginPosZ + m_FigureMoveArrowDistancePart1*Time/(m_FigureMoveArrowDistancePart1/m_FigureMoveArrowDistance);
			return;
		}
		else
			Time -= (m_FigureMoveEndPosZ-m_FigureMoveBeginPosZ)/m_FigureMoveArrowDistance;
	}

	// The second part
	if( Time<(sqrt(pow(m_FigureMoveBeginPosX-m_FigureMoveEndPosX,2)+pow(m_FigureMoveBeginPosY-m_FigureMoveEndPosY,2))*PI/2.0)/m_FigureMoveArrowDistance )
	{
		// We are in this part
		x = m_FigureMoveBeginPosX + (1-cos(Time/(m_FigureMoveArrowDistancePart2/m_FigureMoveArrowDistance)*PI))*(m_FigureMoveEndPosX-m_FigureMoveBeginPosX)/2;
		y = m_FigureMoveBeginPosY + (1-cos(Time/(m_FigureMoveArrowDistancePart2/m_FigureMoveArrowDistance)*PI))*(m_FigureMoveEndPosY-m_FigureMoveBeginPosY)/2;
		z = max(m_FigureMoveBeginPosZ,m_FigureMoveEndPosZ)+m_FigureMoveArrowDistancePart2/4*(sin(Time/(m_FigureMoveArrowDistancePart2/m_FigureMoveArrowDistance)*PI));
		return;
	}
	else
		Time -= m_FigureMoveArrowDistancePart2/m_FigureMoveArrowDistance;

	// The third and last part
	x = m_FigureMoveEndPosX;
	y = m_FigureMoveEndPosY;
	z = m_FigureMoveBeginPosZ - m_FigureMoveArrowDistancePart3*Time/(m_FigureMoveArrowDistancePart3/m_FigureMoveArrowDistance);
}

// Render the moving arrow
//
void CHeroscapeEditor3DView::RenderMoveArrow( bool ForShadow )
{
	if( m_Mode!=MODE3D_FIGURE_MOVED_ANIMATION )
		return;

	double x,y,z;
	double Time = ((m_LastKeyTime-m_FirstKeyTime) / (double) m_frequency)/4;

	Time = Time * 2;
	if( Time>1 )
		Time = 1;

	// Compute vector for ruban width
	double xv, yv;
	if( m_FigureMoveArrowDistancePart2>0 )
	{
		double k;
		xv = m_FigureMoveBeginPosY-m_FigureMoveEndPosY;
		yv = m_FigureMoveEndPosX-m_FigureMoveBeginPosX;
		k=sqrt(xv*xv+yv*yv);
		xv /= k;
		yv /= k;
	}
	else
	{
		xv = 1;
		yv = 0;
	}

	double Width = 0.3;

	glDisable(GL_CULL_FACE);
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_LIGHTING );
	GLfloat Color[4];
	if( !ForShadow )
	{
		glGetFloatv( GL_CURRENT_COLOR, Color );
		glColor3f(0,0,1);
	}
	glBegin(GL_QUAD_STRIP);
	glNormal3d( 0, 0, 1 );
	for( double i=Time-0.001; i>=0 ; i-=0.01 )
	{
		GetPointMoveArrow( i, x, y, z );
		if( i<Time-0.05 )
		{
			glVertex3d( x+xv*Width, y+yv*Width, z );
			glVertex3d( x-xv*Width, y-yv*Width, z );
		}
		else
		{
			glVertex3d( x+xv*Width*(Time-i)*40, y+yv*Width*(Time-i)*40, z );
			glVertex3d( x-xv*Width*(Time-i)*40, y-yv*Width*(Time-i)*40, z );
			//TRACE(_T("time-i %f\n"),Time-i);
		}
	}
	GetPointMoveArrow( 0, x, y, z );
	glVertex3d( x+xv*Width, y+yv*Width, z );
	glVertex3d( x-xv*Width, y-yv*Width, z );
	glEnd();
	glEnable(GL_CULL_FACE);
	if( !ForShadow )
		glColor4fv( Color );
}

// The view has been modified
//
void CHeroscapeEditor3DView::SetModified()
{
	m_IsModified = true;
}

// To know if we can place figure on map or not
//
void CHeroscapeEditor3DView::OnUpdatePlaceFigureOnMap(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

// Set the check box
//
void CHeroscapeEditor3DView::OnUpdateDie20Faces(CCmdUI *pCmdUI)
{
	if( theApp.m_GameType==CGameDoc::GAMETYPE_EXPERT && (m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE) )
		pCmdUI->Enable();
	else
		pCmdUI->Enable( FALSE );
}

// To display if the user can clic on this item or not
//
void CHeroscapeEditor3DView::OnUpdateRemoveFigureFromMap(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

// To display if the user can clic on this item or not
//
void CHeroscapeEditor3DView::OnUpdateMoveFigure(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

// To display if the user can clic on this item or not
//
void CHeroscapeEditor3DView::OnUpdateAttackChooseFigure(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

// To display if the user can clic on this item or not
//
void CHeroscapeEditor3DView::OnUpdateDefenseDice(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

// To display if the user can clic on this item or not
//
void CHeroscapeEditor3DView::OnUpdateNextTurn(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

// To display if the user can clic on this item or not
//
void CHeroscapeEditor3DView::OnUpdateAttackDice(CCmdUI *pCmdUI)
{
	if( (theApp.m_pGameDoc->m_GameMode==CGameDoc::GAMEMODE_ATTACK_CHOOSEFIGUREENEMI && theApp.m_pGameDoc->m_FigureDefenseList.GetCount()>0) && (m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE) )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

// To display if the user can clic on this item or not
//
void CHeroscapeEditor3DView::OnUpdateReplayGame(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

// To display if the user can clic on this item or not
//
void CHeroscapeEditor3DView::OnUpdateReplayToFile(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}

// To display if the user can clic on this item or not
//
void CHeroscapeEditor3DView::OnUpdateCameraGoHome(CCmdUI *pCmdUI)
{
	if( m_Mode==MODE3D_NULL || m_Mode==MODE3D_SELECT_POSITION || m_Mode==MODE3D_SELECT_FIGURE )
		pCmdUI->Enable();
	else
		pCmdUI->Enable(FALSE);
}
