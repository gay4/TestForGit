
#include "ChooseScene.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "cocos2d.h"
#include "../Network/Client.h"

using namespace ui;
//using namespace CocosDenshion;

#include <string>

USING_NS_CC;


Scene* ChooseScene::createScene()
{
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();
	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = ChooseScene::create();
	// ��ChooseScene����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);
	// ���س�������
	return scene;
}

bool ChooseScene::init() {
	// ���ø����init����
	if (!Layer::init()) {
		return false;
	}
	// ����豸�ɼ���ͼ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();


	auto bg = Sprite::create("bg.png");
	bg->setScaleY(2);
	bg->setScaleX(3);
	this->addChild(bg);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	auto nameBackGroud = Sprite::create("NameInput.png");
	nameBackGroud->setScale(2);
	this->addChild(nameBackGroud);
	nameBackGroud->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 10));


	_chatWindow = cocos2d::ui::TextField::create("  ", "Arial", 10);
	this->addChild(_chatWindow, 2);
	_chatWindow->setPosition(Vec2(visibleSize.width / 2 ,visibleSize.height / 2));
	_chatWindow->setMaxLengthEnabled(true);
	_chatWindow->setMaxLength(20);
	_chatWindow->setTouchSize(Size(200, 60));
	_chatWindow->setTouchAreaEnabled(true);
	_chatWindow->setScale(1.6);
	
	_chatWindow->addEventListener(CC_CALLBACK_2(ChooseScene::textFieldEvent, this));

	


	auto startButton = Button::create("ButtonStart.png");
	this->addChild(startButton);
	startButton->setPosition(Vec2(
		visibleSize.width / 2,
		(visibleSize.height - 90) / 2));
	startButton->setTouchEnabled(true);
	startButton->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			
			_ip = _chatWindow->getString();
			auto client = Client::create(_ip);
			//this->addChild(client);

			auto transition = TransitionFade::create(2.0, MainScene::createScene(client));
			Director::getInstance()->replaceScene(transition);

		


		}
	});
	
	auto inputBar = Sprite::create("InputBar.png");
	inputBar->setPosition(Point(visibleSize.width / 2,
		(visibleSize.height) / 2));
	inputBar->setScale(1.2);
	this->addChild(inputBar, 1);
	

	return true;
}

void ChooseScene::textFieldEvent(Ref *pSender, cocos2d::ui::TextField::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
	{
		cocos2d::ui::TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);
		Size screenSize = CCDirector::getInstance()->getWinSize();


	}
	break;

	case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
	{
		cocos2d::ui::TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);


	}
	break;

	case cocos2d::ui::TextField::EventType::INSERT_TEXT:
	{
		TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);


	}
	break;

	case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
	{
		TextField* textField = dynamic_cast<cocos2d::ui::TextField*>(pSender);


	}
	break;

	default:
		break;
	}
}











