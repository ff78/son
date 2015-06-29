
#include "NetManager.h"
#ifdef YN_WINDOWS
#include <process.h>
#else
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
//#include <sys/types.h>
#include <netinet/in.h>
#endif

#include "cocos2d.h"
USING_NS_CC;

#include "Game_Interface/game_content_interface.h"
#include "Network/msg_manager.h"

#include "Common/GameDefine.h"
#include "Player_Account/Account_Logic.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include "Item_System/Item_Desc_Config_Mgr.h"

#define MAX_CONNECT_TIME	(10*100000)		// 最长连接时间10s

CNetManager* CNetManager::s_pMe = NULL;
extern char Error[_ESIZE] ;


CNetManager::CNetManager()
	: m_SocketInputStream(&m_Socket), 
	  m_SocketOutputStream(&m_Socket),
      connect_state_(0),
      show_(true)
{
	s_pMe = this;
	m_hConnectThread = NULL;
}

CNetManager::~CNetManager()
{
}


VOID CNetManager::Initial(VOID*)
{
	// 初始化WinSock
#ifdef YN_WINDOWS
	WSADATA wsaData;
 	if(0!=WSAStartup( MAKEWORD( 2, 2 ), &wsaData) || (LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 2 ) )
	{
		WSACleanup();
		CCLOG("Could not find a usable WinSock DLL!");
		return;
	}
#endif
	m_hConnectThread = NULL;

    connect_state_ = 0;
    show_ =true;
}

bool CNetManager::connetect_to_gate(Game_Logic::Game_Interface& gm_interface)
{
    GetMe()->Initial(NULL);
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() <= 0 )
        return false;
    int port = (int)para[0];

    string ip = gm_interface.get_keyword();

    //CCLOG("connect to gate %s  %d", ip.data(), port);

    return 0 == GetMe()->real_connect(ip.data(), port) ? true : false;
   
}
bool CNetManager::connetect_to_game_server(Game_Logic::Game_Interface& gm_interface)
{
	CCLog("---------------------CNetManager::connetect_to_game_server11111111111");
   GetMe()->Initial(NULL);
    vector<uint64> para;
    gm_interface.get_para(para);
    if( para.size() <= 0 )
        return false;
    int port = (int)para[0];
	CCLog("---------------------CNetManager::connetect_to_game_server2222222222222222222");
    string ip = gm_interface.get_keyword();
	return 0 == GetMe()->real_connect(ip.data(), port) ? true : false;
}

bool CNetManager::close_server(Game_Logic::Game_Interface& gm_interface)
{
    CCLOG("CNetManager::close_server");
    GetMe()->Release();
    GetMe()->connect_state_ = 0;
    GetMe()->show_ = false;
    return true;
}

int CNetManager::send_msg( message_stream& body_ms )
{
    send_packet(&body_ms);
    return 0;
}

// Tick 主游戏流程
VOID	CNetManager::TickGameMainProcedure(VOID)
{
	//正常处理消息包
	WaitPacket();

	//定时发送心跳消息
	SendHeartBeat();
}


VOID CNetManager::WaitPacket(VOID)
{
	if(!m_Socket.isValid())
	{
        if (connect_state_ == 1)
        {
            if (show_ == true)
            {
                show_ = false;
                const char* szString = DICTIONARY_CONFIG_MGR::instance()->get_string_by_id(SERVER_DISCONNECT);
                UI_ModalDialogue_Layer::DoModal("",szString,UI_ModalDialogue_Layer::DT_OK,[]()
                {
                    Account_Logic::releaseData();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
                    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
                    return;
#endif
                    
                    Director::getInstance()->end();
                    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                    exit(0);
#endif
                }
                );

                //UI_ModalDialogue_Layer::DoModal("",szString,UI_ModalDialogue_Layer::DT_OK,Account_Logic::releaseData);
            }            
        }
        
		return;
	}
	
	//网络数据流操作
	if(!Select() || !ProcessExcept() || !ProcessInput() || !ProcessOutput())
	{
		//CEventSystem::GetMe()->PushEvent(GE_NET_CLOSE);
	}
	
	/*
	int s=Select() ;
	CCLog("--------------------s is %d",s);
	int p1=ProcessExcept();
	CCLog("--------------------p1 is %d",p1);
	int p2=ProcessInput();
	CCLog("--------------------p2 is %d",p2);
	int p3=ProcessOutput();
	CCLog("--------------------p3 is %d",p3);
	*/
	//Packet操作
	ProcessCommands( ) ;

}

