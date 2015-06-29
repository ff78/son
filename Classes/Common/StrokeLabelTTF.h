#ifndef __STROKELABELTTF_H__
#define __STROKELABELTTF_H__
 
#include "cocos2d.h"
using namespace cocos2d;

class StrokeLabelTTF : public cocos2d::Node
{
public:
	StrokeLabelTTF();
	~StrokeLabelTTF();

public:
	static StrokeLabelTTF* create(const char *string, const char *fontName, float fontSize, float strokeSize,const cocos2d::Color3B&      colStroke = cocos2d::ccc3(0, 0, 0), cocos2d::CCTextAlignment hAlignment=cocos2d::kCCTextAlignmentCenter, cocos2d::CCVerticalTextAlignment vAlignment=cocos2d::kCCVerticalTextAlignmentTop);
	bool initWithString(const char *label, const char *fontName, float fontSize, float fStrokeSize, const cocos2d::Color3B&      colStroke, cocos2d::CCTextAlignment hAlignment, cocos2d::CCVerticalTextAlignment vAlignment);

	static StrokeLabelTTF * create(const char *string, const char *fontName, float fontSize);

public:
	void setColor(const cocos2d::Color3B& color3);
	void setString(const char *label);
	void setStrokeColor(cocos2d::Color3B col){ m_colStroke = col; updateStroke(); }
	void setStrokeSize(float StrokeSize){ m_fStrokeSize = StrokeSize; updateStroke();}
	void setAnchorPoint(const cocos2d::Point &anchorPoint);


protected:
	void updateStroke();

private:
	float                   m_fStrokeSize;
	cocos2d::Color3B      m_colStroke;
	cocos2d::Sprite*      m_sprite;
	cocos2d::LabelTTF*    m_label;
	Point anchorPoint;
};

#endif /* __STROKELABELTTF_H__ */
