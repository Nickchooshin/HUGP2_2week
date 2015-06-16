#ifndef __TUTORIAL_SCENE_H__
#define __TUTORIAL_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

class TutorialScene : public cocos2d::Layer
{
private:
	Sprite *m_pTutorial[6];
	int num;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TutorialScene);

	void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);
};

#endif