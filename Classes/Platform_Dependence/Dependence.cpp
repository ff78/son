#include "Dependence.h"
#include "cocos2d.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Player_Account/Account_Data.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
USING_NS_CC;
#include "Player_Account/Account_Data_Mgr.h"
#include "Update_Logic/UpdateData.h"
#include "Update_Logic/UpdateManager.h"
#include "UI/DownLoading_Layer.h"
#include "Update_Logic/MessageInfo.h"
#include "Update_Logic/UpdateHelper.h"
#include "Player_Account/Account_Msg_Proc.h"
#include "Player_Account/RecentlyServer.h"
#include "Game_Interface/game_content_interface.h"
#include "Item_System/Item_Desc_Config_Mgr.h"
#include "UI_Interface/UI_ModalDialogue_Layer.h"
#include  "Common/GameDefine.h"
//#include "UI/Actor.h"
//#include "AI_System/Game_Utils.h"
#include "UI/Login_Scene.h"
extern "C"
{
	void Java_org_cocos2dx_pa_MyApiCallback_sendkey(JNIEnv*	env,jobject jj,jstring tokenid,jstring devicename,jstring deviceversion,jstring clientversion,jint apn,jstring imei,jstring macaddress)
	{
		const char* strid;
		const char* strdevname;
		const char* strdevversion;
		const char* strcliversion;
		const char* strimei;
		const char* strmacaddress;
		int iapn=apn;

		jboolean iscopy;
		CCLog("--------------------tokenid");
		strid = env->GetStringUTFChars(tokenid,&iscopy);
		strdevname=env->GetStringUTFChars(devicename,&iscopy);
		strdevversion=env->GetStringUTFChars(deviceversion,&iscopy);
		strcliversion=env->GetStringUTFChars(clientversion,&iscopy);
		strimei=env->GetStringUTFChars(imei,&iscopy);
		strmacaddress=env->GetStringUTFChars(macaddress,&iscopy);



		Account_Msg_Proc::save_android_property(std::string(strid),std::string(strdevname),std::string(strdevversion),std::string(strcliversion),iapn,strimei,strmacaddress);
		CCLog("-------------------------->>>save tokenid  successed!");
	
//		Login_Scene* ls=Login_Scene::sharedInstance();
//		if(ls)
//		{
//			ls->sendMessage(Login_Scene::EVENT_TYPE_LOGIN_SUCCEED);
//		}
//		Dependence::checkUpdate();


		



	}
}
extern "C"
{
	void Java_org_cocos2dx_pa_MyApiCallback_sendLoginFailed(JNIEnv*env,jobject jj)
	{
		Scene* sc=Director::getInstance()->getRunningScene();
		if(sc)
		{
			sc->setVisible(true);
		}
	}
}

extern "C"
{
	void Java_org_cocos2dx_pa_paladin_sendJson(JNIEnv* env,jobject jj,jstring str)
	{

	


		jboolean iscopy;
		const char* jsonstrchar = env->GetStringUTFChars(str,&iscopy);
		CCLog("------------------------------jstring value %s",jsonstrchar);
		if(strlen(jsonstrchar)<=0)
		{
			/*
			CCLog("---------------------auto login------------------------------- ");
			Server_List_Data temp=RecentlyServer::getRecentlyServerInfomation(0);
			int id=temp.get_id();
			if(id!=0)
			{
				vector<uint64> para;
				para.push_back(id);
				if(!Game_Logic::Game_Content_Interface::instance()->exec_interface("connecttogate", para))
				{

				}
			}
			*/
			//没有更新，发送消息
//			Login_Scene* ls=Login_Scene::sharedInstance();
//			if(ls)
//			{
//				ls->sendMessage(Login_Scene::EVENT_TYPE_NO_UPDATE);
//				ls->sendMessage(Login_Scene::EVENT_TYPE_OBTAIN_SERVER);
//				CCLog("-------------string is null,so don't have update");
//			}

			return;
		}



		int isNeedUpdate = UpDateData::NO_NEW_VERSION;
		string strstring(jsonstrchar);
		isNeedUpdate = UpDateData::sharedInstance()->init(strstring);
		if (isNeedUpdate == UpDateData::HAVE_NEW_VERSION) //有新版本进入更新下载页面
		{
			/*
			
			*/
//			Login_Scene* ls=Login_Scene::sharedInstance();
//			if(ls)
//			{
//				ls->sendMessage(Login_Scene::EVENT_TYPE_HAVE_UPDATE);
//				CCLog("---------------------have update");
//				//ls->sendMessage(Login_Scene::EVENT_TYPE_NO_UPDATE);
//				//ls->sendMessage(Login_Scene::EVENT_TYPE_OBTAIN_SERVER);
//			}
		}
		else
		{
			/*
			CCLog("---------------------auto login------------------------------- ");
			Server_List_Data temp=RecentlyServer::getRecentlyServerInfomation(0);
			int id=temp.get_id();
			if(id!=0)
			{
				vector<uint64> para;
				para.push_back(id);
				if(!Game_Logic::Game_Content_Interface::instance()->exec_interface("connecttogate", para))
				{

				}
			}
			*/
//			Login_Scene* ls=Login_Scene::sharedInstance();
//			if(ls)
//			{
//				ls->sendMessage(Login_Scene::EVENT_TYPE_NO_UPDATE);
//				ls->sendMessage(Login_Scene::EVENT_TYPE_OBTAIN_SERVER);
//			}
		}



	}
}

