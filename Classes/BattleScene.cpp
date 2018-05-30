//
//  BattleSceneScene.cpp
//  AirfightBattleScene
//
//  Created by Jason on 14-5-8.
//
//

#include "BattleScene.h"
#include "ui/CocosGUI.h"
//#include "FKSprite.h"
USING_NS_CC;
using namespace ui;

// ��ͬ�л���tag
static int E0TAG = 10;
static int E1TAG = 11;
static int E2TAG = 12;
static int BOSSTAG = 100;

Scene* BattleScene::createScene()
{
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();
	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = BattleScene::create();
	// ��BattleScene����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);
	// ���س�������
	return scene;
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
	// ���ø����init����
	if (!Layer::init())
	{
		return false;
	}
	// ����豸�ɼ���ͼ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// ��ȡ��Ļ��Ⱥ͸߶�
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;


	_battleMap = TMXTiledMap::create("map/LostTemple.tmx");
	_battleMap->setAnchorPoint(Vec2(0, 0));
	addChild(_battleMap, 0);

	return true;
}

void BattleScene::onEnter() {
	Layer::onEnter();

	}

// �ص����º������ú���ÿһ֡�������
void BattleScene::update(float delta) {
	
}


/*************************�л���غ���*****************************************/



