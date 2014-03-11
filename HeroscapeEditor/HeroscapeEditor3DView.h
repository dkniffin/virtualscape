// HeroscapeEditor3DView.h : interface of the CHeroscapeEditor3DView class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _HEROSCAPEEDITOR3DVIEW_H_
#define _HEROSCAPEEDITOR3DVIEW_H_

#include "FigureObject.h"
#include "General.h"
#include "HeroscapeEditorDoc.h"
#include "Maths\Matrix4x4.h"
#include "Object3D.h"
#include "shared/pbuffer.h"

// Definition de la classe CHeroscapeEditor3DView
//
class CHeroscapeEditor3DView : public CView
{

//**********
// The enums
//**********

public:
// The mode
enum WindowMode
{
	MODE3D_NULL = 0,
	MODE3D_TURN_AROUND,
	MODE3D_CONSTRUCTION,
	MODE3D_FREE_ANIMATION,
	MODE3D_CREATE_ANIMATION,
	MODE3D_SELECT_POSITION,
	MODE3D_FIGURE_PLACED_ANIMATION,
	MODE3D_SELECT_FIGURE,
	MODE3D_FIGURE_REMOVED_ANIMATION,
	MODE3D_FIGURE_MOVED_ANIMATION,
	MODE3D_ATTACK_ANIMATION,
	MODE3D_DEFENSE_ANIMATION
};

// The turn around mode
enum TurnAroundMode
{
	MTA_PLAY = 0,
	MTA_PAUSE,
	MTA_REVERSE
};

typedef struct AnimatedPosition
{
	MyPoint3D*	pCameraPoint;
	MyPoint3D*	pLookAt;
	double		DepthField_Aperture;
	double		DepthField_Distance;
};

//************
// The members
//************
protected:
	// Le device context
	CClientDC   *m_pDC;
	CDC			*m_pDC2;
	// Ancienne taille de la fenetre
	CRect       m_oldRect;
	// La palette
	CPalette    m_cPalette;
	// L'ancienne palette
	CPalette    *m_pOldPalette;
	// For OpenGL
	HGLRC		m_hRC;
	HGLRC		m_hRC2;
	// The horizontal angle of point of view of the camera
	double		m_CameraAngleH;
	// The vertical angle of point of view of the camera
	double		m_CameraAngleV;
	// The old mouse position
	CPoint		m_OldMousePosition;
	// The current mouse position
	CPoint		m_CurrentMousePosition;
	// The size of shadow map
	int			m_ShadowMapSize;
	// The shadow map texture
	GLuint		m_ShadowMapTexture;
	// Some matrix
	MATRIX4X4	m_LightProjectionMatrix, m_LightViewMatrix;
	MATRIX4X4	m_CameraProjectionMatrix, m_CameraViewMatrix;
	VECTOR3D	m_LightPosition;
	// To know if we must display or not the shadow
	bool		m_DisplayShadow;
	// the box coordinate under battlefield
	MyPoint3D	m_Box1, m_Box2;
	MyPoint3D	m_CenterOfBattleField;
	// To know if the shadow is initialise
	bool		m_ComputeShadowIsInitialise;
	// To know if we are in move mode
	bool		m_IsMove;
	PBuffer*	m_pBuffer;
	// For construction mode
	int			m_LastLevelToDisplay;
	// For turn around
	double		m_FirstAngleTurnArround;
	// the turn around mode
	TurnAroundMode	m_ModeTurnAround;
	// The personal texture list
	CPtrArray	m_PersonalTextureList;
	// The texture list
	CPtrArray	m_TextureList;
	// The glyph texture list
	CPtrArray	m_GlyphTextureList;
	// The Figure object list
	CPtrArray	m_FigureObjectList;
	// To know if the scene is modified
	bool		m_IsModified;
	// The Camera Position list for animation or video file
	CPtrArray	m_AnimatedPositionList;
	// The animated path
	CPtrArray	m_AnimatedPath;
	// Memorise the app parameters
	double		m_Backup_DepthField_Aperture;
	double		m_Backup_DepthField_Distance;
	// To know if this is a normal camera or topographic camera
	bool		m_CameraForTopography;
	// To know if this is a rendering for stereo
	bool		m_StereoscopicView;
	// To know if this is an interlaced stereoscopic rendering
	bool		m_RenderInterlacedStereoscopic;
	// To know if this is a stereo rendering for left image
	bool		m_CameraStereoIsLeft;
	// The focus distance for stereoscopique camera
	double		m_CameraStereoFocusDistance;
	// In select mode, display mouse position
	int			m_DisplayPositionX,m_DisplayPositionY,m_DisplayPositionZ;
	// To know if select mode need one or two case
	bool		m_DisplayPositionTwoCase;
	// The current selected figure
	CFigureObject*	m_pSelectedFigure;

public:
	// The frequency of the counter
	__int64		m_frequency;
	// The last key time test
	__int64		m_LastKeyTime;
	// The first key time for various animations
	__int64		m_FirstKeyTime;
	// To know the window mode
	int			m_Mode;
	// The textures for 3DView
	GLuint		m_TextureIdGroundSide;
	GLuint		m_TextureIdBox;
	GLuint		m_TextureIdAttack;
	GLuint		m_TextureIdDefense;
	// The objects for 3D view
	CObject3D*	m_pTree10;
	CObject3D*	m_pTree11;
	CObject3D*	m_pTree12;
	CObject3D*	m_pTree15;
	CObject3D*	m_pRuin2;
	CObject3D*	m_pRuin3;
	CObject3D*	m_pGlacier1;
	CObject3D*	m_pGlacier3;
	CObject3D*	m_pGlacier4;
	CObject3D*	m_pGlacier6;
	CObject3D*	m_pHive6;
	CObject3D*	m_pWall4;
	CObject3D*	m_pCastleBaseEnd;
	CObject3D*	m_pCastleBaseStraight;
	CObject3D*	m_pCastleBaseCorner;
	CObject3D*	m_pCastleWallCorner;
	CObject3D*	m_pCastleWallStraight;
	CObject3D*	m_pCastleWallEnd;
	CObject3D*	m_pCastleBattlement;
	CObject3D*	m_pCastleDoor;
	CObject3D*	m_pCastleArch;
	CObject3D*	m_pCastleLadder;
	CObject3D*	m_pCastleFlag;
	CObject3D*	m_pMarvelRuin6;
	CObject3D*	m_pMarvelRuin6Breaked;
	CObject3D*	m_pPalm1;
	CObject3D*	m_pTicallaGrass1;
	CObject3D*	m_pOutcrop1;
	CObject3D*	m_pOutcrop3;
	// the tile list
	GLint		m_TileUpDownGLList;
	GLint		m_TileSideGLList;
	// The array with image view
	UCHAR*		m_pViewPoint;
	// The window size
	int			m_i_Width;
	int			m_i_Heigth;
	// The camera position
	MyPoint3D	m_CameraPosition;
	// The camera look at
	MyPoint3D	m_CameraLookAt;
	// The begining point for a move figure
	int			m_FigureMoveBeginPosXi,m_FigureMoveBeginPosYi,m_FigureMoveBeginPosZi,m_FigureMoveBeginRotation;
	double		m_FigureMoveBeginPosX,m_FigureMoveBeginPosY,m_FigureMoveBeginPosZ;
	// The ending point for a move figure
	int			m_FigureMoveEndPosXi,m_FigureMoveEndPosYi,m_FigureMoveEndPosZi,m_FigureMoveEndRotation;
	double		m_FigureMoveEndPosX,m_FigureMoveEndPosY,m_FigureMoveEndPosZ;
	// Distance between begin and end
	double		m_FigureMoveArrowDistance,m_FigureMoveArrowDistancePart1,m_FigureMoveArrowDistancePart2,m_FigureMoveArrowDistancePart3;
	// To know if the mouse has been moved until left button down
	bool		m_MouseMoveUntilLButtonDown;
	// To know the rotation of the display position (0-5)
	int			m_DisplayPositionRotation;
	// To know if we are in replay mode or not
	bool		m_IsReplayMode;

//************
// The methods
//************
public:
	// Le constructeur
	CHeroscapeEditor3DView();
	// Le destructeur
	virtual ~CHeroscapeEditor3DView();
	// Apres que la fenetre soit cree
	void					AfterCreate();
	// Initialise OpenGl
	void					Init();
	// The document data have been update so recompute
	virtual void			UpdateData1();
	// The document data have been update so recompute
	virtual void			UpdateData2();
	// Compute shadow
	bool					ComputeShadow();
	// Positionne le Pixel Format
	BOOL					bSetupPixelFormat();
	// Creer la palette
	void					CreateRGBPalette();
	// Utilise pour la creation du pixel descriptor/palette
	unsigned char			ComponentFromIndex(int i, UINT nbits, UINT shift);
	// Start rendering.
	void					RenderScene( bool ForHighQuality=false );
	// Display a position
	void					DisplayPosition();
	// Return the document
	CHeroscapeEditorDoc*	GetDocument() const;
	// Compute and set the view matrix
	void					ViewMatrix();
	// Compute and set the view matrix for right stereo eye
	void					ViewMatrixStereoRight();
	// The lightening
	void					Lightening();
	// Load all the texture useful for the 3D View
	void					LoadTextures();
	// Load all the 3d objects
	void					LoadObjects();
	// Verify if we move the view with key
	bool					VerifyKey( __int64 TimeDif );
	// Render box under battlefield
	void					RenderBox( bool BindTexture );
	// Compute auto move
	bool					ComputeMoveAuto(  );
	// Compute the weapons position
	bool					ComputeWeapons();
	// Display formatted text with getlasterror()
	void					DisplayError();
	// Free memory used by view point
	void					FreeViewPoint();
	// Create the tile list
	void					CreateList();
	// Get the Id of the personal texture (or -1 if file not found)
	GLuint					GetPersonalTextureId( CString FileName );
	// Get the Id of the texture (or -1 if file not found)
	GLuint					GetTextureId( CString FileName, int Alpha );
	// Get the Id of the glyph texture (or -1 if file not found)
	GLuint					GetGlyphTextureId( CString FileName );
	// Get the Object3D for a particular figure
	CObject3D*				GetFigureObject( CString FigureName );
	// Save image in memory
	void					SaveImageInMemory();
	// Compute the animated path for free animation
	void					ComputeAnimatedPath( bool Closed=true );
	// Free memory for animated path
	void					FreeAnimatedPath();
	// Free memory for animated position
	void					FreeAnimatedPosition();
	// Obtient la position de la camera et de la vue a un temps donné
	void					GetFreeAnimatedPosAtTime( double myTime, MyPoint3D* pCamera, MyPoint3D* pLookAt, double* DepthField_Aperture, double* DepthField_Distance );
	// Create animation from path
	void					CreateAnimation( int NbFrame, int FirstFrame, int LastFrame, CString FileName, bool HighQuality );
	// Save the frame buffer in an image
	void					SaveImage( char* FileName );
	// Render a stereo view
	void					RenderStereoView();
	// Play animation
	void					MoveFigurePlacedRealtime();
	// Play animation
	void					MoveFigureRemovedRealtime();
	// Play animation
	void					MoveFigureMovedRealtime();
	// Play animation
	void					AttackRealtime();
	// Play animation
	void					DefenseRealtime();
	// Set the move position to display arrow
	void					SetMoveFigurePosition( int OldPosX, int OldPosY, int OldPosZ, int OldRotation, int x, int y, int z, int Rotation );
	// Render the moving arrow
	void					RenderMoveArrow( bool ForShadow );
	// Get the point at time t (between 0 and 1)
	void					GetPointMoveArrow( double Time, double& x, double& y, double& z );
	// The view has been modified
	void					SetModified();

//***********************
// Generate by Visual C++
//***********************

DECLARE_DYNCREATE(CHeroscapeEditor3DView)

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeroscapeEditor3DView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation

// Generated message map functions
protected:
	//{{AFX_MSG(CHeroscapeEditor3DView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	virtual void OnInitialUpdate();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	afx_msg void OnToolbar3dDisplayshadow();
public:
	afx_msg void OnUpdateToolbar3dDisplayshadow(CCmdUI *pCmdUI);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnOutilsVuehautequalite();
public:
	afx_msg virtual void OnCameraGoHome();
public:
	afx_msg void OnOutilsTourneautour();
public:
	afx_msg void OnUpdateOutilsTourneautour(CCmdUI *pCmdUI);
public:
	afx_msg void OnOutilsVoirlaconstruction();
public:
	afx_msg void OnUpdateOutilsVoirlaconstruction(CCmdUI *pCmdUI);
public:
	afx_msg void OnUpdateOutilsVuehautequalite(CCmdUI *pCmdUI);
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
public:
	afx_msg void OnOutilsSaveimage();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUpdateVideoEraseAllPosition(CCmdUI *pCmdUI);
	afx_msg void OnVideoEraseAllPosition();
	afx_msg void OnVideoAddCurrentPosition();
	afx_msg void OnUpdateVideoAddCurrentPosition(CCmdUI *pCmdUI);
	afx_msg void OnUpdateVideoMoveRealtime(CCmdUI *pCmdUI);
	afx_msg void OnVideoMoveRealtime();
	afx_msg void OnUpdateVideoCreateFile(CCmdUI *pCmdUI);
	afx_msg void OnVideoCreateFile();
	afx_msg void OnUpdateVideoSavePosition(CCmdUI *pCmdUI);
	afx_msg void OnVideoSavePosition();
	afx_msg void OnVideoLoadPosition();
	afx_msg void OnUpdateVideoLoadPosition(CCmdUI *pCmdUI);
	afx_msg void OnOutilsVuetopographique();
	afx_msg void OnOutilsVuestereo();
	afx_msg void OnUpdateOutilsVuestereo(CCmdUI *pCmdUI);
	afx_msg void OnOutilsVuestereointerlaced();
	afx_msg void OnUpdateOutilsVuestereointerlaced(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaceFigureOnMap(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRemoveFigureFromMap(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMoveFigure(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAttackChooseFigure(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDefenseDice(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNextTurn(CCmdUI *pCmdUI);
	afx_msg void OnUpdateAttackDice(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReplayGame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateReplayToFile(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCameraGoHome(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDie20Faces(CCmdUI *pCmdUI);
};

inline CHeroscapeEditorDoc* CHeroscapeEditor3DView::GetDocument() const { return reinterpret_cast<CHeroscapeEditorDoc*>(m_pDocument); }

#endif // #ifndef _HEROSCAPEEDITOR3DVIEW_H_
