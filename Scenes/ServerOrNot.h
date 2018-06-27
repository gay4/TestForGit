#pragma once

/*������ģʽ��ѡ����Ϸģʽ���ͻ���->�л�������ip�ĳ���
											�����->�л��������ĳ�������*/

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "RoomScene.h"
#include "WaitingScene.h"
#include "NameScene.h"

USING_NS_CC;
using namespace ui;

class ServerOrNot :public Scene {
public:
	CREATE_FUNC(ServerOrNot);

private:
	bool init()override
	{
		if (!Scene::init())
		{
			return false;
		}
		auto visibleSize = Director::getInstance()->getVisibleSize();

		auto background = Sprite::create("scene/serverornot.jpg");
		this->addChild(background);
		background->setAnchorPoint(cocos2d::Vec2::ZERO);

		// ��Ϊ���������
		auto clientButton = cocos2d::ui::Button::create("scene/asserver.png");
		clientButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height*0.3));
		clientButton->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
				auto transiton = TransitionSlideInL::create(2.f, NameScene::create());
				Director::getInstance()->replaceScene(transiton);
			}
		});

		this->addChild(clientButton);

		//��Ϊ�ͻ�������
		auto serverButton = cocos2d::ui::Button::create("scene/asclient.png");
		serverButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height*0.7));
		serverButton->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
				auto transiton = TransitionSlideInL::create(2.f, WaitingScene::create());
				Director::getInstance()->replaceScene(transiton);
			}
		});

		this->addChild(serverButton);

		return true;
	}//init

};