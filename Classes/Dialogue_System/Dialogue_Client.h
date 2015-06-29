#ifndef _Dialogue_Client_H_
#define _Dialogue_Client_H_

#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "json/document.h"

namespace Game_Model
{
	struct Line
	{
		int dialogueId;
		int roleName;
		bool isFaceLeft;
		std::string content;

		int segmentId;

	};

	class DialogueData
	{
	public:
		DialogueData(){ _lines.clear(); };
		~DialogueData(){ _lines.clear(); };
	
		static DialogueData*	getInstance();
		bool initWithId(int id);

		Line& getLineByLevel(int level);

	private:
		void loadData(const rapidjson::Document& domt);
		std::vector<Line>          _lines;
	};

};
typedef Game_Model::DialogueData DIALOGUE_MODEL;

namespace Game_View
{
	class DialogueLayer : public cocos2d::Layer
	{
	public:
		DialogueLayer():_rootWidget(nullptr),_closeButton(nullptr),_touchCallback(nullptr){};
		~DialogueLayer(){_rootWidget=nullptr;_closeButton=nullptr;_touchCallback=nullptr;};
		void									onCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
// 		virtual void							onEnter() override;
// 		virtual void							onExit()  override;
		virtual bool							init()    override;
		CREATE_FUNC(DialogueLayer);
		void addListner(cocos2d::ui::Widget::ccWidgetTouchCallback callback);
		void setContentById(int id);
	protected:
	private:
		cocos2d::ui::Widget*						_rootWidget;
		cocos2d::ui::Button*						_closeButton;
		cocos2d::ui::Widget::ccWidgetTouchCallback	_touchCallback;

	};

};
typedef Game_View::DialogueLayer DIALOGUE_VIEW;

namespace Game_Net
{
	class DialogueMsg
	{
	public:
		DialogueMsg(){};
		~DialogueMsg(){};

	private:

	};

};

#endif