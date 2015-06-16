#include "StageScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "TutorialScene.h"

#include "GameData.h"

Scene* StageScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StageScene::create();

	scene->addChild(layer);

	return scene;
}

bool StageScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *pBackground = Sprite::create("Images/Stage/Downtown_Background.png");
	pBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	this->addChild(pBackground);

	ui::Button *pHospital = ui::Button::create("Images/Stage/Hospital.png");
	pHospital->setPosition(Vec2(770.0f, visibleSize.height - 210.0f));
	pHospital->addClickEventListener(CC_CALLBACK_1(StageScene::menuClickEvent, this));
	pHospital->setTag(1);
	this->addChild(pHospital);

	ui::Button *pTown = ui::Button::create("Images/Stage/Town.png");
	pTown->setPosition(Vec2(137.0f, visibleSize.height - 502.0f));
	pTown->addClickEventListener(CC_CALLBACK_1(StageScene::menuClickEvent, this));
	pTown->setTag(2);
	this->addChild(pTown);

	ui::Button *pSubway = ui::Button::create("Images/Stage/Subway.png");
	pSubway->setPosition(Vec2(654.0f, visibleSize.height - 351.5f));
	pSubway->addClickEventListener(CC_CALLBACK_1(StageScene::menuClickEvent, this));
	pSubway->setTag(3);
	this->addChild(pSubway);

	ui::Button *pDaycareCenter = ui::Button::create("Images/Stage/Daycare_Center.png");
	pDaycareCenter->setPosition(Vec2(440.0f, visibleSize.height - 281.5f));
	pDaycareCenter->addClickEventListener(CC_CALLBACK_1(StageScene::menuClickEvent, this));
	pDaycareCenter->setTag(4);
	this->addChild(pDaycareCenter);

	ui::Button *pNursingHome = ui::Button::create("Images/Stage/Nursing_Home.png");
	pNursingHome->setPosition(Vec2(273.5f, visibleSize.height - 385.5f));
	pNursingHome->addClickEventListener(CC_CALLBACK_1(StageScene::menuClickEvent, this));
	pNursingHome->setTag(5);
	this->addChild(pNursingHome);

	ui::Button *pReturnButton = ui::Button::create("Images/Button_Return.png");
	pReturnButton->setPosition(Vec2(visibleSize.width - (pReturnButton->getContentSize().width / 2.0f), (pReturnButton->getContentSize().height / 2.0f)));
	pReturnButton->addClickEventListener(CC_CALLBACK_1(StageScene::menuClickEvent, this));
	pReturnButton->setTag(0);
	this->addChild(pReturnButton);

	if (!GameData::getInstance()->isStageOpen)
	{
		pTown->setEnabled(false);
		pTown->setBright(false);
		pSubway->setEnabled(false);
		pSubway->setBright(false);
		pDaycareCenter->setEnabled(false);
		pDaycareCenter->setBright(false);
		pNursingHome->setEnabled(false);
		pNursingHome->setBright(false);
	}

	return true;
}

void StageScene::menuClickEvent(Ref *pSender)
{
	ui::Button *pButton = (ui::Button*)pSender;
	int tag = pButton->getTag();

	switch (tag)
	{
	case 0:
		Director::getInstance()->replaceScene(CCTransitionFade::create(1.0f, TitleScene::createScene()));
		break;

	case 1:
		Director::getInstance()->replaceScene(CCTransitionTurnOffTiles::create(1.0f, TutorialScene::createScene()));
		break;

	default:
		if (tag <= 3)
			GameData::getInstance()->PersonType = 0;
		else
			GameData::getInstance()->PersonType = tag - 3;
		Director::getInstance()->replaceScene(CCTransitionTurnOffTiles::create(1.0f, GameScene::createScene()));
		break;
	}
}