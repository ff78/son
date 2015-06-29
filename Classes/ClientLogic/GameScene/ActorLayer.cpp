//
//  ActorLayer.cpp
//  soul
//
//  Created by ff on 14-9-15.
//
//

#include "ActorLayer.h"
#include "../Actor/Monster.h"
#include "cocostudio/CocoStudio.h"
#include "../Actor/Bullet.h"
#include "../Actor/YNCamera.h"
#include "../Actor/Gear.h"

USING_NS_CC;
using namespace cocostudio;

bool ActorLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
//    auto monster = Monster::create();
//    monster->addHurtListener();
//	monster->setAnchorPoint(Vec2(0.5, 0));
//    monster->setPosX(1600);
//    monster->setPosY(150);
//	monster->setPosition(Vec2(1600, 150));
//    
//    
//    auto p1 = Vec2(1700, 150);
//    auto p2 = Vec2(1000, 150);
//    std::vector<Point> line;
//    line.push_back(p1);
//    line.push_back(p2);
//    monster->setPartolPosVec(line);
//	addChild(monster);
//
//    monsterVec.pushBack(monster);
    showMonster = nullptr;
    
    return true;
}

void ActorLayer::addBullet(int idx, FightActor *actor, float gunPosY, float gunPosX, SkillTag *skillTag)
{
    auto bullet = Bullet::create();
    bullet->initWithId(idx, actor, gunPosX, gunPosY);
    bullet->setSkillTag(skillTag);
    bullet->setHitDownVal(skillTag->getHitDownVal());
    addChild(bullet);
    if(typeid(*actor) == typeid(Monster))
    {
        monsterBullets.pushBack(bullet);
    }else{
        heroBullets.pushBack(bullet);
    }
}

void ActorLayer::addGear(int gearId, float x, float y, bool flipX)
{
    auto gear = Gear::create();
    addChild(gear);
    gear->initFightData(gearId);
    gear->initViewRes();
    gear->initFightState();
    gear->setPosX(x);
    gear->setPosY(y);
    gear->setPosition(Vec2(x, y));
    gear->setFlipX(flipX);
    gear->getArmature()->setScaleX(flipX?-1:1);
    monsterView2Hero(gear);
    
    gear->preloadSkillRes();
    
    gearVec.pushBack(gear);
}
void ActorLayer::addMonster(int monId, int teamId, float x, float y)
{
    auto monster = Monster::create();
    addChild(monster);
    monster->setTeamId(teamId);
    monster->initFightData(monId);
    monster->initViewRes();
    monster->initFightState();
    monster->addHurtListener();
    
    monster->setAnchorPoint(Vec2(0.5, 0));
    monster->setPosX(x);
    monster->setPosY(y);
    monster->setPosition(Vec2(x, y));
    
    auto p1 = Vec2(1700, y);
    auto p2 = Vec2(1000, y);
//    monster->addPartolPoint(p1, p2);
    std::vector<Point> line;
    line.push_back(p1);
    line.push_back(p2);
    monster->setPartolPosVec(line);
//    addChild(monster);
    monster->changeState(ACTORSTATE::INIT);
    //    changeAction(HEROACTION::STAND);
    monster->changeActionWithName(HEROACTION::STAND);
    
    monsterVec.pushBack(monster);
    
    addActorHitEffect(monster);
    monsterView2Hero(monster);
    
    monster->preloadSkillRes();
}

void ActorLayer::removeBullet(Bullet *bullet)
{
    
    if (typeid(*bullet->getOwner()) == typeid(Monster)) {
        auto bulletItr = monsterBullets.find(bullet);
        if (bulletItr != monsterBullets.end()) {
            monsterBullets.erase(bulletItr);
        }
        
    }else{
        auto bulletItr = heroBullets.find(bullet);
        if (bulletItr != heroBullets.end()) {
            heroBullets.erase(bulletItr);
        }
    }
    removeChild(bullet);
    
}

