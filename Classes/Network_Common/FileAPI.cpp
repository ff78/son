//////////////////////////////////////////////////////////////////////
//
// FileAPI.cpp
//
// by Jack
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////
// include files
//////////////////////////////////////////////////

#include "FileAPI.h"


#if YN_WINDOWS
#include <io.h>			// for _open()
#include <fcntl.h>		// for _open()/_close()/_read()/_write()...
#include <string.h>		// for memcpy()
#elif YN_LINUX
#include <sys/types.h>	// for open()
#include <sys/stat.h>	// for open()
#include <unistd.h>		// for fcntl()
#include <fcntl.h>		// for fcntl()
#include <sys/ioctl.h>	// for ioctl()
#include <errno.h>		// for errno
#endif


//////////////////////////////////////////////////
// external variables
//////////////////////////////////////////////////
#if YN_LINUX
//extern int errno;
#endif

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
INT FileAPI::open_ex ( const CHAR * filename , INT flags ) 
{

#if YN_LINUX
	INT fd = open(filename,flags);
#elif YN_WINDOWS
	INT fd = _open(filename,flags);
#endif
	if ( fd < 0 ) {

#if YN_LINUX
		switch ( errno ) {
		case EEXIST : 
		case ENOENT  : 
		case EISDIR : 
		case EACCES : 
		case ENAMETOOLONG : 
		case ENOTDIR : 
		case ENXIO   : 
		case ENODEV  : 
		case EROFS   : 
		case ETXTBSY : 
		case EFAULT  : 
		case ELOOP   : 
		case ENOSPC  : 
		case ENOMEM  : 
		case EMFILE  : 
		case ENFILE  : 
		default :
			{
				break;
			}
		}//end of switch
#elif YN_WINDOWS
	// ...
#endif
	}

	return fd;

}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
INT FileAPI::open_ex ( const CHAR * filename , INT flags , INT mode ) 
{

#if YN_LINUX
	INT fd = open(filename,flags,mode);
#elif YN_WINDOWS
	INT fd = _open(filename,flags,mode);
#endif

	if ( fd < 0 ) {
#if YN_LINUX
		switch ( errno ) {
		case EEXIST : 
		case EISDIR : 
		case EACCES : 
		case ENAMETOOLONG : 
		case ENOENT  : 
		case ENOTDIR : 
		case ENXIO   : 
		case ENODEV  : 
		case EROFS   : 
		case ETXTBSY : 
		case EFAULT  : 
		case ELOOP   : 
		case ENOSPC  : 
		case ENOMEM  : 
		case EMFILE  : 
		case ENFILE  : 
		default :
			{
				break;
			}
		}//end of switch
#elif YN_WINDOWS
	// ...
#endif
	}

	return fd;

}


//////////////////////////////////////////////////////////////////////
//
// UINT FileAPI::read_ex ( INT fd , VOID * buf , UINT len ) 
//
//
// exception version of read()
//
// Parameters 
//     fd  - file descriptor
//     buf - reading buffer
//     len - reading length
//
// Return
//     length of reading bytes
//
//
//////////////////////////////////////////////////////////////////////
UINT FileAPI::read_ex ( INT fd , VOID * buf , UINT len ) 
{

#if YN_LINUX
	INT result = read ( fd , buf , len );
#elif YN_WINDOWS
	INT result = _read ( fd , buf , len );
#endif

	if ( result < 0 ) {

#if YN_LINUX
		switch ( errno ) {
			case EINTR : 
			case EAGAIN : 
			case EBADF : 
			case EIO : 
			case EISDIR : 
			case EINVAL : 
			case EFAULT : 
			case ECONNRESET :
			default : 
				{
					break;
				}
		}
#elif YN_WINDOWS
	// ...
#endif
	} else if ( result == 0 ) {
	}

	return result;

}

