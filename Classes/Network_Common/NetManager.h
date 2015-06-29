
/** 网络管理器
 */

#pragma once

#ifdef YN_WINDOWS
#include <Winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

#include <string>

#include "Socket.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "Packet.h"
#include "message_stream.h"

#ifdef YN_LINUX
#include <sys/select.h> 
#include <sys/time.h>
#endif


#define VOID			void			//标准空
typedef unsigned char	UCHAR;			//标准无符号CHAR
typedef char			CHAR;			//标准CHAR
typedef unsigned int	UINT;			//标准无符号INT
typedef int				INT;			//标准INT
typedef unsigned short	USHORT;			//标准无符号short
typedef short			SHORT;			//标准short
typedef unsigned long	ULONG;			//标准无符号LONG(不推荐使用)
typedef long			LONG;			//标准LONG(不推荐使用)
typedef float			FLOAT;			//标准float

typedef UCHAR			uchar;
typedef USHORT			ushort;
typedef UINT			uint;
typedef ULONG			ulong;
typedef ULONG			IP_t;
typedef USHORT			PacketID_t;
typedef INT				BOOL;
typedef UCHAR			BYTE;
typedef	BYTE			BPacketID_t;

typedef USHORT			PacketID_t;
#define PACKET_HEADER_SIZE (sizeof(PacketID_t)+sizeof(UINT))

/// 网络管理器
namespace Game_Logic
{
    struct Game_Interface;
}
class message_stream;
class CNetManager 
{
public:

    static bool connetect_to_gate(Game_Logic::Game_Interface& gm_interface);
    static bool connetect_to_game_server(Game_Logic::Game_Interface& gm_interface);

    static bool close_server(Game_Logic::Game_Interface& gm_interface);

    int         send_msg( message_stream& body_ms );

	/// 连接到服务器
	VOID		ConnectToServer(const char* szServerAddr, INT nServerPort);

    int			send_packet(message_stream* ms);
	//断开连接
	VOID		Close(VOID);
	//处理消息缓冲
	VOID		ProcessInputStream(SocketInputStream& inputStream);
	//得到消息工厂

    UINT        executePacket_CPP_Exception(Packet* pPacket);
public:

	//节点初始化
	virtual VOID	Initial(VOID*);
	//释放自己所所拥有的资源
	virtual VOID	Release(VOID);

public:

public:

	enum NETMANAGER_STATUS
	{
		CONNECT_SUCESS  = 0,
		CONNECT_FAILED_CREATE_SOCKET_ERROR,
		CONNECT_FAILED_CONNECT_ERROR,
		CONNECT_FAILED_TIME_OUT,

	};

	//--------------------------------------------------------------------------------------------------------------
	//
	// Tick不同的游戏流程
	//

	// Tick 主游戏流程
	VOID	TickGameMainProcedure();



public:
	CNetManager();
	virtual ~CNetManager();
	static CNetManager* GetMe(VOID) { return s_pMe; }
	VOID				WaitPacket(VOID);
	void				send_output_msg(void);
protected:
	//连接线程,专门用来连接服务器用
#ifdef YN_WINDOWS  
	static UINT CALLBACK	_ConnectThread(LPVOID pParam);
#else
  static void* _ConnectThread( void* );
#endif
	INT				ConnectThread(VOID);

	int			real_connect(const char* ip, const int port);
	//连接线程句柄
#ifdef YN_WINDOWS  
	HANDLE			m_hConnectThread;
#else
  pthread_t  m_hConnectThread;
#endif
	UINT			m_timeConnectBegin;

private:

	VOID				WaitConnecting(VOID);

	VOID				SendHeartBeat(VOID);

	//SOCKET操作集
	BOOL				Select(VOID);
	BOOL				ProcessExcept(VOID);
	BOOL				ProcessInput(VOID);
	BOOL				ProcessOutput(VOID);
	VOID				ProcessCommands(VOID);


	//消息包执行

protected:
	static CNetManager*		s_pMe;
	///服务器信息
	std::string				m_strServerAddr;
	INT						m_nServerPort;

private:
	//可读句柄
	fd_set					m_ReadFD;
	//可写句柄
	fd_set					m_WriteFD;
	//异常句柄
	fd_set					m_ExceptFD;
	///SOCKET
	Socket					m_Socket;
	///输入缓冲区
	SocketInputStream		m_SocketInputStream;
	///输出缓冲区
	SocketOutputStream		m_SocketOutputStream;
	//SOCKET包管理器

    int                     connect_state_;
    bool                    show_;

};