VOID CNetManager::Release(VOID)
{
    CCLOG("CNetManager::Release");
	//尚有登录线程在运行,强制终止
	if(m_hConnectThread) 
	{
#ifdef YN_WINDOWS    
		TerminateThread(m_hConnectThread, 0);
		CloseHandle(m_hConnectThread); 
#else
        //CCLOG("CNetManager::Release pthread_exit");
		//pthread_exit(0);
        //CCLOG("CNetManager::Release close(m_hConnectThread)");
        //close(m_hConnectThread);
		pthread_exit(0);
#endif
	}
    m_hConnectThread = NULL;
    CCLOG("CNetManager::Release m_Socket.close");
	m_Socket.close();

    connect_state_ = 0;
    show_ = true;

#ifdef YN_WINDOWS  
	WSACleanup();
#endif  
}

VOID CNetManager::ConnectToServer(const char* szServerAddr, INT nServerPort)
{
    //CCLOG("CNetManager::ConnectToServer");
	//已经有登录线程在运行中
	if(m_hConnectThread) return;

	m_strServerAddr = szServerAddr;
	m_nServerPort	= nServerPort;

	//创建登录线程
	UINT nThreadID;
  #ifdef YN_WINDOWS
	m_hConnectThread = (HANDLE)::_beginthreadex(NULL, 0, _ConnectThread, this, CREATE_SUSPENDED|THREAD_QUERY_INFORMATION, &nThreadID );
  #else
  pthread_create(&m_hConnectThread,NULL,_ConnectThread,this);
  #endif
	if (m_hConnectThread == NULL)
	{
		CCLOG("CNetManager::ConnectToServer  Can't create connect thread!");
	}

	//开始运行登录线程
	
#ifdef YN_WINDOWS  
	ResumeThread(m_hConnectThread);
  #endif

    connect_state_ = 1;
}

int CNetManager::send_packet(message_stream* ms)
{

	//CCLOG("CNetManager::send_packet");

    if(m_Socket.isValid())
	{
        m_SocketOutputStream.Write( ms->get_ptr(), ms->length() );
		//CCLOG("CNetManager::send_packet m_SocketOutputStream.Write");
    }

    return 0;
}

#ifdef YN_WINDOWS
UINT CNetManager::_ConnectThread(LPVOID pParam)
{
	//KLAssert(pParam);
	CNetManager* pNetManager = (CNetManager*)	pParam;

	return pNetManager->ConnectThread();
}
#else
void* CNetManager::_ConnectThread(void* d)
{
   //CCLOG("CNetManager::_ConnectThread");
  CNetManager* pNetManager = (CNetManager*) d;
  pNetManager->ConnectThread();
}
#endif

//连接线程返回值
// 0  : 尚未连接
// 1  : 成功连接到服务器
// -1 : 创建SOCKET发生错误
// -2 : 无法连接到目的服务器
// -3 : 超时错误
INT CNetManager::ConnectThread(VOID)
{
    //CCLOG("ConnectThread close of socket");
	//关闭SOCKET
	m_Socket.close();
	//创建新的SOCKET
	if(!m_Socket.create()) 
	{
        CCLOG("create new socket fail");
		return -1;
	}
    
	//连接到服务器
	if(!m_Socket.connect( m_strServerAddr.c_str(), m_nServerPort ))
	{
        CCLOG("connect to server fail");
		m_Socket.close();
		return -2 ;
	}
    CCLOG("connect to server success");
#ifdef YN_LINUX
	Msg_Manager::instance()->set_nosync_send(1);

	pthread_exit(0);
#endif
	//成功连接
	return 1;
}

int	 CNetManager::real_connect(const char* ip, const int port)
{
	CCLog("------------------------------CNetManager::real_connect11111111111");
	CCLog("ConnectThread close of socket");
	//关闭SOCKET
	m_Socket.close();
	//创建新的SOCKET
	if(!m_Socket.create()) 
	{
		CCLog("create new socket fail");
		return -1;
	}
	CCLog("------------------------------CNetManager::real_connect22222222222");
    struct hostent *h;

    if(( h = gethostbyname(ip))==NULL)
    {
     CCLog("不能得到IP %s", ip);
     return -1;
    }
	CCLog("------------------------------CNetManager::real_connect33333333333");
    char real_ip[256];
    sprintf(real_ip, "%s",inet_ntoa(*((struct in_addr *)h->h_addr)));

     //CCLOG("HostName :%s/n",h->h_name);
     CCLog("IP Address :%s  port is %d",real_ip,port);

	//连接到服务器
	if(!m_Socket.connect( real_ip,  port))
	{
		
		CCLog("---------------------------------------connect to server fail");
		m_Socket.close();
		return -2 ;
	}
	CCLog("------------------------------CNetManager::real_connect444444444444444");
	CCLog("connect to server success");

    connect_state_ = 1;

    return 0;

}

