#include "TitleScene.h"
#include "StageScene.h"
#include "TrophyScene.h"

Scene* TitleScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TitleScene::create();

	scene->addChild(layer);

	return scene;
}

bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *pBackground = Sprite::create("Images/Title/Title_Background.png");
	pBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(pBackground);

	ui::ImageView *pMenuFrame = ui::ImageView::create("Images/Title/Title_Menu.png");
	pMenuFrame->setPosition(Vec2(731.0f, visibleSize.height - 389.5f));
	this->addChild(pMenuFrame);

	ui::Button *pStartButton = ui::Button::create("Images/Title/Button_Start.png");
	pStartButton->setPosition(Vec2(731.0f, visibleSize.height - 264.0f));
	pStartButton->addClickEventListener(CC_CALLBACK_1(TitleScene::menuClickEvent, this));
	pStartButton->setTag(0);
	this->addChild(pStartButton);

	ui::Button *pTrophyButton = ui::Button::create("Images/Title/Button_Trophy.png");
	pTrophyButton->setPosition(Vec2(734.0f, visibleSize.height - 391.0f));
	pTrophyButton->addClickEventListener(CC_CALLBACK_1(TitleScene::menuClickEvent, this));
	pTrophyButton->setTag(1);
	this->addChild(pTrophyButton);

	ui::Button *pCreditButton = ui::Button::create("Images/Title/Button_Credit.png");
	pCreditButton->setPosition(Vec2(737.0f, visibleSize.height - 515.0f));
	pCreditButton->addClickEventListener(CC_CALLBACK_1(TitleScene::menuClickEvent, this));
	pCreditButton->setTag(2);
	this->addChild(pCreditButton);

	return true;
}

void TitleScene::menuClickEvent(Ref *pSender)
{
	ui::Button *pButton = (ui::Button*)pSender;
	int tag = pButton->getTag();

	switch (tag)
	{
	case 0:
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, StageScene::createScene()));
		break;

	case 1:
		Director::getInstance()->replaceScene(CCTransitionSlideInR::create(1.0f, TrophyScene::createScene()));
		break;

	case 2:
		break;
	}
}