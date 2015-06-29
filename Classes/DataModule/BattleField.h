//
//  BattleField.h
//  cocosGame
//
//  Created by ff on 14-11-24.
//
//

#ifndef __cocosGame__BattleField__
#define __cocosGame__BattleField__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "MonsterWave.h"
#include "../ClientLogic/Utils/GameUtil.h"
#include "Game_Interface/game_event_mgr.h"

class BattleField : public Singleton<BattleField>
{
private:
    void reg_event_update_ui(const char* cmd,const Game_Logic::game_event_handler_t handle,unsigned int owner_type);
    
public:
    BattleField();
    ~BattleField();
    
    bool start1stWave();
    
    bool readCurrWave();
    
    bool change2NextWave();
    
    void notifyServerTime();

	void NotifyServerResult(const bool bValue = false);
	void SendServerFightResult();
//    void onClickNext();
//    static bool onReceiveNext(const Game_Logic::Game_Event& gm_evt);
    
    void waitPacket();
    
    bool readBattle(int idx, rapidjson::Document& _doc);
    
    static void initIdTable(rapidjson::Document &_doc);
    
    void readFile(std::string filename);
public:
    static std::map<int, int> idTable;
    
private:
    CC_SYNTHESIZE(int, sceneId, SceneId);
    CC_SYNTHESIZE_READONLY(cocos2d::experimental::TMXTiledMap *, tiledMap, TiledMap);
    
    CC_SYNTHESIZE_READONLY(int, secondLimit, SecondLimit);

    CC_SYNTHESIZE_READONLY(int, waveSheetId, WaveSheetId);
    CC_SYNTHESIZE_READONLY(int, waveCount, WaveCount);
    CC_SYNTHESIZE_READONLY(std::string, bgImgName, BgImgName);
    CC_SYNTHESIZE_READONLY(std::string, midImgName, MidImgName);
	CC_SYNTHESIZE_READONLY(std::string, frontImgName, FrontImgName);
	/************************** dely *****************************/
	CC_SYNTHESIZE_READONLY(int, condition, Condition);
	CC_SYNTHESIZE_READONLY(int, _hp, Hp);
	CC_SYNTHESIZE_READONLY(int, _time, Time);
	CC_SYNTHESIZE_READONLY(int, _count, Count);
	/************************** dely *****************************/

    CC_SYNTHESIZE_READONLY(std::string, tiledMapName, TiledMapName);
    
    CC_SYNTHESIZE_READONLY(bool, waveOver, WaveOver);
    CC_SYNTHESIZE_READONLY(int, currSecondLeft, CurrSecondLeft);
    CC_SYNTHESIZE_READONLY(int, currWaveId, CurrWaveId);
    CC_SYNTHESIZE_READONLY(int, currWaveCount, CurrWaveCount);
    CC_SYNTHESIZE_READONLY(bool, gameFail, GameFail);
    
    CC_SYNTHESIZE_READONLY(MonsterWave *, currMonsterWave, CurrMonsterWave);

    CC_SYNTHESIZE_READONLY(int, startDialogId, StartDialogId);
    CC_SYNTHESIZE_READONLY(int, startGroupId, StartGroupId);
    
    CC_SYNTHESIZE(int, winDialogId, WinDialogId);
    CC_SYNTHESIZE(int, winGroupId, WinGroupId);
    
    CC_SYNTHESIZE(int, loseDialogId, LoseDialogId);
    CC_SYNTHESIZE(int, loseGroupId, LoseGroupId);
    
	CC_SYNTHESIZE(bool, m_bFightResult, FightResult);
	bool m_bCanSendResult;

public:
	inline bool GetCanSendResultState()
	{
		return m_bCanSendResult;
	}
};

#endif /* defined(__cocosGame__BattleField__) */