void ActorLayer::removeMonster(Monster *actor)
{
        EventCustom event("monsterDied");
        event.setUserData(actor);
    actor->addAllGhost2Guard();
        Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
//    actor->getEventDispatcher()->removeEventListenersForTarget(actor);
//    if (typeid(*actor)==typeid(Monster)) {
        monsterVec.erase(monsterVec.find(actor));
//        actor->getHurtEffectLayer()->setVisible(false);
//        actor->setVisible(false);
//        hitEffeLayer->removeChild(actor->getHurtEffectLayer());
//        actor->setVisible(false);
        actor->buffManager->removeAllBuff();
        removeChild(actor);
    
//    }
}

void ActorLayer::addActorHitEffect(FightActor *actor)
{
    auto effLayer = Layer::create();
    effLayer->setPosition(actor->getPosition());
    actor->setHurtEffectLayer(effLayer);
    
    hitEffeLayer->addChild(effLayer);
}

void ActorLayer::fillHitEffect()
{
    hitEffeLayer = HitEffectLayer::create();
    size_t size = getChildrenCount();
    auto actors = getChildren();
    for (int i = 0; i < size; i++) {
        FightActor *actor = dynamic_cast<FightActor *>(actors.at(i));
		if (actor == NULL)
			continue;

        auto effLayer = Layer::create();
        effLayer->setPosition(actor->getPosition());
        actor->setHurtEffectLayer(effLayer);
        
        hitEffeLayer->addChild(effLayer);
    }
    addChild(hitEffeLayer);
    
    ghostLayer = Layer::create();
    addChild(ghostLayer);
}

