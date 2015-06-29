#ifdef GAME_CLIENT
//#include "AI_System/Game_Utils.h"
//#include "UI/Actor.h"
//#include "UI/Monster.h"
#include "Game/Audio_Manager.h"
//#include "Unique_Skill.h"
//#include "Game_Interface/game_event_mgr.h"
#endif
#include "Character_System/Character.h"
#include "Character_System/Character_Mgr.h"
#include "../Buff/Buff_Logic.h"
#include "../Skill/Skill_Mgr.h"
#include "Impact_Logic.h"
#include "Common/Tool.h"
#include "Item_System/Item_Config_Data.h"
#include "Game_Interface/game_event_mgr.h"

#include "Skill_System/Skill/Skill_Logic.h"
#include "Skill_System/Skill/Technical_Mgr.h"

using namespace Game_Data;

//impactlogic_t const* impact_getlogic(uint32 impactid)
//{
//	return g_impactlogiclist.getlogicbyid(impactid);
//}

////////////////////////////////////////////////////////////////////////// 

void ImpactLogic_T::OnActive(Buff_Logic* /*buffPtr*/, uint32 /*index*/) const
{

}

void ImpactLogic_T::GetIntPropertyRefix(Buff_Logic* /*buffPtr*/, uint32 /*propertyIndex*/, uint32 /*impactIndex*/, uint32 /*type*/, sint32 &/*valueOut*/) const
{

}

void ImpactLogic_T::GetValueByModifyType(Buff_Logic* buffPtr, uint32 modifyType, sint32 &valueOut, uint32 index /*=0*/) const
{
	//if ( 0 == buffPtr || index >= MAX_IMPACT_COUNT )
		return;

	//ImpactInfo impactInfoPtr;
	//memset(&impactInfoPtr, 0, sizeof(ImpactInfo));
	//buffPtr->GetImapctInfo(index, impactInfoPtr);

	//switch( modifyType )
	//{
	//case MT_MODFITY_TYPE1:
	//	{
	//		if ( MT_MODFITY_TYPE1 == impactInfoPtr.impactParam2 )
	//		{
	//			valueOut += impactInfoPtr.impactParam3;
	//		}
	//	}
	//	break;
	//case MT_MODFITY_TYPE2:
	//	{
	//		// 获得自身属性的值
	//		Character* self = (Character* )CHARACTER_MGR::instance()->get_character( buffPtr->GetPlayerBuff()->m_characterbuff[CBA_RECEIVER_ID] );
	//		self = dynamic_cast<Character*>(self);
	//		if ( self )
	//		{
	//			valueOut = impactInfoPtr.impactParam3;
	//		}
	//	}
	//	break;
	//case MT_MODFITY_TYPE3:
	//	{
	//		if ( MT_MODFITY_TYPE3 == impactInfoPtr.impactParam2 )
	//		{
	//			valueOut = impactInfoPtr.impactParam3;
	//		}
	//	}
	//	break;
	//default:
	//	break;
	//}
}

////////////////////////////////////////////////////////////////////////// ImpactLogic1

void ImpactLogic1::OnActive(Buff_Logic* buffPtr, uint32 index) const
{
	//if ( 0 == buffPtr || index >= MAX_IMPACT_COUNT )
		return;

	/*ImpactInfo* impactInfoPtr = const_cast<ImpactInfo*>(buffPtr->GetImapctInfo(index));
	if ( 0 == impactInfoPtr )
		return;

	if ( impactInfoPtr->impactParam3 < RandGen::GetRand(1, PER_RATIO + 1) )
	{
		impactInfoPtr->impactParam4 = 0;
	}*/

	// 重新计算一下属性
}

void ImpactLogic1::GetIntPropertyRefix(Buff_Logic* buffPtr, uint32 propertyIndex, uint32 impactIndex, uint32 type, sint32 &valueOut) const
{
	return;
	/*ImpactInfo impactInfoPtr;
	memset(&impactInfoPtr, 0, sizeof(ImpactInfo));
	buffPtr->GetImapctInfo(impactIndex, impactInfoPtr);

	if ( (sint32)propertyIndex != impactInfoPtr.impactParam1 )
	return;

	GetValueByModifyType(buffPtr, type, valueOut, impactIndex);*/
}

