// ServerSocket.cpp : implementation file
//

#include "StdAfx.h"

#include "HeroscapeEditor.h"
#include "SocketMessageId.h"
#include "ToDedicatedServerSocket.h"

// The constructor
//
CToDedicatedServerSocket::CToDedicatedServerSocket()
{
	// No buffer now
	m_BufferSend = NULL;
	m_BufferSendSize = 0;
	m_BufferReceive = NULL;
	m_BufferReceiveSize = 0;
}

// The destructor
//
CToDedicatedServerSocket::~CToDedicatedServerSocket()
{
	if( m_BufferSend )
	{
		free( m_BufferSend );
		m_BufferSend = NULL;
	}
	if( m_BufferReceive )
	{
		free( m_BufferReceive );
		m_BufferReceive = NULL;
	}
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CToDedicatedServerSocket, CSocket)
	//{{AFX_MSG_MAP(CToDedicatedServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

// If the socket is close
//
void CToDedicatedServerSocket::OnClose(int nErrorCode) 
{
	// Call the base class
	CSocket::OnClose(nErrorCode);
}

// We receive message from other application
//
void CToDedicatedServerSocket::OnReceive(int nErrorCode) 
{
	DWORD DataToRead;
	if( IOCtl( FIONREAD, &DataToRead )!=0 )
	{
		// Read data in the buffer
		if( m_BufferReceive )
		{
			char* BufferTemp = (char*) malloc( m_BufferReceiveSize+DataToRead );
			memcpy( BufferTemp, m_BufferReceive, m_BufferReceiveSize );
			free( m_BufferReceive );
			m_BufferReceive = BufferTemp;
		}
		else
		{
			m_BufferReceive = (char*) malloc( DataToRead );
			m_BufferReceiveSize = 0;
		}

		Receive( &m_BufferReceive[m_BufferReceiveSize], DataToRead );
		m_BufferReceiveSize += DataToRead;

		// If we have the type and len of the message
		while( m_BufferReceiveSize>=sizeof(short)+sizeof(int) )
		{
			// Verify that the message is complete
			int Len;
			memcpy( &Len, &m_BufferReceive[sizeof(short)], sizeof(Len) );
			short Id;
			memcpy( &Id, m_BufferReceive, sizeof(Id) );

			//CString Str;
			//Str.Format( _T("Recu message. Taille attendu : %i / Taille recue : %i"), Len+6, m_BufferReceiveSize );
			//AfxMessageBox( Str );

			if( m_BufferReceiveSize>=(int) (Len+sizeof(short)+sizeof(int)) )
			{
				// Save the message in a file for debug
				{
					//CString Str, Str2;
					//Str.Format( _T("Message %i (len=%i) : "), (int) Id, Len );
					//for( int i=0; i<(int) (Len+sizeof(short)+sizeof(int)); i++ )
					//{
					//	Str2.Format( _T("%02x "), m_BufferReceive[i] );
					//	Str += Str2;
					//}
					//Str += _T("\n");
					//CStdioFile f(_T("c:\\tracelima.txt"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText | CFile::shareDenyWrite );
					//f.SeekToEnd();
					//f.WriteString(Str);				
					//f.Close();
				}
				ReadAMessage();
				DoEvents();
			}
			else
				break;
		}
	}

	// Call the base class
	CSocket::OnReceive(nErrorCode);
}

// Read a message
//
void CToDedicatedServerSocket::ReadAMessage()
{
	short	MessageId;
	int		Len;

	ReadType( MessageId );
	ReadType( Len );

	TRACE( _T("Server message Id %i\n"), MessageId );

	switch( MessageId )
	{
	case SMI_FROMDEDICATEDSERVER_SET_SERVER_LIST:
		if( theApp.m_pJoinGameListDlg )
		{
			theApp.m_pJoinGameListDlg->SetServerlist( this );
		}
		else
		{
			char a;
			for( int i=0; i<Len; i++ )
				ReadType( a );
		}
		break;
	default:
		{
			char a;
			for( int i=0; i<Len; i++ )
				ReadType( a );
		}
	}
}

