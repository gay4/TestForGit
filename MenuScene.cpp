#include"MenuScene.h"
#include"AudioControlScene.h"
#include"MainScene.h"
#include"ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
#include"cocos2d.h"
#include"HelloWorldScene.h"
USING_NS_CC;
using namespace ui;
using namespace CocosDenshion;
#define MUSIC_FILE "bgm.wav"

Scene* GameMenu::createScene()
{ 
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}

char* EncodeToUTF8(const char* mbcsStr)
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


bool GameMenu::init()
{

	//���ø����init����

	if (!Layer::init())
	{
		return false;
	}

	//Ԥ���ر�������
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);

	//���ű�������
	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1);



	auto sprite = Sprite::create("fate.jpg");
	
	
	//����豸�ɼ���ͼ��С

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite->setScale(1);
	this->addChild(sprite, 0);

	//����ʼ��Ϸ����ť

	auto start_button = Button::create("button.png");
	start_button->setScale(1.7);
	start_button->setTitleText(EncodeToUTF8("��ʼ��Ϸ"));
	start_button->setTitleFontName("΢���ź�");
	start_button->setTitleFontSize(11);
	start_button->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.7));
	start_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{

			//�л���mainscene����

			auto transition = TransitionSlideInL::create(2.0, MainScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(start_button);

	//����Ϸ���á���ť

	auto set_button = Button::create("button.png");
	set_button->setScale(1.7f);
	set_button->setTitleText(EncodeToUTF8("��Ϸ����"));
	set_button->setTitleFontName("΢���ź�");
	set_button->setTitleFontSize(11);
	set_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.55));
	set_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{

			//�л���AudioControl����

			auto transition = TransitionSlideInL::create(2.0, AudioControl::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(set_button);

	//"�˳���Ϸ"��ť

	auto close_button = Button::create("button.png");
	close_button->setScale(1.7);
	close_button->setTitleText(EncodeToUTF8("�˳���Ϸ"));
	close_button->setTitleFontName("΢���ź�");
	close_button->setTitleFontSize(11);
	close_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.4));
	close_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->end();
			exit(0);
		}
	});
	this->addChild(close_button);

	//����

	auto banner_text = Text::create(EncodeToUTF8("�Ľ���"), "Arial-BoldMT", 32);
	banner_text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.15));
	this->addChild(banner_text);





	return true;
}