////////////////////////////////////////////////////////////////////////// ImpactLogic2

void ImpactLogic2::OnActive(Buff_Logic* buffPtr, uint32 index) const
{
	/*
	if ( 0 == buffPtr || index >= 1 )
		return;

	Character_Buff*  buff = buffPtr->GetPlayerBuff();
	Character* self = CHARACTER_MGR::instance()->get_character( buff->m_characterbuff[CBA_RELEASEER_ID] );
	Character* target = CHARACTER_MGR::instance()->get_character( buff->m_characterbuff[CBA_RECEIVER_ID] );
	if ( NULL == self || NULL == target )
		return;

	Skill_Data* skill = SKILL_MGR::instance()->GetSkillData(buff->m_characterbuff[CBA_SKILL_ID]);
	if ( NULL == skill )
		return;

	// 计算伤害
	if ( 0 == buff->m_characterbuff[CBA_ONLY_HURT] )
	{
		// 无敌
		if ( target->get_character_invincible() > 0 )
		{  
#ifdef GAME_CLIENT
			if ( Game_Logic::Game_Event::EVENT_TYPE_PLAYER == target->get_character_type() || Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL == target->get_character_type() )
			{
//				UI::Actor *self_sprite = Game_Utils::instance()->get_primary_actor();
				UI::Dynamic_Sprite *self_sprite = Game_Utils::instance()->get_primary_sprite_by_id(buff->m_characterbuff[CBA_RECEIVER_ID]);
//				self_sprite->play_exclusive_effect("2008");
				//by liaopengfei 2013.11.26 换成持续性特效，以免影响正常的精灵特效体系
				int tag;
				self_sprite->play_continued_effect("2008", tag);
			} 
			else if ( Game_Logic::Game_Event::EVENT_TYPE_MONSTER == target->get_character_type() )
			{
				UI::Monster *monster_sprite = Game_Utils::instance()->get_monster_by_id( buff->m_characterbuff[CBA_RECEIVER_ID] );
//				monster_sprite->play_exclusive_effect("2008");
				//by liaopengfei 2013.11.26 换成持续性特效，以免影响正常的精灵特效体系
				int tag;
				monster_sprite->play_continued_effect("2008", tag);
			}
			else if ( Game_Logic::Game_Event::EVENT_TYPE_FIGHT_PLAYER == target->get_character_type() )
			{
				UI::Actor *fight_player = Game_Utils::instance()->get_opponent();
				int tag;
				fight_player->play_continued_effect("2008", tag);
			}
			Audio_Manager::shared_Audio_Manager()->play_effect("invincible.mp3");
			self->set_ai_state(GUARD_STATE);
#endif // GAME_CLIENT
			return;
		}
		// 闪避
#ifdef GAME_CLIENT
		bool is_hurting = false;
		if ( Game_Logic::Game_Event::EVENT_TYPE_PLAYER == target->get_character_type() || Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL == target->get_character_type() )
		{
//			UI::Actor *self_sprite = Game_Utils::instance()->get_primary_actor();
			UI::Dynamic_Sprite *self_sprite = Game_Utils::instance()->get_primary_sprite_by_id(buff->m_characterbuff[CBA_RECEIVER_ID]);
			if ( true == self_sprite->get_is_hurting() )
			{
				is_hurting = true;
			}
		} 
		else if ( Game_Logic::Game_Event::EVENT_TYPE_MONSTER == target->get_character_type() )
		{
			UI::Monster *monster_sprite = Game_Utils::instance()->get_monster_by_id( buff->m_characterbuff[CBA_RECEIVER_ID] );
			if ( true == monster_sprite->get_is_hurting() )
			{
				is_hurting = true;
			}
		}
		else if ( Game_Logic::Game_Event::EVENT_TYPE_FIGHT_PLAYER == target->get_character_type() )
		{
			UI::Actor *fight_player = Game_Utils::instance()->get_opponent();
			if ( true == fight_player->get_is_hurting() )
			{
				is_hurting = true;
			}
		}
		if ( true == is_hurting )
		{
			int hit_ratio = self->get_character_hit_ratio() - target->get_character_avoidance();
			if ( hit_ratio < RandGen::GetRand(0, PER_RATIO -1) )
			{
				if ( Game_Logic::Game_Event::EVENT_TYPE_PLAYER == target->get_character_type() || Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL == target->get_character_type() )
				{
//					UI::Actor *self_sprite = Game_Utils::instance()->get_primary_actor();
					UI::Dynamic_Sprite *self_sprite = Game_Utils::instance()->get_primary_sprite_by_id(buff->m_characterbuff[CBA_RECEIVER_ID]);
//					self_sprite->play_exclusive_effect("2005");
					//by liaopengfei 2013.11.26 换成持续性特效，以免影响正常的精灵特效体系
					int tag;
					self_sprite->play_continued_effect("2005", tag);
				} 
				else if ( Game_Logic::Game_Event::EVENT_TYPE_MONSTER == target->get_character_type() )
				{
					UI::Monster *monster_sprite = Game_Utils::instance()->get_monster_by_id( buff->m_characterbuff[CBA_RECEIVER_ID] );
//					monster_sprite->play_exclusive_effect("2005");
					//by liaopengfei 2013.11.26 换成持续性特效，以免影响正常的精灵特效体系
					int tag;
					monster_sprite->play_continued_effect("2005", tag);
				}
				else if ( Game_Logic::Game_Event::EVENT_TYPE_FIGHT_PLAYER == target->get_character_type() )
				{
					UI::Actor *fight_player = Game_Utils::instance()->get_opponent();
					int tag;
					fight_player->play_continued_effect("2005", tag);
				}
				Audio_Manager::shared_Audio_Manager()->play_effect("avoidance.mp3");
				Show_Top_Args args(target->get_database_character_id(), target->get_character_type(), "avoidance.png");
				Game_Utils::instance()->show_top( args );
				self->set_ai_state(GUARD_STATE);
				return;
			}
		}
#endif // GAME_CLIENT
	}

	int hurt_value = self->get_character_attack() - target->get_character_define();
	const ImpactInfo impactinfo1 = buffPtr->GetImapctInfo(0);
	const ImpactInfo impactinfo2 = buffPtr->GetImapctInfo(1);
	int old = target->get_character_cur_hp();
	if ( hurt_value <= 0 )
	{
		hurt_value = 1;
	}
	if ( MT_MODFITY_TYPE1 == impactinfo1.impactParam1 )
	{// Harm =（（ Attact–Defence）+技能伤害）×（技能百分比系数×(1+技能等级*技能百分比成长） × P
		hurt_value += impactinfo1.impactParam2;
	}
	else if ( MT_MODFITY_TYPE2 == impactinfo1.impactParam1 )
	{
		hurt_value = hurt_value + self->get_character_attack()*impactinfo1.impactParam2/PER_RATIO;
	}
	int skill_level = self->get_skill_level(buff->m_characterbuff[CBA_SKILL_ID]);
	float temp = 0.0;
	temp = 1+ (float)impactinfo2.impactParam4*(float)skill_level/PER_RATIO;
	temp *= impactinfo2.impactParam2;
	hurt_value = int(hurt_value*temp/PER_RATIO);
	int crit_rate = 0;
	if ( 0 == buff->m_characterbuff[CBA_ONLY_HURT] )
	{
		crit_rate = self->get_character_crit_rate() - target->get_character_tenacity();
		if ( buff->m_characterbuff[CBA_CRIT] )
		{
			hurt_value = hurt_value*self->get_character_crit()/PER_RATIO;
		}
	}
	
	// 罡气
	int yingzhe_time = 0;
	int X_Move = 0;
	int Y_Move  = 0;
	int hurtType  = 0;

	if ( 0 == buff->m_characterbuff[CBA_ONLY_HURT] )
	{
		int gangqi_reduce = 0;
		if ( target->get_character_cur_gp() > 0 )
		{
#ifdef GAME_CLIENT
			if ( Game_Logic::Game_Event::EVENT_TYPE_PLAYER == target->get_character_type() || Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL == target->get_character_type() )
			{
//				UI::Actor *self_sprite = Game_Utils::instance()->get_primary_actor();
				UI::Dynamic_Sprite *self_sprite = Game_Utils::instance()->get_primary_sprite_by_id(buff->m_characterbuff[CBA_RECEIVER_ID]);
//				self_sprite->play_exclusive_effect("2006");
				//by liaopengfei 2013.11.26 换成持续性特效，以免影响正常的精灵特效体系
				int tag;
				self_sprite->play_continued_effect("2006", tag);
			} 
			else if ( Game_Logic::Game_Event::EVENT_TYPE_MONSTER == target->get_character_type() )
			{
				UI::Monster *monster_sprite = Game_Utils::instance()->get_monster_by_id( buff->m_characterbuff[CBA_RECEIVER_ID] );
//				monster_sprite->play_exclusive_effect("2006");
				//by liaopengfei 2013.11.26 换成持续性特效，以免影响正常的精灵特效体系
				int tag;
				monster_sprite->play_continued_effect("2006", tag);
			}
			else if ( Game_Logic::Game_Event::EVENT_TYPE_FIGHT_PLAYER == target->get_character_type() )
			{
				UI::Actor *fight_player = Game_Utils::instance()->get_opponent();
				int tag;
				fight_player->play_continued_effect("2006", tag);
			}
			Audio_Manager::shared_Audio_Manager()->play_effect("gangqi.mp3");
			hurt_value *= (PER_RATIO - target->get_character_gp_reduce_hurt())/PER_RATIO;
			gangqi_reduce = 1;
#endif // GAME_CLIENT
		}

		hurtType = SKILL_LOGIC::instance()->GetHurtType(buff->m_characterbuff[CBA_IS_IN_AIR], buff->m_characterbuff[CBA_HURT_POS], skill->m_Attr[SA_ID]);
		if ( 1 == gangqi_reduce )
		{
			hurtType = -1;
		}
		if ( 0 == buff->m_characterbuff[CBA_IS_IN_AIR] )
		{
			X_Move = buff->m_characterbuff[CBA_MOVE_POS]*skill->m_Attr[SA_HURT_ROAD_X_MOVE];
			Y_Move  = skill->m_Attr[SA_HURT_ROAD_Y_MOVE];
		}
		else
		{
			X_Move = buff->m_characterbuff[CBA_MOVE_POS]*skill->m_Attr[SA_HURT_SKY_X_MOVE];
			Y_Move  = skill->m_Attr[SA_HURT_SKY_Y_MOVE];
		}
		
		yingzhe_time = skill->m_Attr[SA_YINGZHI_TIME];
	}
	hurt_value = -hurt_value;

	// 减去罡气
	int jipo = 0;
	int old_gangqi = target->get_character_cur_gp();
	target->set_character_cur_gp(target->get_character_cur_gp() + hurt_value);
	int new_gangqi = target->get_character_cur_gp();
	if ( old_gangqi > 0 && new_gangqi <= 0 )
	{
#ifdef GAME_CLIENT
		if ( Game_Logic::Game_Event::EVENT_TYPE_PLAYER == target->get_character_type() || Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL == target->get_character_type())
		{
//			UI::Actor *self_sprite = Game_Utils::instance()->get_primary_actor();
			UI::Dynamic_Sprite *self_sprite = Game_Utils::instance()->get_primary_sprite_by_id(buff->m_characterbuff[CBA_RECEIVER_ID]);
//			self_sprite->play_exclusive_effect("2007");
			//by liaopengfei 2013.11.26 换成持续性特效，以免影响正常的精灵特效体系
			int tag;
			self_sprite->play_continued_effect("2007", tag);
		} 
		else if ( Game_Logic::Game_Event::EVENT_TYPE_MONSTER == target->get_character_type() )
		{
			UI::Monster *monster_sprite = Game_Utils::instance()->get_monster_by_id( buff->m_characterbuff[CBA_RECEIVER_ID] );
//			monster_sprite->play_exclusive_effect("2007");
			//by liaopengfei 2013.11.26 换成持续性特效，以免影响正常的精灵特效体系
			int tag;
			monster_sprite->play_continued_effect("2007", tag);
		}
		else if ( Game_Logic::Game_Event::EVENT_TYPE_FIGHT_PLAYER == target->get_character_type() )
		{
			UI::Actor *fight_player = Game_Utils::instance()->get_opponent();
			int tag;
			fight_player->play_continued_effect("2007", tag);
		}
#endif
		jipo = 1;
	}// if ( old_gangqi > 0 && new_gangqi <= 0 )
	if ( 1 == jipo )
	{
		hurtType = SKILL_LOGIC::instance()->GetHurtType(0, buff->m_characterbuff[CBA_HURT_POS], skill->m_Attr[SA_ID]);
	}
	// 减去血量
	target->set_character_cur_hp(old + hurt_value);
#ifdef GAME_CLIENT
	int target_characterId = target->get_database_character_id();
	if ( target->get_character_cur_hp() <= 0 )
	{
		X_Move = 387 * buff->m_characterbuff[CBA_MOVE_POS];
		Y_Move = 774;
		if ( 0 == buff->m_characterbuff[CBA_HURT_POS] )
		{// 后面
			hurtType = BACK_HIT_FLY;
		}
		else
		{// 前面
			hurtType = HIT_FLY;
		}
	}
	Hurt_Args args(target_characterId, target->get_character_type(), hurtType, hurt_value, buff->m_characterbuff[CBA_RELEASEER_ID], yingzhe_time, (float)X_Move, (float)Y_Move);
	Game_Utils::instance()->hurt(args);
#endif

	if (hurt_value<0)
	{
		if ( 0 == buff->m_characterbuff[CBA_ONLY_HURT] )
		{
			Character* releaser = CHARACTER_MGR::instance()->get_character( buff->m_characterbuff[CBA_RELEASEER_ID] );
			if (releaser)
			{
				if (Game_Logic::Game_Event::EVENT_TYPE_PLAYER==releaser->get_character_type() /*|| Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL == target->get_character_type() )
				{
#ifdef GAME_CLIENT
					UI::Actor *self_sprite = Game_Utils::instance()->get_primary_actor();
					if ( self_sprite->sprite_id() == releaser->get_database_character_id() )
					{
						releaser->set_character_combo(releaser->get_character_combo()+1);//释放者连击数+1
						Game_Utils::instance()->update_combo(releaser->get_database_character_id(),releaser->get_character_type(), releaser->get_character_combo());
					}
#endif
				}
			}
			target->set_character_combo(0); //受伤者，连击数清0
			if (Game_Logic::Game_Event::EVENT_TYPE_PLAYER==target->get_character_type() /*|| Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL == target->get_character_type() )
			{
#ifdef GAME_CLIENT
				UI::Actor *self_sprite = Game_Utils::instance()->get_primary_actor();
				if ( self_sprite->sprite_id() == releaser->get_database_character_id() )
				{
					Game_Utils::instance()->update_combo(target->get_database_character_id(),target->get_character_type(), target->get_character_combo());
				}

				target->set_character_no_hurt_time(GetCurTime());
				

				if(target->get_character_cur_hp() > 0)
				{
					hurt_value = -hurt_value;
					UI::Unique_Skill::get_instance()->calculateAngryNum(UI::Unique_Skill::gainType::BE_HIT_BY_ENEMY,target->get_database_character_id(), hurt_value);
				}
				else //角色死亡
				{
					//清理数据  为 0 
					CCLOG("set role ANGRY_GAS = 0 ");
					UI::Unique_Skill::get_instance()->setAngryGas(target->get_database_character_id());
				}
#endif
			}// if (Game_Logic::Game_Event::EVENT_TYPE_PLAYER==target->get_character_type())
			else if (Game_Logic::Game_Event::EVENT_TYPE_PLAYER == releaser->get_character_type()  || Game_Logic::Game_Event::EVENT_TYPE_DEPUTY_GENERAL == releaser->get_character_type())
			{
#ifdef GAME_CLIENT
				if(target->get_character_cur_hp()<=0)  //没死一个怪 都会调用一次  所以此处不用计数器
				{
					UI::Unique_Skill::get_instance()->calculateAngryNum(UI::Unique_Skill::gainType::KILL_ENEMY,releaser->get_database_character_id(),1);
				}
#endif
			}
#ifdef GAME_CLIENT
			Game_Utils::instance()->createShake( skill->m_Attr[SA_SHAKE_ID] );
			if ( 0 == jipo )
			{
				releaser->set_ai_state(NOMAL_STATE);
			}
			else
			{
				releaser->set_ai_state(GUARD_STATE);
			}
#endif
		}// if ( 0 == buff->m_characterbuff[CBA_ONLY_HURT] )
	}*/
}

