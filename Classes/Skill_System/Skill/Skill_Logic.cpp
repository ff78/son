#ifdef GAME_SERVER
#include "logger.h"
#endif //GAME_SERVER
#include "Network_Common/message_stream.h"
#include "Game_Interface/game_content_interface.h"
#include "Game_Interface/game_event_response.h"
#include "Character_System/Character_Mgr.h"
#include "Character_System/Player.h"
#include "Skill_System/Skill/Technical_Mgr.h"
#include "../Buff/Buff_Mgr.h"
#include "../Buff/Buff_Logic.h"
#include "Common/Tool.h"
#include "../Impact/Impact_Common.h"
#include "Skill_Mgr.h"
#include "Player_Account/Account_Data_Mgr.h"

#ifdef GAME_SERVER
#include "log_common_defines.h"
#include "LoggerFacade.h"
#endif //GAME_SERVER

#ifdef GAME_CLIENT
#include "Game/Hurt_Utils.h"
#endif
#include "Skill_Logic.h"

Skill_Logic* Skill_Logic::instance_ = NULL;
Skill_Logic::Skill_Logic(void)
{
}

Skill_Logic::~Skill_Logic(void)
{
}

Skill_Logic* Skill_Logic::instance()
{
    if(instance_ == NULL)
    {
        instance_ = new Skill_Logic;
    }

    return instance_;
}

uint32 Skill_Logic::CanUseSkill(Character* self, Character* target, Skill_Data* skill) const
{
	if ( NULL == self || NULL == target || NULL == skill )
		return 1;

	// �Լ��Ƿ�����
	if ( self->get_character_cur_hp() <= 0 )
	{
		return 2;
	}
	// Ŀ���Ƿ�����
	if ( target->get_character_cur_hp() <= 0 )
	{
		return 3;
	}
	// ��ɫ�Ƿ���������
	// �����Ƿ�����ȴ
	// ��ǰ״̬�Ƿ����ʹ�ü���
	// �����Ƿ�����

	return 0;
}

uint32 Skill_Logic::UseSkill(Skill_Use & skilluse) const
{
	Character* self   = CHARACTER_MGR::instance()->get_character( skilluse.nSelfID );
	Character* target = CHARACTER_MGR::instance()->get_character( skilluse.nTargetID );
	Skill_Data* skill = Skill_Mgr::instance()->GetSkillData(skilluse.nSkillID);
	if ( NULL == self || NULL == target /*|| skilluse.nLevel >= SKILL_MAX_LEVEL*/ )
    {
		return 1;
    }

	if ( CanUseSkill(self, target, skill) )
	{   
		return 2;
	}

	// ��������
	// ������ȴ

	int bCritical = CriticalHitThisTarget(self, target);
#ifdef GAME_CLIENT
	if ( 1 == bCritical )
	{
		/*Show_Top_Args args(target->get_database_character_id(), target->get_character_type(), "Crit.png");
		Game_Utils::instance()->show_top( args );*/
	}
#endif // GAME_CLIENT

	AddBuff(self, target, skilluse.nSkillID, skill->m_Attr[SA_TARGET_BUFF_ID], skilluse.nMovePos, skilluse.nHurtPos, skilluse.is_in_the_air_, bCritical);

	return 0;
}

uint32 Skill_Logic::AddBuff(Character* self, Character* target, BuffID_t nBuffId, bool is_in_air, int nBuffLevel) const
{
	//Buff_Data* newDataPtr = BUFF_MGR::instance()->GetBuffData(nBuffId);
	//if( NULL == newDataPtr )
	//{
	//	return BA_ERROR;
	//}

	//Buff_Logic buffLogic;
	//buffLogic.InitBuffData(nBuffId, 0, nBuffLevel, newDataPtr, self->get_database_character_id(), target->get_database_character_id(), 0, 0, is_in_air, 0);
	//buffLogic.Active();
	//if ( buffLogic.GetBuffInfo()->m_Attr[BA_LAST_TIME] > 0 )
	//{
	//	target->insert_buff( &buffLogic );
	//}

	return 0;
}

