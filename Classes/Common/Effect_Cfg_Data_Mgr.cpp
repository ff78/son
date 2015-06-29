#include "Effect_Cfg_Data_Mgr.h"
#include "json/json_header.h"
#include "Common/Utils.h"
#include "vector"


Effect_Cfg_Data_Mgr* Effect_Cfg_Data_Mgr::instance_ = 0;
Effect_Cfg_Data_Mgr::Effect_Cfg_Data_Mgr(void)
{
}


Effect_Cfg_Data_Mgr::~Effect_Cfg_Data_Mgr(void)
{
}

Effect_Cfg_Data_Mgr* Effect_Cfg_Data_Mgr::instance()
{
    if( NULL == instance_ )
        instance_ = new Effect_Cfg_Data_Mgr;

    return instance_;
}

int Effect_Cfg_Data_Mgr::load_config(void){
	Json::Value data;
    Utils::get_value_by_file("game_data/effect_config.json", data);
	config_data_ = data["effect_map"];
	return 0;

}

int Effect_Cfg_Data_Mgr::get_effect_cfg(const std::string& effect_id ,
										std::string &effect_path,
										float &duration_time,
										float &scale,
										float &x,
										float &y,
										float &delay_time )
{
	Json::Value& item_config = config_data_[effect_id];
	if(item_config.isNull()){
		return -1;
	}
	effect_path = item_config["path"].asCString();
	duration_time = item_config["duration"].asInt()/1000.f;
	scale = item_config["scale"].asFloat();
	x = item_config["pos_x"].asFloat();
	y = item_config["pos_y"].asFloat();
	delay_time = item_config["delay_time"].asInt()/1000.f;
	return 0;
}
void Effect_Cfg_Data_Mgr::get_image(cocos2d::Sprite* image_sprite,std::string image_path,float time)
{
//yypp	image_sprite->initWithFile(image_path.c_str());
	cocos2d::Size sz=Director::getInstance()->getWinSize();
	image_sprite->setPosition(Vec2(sz.width/2,sz.height*2/3));
	image_sprite->setScale(2.0f);
	ActionInterval* delay=CCDelayTime::create(time);
	FiniteTimeAction* se=CCSequence::create(delay,CallFuncN::create(this,callfuncN_selector(Effect_Cfg_Data_Mgr::clean_effect)),NULL);
	image_sprite->runAction(se);
}
int Effect_Cfg_Data_Mgr::get_effect_without_position( cocos2d::Sprite * effect_sprite, const std::string& effect_id )
{
	cocos2d::Animation * animation = get_Animation(effect_id);
	if(!animation){
		return -1;
	}
	Json::Value& item_config = config_data_[effect_id];
	float scale = item_config["scale"].asFloat();
	float x = item_config["pos_x"].asFloat();
	float y = item_config["pos_y"].asFloat();
	float delay_time = item_config["delay_time"].asInt()/1000.f;
	bool loop = item_config["loop"].asInt()==1;

	effect_sprite->setScale(scale);
	//effect_sprite->setPosition( Vec2(x,y));

	FiniteTimeAction* action;
	if(loop){
		action = CCRepeatForever::create( CCAnimate::create(animation) );
	}
	else{
		effect_sprite->setVisible(false);
		action = CCSequence::create
			(
			CCDelayTime::create(delay_time),
			CCShow::create(),
			CCAnimate::create(animation),
			CallFuncN::create(this, callfuncN_selector(Effect_Cfg_Data_Mgr::clean_effect)),
			NULL);
	}

	effect_sprite->runAction(action);
	return 0;
}
int Effect_Cfg_Data_Mgr::get_effect( cocos2d::Sprite * effect_sprite, const std::string& effect_id )
{
	cocos2d::Animation * animation = get_Animation(effect_id);
	if(!animation){
		return -1;
	}
	Json::Value& item_config = config_data_[effect_id];
	float scale = item_config["scale"].asFloat();
	float x = item_config["pos_x"].asFloat();
	float y = item_config["pos_y"].asFloat();
	float delay_time = item_config["delay_time"].asInt()/1000.f;
	bool loop = item_config["loop"].asInt()==1;

	effect_sprite->setScale(scale);
	effect_sprite->setPosition( Vec2(x,y));

	FiniteTimeAction* action;
	if(loop){
		action = CCRepeatForever::create( CCAnimate::create(animation) );
	}
	else{
		effect_sprite->setVisible(false);
		action = CCSequence::create
			(
			CCDelayTime::create(delay_time),
			CCShow::create(),
			CCAnimate::create(animation),
			CallFuncN::create(this, callfuncN_selector(Effect_Cfg_Data_Mgr::clean_effect)),
			NULL);
	}

	effect_sprite->runAction(action);
	return 0;
}