// Send a message to the other application
//
void CToDedicatedServerSocket::SendMessage( short ID )
{
	char* Buffer = (char*) malloc( m_BufferSendSize+sizeof(short)+sizeof(int) );

	char* pBuffer = Buffer;

	memcpy( pBuffer, &ID, sizeof(ID) );
	pBuffer += sizeof(ID);
	memcpy( pBuffer, &m_BufferSendSize, sizeof(m_BufferSendSize) );
	pBuffer += sizeof(m_BufferSendSize);
	if( m_BufferSendSize>0 && m_BufferSend!=NULL )
	{
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize );
		pBuffer += m_BufferSendSize;
	}

	TRACE( _T("Taille message : %d\n"), m_BufferSendSize+sizeof(short)+sizeof(int) );

	int SizeToSend = m_BufferSendSize+sizeof(short)+sizeof(int);
	char* CurrentBuffer = Buffer;
	while( SizeToSend>0 )
	{
		if( SizeToSend>4000 )
		{
			if( Send( CurrentBuffer, 4000 )!=4000 )
			{
				SocketError();
			}
			SizeToSend -= 4000;
			CurrentBuffer += 4000;
		}
		else
		{
			if( Send( CurrentBuffer, SizeToSend  )!=SizeToSend )
			{
				SocketError();
			}
			CurrentBuffer += SizeToSend;
			SizeToSend = 0;
		}
		DoEvents();
	}

	_flushall();

	free( Buffer );
}

// A Do event
//
void CToDedicatedServerSocket::DoEvents(void)
{
	MSG	msg;

	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

// Read a short
//
void CToDedicatedServerSocket::ReadType( short& s )
{
	memcpy( &s, m_BufferReceive, sizeof(s) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(s) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(s)], m_BufferReceiveSize-sizeof(s) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(s);
}

// Read a char
//
void CToDedicatedServerSocket::ReadType( char& c )
{
	memcpy( &c, m_BufferReceive, sizeof(c) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(c) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(c)], m_BufferReceiveSize-sizeof(c) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(c);
}

// Read a double
//
void CToDedicatedServerSocket::ReadType( double& d )
{
	memcpy( &d, m_BufferReceive, sizeof(d) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(d) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(d)], m_BufferReceiveSize-sizeof(d) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(d);
}

// Read a double array
//
void CToDedicatedServerSocket::ReadType( double* d, int Size )
{

	memcpy( d, m_BufferReceive, sizeof(double)*Size );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(double)*Size );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(double)*Size], m_BufferReceiveSize-sizeof(double)*Size );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(double)*Size;
}

// Read a int64
//
void CToDedicatedServerSocket::ReadType( __int64& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a int
//
void CToDedicatedServerSocket::ReadType( int& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a UINT
//
void CToDedicatedServerSocket::ReadType( UINT& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a LONG
//
void CToDedicatedServerSocket::ReadType( LONG& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a BYTE
//
void CToDedicatedServerSocket::ReadType( BYTE& i )
{
	memcpy( &i, m_BufferReceive, sizeof(i) );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-sizeof(i) );
	memcpy( BufferTemp, &m_BufferReceive[sizeof(i)], m_BufferReceiveSize-sizeof(i) );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= sizeof(i);
}

// Read a string
//
void CToDedicatedServerSocket::ReadType( CString& Str )
{
	short	Len;
	ReadType( Len );

	char* Buf = (char*) malloc(Len+1);
	if( Buf==NULL )
	{
		CString Str;
		Str.Format( _T("La tentative d'allouer %i octets à échouée"), Len );
		AfxMessageBox( Str );
		return;
	}
	memcpy( Buf, m_BufferReceive, Len );
	Buf[Len] = 0;

	Str = Buf;

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-Len );
	memcpy( BufferTemp, &m_BufferReceive[Len], m_BufferReceiveSize-Len );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= Len;
	free( Buf );
}

// Read datas
//
void CToDedicatedServerSocket::ReadDatas( char* pBuf, int Size )
{
	memcpy( pBuf, m_BufferReceive, Size );

	char* BufferTemp = (char*) malloc( m_BufferReceiveSize-Size );
	memcpy( BufferTemp, &m_BufferReceive[Size], m_BufferReceiveSize-Size );
	free( m_BufferReceive );
	m_BufferReceive = BufferTemp;
	m_BufferReceiveSize -= Size;
}

// Create a Buffer for send data
//
void CToDedicatedServerSocket::CreateBuffer()
{
	if( m_BufferSend )
	{
		free( m_BufferSend );
		m_BufferSend = NULL;
	}
	m_BufferSendSize = 0;
}

// Write a short
//
void CToDedicatedServerSocket::WriteType( short s )
{
	m_BufferSendSize += sizeof(s);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(s) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(short), &s, sizeof(s) );
}

// Write a int64
//
void CToDedicatedServerSocket::WriteType( __int64 i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(__int64) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(__int64), &i, sizeof(i) );
}

