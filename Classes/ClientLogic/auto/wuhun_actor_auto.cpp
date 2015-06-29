#include "wuhun_actor_auto.hpp"
#include "ClientLogic/Actor/Actor.h"
#include "ClientLogic/Actor/FightActor.h"
#include "ClientLogic/Actor/Hero.h"
#include "ClientLogic/Actor/Monster.h"
#include "DataModule/BlackActor.h"
#include "DataModule/Skill.h"
#include "DataModule/SkillTag.h"
#include "DataModule/BlackBullet.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_wuhun_actor_Actor_getLocalBonePoint(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getLocalBonePoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Point ret = cobj->getLocalBonePoint();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLocalBonePoint",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getLocalBonePoint'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_getRushReady(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getRushReady'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getRushReady();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRushReady",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getRushReady'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_exitState(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_exitState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->exitState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "exitState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_exitState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_arriveTargetPos(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_arriveTargetPos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->arriveTargetPos();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "arriveTargetPos",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_arriveTargetPos'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_getScaleRate(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getScaleRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getScaleRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getScaleRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getScaleRate'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_getPosY(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getPosY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getPosY();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPosY",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getPosY'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_setPosY(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_setPosY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setPosY(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setPosY",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_setPosY'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_setPosX(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_setPosX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setPosX(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setPosX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_setPosX'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_setActorShowPos(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_setActorShowPos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setActorShowPos(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setActorShowPos",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_setActorShowPos'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_animOver(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_animOver'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->animOver();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "animOver",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_animOver'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_calBoneMove(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_calBoneMove'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Point ret = cobj->calBoneMove();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "calBoneMove",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_calBoneMove'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_setRushReady(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_setRushReady'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setRushReady(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setRushReady",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_setRushReady'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_enterState(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_enterState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->enterState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "enterState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_enterState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_Move2Target(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_Move2Target'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->Move2Target(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Move2Target",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_Move2Target'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_arrivePos(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_arrivePos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        bool ret = cobj->arrivePos(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "arrivePos",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_arrivePos'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_setLocalBonePoint(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_setLocalBonePoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setLocalBonePoint(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setLocalBonePoint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_setLocalBonePoint'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_getFlipX(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getFlipX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getFlipX();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFlipX",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getFlipX'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_changeState(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_changeState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->changeState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "changeState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_changeState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_stopMove(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_stopMove'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->stopMove();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "stopMove",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_stopMove'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_doFlag(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_doFlag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->doFlag(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "doFlag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_doFlag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_startMove(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_startMove'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->startMove();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "startMove",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_startMove'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_setFlipX(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_setFlipX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setFlipX(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFlipX",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_setFlipX'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_updateState(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_updateState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateState();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "updateState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_updateState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_getRush(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getRush'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getRush();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRush",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getRush'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_getBodyRect(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getBodyRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Rect ret = cobj->getBodyRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBodyRect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getBodyRect'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_switch2NextState(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_switch2NextState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->switch2NextState(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "switch2NextState",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_switch2NextState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_getPosX(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getPosX'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getPosX();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPosX",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getPosX'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_getTargetMovePos(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getTargetMovePos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Point ret = cobj->getTargetMovePos();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTargetMovePos",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getTargetMovePos'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_changeActionWithName(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_changeActionWithName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->changeActionWithName(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "changeActionWithName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_changeActionWithName'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_updateAI(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_updateAI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateAI();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "updateAI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_updateAI'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_Run2Target(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_Run2Target'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Point arg0;

        ok &= luaval_to_point(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->Run2Target(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Run2Target",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_Run2Target'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_setDir(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_setDir'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setDir(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDir",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_setDir'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_getArmature(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_getArmature'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocostudio::Armature* ret = cobj->getArmature();
        object_to_luaval<cocostudio::Armature>(tolua_S, "ccs.Armature",(cocostudio::Armature*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getArmature",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_getArmature'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_readyRush(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_readyRush'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->readyRush();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "readyRush",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_readyRush'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_logic(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_logic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->logic(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "logic",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_logic'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_isOutWindow(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_isOutWindow'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isOutWindow();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isOutWindow",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_isOutWindow'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Actor_idleTimeEnough(lua_State* tolua_S)
{
    int argc = 0;
    Actor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Actor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Actor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Actor_idleTimeEnough'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->idleTimeEnough();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "idleTimeEnough",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Actor_idleTimeEnough'.",&tolua_err);
#endif

    return 0;
}
static int lua_wuhun_actor_Actor_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Actor)");
    return 0;
}

int lua_register_wuhun_actor_Actor(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"Actor");
    tolua_cclass(tolua_S,"Actor","Actor","cc.Node",nullptr);

    tolua_beginmodule(tolua_S,"Actor");
        tolua_function(tolua_S,"getLocalBonePoint",lua_wuhun_actor_Actor_getLocalBonePoint);
        tolua_function(tolua_S,"getRushReady",lua_wuhun_actor_Actor_getRushReady);
        tolua_function(tolua_S,"exitState",lua_wuhun_actor_Actor_exitState);
        tolua_function(tolua_S,"arriveTargetPos",lua_wuhun_actor_Actor_arriveTargetPos);
        tolua_function(tolua_S,"getScaleRate",lua_wuhun_actor_Actor_getScaleRate);
        tolua_function(tolua_S,"getPosY",lua_wuhun_actor_Actor_getPosY);
        tolua_function(tolua_S,"setPosY",lua_wuhun_actor_Actor_setPosY);
        tolua_function(tolua_S,"setPosX",lua_wuhun_actor_Actor_setPosX);
        tolua_function(tolua_S,"setActorShowPos",lua_wuhun_actor_Actor_setActorShowPos);
        tolua_function(tolua_S,"animOver",lua_wuhun_actor_Actor_animOver);
        tolua_function(tolua_S,"calBoneMove",lua_wuhun_actor_Actor_calBoneMove);
        tolua_function(tolua_S,"setRushReady",lua_wuhun_actor_Actor_setRushReady);
        tolua_function(tolua_S,"enterState",lua_wuhun_actor_Actor_enterState);
        tolua_function(tolua_S,"Move2Target",lua_wuhun_actor_Actor_Move2Target);
        tolua_function(tolua_S,"arrivePos",lua_wuhun_actor_Actor_arrivePos);
        tolua_function(tolua_S,"setLocalBonePoint",lua_wuhun_actor_Actor_setLocalBonePoint);
        tolua_function(tolua_S,"getFlipX",lua_wuhun_actor_Actor_getFlipX);
        tolua_function(tolua_S,"changeState",lua_wuhun_actor_Actor_changeState);
        tolua_function(tolua_S,"stopMove",lua_wuhun_actor_Actor_stopMove);
        tolua_function(tolua_S,"doFlag",lua_wuhun_actor_Actor_doFlag);
        tolua_function(tolua_S,"startMove",lua_wuhun_actor_Actor_startMove);
        tolua_function(tolua_S,"setFlipX",lua_wuhun_actor_Actor_setFlipX);
        tolua_function(tolua_S,"updateState",lua_wuhun_actor_Actor_updateState);
        tolua_function(tolua_S,"getRush",lua_wuhun_actor_Actor_getRush);
        tolua_function(tolua_S,"getBodyRect",lua_wuhun_actor_Actor_getBodyRect);
        tolua_function(tolua_S,"switch2NextState",lua_wuhun_actor_Actor_switch2NextState);
        tolua_function(tolua_S,"getPosX",lua_wuhun_actor_Actor_getPosX);
        tolua_function(tolua_S,"getTargetMovePos",lua_wuhun_actor_Actor_getTargetMovePos);
        tolua_function(tolua_S,"changeActionWithName",lua_wuhun_actor_Actor_changeActionWithName);
        tolua_function(tolua_S,"updateAI",lua_wuhun_actor_Actor_updateAI);
        tolua_function(tolua_S,"Run2Target",lua_wuhun_actor_Actor_Run2Target);
        tolua_function(tolua_S,"setDir",lua_wuhun_actor_Actor_setDir);
        tolua_function(tolua_S,"getArmature",lua_wuhun_actor_Actor_getArmature);
        tolua_function(tolua_S,"readyRush",lua_wuhun_actor_Actor_readyRush);
        tolua_function(tolua_S,"logic",lua_wuhun_actor_Actor_logic);
        tolua_function(tolua_S,"isOutWindow",lua_wuhun_actor_Actor_isOutWindow);
        tolua_function(tolua_S,"idleTimeEnough",lua_wuhun_actor_Actor_idleTimeEnough);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Actor).name();
    g_luaType[typeName] = "Actor";
    g_typeCast["Actor"] = "Actor";
    return 1;
}

