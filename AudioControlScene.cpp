#include"AudioControlScene.h"
#include"ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include"MenuScene.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;

Scene* AudioControl::createScene()
{
	auto scene = Scene::create();
	auto layer = AudioControl::create();
	scene->addChild(layer);
	return scene;
}


char* EncodeToUTF81(const char* mbcsStr)
{
	wchar_t*  wideStr;
	char*     utf8Str;
	int       charLen;
	charLen = MultiByteToWideChar(936, 0, mbcsStr, -1, NULL, 0);
	wideStr = (wchar_t*)malloc(sizeof(wchar_t)*charLen);
	MultiByteToWideChar(936, 0, mbcsStr, -1, wideStr, charLen);
	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
	utf8Str = (char*)malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);
	free(wideStr);
	return utf8Str;
}



bool::AudioControl::init()
{

	//���ø����init����

	if (!Layer::init())
	{
		return false;
	}

	//����豸�ɼ���ͼ��С

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�������������֡��ı������Ϊ��ǰ����ӽڵ�

	auto music_text = Text::create(EncodeToUTF81("��������"), "Arial", 14);
	music_text->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.7));
	this->addChild(music_text);

	

	//����������"��ť�����ʱ����returnMenu����

	auto return_button = Button::create("b1.jpg");
	return_button->setPosition(Vec2(visibleSize.width - return_button->getContentSize().width / 2, return_button->getContentSize().height / 2));
	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{

			//�л���MenuScene����

			auto transition = TransitionSlideInL::create(2.0, GameMenu::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(return_button);

	// ��ͣ��������
	auto pauseMusic = Button::create("musicPause.png");
	pauseMusic->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		}
	});
	pauseMusic->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.65));
	this->addChild(pauseMusic);

	// ������������
	auto resumeMusic = Button::create("musicContinue.png");
	resumeMusic->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	});
	resumeMusic->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height*0.65));
	this->addChild(resumeMusic);

	//����

	auto banner_text = Text::create(EncodeToUTF81("�Ľ���"), "Arial-BoldMT", 32);
	banner_text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.15));
	this->addChild(banner_text);
	return true;
}



