
#include "StartMenu.h"
#include "ui/CocosGUI.h"
#include "ChooseScene.h"
#include "../Network/Client.h"
#include "MainScene.h"

USING_NS_CC;
using namespace ui;

Scene* StartMenu::createScene()
{
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();
	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = StartMenu::create();
	// ��StartMenu����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);
	// ���س�������
	return scene;
}

bool StartMenu::init() {
	// ���ø����init����
	if (!Layer::init()) {
		return false;
	}
	// ����豸�ɼ���ͼ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();


	auto bg = Sprite::create("bg.jpg");
	bg->setScaleY(2);
	bg->setScaleX(3);
	this->addChild(bg);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	auto netButton = Button::create("netfight.png");
	this->addChild(netButton);
	netButton->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height * 0.9));
	netButton->setTouchEnabled(true);
	netButton->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			auto client = Client::create("0", 1);
			this->addChild(client);


			auto transition = TransitionFade::create(2.0, MainScene::createScene(client));
			Director::getInstance()->pushScene(transition);




		}
	});

	// ����ʼ��Ϸ����ť
	auto lanButton = Button::create("lanfight.png");
	this->addChild(lanButton);
	lanButton->setPosition(Vec2(
		visibleSize.width / 2,
		visibleSize.height * 0.7));
	lanButton->setTouchEnabled(true);
	lanButton->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// �л���PreLoad����
			auto transition = TransitionSlideInL::create(2.0, ChooseScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});

	// ����Ϸ���á���ť
	auto setButton = Button::create("settings.png");
	setButton->setTitleFontName("΢���ź�");
	setButton->setTitleFontSize(12);
	setButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.5));
	setButton->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// �л���AudioControl����
			
		}
	});
	this->addChild(setButton);

	// ���˳���Ϸ����ť
	auto closeButton = Button::create("quit.png");
	closeButton->setTitleFontName("΢���ź�");
	closeButton->setTitleFontSize(12);
	closeButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.3));
	closeButton->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
			return;
#endif
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif

		}
	});
	this->addChild(closeButton);

	return true;
}












