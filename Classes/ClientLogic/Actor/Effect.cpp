//
//  Effect.cpp
//  ssoul
//
//  Created by ff on 14-10-10.
//
//

#include "Effect.h"
#include "ClientLogic/Utils/BaseUtils.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

bool Effect::init()
{
    if (!Node::init()) {
        return false;
    }
    scaleRate = 1;
    return true;
}

bool Effect::initWithRes(std::string boneName, float scale)
{
    std::string resPath = ARM_DIR +boneName + ".ExportJson";
    //初始化和资源载入
    ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
    armature = Armature::create(boneName);
    scaleRate = scale;
    armature->setScale(scaleRate);
    armature->getAnimation()->playWithIndex(0);
    addChild(armature);
    
    return true;
}
bool Effect::initWithArmature(std::string boneName, float scale)
{
    std::string resPath = ARM_DIR +boneName + ".ExportJson";
    //初始化和资源载入
    ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
    armature = Armature::create(boneName);
    armature->setScale(scale/scaleRate);
    scaleRate = scale;
    armature->getAnimation()->playWithIndex(0);
    addChild(armature);
    
    return true;
}

bool Effect::initWithArmatureAR(std::string boneName, float scale)
{
    std::string resPath = ARM_DIR +boneName + ".ExportJson";
    //初始化和资源载入
    ArmatureDataManager::getInstance()->addArmatureFileInfo(resPath);
    armature = Armature::create(boneName);
    armature->setScale(scale/scaleRate);
    scaleRate = scale;
    armature->getAnimation()->playWithIndex(0);
    armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_0(Effect::animationEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    addChild(armature);
    
    return true;
 
}

bool Effect::initWithNumber(std::string numImgName, int num, int width, int height)
{
    hurtText = TextAtlas::create("0123456789", numImgName, width, height, "0");
    hurtText->setString(Convert2String(num));
    addChild(hurtText);
    return true;
}

bool Effect::initWithImg(std::string imgName)
{
    flagSpt = Sprite::create(imgName);
    addChild(flagSpt);
    return true;
}

void Effect::animationEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType == MovementEventType::COMPLETE)
    {
//        armature->stopAllActions();
        removeAllChildren();
        removeFromParent();
    }
}