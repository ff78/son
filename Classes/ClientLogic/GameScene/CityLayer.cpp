//
//  CityLayer.cpp
//  cocosGame
//
//  Created by ff on 14-11-5.
//
//

#include "CityLayer.h"
#include "../Actor/Effect.h"
#include "../Actor/Guardian.h"
#include "../Actor/Colossus.h"

#include "Player_Account/Account_Data_Mgr.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"

USING_NS_CC;
using namespace cocostudio;

bool CityLayer::playerInDoors = false;
bool CityLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    freindsVec.clear();
    return true;
}

void CityLayer::initData(int idx)
{
    blackCity = new BlackCity();
    blackCity->readFile(idx, CITY_FILE);
	bgSpt = nullptr;
	frontLayer = nullptr;
    pressJoy = false;
    playerInDoors = false;

    
    joyDir[0] = DIRECT::RIGHT;
    joyDir[1] = DIRECT::RIGHT | DIRECT::UP;
    joyDir[2] = DIRECT::UP;
    joyDir[3] = DIRECT::LEFT | DIRECT::UP;
    joyDir[4] = DIRECT::LEFT;
    joyDir[5] = DIRECT::LEFT | DIRECT::DOWN;
    joyDir[6] = DIRECT::DOWN;
    joyDir[7] = DIRECT::RIGHT | DIRECT::DOWN;
}

void CityLayer::initBackLayer()
{
    auto winSize = Director::getInstance()->getWinSize();
    if (blackCity->getBgPath() != "null" && blackCity->getBgPath() != "") {
        backLayer = Layer::create();
        bgSpt = Sprite::create("img/scene/"+blackCity->getBgPath());
        bgSpt->setAnchorPoint(Point(0, 1));
        bgSpt->setPosition(Vec2(0, 660));
        backLayer->addChild(bgSpt);
        addSceneEffect("bgAnim", bgSpt, true);
        
        backLayer->setPosition(Vec2(0, -5));
//        backLayer->setPosition(Vec2(0, winSize.height));
        addChild(backLayer);
    }
}

void CityLayer::initMidLayer()
{
    if (blackCity->getMidPath() != "null" && blackCity->getFrontPath() != "") {
        midLayer = Layer::create();
        auto midSpt = Sprite::create("img/scene/" + blackCity->getMidPath());
        midSpt->setAnchorPoint(Point(0, 0));
        midLayer->addChild(midSpt);
        addSceneEffect("midAnim", midSpt, false);
        
        midLayer->setPosition(Vec2(0, 0));
        addChild(midLayer);
    }
}

void CityLayer::initFrontLayer()
{
    if (blackCity->getFrontPath() != "null" && blackCity->getFrontPath() != "") {
        frontLayer = Layer::create();
        auto frontSpt = Sprite::create("img/scene/"+blackCity->getFrontPath());
        frontSpt->setAnchorPoint(Point(0, 0));
        frontLayer->addChild(frontSpt);
        addSceneEffect("frtAnim", frontSpt, false);
        frontLayer->setPosition(Vec2(0, 0));
        addChild(frontLayer);
    }
}
void CityLayer::addSceneEffect(std::string groupName, Node *parent, bool alignTop)
{
    std::string tiledDir("scene/");
    log("actor layer 3");
    auto tmx = experimental::TMXTiledMap::create(tiledDir+blackCity->getTiledMapPath());
    log("actor layer 4");
    auto midGroup = tmx->getObjectGroup(groupName);
    
    if (midGroup==nullptr) {
        return;
    }
    
    auto midObjs = midGroup->getObjects();
    for (auto npc : midObjs) {
        auto dict = npc.asValueMap();
        auto animName = dict["name"].asString();
        auto x = dict["x"].asFloat();
        auto y = dict["y"].asFloat();
        
        auto gid = dict["gid"].asInt();
        auto mapInfo = TMXMapInfo::create(tiledDir+blackCity->getTiledMapPath());
        auto tilesetVec = mapInfo->getTilesets();
        for (auto tileset : tilesetVec)
        {
            if(tileset->_firstGid == gid)
            {
                x += tileset->_tileSize.width/2;
                y += tileset->_tileSize.height/2;
                //                        y = 660 - y;
                break;
            }
        }
        if (alignTop) {
            y = bgSpt->getContentSize().height - (tmx->getMapSize().height * tmx->getTileSize().height - y);
        }
        //                y = 0;
        //                x = 0;
        //                if(midSpt->getContentSize().height > (tmx->getMapSize().height * tmx->getTileSize().height))
        //                {
        //                    y += midSpt->getContentSize().height - (tmx->getMapSize().height * tmx->getTileSize().height);
        //                }
        
        
        auto effect = Effect::create();
        effect->initWithArmature(animName);
        effect->setPosition(Vec2(x, y));
        parent->addChild(effect);
    }
}

