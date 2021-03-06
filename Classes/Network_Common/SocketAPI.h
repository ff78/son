
#ifndef __SOCKET_API_H__
#define __SOCKET_API_H__

// include files
#include "BaseType.h"

#if defined(YN_WINDOWS)
#include <WinSock2.h>
#elif defined(YN_LINUX)
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#endif

#ifdef YN_LINUX
#include <sys/select.h> 
#include <sys/time.h>
#endif

#define _ESIZE 256

//////////////////////////////////////////////////
//
// 
// 
// 
//
//////////////////////////////////////////////////
#if defined(YN_LINUX)
#define SOCKET int
//typedef		u_int	SOCKET;
#define     INVALID_SOCKET   -1
#define		SOCKET_ERROR	 -1

#endif

static const INT SOCKET_ERROR_WOULDBLOCK = -100;

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_in SOCKADDR_IN;
static const UINT szSOCKADDR_IN = sizeof(SOCKADDR_IN);

//////////////////////////////////////////////////////////////////////
//
// Platform Independent Socket API Collection (exception based)
//
//////////////////////////////////////////////////////////////////////

namespace SocketAPI 
{

	//
	// exception version of socket ()
	//
	SOCKET socket_ex (INT domain, INT type, INT protocol) ;


	//
	// exception version of bind ()
	//
	BOOL bind_ex (SOCKET s, const struct sockaddr* name, UINT namelen) ;


	//
	// exception version of connect ()
	//
	BOOL connect_ex (SOCKET s, const struct sockaddr* name, UINT namelen) ;

	//
	// exception version of listen ()
	//
	BOOL listen_ex (SOCKET s, UINT backlog) ;


	//
	// exception version of accept ()
	//
	SOCKET accept_ex (SOCKET s, struct sockaddr* addr, UINT* addrlen) ;


	//
	// exception version of getsockopt ()
	//
	BOOL getsockopt_ex (SOCKET s, INT level, INT optname, VOID* optval, UINT* optlen) ;

	UINT getsockopt_ex2 (SOCKET s, INT level, INT optname, VOID* optval, UINT* optlen) ;

	//
	// exception version of setsockopt ()
	//
	BOOL setsockopt_ex (SOCKET s, INT level, INT optname, const VOID* optval, UINT optlen) ;

	//
	// exception version of send()
	//
	UINT send_ex (SOCKET s, const VOID* buf, UINT len, UINT flags) ;


	//
	// exception version of sendto()
	//
	UINT sendto_ex (SOCKET s, const VOID* buf, INT len, UINT flags, const struct sockaddr* to, INT tolen) ;

	//
	// exception version of recv()
	//
	UINT recv_ex (SOCKET s, VOID* buf, UINT len, UINT flags) ;


	//
	// exception version of recvfrom()
	//
	UINT recvfrom_ex (SOCKET s, VOID* buf, INT len, UINT flags, struct sockaddr* from, UINT* fromlen) ;
	 

	//
	// exception version of closesocket() 
	//
	// *CAUTION*
	//
	// in UNIX, close() used instead
	//
	BOOL closesocket_ex (SOCKET s) ;


	//
	// exception version of ioctlsocket()
	//
	// *CAUTION*
	//
	// in UNIX, ioctl() used instead
	//
	BOOL ioctlsocket_ex (SOCKET s, LONG cmd, ULONG* argp) ;


	//
	// check if socket is nonblocking mode
	//
	BOOL getsocketnonblocking_ex (SOCKET s) ;


	//
	// make socket nonblocking mode
	//
	BOOL setsocketnonblocking_ex (SOCKET s, BOOL on) ;


	//
	// get amount of data in socket input buffer
	//
	UINT availablesocket_ex (SOCKET s) ;


	//
	// exception version of shutdown()
	//
	BOOL shutdown_ex (SOCKET s, UINT how) ;


	//
	// exception version of select()
	//
	INT select_ex (INT maxfdp1, fd_set* readset, fd_set* writeset, fd_set* exceptset, struct timeval* timeout) ;


};//end of namespace 



#endif
