// Object3D.h: interface for the CObject3D class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

// Open GL
#include <GL/gl.h> 
#include <GL/glu.h> 
#include <GL/glaux.h> 

#include "General.h"
#include "Point.h"

// The CObject3D Class
//
class CObject3D  
{
#define	MAX_SUBOBJECT 5000

//************
// Les membres
//************

public:
	// The translation
	Point3D				m_Translation;
	// The rotation
	double				m_Rotate;
	// The scale height
	double				m_ScaleHeight;
	// The scale
	double				m_Scale;

protected:
	// Name of the objects
	CString				m_ObjectName[MAX_SUBOBJECT];
	// Real Name of the objects
	CString				m_ObjectRealName[MAX_SUBOBJECT];
	// Vertex
	GLfloat*			m_GlVtx[MAX_SUBOBJECT];
	// Normal
	GLfloat*			m_GlNormal[MAX_SUBOBJECT];
	// Texture
	GLfloat*			m_GlTexture[MAX_SUBOBJECT];
	// Nbr of vertex
	int					m_i_NbrVtx[MAX_SUBOBJECT];
	// Les id de texture
	GLuint				m_TextureId[MAX_SUBOBJECT];
	// Les liste d'objet
	GLuint				m_GeomListe[MAX_SUBOBJECT];
	// Le chromage de chaque object
	GLfloat				m_f_ObjectChrome[MAX_SUBOBJECT];
	// Le reflet de chaque object
	GLfloat				m_f_ObjectReflect[MAX_SUBOBJECT];
	// La transparence de chaque object
	GLfloat				m_f_ObjectTransparency[MAX_SUBOBJECT];
	// The Object speciality
	int					m_i_Speciality[MAX_SUBOBJECT];
	// Number of sub object
	int					m_i_NbrObject;
	// The Type of Object
	int					m_i_Type;
	// The object name
	CString				m_Name;

public:
	// The object size
	double				m_Width, m_Height, m_Depth;
	// The bounding Box of the object
	double				m_XMin, m_XMax, m_YMin, m_YMax, m_ZMin, m_ZMax;

//*************
// Les methodes
//*************
public:
	// The constructor with texture display or not
	CObject3D();
	// The destructor
	virtual ~CObject3D();
	// Do Frame 
	void Render( bool BindTexture );
	// Load an sgl file
	void LoadSgl( CString FileName );
	// Create the lists
	void CreateList();
	// Return the translation of the object
	Point3D GetTranslation() { return m_Translation; }
	// set the translation
	void SetTranslation( double x, double y, double z );
	// Return the name of the object
	CString	GetName() { return m_Name; }
	// Compute the vectorial product
	void ComputeVectorialProduct( double Vx1, double Vy1, double Vz1, double Vx2, double Vy2, double Vz2, double& Vx, double& Vy, double& Vz );
	// Draw the object as exploded point
	void RenderAsExplodedPoint( double ExplodedSize );
	// Render the selected state
	void RenderSelected();

//************************
// Les fonctions statiques
//************************
public:
};

#endif // #ifndef _OBJECT3D_H_
