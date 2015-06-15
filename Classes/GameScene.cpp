#include "GameScene.h"
#include "StageScene.h"

#include "GameData.h"

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *pBackground = Sprite::create("Images/blank.png", Rect(0.0f, 0.0f, visibleSize.width, visibleSize.height));
	pBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	pBackground->setColor(Color3B(204, 204, 204));
	this->addChild(pBackground);

	Sprite *pPerson;

	switch (GameData::getInstance()->PersonType)
	{
	case 0 :
		pPerson = Sprite::create("Images/Game/Man.png");
		break;

	case 1:
		pPerson = Sprite::create("Images/Game/Child.png");
		break;

	case 2:
		pPerson = Sprite::create("Images/Game/OldMan.png");
		break;
	}

	pPerson->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(pPerson);

	ui::ImageView *pGaugeBarFrame = ui::ImageView::create("Images/Game/Gauge_Bar_Frame.png");
	pGaugeBarFrame->setPosition(Vec2(visibleSize.width - ((pGaugeBarFrame->getContentSize().width / 2.0f) + 15.0f), (visibleSize.height / 2.0f) + 47.0f));
	this->addChild(pGaugeBarFrame);

	ui::ImageView *pGaugeBar = ui::ImageView::create("Images/Game/Gauge_Bar.png");
	pGaugeBar->setPosition(Vec2(pGaugeBarFrame->getContentSize().width / 2.0f, pGaugeBarFrame->getContentSize().height / 2.0f));
	pGaugeBarFrame->addChild(pGaugeBar);

	ui::LoadingBar *pGaugeBarMask = ui::LoadingBar::create("Images/Game/Gauge_Bar_Mask.png", 100.0f);
	pGaugeBarMask->setPosition(pGaugeBar->getPosition());
	pGaugeBarFrame->addChild(pGaugeBarMask);

	ui::Button *pPressButton = ui::Button::create("Images/Game/Button_Press.png");
	pPressButton->setPosition(Vec2(visibleSize.width - ((pPressButton->getContentSize().width / 2.0f) + 15.0f), (pPressButton->getContentSize().height / 2.0f) + 15.0f));
	pPressButton->addClickEventListener(CC_CALLBACK_1(GameScene::pressButtonClickEvent, this));
	this->addChild(pPressButton);

	ui::Button *pReturnButton = ui::Button::create("Images/Button_Return.png");
	pReturnButton->setPosition(Vec2((pReturnButton->getContentSize().width / 2.0f), visibleSize.height - (pReturnButton->getContentSize().height / 2.0f)));
	pReturnButton->addClickEventListener(CC_CALLBACK_1(GameScene::returnMenuClickEvent, this));
	this->addChild(pReturnButton);

	return true;
}

void GameScene::pressButtonClickEvent(Ref *pSender)
{
}

void GameScene::returnMenuClickEvent(Ref *pSender)
{
	Director::getInstance()->replaceScene(CCTransitionTurnOffTiles::create(1.0f, StageScene::createScene()));
}