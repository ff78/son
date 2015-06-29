//
//  BuffManager.h
//  WuhunLua
//
//  Created by ff on 15-3-19.
//
//

#ifndef __WuhunLua__BuffManager__
#define __WuhunLua__BuffManager__

#include "cocos2d.h"
#include "../Utils/GameUtil.h"
#include "cocostudio/CocoStudio.h"
#include "Buff.h"
#include "../../Skill_System/Buff/Buff_Common.h"

#define BUFF_FILE "GameData/data_buff.json"


class BuffManager : public cocos2d::Node
{
public:
    bool init();
    
    CREATE_FUNC(BuffManager);
    
//    void onExit();
    
    bool addBuff(int idx, std::function<void(Buff *)> handle, std::function<void(Buff *)> remove);
    
    static void initIdTable(rapidjson::Document &_doc);
    
    void addBuff(int buffId, rapidjson::Document& _doc, std::function<void(Buff *)> handle, std::function<void(Buff *)> remove);
    
    void replaceBuff(int buffId, rapidjson::Document& _doc, std::function<void(Buff *)> handle, std::function<void(Buff *)> remove);
    
    void removeAllBuff();
    
    void removeBuff(int buffId);
    
    void update(float dt);
    
    void removeImmu(int buffId);
    
    static std::map<int, int> idTable;
    
    static std::map<int, int> targetTable;
    
    static std::map<int, int> typeTable;
    static std::map<int, bool> deBuffTable;
    
private:
    std::map<int, Buff*> buffs;
    std::map<int, int> immuTable;
};

#endif /* defined(__WuhunLua__BuffManager__) */
