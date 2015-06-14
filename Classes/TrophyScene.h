#ifndef __TROPHY_SCENE_H__
#define __TROPHY_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

class TrophyScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TrophyScene);

	void menuClickEvent(Ref *pSender);
};

#endif