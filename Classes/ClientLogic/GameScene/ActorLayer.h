//
//  ActorLayer.h
//  soul
//
//  Created by ff on 14-9-15.
//
//

#ifndef __soul__ActorLayer__
#define __soul__ActorLayer__

#include "cocos2d.h"
#include "../Actor/FightActor.h"
#include "../Actor/Hero.h"
#include "../Actor/Monster.h"
#include "HitEffectLayer.h"
#include "../FightDefine.h"
#include "../Actor/Bullet.h"

class ActorLayer : public cocos2d::Layer
{
public:
    
    bool init();
    void onExit();
    CREATE_FUNC(ActorLayer);
    
    void setHero(Hero *hero);
    void update(float dt);
    void fillHitEffect();
    void addMonster(int monId, int teamId, float x, float y);
    void addGear(int gearId, float x, float y, bool flipX);
    void addBullet(int idx, FightActor *actor, float gunPosY, float gunPosX, SkillTag *skillTag);
    void addActorHitEffect(FightActor *actor);
    void monsterView2Hero(FightActor *monster);
    void removeMonster(Monster *monster);
    void removeBullet(Bullet *bullet);
    
    std::vector<FightActor *> findEnemies(FightActor *man);
private:
    cocos2d::Vector<FightActor *> heroVec;
    cocos2d::Vector<FightActor *> monsterVec;
    cocos2d::Vector<FightActor *> hurtMonsters;
    cocos2d::Vector<Bullet *> monsterBullets;
    cocos2d::Vector<Bullet *> heroBullets;
    cocos2d::Vector<FightActor *> gearVec;
//    Hero *hero;
    CC_SYNTHESIZE_READONLY(Hero *, hero, Hero);
    CC_SYNTHESIZE_READONLY(FightActor *, showMonster, ShowMonster);
    CC_SYNTHESIZE_READONLY(HitEffectLayer *, hitEffeLayer, HitEffeLayer);
    CC_SYNTHESIZE_READONLY(Layer *, ghostLayer, GhostLayer);
};

#endif /* defined(__soul__ActorLayer__) */
