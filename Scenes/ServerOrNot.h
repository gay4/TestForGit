#pragma once

/*������ģʽ��ѡ����Ϸģʽ���ͻ���->�л�������ip�ĳ���
											�����->�л��������ĳ�������*/

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "RoomScene.h"

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

		// ��Ϊ���������
		auto clientButton = cocos2d::ui::Button::create("picture/MenuItems/ButtonStartAsServer.png");
		clientButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height*0.3));
		clientButton->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
				auto transiton = TransitionSlideInL::create(2.f, RoomScene::create());
				Director::getInstance()->replaceScene(transiton);
			}
		});

		this->addChild(clientButton);

		//��Ϊ�ͻ�������
		auto serverButton = cocos2d::ui::Button::create("picture/MenuItems/ButtonStartAsClient.png");
		serverButton->setPosition(cocos2d::Vec2(visibleSize.width / 2, visibleSize.height*0.7));
		serverButton->addTouchEventListener([](Ref* pSender, cocos2d::ui::Widget::TouchEventType type) {
			if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
				assert(0);
			}
		});

		this->addChild(serverButton);

		return true;
	}//init

};