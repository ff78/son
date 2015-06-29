//
//  Bullet.cpp
//  cocosGame
//
//  Created by ff on 14-12-15.
//
//

#include "Bullet.h"
#include "FightActor.h"
#include "../Utils/BaseUtils.h"

USING_NS_CC;
using namespace cocostudio;

bool Bullet::init()
{
    flipX = false;
    speed = 0;
    isAlive = false;
    owner = nullptr;
    armature = nullptr;
    
    return true;
}

void Bullet::initWithId(int idx, FightActor *owner, float gunPosX, float gunPosY)
{
    blackBullet = new BlackBullet();
    blackBullet->readFile(idx, "GameData/data_bullet.json");

    auto fighter = dynamic_cast<FightActor *>(owner);
    initAttr(fighter->getCurrSkillTag(), fighter);
    
    this->owner = owner;
    this->flipX = owner->getFlipX();
    
    std::string resPath(ARM_DIR);
    resPath += blackBullet->getResName();
    resPath += ".ExportJson";
    ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
    armature = Armature::create(blackBullet->getResName());
    armature->getAnimation()->playWithIndex(0);
    armature->setPositionY(gunPosY);
    scaleRate = blackBullet->getScaleRate();
    armature->setScale(scaleRate);
    addChild(armature);
    
    speed = blackBullet->getSpeed();
    if (flipX) {
        speed *= -1;
        armature->setScaleX(-scaleRate);
    }
    
    isAlive = true;
    setPosition(owner->getPosition()+Vec2(gunPosX*(flipX?-1:1), 0));
    
    if(blackBullet->getBulletType() == 2)
    {
        armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_0(Bullet::onFrameEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    }
    
}

void Bullet::initAttr(SkillTag *skill, FightActor *owner)
{
    skillId = skill->getSkillTagId()/100;
    
    
    blackBullet->setIceResist(skill->getIceResist());
    blackBullet->setFireResist(skill->getFireResist());
    blackBullet->setThunderResist(skill->getThunderResist());
    blackBullet->setWindResist(skill->getWindResist());
    blackBullet->setLightResist(skill->getLightResist());
    blackBullet->setDarkResist(skill->getDarkResist());
    
    auto actor = owner->getBlackActor();
    if (blackBullet->getIceResist() != 0) {
        blackBullet->setIceResist(actor->getIceResist()+blackBullet->getIceResist());
    }
    if (blackBullet->getFireResist() != 0) {
        blackBullet->setFireResist(actor->getFireResist()+blackBullet->getFireResist());
    }
    if (blackBullet->getThunderResist() != 0) {
        blackBullet->setThunderResist(actor->getThunderResist()+blackBullet->getThunderResist());
    }
    if (blackBullet->getWindResist() != 0) {
        blackBullet->setWindResist(actor->getWindResist()+blackBullet->getWindResist());
    }
    if (blackBullet->getLightResist() != 0) {
        blackBullet->setLightResist(actor->getLightResist()+blackBullet->getLightResist());
    }
    if (blackBullet->getDarkResist() != 0) {
        blackBullet->setDarkResist(actor->getDarkResist()+blackBullet->getDarkResist());
    }
    blackBullet->setAttack(blackBullet->getAttack() * actor->getAttack());

    if (blackBullet->getBulletType() == 2) {
        int skillTagId = skill->getSkillTagId() + 1;
        auto blackOwner = owner->getBlackActor();
        auto ownerTags = blackOwner->selSkillTags;
        while (ownerTags.find(skillTagId) != ownerTags.end() && skillTagId < skillId*100 +100) {
            blackBullet->selSkillTags[skillTagId] = ownerTags[skillTagId];
            skillTagId++;
        }
        currSkill = blackOwner->selSkills[skillId];
    }
}

void Bullet::Logic(float dt)
{
    setPosition(getPosition()+Vec2(speed, 0));
}

Rect Bullet::getAtkRect()
{
    if(!flipX)
    {
        return Rect(-50, 0, blackBullet->getSplashWidth(), blackBullet->getSplashHeight());
    }
    return Rect(50-blackBullet->getSplashWidth(), 0, blackBullet->getSplashWidth(), blackBullet->getSplashHeight());
}

bool Bullet::isOutsideCamera(float cameraPosX)
{
    if (getPositionX()<-50 || getPositionX()>MAP_AREA_WIDTH+50) {
        return true;
    }
    
//    float cameraPosX = YNCamera::getInstance()->getPositionX();
    if (abs(cameraPosX - getPositionX()) < 530) {
        return false;
    }
    
    if (cameraPosX < 480) {
        if (getPositionX() - cameraPosX > 960-cameraPosX+50 ) {
            return true;
        }
    }else if(cameraPosX > MAP_AREA_WIDTH - 480) {
        if (cameraPosX - getPositionX() > 960 + 50 - (MAP_AREA_WIDTH - cameraPosX)) {
            return true;
        }
    }
    return false;
}

bool Bullet::isAnimationOver()
{
    return armature->getAnimation()->isComplete();
}

void Bullet::onFrameEvent(cocostudio::Bone *bone, const std::string& evt, int originFrameIndex, int currentFrameIndex)
{
    
    auto *val = evt.c_str();
    if (strcmp(val, "") == 0) {
        return;
    }
    
    auto result = YNBaseUtil::splitString(evt, ",");
    for (int i = 0; i<result.size(); i++) {
        if (strcmp(result[i].c_str(), "startAttack") == 0) {
            //            log("start Attack @ %d", action);
            atking = true;
        }
        if (strcmp(result[i].c_str(), "endAttack") == 0) {
            atking = false;
        }
        if (strcmp(result[i].c_str(), "attackHead") == 0) {
            attackHead = true;
            attackWaist = false;
        }
        if (strcmp(result[i].c_str(), "attackWaist") == 0) {
            attackWaist = true;
            attackHead = false;
        }
        if (strcmp(result[i].c_str(), "hit2air") == 0) {
            
            hit2Air = true;
        }
        
        if (strncmp(result[i].c_str(), "attackTag", strlen("attackTag")) == 0) {
            size_t tagLen = strlen("attackTag");
            size_t sLen = result[i].length();
            attackTag = atoi(result[i].substr(tagLen, sLen - tagLen).c_str());
            attackTag += currSkill->getSkillID()*100;
            currSkillTag = blackBullet->selSkillTags[attackTag];
        }
        
        if (strcmp(result[i].c_str(), "bound2Air") == 0)
        {
            hit2Ground = true;
        }
        
        if (strcmp(result[i].c_str(), "bound2Wall") == 0) {
            hit2Wall = true;
        }
            }
    
}