int lua_wuhun_actor_Skill_getXuliDur(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getXuliDur'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getXuliDur();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getXuliDur",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getXuliDur'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_geticonStr(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_geticonStr'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->geticonStr();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "geticonStr",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_geticonStr'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getConsumeAP(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getConsumeAP'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getConsumeAP();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getConsumeAP",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getConsumeAP'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getName(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getName'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_readFile(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_readFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        std::string arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->readFile(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "readFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_readFile'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getConsumeMP(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getConsumeMP'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getConsumeMP();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getConsumeMP",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getConsumeMP'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getSkillID(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getSkillID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getSkillID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSkillID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getSkillID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getEffectFollowY(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getEffectFollowY'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getEffectFollowY();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getEffectFollowY",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getEffectFollowY'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getConsumeHP(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getConsumeHP'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getConsumeHP();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getConsumeHP",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getConsumeHP'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getCanBreak(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getCanBreak'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getCanBreak();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCanBreak",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getCanBreak'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getBrokeID(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getBrokeID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getBrokeID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBrokeID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getBrokeID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getFrontEffectStr(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getFrontEffectStr'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::vector<std::string> ret = cobj->getFrontEffectStr();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFrontEffectStr",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getFrontEffectStr'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getBackScale(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getBackScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::vector<float, std::allocator<float> > ret = cobj->getBackScale();
        ccvector_float_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBackScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getBackScale'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getAction(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getAction();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getAction'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getBackEffectStr(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getBackEffectStr'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::vector<std::string> ret = cobj->getBackEffectStr();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBackEffectStr",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getBackEffectStr'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getFrontScale(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getFrontScale'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::vector<float, std::allocator<float> > ret = cobj->getFrontScale();
        ccvector_float_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFrontScale",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getFrontScale'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getLinkID(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getLinkID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getLinkID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLinkID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getLinkID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getLinkDur(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getLinkDur'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getLinkDur();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLinkDur",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getLinkDur'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getBaseSkillID(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getBaseSkillID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getBaseSkillID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBaseSkillID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getBaseSkillID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getXuliId(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getXuliId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getXuliId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getXuliId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getXuliId'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_getCoolDownDur(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Skill*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Skill_getCoolDownDur'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getCoolDownDur();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCoolDownDur",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_getCoolDownDur'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Skill_readFileAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"Skill",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        Skill::readFileAll(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "readFileAll",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_readFileAll'.",&tolua_err);
#endif
    return 0;
}
int lua_wuhun_actor_Skill_constructor(lua_State* tolua_S)
{
    int argc = 0;
    Skill* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new Skill();
        tolua_pushusertype(tolua_S,(void*)cobj,"Skill");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Skill",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Skill_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_wuhun_actor_Skill_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Skill)");
    return 0;
}

int lua_register_wuhun_actor_Skill(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"Skill");
    tolua_cclass(tolua_S,"Skill","Skill","",nullptr);

    tolua_beginmodule(tolua_S,"Skill");
        tolua_function(tolua_S,"new",lua_wuhun_actor_Skill_constructor);
        tolua_function(tolua_S,"getXuliDur",lua_wuhun_actor_Skill_getXuliDur);
        tolua_function(tolua_S,"geticonStr",lua_wuhun_actor_Skill_geticonStr);
        tolua_function(tolua_S,"getConsumeAP",lua_wuhun_actor_Skill_getConsumeAP);
        tolua_function(tolua_S,"getName",lua_wuhun_actor_Skill_getName);
        tolua_function(tolua_S,"readFile",lua_wuhun_actor_Skill_readFile);
        tolua_function(tolua_S,"getConsumeMP",lua_wuhun_actor_Skill_getConsumeMP);
        tolua_function(tolua_S,"getSkillID",lua_wuhun_actor_Skill_getSkillID);
        tolua_function(tolua_S,"getEffectFollowY",lua_wuhun_actor_Skill_getEffectFollowY);
        tolua_function(tolua_S,"getConsumeHP",lua_wuhun_actor_Skill_getConsumeHP);
        tolua_function(tolua_S,"getCanBreak",lua_wuhun_actor_Skill_getCanBreak);
        tolua_function(tolua_S,"getBrokeID",lua_wuhun_actor_Skill_getBrokeID);
        tolua_function(tolua_S,"getFrontEffectStr",lua_wuhun_actor_Skill_getFrontEffectStr);
        tolua_function(tolua_S,"getBackScale",lua_wuhun_actor_Skill_getBackScale);
        tolua_function(tolua_S,"getAction",lua_wuhun_actor_Skill_getAction);
        tolua_function(tolua_S,"getBackEffectStr",lua_wuhun_actor_Skill_getBackEffectStr);
        tolua_function(tolua_S,"getFrontScale",lua_wuhun_actor_Skill_getFrontScale);
        tolua_function(tolua_S,"getLinkID",lua_wuhun_actor_Skill_getLinkID);
        tolua_function(tolua_S,"getLinkDur",lua_wuhun_actor_Skill_getLinkDur);
        tolua_function(tolua_S,"getBaseSkillID",lua_wuhun_actor_Skill_getBaseSkillID);
        tolua_function(tolua_S,"getXuliId",lua_wuhun_actor_Skill_getXuliId);
        tolua_function(tolua_S,"getCoolDownDur",lua_wuhun_actor_Skill_getCoolDownDur);
        tolua_function(tolua_S,"readFileAll", lua_wuhun_actor_Skill_readFileAll);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Skill).name();
    g_luaType[typeName] = "Skill";
    g_typeCast["Skill"] = "Skill";
    return 1;
}

int lua_wuhun_actor_SkillTag_getBuff2Rate(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getBuff2Rate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getBuff2Rate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBuff2Rate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getBuff2Rate'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getSkillSoundRes(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getSkillSoundRes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getSkillSoundRes();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSkillSoundRes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getSkillSoundRes'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getAtkStiffDur(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getAtkStiffDur'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getAtkStiffDur();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAtkStiffDur",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getAtkStiffDur'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getAirAtkStiffDur(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getAirAtkStiffDur'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getAirAtkStiffDur();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAirAtkStiffDur",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getAirAtkStiffDur'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getAirHitStiffDur(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getAirHitStiffDur'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getAirHitStiffDur();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAirHitStiffDur",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getAirHitStiffDur'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getChatterLoop(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getChatterLoop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getChatterLoop();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getChatterLoop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getChatterLoop'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getBuff1Rate(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getBuff1Rate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getBuff1Rate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBuff1Rate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getBuff1Rate'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getAirChatterLoop(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getAirChatterLoop'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getAirChatterLoop();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAirChatterLoop",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getAirChatterLoop'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getHitDownVal(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getHitDownVal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getHitDownVal();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHitDownVal",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getHitDownVal'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getFireResist(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getFireResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getFireResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFireResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getFireResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getFullScreenRange(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getFullScreenRange'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getFullScreenRange();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFullScreenRange",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getFullScreenRange'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getHitSoundRes(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getHitSoundRes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getHitSoundRes();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHitSoundRes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getHitSoundRes'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_readFile(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_readFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        std::string arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->readFile(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "readFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_readFile'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getSkillTagId(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getSkillTagId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getSkillTagId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSkillTagId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getSkillTagId'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getFloatRate(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getFloatRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getFloatRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFloatRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getFloatRate'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getAttackRect(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getAttackRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Rect ret = cobj->getAttackRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAttackRect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getAttackRect'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getHitCount(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getHitCount'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getHitCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHitCount",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getHitCount'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getHitBackSpeed(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getHitBackSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getHitBackSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHitBackSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getHitBackSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getBoundUpRate(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getBoundUpRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getBoundUpRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBoundUpRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getBoundUpRate'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getLightResist(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getLightResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getLightResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLightResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getLightResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getDarkResist(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getDarkResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getDarkResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDarkResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getDarkResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getHitEffect(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getHitEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getHitEffect();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHitEffect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getHitEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getIceResist(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getIceResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getIceResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIceResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getIceResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getAirAtkUpVal(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getAirAtkUpVal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getAirAtkUpVal();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAirAtkUpVal",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getAirAtkUpVal'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_gethitFlyRate(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_gethitFlyRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->gethitFlyRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "gethitFlyRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_gethitFlyRate'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getThunderResist(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getThunderResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getThunderResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getThunderResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getThunderResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getWindResist(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getWindResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getWindResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getWindResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getWindResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getBuff1Id(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getBuff1Id'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getBuff1Id();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBuff1Id",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getBuff1Id'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getBuff2Id(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getBuff2Id'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getBuff2Id();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBuff2Id",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getBuff2Id'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getAirHitBackSpeed(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getAirHitBackSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getAirHitBackSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAirHitBackSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getAirHitBackSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getAttack(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getAttack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getAttack();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAttack",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getAttack'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getBulletID(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getBulletID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getBulletID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBulletID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getBulletID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_getHitStiffDur(lua_State* tolua_S)
{
    int argc = 0;
    SkillTag* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SkillTag*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_SkillTag_getHitStiffDur'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getHitStiffDur();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHitStiffDur",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_getHitStiffDur'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_SkillTag_readFileAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        SkillTag::readFileAll(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "readFileAll",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_readFileAll'.",&tolua_err);
#endif
    return 0;
}
int lua_wuhun_actor_SkillTag_DealWithRectString(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SkillTag",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        cocos2d::Rect* arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        ok &= luaval_to_object<cocos2d::Rect>(tolua_S, 3, "cc.Rect",&arg1);
        if(!ok)
            return 0;
        SkillTag::DealWithRectString(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "DealWithRectString",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_SkillTag_DealWithRectString'.",&tolua_err);
#endif
    return 0;
}
static int lua_wuhun_actor_SkillTag_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SkillTag)");
    return 0;
}

int lua_register_wuhun_actor_SkillTag(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"SkillTag");
    tolua_cclass(tolua_S,"SkillTag","SkillTag","",nullptr);

    tolua_beginmodule(tolua_S,"SkillTag");
        tolua_function(tolua_S,"getBuff2Rate",lua_wuhun_actor_SkillTag_getBuff2Rate);
        tolua_function(tolua_S,"getSkillSoundRes",lua_wuhun_actor_SkillTag_getSkillSoundRes);
        tolua_function(tolua_S,"getAtkStiffDur",lua_wuhun_actor_SkillTag_getAtkStiffDur);
        tolua_function(tolua_S,"getAirAtkStiffDur",lua_wuhun_actor_SkillTag_getAirAtkStiffDur);
        tolua_function(tolua_S,"getAirHitStiffDur",lua_wuhun_actor_SkillTag_getAirHitStiffDur);
        tolua_function(tolua_S,"getChatterLoop",lua_wuhun_actor_SkillTag_getChatterLoop);
        tolua_function(tolua_S,"getBuff1Rate",lua_wuhun_actor_SkillTag_getBuff1Rate);
        tolua_function(tolua_S,"getAirChatterLoop",lua_wuhun_actor_SkillTag_getAirChatterLoop);
        tolua_function(tolua_S,"getHitDownVal",lua_wuhun_actor_SkillTag_getHitDownVal);
        tolua_function(tolua_S,"getFireResist",lua_wuhun_actor_SkillTag_getFireResist);
        tolua_function(tolua_S,"getFullScreenRange",lua_wuhun_actor_SkillTag_getFullScreenRange);
        tolua_function(tolua_S,"getHitSoundRes",lua_wuhun_actor_SkillTag_getHitSoundRes);
        tolua_function(tolua_S,"readFile",lua_wuhun_actor_SkillTag_readFile);
        tolua_function(tolua_S,"getSkillTagId",lua_wuhun_actor_SkillTag_getSkillTagId);
        tolua_function(tolua_S,"getFloatRate",lua_wuhun_actor_SkillTag_getFloatRate);
        tolua_function(tolua_S,"getAttackRect",lua_wuhun_actor_SkillTag_getAttackRect);
        tolua_function(tolua_S,"getHitCount",lua_wuhun_actor_SkillTag_getHitCount);
        tolua_function(tolua_S,"getHitBackSpeed",lua_wuhun_actor_SkillTag_getHitBackSpeed);
        tolua_function(tolua_S,"getBoundUpRate",lua_wuhun_actor_SkillTag_getBoundUpRate);
        tolua_function(tolua_S,"getLightResist",lua_wuhun_actor_SkillTag_getLightResist);
        tolua_function(tolua_S,"getDarkResist",lua_wuhun_actor_SkillTag_getDarkResist);
        tolua_function(tolua_S,"getHitEffect",lua_wuhun_actor_SkillTag_getHitEffect);
        tolua_function(tolua_S,"getIceResist",lua_wuhun_actor_SkillTag_getIceResist);
        tolua_function(tolua_S,"getAirAtkUpVal",lua_wuhun_actor_SkillTag_getAirAtkUpVal);
        tolua_function(tolua_S,"gethitFlyRate",lua_wuhun_actor_SkillTag_gethitFlyRate);
        tolua_function(tolua_S,"getThunderResist",lua_wuhun_actor_SkillTag_getThunderResist);
        tolua_function(tolua_S,"getWindResist",lua_wuhun_actor_SkillTag_getWindResist);
        tolua_function(tolua_S,"getBuff1Id",lua_wuhun_actor_SkillTag_getBuff1Id);
        tolua_function(tolua_S,"getBuff2Id",lua_wuhun_actor_SkillTag_getBuff2Id);
        tolua_function(tolua_S,"getAirHitBackSpeed",lua_wuhun_actor_SkillTag_getAirHitBackSpeed);
        tolua_function(tolua_S,"getAttack",lua_wuhun_actor_SkillTag_getAttack);
        tolua_function(tolua_S,"getBulletID",lua_wuhun_actor_SkillTag_getBulletID);
        tolua_function(tolua_S,"getHitStiffDur",lua_wuhun_actor_SkillTag_getHitStiffDur);
        tolua_function(tolua_S,"readFileAll", lua_wuhun_actor_SkillTag_readFileAll);
        tolua_function(tolua_S,"DealWithRectString", lua_wuhun_actor_SkillTag_DealWithRectString);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(SkillTag).name();
    g_luaType[typeName] = "SkillTag";
    g_typeCast["SkillTag"] = "SkillTag";
    return 1;
}

int lua_wuhun_actor_BlackActor_getSkillCID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getSkillCID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getSkillCID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSkillCID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getSkillCID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getHitRatio(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getHitRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getHitRatio();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHitRatio",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getHitRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setSkillDID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setSkillDID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setSkillDID(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSkillDID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setSkillDID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getStateMachineFile(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getStateMachineFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getStateMachineFile();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getStateMachineFile",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getStateMachineFile'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getMoveSpeed(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getMoveSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getMoveSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getMoveSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getMoveSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getAp(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getAp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getAp();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAp",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getAp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setSkillBID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setSkillBID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setSkillBID(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSkillBID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setSkillBID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getLevel(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getLevel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getLevel();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLevel",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getLevel'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setSkillCID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setSkillCID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setSkillCID(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSkillCID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setSkillCID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setRunAttack2ID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setRunAttack2ID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setRunAttack2ID(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setRunAttack2ID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setRunAttack2ID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setSkillSPID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setSkillSPID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setSkillSPID(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSkillSPID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setSkillSPID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getDarkResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getDarkResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getDarkResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDarkResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getDarkResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_readRelativeSkillTag(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_readRelativeSkillTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->readRelativeSkillTag(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "readRelativeSkillTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_readRelativeSkillTag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getFireResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getFireResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getFireResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFireResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getFireResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_initSelSkill(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_initSelSkill'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->initSelSkill();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSelSkill",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_initSelSkill'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getSkillDID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getSkillDID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getSkillDID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSkillDID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getSkillDID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getName(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getName'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_initSelSkillTag(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_initSelSkillTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->initSelSkillTag();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initSelSkillTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_initSelSkillTag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setHp(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setHp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setHp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setHp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setHp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_readFile(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_readFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        std::string arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->readFile(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "readFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_readFile'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getResName(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getResName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getResName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getResName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getResName'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getMp(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getMp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getMp();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getMp",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getMp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getLightResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getLightResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getLightResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLightResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getLightResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getActorID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getActorID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getActorID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getActorID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getActorID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setRunAttack1ID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setRunAttack1ID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setRunAttack1ID(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setRunAttack1ID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setRunAttack1ID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getRunAttackID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getRunAttackID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getRunAttackID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRunAttackID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getRunAttackID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getDeHitDownVal(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getDeHitDownVal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getDeHitDownVal();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDeHitDownVal",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getDeHitDownVal'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setRunAttackID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setRunAttackID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setRunAttackID(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setRunAttackID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setRunAttackID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getTenacity(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getTenacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getTenacity();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTenacity",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getTenacity'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getAtk1SkillID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getAtk1SkillID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getAtk1SkillID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAtk1SkillID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getAtk1SkillID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getMaxHp(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getMaxHp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getMaxHp();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getMaxHp",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getMaxHp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getRushSpeed(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getRushSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getRushSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRushSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getRushSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setSkillAID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setSkillAID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setSkillAID(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSkillAID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setSkillAID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setMp(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setMp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setMp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setMp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setMp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getDodgeRatio(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getDodgeRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getDodgeRatio();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDodgeRatio",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getDodgeRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getSkillSPID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getSkillSPID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getSkillSPID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSkillSPID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getSkillSPID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getDefence(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getDefence'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getDefence();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDefence",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getDefence'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getIceResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getIceResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getIceResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIceResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getIceResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getAtk3SkillID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getAtk3SkillID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getAtk3SkillID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAtk3SkillID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getAtk3SkillID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setAtkSkillID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setAtkSkillID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setAtkSkillID(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAtkSkillID",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setAtkSkillID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getScaleRate(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getScaleRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getScaleRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getScaleRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getScaleRate'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_readRelativeSkill(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_readRelativeSkill'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->readRelativeSkill(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "readRelativeSkill",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_readRelativeSkill'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getThunderResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getThunderResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getThunderResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getThunderResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getThunderResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getWindResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getWindResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getWindResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getWindResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getWindResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getCritRatio(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getCritRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getCritRatio();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCritRatio",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getCritRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getAtk4SkillID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getAtk4SkillID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getAtk4SkillID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAtk4SkillID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getAtk4SkillID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getMaxAp(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getMaxAp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getMaxAp();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getMaxAp",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getMaxAp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getRunAttack2ID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getRunAttack2ID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getRunAttack2ID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRunAttack2ID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getRunAttack2ID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getSkillBID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getSkillBID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getSkillBID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSkillBID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getSkillBID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getRunAttack1ID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getRunAttack1ID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getRunAttack1ID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRunAttack1ID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getRunAttack1ID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getAttack(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getAttack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getAttack();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAttack",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getAttack'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getAtk2SkillID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getAtk2SkillID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getAtk2SkillID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAtk2SkillID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getAtk2SkillID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getSkillAID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getSkillAID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getSkillAID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSkillAID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getSkillAID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_setAp(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_setAp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setAp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_setAp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getHp(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getHp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getHp();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHp",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getHp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getAtkSkillID(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getAtkSkillID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getAtkSkillID();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAtkSkillID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getAtkSkillID'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_getMaxMp(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_getMaxMp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getMaxMp();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getMaxMp",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_getMaxMp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_initPlayerData(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackActor_initPlayerData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->initPlayerData();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initPlayerData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_initPlayerData'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackActor_constructor(lua_State* tolua_S)
{
    int argc = 0;
    BlackActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new BlackActor();
        tolua_pushusertype(tolua_S,(void*)cobj,"BlackActor");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "BlackActor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackActor_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_wuhun_actor_BlackActor_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BlackActor)");
    return 0;
}

int lua_register_wuhun_actor_BlackActor(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"BlackActor");
    tolua_cclass(tolua_S,"BlackActor","BlackActor","",nullptr);

    tolua_beginmodule(tolua_S,"BlackActor");
        tolua_function(tolua_S,"new",lua_wuhun_actor_BlackActor_constructor);
        tolua_function(tolua_S,"getSkillCID",lua_wuhun_actor_BlackActor_getSkillCID);
        tolua_function(tolua_S,"getHitRatio",lua_wuhun_actor_BlackActor_getHitRatio);
        tolua_function(tolua_S,"setSkillDID",lua_wuhun_actor_BlackActor_setSkillDID);
        tolua_function(tolua_S,"getStateMachineFile",lua_wuhun_actor_BlackActor_getStateMachineFile);
        tolua_function(tolua_S,"getMoveSpeed",lua_wuhun_actor_BlackActor_getMoveSpeed);
        tolua_function(tolua_S,"getAp",lua_wuhun_actor_BlackActor_getAp);
        tolua_function(tolua_S,"setSkillBID",lua_wuhun_actor_BlackActor_setSkillBID);
        tolua_function(tolua_S,"getLevel",lua_wuhun_actor_BlackActor_getLevel);
        tolua_function(tolua_S,"setSkillCID",lua_wuhun_actor_BlackActor_setSkillCID);
        tolua_function(tolua_S,"setRunAttack2ID",lua_wuhun_actor_BlackActor_setRunAttack2ID);
        tolua_function(tolua_S,"setSkillSPID",lua_wuhun_actor_BlackActor_setSkillSPID);
        tolua_function(tolua_S,"getDarkResist",lua_wuhun_actor_BlackActor_getDarkResist);
        tolua_function(tolua_S,"readRelativeSkillTag",lua_wuhun_actor_BlackActor_readRelativeSkillTag);
        tolua_function(tolua_S,"getFireResist",lua_wuhun_actor_BlackActor_getFireResist);
        tolua_function(tolua_S,"initSelSkill",lua_wuhun_actor_BlackActor_initSelSkill);
        tolua_function(tolua_S,"getSkillDID",lua_wuhun_actor_BlackActor_getSkillDID);
        tolua_function(tolua_S,"getName",lua_wuhun_actor_BlackActor_getName);
        tolua_function(tolua_S,"initSelSkillTag",lua_wuhun_actor_BlackActor_initSelSkillTag);
        tolua_function(tolua_S,"setHp",lua_wuhun_actor_BlackActor_setHp);
        tolua_function(tolua_S,"readFile",lua_wuhun_actor_BlackActor_readFile);
        tolua_function(tolua_S,"getResName",lua_wuhun_actor_BlackActor_getResName);
        tolua_function(tolua_S,"getMp",lua_wuhun_actor_BlackActor_getMp);
        tolua_function(tolua_S,"getLightResist",lua_wuhun_actor_BlackActor_getLightResist);
        tolua_function(tolua_S,"getActorID",lua_wuhun_actor_BlackActor_getActorID);
        tolua_function(tolua_S,"setRunAttack1ID",lua_wuhun_actor_BlackActor_setRunAttack1ID);
        tolua_function(tolua_S,"getRunAttackID",lua_wuhun_actor_BlackActor_getRunAttackID);
        tolua_function(tolua_S,"getDeHitDownVal",lua_wuhun_actor_BlackActor_getDeHitDownVal);
        tolua_function(tolua_S,"setRunAttackID",lua_wuhun_actor_BlackActor_setRunAttackID);
        tolua_function(tolua_S,"getTenacity",lua_wuhun_actor_BlackActor_getTenacity);
        tolua_function(tolua_S,"getAtk1SkillID",lua_wuhun_actor_BlackActor_getAtk1SkillID);
        tolua_function(tolua_S,"getMaxHp",lua_wuhun_actor_BlackActor_getMaxHp);
        tolua_function(tolua_S,"getRushSpeed",lua_wuhun_actor_BlackActor_getRushSpeed);
        tolua_function(tolua_S,"setSkillAID",lua_wuhun_actor_BlackActor_setSkillAID);
        tolua_function(tolua_S,"setMp",lua_wuhun_actor_BlackActor_setMp);
        tolua_function(tolua_S,"getDodgeRatio",lua_wuhun_actor_BlackActor_getDodgeRatio);
        tolua_function(tolua_S,"getSkillSPID",lua_wuhun_actor_BlackActor_getSkillSPID);
        tolua_function(tolua_S,"getDefence",lua_wuhun_actor_BlackActor_getDefence);
        tolua_function(tolua_S,"getIceResist",lua_wuhun_actor_BlackActor_getIceResist);
        tolua_function(tolua_S,"getAtk3SkillID",lua_wuhun_actor_BlackActor_getAtk3SkillID);
        tolua_function(tolua_S,"setAtkSkillID",lua_wuhun_actor_BlackActor_setAtkSkillID);
        tolua_function(tolua_S,"getScaleRate",lua_wuhun_actor_BlackActor_getScaleRate);
        tolua_function(tolua_S,"readRelativeSkill",lua_wuhun_actor_BlackActor_readRelativeSkill);
        tolua_function(tolua_S,"getThunderResist",lua_wuhun_actor_BlackActor_getThunderResist);
        tolua_function(tolua_S,"getWindResist",lua_wuhun_actor_BlackActor_getWindResist);
        tolua_function(tolua_S,"getCritRatio",lua_wuhun_actor_BlackActor_getCritRatio);
        tolua_function(tolua_S,"getAtk4SkillID",lua_wuhun_actor_BlackActor_getAtk4SkillID);
        tolua_function(tolua_S,"getMaxAp",lua_wuhun_actor_BlackActor_getMaxAp);
        tolua_function(tolua_S,"getRunAttack2ID",lua_wuhun_actor_BlackActor_getRunAttack2ID);
        tolua_function(tolua_S,"getSkillBID",lua_wuhun_actor_BlackActor_getSkillBID);
        tolua_function(tolua_S,"getRunAttack1ID",lua_wuhun_actor_BlackActor_getRunAttack1ID);
        tolua_function(tolua_S,"getAttack",lua_wuhun_actor_BlackActor_getAttack);
        tolua_function(tolua_S,"getAtk2SkillID",lua_wuhun_actor_BlackActor_getAtk2SkillID);
        tolua_function(tolua_S,"getSkillAID",lua_wuhun_actor_BlackActor_getSkillAID);
        tolua_function(tolua_S,"setAp",lua_wuhun_actor_BlackActor_setAp);
        tolua_function(tolua_S,"getHp",lua_wuhun_actor_BlackActor_getHp);
        tolua_function(tolua_S,"getAtkSkillID",lua_wuhun_actor_BlackActor_getAtkSkillID);
        tolua_function(tolua_S,"getMaxMp",lua_wuhun_actor_BlackActor_getMaxMp);
        tolua_function(tolua_S,"initPlayerData",lua_wuhun_actor_BlackActor_initPlayerData);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(BlackActor).name();
    g_luaType[typeName] = "BlackActor";
    g_typeCast["BlackActor"] = "BlackActor";
    return 1;
}

int lua_wuhun_actor_BlackBullet_setThunderResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_setThunderResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setThunderResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setThunderResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_setThunderResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_setDarkResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_setDarkResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setDarkResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDarkResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_setDarkResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getScaleRate(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getScaleRate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getScaleRate();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getScaleRate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getScaleRate'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getBulletId(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getBulletId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getBulletId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBulletId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getBulletId'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getBufferId(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getBufferId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getBufferId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBufferId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getBufferId'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getBulletType(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getBulletType'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getBulletType();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBulletType",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getBulletType'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getSplashHeight(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getSplashHeight'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getSplashHeight();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSplashHeight",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getSplashHeight'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_setLightResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_setLightResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setLightResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setLightResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_setLightResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_setAttack(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_setAttack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setAttack(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAttack",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_setAttack'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getDarkResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getDarkResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getDarkResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDarkResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getDarkResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_readFile(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_readFile'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        std::string arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        cobj->readFile(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "readFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_readFile'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getResName(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getResName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getResName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getResName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getResName'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getLightResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getLightResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getLightResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLightResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getLightResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_setFireResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_setFireResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setFireResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setFireResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_setFireResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_setWindResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_setWindResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setWindResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setWindResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_setWindResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getIceResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getIceResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getIceResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIceResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getIceResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getSplash(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getSplash'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getSplash();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSplash",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getSplash'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getFireResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getFireResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getFireResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFireResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getFireResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getWindResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getWindResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getWindResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getWindResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getWindResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_setIceResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_setIceResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setIceResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setIceResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_setIceResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getThunderResist(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getThunderResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getThunderResist();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getThunderResist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getThunderResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getSpeed(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getAttack(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getAttack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getAttack();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAttack",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getAttack'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_BlackBullet_getSplashWidth(lua_State* tolua_S)
{
    int argc = 0;
    BlackBullet* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"BlackBullet",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (BlackBullet*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_BlackBullet_getSplashWidth'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getSplashWidth();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSplashWidth",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_BlackBullet_getSplashWidth'.",&tolua_err);
#endif

    return 0;
}
static int lua_wuhun_actor_BlackBullet_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (BlackBullet)");
    return 0;
}

int lua_register_wuhun_actor_BlackBullet(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"BlackBullet");
    tolua_cclass(tolua_S,"BlackBullet","BlackBullet","",nullptr);

    tolua_beginmodule(tolua_S,"BlackBullet");
        tolua_function(tolua_S,"setThunderResist",lua_wuhun_actor_BlackBullet_setThunderResist);
        tolua_function(tolua_S,"setDarkResist",lua_wuhun_actor_BlackBullet_setDarkResist);
        tolua_function(tolua_S,"getScaleRate",lua_wuhun_actor_BlackBullet_getScaleRate);
        tolua_function(tolua_S,"getBulletId",lua_wuhun_actor_BlackBullet_getBulletId);
        tolua_function(tolua_S,"getBufferId",lua_wuhun_actor_BlackBullet_getBufferId);
        tolua_function(tolua_S,"getBulletType",lua_wuhun_actor_BlackBullet_getBulletType);
        tolua_function(tolua_S,"getSplashHeight",lua_wuhun_actor_BlackBullet_getSplashHeight);
        tolua_function(tolua_S,"setLightResist",lua_wuhun_actor_BlackBullet_setLightResist);
        tolua_function(tolua_S,"setAttack",lua_wuhun_actor_BlackBullet_setAttack);
        tolua_function(tolua_S,"getDarkResist",lua_wuhun_actor_BlackBullet_getDarkResist);
        tolua_function(tolua_S,"readFile",lua_wuhun_actor_BlackBullet_readFile);
        tolua_function(tolua_S,"getResName",lua_wuhun_actor_BlackBullet_getResName);
        tolua_function(tolua_S,"getLightResist",lua_wuhun_actor_BlackBullet_getLightResist);
        tolua_function(tolua_S,"setFireResist",lua_wuhun_actor_BlackBullet_setFireResist);
        tolua_function(tolua_S,"setWindResist",lua_wuhun_actor_BlackBullet_setWindResist);
        tolua_function(tolua_S,"getIceResist",lua_wuhun_actor_BlackBullet_getIceResist);
        tolua_function(tolua_S,"getSplash",lua_wuhun_actor_BlackBullet_getSplash);
        tolua_function(tolua_S,"getFireResist",lua_wuhun_actor_BlackBullet_getFireResist);
        tolua_function(tolua_S,"getWindResist",lua_wuhun_actor_BlackBullet_getWindResist);
        tolua_function(tolua_S,"setIceResist",lua_wuhun_actor_BlackBullet_setIceResist);
        tolua_function(tolua_S,"getThunderResist",lua_wuhun_actor_BlackBullet_getThunderResist);
        tolua_function(tolua_S,"getSpeed",lua_wuhun_actor_BlackBullet_getSpeed);
        tolua_function(tolua_S,"getAttack",lua_wuhun_actor_BlackBullet_getAttack);
        tolua_function(tolua_S,"getSplashWidth",lua_wuhun_actor_BlackBullet_getSplashWidth);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(BlackBullet).name();
    g_luaType[typeName] = "BlackBullet";
    g_typeCast["BlackBullet"] = "BlackBullet";
    return 1;
}

int lua_wuhun_actor_FightActor_getBHero(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getBHero'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getBHero();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBHero",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getBHero'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeFireResist(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeFireResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeFireResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeFireResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeFireResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeCurrApBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeCurrApBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeCurrApBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeCurrApBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeCurrApBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeMaxAp(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeMaxAp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeMaxAp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeMaxAp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeMaxAp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeMp(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeMp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeMp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeMp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeMp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeCurrMpBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeCurrMpBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeCurrMpBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeCurrMpBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeCurrMpBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getMaxCombo(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getMaxCombo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getMaxCombo();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getMaxCombo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getMaxCombo'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_addCombo(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_addCombo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->addCombo();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addCombo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_addCombo'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_skillBulletHurt(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_skillBulletHurt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->skillBulletHurt();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "skillBulletHurt",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_skillBulletHurt'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_needSneak(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_needSneak'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->needSneak();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "needSneak",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_needSneak'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getAtking(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getAtking'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getAtking();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAtking",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getAtking'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeLightResistBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeLightResistBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeLightResistBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeLightResistBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeLightResistBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_addBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_addBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        bool arg0;
        SkillTag* arg1;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);

        ok &= luaval_to_object<SkillTag>(tolua_S, 3, "SkillTag",&arg1);
        if(!ok)
            return 0;
        cobj->addBuff(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addBuff",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_addBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getFrameCommand(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getFrameCommand'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getFrameCommand();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getFrameCommand",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getFrameCommand'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeThunderResistBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeThunderResistBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeThunderResistBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeThunderResistBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeThunderResistBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeCurrHpBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeCurrHpBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeCurrHpBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeCurrHpBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeCurrHpBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setIsFrozen(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setIsFrozen'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setIsFrozen(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setIsFrozen",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setIsFrozen'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffImmuFrozen(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffImmuFrozen'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffImmuFrozen(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffImmuFrozen",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffImmuFrozen'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeMaxHpBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeMaxHpBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeMaxHpBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeMaxHpBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeMaxHpBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_gethurtStiff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_gethurtStiff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->gethurtStiff();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "gethurtStiff",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_gethurtStiff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_parseHurtEvent(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_parseHurtEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::EventCustom* arg0;

        ok &= luaval_to_object<cocos2d::EventCustom>(tolua_S, 2, "cc.EventCustom",&arg0);
        if(!ok)
            return 0;
        cobj->parseHurtEvent(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "parseHurtEvent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_parseHurtEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getAttackHead(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getAttackHead'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getAttackHead();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAttackHead",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getAttackHead'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeDarkResistBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeDarkResistBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeDarkResistBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeDarkResistBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeDarkResistBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeTenacity(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeTenacity'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeTenacity(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeTenacity",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeTenacity'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeImmuAllDeBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeImmuAllDeBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeImmuAllDeBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeImmuAllDeBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeImmuAllDeBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeThunderResist(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeThunderResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeThunderResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeThunderResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeThunderResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setHurtEffectLayer(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setHurtEffectLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Layer* arg0;

        ok &= luaval_to_object<cocos2d::Layer>(tolua_S, 2, "cc.Layer",&arg0);
        if(!ok)
            return 0;
        cobj->setHurtEffectLayer(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setHurtEffectLayer",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setHurtEffectLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_animationEvent(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_animationEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocostudio::Armature* arg0;
        cocostudio::MovementEventType arg1;
        std::string arg2;

        ok &= luaval_to_object<cocostudio::Armature>(tolua_S, 2, "ccs.Armature",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        cobj->animationEvent(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "animationEvent",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_animationEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeFaintBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeFaintBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeFaintBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeFaintBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeFaintBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getDeHitDownVal(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getDeHitDownVal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getDeHitDownVal();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDeHitDownVal",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getDeHitDownVal'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_lostTarget(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_lostTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->lostTarget();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "lostTarget",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_lostTarget'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeFrozenBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeFrozenBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeFrozenBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeFrozenBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeFrozenBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeHpRecoverBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeHpRecoverBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeHpRecoverBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeHpRecoverBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeHpRecoverBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getHurtMoveSpeed(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getHurtMoveSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getHurtMoveSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHurtMoveSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getHurtMoveSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_dispatchResetPunchTag(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_dispatchResetPunchTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->dispatchResetPunchTag();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "dispatchResetPunchTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_dispatchResetPunchTag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getComboNum(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getComboNum'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getComboNum();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getComboNum",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getComboNum'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_canUseSomeSkill(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_canUseSomeSkill'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->canUseSomeSkill();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "canUseSomeSkill",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_canUseSomeSkill'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getIsFix(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getIsFix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getIsFix();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIsFix",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getIsFix'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getDying(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getDying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getDying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getDying'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeMoveSpeedBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeMoveSpeedBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeMoveSpeedBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeMoveSpeedBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeMoveSpeedBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getAtkRect(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getAtkRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cocos2d::Rect ret = cobj->getAtkRect(arg0);
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAtkRect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getAtkRect'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getHit2Ground(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getHit2Ground'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getHit2Ground();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHit2Ground",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getHit2Ground'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getBlackActor(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getBlackActor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        BlackActor* ret = cobj->getBlackActor();
        object_to_luaval<BlackActor>(tolua_S, "BlackActor",(BlackActor*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBlackActor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getBlackActor'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setWaitTimeOut(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setWaitTimeOut'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setWaitTimeOut(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setWaitTimeOut",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setWaitTimeOut'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffFrozenState(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffFrozenState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffFrozenState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffFrozenState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffFrozenState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getIsFaint(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getIsFaint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getIsFaint();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIsFaint",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getIsFaint'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getLieShockSpeed(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getLieShockSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getLieShockSpeed();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLieShockSpeed",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getLieShockSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_DeStiff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_DeStiff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->DeStiff();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "DeStiff",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_DeStiff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeImmuFaintBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeImmuFaintBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeImmuFaintBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeImmuFaintBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeImmuFaintBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_preloadSkillRes(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_preloadSkillRes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->preloadSkillRes();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "preloadSkillRes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_preloadSkillRes'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeDodgeRatioBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeDodgeRatioBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeDodgeRatioBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeDodgeRatioBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeDodgeRatioBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeMpRecover(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeMpRecover'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeMpRecover(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeMpRecover",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeMpRecover'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffImmuFaint(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffImmuFaint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffImmuFaint(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffImmuFaint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffImmuFaint'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeMaxHp(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeMaxHp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeMaxHp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeMaxHp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeMaxHp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeMaxApBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeMaxApBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeMaxApBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeMaxApBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeMaxApBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeDarkResist(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeDarkResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeDarkResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeDarkResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeDarkResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeLightResist(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeLightResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeLightResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeLightResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeLightResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeApRecover(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeApRecover'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeApRecover(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeApRecover",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeApRecover'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getBombHitVal(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getBombHitVal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getBombHitVal();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBombHitVal",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getBombHitVal'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getHit2Air(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getHit2Air'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getHit2Air();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHit2Air",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getHit2Air'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setMp(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setMp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setMp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setMp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setMp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getBackInAir(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getBackInAir'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getBackInAir();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBackInAir",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getBackInAir'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_changeActionWithName(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_changeActionWithName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->changeActionWithName(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "changeActionWithName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_changeActionWithName'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getAsBomb(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getAsBomb'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getAsBomb();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAsBomb",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getAsBomb'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setTargetActor(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setTargetActor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        FightActor* arg0;

        ok &= luaval_to_object<FightActor>(tolua_S, 2, "FightActor",&arg0);
        if(!ok)
            return 0;
        cobj->setTargetActor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTargetActor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setTargetActor'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeImmuFrozenBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeImmuFrozenBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeImmuFrozenBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeImmuFrozenBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeImmuFrozenBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffFaintState(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffFaintState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffFaintState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffFaintState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffFaintState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeCritRatio(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeCritRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeCritRatio(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeCritRatio",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeCritRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setIsFaint(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setIsFaint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setIsFaint(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setIsFaint",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setIsFaint'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_DealAttackRectByFlip(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_DealAttackRectByFlip'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        bool arg0;
        cocos2d::Rect* arg1;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);

        ok &= luaval_to_object<cocos2d::Rect>(tolua_S, 3, "cc.Rect",&arg1);
        if(!ok)
            return 0;
        cobj->DealAttackRectByFlip(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "DealAttackRectByFlip",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_DealAttackRectByFlip'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_initFightData(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_initFightData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->initFightData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initFightData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_initFightData'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeHpRecover(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeHpRecover'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeHpRecover(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeHpRecover",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeHpRecover'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_backSkill2Base(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_backSkill2Base'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->backSkill2Base(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "backSkill2Base",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_backSkill2Base'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getTargetActor(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getTargetActor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        FightActor* ret = cobj->getTargetActor();
        object_to_luaval<FightActor>(tolua_S, "FightActor",(FightActor*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTargetActor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getTargetActor'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeWindResistBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeWindResistBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeWindResistBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeWindResistBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeWindResistBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getDieLie(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getDieLie'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getDieLie();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDieLie",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getDieLie'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeMaxMp(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeMaxMp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeMaxMp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeMaxMp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeMaxMp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeMoveSpeed(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeMoveSpeed'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeMoveSpeed(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeMoveSpeed",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeMoveSpeed'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeAttackBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeAttackBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeAttackBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeAttackBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeAttackBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setTargetToActor(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setTargetToActor'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        FightActor* arg0;

        ok &= luaval_to_object<FightActor>(tolua_S, 2, "FightActor",&arg0);
        if(!ok)
            return 0;
        cobj->setTargetToActor(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTargetToActor",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setTargetToActor'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getBombAtkRect(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getBombAtkRect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Rect ret = cobj->getBombAtkRect();
        rect_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBombAtkRect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getBombAtkRect'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeApRecoverBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeApRecoverBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeApRecoverBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeApRecoverBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeApRecoverBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getShowCombo(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getShowCombo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getShowCombo();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getShowCombo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getShowCombo'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getCurrSkillTag(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getCurrSkillTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        SkillTag* ret = cobj->getCurrSkillTag();
        object_to_luaval<SkillTag>(tolua_S, "SkillTag",(SkillTag*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCurrSkillTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getCurrSkillTag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_isLandGround(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_isLandGround'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isLandGround();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isLandGround",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_isLandGround'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setCurrHitDownVal(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setCurrHitDownVal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setCurrHitDownVal(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setCurrHitDownVal",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setCurrHitDownVal'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeHitRatioBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeHitRatioBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeHitRatioBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeHitRatioBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeHitRatioBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getHurtEffectLayer(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getHurtEffectLayer'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Layer* ret = cobj->getHurtEffectLayer();
        object_to_luaval<cocos2d::Layer>(tolua_S, "cc.Layer",(cocos2d::Layer*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHurtEffectLayer",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getHurtEffectLayer'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeDodgeRatio(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeDodgeRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeDodgeRatio(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeDodgeRatio",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeDodgeRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setHp(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setHp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setHp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setHp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setHp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_resetPunchTag(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_resetPunchTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::EventCustom* arg0;

        ok &= luaval_to_object<cocos2d::EventCustom>(tolua_S, 2, "cc.EventCustom",&arg0);
        if(!ok)
            return 0;
        cobj->resetPunchTag(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "resetPunchTag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_resetPunchTag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getSkillAction(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getSkillAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        int ret = cobj->getSkillAction(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSkillAction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getSkillAction'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_canFindOpponent(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_canFindOpponent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->canFindOpponent();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "canFindOpponent",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_canFindOpponent'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_canChase(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_canChase'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->canChase();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "canChase",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_canChase'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeIceResist(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeIceResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeIceResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeIceResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeIceResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeDeHitDown(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeDeHitDown'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeDeHitDown(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeDeHitDown",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeDeHitDown'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeAp(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeAp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeAp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeAp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeAp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffFixState(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffFixState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffFixState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffFixState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffFixState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getAtkStiff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getAtkStiff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getAtkStiff();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAtkStiff",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getAtkStiff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_adjustHurtEffectPos(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_adjustHurtEffectPos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->adjustHurtEffectPos();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "adjustHurtEffectPos",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_adjustHurtEffectPos'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_changeSkill(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_changeSkill'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->changeSkill(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "changeSkill",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_changeSkill'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeCritRatioBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeCritRatioBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeCritRatioBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeCritRatioBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeCritRatioBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_onFrameEvent(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_onFrameEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        cocostudio::Bone* arg0;
        std::string arg1;
        int arg2;
        int arg3;

        ok &= luaval_to_object<cocostudio::Bone>(tolua_S, 2, "ccs.Bone",&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);

        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3);
        if(!ok)
            return 0;
        cobj->onFrameEvent(arg0, arg1, arg2, arg3);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "onFrameEvent",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_onFrameEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_hurt(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_hurt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->hurt();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "hurt",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_hurt'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeIceResistBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeIceResistBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeIceResistBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeIceResistBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeIceResistBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeDehitDownBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeDehitDownBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeDehitDownBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeDehitDownBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeDehitDownBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeHitRatio(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeHitRatio'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeHitRatio(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeHitRatio",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeHitRatio'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_updateBackEffect(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_updateBackEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateBackEffect();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "updateBackEffect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_updateBackEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getIsValidAtk(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getIsValidAtk'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getIsValidAtk();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIsValidAtk",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getIsValidAtk'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_clearCombo(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_clearCombo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearCombo();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clearCombo",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_clearCombo'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffImmuAll(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffImmuAll'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffImmuAll(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffImmuAll",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffImmuAll'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setDeHitDownVal(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setDeHitDownVal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setDeHitDownVal(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDeHitDownVal",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setDeHitDownVal'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getCurrHitDownVal(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getCurrHitDownVal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getCurrHitDownVal();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCurrHitDownVal",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getCurrHitDownVal'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getAttackFoot(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getAttackFoot'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getAttackFoot();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAttackFoot",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getAttackFoot'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getCurrAction(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getCurrAction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getCurrAction();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCurrAction",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getCurrAction'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getBombHitDownVal(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getBombHitDownVal'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->getBombHitDownVal();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getBombHitDownVal",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getBombHitDownVal'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeAttack(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeAttack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeAttack(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeAttack",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeAttack'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_initFightState(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_initFightState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->initFightState();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initFightState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_initFightState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setIsFix(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setIsFix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setIsFix(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setIsFix",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setIsFix'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeFireResistBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeFireResistBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeFireResistBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeFireResistBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeFireResistBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffImmuFix(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffImmuFix'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffImmuFix(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffImmuFix",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffImmuFix'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_startAtkStiff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_startAtkStiff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->startAtkStiff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "startAtkStiff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_startAtkStiff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeMaxMpBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeMaxMpBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeMaxMpBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeMaxMpBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeMaxMpBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setIsValidAtk(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setIsValidAtk'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setIsValidAtk(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setIsValidAtk",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setIsValidAtk'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeMpRecoverBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeMpRecoverBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeMpRecoverBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeMpRecoverBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeMpRecoverBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeDefloatBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeDefloatBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeDefloatBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeDefloatBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeDefloatBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_setDieLie(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_setDieLie'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setDieLie(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDieLie",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_setDieLie'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_initViewRes(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_initViewRes'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->initViewRes();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initViewRes",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_initViewRes'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_updateFrontEffect(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_updateFrontEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateFrontEffect();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "updateFrontEffect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_updateFrontEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_bodyHurt(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_bodyHurt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->bodyHurt();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "bodyHurt",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_bodyHurt'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_canAttackTarget(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_canAttackTarget'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->canAttackTarget();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "canAttackTarget",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_canAttackTarget'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getCurrSkill(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getCurrSkill'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        Skill* ret = cobj->getCurrSkill();
        object_to_luaval<Skill>(tolua_S, "Skill",(Skill*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCurrSkill",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getCurrSkill'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeDefence(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeDefence'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeDefence(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeDefence",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeDefence'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_addHurtListener(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_addHurtListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->addHurtListener();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addHurtListener",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_addHurtListener'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getWaitTimeOut(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getWaitTimeOut'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getWaitTimeOut();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getWaitTimeOut",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getWaitTimeOut'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_bulletHurt(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_bulletHurt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Bullet* arg0;

        ok &= luaval_to_object<Bullet>(tolua_S, 2, "Bullet",&arg0);
        if(!ok)
            return 0;
        cobj->bulletHurt(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "bulletHurt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_bulletHurt'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeTenacityBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeTenacityBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeTenacityBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeTenacityBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeTenacityBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_effAnimEvent(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_effAnimEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        cocostudio::Armature* arg0;
        cocostudio::MovementEventType arg1;
        std::string arg2;

        ok &= luaval_to_object<cocostudio::Armature>(tolua_S, 2, "ccs.Armature",&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2);
        if(!ok)
            return 0;
        cobj->effAnimEvent(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "effAnimEvent",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_effAnimEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getHit2Wall(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getHit2Wall'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getHit2Wall();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getHit2Wall",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getHit2Wall'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getIsFrozen(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getIsFrozen'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getIsFrozen();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIsFrozen",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getIsFrozen'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_waitTimeEnough(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_waitTimeEnough'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->waitTimeEnough();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "waitTimeEnough",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_waitTimeEnough'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeImmuFixBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeImmuFixBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeImmuFixBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeImmuFixBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeImmuFixBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getAttackTag(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getAttackTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getAttackTag();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAttackTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getAttackTag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeDefenceBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeDefenceBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeDefenceBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeDefenceBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeDefenceBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_startHurtStiff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_startHurtStiff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->startHurtStiff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "startHurtStiff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_startHurtStiff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeHp(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeHp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeHp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeHp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeHp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeFixBuff(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_removeFixBuff'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->removeFixBuff(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeFixBuff",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeFixBuff'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeWindResist(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeWindResist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeWindResist(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeWindResist",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeWindResist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_getAttackWaist(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_getAttackWaist'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getAttackWaist();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAttackWaist",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_getAttackWaist'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_buffChangeDeFloat(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (FightActor*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_FightActor_buffChangeDeFloat'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        Buff* arg0;

        ok &= luaval_to_object<Buff>(tolua_S, 2, "Buff",&arg0);
        if(!ok)
            return 0;
        cobj->buffChangeDeFloat(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "buffChangeDeFloat",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_buffChangeDeFloat'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_FightActor_removeHurtListener(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"FightActor",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        FightActor::removeHurtListener();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "removeHurtListener",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_removeHurtListener'.",&tolua_err);
#endif
    return 0;
}
int lua_wuhun_actor_FightActor_constructor(lua_State* tolua_S)
{
    int argc = 0;
    FightActor* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj = new FightActor();
        cobj->autorelease();
        int ID =  (int)cobj->_ID ;
        int* luaID =  &cobj->_luaID ;
        toluafix_pushusertype_ccobject(tolua_S, ID, luaID, (void*)cobj,"FightActor");
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "FightActor",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_FightActor_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_wuhun_actor_FightActor_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (FightActor)");
    return 0;
}

int lua_register_wuhun_actor_FightActor(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"FightActor");
    tolua_cclass(tolua_S,"FightActor","FightActor","Actor",nullptr);

    tolua_beginmodule(tolua_S,"FightActor");
        tolua_function(tolua_S,"new",lua_wuhun_actor_FightActor_constructor);
        tolua_function(tolua_S,"getBHero",lua_wuhun_actor_FightActor_getBHero);
        tolua_function(tolua_S,"buffChangeFireResist",lua_wuhun_actor_FightActor_buffChangeFireResist);
        tolua_function(tolua_S,"removeCurrApBuff",lua_wuhun_actor_FightActor_removeCurrApBuff);
        tolua_function(tolua_S,"buffChangeMaxAp",lua_wuhun_actor_FightActor_buffChangeMaxAp);
        tolua_function(tolua_S,"buffChangeMp",lua_wuhun_actor_FightActor_buffChangeMp);
        tolua_function(tolua_S,"removeCurrMpBuff",lua_wuhun_actor_FightActor_removeCurrMpBuff);
        tolua_function(tolua_S,"getMaxCombo",lua_wuhun_actor_FightActor_getMaxCombo);
        tolua_function(tolua_S,"addCombo",lua_wuhun_actor_FightActor_addCombo);
        tolua_function(tolua_S,"skillBulletHurt",lua_wuhun_actor_FightActor_skillBulletHurt);
        tolua_function(tolua_S,"needSneak",lua_wuhun_actor_FightActor_needSneak);
        tolua_function(tolua_S,"getAtking",lua_wuhun_actor_FightActor_getAtking);
        tolua_function(tolua_S,"removeLightResistBuff",lua_wuhun_actor_FightActor_removeLightResistBuff);
        tolua_function(tolua_S,"addBuff",lua_wuhun_actor_FightActor_addBuff);
        tolua_function(tolua_S,"getFrameCommand",lua_wuhun_actor_FightActor_getFrameCommand);
        tolua_function(tolua_S,"removeThunderResistBuff",lua_wuhun_actor_FightActor_removeThunderResistBuff);
        tolua_function(tolua_S,"removeCurrHpBuff",lua_wuhun_actor_FightActor_removeCurrHpBuff);
        tolua_function(tolua_S,"setIsFrozen",lua_wuhun_actor_FightActor_setIsFrozen);
        tolua_function(tolua_S,"buffImmuFrozen",lua_wuhun_actor_FightActor_buffImmuFrozen);
        tolua_function(tolua_S,"removeMaxHpBuff",lua_wuhun_actor_FightActor_removeMaxHpBuff);
        tolua_function(tolua_S,"gethurtStiff",lua_wuhun_actor_FightActor_gethurtStiff);
        tolua_function(tolua_S,"parseHurtEvent",lua_wuhun_actor_FightActor_parseHurtEvent);
        tolua_function(tolua_S,"getAttackHead",lua_wuhun_actor_FightActor_getAttackHead);
        tolua_function(tolua_S,"removeDarkResistBuff",lua_wuhun_actor_FightActor_removeDarkResistBuff);
        tolua_function(tolua_S,"buffChangeTenacity",lua_wuhun_actor_FightActor_buffChangeTenacity);
        tolua_function(tolua_S,"removeImmuAllDeBuff",lua_wuhun_actor_FightActor_removeImmuAllDeBuff);
        tolua_function(tolua_S,"buffChangeThunderResist",lua_wuhun_actor_FightActor_buffChangeThunderResist);
        tolua_function(tolua_S,"setHurtEffectLayer",lua_wuhun_actor_FightActor_setHurtEffectLayer);
        tolua_function(tolua_S,"animationEvent",lua_wuhun_actor_FightActor_animationEvent);
        tolua_function(tolua_S,"removeFaintBuff",lua_wuhun_actor_FightActor_removeFaintBuff);
        tolua_function(tolua_S,"getDeHitDownVal",lua_wuhun_actor_FightActor_getDeHitDownVal);
        tolua_function(tolua_S,"lostTarget",lua_wuhun_actor_FightActor_lostTarget);
        tolua_function(tolua_S,"removeFrozenBuff",lua_wuhun_actor_FightActor_removeFrozenBuff);
        tolua_function(tolua_S,"removeHpRecoverBuff",lua_wuhun_actor_FightActor_removeHpRecoverBuff);
        tolua_function(tolua_S,"getHurtMoveSpeed",lua_wuhun_actor_FightActor_getHurtMoveSpeed);
        tolua_function(tolua_S,"dispatchResetPunchTag",lua_wuhun_actor_FightActor_dispatchResetPunchTag);
        tolua_function(tolua_S,"getComboNum",lua_wuhun_actor_FightActor_getComboNum);
        tolua_function(tolua_S,"canUseSomeSkill",lua_wuhun_actor_FightActor_canUseSomeSkill);
        tolua_function(tolua_S,"getIsFix",lua_wuhun_actor_FightActor_getIsFix);
        tolua_function(tolua_S,"getDying",lua_wuhun_actor_FightActor_getDying);
        tolua_function(tolua_S,"removeMoveSpeedBuff",lua_wuhun_actor_FightActor_removeMoveSpeedBuff);
        tolua_function(tolua_S,"getAtkRect",lua_wuhun_actor_FightActor_getAtkRect);
        tolua_function(tolua_S,"getHit2Ground",lua_wuhun_actor_FightActor_getHit2Ground);
        tolua_function(tolua_S,"getBlackActor",lua_wuhun_actor_FightActor_getBlackActor);
        tolua_function(tolua_S,"setWaitTimeOut",lua_wuhun_actor_FightActor_setWaitTimeOut);
        tolua_function(tolua_S,"buffFrozenState",lua_wuhun_actor_FightActor_buffFrozenState);
        tolua_function(tolua_S,"getIsFaint",lua_wuhun_actor_FightActor_getIsFaint);
        tolua_function(tolua_S,"getLieShockSpeed",lua_wuhun_actor_FightActor_getLieShockSpeed);
        tolua_function(tolua_S,"DeStiff",lua_wuhun_actor_FightActor_DeStiff);
        tolua_function(tolua_S,"removeImmuFaintBuff",lua_wuhun_actor_FightActor_removeImmuFaintBuff);
        tolua_function(tolua_S,"preloadSkillRes",lua_wuhun_actor_FightActor_preloadSkillRes);
        tolua_function(tolua_S,"removeDodgeRatioBuff",lua_wuhun_actor_FightActor_removeDodgeRatioBuff);
        tolua_function(tolua_S,"buffChangeMpRecover",lua_wuhun_actor_FightActor_buffChangeMpRecover);
        tolua_function(tolua_S,"buffImmuFaint",lua_wuhun_actor_FightActor_buffImmuFaint);
        tolua_function(tolua_S,"buffChangeMaxHp",lua_wuhun_actor_FightActor_buffChangeMaxHp);
        tolua_function(tolua_S,"removeMaxApBuff",lua_wuhun_actor_FightActor_removeMaxApBuff);
        tolua_function(tolua_S,"buffChangeDarkResist",lua_wuhun_actor_FightActor_buffChangeDarkResist);
        tolua_function(tolua_S,"buffChangeLightResist",lua_wuhun_actor_FightActor_buffChangeLightResist);
        tolua_function(tolua_S,"buffChangeApRecover",lua_wuhun_actor_FightActor_buffChangeApRecover);
        tolua_function(tolua_S,"getBombHitVal",lua_wuhun_actor_FightActor_getBombHitVal);
        tolua_function(tolua_S,"getHit2Air",lua_wuhun_actor_FightActor_getHit2Air);
        tolua_function(tolua_S,"setMp",lua_wuhun_actor_FightActor_setMp);
        tolua_function(tolua_S,"getBackInAir",lua_wuhun_actor_FightActor_getBackInAir);
        tolua_function(tolua_S,"changeActionWithName",lua_wuhun_actor_FightActor_changeActionWithName);
        tolua_function(tolua_S,"getAsBomb",lua_wuhun_actor_FightActor_getAsBomb);
        tolua_function(tolua_S,"setTargetActor",lua_wuhun_actor_FightActor_setTargetActor);
        tolua_function(tolua_S,"removeImmuFrozenBuff",lua_wuhun_actor_FightActor_removeImmuFrozenBuff);
        tolua_function(tolua_S,"buffFaintState",lua_wuhun_actor_FightActor_buffFaintState);
        tolua_function(tolua_S,"buffChangeCritRatio",lua_wuhun_actor_FightActor_buffChangeCritRatio);
        tolua_function(tolua_S,"setIsFaint",lua_wuhun_actor_FightActor_setIsFaint);
        tolua_function(tolua_S,"DealAttackRectByFlip",lua_wuhun_actor_FightActor_DealAttackRectByFlip);
        tolua_function(tolua_S,"initFightData",lua_wuhun_actor_FightActor_initFightData);
        tolua_function(tolua_S,"buffChangeHpRecover",lua_wuhun_actor_FightActor_buffChangeHpRecover);
        tolua_function(tolua_S,"backSkill2Base",lua_wuhun_actor_FightActor_backSkill2Base);
        tolua_function(tolua_S,"getTargetActor",lua_wuhun_actor_FightActor_getTargetActor);
        tolua_function(tolua_S,"removeWindResistBuff",lua_wuhun_actor_FightActor_removeWindResistBuff);
        tolua_function(tolua_S,"getDieLie",lua_wuhun_actor_FightActor_getDieLie);
        tolua_function(tolua_S,"buffChangeMaxMp",lua_wuhun_actor_FightActor_buffChangeMaxMp);
        tolua_function(tolua_S,"buffChangeMoveSpeed",lua_wuhun_actor_FightActor_buffChangeMoveSpeed);
        tolua_function(tolua_S,"removeAttackBuff",lua_wuhun_actor_FightActor_removeAttackBuff);
        tolua_function(tolua_S,"setTargetToActor",lua_wuhun_actor_FightActor_setTargetToActor);
        tolua_function(tolua_S,"getBombAtkRect",lua_wuhun_actor_FightActor_getBombAtkRect);
        tolua_function(tolua_S,"removeApRecoverBuff",lua_wuhun_actor_FightActor_removeApRecoverBuff);
        tolua_function(tolua_S,"getShowCombo",lua_wuhun_actor_FightActor_getShowCombo);
        tolua_function(tolua_S,"getCurrSkillTag",lua_wuhun_actor_FightActor_getCurrSkillTag);
        tolua_function(tolua_S,"isLandGround",lua_wuhun_actor_FightActor_isLandGround);
        tolua_function(tolua_S,"setCurrHitDownVal",lua_wuhun_actor_FightActor_setCurrHitDownVal);
        tolua_function(tolua_S,"removeHitRatioBuff",lua_wuhun_actor_FightActor_removeHitRatioBuff);
        tolua_function(tolua_S,"getHurtEffectLayer",lua_wuhun_actor_FightActor_getHurtEffectLayer);
        tolua_function(tolua_S,"buffChangeDodgeRatio",lua_wuhun_actor_FightActor_buffChangeDodgeRatio);
        tolua_function(tolua_S,"setHp",lua_wuhun_actor_FightActor_setHp);
        tolua_function(tolua_S,"resetPunchTag",lua_wuhun_actor_FightActor_resetPunchTag);
        tolua_function(tolua_S,"getSkillAction",lua_wuhun_actor_FightActor_getSkillAction);
        tolua_function(tolua_S,"canFindOpponent",lua_wuhun_actor_FightActor_canFindOpponent);
        tolua_function(tolua_S,"canChase",lua_wuhun_actor_FightActor_canChase);
        tolua_function(tolua_S,"buffChangeIceResist",lua_wuhun_actor_FightActor_buffChangeIceResist);
        tolua_function(tolua_S,"buffChangeDeHitDown",lua_wuhun_actor_FightActor_buffChangeDeHitDown);
        tolua_function(tolua_S,"buffChangeAp",lua_wuhun_actor_FightActor_buffChangeAp);
        tolua_function(tolua_S,"buffFixState",lua_wuhun_actor_FightActor_buffFixState);
        tolua_function(tolua_S,"getAtkStiff",lua_wuhun_actor_FightActor_getAtkStiff);
        tolua_function(tolua_S,"adjustHurtEffectPos",lua_wuhun_actor_FightActor_adjustHurtEffectPos);
        tolua_function(tolua_S,"changeSkill",lua_wuhun_actor_FightActor_changeSkill);
        tolua_function(tolua_S,"removeCritRatioBuff",lua_wuhun_actor_FightActor_removeCritRatioBuff);
        tolua_function(tolua_S,"onFrameEvent",lua_wuhun_actor_FightActor_onFrameEvent);
        tolua_function(tolua_S,"hurt",lua_wuhun_actor_FightActor_hurt);
        tolua_function(tolua_S,"removeIceResistBuff",lua_wuhun_actor_FightActor_removeIceResistBuff);
        tolua_function(tolua_S,"removeDehitDownBuff",lua_wuhun_actor_FightActor_removeDehitDownBuff);
        tolua_function(tolua_S,"buffChangeHitRatio",lua_wuhun_actor_FightActor_buffChangeHitRatio);
        tolua_function(tolua_S,"updateBackEffect",lua_wuhun_actor_FightActor_updateBackEffect);
        tolua_function(tolua_S,"getIsValidAtk",lua_wuhun_actor_FightActor_getIsValidAtk);
        tolua_function(tolua_S,"clearCombo",lua_wuhun_actor_FightActor_clearCombo);
        tolua_function(tolua_S,"buffImmuAll",lua_wuhun_actor_FightActor_buffImmuAll);
        tolua_function(tolua_S,"setDeHitDownVal",lua_wuhun_actor_FightActor_setDeHitDownVal);
        tolua_function(tolua_S,"getCurrHitDownVal",lua_wuhun_actor_FightActor_getCurrHitDownVal);
        tolua_function(tolua_S,"getAttackFoot",lua_wuhun_actor_FightActor_getAttackFoot);
        tolua_function(tolua_S,"getCurrAction",lua_wuhun_actor_FightActor_getCurrAction);
        tolua_function(tolua_S,"getBombHitDownVal",lua_wuhun_actor_FightActor_getBombHitDownVal);
        tolua_function(tolua_S,"buffChangeAttack",lua_wuhun_actor_FightActor_buffChangeAttack);
        tolua_function(tolua_S,"initFightState",lua_wuhun_actor_FightActor_initFightState);
        tolua_function(tolua_S,"setIsFix",lua_wuhun_actor_FightActor_setIsFix);
        tolua_function(tolua_S,"removeFireResistBuff",lua_wuhun_actor_FightActor_removeFireResistBuff);
        tolua_function(tolua_S,"buffImmuFix",lua_wuhun_actor_FightActor_buffImmuFix);
        tolua_function(tolua_S,"startAtkStiff",lua_wuhun_actor_FightActor_startAtkStiff);
        tolua_function(tolua_S,"removeMaxMpBuff",lua_wuhun_actor_FightActor_removeMaxMpBuff);
        tolua_function(tolua_S,"setIsValidAtk",lua_wuhun_actor_FightActor_setIsValidAtk);
        tolua_function(tolua_S,"removeMpRecoverBuff",lua_wuhun_actor_FightActor_removeMpRecoverBuff);
        tolua_function(tolua_S,"removeDefloatBuff",lua_wuhun_actor_FightActor_removeDefloatBuff);
        tolua_function(tolua_S,"setDieLie",lua_wuhun_actor_FightActor_setDieLie);
        tolua_function(tolua_S,"initViewRes",lua_wuhun_actor_FightActor_initViewRes);
        tolua_function(tolua_S,"updateFrontEffect",lua_wuhun_actor_FightActor_updateFrontEffect);
        tolua_function(tolua_S,"bodyHurt",lua_wuhun_actor_FightActor_bodyHurt);
        tolua_function(tolua_S,"canAttackTarget",lua_wuhun_actor_FightActor_canAttackTarget);
        tolua_function(tolua_S,"getCurrSkill",lua_wuhun_actor_FightActor_getCurrSkill);
        tolua_function(tolua_S,"buffChangeDefence",lua_wuhun_actor_FightActor_buffChangeDefence);
        tolua_function(tolua_S,"addHurtListener",lua_wuhun_actor_FightActor_addHurtListener);
        tolua_function(tolua_S,"getWaitTimeOut",lua_wuhun_actor_FightActor_getWaitTimeOut);
        tolua_function(tolua_S,"bulletHurt",lua_wuhun_actor_FightActor_bulletHurt);
        tolua_function(tolua_S,"removeTenacityBuff",lua_wuhun_actor_FightActor_removeTenacityBuff);
        tolua_function(tolua_S,"effAnimEvent",lua_wuhun_actor_FightActor_effAnimEvent);
        tolua_function(tolua_S,"getHit2Wall",lua_wuhun_actor_FightActor_getHit2Wall);
        tolua_function(tolua_S,"getIsFrozen",lua_wuhun_actor_FightActor_getIsFrozen);
        tolua_function(tolua_S,"waitTimeEnough",lua_wuhun_actor_FightActor_waitTimeEnough);
        tolua_function(tolua_S,"removeImmuFixBuff",lua_wuhun_actor_FightActor_removeImmuFixBuff);
        tolua_function(tolua_S,"getAttackTag",lua_wuhun_actor_FightActor_getAttackTag);
        tolua_function(tolua_S,"removeDefenceBuff",lua_wuhun_actor_FightActor_removeDefenceBuff);
        tolua_function(tolua_S,"startHurtStiff",lua_wuhun_actor_FightActor_startHurtStiff);
        tolua_function(tolua_S,"buffChangeHp",lua_wuhun_actor_FightActor_buffChangeHp);
        tolua_function(tolua_S,"removeFixBuff",lua_wuhun_actor_FightActor_removeFixBuff);
        tolua_function(tolua_S,"buffChangeWindResist",lua_wuhun_actor_FightActor_buffChangeWindResist);
        tolua_function(tolua_S,"getAttackWaist",lua_wuhun_actor_FightActor_getAttackWaist);
        tolua_function(tolua_S,"buffChangeDeFloat",lua_wuhun_actor_FightActor_buffChangeDeFloat);
        tolua_function(tolua_S,"removeHurtListener", lua_wuhun_actor_FightActor_removeHurtListener);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(FightActor).name();
    g_luaType[typeName] = "FightActor";
    g_typeCast["FightActor"] = "FightActor";
    return 1;
}

int lua_wuhun_actor_Hero_setAutoControll(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_setAutoControll'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setAutoControll(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAutoControll",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_setAutoControll'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_removeHurtListener(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_removeHurtListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->removeHurtListener();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeHurtListener",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_removeHurtListener'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_exitState(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_exitState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->exitState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "exitState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_exitState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_getAutoControll(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_getAutoControll'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getAutoControll();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAutoControll",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_getAutoControll'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_clearKey(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_clearKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->clearKey();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "clearKey",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_clearKey'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_backSkillAtkBase(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_backSkillAtkBase'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->backSkillAtkBase();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "backSkillAtkBase",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_backSkillAtkBase'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_setRushAtkReady(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_setRushAtkReady'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setRushAtkReady(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setRushAtkReady",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_setRushAtkReady'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_enterState(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_enterState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->enterState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "enterState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_enterState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_setHp(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_setHp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setHp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setHp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_setHp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_resetWalkOrRush(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_resetWalkOrRush'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        int arg0;
        int arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->resetWalkOrRush(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "resetWalkOrRush",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_resetWalkOrRush'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_init(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_init'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_startXuli(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_startXuli'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->startXuli(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "startXuli",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_startXuli'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_addHurtListener(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_addHurtListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->addHurtListener();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addHurtListener",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_addHurtListener'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_endXuli(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_endXuli'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->endXuli(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "endXuli",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_endXuli'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_getKeyCommand(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_getKeyCommand'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getKeyCommand();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getKeyCommand",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_getKeyCommand'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_doFlag(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_doFlag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->doFlag(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "doFlag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_doFlag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_updateState(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_updateState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateState();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "updateState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_updateState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_setMp(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_setMp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setMp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setMp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_setMp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_getCurrKey(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_getCurrKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getCurrKey();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCurrKey",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_getCurrKey'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_setCurrKey(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_setCurrKey'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->setCurrKey(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setCurrKey",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_setCurrKey'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_updateAI(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_updateAI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateAI();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "updateAI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_updateAI'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_readyRushAtk(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_readyRushAtk'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->readyRushAtk();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "readyRushAtk",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_readyRushAtk'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_getIsXuliEnough(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_getIsXuliEnough'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getIsXuliEnough();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getIsXuliEnough",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_getIsXuliEnough'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_initFightData(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_initFightData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->initFightData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initFightData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_initFightData'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_getJoyCommand(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_getJoyCommand'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getJoyCommand();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getJoyCommand",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_getJoyCommand'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_xuliEnough(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_xuliEnough'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->xuliEnough();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "xuliEnough",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_xuliEnough'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_getRushAtkReady(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_getRushAtkReady'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->getRushAtkReady();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRushAtkReady",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_getRushAtkReady'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_dispatchResetPunchTag(lua_State* tolua_S)
{
    int argc = 0;
    Hero* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Hero*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Hero_dispatchResetPunchTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->dispatchResetPunchTag();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "dispatchResetPunchTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_dispatchResetPunchTag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Hero_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"Hero",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        Hero* ret = Hero::create();
        object_to_luaval<Hero>(tolua_S, "Hero",(Hero*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Hero_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_wuhun_actor_Hero_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Hero)");
    return 0;
}

int lua_register_wuhun_actor_Hero(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"Hero");
    tolua_cclass(tolua_S,"Hero","Hero","FightActor",nullptr);

    tolua_beginmodule(tolua_S,"Hero");
        tolua_function(tolua_S,"setAutoControll",lua_wuhun_actor_Hero_setAutoControll);
        tolua_function(tolua_S,"removeHurtListener",lua_wuhun_actor_Hero_removeHurtListener);
        tolua_function(tolua_S,"exitState",lua_wuhun_actor_Hero_exitState);
        tolua_function(tolua_S,"getAutoControll",lua_wuhun_actor_Hero_getAutoControll);
        tolua_function(tolua_S,"clearKey",lua_wuhun_actor_Hero_clearKey);
        tolua_function(tolua_S,"backSkillAtkBase",lua_wuhun_actor_Hero_backSkillAtkBase);
        tolua_function(tolua_S,"setRushAtkReady",lua_wuhun_actor_Hero_setRushAtkReady);
        tolua_function(tolua_S,"enterState",lua_wuhun_actor_Hero_enterState);
        tolua_function(tolua_S,"setHp",lua_wuhun_actor_Hero_setHp);
        tolua_function(tolua_S,"resetWalkOrRush",lua_wuhun_actor_Hero_resetWalkOrRush);
        tolua_function(tolua_S,"init",lua_wuhun_actor_Hero_init);
        tolua_function(tolua_S,"startXuli",lua_wuhun_actor_Hero_startXuli);
        tolua_function(tolua_S,"addHurtListener",lua_wuhun_actor_Hero_addHurtListener);
        tolua_function(tolua_S,"endXuli",lua_wuhun_actor_Hero_endXuli);
        tolua_function(tolua_S,"getKeyCommand",lua_wuhun_actor_Hero_getKeyCommand);
        tolua_function(tolua_S,"doFlag",lua_wuhun_actor_Hero_doFlag);
        tolua_function(tolua_S,"updateState",lua_wuhun_actor_Hero_updateState);
        tolua_function(tolua_S,"setMp",lua_wuhun_actor_Hero_setMp);
        tolua_function(tolua_S,"getCurrKey",lua_wuhun_actor_Hero_getCurrKey);
        tolua_function(tolua_S,"setCurrKey",lua_wuhun_actor_Hero_setCurrKey);
        tolua_function(tolua_S,"updateAI",lua_wuhun_actor_Hero_updateAI);
        tolua_function(tolua_S,"readyRushAtk",lua_wuhun_actor_Hero_readyRushAtk);
        tolua_function(tolua_S,"getIsXuliEnough",lua_wuhun_actor_Hero_getIsXuliEnough);
        tolua_function(tolua_S,"initFightData",lua_wuhun_actor_Hero_initFightData);
        tolua_function(tolua_S,"getJoyCommand",lua_wuhun_actor_Hero_getJoyCommand);
        tolua_function(tolua_S,"xuliEnough",lua_wuhun_actor_Hero_xuliEnough);
        tolua_function(tolua_S,"getRushAtkReady",lua_wuhun_actor_Hero_getRushAtkReady);
        tolua_function(tolua_S,"dispatchResetPunchTag",lua_wuhun_actor_Hero_dispatchResetPunchTag);
        tolua_function(tolua_S,"create", lua_wuhun_actor_Hero_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Hero).name();
    g_luaType[typeName] = "Hero";
    g_typeCast["Hero"] = "Hero";
    return 1;
}

int lua_wuhun_actor_Monster_removeHurtListener(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_removeHurtListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->removeHurtListener();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "removeHurtListener",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_removeHurtListener'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_exitState(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_exitState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->exitState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "exitState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_exitState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_getTeamId(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_getTeamId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getTeamId();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTeamId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_getTeamId'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_addPartolPoint(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_addPartolPoint'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::Point arg0;
        cocos2d::Point arg1;

        ok &= luaval_to_point(tolua_S, 2, &arg0);

        ok &= luaval_to_point(tolua_S, 3, &arg1);
        if(!ok)
            return 0;
        cobj->addPartolPoint(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addPartolPoint",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_addPartolPoint'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_enterState(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_enterState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->enterState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "enterState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_enterState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_getEnemiesVec(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_getEnemiesVec'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Vector<FightActor *> ret = cobj->getEnemiesVec();
        ccvector_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getEnemiesVec",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_getEnemiesVec'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_setHp(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_setHp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setHp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setHp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_setHp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_Hurt(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_Hurt'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->Hurt(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "Hurt",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_Hurt'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_init(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "init",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_init'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_setEnemiesVec(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_setEnemiesVec'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::Vector<FightActor *> arg0;

        ok &= luaval_to_ccvector(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setEnemiesVec(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setEnemiesVec",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_setEnemiesVec'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_getLeavePartolPos(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_getLeavePartolPos'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Point ret = cobj->getLeavePartolPos();
        point_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getLeavePartolPos",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_getLeavePartolPos'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_addHurtListener(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_addHurtListener'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->addHurtListener();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addHurtListener",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_addHurtListener'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_doFlag(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_doFlag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->doFlag(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "doFlag",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_doFlag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_updateState(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_updateState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateState();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "updateState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_updateState'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_getViewSize(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_getViewSize'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::Size ret = cobj->getViewSize();
        size_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getViewSize",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_getViewSize'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_setMp(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_setMp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setMp(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setMp",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_setMp'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_updateAI(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_updateAI'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->updateAI();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "updateAI",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_updateAI'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_hasFadeIn(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_hasFadeIn'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->hasFadeIn();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "hasFadeIn",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_hasFadeIn'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_setTeamId(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_setTeamId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->setTeamId(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTeamId",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_setTeamId'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_initFightData(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_initFightData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->initFightData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "initFightData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_initFightData'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_dispatchResetPunchTag(lua_State* tolua_S)
{
    int argc = 0;
    Monster* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (Monster*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_wuhun_actor_Monster_dispatchResetPunchTag'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->dispatchResetPunchTag();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "dispatchResetPunchTag",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_dispatchResetPunchTag'.",&tolua_err);
#endif

    return 0;
}
int lua_wuhun_actor_Monster_create(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"Monster",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        Monster* ret = Monster::create();
        object_to_luaval<Monster>(tolua_S, "Monster",(Monster*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "create",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_wuhun_actor_Monster_create'.",&tolua_err);
#endif
    return 0;
}
static int lua_wuhun_actor_Monster_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Monster)");
    return 0;
}

int lua_register_wuhun_actor_Monster(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"Monster");
    tolua_cclass(tolua_S,"Monster","Monster","FightActor",nullptr);

    tolua_beginmodule(tolua_S,"Monster");
        tolua_function(tolua_S,"removeHurtListener",lua_wuhun_actor_Monster_removeHurtListener);
        tolua_function(tolua_S,"exitState",lua_wuhun_actor_Monster_exitState);
        tolua_function(tolua_S,"getTeamId",lua_wuhun_actor_Monster_getTeamId);
        tolua_function(tolua_S,"addPartolPoint",lua_wuhun_actor_Monster_addPartolPoint);
        tolua_function(tolua_S,"enterState",lua_wuhun_actor_Monster_enterState);
        tolua_function(tolua_S,"getEnemiesVec",lua_wuhun_actor_Monster_getEnemiesVec);
        tolua_function(tolua_S,"setHp",lua_wuhun_actor_Monster_setHp);
        tolua_function(tolua_S,"Hurt",lua_wuhun_actor_Monster_Hurt);
        tolua_function(tolua_S,"init",lua_wuhun_actor_Monster_init);
        tolua_function(tolua_S,"setEnemiesVec",lua_wuhun_actor_Monster_setEnemiesVec);
        tolua_function(tolua_S,"getLeavePartolPos",lua_wuhun_actor_Monster_getLeavePartolPos);
        tolua_function(tolua_S,"addHurtListener",lua_wuhun_actor_Monster_addHurtListener);
        tolua_function(tolua_S,"doFlag",lua_wuhun_actor_Monster_doFlag);
        tolua_function(tolua_S,"updateState",lua_wuhun_actor_Monster_updateState);
        tolua_function(tolua_S,"getViewSize",lua_wuhun_actor_Monster_getViewSize);
        tolua_function(tolua_S,"setMp",lua_wuhun_actor_Monster_setMp);
        tolua_function(tolua_S,"updateAI",lua_wuhun_actor_Monster_updateAI);
        tolua_function(tolua_S,"hasFadeIn",lua_wuhun_actor_Monster_hasFadeIn);
        tolua_function(tolua_S,"setTeamId",lua_wuhun_actor_Monster_setTeamId);
        tolua_function(tolua_S,"initFightData",lua_wuhun_actor_Monster_initFightData);
        tolua_function(tolua_S,"dispatchResetPunchTag",lua_wuhun_actor_Monster_dispatchResetPunchTag);
        tolua_function(tolua_S,"create", lua_wuhun_actor_Monster_create);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(Monster).name();
    g_luaType[typeName] = "Monster";
    g_typeCast["Monster"] = "Monster";
    return 1;
}
TOLUA_API int register_all_wuhun_actor(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,nullptr,0);
	tolua_beginmodule(tolua_S,nullptr);

	lua_register_wuhun_actor_SkillTag(tolua_S);
	lua_register_wuhun_actor_Actor(tolua_S);
	lua_register_wuhun_actor_FightActor(tolua_S);
	lua_register_wuhun_actor_Hero(tolua_S);
	lua_register_wuhun_actor_Monster(tolua_S);
	lua_register_wuhun_actor_BlackBullet(tolua_S);
	lua_register_wuhun_actor_BlackActor(tolua_S);
	lua_register_wuhun_actor_Skill(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

