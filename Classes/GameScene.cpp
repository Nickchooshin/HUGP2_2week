#include "GameScene.h"
#include "StageScene.h"

#include "GameData.h"
#include "UIPopupWindow.h"

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

	this->setTouchEnabled(true);
	//this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	//this->setSwallowsTouches(true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *pBackground = Sprite::create("Images/blank.png", Rect(0.0f, 0.0f, visibleSize.width, visibleSize.height));
	pBackground->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	pBackground->setColor(Color3B(204, 204, 204));
	this->addChild(pBackground);

	// Person
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

	// Cursor
	m_pCursor = ui::ImageView::create("Images/Game/Cursor.png");
	m_pCursor->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->addChild(m_pCursor);

	// Press Gauge
	ui::ImageView *pGaugeBarFrame = ui::ImageView::create("Images/Game/Gauge_Bar_Frame.png");
	pGaugeBarFrame->setPosition(Vec2(visibleSize.width - ((pGaugeBarFrame->getContentSize().width / 2.0f) + 15.0f), (visibleSize.height / 2.0f) + 47.0f));
	this->addChild(pGaugeBarFrame);

	ui::ImageView *pGaugeBar = ui::ImageView::create("Images/Game/Gauge_Bar.png");
	pGaugeBar->setPosition(Vec2(pGaugeBarFrame->getContentSize().width / 2.0f, pGaugeBarFrame->getContentSize().height / 2.0f));
	pGaugeBarFrame->addChild(pGaugeBar);

	m_pGaugeBarMask = ui::LoadingBar::create("Images/Game/Gauge_Bar_Mask2.png", 100.0f);
	m_pGaugeBarMask->setPosition(pGaugeBar->getPosition());
	m_pGaugeBarMask->setRotation(90.0f);
	pGaugeBarFrame->addChild(m_pGaugeBarMask);

	ui::Button *pPressButton = ui::Button::create("Images/Game/Button_Press.png");
	pPressButton->setPosition(Vec2(visibleSize.width - ((pPressButton->getContentSize().width / 2.0f) + 15.0f), (pPressButton->getContentSize().height / 2.0f) + 15.0f));
	pPressButton->addClickEventListener(CC_CALLBACK_1(GameScene::pressButtonClickEvent, this));
	this->addChild(pPressButton);

	// Time Gauge
	ui::ImageView *pTimeGaugeBarFrame = ui::ImageView::create("Images/Game/TimeGauge_Bar_Frame.png");
	pTimeGaugeBarFrame->setPosition(Vec2(458.5f, visibleSize.height - ((pTimeGaugeBarFrame->getContentSize().height / 2.0f) + 10.0f)));
	this->addChild(pTimeGaugeBarFrame);

	m_pTimeGauge = ui::LoadingBar::create("Images/Game/TimeGauge_Bar.png", 100.0f);
	m_pTimeGauge->setPosition(Vec2(pTimeGaugeBarFrame->getContentSize().width / 2.0f, pTimeGaugeBarFrame->getContentSize().height / 2.0f));
	pTimeGaugeBarFrame->addChild(m_pTimeGauge, -1);

	this->schedule(schedule_selector(GameScene::updateTimer));

	// Health Gauge
	ui::ImageView *pHealthGaugeBarFrame = ui::ImageView::create("Images/Game/HealthGauge_Bar_Frame.png");
	pHealthGaugeBarFrame->setPosition(Vec2(458.5f, pTimeGaugeBarFrame->getPosition().y - ((pTimeGaugeBarFrame->getContentSize().height / 2.0f) + (pHealthGaugeBarFrame->getContentSize().height / 2.0f) + 10.0f)));
	this->addChild(pHealthGaugeBarFrame);

	m_pHealthGauge = ui::LoadingBar::create("Images/Game/HealthGauge_Bar.png", 0.0f);
	m_pHealthGauge->setPosition(Vec2(pHealthGaugeBarFrame->getContentSize().width / 2.0f, pHealthGaugeBarFrame->getContentSize().height / 2.0f));
	pHealthGaugeBarFrame->addChild(m_pHealthGauge, -1);

	m_bTryPress = false;
	m_fPercent = 100.0f;
	m_fSign = -1.0f;

	//FileUtils::sharedFileUtils()->getFileData("Data/Man_BodyParts.dat", "r", );

	std::string fullPath = FileUtils::sharedFileUtils()->fullPathForFilename("Data/Man_BodyParts.dat");
	unsigned char *pBuffer = NULL;
	long bufferSize = 0;
	pBuffer = FileUtils::sharedFileUtils()->getFileData(fullPath.c_str(), "r", &bufferSize);

	char *ptr = strtok((char*)pBuffer, ",| ");
	while (ptr)
	{
		float x, y;
		float a, b;
		int type;

		x = atof(ptr);
		ptr = strtok(NULL, ",| \r\n");
		y = atof(ptr);
		ptr = strtok(NULL, ",| \r\n");
		a = atof(ptr);
		ptr = strtok(NULL, ",| \r\n");
		b = atof(ptr);
		ptr = strtok(NULL, ",| \r\n");
		type = atoi(ptr);
		ptr = strtok(NULL, ",| \r\n");

		m_BodyParts.push_back(BodyPart(x, y, a, b, type));
	}
	free(pBuffer);

	// Return Button
	ui::Button *pReturnButton = ui::Button::create("Images/Button_Return.png");
	pReturnButton->setPosition(Vec2((pReturnButton->getContentSize().width / 2.0f), (pReturnButton->getContentSize().height / 2.0f)));
	pReturnButton->addClickEventListener(CC_CALLBACK_1(GameScene::returnMenuClickEvent, this));
	this->addChild(pReturnButton);

	return true;
}

