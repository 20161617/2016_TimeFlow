#include "Correct.h"
#include "SimpleAudioEngine.h"
#include "MENU_SCENE.h"
#include "Menu_Layer.h"

MenuLayer* menuLayerC;

Scene* CorrectScene::createScene()
{
	auto scene = Scene::create();

	auto layer = CorrectScene::create();

	scene->addChild(layer);

	menuLayerC = MenuLayer::create();
	menuLayerC->setVisible(false);
	scene->addChild(menuLayerC, 5);

	return scene;
}

bool CorrectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("./Effect Music/Correct/bgm1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("./Effect Music/Correct/bgm2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Effect Music/Correct/bgm1.mp3");

	palace = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/palace.png");
	palace->setPosition(Point::ZERO);
	palace->setAnchorPoint(Point::ZERO);
	this->addChild(palace, 0);

	epilogue1 = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/1.png");
	epilogue1->setPosition(Point::ZERO);
	epilogue1->setAnchorPoint(Point::ZERO);
	this->addChild(epilogue1, 2);

	epilogue2 = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/2.png");
	epilogue2->setPosition(Point::ZERO);
	epilogue2->setAnchorPoint(Point::ZERO);
	epilogue2->setOpacity(0);
	this->addChild(epilogue2, 2);

	daughter = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/daughter1.png");
	daughter->setPosition(Point::ZERO);
	daughter->setAnchorPoint(Point::ZERO);
	daughter->setVisible(false);
	this->addChild(daughter, 1);

	designer1 = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/designer1.png");
	designer1->setPosition(Point::ZERO);
	designer1->setAnchorPoint(Point::ZERO);
	designer1->setVisible(false);
	this->addChild(designer1, 1);

	designer2 = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/designer2.png");
	designer2->setPosition(Point::ZERO);
	designer2->setAnchorPoint(Point::ZERO);
	designer2->setVisible(false);
	this->addChild(designer2, 1);

	designer3 = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/designer3.png");
	designer3->setPosition(Point::ZERO);
	designer3->setAnchorPoint(Point::ZERO);
	designer3->setVisible(false);
	this->addChild(designer3, 1);

	king1 = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/king1.png");
	king1->setPosition(Point::ZERO);
	king1->setAnchorPoint(Point::ZERO);
	king1->setVisible(false);
	this->addChild(king1, 1);

	king2 = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/king2.png");
	king2->setPosition(Point::ZERO);
	king2->setAnchorPoint(Point::ZERO);
	king2->setVisible(false);
	this->addChild(king2, 1);

	king3 = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/king3.png");
	king3->setPosition(Point::ZERO);
	king3->setAnchorPoint(Point::ZERO);
	king3->setVisible(false);
	this->addChild(king3, 1);

	king4 = Sprite::create("./Pro_Thi_Epi/Epilogue/Correct/king3.png");
	king4->setPosition(Point::ZERO);
	king4->setAnchorPoint(Point::ZERO);
	king4->setVisible(false);
	this->addChild(king4, 1);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(CorrectScene::onKeyPressed, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	return true;
}

//��ȭâ �ø���
void CorrectScene::CallCommunication(std::string info){

	Texts = Label::createWithTTF(info, "./Moris.ttf", 25, Size(820, 190));
	Texts->setPosition(Point(113, 18));
	Texts->setAnchorPoint(Point::ZERO);
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

//��ȭâ ��������
void CorrectScene::BackCommunication(){
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

void CorrectScene::changeMenuScene_R(Ref *sender){
	auto scene = TransitionFade::create(3, MenuScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void CorrectScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{ //�����̽��� ������ ��
		count++;
		if (count == 2){
			auto action1 = FadeOut::create(1.5);
			epilogue1->runAction(action1);
			king1->setVisible(true);
			CorrectScene::CallCommunication(UTF8("�̰��� �ð�ž����Ϲ����� �ƴϴ���?\n\n��Ϲ����� ��ģ ������ ������ ���� ���ϰŶ�!"));
		}
		else if (count == 3){
			king1->setVisible(false);
			CorrectScene::BackCommunication();
			daughter->setVisible(true);
			CorrectScene::CallCommunication(UTF8("������ �ٷ� �ս��� �Ǻ��� �����ϰ� �ִ� �̹������Դϴ�!"));
		}
		else if (count == 4){
			daughter->setVisible(false);
			CorrectScene::BackCommunication();
			king2->setVisible(true);
			CorrectScene::CallCommunication(UTF8("����? ���� ���ڸ� �������Ŷ�!"));
		}
		else if (count == 5){
			king2->setVisible(false);
			CorrectScene::BackCommunication();
			king3->setVisible(true);
			CorrectScene::CallCommunication(UTF8("�ð�ž�� ��Ϲ����� ��ģ ���δ� �ʿ�����!\n\n�� �ʸ� �ϰ� �츮 �ս��� ���� ����� ���� �ð�Ŵ�..\n\n���� �׷� ���� ���������� ���� ���ϰŶ�!"));
		}
		else if (count == 6){
			king3->setVisible(false);
			CorrectScene::BackCommunication();
			designer1->setVisible(true);
			CorrectScene::CallCommunication(UTF8("..."));
		}
		else if (count == 7){
			designer1->setVisible(false);
			CorrectScene::BackCommunication();
			king3->setVisible(true);
			CorrectScene::CallCommunication(UTF8("� ������ ���ұ�!!"));
		}
		else if (count == 8){
			king3->setVisible(false);
			CorrectScene::BackCommunication();
			designer2->setVisible(true);
			CorrectScene::CallCommunication(UTF8("�����... �̿� ���� ���簡 ������ �ϳ� �ؿԽ��ϴ�.\n\n�츮 �ձ����� ���� ������ �ð�ž�� ���߰Ը� ���شٸ� ���� ���� ���� �ְڴٰ�..."));
		}
		else if (count == 9){
			designer2->setVisible(false);
			CorrectScene::BackCommunication();
			king2->setVisible(true);
			CorrectScene::CallCommunication(UTF8("�׳��� ���� ���� �־� �츮 �ձ��� �Ȱ�, �鼺���� �Ҿȿ� ���� �ϴٴ�..."));
		}
		else if (count == 10){
			king2->setVisible(false);
			CorrectScene::BackCommunication();
			king3->setVisible(true);
			CorrectScene::CallCommunication(UTF8("�� �뼭�� �� ����! ���� �� ���� ��� ����� �м��ϰ�, �츮 �ձ����� �ѾƳ� �Ŷ�!\n\n��, �ٽô� ���� �鿩���� ���ϵ��� �Ͽ���!"));
		}
		else if (count == 11){
			king3->setVisible(false);
			CorrectScene::BackCommunication();
			designer3->setVisible(true);
			CorrectScene::CallCommunication(UTF8("�˼��մϴ�, �˼��մϴ�..! �� ���� ���ֽʽÿ�!!\n\n���� �ٽô� �׷� ���� �������� �ʰڽ��ϴ�!!"));
		}
		else if (count == 12){
			designer3->setVisible(false);
			CorrectScene::BackCommunication();
			king3->setVisible(true);
			CorrectScene::CallCommunication(UTF8("�� �� �ٹ��Ŷ�! � �� �ڸ� ����� �ʰ� �� �ϴ� ���̳�!"));
		}
		else if (count == 13){
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("./Effect Music/Correct/bgm1.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Effect Music/Correct/bgm2.mp3");
			king3->setVisible(false);
			CorrectScene::BackCommunication();
			king4->setVisible(true);
			CorrectScene::CallCommunication(UTF8("�׸��� ������ ã�� ������ �����Դ� ���� ����� �����ڴ�.\n\n��, ������ �ִ� ���絵 Ǯ���ְŶ�."));
		}
		else if (count == 14){
			auto action1 = FadeOut::create(1.5);
			king4->runAction(action1);
			auto action2 = FadeOut::create(1.5);
			Texts->runAction(action2);
			auto action3 = FadeIn::create(1.5);
			epilogue2->runAction(action3);
		}
		else if (count == 15){
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("./Effect Music/Correct/bgm2.mp3");
			CorrectScene::changeMenuScene_R(this);
		}
	}
	}
}