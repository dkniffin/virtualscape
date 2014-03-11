// MySocket.cpp : implementation file
//

#include "StdAfx.h"

#include "ConnexionSocket.h"
#include "MySocket.h"
#include "SocketMessageId.h"
#include "VirtualScapeDedicatedServer.h"

extern CVirtualScapeDedicatedServerApp theApp;

// The constructor
//
CConnexionSocket::CConnexionSocket()
{
	// No buffer now
	m_BufferSend = NULL;
	m_BufferSendSize = 0;
	m_BufferReceive = NULL;
	m_BufferReceiveSize = 0;
}

// The destructor
//
CConnexionSocket::~CConnexionSocket()
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
BEGIN_MESSAGE_MAP(CConnexionSocket, CSocket)
	//{{AFX_MSG_MAP(CConnexionSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

// If the socket is close
//
void CConnexionSocket::OnClose(int nErrorCode) 
{
	// Call the base class
	CSocket::OnClose(nErrorCode);
}

// We receive message from other application
//
void CConnexionSocket::OnReceive(int nErrorCode) 
{
	CString IP;
	UINT	Port;

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

		ReceiveFrom( &m_BufferReceive[m_BufferReceiveSize], DataToRead, IP, Port );
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
				ReadAMessage( IP, Port );
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
void CConnexionSocket::ReadAMessage( CString IP, int Port )
{
	short	MessageId;
	int		Len;

	ReadType( MessageId );
	ReadType( Len );

	switch( MessageId )
	{
	case SMI_TOSERVER_SEARCH_SERVER:
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
void CConnexionSocket::SendMessage( short ID )
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

	Send( Buffer, m_BufferSendSize+sizeof(short)+sizeof(int)  );

	free( Buffer );
}

// Send a message to the other application
//
void CConnexionSocket::SendMessageTo( short ID, int Port, CString IP )
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

	SendTo( Buffer, m_BufferSendSize+sizeof(short)+sizeof(int), Port, IP  );

	free( Buffer );
}

// Read a short
//
void CConnexionSocket::ReadType( short& s )
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
void CConnexionSocket::ReadType( char& c )
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
void CConnexionSocket::ReadType( double& d )
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
void CConnexionSocket::ReadType( double* d, int Size )
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
void CConnexionSocket::ReadType( __int64& i )
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
void CConnexionSocket::ReadType( int& i )
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
void CConnexionSocket::ReadType( UINT& i )
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
void CConnexionSocket::ReadType( LONG& i )
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
void CConnexionSocket::ReadType( BYTE& i )
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
void CConnexionSocket::ReadType( CString& Str )
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
void CConnexionSocket::ReadDatas( char* pBuf, int Size )
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
void CConnexionSocket::CreateBuffer()
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
void CConnexionSocket::WriteType( short s )
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
void CConnexionSocket::WriteType( __int64 i )
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
void CConnexionSocket::WriteType( double d )
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
void CConnexionSocket::WriteType( int i )
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
void CConnexionSocket::WriteType( UINT i )
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
void CConnexionSocket::WriteType( LONG i )
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
void CConnexionSocket::WriteType( BYTE i )
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
void CConnexionSocket::WriteType( char c )
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

// Create a char* from a unicode CString
//
char* CConnexionSocket::GetAsciiString( CString Str )
{
	char* NewStr = (char*) malloc(Str.GetLength()+1);

	for( int i=0; i<Str.GetLength(); i++ )
	{
		unsigned short us = _mbbtombc( Str.GetAt(i) );
		if( us<256 )
			NewStr[i] = (char) us;
		else
			NewStr[i] = ' ';
	}
	NewStr[Str.GetLength()] = 0;

	return NewStr;
}

// Write a CString
//
void CConnexionSocket::WriteType( CString Str )
{
	short Len = Str.GetLength();
	WriteType( Len );
	m_BufferSendSize += Str.GetLength();
	char* pStr = GetAsciiString( Str );
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
void CConnexionSocket::SocketError()
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

	AfxMessageBox( Str );
}

// A client ask a connexion
//
void CConnexionSocket::OnAccept(int nErrorCode)
{
	// Create a new socket
	CMySocket* pSocket = new CMySocket;
	if( Accept( *pSocket )==0 )
		SocketError();

	pSocket->AsyncSelect();
	// This new socket is add to the list
	//theApp.AddSocket( pSocket );

	// Call the base code
	CSocket::OnAccept(nErrorCode);
}