//////////////////////////////////////////////////////////////////////
//
// UINT FileAPI::write_ex ( INT fd , VOID * buf , UINT len ) 
//
//
// exception version of write()
//
// Parameters 
//     fd  - file descriptor
//     buf - writing buffer
//     len - writing length
//
// Return
//     length of reading bytes
//
//
//////////////////////////////////////////////////////////////////////
UINT FileAPI::write_ex ( INT fd , const VOID * buf , UINT len ) 
{

#if YN_LINUX
	INT result = write ( fd , buf , len );
#elif YN_WINDOWS
	INT result = _write ( fd , buf , len );
#endif

	if ( result < 0 ) {
		
#if YN_LINUX
		switch ( errno ) {
			case EAGAIN : 
			case EINTR : 
			case EBADF : 
			case EPIPE : 
			case EINVAL: 
			case EFAULT: 
			case ENOSPC : 
			case EIO : 
			case ECONNRESET :
			default : 
				{
					break;
				}
		}
#elif YN_WINDOWS
	//...
#endif
	}

	return result;

}


//////////////////////////////////////////////////////////////////////
//
// VOID FileAPI::close_ex ( INT fd ) 
//
//
// exception version of close()
//
// Parameters
//     fd - file descriptor
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
VOID FileAPI::close_ex ( INT fd ) 
{
#if YN_WINDOWS
	if ( _close(fd) < 0 ) {
#elif YN_LINUX
	if ( close(fd) < 0 ) {
#endif
#if YN_LINUX
		switch ( errno ) {
			case EBADF : 
			default :
				{
					break;
				}
		}
#elif YN_WINDOWS
#endif
	}

}

//////////////////////////////////////////////////////////////////////
//
// INT FileAPI::fcntl_ex ( INT fd , INT cmd ) 
//
//
// Parameters
//     fd  - file descriptor
//     cmd - file control command
//
// Return
//     various according to cmd
//
//
//////////////////////////////////////////////////////////////////////
INT FileAPI::fcntl_ex ( INT fd , INT cmd ) 
{

#if YN_LINUX
	INT result = fcntl ( fd , cmd );
	if ( result < 0 ) {
		switch ( errno ) {
			case EINTR : 
			case EBADF : 
			case EACCES : 
			case EAGAIN : 
			case EDEADLK : 
			case EMFILE  : 
			case ENOLCK : 
			default : 
				{
					break;
				}
		}
	}
	return result;
#elif YN_WINDOWS
	return 0 ;
#endif

}

//////////////////////////////////////////////////////////////////////
//
// INT FileAPI::fcntl_ex ( INT fd , INT cmd , LONG arg ) 
//
//
// Parameters
//     fd  - file descriptor
//     cmd - file control command
//     arg - command argument
//
// Return
//     various according to cmd
//
//
//////////////////////////////////////////////////////////////////////
INT FileAPI::fcntl_ex ( INT fd , INT cmd , LONG arg ) 
{

#if YN_LINUX
	INT result = fcntl ( fd , cmd , arg );
	if ( result < 0 ) {
		switch ( errno ) {
			case EINTR : 
			case EINVAL : 
			case EBADF : 
			case EACCES : 
			case EAGAIN : 
			case EDEADLK : 
			case EMFILE  : 
			case ENOLCK : 
			default : 
				{
					break;
				}
		}
	}
	return result;
#elif YN_WINDOWS
	return 0 ;
#endif

}


//////////////////////////////////////////////////////////////////////
//
// BOOL getfilenonblocking_ex ( INT fd ) 
//
//
// check if this file is nonblocking mode
//
// Parameters
//     fd - file descriptor
//
// Return
//     TRUE if nonblocking, FALSE if blocking
//
//
//////////////////////////////////////////////////////////////////////
BOOL FileAPI::getfilenonblocking_ex ( INT fd ) 
{

#if YN_LINUX
	INT flags = fcntl_ex( fd , F_GETFL , 0 );
	return flags | O_NONBLOCK;
#elif YN_WINDOWS
	return FALSE;
#endif

}

//////////////////////////////////////////////////////////////////////
//
// VOID setfilenonblocking_ex ( INT fd , BOOL on ) 
//
//
// make this file blocking/nonblocking
//
// Parameters
//     fd - file descriptor
//     on - TRUE if nonblocking, FALSE if blocking
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
VOID FileAPI::setfilenonblocking_ex ( INT fd , BOOL on ) 
{

#if YN_LINUX
	INT flags = fcntl_ex( fd , F_GETFL , 0 );

	if ( on )
		// make nonblocking fd
		flags |= O_NONBLOCK;
	else
		// make blocking fd
		flags &= ~O_NONBLOCK;

	fcntl_ex( fd , F_SETFL , flags );
#elif YN_WINDOWS
#endif

}

//////////////////////////////////////////////////////////////////////
//
// VOID FileAPI::ioctl_ex ( INT fd , INT request , VOID * argp )
//
//
// exception version of ioctl()
//
// Parameters
//     fd      - file descriptor
//     request - i/o control request
//     argp    - argument
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
VOID FileAPI::ioctl_ex ( INT fd , INT request , VOID * argp )
{

#if YN_LINUX
	if ( ioctl(fd,request,argp) < 0 ) {
		switch ( errno ) {
		case EBADF : 
		case ENOTTY : 
		case EINVAL : 
		default :
			{
				break;
			}
		}
	}
#elif YN_WINDOWS
#endif

}



//////////////////////////////////////////////////////////////////////
//
// VOID FileAPI::setfilenonblocking_ex2 ( INT fd , BOOL on )
//
//
// make this stream blocking/nonblocking using ioctl_ex()
//
// Parameters
//     fd - file descriptor
//     on - TRUE if nonblocking, FALSE else
//
// Return
//     none
//
//
//////////////////////////////////////////////////////////////////////
VOID FileAPI::setfilenonblocking_ex2 ( INT fd , BOOL on )
{

#if YN_LINUX
	ULONG arg = ( on == TRUE ? 1 : 0 );
	ioctl_ex(fd,FIONBIO,&arg);
#elif YN_WINDOWS
#endif

}


//////////////////////////////////////////////////////////////////////
//
// UINT FileAPI::available_ex ( INT fd )
//
//
// how much bytes available in this stream? using ioctl_ex()
//
// Parameters
//     fd - file descriptor
//
// Return
//     #bytes available
//
//
//////////////////////////////////////////////////////////////////////
UINT FileAPI::availablefile_ex ( INT fd )
{

#if YN_LINUX
	UINT arg = 0;
	ioctl_ex(fd,FIONREAD,&arg);
	return arg;
#elif YN_WINDOWS
	return 0;
#endif

}


//////////////////////////////////////////////////////////////////////
//
// INT FileAPI::dup_ex ( INT fd )
//
//
//////////////////////////////////////////////////////////////////////
INT FileAPI::dup_ex ( INT fd )
{

#if YN_LINUX
	INT newfd = dup(fd);
#elif YN_WINDOWS
	INT newfd = _dup(fd);
#endif

	if ( newfd < 0 ) {
#if YN_LINUX
		switch ( errno ) {
		case EBADF : 
		case EMFILE : 
		default :
			{
				break;
			}
		}//end of switch
#elif YN_WINDOWS
#endif
	}

	return newfd;

}


//////////////////////////////////////////////////////////////////////
//
// LONG FileAPI::lseek_ex ( INT fd , LONG offset , INT whence )
//
//
//////////////////////////////////////////////////////////////////////
LONG FileAPI::lseek_ex ( INT fd , LONG offset , INT whence )
{

#if YN_LINUX
	LONG result = lseek(fd,offset,whence);
	if ( result < 0 ) {
		switch ( errno ) {
		case EBADF : 
		case ESPIPE : 
		case EINVAL : 
		default :
			{
				break;
			}
		}
	}
#elif YN_WINDOWS
	LONG result = _lseek(fd,offset,whence);
	if ( result < 0 ) {
	}
#endif

	return result;


}

LONG FileAPI::tell_ex( INT fd )
{

#if YN_LINUX
	LONG result;
#elif YN_WINDOWS
	LONG result = _tell(fd);
	if ( result < 0 ) {
	}
#endif

	return result ;

}

