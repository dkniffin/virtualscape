#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_

class CClientSocket : public CSocket
{
//*************
// The defines
//*************

//*************
// The members
//*************
protected:
	// Buffer for create message to send
	char*	m_BufferSend;
	// The buffer size
	int		m_BufferSendSize;
	// Buffer for reception
	char*	m_BufferReceive;
	// The receive buffer size
	int		m_BufferReceiveSize;
	// The replay buffer size
	char	m_ReplayBuffer[1000000];
	// The current replay position in the buffer
	int		m_ReplayPosition;
	// To know if we are in replay mode
	bool	m_ReplayMode;
	// To save replay as picture
	int		m_CurrentImage;
	// To know if replay must be done at high speed
	bool	m_ReplayHighSpeed;
	// To know if we must replay to file or to view
	bool	m_ReplayToFile;
	// The replay File
	CString m_ReplayFile;

//*************
// The methods
//*************
public:
	// The constructor
	CClientSocket();
	// The destructor
	virtual ~CClientSocket();
	// Send a message to the other application
	void	SendMessage( short ID );
	// Send a message to the other application
	void	SendMessageTo( short ID, int Port, CString* IP );
	// Read a short
	void	ReadType( short& s );
	// Read a char
	void	ReadType( char& c );
	// Read a double
	void	ReadType( double& d );
	// Read a double array
	void	ReadType( double* d, int Size );
	// Read a int64
	void	ReadType( __int64& i );
	// Read a int
	void	ReadType( int& i );
	// Read a UINT
	void	ReadType( UINT& i );
	// Read a LONG
	void	ReadType( LONG& i );
	// Read a BYTE
	void	ReadType( BYTE& i );
	// Read a string
	void	ReadType( CString& Str );
	// Read datas
	void	ReadDatas( char* pBuf, int Size );
	// Create a Buffer for send data
	void	CreateBuffer();
	// Write a short
	void	WriteType( short s );
	// Write a int64
	void	WriteType( __int64 i );
	// Write a double
	void	WriteType( double d );
	// Write a int
	void	WriteType( int i );
	// Write a UINT
	void	WriteType( UINT i );
	// Write a LONG
	void	WriteType( LONG i );
	// Write a BYTE
	void	WriteType( BYTE i );
	// Write a char
	void	WriteType( char c );
	// Write a CString
	void	WriteType( CString Str );
	// An error occur (display the error)
	void	SocketError();
	// Launch a replay
	void	Replay( bool ReplayToFile, CString ReplayFile=_T("") );
	// Show next replay
	void	NextReplay();

protected:
	// Read a message
	void	ReadAMessage( CString IP, int Port );
	// Wait that the view is ready for next replay
	void	WaitViewReady( void* pGameView );
	// Wait that the view is ready for next replay and save picture to file
	void	WaitViewReadyToFile( void* pGameView );
	// A Do event
	void	DoEvents(void);

//******************
// Generate by VC++
//******************
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
public:
	virtual void OnConnect(int nErrorCode);
public:
	virtual void OnAccept(int nErrorCode);
};

#endif // #ifndef _CLIENTSOCKET_H_
