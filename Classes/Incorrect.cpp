#include "Incorrect.h"
#include "SimpleAudioEngine.h"
#include "MENU_SCENE.h"
#include "Menu_Layer.h"

MenuLayer* menuLayerI;

Scene* IncorrectScene::createScene()
{
	auto scene = Scene::create();

	auto layer = IncorrectScene::create();

	scene->addChild(layer);

	menuLayerI = MenuLayer::create();
	menuLayerI->setVisible(false);
	scene->addChild(menuLayerI, 5);

	return scene;
}

bool IncorrectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("./Effect Music/Incorrect/bgm3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Effect Music/Incorrect/bgm3.mp3");

	palace = Sprite::create("./Pro_Thi_Epi/Epilogue/Incorrect/palace.png");
	palace->setPosition(Point::ZERO);
	palace->setAnchorPoint(Point::ZERO);
	this->addChild(palace, 0);

	epilogue1 = Sprite::create("./Pro_Thi_Epi/Epilogue/Incorrect/1.png");
	epilogue1->setPosition(Point::ZERO);
	epilogue1->setAnchorPoint(Point::ZERO);
	this->addChild(epilogue1, 2);

	epilogue2 = Sprite::create("./Pro_Thi_Epi/Epilogue/Incorrect/3.png");
	epilogue2->setPosition(Point::ZERO);
	epilogue2->setAnchorPoint(Point::ZERO);
	epilogue2->setOpacity(0);
	this->addChild(epilogue2, 2);

	daughter = Sprite::create("./Pro_Thi_Epi/Epilogue/Incorrect/daughter2.png");
	daughter->setPosition(Point::ZERO);
	daughter->setAnchorPoint(Point::ZERO);
	daughter->setVisible(false);
	this->addChild(daughter, 1);

	king1 = Sprite::create("./Pro_Thi_Epi/Epilogue/Incorrect/king2.png");
	king1->setPosition(Point::ZERO);
	king1->setAnchorPoint(Point::ZERO);
	king1->setVisible(false);
	this->addChild(king1, 1);

	king2 = Sprite::create("./Pro_Thi_Epi/Epilogue/Incorrect/king3.png");
	king2->setPosition(Point::ZERO);
	king2->setAnchorPoint(Point::ZERO);
	king2->setVisible(false);
	this->addChild(king2, 1);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(IncorrectScene::onKeyPressed, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	return true;
}

//��ȭâ �ø���
void IncorrectScene::CallCommunication(std::string info){

	Texts = Label::createWithTTF(info, "./Moris.ttf", 25, Size(840, 190));
	Texts->setPosition(Point(113, 18));
	Texts->setAnchorPoint(Point::ZERO);
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

//��ȭâ ��������
void IncorrectScene::BackCommunication(){
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

void IncorrectScene::changeMenuScene_R(Ref *sender){
	auto scene = TransitionFade::create(3, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void IncorrectScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{ //�����̽��� ������ ��
		count++;
		if (count == 2){
			auto action1 = FadeOut::create(1.5);
			epilogue1->runAction(action1);
			king1->setVisible(true);
			IncorrectScene::CallCommunication(UTF8("�̰��� �ð�ž����Ϲ����� �ƴ��� �ʴ���!!\n\n���� �� ������ ������ ���ϴٴ�.. ���� �� ���̸� �ѾƳ��Ŷ�!"));
		}
		else if (count == 3){
			king1->setVisible(false);
			IncorrectScene::BackCommunication();
			daughter->setVisible(true);
			IncorrectScene::CallCommunication(UTF8("���� �� ��! �̰� ��¥ ��Ϲ�������!\n\n��¥ ��Ϲ����� �ƴ϶󱸿�!"));
		}
		else if (count == 4){
			daughter->setVisible(false);
			IncorrectScene::BackCommunication();
			king2->setVisible(true);
			IncorrectScene::CallCommunication(UTF8("�װ� ������ �������� �þ���±���!\n\n������! �� ���̿� ���縦 ��� �ձ����� ������ �߹��� �����Ŷ�!"));
		}
		else if (count == 5){
			auto action1 = FadeOut::create(1.5);
			king2->runAction(action1);
			auto action2 = FadeOut::create(1.5);
			Texts->runAction(action2);
			auto action3 = FadeIn::create(1.5);
			epilogue2->runAction(action3);
		}
		else if (count == 6){
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("./Effect Music/Incorrect/bgm3.mp3");
			IncorrectScene::changeMenuScene_R(this);
		}
	}
	}
}