////////////////////////////////////////////////////////////////////////// ImpactLogic3

void ImpactLogic3::OnActive(Buff_Logic* buffPtr, uint32 index) const
{
	//if ( 0 == buffPtr || index >= MAX_IMPACT_COUNT )
		return;

	/*ImpactInfo* impactInfoPtr = const_cast<ImpactInfo*>(buffPtr->GetImapctInfo(index));
	if ( 0 == impactInfoPtr )
		return;*/

	/*Team * attackerTeamPtr   = const_cast<Team*>(INSTANCE_COMBAT_LOGIC()->GetTeam(releaseSide, buffPtr->GetBuffData(RELEASER_IDX)));
	Team * beAttackerTeamPtr = const_cast<Team*>(INSTANCE_COMBAT_LOGIC()->GetTeam(receiveSide, buffPtr->GetBuffData(RECEIVER_IDX)));
    if ( 0 == attackerTeamPtr || 0 == beAttackerTeamPtr )
		return;

	StatusSummary* beAttackerStatusSummray = INSTANCE_COMBAT_LOGIC()->GetStatusSummary(receiveSide, buffPtr->GetBuffData(RECEIVER_IDX));
	if ( 0 == beAttackerStatusSummray )
		return;

	int32  reciverTroops  = 0;
	int32  reciverMorals  = 0;
	switch(impactInfoPtr->impactParam1)
	{
	case ST_TROOPS:
		{
			GetValueByModifyType(buffPtr, releaseSide, receiveSide, impactInfoPtr->impactParam2, reciverTroops, index, loop);
			if ( reciverTroops > 0 )
			{
				if ( reciverTroops > (int32)beAttackerTeamPtr->info.troopsMax - (int32)beAttackerTeamPtr->info.troops )
				{
					reciverTroops = (int32)beAttackerTeamPtr->info.troopsMax - (int32)beAttackerTeamPtr->info.troops;
				}
			}
			else if ( reciverTroops < 0 )
			{
				if ( -reciverTroops > beAttackerTeamPtr->info.troops )
				{
					reciverTroops = -beAttackerTeamPtr->info.troops;
				}
			}

			if ( reciverTroops == 0 && 2 == buffPtr->GetBuffInfo()->influenceType)
			{
				reciverTroops = -1;
			}
			
			beAttackerTeamPtr->info.troops += reciverTroops;
			if ( beAttackerTeamPtr->info.troops <= 0 )
			{
				INSTANCE_COMBAT_LOGIC()->RemoveAllBuff(receiveSide, buffPtr->GetBuffData(RECEIVER_IDX));
			}
		}
		break;
	case ST_MORALE:
		{
			GetValueByModifyType(buffPtr, releaseSide, receiveSide, impactInfoPtr->impactParam2, reciverMorals, index, loop);
			if ( MT_MODFITY_TYPE3 == impactInfoPtr->impactParam2 )
			{
				int32 temp = reciverMorals - beAttackerTeamPtr->info.morals;
				beAttackerTeamPtr->info.morals = reciverMorals;
				reciverMorals = temp;
			}
			else
			{
				beAttackerTeamPtr->info.morals     += reciverMorals;
			}
		}
		break;
	case ST_SKILL_ACTION_RATIO:
		{
			int32 tempValue = 0;
			GetValueByModifyType(buffPtr, releaseSide, receiveSide, impactInfoPtr->impactParam2, tempValue, index, loop);
			tempValue += buffPtr->GetBuffData(ACTION_RATIO);
			buffPtr->SetBuffData(ACTION_RATIO, tempValue);
		}
		break;
	default:
		break;
	}

	ActionCombatResult* actionCombatResultPtr = INSTANCE_COMBAT_CALC()->GetActionCombatResult();
	if ( CS_RED == releaseSide )
	{
		actionCombatResultPtr->combatResult2.idx = buffPtr->GetBuffData(RELEASER_IDX);
	}
	else
	{
		actionCombatResultPtr->combatResult2.idx = buffPtr->GetBuffData(RELEASER_IDX) + 10;
	}
	actionCombatResultPtr->combatResult2.action  = ACT_PHYSICAL_ATTACK;

	uint32 idxTemp = INSTANCE_COMBAT_CALC()->GetResultReciverIndex(receiveSide, buffPtr->GetBuffData(RECEIVER_IDX)); 
	if ( FORMATION_SIZE*2 == idxTemp )
	{
		if ( CS_RED == receiveSide )
		{
			actionCombatResultPtr->combatResult3[actionCombatResultPtr->combatResult3Count].idx = buffPtr->GetBuffData(RECEIVER_IDX);			
		}
		else
		{
			actionCombatResultPtr->combatResult3[actionCombatResultPtr->combatResult3Count].idx = buffPtr->GetBuffData(RECEIVER_IDX) + 10;
		}
		actionCombatResultPtr->combatResult3[actionCombatResultPtr->combatResult3Count].troops += reciverTroops;
		actionCombatResultPtr->combatResult3[actionCombatResultPtr->combatResult3Count].morals += reciverMorals;
		if ( buffPtr->GetBuffInfo()->lastTime > 0 )
		{
			actionCombatResultPtr->combatResult3[actionCombatResultPtr->combatResult3Count].addBuffId += buffPtr->GetBuffData(BUFF_ID);
		}
		actionCombatResultPtr->combatResult3Count++;
	}
	else
	{
		actionCombatResultPtr->combatResult3[idxTemp].troops += reciverTroops;
		actionCombatResultPtr->combatResult3[idxTemp].morals += reciverMorals;
		if ( buffPtr->GetBuffInfo()->lastTime > 0 )
		{
			actionCombatResultPtr->combatResult3[idxTemp].addBuffId = buffPtr->GetBuffData(BUFF_ID);
		}
	}*/
}

