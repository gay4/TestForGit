#pragma once

/*����һ����ȡ���ֵĳ�����������Ҫ��Ϊ��ʵ�ַ���ˣ�������Ϊ��
���䣩�����ֵ��߼����뷨�ǰ�������Ϊȫ�ֱ�������������ȻҲ����
ֱ����create server�İ�������Ϊclass�ڲ��������������������ԭ��
1����Ķ����� 2һ�����һ̨����ֻ��Ϊһ������˻��߿ͻ��ˣ���Ҳ
����ʵ�ַ�������ҵ�������ʾ���ܡ���Ȼ��Ҫ����Ϊ1����*/

#include "cocos2d.h"

class NameScene :public cocos2d::Scene {
public:
	CREATE_FUNC(NameScene);

	static std::string getName();
private:
	bool init()override;
};