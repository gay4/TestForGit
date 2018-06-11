#include "MainScene.h"
#include "cocos2d.h"
#include "GameManager.h"
#include"SimpleAudioEngine.h"
#include"ui/CocosGUI.h"
using namespace ui;
using namespace CocosDenshion;

#include <string>

USING_NS_CC;


MainScene* MainScene::create()
{
	MainScene* mainScene = new MainScene();
	if (mainScene&&mainScene->init())
	{
		mainScene->autorelease();
		return mainScene;
	}

	log("MainScene::create error\n");

	CC_SAFE_DELETE(mainScene);
	return nullptr;
}

MainScene* MainScene::createScene()
{
	return MainScene::create();
}

bool MainScene::init()
{
	//���ຯ��
	if (!Scene::init())
	{
		return false;
	}
	//�ͻ���
	_client = Client::create();
	this->addChild(_client);

	//����ǰ�̣߳��ȴ��ͻ��˳�ʼ��
	Sleep(2000);
	//_client->sendMessage("Client is ready");
	//_client->sendMessage(_client->ip);

	//�������
	_controlPanel = ControlPanel::create();
	this->addChild(_controlPanel, 10);
	_controlPanel->setPosition(_screenWidth, _screenHeight);




	//���ö�ʱ���ص����º���
	scheduleUpdate();

	//��ȡGameManagerʵ��
	_gameManager = GameManager::create(this);
	this->addChild(_gameManager);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;

	//��ʱ��lostTemple.tmx
	_tiledMap = TMXTiledMap::create("Map/LostTemple.tmx");

	_tiledMap->setAnchorPoint(Vec2::ZERO);
	_tiledMap->setPosition(Vec2::ZERO);

	_gridMap = GridMap::create(_tiledMap);

	this->addChild(_gridMap);

	this->addChild(_tiledMap, 0);

	_unitManager = UnitManager::createWithScene(this);
	_unitManager->schedule(schedule_selector(UnitManager::update));
	
	this->addChild(_unitManager);

	_mouseRect = MouseRect::create();
	_mouseRect->setVisible(false);
	_tiledMap->addChild(_mouseRect, 10);
	//-----------------------//
	auto base_0_button = Sprite::create("base_0.png");
	base_0_button->setPosition(Vec2(visibleSize.width- base_0_button->getContentSize().width * 2, visibleSize.height - base_0_button->getContentSize().height * 2));
	this->addChild(base_0_button);
	Vec2 base_0_position = base_0_button->getPosition();
	auto base_0_button1 = Sprite::create("base_0.png");
	base_0_button1->setPosition(base_0_position);
	this->addChild(base_0_button1);
	//�������㴥��������
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [=](Touch* touch, Event* event)
	{
		//��õ�ǰ�����¼���Ŀ�����
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//��õ�ǰ�Ĵ�����
		Point locationPoint = target->convertToNodeSpace(touch->getLocation());
		//��ô�������
		Vec2 touchLocation = touch->getLocation();
		

		//��ô��������contentSize
		Size s = target->getContentSize();
		//���λ�þ���
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationPoint))
		{
			target->setOpacity(180);
			return true;
		}
		return false;
	};
	listener1->onTouchMoved=[](Touch* touch, Event* event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//�ƶ������ľ���
		target->setPosition(target->getPosition() + touch->getDelta());

	};
	listener1->onTouchEnded = [=](Touch* touch, Event* event)
	{
		
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setOpacity(255);
		target->setPosition(base_0_position);
		Unit* base_0 = Unit::create("base_0.png");
		base_0->addToMap(_gridMap, _tiledMap);
		base_0->_unitManager = _unitManager;
		base_0->setPosition(_tiledMap->convertToNodeSpace(touch->getLocation()));
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, base_0_button);
	//-----------------------//


	_unitManager->createUnit(1, 1, Grid(10, 18));

	//test rectSelect
	_unitManager->createUnit(0, 1);
	//_unitManager->deleteUnit(3);
	//_unitManager->selectOneUnit(4);
	//_unitManager->_getUnitById[4]->setTraceId(3);
	//_unitManager->_getUnitById[4]->setState(Unit::TRACING);

	auto mouseListener = EventListenerTouchOneByOne::create();
	mouseListener->setSwallowTouches(true);//
	mouseListener->onTouchBegan = [=](Touch* touch, Event* /*event*/) {
		//��¼���ѡ��ĵ�һ����
		_mouseRect->_touchStart = touch->getLocation();
		_mouseRect->start = _tiledMap->convertToNodeSpace(_mouseRect->_touchStart);

		return true;
	};
	mouseListener->onTouchMoved = [=](Touch* touch, Event* /*event*/) {
		//����ƶ�ʱ����ѡ���յ�
		_mouseRect->_touchEnd = touch->getLocation();

		//��Began������Ƶ����start�ͱ�ɣ�0��0������������
		//_mouseRect->start = _tiledMap->convertToNodeSpace(_mouseRect->_touchStart);
		_mouseRect->end = _tiledMap->convertToNodeSpace(_mouseRect->_touchEnd);

		_mouseRect->clear();

		_mouseRect->setVisible(true);
		_mouseRect->drawRect(_mouseRect->start, _mouseRect->end, Color4F(0, 1, 0, 1));

	};
	mouseListener->onTouchEnded = [=](Touch* touch, Event* /*event*/) {

		_mouseRect->clear();
	
		_mouseRect->_touchEnd = touch->getLocation();
		_mouseRect->end = _tiledMap->convertToNodeSpace(_mouseRect->_touchEnd);

		//select id in the rect
		_unitManager->selectUnitByRect(Rect{ MIN(_mouseRect->start.x, _mouseRect->end.x),
			MIN(_mouseRect->start.y, _mouseRect->end.y),
			abs(_mouseRect->start.x - _mouseRect->end.x),
			abs(_mouseRect->start.y - _mouseRect->end.y)
		});

		_mouseRect->setVisible(false);
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	

	auto keyboardListener = EventListenerKeyboard::create();

	//���ð�����Ӧ����
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		//log("Key with keycod % d pressed");

		return true;
	};

	keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		auto mapCenter = this->_tiledMap->getPosition();

		Director::getInstance()->getVisibleSize();

		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_W:
			mapCenter += Vec2(0, -50);
			if (this->_tiledMap->getBoundingBox().containsPoint(Vec2(0, 50) + Director::getInstance()->getVisibleSize()))
				this->_tiledMap->setPosition(mapCenter);
			break;

		case EventKeyboard::KeyCode::KEY_A:
			mapCenter += Vec2(50, 0);
			if (this->_tiledMap->getBoundingBox().containsPoint(Vec2(-50, 0)))
				this->_tiledMap->setPosition(mapCenter);
			break;
		
		case EventKeyboard::KeyCode::KEY_S:
			mapCenter += Vec2(0, 50);
			if (this->_tiledMap->getBoundingBox().containsPoint(Vec2(0, -50)))
				this->_tiledMap->setPosition(mapCenter);
			break;

		case EventKeyboard::KeyCode::KEY_D:
			mapCenter += Vec2(-50, 0);
			if (this->_tiledMap->getBoundingBox().containsPoint(Vec2(50, 0) + Director::getInstance()->getVisibleSize()))
				this->_tiledMap->setPosition(mapCenter);
			break;

		case EventKeyboard::KeyCode::KEY_SPACE:
			_gameManager->focusOnBase();
			break;

		default:
			break;
		}

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	//������������
	auto mouse_event = EventListenerMouse::create();
	mouse_event->onMouseMove = [=](Event *event)
	{
		EventMouse* e = static_cast<EventMouse*>(event);
		//��ȡ��ǰ�������

		_cursorPosition = Vec2(e->getCursorX(), e->getCursorY());
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouse_event, this);
	
	return true;
}

void MainScene::update(float delta)
{
	_gameManager->scrollMap();
}

bool ControlPanel::init()
{
	if (!Menu::init())
	{
		return false;
	}

	_fighter = MenuItemImage::create("fighter.png",
		"fighter.png", CC_CALLBACK_1(ControlPanel::createFighterCallBack, this));
	assert(_fighter != nullptr);

	_fighter->setAnchorPoint(Vec2(1, 1));
	_fighter->setPosition(getContentSize().width, getContentSize().height);
	//��̹�˵�ͼƬ���ڿ��������
	this->addChild(_fighter, 10);


	return true;
}

void ControlPanel::createFighterCallBack(Ref* psender)
{
	_fighter->setOpacity(100);
}