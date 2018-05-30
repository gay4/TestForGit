//#include "CallFuncActionTest.h"
//
//  CallFuncActionTest.cpp
//  ActionCallFuncTest
//
//  Created by Jason on 14-5-7.
//
//

#include "CallFuncActionTest.h"

USING_NS_CC;

// ��̬��������ʾplane��tag
static int kTagPlane = 1;

Scene* CallFuncActionTest::createScene()
{
	// ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto scene = Scene::create();

	// ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
	auto layer = CallFuncActionTest::create();

	// ��CallFuncActionScene����Ϊ�ӽڵ���ӵ�����
	scene->addChild(layer);

	// ���س�������
	return scene;
}

bool CallFuncActionTest::init()
{
	// ���ø����init����
	if (!Layer::init())
	{
		return false;
	}
	// ���OpenGL ES��ͼ�Ĵ�С
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// ����Ļ��ȡ��߶ȱ��浽����ı�������
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;
	// ʹ��.pngͼƬ����һ������
	_plane = Sprite::create("plane.png");
	// ���þ����λ��
	_plane->setPosition(Vec2(_plane->getContentSize().width / 2, _screenHeight / 2));
	// ���������Ϊ��ǰ����ӽڵ�
	this->addChild(_plane, 1, kTagPlane);
	/**
	������һ��CallFunc����������move����
	3.0 ���µĻص��ӿڣ����ĸ�CC_CALLBACKȡ����
	��ʵCC_CALLBACK�Ĳ������ں��������
	0�ʹ���ص�����û�в����ĺ�����1������һ��������2����������������3��������������
	*/
	// auto callFunc = CallFunc::create(CC_CALLBACK_0(CallFuncActionScene::move, this));
	// C++11��lambda���ʽʵ�ֺ����ص�����
	auto callFunc = CallFunc::create([&] {
		// ����һ��MoveTo�������������Ļ����ƶ�����Ļ�ұ�
		auto moveTo = MoveTo::create(3, Vec2(_screenWidth - _plane->getContentSize().width / 2, _screenHeight / 2));
		// ���飨�ɻ���ִ��MoveTo����
		_plane->runAction(moveTo);
	});
	// ���飨�ɻ���ִ��CallFunc�ص�����
	_plane->runAction(callFunc);
	return true;
}

// ʵ���Զ����move����
void CallFuncActionTest::move() {
	// ͨ��tagֵ��þ������
	auto plane = this->getChildByTag(kTagPlane);
	// ����һ��MoveTo�������������Ļ����ƶ�����Ļ�ұ�
	auto moveTo = MoveTo::create(3, Vec2(_screenWidth - plane->getContentSize().width / 2, _screenHeight / 2));
	// ���飨�ɻ���ִ��MoveTo����
	plane->runAction(moveTo);
}
