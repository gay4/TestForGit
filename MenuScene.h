//GameMenu�����������ʾһ���˵������������ѡ�񡰿�ʼ��Ϸ�����ǡ���Ϸ���á�
#include<cocos2d.h>
class GameMenu : public cocos2d ::Layer
{
public:
	
	/*
	��̬����������Scece����
	���鷵��ʵ�����͵�ָ��
	*/

	static cocos2d::Scene*createScene();
	
	/*
	init��������ɳ�ʼ������
	����boolֵ
	*/

	virtual bool init();
	
	/*
	ʹ��CREATE_FUNC����������ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
	*/

	CREATE_FUNC(GameMenu);
};