void CityLayer::initActorLayer()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player_data = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));

    actorLayer = Layer::create();
    std::string path("scene/");
    log("actor layer 1");
    path += blackCity->getTiledMapPath();
    log("actor tmx:%s", path.c_str());
    auto tmx = cocos2d::experimental::TMXTiledMap::create(path);
    
    auto npcGroup = tmx->getObjectGroup("npc");
    log("actor layer 2");
    auto npcObjs = npcGroup->getObjects();
    for (auto npc : npcObjs) {
        auto dict = npc.asValueMap();
        auto x = dict["x"].asFloat();
        auto y = dict["y"].asFloat();
//        auto npcName = dict["name"].asString();
        auto npcId = dict["id"].asInt();
        City_NPC *role = City_NPC::create();
        role->initWithId(npcId);
        role->setPosition(Vec2(x, y));
        actorLayer->addChild(role);
    }
    npcGroup = tmx->getObjectGroup("doors");
    npcObjs = npcGroup->getObjects();
    for (auto npc : npcObjs) {
        auto dict = npc.asValueMap();
        auto npcType = dict["type"].asString();
        auto x = dict["x"].asFloat();
        auto y = dict["y"].asFloat();
        
        if (npcType == "born") {
            player = City_Player::create();
            player->initWithId(player_data->get_job() + 20);
            player->setPosX(x);
            player->setPosY(y);
            player->setPosition(Vec2(x, y));
            actorLayer->addChild(player);
        }else if (npcType == "door"){
			auto npcId = dict["id"].asInt();
            door = City_NPC::create();
            door->setPosition(Vec2(x, y));
			door->initWithId(npcId);

            actorLayer->addChild(door);
        }
    }
    addChild(actorLayer);
    
//    player_data->set_cur_pet_id(100001);
    if (player_data->get_cur_pet_id() > 0) {
        auto guard = Guardian::create();
    player->setGuard(guard);
        guard->initFightData(player_data->get_cur_pet_id());
        guard->initViewRes();
        guard->initFightState();
        guard->setMan(player);
        guard->setPosX(player->getPositionX());
        guard->setPosY(player->getPositionY());
        guard->setPosition(player->getPosition());
        guard->preloadSkillRes();
        
        actorLayer->addChild(guard);
    }
    if (player_data->get_cur_god_id() > 0) {
        auto col = Colossus::create();
        col->initFightData(player_data->get_cur_god_id());
        col->initViewRes();
        col->initFightState();
        col->setMan(player);
        col->setPosX(player->getPositionX());
        col->setPosY(player->getPositionY());
        col->setPosition(player->getPosition());
        col->preloadSkillRes();
        player->setColossus(col);
        actorLayer->addChild(col);
    }
    
    auto freinds = CHARACTER_MGR::instance()->_other_player_map;
    for (auto freind : *freinds) {
        auto freind_data = freind.second;
        auto obj = City_Freind::create();
        obj->initWithId(freind_data->get_job() + 20, freind_data);
        actorLayer->addChild(obj);
        freindsVec.push_back(obj);
        
        if (freind_data->get_cur_pet_id() > 0) {
            auto guard = Guardian::create();
            obj->setGuard(guard);
            guard->initFightData(freind_data->get_cur_pet_id());
            guard->initViewRes();
            guard->initFightState();
            guard->setMan(obj);
            guard->setPosX(obj->getPositionX());
            guard->setPosY(obj->getPositionY());
            guard->setPosition(obj->getPosition());
            guard->preloadSkillRes();
            
            actorLayer->addChild(guard);
        }
        if (freind_data->get_cur_god_id() > 0) {
            auto col = Colossus::create();
            col->initFightData(freind_data->get_cur_god_id());
            col->initViewRes();
            col->initFightState();
            col->setMan(obj);
            col->setPosX(obj->getPositionX());
            col->setPosY(obj->getPositionY());
            col->setPosition(obj->getPosition());
            col->preloadSkillRes();
            obj->setColossus(col);
            actorLayer->addChild(col);
        }
        
    }
}

void CityLayer::addGuard2Hero()
{
    int player_id = Account_Data_Mgr::instance()->get_current_role_id();
    Game_Data::Player* player_data = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));

    if (player_data->get_cur_pet_id() > 0) {
        auto guard = Guardian::create();
        player->setGuard(guard);
        guard->initFightData(player_data->get_cur_pet_id());
        guard->initViewRes();
        guard->initFightState();
        guard->setMan(player);
        guard->setPosX(player->getPositionX());
        guard->setPosY(player->getPositionY());
        guard->setPosition(player->getPosition());
        guard->preloadSkillRes();
        
        actorLayer->addChild(guard);
    }
}
void CityLayer::initCamera()
{
    camera = YNCamera::create();
    addChild(camera);
    camera->setCameraCenter(player->getPosition());
    setViewWindow();
    
}