void GameScene::updateGaugeBar(float dt)
{
	m_fPercent += (100.0f * m_fSign) * dt;
	if (m_fPercent <= 0.0f)
	{
		m_fPercent = -m_fPercent;
		m_fSign = 1.0f;
	}
	else if (m_fPercent >= 100.0f)
	{
		m_fPercent = 100.0f;
		m_fSign = -1.0f;
		m_bTryPress = false;

		this->unschedule(schedule_selector(GameScene::updateGaugeBar));
	}

	m_pGaugeBarMask->setPercent(m_fPercent);
}

void GameScene::updateCursorScale(float dt)
{
	m_pCursor->setScale(1.0f);

	this->unschedule(schedule_selector(GameScene::updateCursorScale));
}

void GameScene::updateTimer(float dt)
{
	float percent = m_pTimeGauge->getPercent();

	percent -= 100.0f * (dt / 180.0f);
	m_pTimeGauge->setPercent(percent);

	if (percent <= 0.0f)
		ShowPopup();
}

void GameScene::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	Touch *touch = *touches.begin();
	Vec2 position = touch->getLocation();

	m_pCursor->setPosition(position);
}

void GameScene::pressButtonClickEvent(Ref *pSender)
{
	if (!m_bTryPress)
	{
		m_bTryPress = true;

		this->schedule(schedule_selector(GameScene::updateGaugeBar));
	}
	else
	{
		// Hit Test
		int type = HitTest();

		if (type == 0)
		{
			float healthPercent = m_pHealthGauge->getPercent();
			healthPercent += ((100.0f - m_fPercent) / 24.0f);
			m_pHealthGauge->setPercent(healthPercent);

			if (healthPercent >= 100.0f)
				ShowPopup();
		}

		m_pGaugeBarMask->setPercent(100.0f);
		m_fPercent = 100.0f;
		m_fSign = -1.0f;
		m_bTryPress = false;

		m_pCursor->setScale(1.5f);
		this->schedule(schedule_selector(GameScene::updateCursorScale), 0.1f);

		this->unschedule(schedule_selector(GameScene::updateGaugeBar));
	}
}

void GameScene::returnMenuClickEvent(Ref *pSender)
{
	Director::getInstance()->replaceScene(CCTransitionTurnOffTiles::create(1.0f, StageScene::createScene()));
}

void GameScene::menuCallback(Ref *pSender)
{
	UIPopupWindow *pPopup = (UIPopupWindow*)pSender;
	int tag = pPopup->getResult();

	switch (tag)
	{
	case 1:
		Director::getInstance()->replaceScene(CCTransitionTurnOffTiles::create(1.0f, GameScene::createScene()));
		break;

	case 2:
		Director::getInstance()->replaceScene(CCTransitionTurnOffTiles::create(1.0f, StageScene::createScene()));
		break;
	}
}

int GameScene::HitTest()
{
	auto iter_end = m_BodyParts.end();
	Vec2 position = m_pCursor->getPosition();

	for (auto iter = m_BodyParts.begin(); iter != iter_end; iter++)
	{
		BodyPart bodyParts = *iter;
		float x = bodyParts._x - position.x;
		float y = bodyParts._y - position.y;
		float temp = (pow(x, 2.0f) / pow(bodyParts._a, 2.0f)) + (pow(y, 2.0f) / pow(bodyParts._b, 2.0f));

		if (temp <= 1.0f)
			return bodyParts._type;
	}

	return -1;
}

void GameScene::ShowPopup()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Menu Popup
	m_pMenuPopup = UIPopupWindow::create(NULL, NULL);
	m_pMenuPopup->setBackgroundBorard(Sprite::create("Images/PopupFrame.png"));
	m_pMenuPopup->setCallBackFunc(CC_CALLBACK_1(GameScene::menuCallback, this));
	m_pMenuPopup->addButton("Images/Button_Return.png", "Images/Button_Return.png", "", ui::Widget::TextureResType::LOCAL, Point((visibleSize.width / 2.0f) - 48.0f, (visibleSize.height / 2.0f) - 150.0f), "", 1);
	m_pMenuPopup->addButton("Images/Button_Menu.png", "Images/Button_Menu.png", "", ui::Widget::TextureResType::LOCAL, Point((visibleSize.width / 2.0f) + 48.0f, (visibleSize.height / 2.0f) - 150.0f), "", 2);

	Sprite *pSprite;

	if (m_pTimeGauge->getPercent() <= 0.0f)
		pSprite = Sprite::create("Images/Text_Died.png");
	else if (m_pHealthGauge->getPercent() >= 100.0f)
		pSprite = Sprite::create("Images/Text_Save.png");
	pSprite->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
	m_pMenuPopup->addChild(pSprite);

	m_pMenuPopup->showPopup(this);
}