void ActorLayer::update(float dt)
{
    
    size_t size = monsterVec.size();
//    auto monsters = monsterVec;
    for(int i = size - 1; i >= 0;i--)
    {
        auto obj = monsterVec.at(i);
//        if (typeid(*obj) == typeid(HitEffectLayer)) {
//            continue;
//        }
        auto actor = dynamic_cast<Monster *>(obj);
        if(actor->getDieLie())
        {
            if (actor == showMonster) {
                showMonster = nullptr;
            }
        }
        if (actor->getDying()) {
            removeMonster(actor);
        }
    }
    
    size = monsterBullets.size();
    for (int i = size - 1; i >= 0; i--) {
        auto bullet = monsterBullets.at(i);
        if (!bullet->getAlive()) {
            removeBullet(bullet);
            continue;
        }
        if(bullet->getBlackBullet()->getBulletType() == 1){
            float cameraPosX = YNCamera::getInstance()->getPositionX();
            if (bullet->isOutsideCamera(cameraPosX))
            {
                removeBullet(bullet);
            }
            //            if (bullet->getPositionX()<-50 || bullet->getPositionX()>MAP_AREA_WIDTH+50) {
            //                removeBullet(bullet);
            //                continue;
            //            }
            //
            //
            //            if (abs(cameraPosX - bullet->getPositionX()) < 530) {
            //                continue;
            //            }
            //
            //            if (cameraPosX < 480) {
            //                if (bullet->getPositionX() - cameraPosX > 960-cameraPosX+50 ) {
            //                    removeBullet(bullet);
            //                }
            //            }else if(cameraPosX > MAP_AREA_WIDTH - 480) {
            //                if (cameraPosX - bullet->getPositionX() > 960 + 50 - (MAP_AREA_WIDTH - cameraPosX)) {
            //                    removeBullet(bullet);
            //                }
            //            }            
        }else if(bullet->getBlackBullet()->getBulletType() == 2){
            if(bullet->isAnimationOver())
            {
                removeBullet(bullet);
            }
        }
    }
    size = heroBullets.size();
    for (int i = size - 1; i >= 0; i--) {
        auto bullet = heroBullets.at(i);
        if (!bullet->getAlive()) {
            removeBullet(bullet);
            continue;
        }
        if(bullet->getBlackBullet()->getBulletType() == 1){
            float cameraPosX = YNCamera::getInstance()->getPositionX();
            if (bullet->isOutsideCamera(cameraPosX))
            {
                removeBullet(bullet);
            }
//            if (bullet->getPositionX()<-50 || bullet->getPositionX()>MAP_AREA_WIDTH+50) {
//                removeBullet(bullet);
//                continue;
//            }
//            
//            
//            if (abs(cameraPosX - bullet->getPositionX()) < 530) {
//                continue;
//            }
//            
//            if (cameraPosX < 480) {
//                if (bullet->getPositionX() - cameraPosX > 960-cameraPosX+50 ) {
//                    removeBullet(bullet);
//                }
//            }else if(cameraPosX > MAP_AREA_WIDTH - 480) {
//                if (cameraPosX - bullet->getPositionX() > 960 + 50 - (MAP_AREA_WIDTH - cameraPosX)) {
//                    removeBullet(bullet);
//                }
//            }            
        }else if(bullet->getBlackBullet()->getBulletType() == 2){
            
            
            if(bullet->isAnimationOver())
            {
                removeBullet(bullet);
            }
        }

        
    }
//    actors.clear();
    size = getChildrenCount();
    auto actors = getChildren();
    for (int i = 0; i < size; i++) {
        actors.at(i)->setLocalZOrder(240 - actors.at(i)->getPositionY());
    }
    size = monsterVec.size();
    for (int i = 0; i < size; i++) {
        auto monster = dynamic_cast<Monster *>(monsterVec.at(i));
        monster->logic(0);
        monster->adjustHurtEffectPos();
    }
    size = gearVec.size();
    for (int i = 0; i < size; i++) {
        auto gear = dynamic_cast<Gear *>(gearVec.at(i));
        gear->logic(0);
    }
    if (hero->Guard != nullptr){
        hero->Guard->logic(0);
    }
    if (hero->colossus != nullptr) {
        hero->colossus->logic(0);
    }
    
    
    size = heroBullets.size();
//    hurtMonsters.clear();
    for (int i = 0; i < size; i++) {
        auto bullet = dynamic_cast<Bullet *>(heroBullets.at(i));

        bullet->Logic(0);
        bool hitSomeOne = false;
        auto bulletPos = bullet->getPosition()+Vec2(0, bullet->getArmature()->getPositionY());
        auto aRect = bullet->getArmature()->getBoundingBox();
//        if (bullet->getFlipX()) {
//            aRect.origin.x = (aRect.size.width + aRect.origin.x) * -1;
//        }
        aRect.origin += bulletPos;
        FightActor *hurtMonster = nullptr;
        for (auto mon : monsterVec) {
            if (mon->getIsInvincible())
            {
                continue;
            }
            if (fabs(bullet->getPositionY() - mon->getPositionY()) < 80 && fabs(bullet->getPositionX() - mon->getPositionX()) < 500){
                auto bRect = mon->getBodyRect();
                auto armature = mon->getArmature();
                auto armatureY = armature->getPositionY();
                bRect.origin += Vec2(mon->getPositionX(), armatureY + mon->getPositionY());
                if (bullet->getBlackBullet()->getBulletType() == 2) {
                    if (aRect.intersectsRect(bRect)) {
                        EventCustom event(MONSTER_HURT_TAG);
                        fightPair pair;
                        pair.attacker = bullet;
                        pair.defender = mon;
                        event.setUserData(&pair);
                        mon->getEventDispatcher()->dispatchEvent(&event);
                        hurtMonster = mon;
                        hitSomeOne = true;
//                        bullet->setAlive(false);
                        continue;
                    }
                }else if(bullet->getBlackBullet()->getBulletType() == 1){
                    if (bRect.containsPoint(bulletPos)) {
                        mon->bulletHurt(bullet);
                        hurtMonster = mon;

                        hitSomeOne = true;
                        bullet->setAlive(false);
                        break;
                    }
                }
            }
            
        }
        if (hitSomeOne && bullet->getBlackBullet()->getSplash()) {
            auto aRect = bullet->getAtkRect();
            float boneY = 0, armatureY = 0;
            auto armature = bullet->getArmature();
            armatureY = armature->getPositionY();
            aRect.origin += Vec2(bullet->getPositionX(), armatureY + bullet->getPositionY());
            for (auto mon : monsterVec) {
                if (mon == hurtMonster) {
                    continue;
                }
                if (mon->getIsInvincible()) {
                    continue;
                }
                if (fabs(bullet->getPositionY() - mon->getPositionY()) < 80 && fabs(bullet->getPositionX() - mon->getPositionX()) < 500){
                    auto bRect = mon->getBodyRect();
                    auto armature = mon->getArmature();
                    auto armatureY = armature->getPositionY();
                    bRect.origin += Vec2(mon->getPositionX(), armatureY + mon->getPositionY());
                    if (bRect.intersectsRect(aRect)) {
                        mon->bulletHurt(bullet);
                        hurtMonsters.pushBack(mon);
                    }
                }
                
            }

        }

    }
    size = monsterVec.size();
    if (!hero->getIsInvincible()) {
        for (int i = 0; i<size; i++) {
            auto mon = dynamic_cast<Monster *>(monsterVec.at(i));
            if(mon->getAtking())
            {
                Rect rAttackRect = mon->getCurrSkillTag()->getAttackRect();
                float thick = mon->getCurrSkillTag()->getAtkAreaThick();
                bool  bMonsterFlipX = mon->getFlipX();
                mon->DealAttackRectByFlip(bMonsterFlipX, &rAttackRect);
                float boneY = 0, armatureY = 0;
                auto armature = mon->getArmature();
                armatureY = armature->getPositionY();
                rAttackRect.origin += Vec2(mon->getPositionX(), armatureY + boneY + mon->getPositionY());
                
                if (mon->getCurrSkillTag()->getFullScreenRange() == 1) {
                    EventCustom event(HERO_HURT_TAG);
                    fightPair pair;
                    pair.attacker = mon;
                    pair.defender = hero;
                    event.setUserData(&pair);
                    hero->getEventDispatcher()->dispatchEvent(&event);
                    mon->setIsValidAtk(true);
                    continue;
                }
                if (abs(mon->getPositionY() - hero->getPositionY()) < thick && abs(mon->getPositionX() - hero->getPositionX()) < 500)
                {
                    auto bRect = hero->getBodyRect();
                    armature = hero->getArmature();
                    armatureY = armature->getPositionY();
                    bRect.origin += Vec2(hero->getPositionX(), armatureY+boneY+hero->getPositionY());
                    if (mon->getCurrSkillTag()->getFullScreenRange() == 0) {
                        if (bRect.intersectsRect(rAttackRect)) {
                            EventCustom event(HERO_HURT_TAG);
                            fightPair pair;
                            pair.attacker = mon;
                            pair.defender = hero;
                            event.setUserData(&pair);
                            hero->getEventDispatcher()->dispatchEvent(&event);
                            mon->setIsValidAtk(true);
                        }                        
                    } else if (mon->getCurrSkillTag()->getFullScreenRange() == 2) {
                        if ((mon->getFlipX() && hero->getPositionX() <= mon->getPositionX()) || (!mon->getFlipX() && hero->getPositionX() >= mon->getPositionX())) {
                            EventCustom event(HERO_HURT_TAG);
                            fightPair pair;
                            pair.attacker = mon;
                            pair.defender = hero;
                            event.setUserData(&pair);
                            hero->getEventDispatcher()->dispatchEvent(&event);
                            mon->setIsValidAtk(true);
                        }
                    }

                }
            }
        }
        
    }
    
    size = gearVec.size();
    if (!hero->getIsInvincible()) {
        for (int i = 0; i<size; i++) {
            auto gear = dynamic_cast<Gear *>(gearVec.at(i));
            if(gear->getAtking())
            {
                Rect rAttackRect = gear->getCurrSkillTag()->getAttackRect();
                float thick = gear->getCurrSkillTag()->getAtkAreaThick();
                bool  bGearsterFlipX = gear->getFlipX();
                gear->DealAttackRectByFlip(bGearsterFlipX, &rAttackRect);
                float boneY = 0, armatureY = 0;
                auto armature = gear->getArmature();
                armatureY = armature->getPositionY();
                rAttackRect.origin += Vec2(gear->getPositionX(), armatureY + boneY + gear->getPositionY());

                if (abs(gear->getPositionY() - hero->getPositionY()) < thick && abs(gear->getPositionX() - hero->getPositionX()) < 500)
                {
                    auto bRect = hero->getBodyRect();
                    armature = hero->getArmature();
                    armatureY = armature->getPositionY();
                    bRect.origin += Vec2(hero->getPositionX(), armatureY+boneY+hero->getPositionY());
                    if (bRect.intersectsRect(rAttackRect)) {
                        EventCustom event(HERO_HURT_TAG);
                        fightPair pair;
                        pair.attacker = gear;
                        pair.defender = hero;
                        event.setUserData(&pair);
                        hero->getEventDispatcher()->dispatchEvent(&event);
                        gear->setIsValidAtk(true);
                    }
                }
            }
        }
    }
    if(hero->getAtking())
	{
		Rect rAttackRect = hero->getCurrSkillTag()->getAttackRect();
        float thick = hero->getCurrSkillTag()->getAtkAreaThick();
		bool  bMonsterFlipX = hero->getFlipX();
		hero->DealAttackRectByFlip(bMonsterFlipX, &rAttackRect);
        float boneY = 0, armatureY = 0;
        auto armature = hero->getArmature();
        armatureY = armature->getPositionY();
		rAttackRect.origin += Vec2(hero->getPositionX(), armatureY + boneY + hero->getPositionY());
        
        size = monsterVec.size();
        hurtMonsters.clear();
        FightActor *monster;
        FightActor *nearstMon = nullptr;
        float nearstDis = Director::getInstance()->getWinSize().width;
        for (int i = 0; i<size; i++) {
            monster = monsterVec.at(i);
            if (monster->getIsInvincible()) {
                continue;
            }
            if (hero->getCurrSkillTag()->getFullScreenRange() == 1) {
                hurtMonsters.pushBack(monster);
                EventCustom event(MONSTER_HURT_TAG);
                fightPair pair;
                pair.attacker = hero;
                pair.defender = monster;
                event.setUserData(&pair);
                monster->getEventDispatcher()->dispatchEvent(&event);
                hero->setIsValidAtk(true);
                continue;
            }
            if (hero->getCurrSkillTag()->getFullScreenRange() == 2) {
                if (fabs(hero->getPositionX() - monster->getPositionX()) < Director::getInstance()->getWinSize().width) {
                    if ((hero->getFlipX() && (hero->getPositionX() >= monster->getPositionX())) ||
                        (!hero->getFlipX() && (hero->getPositionX() <= monster->getPositionX()))) {
                        if (fabs(hero->getPositionX() - monster->getPositionX()) < nearstDis) {
                            nearstDis = fabs(hero->getPositionX() - monster->getPositionX());
                            nearstMon = monster;
//                            hurtMonsters.pushBack(monster);
//                            EventCustom event(MONSTER_HURT_TAG);
//                            fightPair pair;
//                            pair.attacker = hero;
//                            pair.defender = monster;
//                            event.setUserData(&pair);
//                            monster->getEventDispatcher()->dispatchEvent(&event);
//                            hero->setIsValidAtk(true);
                        }
                    }
                }
                continue;
            }
            if (fabs(hero->getPositionY() - monster->getPositionY()) < thick && fabs(hero->getPositionX() - monster->getPositionX()) < 500) {
                auto bRect = monster->getBodyRect();
                armature = monster->getArmature();
                armatureY = armature->getPositionY();
                bRect.origin += Vec2(monster->getPositionX(), armatureY+boneY+monster->getPositionY());
                if (hero->getCurrSkillTag()->getFullScreenRange() == 0) {
                    if (bRect.intersectsRect(rAttackRect)) {
                        hurtMonsters.pushBack(monster);
                        EventCustom event(MONSTER_HURT_TAG);
                        fightPair pair;
                        pair.attacker = hero;
                        pair.defender = monster;
                        event.setUserData(&pair);
                        monster->getEventDispatcher()->dispatchEvent(&event);
                        hero->setIsValidAtk(true);
                    }
                }
            }
        }
        if (hero->getCurrSkillTag()->getFullScreenRange() == 2 && nearstMon != nullptr) {
            hurtMonsters.pushBack(nearstMon);
            EventCustom event(MONSTER_HURT_TAG);
            fightPair pair;
            pair.attacker = hero;
            pair.defender = nearstMon;
            event.setUserData(&pair);
            nearstMon->getEventDispatcher()->dispatchEvent(&event);
            hero->setIsValidAtk(true);

            for (int i = 0; i<size; i++) {
                monster = monsterVec.at(i);
                if (monster == nearstMon) {
                    continue;
                }
                if (fabs(hero->getPositionX() - monster->getPositionX()) < Director::getInstance()->getWinSize().width) {
                    if ((hero->getFlipX() && (hero->getPositionX() >= monster->getPositionX())) ||
                        (!hero->getFlipX() && (hero->getPositionX() <= monster->getPositionX()))) {
                        float dis = fabs(nearstMon->getPositionX() - monster->getPositionX());
                        if (dis <= hero->getCurrSkillTag()->getAttackRect().size.width) {
                            hurtMonsters.pushBack(monster);
                            EventCustom event(MONSTER_HURT_TAG);
                            fightPair pair;
                            pair.attacker = hero;
                            pair.defender = monster;
                            event.setUserData(&pair);
                            monster->getEventDispatcher()->dispatchEvent(&event);
                            hero->setIsValidAtk(true);
                        }
                    }
                }
            }
        }

        
        if (hurtMonsters.empty()) {
            //消失血条
            showMonster = nullptr;
        } else {
            if (showMonster != nullptr) {
                if(hurtMonsters.find(showMonster) != hurtMonsters.end()){
                    showMonster = hurtMonsters.at(0);
                }
            }else{
                showMonster = hurtMonsters.at(0);
            }
        }
    }
    
    auto guard = hero->Guard;
    if (guard !=nullptr) {
        if(guard->getAtking())
        {
            Rect rAttackRect = guard->getCurrSkillTag()->getAttackRect();
            float thick = guard->getCurrSkillTag()->getAtkAreaThick();
            bool  bMonsterFlipX = guard->getFlipX();
            guard->DealAttackRectByFlip(bMonsterFlipX, &rAttackRect);
            float boneY = 0, armatureY = 0;
            auto armature = guard->getArmature();
            armatureY = armature->getPositionY();
            rAttackRect.origin += Vec2(guard->getPositionX(), armatureY + boneY + guard->getPositionY());
            
            size = monsterVec.size();
            hurtMonsters.clear();
            FightActor *monster;
            FightActor *nearstMon = nullptr;
            float nearstDis = Director::getInstance()->getWinSize().width;
            for (int i = 0; i<size; i++) {
                monster = monsterVec.at(i);
                if (monster->getIsInvincible()) {
                    continue;
                }
                if (guard->getCurrSkillTag()->getFullScreenRange() == 1) {
                    hurtMonsters.pushBack(monster);
                    EventCustom event(MONSTER_HURT_TAG);
                    fightPair pair;
                    pair.attacker = hero->Guard;
                    pair.defender = monster;
                    event.setUserData(&pair);
                    monster->getEventDispatcher()->dispatchEvent(&event);
                    guard->setIsValidAtk(true);
                    continue;
                }
                if (guard->getCurrSkillTag()->getFullScreenRange() == 2) {
                    if (fabs(guard->getPositionX() - monster->getPositionX()) < Director::getInstance()->getWinSize().width) {
                        if ((guard->getFlipX() && (guard->getPositionX() >= monster->getPositionX())) ||
                            (!guard->getFlipX() && (guard->getPositionX() <= monster->getPositionX()))) {
                            if (fabs(guard->getPositionX() - monster->getPositionX()) < nearstDis) {
                                nearstDis = fabs(guard->getPositionX() - monster->getPositionX());
                                nearstMon = monster;
                                //                            hurtMonsters.pushBack(monster);
                                //                            EventCustom event(MONSTER_HURT_TAG);
                                //                            fightPair pair;
                                //                            pair.attacker = hero;
                                //                            pair.defender = monster;
                                //                            event.setUserData(&pair);
                                //                            monster->getEventDispatcher()->dispatchEvent(&event);
                                //                            hero->setIsValidAtk(true);
                            }
                        }
                    }
                    continue;
                }
                if (fabs(guard->getPositionY() - monster->getPositionY()) < thick && fabs(guard->getPositionX() - monster->getPositionX()) < 500) {
                    auto bRect = monster->getBodyRect();
                    armature = monster->getArmature();
                    armatureY = armature->getPositionY();
                    bRect.origin += Vec2(monster->getPositionX(), armatureY+boneY+monster->getPositionY());
                    if (guard->getCurrSkillTag()->getFullScreenRange() == 0) {
                        if (bRect.intersectsRect(rAttackRect)) {
                            hurtMonsters.pushBack(monster);
                            EventCustom event(MONSTER_HURT_TAG);
                            fightPair pair;
                            pair.attacker = hero->Guard;
                            pair.defender = monster;
                            event.setUserData(&pair);
                            monster->getEventDispatcher()->dispatchEvent(&event);
                            guard->setIsValidAtk(true);
                        }
                    }
                }
            }
            if (guard->getCurrSkillTag()->getFullScreenRange() == 2 && nearstMon != nullptr) {
                hurtMonsters.pushBack(nearstMon);
                EventCustom event(MONSTER_HURT_TAG);
                fightPair pair;
                pair.attacker = hero->Guard;
                pair.defender = nearstMon;
                event.setUserData(&pair);
                nearstMon->getEventDispatcher()->dispatchEvent(&event);
                guard->setIsValidAtk(true);
                
                for (int i = 0; i<size; i++) {
                    monster = monsterVec.at(i);
                    if (monster == nearstMon) {
                        continue;
                    }
                    if (fabs(guard->getPositionX() - monster->getPositionX()) < Director::getInstance()->getWinSize().width) {
                        if ((guard->getFlipX() && (guard->getPositionX() >= monster->getPositionX())) ||
                            (!guard->getFlipX() && (guard->getPositionX() <= monster->getPositionX()))) {
                            float dis = fabs(nearstMon->getPositionX() - monster->getPositionX());
                            if (dis <= guard->getCurrSkillTag()->getAttackRect().size.width) {
                                hurtMonsters.pushBack(monster);
                                EventCustom event(MONSTER_HURT_TAG);
                                fightPair pair;
                                pair.attacker = hero->Guard;
                                pair.defender = monster;
                                event.setUserData(&pair);
                                monster->getEventDispatcher()->dispatchEvent(&event);
                                guard->setIsValidAtk(true);
                            }
                        }
                    }
                }
            }
        }
    }
    
    auto col = hero->colossus;
    if (col != nullptr) {
        if(col->getAtking())
        {
            Rect rAttackRect = col->getCurrSkillTag()->getAttackRect();
            float thick = col->getCurrSkillTag()->getAtkAreaThick();
            bool  bMonsterFlipX = col->getFlipX();
            col->DealAttackRectByFlip(bMonsterFlipX, &rAttackRect);
            float boneY = 0, armatureY = 0;
            auto armature = col->getArmature();
            armatureY = armature->getPositionY();
            rAttackRect.origin += Vec2(col->getPositionX(), armatureY + boneY + col->getPositionY());
            
            size = monsterVec.size();
            hurtMonsters.clear();
            FightActor *monster;
            FightActor *nearstMon = nullptr;
            float nearstDis = Director::getInstance()->getWinSize().width;
            for (int i = 0; i<size; i++) {
                monster = monsterVec.at(i);
                if (monster->getIsInvincible()) {
                    continue;
                }
                if (col->getCurrSkillTag()->getFullScreenRange() == 1) {
                    hurtMonsters.pushBack(monster);
                    EventCustom event(MONSTER_HURT_TAG);
                    fightPair pair;
                    pair.attacker = hero->colossus;
                    pair.defender = monster;
                    event.setUserData(&pair);
                    monster->getEventDispatcher()->dispatchEvent(&event);
                    col->setIsValidAtk(true);
                    continue;
                }
                if (col->getCurrSkillTag()->getFullScreenRange() == 2) {
                    if (fabs(col->getPositionX() - monster->getPositionX()) < Director::getInstance()->getWinSize().width) {
                        if ((col->getFlipX() && (col->getPositionX() >= monster->getPositionX())) ||
                            (!col->getFlipX() && (col->getPositionX() <= monster->getPositionX()))) {
                            if (fabs(col->getPositionX() - monster->getPositionX()) < nearstDis) {
                                nearstDis = fabs(col->getPositionX() - monster->getPositionX());
                                nearstMon = monster;
                                //                            hurtMonsters.pushBack(monster);
                                //                            EventCustom event(MONSTER_HURT_TAG);
                                //                            fightPair pair;
                                //                            pair.attacker = hero;
                                //                            pair.defender = monster;
                                //                            event.setUserData(&pair);
                                //                            monster->getEventDispatcher()->dispatchEvent(&event);
                                //                            hero->setIsValidAtk(true);
                            }
                        }
                    }
                    continue;
                }
                if (fabs(col->getPositionY() - monster->getPositionY()) < thick && fabs(col->getPositionX() - monster->getPositionX()) < 500) {
                    auto bRect = monster->getBodyRect();
                    armature = monster->getArmature();
                    armatureY = armature->getPositionY();
                    bRect.origin += Vec2(monster->getPositionX(), armatureY+boneY+monster->getPositionY());
                    if (col->getCurrSkillTag()->getFullScreenRange() == 0) {
                        if (bRect.intersectsRect(rAttackRect)) {
                            hurtMonsters.pushBack(monster);
                            EventCustom event(MONSTER_HURT_TAG);
                            fightPair pair;
                            pair.attacker = hero->colossus;
                            pair.defender = monster;
                            event.setUserData(&pair);
                            monster->getEventDispatcher()->dispatchEvent(&event);
                            col->setIsValidAtk(true);
                        }
                    }
                }
            }
            if (col->getCurrSkillTag()->getFullScreenRange() == 2 && nearstMon != nullptr) {
                hurtMonsters.pushBack(nearstMon);
                EventCustom event(MONSTER_HURT_TAG);
                fightPair pair;
                pair.attacker = hero->colossus;
                pair.defender = nearstMon;
                event.setUserData(&pair);
                nearstMon->getEventDispatcher()->dispatchEvent(&event);
                col->setIsValidAtk(true);
                
                for (int i = 0; i<size; i++) {
                    monster = monsterVec.at(i);
                    if (monster == nearstMon) {
                        continue;
                    }
                    if (fabs(col->getPositionX() - monster->getPositionX()) < Director::getInstance()->getWinSize().width) {
                        if ((col->getFlipX() && (col->getPositionX() >= monster->getPositionX())) ||
                            (!col->getFlipX() && (col->getPositionX() <= monster->getPositionX()))) {
                            float dis = fabs(nearstMon->getPositionX() - monster->getPositionX());
                            if (dis <= col->getCurrSkillTag()->getAttackRect().size.width) {
                                hurtMonsters.pushBack(monster);
                                EventCustom event(MONSTER_HURT_TAG);
                                fightPair pair;
                                pair.attacker = hero->colossus;
                                pair.defender = monster;
                                event.setUserData(&pair);
                                monster->getEventDispatcher()->dispatchEvent(&event);
                                col->setIsValidAtk(true);
                            }
                        }
                    }
                }
            }
        }
    }
    
}

