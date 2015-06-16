#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"

#include "UIPopupWindow.h"

USING_NS_CC;

struct BodyPart
{
	float _x, _y;
	float _a, _b;
	int _type;

	BodyPart() : _x(0.0f), _y(0.0f), _a(0.0f), _b(0.0f), _type(0) {}
	BodyPart(float x, float y, float a, float b, int type) : _x(x), _y(y), _a(a), _b(b), _type(type) {}
};

class GameScene : public cocos2d::Layer
{
private :
	ui::ImageView *m_pCursor;
	ui::LoadingBar *m_pGaugeBarMask;
	ui::LoadingBar *m_pTimeGauge, *m_pHealthGauge;

	UIPopupWindow *m_pMenuPopup;

	std::vector<BodyPart> m_BodyParts;

	bool m_bTryPress;
	int m_fPercent, m_fSign;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameScene);

	void updateGaugeBar(float dt);
	void updateCursorScale(float dt);
	void updateTimer(float dt);

	//void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);

	void pressButtonClickEvent(Ref *pSender);
	void returnMenuClickEvent(Ref *pSender);
	void menuCallback(Ref *pSender);

	int HitTest();
	void ShowPopup();
};

#endif