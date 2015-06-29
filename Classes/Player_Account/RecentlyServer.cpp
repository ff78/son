#include "RecentlyServer.h"
RecentlyServer::RecentlyServer(void)
{
}


RecentlyServer::~RecentlyServer(void)
{
}
Server_List_Data RecentlyServer::getRecentlyServerInfomation(int index)
{
	Server_List_Data ret;
	ret.reset();
	if(index>=3)
		return ret;
	//��ȡid
	char textid[64]={0};
	SPRINTF(textid,"ID%d",index);
	ret.set_id(UserDefault::getInstance()->getIntegerForKey(textid,0));
	//��ȡservername
	char textservername[64]={0};
	SPRINTF(textservername,"SERVERNAME%d",index);
	ret.set_server_name(UserDefault::getInstance()->getStringForKey(textservername,std::string("")).c_str());
	//��ȡserverip
	char textserverip[64]={0};
	SPRINTF(textserverip,"SERVERIP%d",index);
	ret.set_server_ip(UserDefault::getInstance()->getStringForKey(textserverip,std::string("")).c_str());
	//��ȡ�˿ں�
	char textserverport[64]={0};
	SPRINTF(textserverport,"SERVERPORT%d",index);
	ret.set_server_port(UserDefault::getInstance()->getIntegerForKey(textserverport,0));
	//���nextui
	char textnextui[64]={0};
	SPRINTF(textnextui,"NEXTUI%d",index);
	ret.set_next_ui(UserDefault::getInstance()->getIntegerForKey(textnextui,0));
	//��ȡ��������״̬
	char textstate[64]={0};
	SPRINTF(textstate,"SERVERSTATE%d",index);
	ret.set_state(UserDefault::getInstance()->getIntegerForKey(textstate,-1));
	return ret;

}

void RecentlyServer::addServer(Server_List_Data sld)
{

	//��ȡserver2�����ݣ��ŵ�server3��
	Server_List_Data sld1=getRecentlyServerInfomation(1);
	
	//��ȡserver1�����ݣ��ŵ�server2��
	Server_List_Data sld0=getRecentlyServerInfomation(0);

	if(sld.get_id()==sld0.get_id())
	{
		return;
	}
	if(sld.get_id()==sld1.get_id())
	{
		//����������
		setServerData(0,sld);
		setServerData(1,sld0);


		return;
	}

	setServerData(2,sld1);
	setServerData(1,sld0);
	//����server1������
	setServerData(0,sld);

}
void RecentlyServer::setServerData(int index,Server_List_Data sld)
{
	if(index>=3)
		return;


	//����id
	char textid[64]={0};
	SPRINTF(textid,"ID%d",index);
	UserDefault::getInstance()->setIntegerForKey(textid,sld.get_id());
	//����servername
	char textservername[64]={0};
	SPRINTF(textservername,"SERVERNAME%d",index);
	UserDefault::getInstance()->setStringForKey(textservername,sld.get_server_name());
	//����serverip
	char textserverip[64]={0};
	SPRINTF(textserverip,"SERVERIP%d",index);
	UserDefault::getInstance()->setStringForKey(textserverip,sld.get_server_ip());
	//���ö˿�
	char textserverport[64]={0};
	SPRINTF(textserverport,"SERVERPORT%d",index);
	UserDefault::getInstance()->setIntegerForKey(textserverport,sld.get_server_port());
	//����nextui
	char textnextui[64]={0};
	SPRINTF(textnextui,"NEXTUI%d",index);
	UserDefault::getInstance()->setIntegerForKey(textnextui,sld.get_next_ui());
	//���÷�����״̬
	char textstate[64]={0};
	SPRINTF(textstate,"SERVERSTATE%d",index);
	UserDefault::getInstance()->setIntegerForKey(textstate,sld.get_state());
	//ˢ����
	UserDefault::getInstance()->flush();


}

bool RecentlyServer::getBackgroundMusicState()
{
	bool ret=true;
	ret=UserDefault::getInstance()->getBoolForKey("BACKGROUNDMUSICSTATE",true);
	return ret;
}
void RecentlyServer::setBackgroundMusicStateAndBehavior(bool value)
{
	UserDefault::getInstance()->setBoolForKey("BACKGROUNDMUSICSTATE",value);
	UserDefault::getInstance()->flush();
	if(value)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
	

}
bool RecentlyServer::getEffectState()
{
	bool ret=true;
	ret=UserDefault::getInstance()->getBoolForKey("EFFECTSTATE",true);
	return ret;
}
void RecentlyServer::setEffectStateAndBehavior(bool value)
{
	UserDefault::getInstance()->setBoolForKey("EFFECTSTATE",value);
	UserDefault::getInstance()->flush();
	if(value)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	}
}
bool RecentlyServer::getShieldState()
{
	bool ret=true;
	ret=UserDefault::getInstance()->getBoolForKey("SHIELDSTATE",true);
	return ret;
}
void RecentlyServer::setShieldState(bool value)
{

	UserDefault::getInstance()->setBoolForKey("SHIELDSTATE",value);
	UserDefault::getInstance()->flush();
}
int RecentlyServer::getBackgroundMusicValue()
{
	int ret=100;
	ret=UserDefault::getInstance()->getIntegerForKey("BACKGROUNDMUSICVALUE",100);
	return ret;
}
void RecentlyServer::setBackgroundMusicValue(int value)
{
	UserDefault::getInstance()->setIntegerForKey("BACKGROUNDMUSICVALUE",value);
	UserDefault::getInstance()->flush();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(value/100.0f);

}
int RecentlyServer::getEffectValue()
{
	int ret=100;
	ret=UserDefault::getInstance()->getIntegerForKey("EFFECTVALUE",100);
	return ret;
}
void RecentlyServer::setEffectValue(int value)
{
	UserDefault::getInstance()->setIntegerForKey("EFFECTVALUE",value);
	UserDefault::getInstance()->flush();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(value/100.0f);
}
int RecentlyServer::effectvalue=100;
int RecentlyServer::musicvalue=100;
bool RecentlyServer::music=true;
bool RecentlyServer::effect=true;
