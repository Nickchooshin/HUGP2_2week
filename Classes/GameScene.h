#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void pressButtonClickEvent(Ref *pSender);
	void returnMenuClickEvent(Ref *pSender);
};

#endif