uint32 Skill_Logic::AddBuff(Character* self, Character* target, SkillID_t nSkillID, BuffID_t nBuffId, int movePos, int hurtPos, bool is_in_air, int bCritical) const
{
	//Buff_Data* newDataPtr = BUFF_MGR::instance()->GetBuffData(nBuffId);
	//if( NULL == newDataPtr )
 //   {
	//	return BA_ERROR;
 //   }

	//int old_buff_index = target->get_buff_replace_index( newDataPtr );
	//if ( old_buff_index < 0 )
	//{// û��ͬ���Buff
	//	Buff_Logic buffLogic;
	//	buffLogic.InitBuffData(nBuffId, nSkillID, self->get_skill_level(nSkillID), newDataPtr, self->get_database_character_id(), target->get_database_character_id(), movePos, hurtPos, is_in_air, bCritical);
	//	buffLogic.Active();
	//	if ( buffLogic.GetBuffInfo()->m_Attr[BA_LAST_TIME] > 0 )
	//	{
	//		target->insert_buff( &buffLogic );
	//	}
	//}
	//else
	//{// ��ͬ���Buff
	//	Buff_Logic* oldBuffPtr = target->get_buff_logic_by_index( old_buff_index );
	//	if ( newDataPtr->m_Attr[BA_PRIORITY] < oldBuffPtr->GetBuffInfo()->m_Attr[BA_PRIORITY] ) 
	//	{// ��buff���ȼ�С��ԭbuff
	//		// ���ȼ��;Ͳ������
	//	}
	//	else
	//	{// ��buff���ȼ����ڵ���ԭbuff
	//		Character_Buff* characterBuffPtr = oldBuffPtr->GetPlayerBuff();
	//		if ( newDataPtr->m_Attr[BA_MAX_LAYER] > 1 )
	//		{// ��buff�����Ӳ�������1
	//			if ( characterBuffPtr->m_characterbuff[CBA_LAYER] < oldBuffPtr->GetBuffInfo()->m_Attr[BA_MAX_LAYER])
	//				characterBuffPtr->m_characterbuff[CBA_LAYER]++;
	//		}
	//		else
	//		{
	//			if ( newDataPtr->m_Attr[BA_PRIORITY] == oldBuffPtr->GetBuffInfo()->m_Attr[BA_PRIORITY] )
	//			{// ��buff���ȼ��Ƿ����ԭbuff
	//				// b)	ˢ�£�ԭbuffЧ�����䡢����ʱ�������
	//				characterBuffPtr->m_characterbuff[CBA_LAST_TIME] = oldBuffPtr->GetBuffInfo()->m_Attr[BA_LAST_TIME];
	//			}
	//			else
	//			{
	//				//ԭbuff�Ƴ��������buff���������Զ����¿�ʼ���㣨buffЧ��������ʱ�䣩
	//				target->remove_buff( oldBuffPtr->GetBuffInfo()->m_Attr[BA_ID] );
	//				Buff_Logic buffLogic;
	//				buffLogic.InitBuffData(nBuffId, nSkillID, self->get_skill_level(nSkillID), newDataPtr, self->get_database_character_id(), target->get_database_character_id(), movePos, hurtPos, is_in_air, bCritical);
	//				buffLogic.Active();
	//				target->insert_buff( &buffLogic );
	//			}
	//		}
	//	}
	//}

	return 0;
}

uint32 Skill_Logic::CalculateTargetList(Character & /*rMe*/, OBJLIST& /*rTargets*/) const
{
	return 0;
}

uint32 Skill_Logic::HitThisTarget(Character& /*rMe*/, Character& /*rTar*/) const
{
	return 0;
}

uint32 Skill_Logic::EffectOnUnitOnce(Character& /*rMe*/, Character& /*rTar*/, BYTE /*HitTimes*/, BOOL /*bCriticalFlag*/) const
{
	// ���ݹ������BUFF
	return 0;
}

int Skill_Logic::CriticalHitThisTarget(Character* self, Character* target) const
{
	int crit_rate = self->get_character_crit_rate() - target->get_character_tenacity();
	if ( crit_rate >= RandGen::GetRand(0, PER_RATIO -1) )
	{
		return 1;
	}

	return 0;
}

uint32 Skill_Logic::GetHurtType(int pos, int hurtPos, int skillId)
{
	int value = 0;
	Skill_Data* skill = Skill_Mgr::instance()->GetSkillData(skillId);
	if ( 0 == skill )
		return value;

	if ( 0 == pos )
	{// ����
		if ( 0 != skill->m_Attr[SA_HURT_ROAD_Y_MOVE] )
		{// �����и߶Ȳ�Ϊ0
			if ( 0 == hurtPos )
			{// ����
				value = BACK_HIT_FLY;
			}
			else
			{// ǰ��
				value = HIT_FLY;
			}
		}
		else
		{// �����и߶�Ϊ0
			if ( 0 == hurtPos )
			{// ����
				if ( 0 == skill->m_Attr[SA_HURT_LEVEL] )
				{// ���ܴ�
					value = BACK_LIGHT_HIT;
				}
				else
				{// ���ܴ�
					value = BACK_HEAVY_HIT;
				}
			}
			else
			{// ǰ��
				if ( 0 == skill->m_Attr[SA_HURT_LEVEL] )
				{// ���ܴ�
					value = LIGHT_HIT;
				}
				else
				{// ���ܴ�
					value = HEAVY_HIT;
				}
			}
		}
	}
	else
	{// ����
		if ( 0 == hurtPos )
		{// ����
			value = BACK_HIT_FLY;
		}
		else
		{// ǰ��
			value = HIT_FLY;
		}
	}

	return value;
}