////////////////////////////////////////////////////////////////////////// ImpactLogic4

void ImpactLogic4::OnActive(Buff_Logic* buffPtr, uint32 index) const
{
	//if ( 0 == buffPtr  || index >= MAX_IMPACT_COUNT )
		return;

	/*ImpactInfo* impactInfoPtr = const_cast<ImpactInfo*>(buffPtr->GetImapctInfo(index));
	if ( 0 == impactInfoPtr )
		return;*/

	/*Team * attackerTeamPtr   = const_cast<Team*>(INSTANCE_COMBAT_LOGIC()->GetTeam(releaseSide, buffPtr->GetBuffData(RELEASER_IDX)));
	Team * beAttackerTeamPtr = const_cast<Team*>(INSTANCE_COMBAT_LOGIC()->GetTeam(receiveSide, buffPtr->GetBuffData(RECEIVER_IDX)));
	if ( 0 == attackerTeamPtr || 0 == beAttackerTeamPtr )
	return;

	StatusSummary* attackerStatusSummray = INSTANCE_COMBAT_LOGIC()->GetStatusSummary(releaseSide, buffPtr->GetBuffData(RELEASER_IDX));
	if ( 0 == attackerStatusSummray )
	return;

	int32  reciverTroops  = 0;
	int32  reciverMorals  = 0;
	switch(impactInfoPtr->impactParam1)
	{
	case ST_MORALE:
	{
	GetValueByModifyType(buffPtr, releaseSide, receiveSide, impactInfoPtr->impactParam2, reciverMorals, index, loop);
	attackerTeamPtr->info.morals     += reciverMorals; 
	}
	break;
	case ST_SKILL_ACTION_RATIO:
	{
	int32 tempValue = 0;
	GetValueByModifyType(buffPtr, releaseSide, receiveSide, impactInfoPtr->impactParam2, tempValue, index, loop);
	tempValue += buffPtr->GetBuffData(ACTION_RATIO);
	buffPtr->SetBuffData(ACTION_RATIO, tempValue);
	}
	break;
	default:
	break;
	}

	ActionCombatResult* actionCombatResultPtr = INSTANCE_COMBAT_CALC()->GetActionCombatResult();
	if ( CS_RED == releaseSide )
	{
	actionCombatResultPtr->combatResult2.idx = buffPtr->GetBuffData(RELEASER_IDX);
	}
	else
	{
	actionCombatResultPtr->combatResult2.idx = buffPtr->GetBuffData(RELEASER_IDX) + 10;
	}
	actionCombatResultPtr->combatResult5.morals += reciverMorals;*/
}

