//
//  MonsterWave.h
//  cocosGame
//
//  Created by ff on 14-11-30.
//
//

#ifndef __cocosGame__MonsterWave__
#define __cocosGame__MonsterWave__

#include "cocos2d.h"
#include "MonsterTeam.h"
#include "../ClientLogic/Utils/GameUtil.h"

class MonsterWave : public Singleton<MonsterWave>
{
public:
    MonsterWave();
    ~MonsterWave();
    
    bool startWave();
    
    bool sendTeam(int teamId);
    
    MonsterTeam *getTeam(int teamId);
    
    bool isAllTeamOut();
    
    bool isWaveOver();
    
    bool someOneDead(int teamIdx);
    
    void sendWaitOver();
    
    bool readWave(int idx, rapidjson::Document& _doc);
    
    static void initIdTable(rapidjson::Document &_doc);
    
    bool readFile(int idx, std::string filename);

	bool LoadDialogue(const int nDialogueID);			// 载入对话
public:
    static std::map<int, int> idTable;
    
private:
    CC_SYNTHESIZE_READONLY(int, waveId, WaveId);
    //下一波怪ID,没有为0
    CC_SYNTHESIZE_READONLY(int, nextWaveId, NextWaveId);
    
    //第一队怪
    CC_SYNTHESIZE_READONLY(int, startTeamId, StartTeamId);
    //队伍数
    CC_SYNTHESIZE_READONLY(int, teamCount, TeamCount);
    //存活人数
    CC_SYNTHESIZE_READONLY(int, surviveCount, surviveCount);
    
    CC_SYNTHESIZE(cocos2d::experimental::TMXTiledMap *, tiledMap, TiledMap);
    
    CC_SYNTHESIZE_READONLY(std::vector<mon>, waitSendMons, WaitSendMons);
    CC_SYNTHESIZE(bool, sendTeamOver, sendTeamOver);

	std::list<int>		m_pDialogueIDList;		// 对话列表
    
    //队伍容器
    std::map<int, MonsterTeam *> teams;

public:
	inline void	GetDialogueIDList(std::list<int> * pDialogueList)
	{
		if (m_pDialogueIDList.size() == 0)
			return;

		std::list<int>::const_iterator dialogueid_iter = m_pDialogueIDList.begin();
		for (dialogueid_iter; dialogueid_iter != m_pDialogueIDList.end(); ++dialogueid_iter)
		{
			pDialogueList->push_back(*dialogueid_iter);
		}
		m_pDialogueIDList.clear();
	}
};

#endif /* defined(__cocosGame__MonsterWave__) */