void ActorLayer::setHero(Hero *hero)
{
    this->hero = hero;
    heroVec.pushBack(hero);
//    size_t size = monsterVec.size();
//    for (int i = 0; i < size; i++) {
//        dynamic_cast<Monster *>(monsterVec.at(i))->setEnemiesVec(heroVec);
//    }
}

void ActorLayer::monsterView2Hero(FightActor *monster)
{
    monster->setEnemiesVec(heroVec);
}

void ActorLayer::onExit()
{
    FightActor::removeHurtListener();
    Layer::onExit();
}

std::vector<FightActor *> ActorLayer::findEnemies(FightActor *man)
{
    std::vector<FightActor *> result;
    
    auto actors = heroVec;
    if (typeid(*man) ==  typeid(Hero)) {
        actors = monsterVec;
    }
    auto size = actors.size();
    Size viewSize = Director::getInstance()->getWinSize();
    viewSize.height = MAP_AREA_TOP-MAP_AREA_BOTTOM;
    
    auto viewRect = Rect(man->getPositionX()-viewSize.width/2, MAP_AREA_BOTTOM, viewSize.width, viewSize.height);
    for (size_t i=0; i<size; i++) {
        FightActor *actor = actors.at(i);
        if (actor->getDying() || actor->getDieLie()) {
            continue;
        }
        if (viewRect.containsPoint(actor->getPosition())) {
            result.push_back(actor);
        }
    }
    return result;
}