////////////////////////////////////////////////////////////////////////// ImpactLogic5

void ImpactLogic5::OnActive(Buff_Logic* buffPtr, uint32 index) const
{
	//if ( 0 == buffPtr || index >= MAX_IMPACT_COUNT )
		return;

	/*ImpactInfo* impactInfoPtr = const_cast<ImpactInfo*>(buffPtr->GetImapctInfo(index));
	if ( 0 == impactInfoPtr )
		return;*/

	/*General* gnPtr = INSTANCE_LOGIC()->GetGeneral(buffPtr->GetBuffData(RECEIVER_ID));
	if ( 0 == gnPtr )
	return;

	uint32 type = impactInfoPtr->impactParam1;
	uint32 count = impactInfoPtr->impactParam2;
	for (uint32 i = 0; i < count; i++)
	{
	for (uint32 j = 0; j < MAX_BUFF_COUNT; j++)
	{
	Buff* buffTempPtr = INSTANCE_COMBAT_LOGIC()->GetBuffByIndex(receiveSide, buffPtr->GetBuffData(RELEASER_IDX), j);
	if ( 0 != buffTempPtr && 0 != buffTempPtr->GetBuffInfo() && type & buffTempPtr->GetBuffInfo()->influenceType )
	{
	INSTANCE_COMBAT_LOGIC()->RemoveBuffByIndex(releaseSide, receiveSide, buffPtr->GetBuffData(RELEASER_IDX), j);
	break;
	}
	}
	}*/
}