void CityLayer::setViewWindow()
{
    Vec2 off;
    auto winSize = Director::getInstance()->getWinSize();
    
    off.x = MAX(camera->getPositionX() - winSize.width / 2, 0);
    off.x = MIN(off.x, 1920 - winSize.width);
    off.y =  YNCamera::bShake?camera->vShake():0;
    
    if (bgSpt!=nullptr) {
        int bgWidth = bgSpt->getTexture()->getPixelsWide();
        float bgOffx = MAX(1920 - bgWidth, 0) / (1920 - winSize.width)*off.x;
        backLayer->setPosition(Vec2(0, 0) - off + Vec2(bgOffx, 0));
    }
    
    midLayer->setPosition(Vec2(0, 0) - off);
    actorLayer->setPosition(Vec2(0, -5) - off);
    if (frontLayer!=nullptr) {
        frontLayer->setPosition(Vec2(0, 0) - off);
    }
}

void CityLayer::controlByJoyStick(SneakyJoystick *joyStick, float delta)
{
    if (!joyStick->getPress())
    {
        if (pressJoy) {
            pressJoy = false;
            //log("stop Move");
            player->stopMove();
            
            player->readyRush();
        }
    }else {
        pressJoy = true;
        float dirDegree = joyStick->getDegrees();
        //log("joy dir : %f", joyStick->getDegrees());
        
        int disct = ((dirDegree - 22) / 45 + 1);
        //		log("disct: %d", (disct % 8));
        player->setDir(joyDir[disct % 8]);
        player->startMove();
    }
    player->setJoyPress(pressJoy);
    
    player->logic(delta);
    auto guard = player->getGuard();
    if (guard != nullptr) {
        guard->logic(delta);
    }
    
    auto col = player->getColossus();
    if (col != nullptr) {
        col->logic(delta);
    }
    
    for (auto freind : freindsVec) {
        freind->logic(delta);
        if (freind->getGuard() != nullptr) {
            freind->getGuard()->logic(delta);
        }
        if (freind->getColossus() != nullptr) {
            freind->getColossus()->logic(delta);
        }
    }
    camera->setCameraCenter(player->getPosition());
    setViewWindow();
}

void CityLayer::reorderPlayer()
{
    size_t size = actorLayer->getChildrenCount();
    auto actors = actorLayer->getChildren();
    for (int i = 0; i < size; i++) {
        actors.at(i)->setLocalZOrder(240 - actors.at(i)->getPositionY());
    }
}


City_NPC* CityLayer::getNPCbyId(int idx)
{
    size_t size = actorLayer->getChildrenCount();
    auto actors = actorLayer->getChildren();
    for (int i = 0; i < size; i++) {

		if (typeid(*actors.at(i)) != typeid(City_NPC)) {
            continue;
        }
        
        City_NPC *npc = dynamic_cast<City_NPC *>(actors.at(i));
        if (idx == npc->getCityActor()->getActorId()) {
            return npc;
        }
    }
    return nullptr;
}

bool CityLayer::isCollideDoor()
{
    bool coldoor = (door->getPosition().getDistance(player->getPosition()) < 60);

    if (!playerInDoors) {
        if (coldoor) {
            playerInDoors = true;
            return true;
        }
    } else {
        if (!coldoor) {
            playerInDoors = false;
        }
    }
    return false;
}

void CityLayer::onCollideDoor()
{
    blackCity->onCollideDoor();
}

std::vector<int> CityLayer::getNpcIds()
{
    std::vector<int> idVec;
    size_t size = actorLayer->getChildrenCount();
    auto actors = actorLayer->getChildren();
    for (int i = 0; i < size; i++) {

		//log("%s %s", typeid(actors.at(i)).name(), typeid(City_NPC).name());
        if (typeid(*actors.at(i)) != typeid(City_NPC)) {
            continue;
        }
        
        City_NPC *npc = dynamic_cast<City_NPC *>(actors.at(i));
        idVec.push_back(npc->getCityActor()->getActorId());
    }
    return idVec;
}

int CityLayer::getNpcCount()
{
    int count = 0;
    size_t size = actorLayer->getChildrenCount();
    auto actors = actorLayer->getChildren();
    for (int i = 0; i < size; i++) {
		if (typeid(*actors.at(i)) != typeid(City_NPC)) {
            continue;
        }
        
        count++;
    }
    return count;
}

void CityLayer::setNpcTipSprite(int npcId, std::string path, bool isPlist)
{
    
}

void CityLayer::autoMove2NPC(int npcId)
{
    auto targetNpc = getNPCbyId(npcId);
    player->startAutoMove(targetNpc->getPosition());
}

void CityLayer::autoMove2NPC(int npcId, CallBackFun func, int param)
{
    autoMove2NPC(npcId);
    player->setArrvieFunc(func);
    player->setArriveParam(param);
}
