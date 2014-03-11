#pragma once

class CMarquer
{
//************
// The defines
//************
protected:

//**********
// The enums
//**********
public:

//************
// The members
//************
public:
	// To know the value (0=X, 1=1, 2=2, 3=3)
	int			m_Value;
	// To know if marquer is show or not
	bool		m_IsShow;

public:

//************
// The methods
//************
public:
	// The constructor
	CMarquer( int Value );
	// The destructor
	~CMarquer(void);
};
