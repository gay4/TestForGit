#pragma once
//
//  CallFuncActionTest.h
//  ActionCallFuncTest
//
//  Created by Jason on 14-5-7.
//
//

#ifndef __ActionCallFuncTest__CallFuncActionScene__
#define __ActionCallFuncTest__CallFuncActionScene__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class CallFuncActionTest : public cocos2d::Layer
{
private:
	// ����
	Sprite * _plane;
	// ��Ļ��ȡ��߶ȵı���
	int _screenWidth, _screenHeight;
public:
	/**
	* ��̬����������Scene����
	* ע�⣺��Cocos2d-x��û��Cocos2d-iPhone�еġ�id��,���鷵����ʵ����ָ��
	*/
	static cocos2d::Scene* createScene();
	/**
	* init��������ɳ�ʼ��������
	* ע�⣺init������Cocos2d-x�з���boolֵ�������Ƿ���Cocos2d-iPhone�еġ�id��
	*/
	virtual bool init();

	// �Զ����move����
	void move();

	/**
	* ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	*/
	CREATE_FUNC(CallFuncActionTest);
};

#endif /* defined(__ActionCallFuncTest__CallFuncActionTest__) */
