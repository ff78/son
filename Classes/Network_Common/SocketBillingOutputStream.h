

#ifndef __SOCKETBILLINGOUTPUTSTREAM_H__
#define __SOCKETBILLINGOUTPUTSTREAM_H__

#include "BaseType.h"
#include "Socket.h"
#include "SocketOutputStream.h"

class BillPacket;

class SocketBillingOutputStream : public SocketOutputStream
{
public :
	SocketBillingOutputStream( Socket* sock, 
						UINT BufferSize = DEFAULTSOCKETOUTPUTBUFFERSIZE,
						UINT MaxBufferSize = DISCONNECTSOCKETOUTPUTSIZE ) ;


public :
	BOOL						WritePacket( const BillPacket* pPacket ) ;


};




#endif

