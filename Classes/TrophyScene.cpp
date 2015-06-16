#include "TrophyScene.h"
#include "TitleScene.h"

#include "UIPopupWindow.h"

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

	UIPopupWindow *pPopupOK = UIPopupWindow::create(NULL, Sprite::create("HelloWorld.png"));
	pPopupOK->setBackgroundBorard(Sprite::create("CloseSelected.png")); // 불투명 배경?
	//UIPopupWindow *pPopupOK = UIPopupWindow::create(Sprite::create("CloseSelected.png"), Sprite::create("HelloWorld.png"));

	pPopupOK->setCallBackFunc(CC_CALLBACK_1(TrophyScene::menuClickEvent, this));

	pPopupOK->addButton("Images/Button_Return.png", "Images/Button_Return.png", "", ui::Widget::TextureResType::LOCAL, Point(0, -112), "", 1);
	pPopupOK->setMessageString("하하");
	pPopupOK->showPopup(this);

	return true;
}

void TrophyScene::menuClickEvent(Ref *pSender)
{
	Director::getInstance()->replaceScene(CCTransitionSlideInL::create(1.0f, TitleScene::createScene()));
}