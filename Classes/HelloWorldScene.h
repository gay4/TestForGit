#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

// HelloWorld��̳�cocos2d::Layer���㣩
class HelloWorld : public cocos2d::Layer
{
private:
	TMXTiledMap * _tileMap; // ��ͼ
	Sprite* _player; // ���
	int _screenWidth, _screenHeight; // ��Ļ�Ŀ�Ⱥ͸߶�
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

	// �������Ϊ�Ӿ���������ʾ���õ�ͼ�����һ���ƶ�
	void setViewpointCenter(Vec2 position);

	// ѡ�����ص�����
	void menuCloseCallback(cocos2d::Ref* pSender);

	/**
	* ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	*/
	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
