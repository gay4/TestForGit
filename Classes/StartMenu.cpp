
#include "StartMenu.h"
#include "ui/CocosGUI.h"
#include "ChooseScene.h"

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


	auto bg = Sprite::create("bg.png");
	bg->setScaleY(2);
	bg->setScaleX(3);
	this->addChild(bg);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	// ����ʼ��Ϸ����ť
	auto startButton = Button::create("button.png");
	startButton->setScale(2.2);
	startButton->setTitleText("Start");
	startButton->setTitleFontName("΢���ź�");
	startButton->setTitleFontSize(12);
	startButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.8));
	startButton->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// �л���PreLoad����
			auto transition = TransitionSlideInL::create(2.0, ChooseScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(startButton);

	// ����Ϸ���á���ť
	auto setButton = Button::create("button.png");
	setButton->setScale(2.2);
	setButton->setTitleText("Settings");
	setButton->setTitleFontName("΢���ź�");
	setButton->setTitleFontSize(12);
	setButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.55));
	setButton->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			// �л���AudioControl����
			
		}
	});
	this->addChild(setButton);

	// ���˳���Ϸ����ť
	auto closeButton = Button::create("button.png");
	closeButton->setScale(2.2);
	closeButton->setTitleText("Quit");
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












