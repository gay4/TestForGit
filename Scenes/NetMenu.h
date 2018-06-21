#pragma once

/*NetMenu�ǿ�ʼ�˵��࣬�����������ѡ
���������ս�ͻ�������ս*/

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ServerOrNot.h"

//USING_NS_CC;
//using namespace cocos2d::ui;

class NetMenu :public cocos2d::Scene {
public:
	CREATE_FUNC(NetMenu);

private:
	

	bool init()override
	{
		if (!Scene::init())
		{
			return false;
		}
		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
		//����
		auto background = cocos2d::Sprite::create("scene/bg.jpg");
		assert(background != nullptr);

		//background->setScaleX(2);
		//background->setScaleY(3);
		this->addChild(background);
		background->setAnchorPoint(cocos2d::Vec2::ZERO);

		//������
		auto netButton = cocos2d::ui::Button::create("scene/netfight.png");
		this->addChild(netButton);
		netButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height * 0.9));
		netButton->setTouchEnabled(true);

		netButton->addTouchEventListener([&](Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {

			if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {

			}
		});

		// ������
		auto lanButton = cocos2d::ui::Button::create("scene/lanfight.png");
		this->addChild(lanButton);
		lanButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height * 0.7));
		lanButton->setTouchEnabled(true);

		lanButton->addTouchEventListener([&](Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
				auto transiton = TransitionSlideInL::create(2.f, ServerOrNot::create());
				Director::getInstance()->replaceScene(transiton);
			}
		});


		// ����Ϸ���á���ť
		auto setButton = cocos2d::ui::Button::create("scene/settings.png");
		setButton->setTitleFontName("΢���ź�");
		setButton->setTitleFontSize(12);
		setButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height*0.5));
		setButton->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
				// �л���AudioControl����
			}
		});

		this->addChild(setButton);


		// ���˳���Ϸ����ť
		auto closeButton = cocos2d::ui::Button::create("scene/quit.png");
		closeButton->setTitleFontName("΢���ź�");
		closeButton->setTitleFontSize(12);
		closeButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height*0.3));

		closeButton->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
				MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
				return;
#endif
				cocos2d::Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
#endif
			}
		});
		this->addChild(closeButton);

		return true;
	}//init

};
