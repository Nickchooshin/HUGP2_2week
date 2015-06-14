#include "TrophyScene.h"
#include "TitleScene.h"

Scene* TrophyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TrophyScene::create();

	scene->addChild(layer);

	return scene;
}

bool TrophyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *pBackground = Sprite::create("Images/Trophy/Trophy_Background.png");
	pBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(pBackground);

	ui::Button *pReturnButton = ui::Button::create("Images/Button_Return.png");
	pReturnButton->setPosition(Vec2(visibleSize.width - (pReturnButton->getContentSize().width / 2.0f), (pReturnButton->getContentSize().height / 2.0f)));
	pReturnButton->addClickEventListener(CC_CALLBACK_1(TrophyScene::menuClickEvent, this));
	this->addChild(pReturnButton);

	return true;
}

void TrophyScene::menuClickEvent(Ref *pSender)
{
	Director::getInstance()->replaceScene(CCTransitionSlideInL::create(1.0f, TitleScene::createScene()));
}