int Effect_Cfg_Data_Mgr::get_effect( cocos2d::Sprite * effect_sprite, Json::Value * effect_cfs, bool bflip)
{
	if((*effect_cfs).isNull() || (*effect_cfs).size() == 0){
		return -1;
	}
	for(int i = 0; i < (int)(*effect_cfs).size(); i++){
		Json::Value& effect_cfg_item = (*effect_cfs)[i];
		float action_delay = effect_cfg_item["delay"].asInt()/1000.f;
		const char *effect_id = effect_cfg_item["effect_id"].asCString();

		cocos2d::Animation * animation = get_Animation(effect_id);
		if(!animation){
			continue;
		}
		cocos2d::Sprite * child_effect = cocos2d::Sprite::create();
		Json::Value& item_config = config_data_[effect_id];
		float scale = item_config["scale"].asFloat();
		float x = item_config["pos_x"].asFloat();
		float y = item_config["pos_y"].asFloat();
		float delay_time = item_config["delay_time"].asInt()/1000.f;
		bool loop = item_config["loop"].asInt()==1;

		if (bflip)
		{
			x = -x;
			child_effect->setFlipX(true);
		}
		child_effect->setScale(scale);
		child_effect->setPosition( Vec2(x,y));
		child_effect->setVisible(false);
		FiniteTimeAction* action;
		if(loop){
			action = CCRepeatForever::create( CCAnimate::create(animation));
			child_effect->runAction(action);
			action = CCSequence::create(
				CCDelayTime::create(delay_time + action_delay),
				CCShow::create(),
				NULL
				);
		}
		else{
			action = CCSequence::create
				(
				CCDelayTime::create(delay_time + action_delay),
				CCShow::create(),
				CCAnimate::create(animation),
				CallFuncN::create(this, callfuncN_selector(Effect_Cfg_Data_Mgr::clean_effect)),
				NULL);
		}
		child_effect->runAction(action);
		effect_sprite->addChild(child_effect);
	}
	return 0;
}



cocos2d::Animation* Effect_Cfg_Data_Mgr::get_Animation( const std::string& effect_id )
{
	Json::Value& item_config = config_data_[effect_id];
	if(item_config.isNull()){
		return NULL;
	}

	cocos2d::AnimationCache* animationCache = cocos2d::AnimationCache::sharedAnimationCache();
	cocos2d::Animation * animation = animationCache->animationByName(effect_id.c_str());
	if(animation){
		return animation;
	}

	float duration_time = item_config["duration"].asInt()/1000.f;
	int count = item_config["count"].asInt();
	std::string effect_path= item_config["path"].asCString();
	char plist_file[80] = {0};
	char item_name[80] = {0};

	int pos = effect_path.find_first_of('/');
	std::string file_name = effect_path.substr(pos+1);

	sprintf(plist_file,("%s.%s"),effect_path.c_str(),"plist");

	SpriteFrameCache* cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(plist_file);

	//Array* frame_array = Array::create();

	Vector<SpriteFrame*> frame_array(count);
	for(int i = 1; i <= count; i++){
		sprintf(item_name,("%s_%d.%s"),file_name.c_str(),i,"png");
		SpriteFrame* f = cache->spriteFrameByName(item_name);
		frame_array.pushBack(f);
	}
	animation = cocos2d::Animation::createWithSpriteFrames(frame_array, duration_time/count);
	cocos2d::AnimationCache::sharedAnimationCache()->addAnimation(animation, effect_id.c_str());
	frame_array.clear();
	return animation;
}

void Effect_Cfg_Data_Mgr::clean_effect( Node * effect )
{
	effect->removeFromParentAndCleanup(true);
}

