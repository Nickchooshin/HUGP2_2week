#include "TutorialScene.h"
#include "StageScene.h"

#include "GameData.h"

Scene* TutorialScene::createScene()
{
	auto scene = Scene::create();

	auto layer = TutorialScene::create();

	scene->addChild(layer);

	return scene;
}

bool TutorialScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->setTouchEnabled(true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	char filepath[100];
	for (int i = 0; i < 6; i++)
	{
		sprintf_s(filepath, "Images/Tutorial/Tutorial_%d.png", i + 1);
		m_pTutorial[i] = Sprite::create(filepath);
		m_pTutorial[i]->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
		m_pTutorial[i]->setVisible(false);
		this->addChild(m_pTutorial[i]);
	}

	num = 0;
	m_pTutorial[0]->setVisible(true);

	return true;
}

void TutorialScene::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	if (num < 5)
	{
		m_pTutorial[num++]->setVisible(false);
		m_pTutorial[num]->setVisible(true);
	}
	else
	{
		GameData::getInstance()->isStageOpen = 1;
		GameData::getInstance()->saveData();

		Director::getInstance()->replaceScene(CCTransitionTurnOffTiles::create(1.0f, StageScene::createScene()));
	}
}