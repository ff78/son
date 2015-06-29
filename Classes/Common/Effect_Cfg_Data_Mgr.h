#ifndef EFFECT_CFG_DATA_MGR_H
#define EFFECT_CFG_DATA_MGR_H

#include "json/json_header.h"
#include "cocos2d.h"

USING_NS_CC;

class Effect_Cfg_Data_Mgr:public Ref
{
public:
	Effect_Cfg_Data_Mgr(void);
	~Effect_Cfg_Data_Mgr(void);

    static Effect_Cfg_Data_Mgr* instance();

	int load_config(void);
	int get_effect_cfg(const std::string& effect_id ,
		std::string &effect_path,
		float &duration_time,
		float &scale,
		float &x,
		float &y,
		float &delay_time );
	int get_effect(cocos2d::Sprite * effect_sprite, const std::string& effect_id);
	int get_effect_without_position( cocos2d::Sprite * effect_sprite, const std::string& effect_id );
	int get_effect(cocos2d::Sprite * effect_sprite, Json::Value * effect_cfs, bool bflip);
	void get_image(cocos2d::Sprite* image_sprite,std::string image_path,float time);
	cocos2d::Animation* get_Animation(const std::string& effect_id);
    void clean_effect(Node * effect);
private:
	Json::Value config_data_;
    static Effect_Cfg_Data_Mgr* instance_;
};

#endif