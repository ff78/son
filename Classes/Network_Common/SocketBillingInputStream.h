
#ifndef __SOCKETBILLINGINPUTSTREAM_H__
#define __SOCKETBILLINGINPUTSTREAM_H__

#include "BaseType.h"
#include "Socket.h"
#include "SocketInputStream.h"

class BillPacket;

class SocketBillingInputStream : public SocketInputStream
{
public :
	SocketBillingInputStream( Socket* sock, 
					   UINT BufferSize = DEFAULTSOCKETINPUTBUFFERSIZE,
					   UINT MaxBufferSize = DISCONNECTSOCKETINPUTSIZE ) ;


public :
	BOOL						ReadPacket( BillPacket* pPacket ) ;

};




#endif

