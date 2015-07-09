LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_CFLAGS += -fexceptions -DYN_LINUX -DGAME_CLIENT -DYN_NETWORK -DNET_SUPPORT

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/Chat_System/Chat_Client.cpp \
../../Classes/DataModule/BlackActor.cpp \
../../Classes/DataModule/BattleField.cpp \
../../Classes/DataModule/BlackBullet.cpp \
../../Classes/DataModule/BlackCity.cpp \
../../Classes/DataModule/CityActor.cpp \
../../Classes/DataModule/Little.cpp \
../../Classes/DataModule/MonsterTeam.cpp \
../../Classes/DataModule/MonsterWave.cpp \
../../Classes/DataModule/Skill.cpp \
../../Classes/DataModule/SkillTag.cpp \
../../Classes/DataModule/WarWorld.cpp \
../../Classes/DataModule/WarZone.cpp \
../../Classes/DataModule/FightFormula.cpp \
../../Classes/DataModule/BlackColossus.cpp \
../../Classes/DataModule/ClsSkill.cpp \
../../Classes/ClientLogic/LoadScene/LoadScene.cpp \
../../Classes/ClientLogic/Actor/FightActor.cpp \
../../Classes/ClientLogic/Actor/Bullet.cpp \
../../Classes/ClientLogic/Actor/Hero.cpp \
../../Classes/ClientLogic/Actor/Monster.cpp \
../../Classes/ClientLogic/Actor/YNCamera.cpp \
../../Classes/ClientLogic/Actor/Effect.cpp \
../../Classes/ClientLogic/Actor/Actor.cpp \
../../Classes/ClientLogic/Actor/City_NPC.cpp \
../../Classes/ClientLogic/Actor/City_Player.cpp \
../../Classes/ClientLogic/Actor/Gear.cpp \
../../Classes/ClientLogic/Actor/Guardian.cpp \
../../Classes/ClientLogic/Actor/Colossus.cpp \
../../Classes/ClientLogic/Actor/ItemSpirit.cpp \
../../Classes/ClientLogic/Actor/City_Freind.cpp \
../../Classes/ClientLogic/Buff/Buff.cpp \
../../Classes/ClientLogic/Buff/BuffManager.cpp \
../../Classes/ClientLogic/GameScene/MyPageView.cpp \
../../Classes/ClientLogic/GameScene/GameScene.cpp \
../../Classes/ClientLogic/GameScene/ActorLayer.cpp \
../../Classes/ClientLogic/GameScene/HitEffectLayer.cpp \
../../Classes/ClientLogic/GameScene/CityLayer.cpp \
../../Classes/ClientLogic/GameScene/ResultLayer.cpp \
../../Classes/ClientLogic/GameScene/SelectBattleLayer.cpp \
../../Classes/ClientLogic/SneakyJoy/SneakyJoystick.cpp \
../../Classes/ClientLogic/SneakyJoy/SneakyJoystickSkinnedBase.cpp \
../../Classes/ClientLogic/StateMachine/StateMachine.cpp \
../../Classes/ClientLogic/Utils/GameReader.cpp \
../../Classes/ClientLogic/Utils/BaseUtils.cpp \
../../Classes/ClientLogic/Utils/RotateAction.cpp \
../../Classes/Activity_System/Activity_Config_Mgr.cpp \
../../Classes/Activity_System/Activity_Logic_Cl.cpp \
../../Classes/Activity_System/Activity_Msg_Proc_Cl.cpp \
../../Classes/Activity_System/Activity_Record_Mgr_Cl.cpp \
../../Classes/Acupoint_System/Acupoint_Config_Mgr.cpp \
../../Classes/Acupoint_System/Acupoint_Logic_Cl.cpp \
../../Classes/Acupoint_System/Acupoint_Mgr_Cl.cpp \
../../Classes/Acupoint_System/Acupoint_Msg_Proc_Cl.cpp \
../../Classes/Arena_System/Arena_Client.cpp \
../../Classes/Award_System/Award_Msg_Proc_Cl.cpp \
../../Classes/Banks_System/Banks_Logic_Mgr.cpp \
../../Classes/Banks_System/Banks_Msg_Proc_Cl.cpp \
../../Classes/BossBattle_System/Boss_Client.cpp \
../../Classes/Character_System/Character.cpp \
../../Classes/Character_System/Character_Logic.cpp \
../../Classes/Character_System/Character_Mgr.cpp \
../../Classes/Character_System/CommonNpc.cpp \
../../Classes/Character_System/CommonNpc_Config_Mgr.cpp \
../../Classes/Character_System/CommonNpc_Logic.cpp \
../../Classes/Character_System/FightNpc.cpp \
../../Classes/Character_System/FightNpc_Config_Mgr.cpp \
../../Classes/Character_System/FightNpc_Logic.cpp \
../../Classes/Character_System/FightPlayer.cpp \
../../Classes/Character_System/Player.cpp \
../../Classes/Character_System/Player_Config_Mgr.cpp \
../../Classes/Character_System/Player_Logic_Cl.cpp \
../../Classes/Character_System/Player_Msg_Proc_Cl.cpp \
../../Classes/Common/Effect_Cfg_Data_Mgr.cpp \
../../Classes/Common/Game_Utils.cpp \
../../Classes/Common/StrokeLabelTTF.cpp \
../../Classes/Common/Tool.cpp \
../../Classes/Common/Utils.cpp \
../../Classes/Common/VisibleRect.cpp \
../../Classes/Cool_Time_System/Cool_Time_Config_Mgr.cpp \
../../Classes/Cool_Time_System/Cool_Time_Logic_Cl.cpp \
../../Classes/Cool_Time_System/Cool_Time_Mgr_Cl.cpp \
../../Classes/Cool_Time_System/Cool_Time_Msg_Proc_Cl.cpp \
../../Classes/Daily_Task_System/Daily_Task_Config_Mgr.cpp \
../../Classes/Daily_Task_System/Daily_Task_Logic_Cl.cpp \
../../Classes/Daily_Task_System/Daily_Task_Mgr_Cl.cpp \
../../Classes/Daily_Task_System/Daily_Task_Msg_Proc_Cl.cpp \
../../Classes/Dialogue_System/Dialogue_Client.cpp \
../../Classes/Dialogue_System/DialogGroup.cpp \
../../Classes/Dialogue_System/DialogSegment.cpp \
../../Classes/Dialogue_System/DialogLine.cpp \
../../Classes/Dialogue_System/DialogManager.cpp \
../../Classes/Dialogue_System/DialogLayer.cpp \
../../Classes/Dialogue_System/MissionDialog.cpp \
../../Classes/Reward_System/Reward_Client.cpp \
../../Classes/Emai_System/Email_Client.cpp \
../../Classes/EndlessTower_System/Endless_Client.cpp \
../../Classes/EndlessTower_System/EndlessPrayLayer.cpp \
../../Classes/Events/OnResultEvent.cpp \
../../Classes/Events/SendResultEvent.cpp \
../../Classes/Event_System/Event_Data.cpp \
../../Classes/Event_System/Event_Function_Instance.cpp \
../../Classes/Event_System/event_system_data_mgr.cpp \
../../Classes/Event_System/event_system_logic.cpp \
../../Classes/Faction_System/Faction_Client.cpp \
../../Classes/Faction_System/Faction_Config_Mgr.cpp \
../../Classes/Function_Open_System/Function_Open_Config_Mgr.cpp \
../../Classes/Function_Open_System/Function_Open_Logic.cpp \
../../Classes/Fate_System/Fate_Client.cpp \
../../Classes/Game/Audio_Manager.cpp \
../../Classes/Game_Interface/game_condition.cpp \
../../Classes/Game_Interface/game_content_interface.cpp \
../../Classes/Game_Interface/game_data_exchange_client.cpp \
../../Classes/Game_Interface/Game_Element_Parse.cpp \
../../Classes/Game_Interface/game_event_mgr.cpp \
../../Classes/Game_Interface/game_event_response.cpp \
../../Classes/game_play_controler/game_play_controler_data/ctrl_data.cpp \
../../Classes/game_play_controler/game_play_controler_data/gameplay_ctrl_data_mgr.cpp \
../../Classes/game_play_controler/game_play_controler_data/gameplay_ctrl_tool.cpp \
../../Classes/game_play_controler/game_play_controler_logic/gameplay_ctrl_db_proc.cpp \
../../Classes/game_play_controler/game_play_controler_logic/gameplay_ctrl_event_proc.cpp \
../../Classes/game_play_controler/game_play_controler_logic/gameplay_ctrl_fun_proc.cpp \
../../Classes/game_play_controler/game_play_controler_logic/gameplay_ctrl_logic.cpp \
../../Classes/God_System/God_Client.cpp \
../../Classes/God_System/God_Weapon_Config_Mgr.cpp \
../../Classes/Item_Container_System/Item_Container_Mgr_Cl.cpp \
../../Classes/Item_Container_System/Item_Container_Msg_Proc_Cl.cpp \
../../Classes/Item_System/Item_Config_Mgr.cpp \
../../Classes/Item_System/Item_Desc_Config_Mgr.cpp \
../../Classes/Item_System/Item_Logic_Cl.cpp \
../../Classes/Item_System/Item_Mgr_Cl.cpp \
../../Classes/Item_System/Item_Msg_Proc_Cl.cpp \
../../Classes/json/json_reader.cpp \
../../Classes/json/json_value.cpp \
../../Classes/json/json_writer.cpp \
../../Classes/Junior_Guide_System/Junior_Guide_Mgr.cpp \
../../Classes/Login_Reward_System/Login_Reward_Config_Mgr.cpp \
../../Classes/Login_Reward_System/Login_Reward_Mgr_Cl.cpp \
../../Classes/Login_Reward_System/Login_Reward_Msg_Proc_Cl.cpp \
../../Classes/Lottery_System/Lottery_Config_Mgr.cpp \
../../Classes/Lottery_System/Lottery_Msg_Proc_CL.cpp \
../../Classes/Network/msg_manager.cpp \
../../Classes/Network/msg_proc.cpp \
../../Classes/Network_Common/dhkey.cpp \
../../Classes/Network_Common/Encoder_XOR.cpp \
../../Classes/Network_Common/EncoderManager.cpp \
../../Classes/Network_Common/FileAPI.cpp \
../../Classes/Network_Common/message_coder.cpp \
../../Classes/Network_Common/NetManager.cpp \
../../Classes/Network_Common/Packet.cpp \
../../Classes/Network_Common/ServerSocket.cpp \
../../Classes/Network_Common/Socket.cpp \
../../Classes/Network_Common/SocketAPI.cpp \
../../Classes/Network_Common/SocketBillingInputStream.cpp \
../../Classes/Network_Common/SocketBillingOutputStream.cpp \
../../Classes/Network_Common/SocketInputStream.cpp \
../../Classes/Network_Common/SocketOutputStream.cpp \
../../Classes/Partition_System/Partition_Msg_Proc_Cl.cpp \
../../Classes/Pet_System/Pet_Client.cpp \
../../Classes/Platform_Dependence/Dependence.cpp \
../../Classes/Play_System/Client_Instance_Msg_Proc.cpp \
../../Classes/Play_System/Container_Logic.cpp \
../../Classes/Play_System/Container_Mgr.cpp \
../../Classes/Play_System/Formula_Function_Instance.cpp \
../../Classes/Play_System/Formula_Function_Instance_Client.cpp \
../../Classes/Play_System/Formula_Function_Monster_Wave.cpp \
../../Classes/Play_System/Formula_Logic.cpp \
../../Classes/Play_System/Formula_Mgr.cpp \
../../Classes/Play_System/Instance_Data_Mgr.cpp \
../../Classes/Play_System/Instance_Sweep_Data_Mgr.cpp \
../../Classes/Player_Account/Account_Data_Mgr.cpp \
../../Classes/Player_Account/Account_Logic.cpp \
../../Classes/Player_Account/Account_Msg_Proc.cpp \
../../Classes/Player_Account/Profile.cpp \
../../Classes/Player_Account/RecentlyServer.cpp \
../../Classes/Public_Annoucement/Public_Annoucement_Data_Mgr.cpp \
../../Classes/Public_Annoucement/Public_Annoucement_Mgr_Proc_CL.cpp \
../../Classes/quest_system/quest_data/quest_data_mgr.cpp \
../../Classes/quest_system/quest_data/quest_json_config.cpp \
../../Classes/quest_system/quest_logic/quest_logic.cpp \
../../Classes/quest_system/quest_logic/quest_logic_client.cpp \
../../Classes/quest_system/quest_logic/quest_msg_proc_client.cpp \
../../Classes/quest_system/quest_logic/quest_npc_logic.cpp \
../../Classes/RadiateSystem/Radiate_Msg_Proc.cpp \
../../Classes/Random_System/Name_Random_Mgr.cpp \
../../Classes/Rank_System/Rank_Logic_Cl.cpp \
../../Classes/Rank_System/Rank_Mgr_Cl.cpp \
../../Classes/Rank_System/Rank_Msg_Proc_Cl.cpp \
../../Classes/Relation_System/Relation_Mgr.cpp \
../../Classes/Relation_System/Relation_Msg_Proc.cpp \
../../Classes/Secretary_System/Secretary_Client.cpp \
../../Classes/Shield_Word/ShieldManager.cpp \
../../Classes/Shop_System/Shop_Config_Mgr.cpp \
../../Classes/Shop_System/Shop_Msg_Proc_Cl.cpp \
../../Classes/Shop_System/Shoping_Record_Mgr_Cl.cpp \
../../Classes/Sign_System/Sign_Client.cpp \
../../Classes/Star_System/Star_Client.cpp \
../../Classes/Task_System/Task_Client.cpp \
../../Classes/Title_System/Title_Client.cpp \
../../Classes/TouchSkill/LogicSkill.cpp \
../../Classes/TouchSkill/SkillManager.cpp \
../../Classes/TouchSkill/SkillMsgProc.cpp \
../../Classes/UI/Actor_Layer.cpp \
../../Classes/UI/City_Scene.cpp \
../../Classes/UI/DownLoading_Layer.cpp \
../../Classes/UI/Loading_NoTouch_Layer.cpp \
../../Classes/UI/Loading_Scene.cpp \
../../Classes/UI/Login_Scene.cpp \
../../Classes/UI/Main_City_Scene.cpp \
../../Classes/UI/Message_Layer.cpp \
../../Classes/UI_Interface/CocoStu_UI_Scene_Config_Mgr.cpp \
../../Classes/UI_Interface/CocoStu_UI_Scene_Interface.cpp \
../../Classes/UI_Interface/CocoStu_UI_Scene_Logic.cpp \
../../Classes/UI_Interface/Joiner_Guidance.cpp \
../../Classes/UI_Interface/MyEditBox.cpp \
../../Classes/UI_Interface/Select_Server_UI.cpp \
../../Classes/UI_Interface/UI_Activity_Layer.cpp \
../../Classes/UI_Interface/UI_Activity_Six_Sect_Layer.cpp \
../../Classes/UI_Interface/UI_AllSetting_Layer.cpp \
../../Classes/UI_Interface/UI_Arena_Layer.cpp \
../../Classes/UI_Interface/UI_Bag_Info_Layer.cpp \
../../Classes/UI_Interface/UI_Banks_Layer.cpp \
../../Classes/UI_Interface/UI_ChatBoard_Layer.cpp \
../../Classes/UI_Interface/UI_Config_Data_Mgr.cpp \
../../Classes/UI_Interface/UI_Daily_Mission.cpp \
../../Classes/UI_Interface/UI_Exchange_Code_Layer.cpp \
../../Classes/UI_Interface/UI_Fate_Layer.cpp \
../../Classes/UI_Interface/UI_FuBenDialog.cpp \
../../Classes/UI_Interface/UI_Function_Instance.cpp \
../../Classes/UI_Interface/UI_Goods_Grid_Layer.cpp \
../../Classes/UI_Interface/UI_Icon_Info_Layer.cpp \
../../Classes/UI_Interface/UI_Interface.cpp \
../../Classes/UI_Interface/UI_Json_Manager.cpp \
../../Classes/UI_Interface/UI_Logic.cpp \
../../Classes/UI_Interface/UI_LoginLayer.cpp \
../../Classes/UI_Interface/UI_Login_Award_Layer.cpp \
../../Classes/UI_Interface/UI_LogoLayer.cpp \
../../Classes/UI_Interface/UI_MainMenu_Layer.cpp \
../../Classes/UI_Interface/UI_Material_Fragment_Layer.cpp \
../../Classes/UI_Interface/UI_Message.cpp \
../../Classes/UI_Interface/UI_Mission_Layer.cpp \
../../Classes/UI_Interface/UI_MissionDialogue_Layer.cpp \
../../Classes/UI_Interface/UI_ModalDialogue_Layer.cpp \
../../Classes/UI_Interface/UI_New_Function_Open.cpp \
../../Classes/UI_Interface/UI_NpcDialogue_Layer.cpp \
../../Classes/UI_Interface/UI_PowerChangeTips.cpp \
../../Classes/UI_Interface/UI_Public_Announcement.cpp \
../../Classes/UI_Interface/UI_Ranking_List_Layer.cpp \
../../Classes/UI_Interface/UI_Shop_Center_Layer.cpp \
../../Classes/UI_Interface/UI_Skill_Info_Layer/SkillView.cpp \
../../Classes/UI_Interface/UI_Skill_Info_Layer/MyImageView.cpp \
../../Classes/UI_Interface/UI_Society_Layer/UI_Email_Layer/UI_Email_Cell_Layer.cpp \
../../Classes/UI_Interface/UI_Society_Layer/UI_Email_Layer/UI_Email_Layer.cpp \
../../Classes/UI_Interface/UI_Society_Layer/UI_Email_Layer/UI_Receive_Email_Layer.cpp \
../../Classes/UI_Interface/UI_Society_Layer/UI_Email_Layer/UI_Send_Email_Layer.cpp \
../../Classes/UI_Interface/UI_Society_Layer/UI_Friend_Layer/UI_Add_Friend_Layer.cpp \
../../Classes/UI_Interface/UI_Society_Layer/UI_Friend_Layer/UI_Friend_Cell_Layer.cpp \
../../Classes/UI_Interface/UI_Society_Layer/UI_Friend_Layer/UI_Friend_Layer.cpp \
../../Classes/UI_Interface/UI_Wash_Layer/WashLayer.cpp \
../../Classes/UI_Interface/UI_Society_Layer/UI_Society_Layer.cpp \
../../Classes/UI_Interface/UI_StartGameLayer.cpp \
../../Classes/UI_Interface/UI_SystemSetting_Layer.cpp \
../../Classes/UI_Interface/UI_TimeLimitedInstance_Layer.cpp \
../../Classes/UI_Interface/UI_Tips_Layer.cpp \
../../Classes/UI_Interface/UI_Tools.cpp \
../../Classes/UI_Interface/UI_Trade_Layer.cpp \
../../Classes/UI_Interface/UI_UpdateLayer.cpp \
../../Classes/UI_Interface/UI_Bag_Gem_Layer/UI_Bag_Gem_Layer.cpp \
../../Classes/UI_Interface/UI_Equipment_StarUp_Layer/UI_Equipment_StarUp_Info_Layer.cpp \
../../Classes/UI_Interface/UI_Equipment_StarUp_Layer/UI_Equipment_StarUp_Layer.cpp \
../../Classes/UI_Interface/UI_Equipment_Strength_Layer/UI_Equipment_Strengthen_Info_Layer.cpp \
../../Classes/UI_Interface/UI_Equipment_Strength_Layer/UI_Equipment_Strengthen_Layer.cpp \
../../Classes/UI_Interface/UI_Equipment_Gem_Layer/UI_Equipment_Gem_Cell_Layer.cpp \
../../Classes/UI_Interface/UI_Equipment_Gem_Layer/UI_Equipment_Gem_Layer.cpp \
../../Classes/UI_Ranking_List_Layer/UI_Ranking_List_Cell_Layer.cpp \
../../Classes/UI_Ranking_List_Layer/UI_Ranking_List_Layer.cpp \
../../Classes/Update_Logic/MessageInfo.cpp \
../../Classes/Update_Logic/UpdateData.cpp \
../../Classes/Update_Logic/UpdateHelper.cpp \
../../Classes/Update_Logic/UpdateManager.cpp \
../../Classes/Update_Logic/UpdateProtocol.cpp \
../../Classes/Update_Logic/VersionInfo.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
$(call import-module,editor-support/cocostudio)
# $(call import-module,network)
$(call import-module,extensions)