void Dependence::checkUpdate()
{


	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","checkUpdate", "(Ljava/lang/String;)V");
	if (!isHave)
	{
		CCLog("jni:not exist");
	}
	else
	{
		CCLog("jni:exist");        //调用此函数
		jstring jstr=minfo.env->NewStringUTF("0.62");
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jstr);
	}

}
void Dependence::showLogin()
{
	CCLog("-------------------->not in 9191919191991919");
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","login", "()V");
	if (!isHave)
	{
		CCLog("jni:not exist");
	}
	else
	{
		CCLog("jni:exist");        //调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}

}


string Dependence::getResourcesSearchPath()
{
	JniMethodInfo minfo;
	string datapath="/mnt/sdcard/jieji/data";
	bool isHave =JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","getWorkingDir", "()Ljava/lang/String;");
	if (isHave) 
	{
		jstring temppath=(jstring)minfo.env -> CallStaticObjectMethod(minfo.classID,minfo.methodID);
		jboolean isCopy;
		datapath=string(minfo.env->GetStringUTFChars(temppath,&isCopy));
		CCLog("path----------------------------->%s",datapath.c_str());
	}
	else
	{
		CCLog("have no getTempDir");
	}
	return datapath;
}
void Dependence::setGameInfoWhenLoginDone(string serverId,string roleName)
{
	CCLog("-------------->jni serverId is %s",serverId.c_str());
	CCLog("--------------->jni rolename is %s",roleName.c_str());
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","loginDone", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (!isHave)
	{
		CCLog("setGameInfoWhenLoginDone jni:not exist");
	}
	else
	{
		CCLog("setGameInfoWhenLoginDone jni:exist");        //调用此函数
		jstring jserverId=minfo.env->NewStringUTF(serverId.c_str());
		jstring jroleName=minfo.env->NewStringUTF(roleName.c_str());
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jserverId,jroleName);
	}
}
void Dependence::showGameCenter()
{
	CCLog("-------------------->not in 9191919191991919");
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","showGameCenter", "()V");
	if (!isHave)
	{
		CCLog("jni:not exist");
	}
	else
	{
		CCLog("jni:exist");        //调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
}
void Dependence::setUpdateState(int state)
{

	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","updateState", "(I)V");
	if (!isHave)
	{
		CCLog("jni:deleteSOFile not exist ");
	}
	else
	{
		CCLog("jni:deleteSOFile exist");        //调用此函数
		jint info=state;
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,info);
	}
}
void Dependence::installAPK()
{
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","installAPK", "()V");
	if (!isHave)
	{
		CCLog("jni:deleteSOFile not exist ");
	}
	else
	{
		CCLog("jni:deleteSOFile exist");        //调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
}
void Dependence::reboot()
{
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","reboot", "()V");
	if (!isHave)
	{
		CCLog("jni:reboot not exist ");
	}
	else
	{
		CCLog("jni:reboot exist");        //调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
}
void Dependence::downloadedFile(string respath,string md5,string filename)
{
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","downloadedFile", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
	if (!isHave)
	{
		CCLog("jni:not exist");
	}
	else
	{
		CCLog("jni:exist");        //调用此函数
		jstring jrespath=minfo.env->NewStringUTF(respath.c_str());
		jstring jmd5=minfo.env->NewStringUTF(md5.c_str());
		jstring jfilename=minfo.env->NewStringUTF(filename.c_str());
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,jrespath,jmd5,jfilename);
	}
}

void Dependence::deleteZIP()
{
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","deleteZip", "()V");
	if (!isHave)
	{
		CCLog("jni:deleteZip not exist ");
	}
	else
	{
		CCLog("jni:deleteZip exist");        //调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
}
void Dependence::deleteSO()
{
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","deleteSOFile", "()V");
	if (!isHave)
	{
		CCLog("jni:deleteSOFile not exist ");
	}
	else
	{
		CCLog("jni:deleteSOFile exist");        //调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
}
string Dependence::getTempDir()
{
	string ret;
	JniMethodInfo minfo;
	bool isHave =JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","getTempDir", "()Ljava/lang/String;");
	if (isHave) 
	{
		jstring temppath=(jstring)minfo.env -> CallStaticObjectMethod(minfo.classID,minfo.methodID);
		jboolean isCopy;
		ret=string(minfo.env->GetStringUTFChars(temppath,&isCopy));
	}
	else
	{
		CCLog("have no getTempDir");
	}
	return ret;
}
void Dependence::showAd()
{
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","showAD", "()V");
	if (!isHave)
	{
		CCLog("jni:showAD not exist ");
	}
	else
	{
		CCLog("jni:showAD exist");        //调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
}
string Dependence::getWorkingDir()
{
	string ret;
	JniMethodInfo minfore;
	bool isHavere =JniHelper::getStaticMethodInfo(minfore,"org/cocos2dx/cpp/Depend", "getResSdPath", "()Ljava/lang/String;");
	if (isHavere) 
	{
		jstring temppathre=(jstring)minfore.env -> CallStaticObjectMethod(minfore.classID,minfore.methodID);
		jboolean isCopyre;
		ret=string(minfore.env->GetStringUTFChars(temppathre,&isCopyre));
	}
	else
	{
		CCLog("have no getWorkingDir");
	}
	return ret;
}

void Dependence::removeData()
{
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","removeData", "()V");
	if (!isHave)
	{
		CCLog("jni:removeData not exist ");
	}
	else
	{
		CCLog("jni:removeData exist");        //调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
}
void Dependence::showNetworkFailed()
{
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","showNetworkFailed", "()V");
	if (!isHave)
	{
		CCLog("jni:showNetworkFailed not exist ");
	}
	else
	{
		CCLog("jni:showNetworkFailed exist");        //调用此函数
		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
	}
}
bool Dependence::isWiFiConnected()
{
	jboolean ret=0;
	JniMethodInfo minfo;//定义Jni函数信息结构体     
	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","isWiFiConnected", "()Z");
	if (!isHave)
	{
		CCLog("jni:isWiFiConnected not exist ");
	}
	else
	{
		CCLog("jni:isWiFiConnected exist");        //调用此函数
		ret=minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
	}
	CCLog("-------------WIFI is %d",ret);
	return ret;
}
string Dependence::getLogoName()
{
	string str="ui/Loading/logo_for_windows.png";
    CCLog("%s",str.c_str());
	return str;
}
void Dependence::showPay()
{
//	UI::Actor* actor = Game_Utils::instance()->get_primary_actor();
//	int role_id=actor->sprite_id();
//	const char* role_name=actor->get_name();
//	std::string server_id=Account_Msg_Proc::server_id_save;
//	std::string nnUid=Account_Msg_Proc::nn_uid;
//	std::string server_name=Account_Msg_Proc::server_name_save;
//
//
//
//	JniMethodInfo minfo;//定义Jni函数信息结构体     
//	bool isHave = JniHelper::getStaticMethodInfo(minfo,"org/cocos2dx/pa/paladin","showPay", "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
//	if (!isHave)
//	{
//		CCLog("jni:showPay not exist ");
//	}
//	else
//	{
//		CCLog("jni:showPay exist");        //调用此函数
//		jstring roleName=minfo.env->NewStringUTF(role_name);
//		jstring serverId=minfo.env->NewStringUTF(server_id.c_str());
//		jstring NNUID=minfo.env->NewStringUTF(nnUid.c_str());
//		jstring serverName=minfo.env->NewStringUTF(server_name.c_str());
//
//		minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID,role_id,roleName,serverId,NNUID,serverName);
//	}
}
#endif

