#ifndef MESSAGE_LAYER_H
#define MESSAGE_LAYER_H

#include "cocos2d.h"
#include <queue>
#include <string>
#include "ui/CocosGUI.h"
#include "Common/Utils.h"
USING_NS_CC;
using namespace ui;
USING_NS_CC;

#define MOVE_SPEED          150.f
#define SHOW_ALERT_TIME     2.f
#define SHOW_ALERT_FADE_IN_TIME 0.5f
#define SHOW_ALERT_DELAY_TIME 1.f

#define ALERT_FONT_SIZE     28
#define ALERT_LABEL_POS_Y   630.f
#define ALERT_LABEL_COLOR   ccc3(251,152,0)

#define MSG_FONT_SIZE       25
#define MSG_LABEL_POS_Y     560.f
#define MSG_LABEL_COLOR     ccc3(255, 0, 0)

namespace UI
{
  class Message_Layer : public Layer
  {
  public:
	  CREATE_FUNC(Message_Layer);
	  Message_Layer();
	  bool init();
	  void add_message(const char *msg);
	  void show_alert(const char *msg);
	  ~Message_Layer();
  private:
	  void show_message();
	  void do_next();
  private:
	  std::queue<std::string> message_queue_;
	  LabelTTF * message_label_;
	  LabelTTF * alert_label_;
	  cocos2d::Sprite*		backgroundimage;

	  cocos2d::Sprite*		m_pubulic_notice_back;
  };
};



#endif /* MESSAGE_LAYER_H */