int Skill_Logic::save_skill(int player_id)
{
	Player* player  = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character( player_id ));
	if ( NULL == player )
	{
		return -1;
	}

	for (int i = 0; i < player->get_skill_size(); i++)
	{
		vector<uint64> para;
		para.push_back(player_id);
		para.push_back(player_id);
		para.push_back(player->get_skill_by_index(i)->database_id);
		Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_skill", para);
	}

	Deputy_General_Map& general_map = player->get_deputy_general();
	DeputyGeneral* general = NULL;
	Deputy_General_Map_Iter iter = general_map.begin();
	for (;iter != general_map.end();++iter)
	{
		general = iter->second;
		if (general)
		{
			vector<Character_Skill>&skill_vector = general->get_skill_vector();
			vector<Character_Skill>::iterator it = skill_vector.begin();
			for (; it != skill_vector.end(); it++)
			{
				vector<uint64> para;
				para.push_back(player_id);
				para.push_back(general->get_database_character_id());
				para.push_back(it->database_id);
				Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_skill", para);
			}
		}
	}

	return 0;
}
#ifdef GAME_CLIENT
void Skill_Logic::load_skill(int character_id)
{

	if (SKILL_MGR::instance()->is_load())
	{
		return;
	}
    
	std::vector<uint64> para;
	para.push_back(character_id);
	Game_Logic::Game_Content_Interface::instance()->exec_interface("send_load_skill", para);

}
#endif
bool Skill_Logic::fill_skill_message_stream(int player_id, message_stream& ms)
{
	Player* player = dynamic_cast<Player*>(CHARACTER_MGR::instance()->get_character( player_id ));
	if ( NULL == player )
		return false;

	int player_skill_count = player->get_skill_size();
    int general_skill_count = player->get_deputy_general_skill_count();

	ms << (player_skill_count + general_skill_count);

	for (int i = 0; i < player_skill_count; i++)
	{
        ms << player->get_database_character_id();
		ms << player->get_skill_by_index(i)->skill_id;
		//ms << player->get_skill_by_index(i)->skill_level;
	}

    int count = 0;
    Deputy_General_Map& general_map = player->get_deputy_general();
    DeputyGeneral* general = NULL;
    Deputy_General_Map_Iter iter = general_map.begin();
    for (;iter != general_map.end();++iter)
    {
        general = iter->second;
        if (general)
        {
            count = general->get_skill_size();
            for (int i = 0; i < count; i++)
            {
                ms << general->get_database_character_id();
                ms << general->get_skill_by_index(i)->skill_id;
                //ms << general->get_skill_by_index(i)->skill_level;
            }
        }
    }

	return true;
}

bool Skill_Logic::fill_create_deputy_general_skill_message_stream(int deputy_general_id, message_stream& ms)
{
    DeputyGeneral* general = dynamic_cast<DeputyGeneral*>(CHARACTER_MGR::instance()->get_character( deputy_general_id ));
    if (!general)
    {
        return false;
    }

    int skill_count = general->get_skill_size();
    ms << skill_count;

    for (int i = 0; i < skill_count; i++)
    {
        ms << general->get_database_character_id();
        ms << general->get_skill_by_index(i)->skill_id;
        //ms << general->get_skill_by_index(i)->skill_level;
    }

    return true;
}

uint32 Skill_Logic::uplevel_skill(int player_id, int character_id, int skill_id, int & skill_level_out)
{
    Game_Data::Player* player = dynamic_cast<Game_Data::Player*>(CHARACTER_MGR::instance()->get_character(player_id));
    if ( NULL == player )
        return 1;

	Game_Data::Character* character = CHARACTER_MGR::instance()->get_character(character_id);
	if ( NULL == character )
		return 7;
    

	Character_Skill* skill = character->get_skill_by_id(skill_id);
	if ( NULL == skill )
	{
		return 4;
	}

    /*if (skill->skill_level*10 > character->get_character_level())
    {
        return 6;
    }*/
    
	
	Technical_Data* technical = TECHNICAL_MGR::instance()->GetTechnicalData(skill->skill_id);
	if ( NULL == technical )
	{
		return 5;
	}
	
	// �����������ģ�
	/*int need_money = technical->learn_base_money + technical->learn_level_money * (skill->skill_level - 1);
	int self_money = player->get_gold();
	if ( self_money < need_money )
	{
		return 2;
	}
	if ( skill->skill_level >= technical->levelup_max )
	{
		return 3;
	}*/

#ifdef GAME_SERVER
		int original_money_value = self_money;
#endif //GAME_SERVER

	/*player->change_gold(-need_money);
	character->set_skill_level(skill_id, skill->skill_level + 1);*/
	skill_level_out = character->get_skill_level(skill_id);
#ifdef GAME_SERVER
	LoggerFacade::instance()->facade_role_money_die(player_id,MONEY_DEAD_REASON_SKILL_UP_COST,skill_id,MONEY_TYPE_JINBI,original_money_value,need_money,1);
#endif //GAME_SERVER
	
    Game_Logic::Game_Event_Response::instance()->on_skill_upgrade( player_id, skill_id );

    // save db 
    vector<uint64> para;
    para.push_back(player_id);
    Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_role_gold",para);
    // save db
    para.clear();
    para.push_back(player_id);
    para.push_back(character_id);
	para.push_back(character->get_skill_database_id_by_id(skill_id));
	Game_Logic::Game_Content_Interface::instance()->exec_interface("sql_update_skill", para);
	return 0;
}
