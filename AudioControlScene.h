#include"cocos2d.h"

//AudioControl���������ñ������ֺ�������Ч

class AudioControl :public cocos2d::Layer
{
public:
	
	/*
	��̬����������Scene����
	���鷵����ʵ����ָ��
	*/
	
	static cocos2d::Scene* createScene();
	
	/*
	init��������ɳ�ʼ������
	ע�⣺init������cocos2d-x�з���boolֵ
	*/

	virtual bool init();

	/*
	ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	*/

	CREATE_FUNC(AudioControl);
};