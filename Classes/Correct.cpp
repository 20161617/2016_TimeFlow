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

//대화창 올리기
void CorrectScene::CallCommunication(std::string info){

	Texts = Label::createWithTTF(info, "./Moris.ttf", 25, Size(820, 190));
	Texts->setPosition(Point(113, 18));
	Texts->setAnchorPoint(Point::ZERO);
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

//대화창 내보내기
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
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{ //스페이스를 눌렀을 때
		count++;
		if (count == 2){
			auto action1 = FadeOut::create(1.5);
			epilogue1->runAction(action1);
			king1->setVisible(true);
			CorrectScene::CallCommunication(UTF8("이것은 시계탑의톱니바퀴가 아니더냐?\n\n톱니바퀴를 훔친 범인이 누군지 당장 말하거라!"));
		}
		else if (count == 3){
			king1->setVisible(false);
			CorrectScene::BackCommunication();
			daughter->setVisible(true);
			CorrectScene::CallCommunication(UTF8("범인은 바로 왕실의 의복을 전담하고 있는 이민혁씨입니다!"));
		}
		else if (count == 4){
			daughter->setVisible(false);
			CorrectScene::BackCommunication();
			king2->setVisible(true);
			CorrectScene::CallCommunication(UTF8("뭐야? 당장 그자를 데려오거라!"));
		}
		else if (count == 5){
			king2->setVisible(false);
			CorrectScene::BackCommunication();
			king3->setVisible(true);
			CorrectScene::CallCommunication(UTF8("시계탑의 톱니바퀴를 훔친 범인니 너였으냐!\n\n내 너를 믿고 우리 왕실의 옷을 만드는 일을 맡겼거늘..\n\n어찌 그런 일을 저질렀는지 당장 고하거라!"));
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
			CorrectScene::CallCommunication(UTF8("어서 말하지 못할까!!"));
		}
		else if (count == 8){
			king3->setVisible(false);
			CorrectScene::BackCommunication();
			designer2->setVisible(true);
			CorrectScene::CallCommunication(UTF8("사실은... 이웃 나라 병사가 제안을 하나 해왔습니다.\n\n우리 왕국에서 가장 소중한 시계탑을 멈추게만 해준다면 많은 돈과 명예를 주겠다고..."));
		}
		else if (count == 9){
			designer2->setVisible(false);
			CorrectScene::BackCommunication();
			king2->setVisible(true);
			CorrectScene::CallCommunication(UTF8("네놈이 돈에 눈이 멀어 우리 왕국을 팔고, 백성들을 불안에 떨게 하다니..."));
		}
		else if (count == 10){
			king2->setVisible(false);
			CorrectScene::BackCommunication();
			king3->setVisible(true);
			CorrectScene::CallCommunication(UTF8("내 용서할 수 없다! 당장 이 자의 모든 재산을 압수하고, 우리 왕국에서 쫓아내 거라!\n\n또, 다시는 발을 들여놓지 못하도록 하여라!"));
		}
		else if (count == 11){
			king3->setVisible(false);
			CorrectScene::BackCommunication();
			designer3->setVisible(true);
			CorrectScene::CallCommunication(UTF8("죄송합니다, 죄송합니다..! 한 번만 봐주십시오!!\n\n절대 다시는 그런 일을 저지르지 않겠습니다!!"));
		}
		else if (count == 12){
			designer3->setVisible(false);
			CorrectScene::BackCommunication();
			king3->setVisible(true);
			CorrectScene::CallCommunication(UTF8("그 입 다물거라! 어서 이 자를 끌어내지 않고 뭐 하는 것이냐!"));
		}
		else if (count == 13){
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("./Effect Music/Correct/bgm1.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Effect Music/Correct/bgm2.mp3");
			king3->setVisible(false);
			CorrectScene::BackCommunication();
			king4->setVisible(true);
			CorrectScene::CallCommunication(UTF8("그리고 범인을 찾은 병사의 딸에게는 많은 상금을 내리겠다.\n\n또, 감옥에 있는 병사도 풀어주거라."));
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