BOOL CNetManager::Select(VOID)
{
    //CCLOG("CNetManager::Select");
	FD_ZERO( &m_ReadFD ) ;
	FD_ZERO( &m_WriteFD ) ;
	FD_ZERO( &m_ExceptFD ) ;

	FD_SET( m_Socket.getSOCKET(), &m_ReadFD ) ;
	FD_SET( m_Socket.getSOCKET(), &m_WriteFD ) ;
	FD_SET( m_Socket.getSOCKET(), &m_ExceptFD ) ;
	
	timeval	Timeout ;
	Timeout.tv_sec = 0 ;
	Timeout.tv_usec = 0 ;
#ifdef YN_WINDOWS
	if(SOCKET_ERROR == SocketAPI::select_ex(0 , 
										&m_ReadFD , 
										&m_WriteFD , 
										&m_ExceptFD , 
										&Timeout ) )
#else
	if(SOCKET_ERROR == SocketAPI::select_ex(m_Socket.getSOCKET()+1 ,
										&m_ReadFD , 
										&m_WriteFD , 
										&m_ExceptFD , 
										&Timeout ) )
#endif
	{
		return FALSE;
	}
	return true;
}
void CNetManager::send_output_msg(void)
{
	Msg_Data md;
	if( 0 == Msg_Manager::instance()->pop_send_msg_list(md) )
	{
		Msg_Manager::instance()->push_send_msg_to_list(md);
		 //CCLOG("CNetManager::send_output_msg size %d",md.get_size());
		 message_stream body_ms((char*)md.get_buff(), md.get_size());
		send_packet(&body_ms);
	}
	return;

}
BOOL CNetManager::ProcessInput(VOID)
{
    //CCLOG("CNetManager::ProcessInput");
	if( FD_ISSET( m_Socket.getSOCKET(), &m_ReadFD ) )
	{
        //CCLOG(" m_SocketInputStream.Fill");
		uint ret = m_SocketInputStream.Fill( ) ;
		if( (INT)ret <= SOCKET_ERROR )
		{
			CCLOG("m_SocketInputStream.Fill ret %d %s", (INT)ret, Error);
			m_Socket.close() ;
			return FALSE;
		}
	}
    //CCLOG("CNetManager::ProcessInput end");
	return true;
}

BOOL CNetManager::ProcessOutput(VOID)
{
    //CCLOG("CNetManager::ProcessOutput");
	//如果是处于等待切换场景流程中

	if( FD_ISSET( m_Socket.getSOCKET(), &m_WriteFD ) )
	{
		uint ret = m_SocketOutputStream.Flush( ) ;
		if( (INT)ret <= SOCKET_ERROR )
		{
			CCLOG("m_SocketInputStream.Fill ret %d %s", (INT)ret, Error);
			m_Socket.close() ;
           connect_state_ = 0;
           show_ = true;
			return FALSE;
		}
	}
	return true;
}

//处理消息缓冲
VOID CNetManager::ProcessInputStream(SocketInputStream& inputStream)
{
    //CCLOG("CNetManager::ProcessInputStream");

	{
         if( -1 == Msg_Manager::instance()->is_empty())
         {
            vector<uint64> para;
            Game_Logic::Game_Content_Interface::instance()->exec_interface("procmsg", para,"gate");
         }
	
	}
}


UINT CNetManager::executePacket_CPP_Exception(Packet* pPacket)
{
	

	return PACKET_EXE_CONTINUE;
}

VOID CNetManager::ProcessCommands(VOID)
{
    //CCLOG("CNetManager::ProcessCommands");
	for (int i = 0; i < 20; i++)
	{
		m_SocketInputStream.Peek(sizeof(int) );
	}
	
	ProcessInputStream(m_SocketInputStream);
}

BOOL CNetManager::ProcessExcept( )
{
	if( FD_ISSET( m_Socket.getSOCKET(), &m_ExceptFD ) )
	{

		m_Socket.close() ;
        connect_state_ = 0;
        show_ = true;
		CCLog("--------------------------CNetManager::ProcessExcept11111111111111111111");
		return FALSE;
	}
	return true;
}


VOID CNetManager::SendHeartBeat(VOID)
{
	static UINT s_dwLastSendTime = 0;
	const UINT HEART_BEAT_RATE = 60*1000;		// 1 Minutes

	//UINT dwTimeNow = CGameProcedure::s_pTimeSystem->GetTimeNow();
	//if(dwTimeNow - s_dwLastSendTime >= HEART_BEAT_RATE)
	//{
		//CGHeartBeat msg;
		//this->SendPacket(&msg);

	//	s_dwLastSendTime = dwTimeNow;
	//}
}

VOID CNetManager::Close(VOID)
{
    //CCLOG("CNetManager::Close");
	m_Socket.close();
    connect_state_ = 0;
    show_ = true;
}


