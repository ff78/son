#include "StrokeLabelTTF.h"
USING_NS_CC;
StrokeLabelTTF::StrokeLabelTTF()
	:m_colStroke(ccc3(0,0,0))
	,m_fStrokeSize(1.0f)
	,m_sprite(NULL)
	,m_label(NULL)
	,anchorPoint(0.5,0.5)
{}
StrokeLabelTTF::~StrokeLabelTTF()
{
	CC_SAFE_RELEASE_NULL(m_label);
}
bool StrokeLabelTTF::initWithString(const char *string, const char *fontName, float fontSize, float strokeSize,const cocos2d::Color3B& colStroke, CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment)
{
	m_fStrokeSize = strokeSize;
	m_colStroke = colStroke;
	m_label = LabelTTF::create(string, fontName, fontSize, CCSizeZero,hAlignment,vAlignment);
	m_label->retain();

	updateStroke();

	return true;
}
StrokeLabelTTF* StrokeLabelTTF::create(const char *string, const char *fontName, float fontSize, float fStrokeSize,const cocos2d::Color3B& colStroke ,CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment)
{
	StrokeLabelTTF *pRet = new StrokeLabelTTF();
	if(pRet && pRet->initWithString(string, fontName, fontSize, fStrokeSize, colStroke, hAlignment, vAlignment))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

StrokeLabelTTF * StrokeLabelTTF::create(const char *string, const char *fontName, float fontSize)
{
	StrokeLabelTTF *pRet = new StrokeLabelTTF();

	if(pRet && pRet->initWithString(string,fontName,fontSize,1,ccc3(0,0,0),kCCTextAlignmentCenter,kCCVerticalTextAlignmentTop))
	{
		pRet->autorelease();
		return pRet;
	}

	CC_SAFE_DELETE(pRet);
	return NULL;

}

void StrokeLabelTTF::updateStroke()
{
	if (m_sprite)
	{
		removeChild(m_sprite, true);
	}

	cocos2d::Size textureSize = m_label->getContentSize();
	textureSize.width += 2 * m_fStrokeSize;
	textureSize.height += 2 * m_fStrokeSize;
	//call to clear error
	glGetError();
	CCRenderTexture *rt = CCRenderTexture::create((int)textureSize.width, (int)textureSize.height);
	if(!rt)
	{
		CCLOG("create render texture failed !!!!");
		addChild(m_label);
		return;
	}

	Color3B col = m_label->getColor();
	m_label->setColor(m_colStroke);

	ccBlendFunc originalBlend = m_label->getBlendFunc();
	//ccBlendFunc func = { GL_SRC_ALPHA, GL_ONE};
	ccBlendFunc func = { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
	m_label->setBlendFunc(func);

	m_label->setAnchorPoint(Vec2(0.5f,0.5f));

	rt->begin();
	for(int i = 0; i < 360; i += 15)
	{
		float r = CC_DEGREES_TO_RADIANS(i);
		m_label->setPosition(Vec2(
			textureSize.width * 0.5f + sin(r) * m_fStrokeSize,
			textureSize.height * 0.5f + cos(r) * m_fStrokeSize));
		//m_label->visit();
	}

	m_label->setColor(col);
	m_label->setBlendFunc(originalBlend);
	m_label->setPosition(Vec2(textureSize.width * 0.5f, textureSize.height * 0.5f));
	//m_label->visit();
	rt->end();

	CCTexture2D *texture = rt->getSprite()->getTexture();
	texture->setAliasTexParameters();
	m_sprite = cocos2d::Sprite::createWithTexture(rt->getSprite()->getTexture());
	setContentSize(m_sprite->getContentSize());
	m_sprite->setAnchorPoint(this->anchorPoint);//------------
	m_sprite->setPosition(Vec2(0, 0));
	((cocos2d::Sprite *)m_sprite)->setFlipY(true);
	addChild(m_sprite);
}
void StrokeLabelTTF::setString(const char *label)
{
	if (m_label)
	{

		if(0!=strcmp(label, m_label->getString().c_str()))

		{
			m_label->setString(label);
			updateStroke();
		}
	}
	else
	{
		CCLOG("ERROR:CCLabelTTFStroke::setString m_label=NULL");
	}
}
void StrokeLabelTTF::setColor(const Color3B& color3)
{
	if (m_label)
	{
		Color3B col = m_label->getColor();
		if(color3.r!=col.r || color3.g!=col.g || color3.b!=col.b)
		{
			m_label->setColor(color3);
			updateStroke();
		}
	}
	else
	{
		CCLOG("ERROR:CCLabelTTFStroke::setColor m_label=NULL");
	}
}

void StrokeLabelTTF::setAnchorPoint(const cocos2d::Point &anchorPoint1)
{

	this->anchorPoint=anchorPoint1;
	updateStroke();
}