// Write a double
//
void CToDedicatedServerSocket::WriteType( double d )
{
	m_BufferSendSize += sizeof(d);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(d) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(d), &d, sizeof(d) );
}

// Write a int
//
void CToDedicatedServerSocket::WriteType( int i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(i) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(i), &i, sizeof(i) );
}

// Write a UINT
//
void CToDedicatedServerSocket::WriteType( UINT i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(i) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(i), &i, sizeof(i) );
}

// Write a LONG
//
void CToDedicatedServerSocket::WriteType( LONG i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(i) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(i), &i, sizeof(i) );
}

// Write a BYTE
//
void CToDedicatedServerSocket::WriteType( BYTE i )
{
	m_BufferSendSize += sizeof(i);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(i) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(i), &i, sizeof(i) );
}

// Write a char
//
void CToDedicatedServerSocket::WriteType( char c )
{
	m_BufferSendSize += sizeof(c);
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-sizeof(c) );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-sizeof(c), &c, sizeof(c) );
}

// Write a CString
//
void CToDedicatedServerSocket::WriteType( CString Str )
{
	short Len = Str.GetLength();
	WriteType( Len );
	m_BufferSendSize += Str.GetLength();
	char* pStr = theApp.GetAsciiString( Str );
	if( m_BufferSend )
	{
		char* pBuffer = (char*) malloc( m_BufferSendSize );
		memcpy( pBuffer, m_BufferSend, m_BufferSendSize-Str.GetLength() );
		free( m_BufferSend );
		m_BufferSend = pBuffer;
	}
	else
	{
		m_BufferSend = (char*) malloc( m_BufferSendSize );
	}
	memcpy( m_BufferSend+m_BufferSendSize-Str.GetLength(), pStr, Str.GetLength() );
	free( pStr );
}

// An error occur (display the error)
//
void CToDedicatedServerSocket::SocketError()
{
	CString Str;
	int SocketError = GetLastError();

	switch( SocketError )
	{
	case WSANOTINITIALISED:
		Str = "A successful AfxSocketInit must occur before using this API.";
		break;
	case WSAENETDOWN:
		Str = "The Windows Sockets implementation detected that the network subsystem failed.";
		break;
	case WSAENOTCONN:
		Str = "The socket is not connected.";
		break;
	case WSAEINPROGRESS:
		Str = "A blocking Windows Sockets operation is in progress.";
		break;
	case WSAENOTSOCK:
		Str = "The descriptor is not a socket.";
		break;
	case WSAEOPNOTSUPP:
		Str = "MSG_OOB was specified, but the socket is not of type SOCK_STREAM.";
		break;
	case WSAESHUTDOWN:
		Str = "The socket has been shut down; it is not possible to call Receive on a socket after ShutDown has been invoked with nHow set to 0 or 2.";
		break;
	case WSAEWOULDBLOCK:
		Str = "The socket is marked as nonblocking and the Receive operation would block.";
		break;
	case WSAEMSGSIZE:
		Str = "The datagram was too large to fit into the specified buffer and was truncated.";
		break;
	case WSAEINVAL:
		Str = "The socket has not been bound with Bind.";
		break;
	case WSAECONNABORTED:
		Str = "The virtual circuit was aborted due to timeout or other failure.";
		break;
	case WSAECONNRESET:
		Str = "The virtual circuit was reset by the remote side.";
		break;
	default:
		Str.Format( _T("A unknown socket error occur : %i"), SocketError );
	}
	//AfxMessageBox( Str );
}