////////////////////////////////////////////////////////////////////////// ImpactLogic6

void ImpactLogic6::OnActive(Buff_Logic* buffPtr, uint32 index) const
{
	//if ( 0 == buffPtr || index >= MAX_IMPACT_COUNT )
		return;

	/*ImpactInfo* impactInfoPtr = const_cast<ImpactInfo*>(buffPtr->GetImapctInfo(index));
	if ( 0 == impactInfoPtr )
		return;*/

	/*Team* attackerTeam = INSTANCE_COMBAT_LOGIC()->GetTeam(releaseSide, buffPtr->GetBuffData(RELEASER_IDX));
	if ( 0 == attackerTeam )
	return;

	int32 reciverTroops = 0;
	int32 reciverMorals = 0;
	switch(impactInfoPtr->impactParam1)
	{
	case ST_MORALE:
	{
	GetValueByModifyType(buffPtr, releaseSide, receiveSide, impactInfoPtr->impactParam2, reciverMorals, index, loop);
	attackerTeam->info.morals     += reciverMorals; 
	}
	break;
	case ST_TROOPS:
	{
	GetValueByModifyType(buffPtr, releaseSide, receiveSide, impactInfoPtr->impactParam2, reciverTroops, index, loop);
	}
	break;
	case ST_SKILL_ACTION_RATIO:
	{
	int32 tempValue = 0;
	GetValueByModifyType(buffPtr, releaseSide, receiveSide, impactInfoPtr->impactParam2, tempValue, index, loop);
	tempValue += buffPtr->GetBuffData(ACTION_RATIO);
	buffPtr->SetBuffData(ACTION_RATIO, tempValue);
	}
	break;
	default:
	break;
	}

	ActionCombatResult* actionCombatResultPtr = INSTANCE_COMBAT_CALC()->GetActionCombatResult();
	switch(combatStep)
	{
	case CRS_ACTION_START:
	{
	actionCombatResultPtr->combatResult1.idx  = buffPtr->GetBuffData(RELEASER_IDX);
	actionCombatResultPtr->combatResult1.troops += reciverTroops;
	}
	break;
	case CRS_SELF:
	{
	actionCombatResultPtr->combatResult2.action  = ACT_PHYSICAL_ATTACK;
	actionCombatResultPtr->combatResult3[actionCombatResultPtr->combatResult3Count - 1].idx = buffPtr->GetBuffData(RECEIVER_IDX);			
	actionCombatResultPtr->combatResult3[actionCombatResultPtr->combatResult3Count - 1].troops += reciverTroops;
	}
	break;
	case CRS_ACTION_END:
	{
	actionCombatResultPtr->combatResult5.idx  = buffPtr->GetBuffData(RELEASER_IDX);
	actionCombatResultPtr->combatResult5.troops += reciverTroops;
	}
	break;
	default:
	break;
	}*/

}


