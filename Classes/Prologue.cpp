#include "Prologue.h"
#include "GAME_SCENE_1.h"
#include "SimpleAudioEngine.h"

Scene* PrologueScene::createScene(){
	auto scene = Scene::create();

	auto layer = PrologueScene::create();

	scene->addChild(layer);

	return scene;
}

bool PrologueScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
    //BGM불러오기	
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("./Effect Music/1~3/1_3.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("./Effect Music/4~9/4_9.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Effect Music/1~3/1_3.mp3");

	prologue1 = Sprite::create("./Pro_Thi_Epi/Prologue/1.png");
	prologue1->setPosition(Point::ZERO);
	prologue1->setAnchorPoint(Point::ZERO);
	this->addChild(prologue1, 1);

	prologue2 = Sprite::create("./Pro_Thi_Epi/Prologue/2.png");
	prologue2->setPosition(Point::ZERO);
	prologue2->setAnchorPoint(Point::ZERO);
	prologue2->setOpacity(0);
	this->addChild(prologue2, 2);

	prologue3 = Sprite::create("./Pro_Thi_Epi/Prologue/3.png");
	prologue3->setPosition(Point::ZERO);
	prologue3->setAnchorPoint(Point::ZERO);
	prologue3->setOpacity(0);
	this->addChild(prologue3, 3);

	prologue4 = Sprite::create("./Pro_Thi_Epi/Prologue/4.png");
	prologue4->setPosition(Point::ZERO);
	prologue4->setAnchorPoint(Point::ZERO);
	prologue4->setOpacity(0);
	this->addChild(prologue4, 4);

	prologue5 = Sprite::create("./Pro_Thi_Epi/Prologue/5.png");
	prologue5->setPosition(Point::ZERO);
	prologue5->setAnchorPoint(Point::ZERO);
	prologue5->setOpacity(0);
	this->addChild(prologue5, 5);

	prologue6 = Sprite::create("./Pro_Thi_Epi/Prologue/6.png");
	prologue6->setPosition(Point::ZERO);
	prologue6->setAnchorPoint(Point::ZERO);
	prologue6->setOpacity(0);
	this->addChild(prologue6, 6);

	prologue7 = Sprite::create("./Pro_Thi_Epi/Prologue/7.png");
	prologue7->setPosition(Point::ZERO);
	prologue7->setAnchorPoint(Point::ZERO);
	prologue7->setOpacity(0);
	this->addChild(prologue7, 7);

	prologue8 = Sprite::create("./Pro_Thi_Epi/Prologue/8.png");
	prologue8->setPosition(Point::ZERO);
	prologue8->setAnchorPoint(Point::ZERO);
	prologue8->setOpacity(0);
	this->addChild(prologue8, 8);

	prologue9 = Sprite::create("./Pro_Thi_Epi/Prologue/9.png");
	prologue9->setPosition(Point::ZERO);
	prologue9->setAnchorPoint(Point::ZERO);
	prologue9->setOpacity(0);
	this->addChild(prologue9, 9);

	//키보드 리스너
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(PrologueScene::onKeyPressed, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	return true;
}

void PrologueScene::changeGameScene1_R(Ref *sender){
	auto scene = TransitionFade::create(1.5, GameScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

void PrologueScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	switch (keyCode){
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{
		count++;
		if (count == 2){
			auto action1 = FadeOut::create(1.5);
			prologue1->runAction(action1);
			auto action2 = FadeIn::create(1.5);
			prologue2->runAction(action2);
		}
		else if (count == 3){
			auto action1 = FadeOut::create(1.5);
			prologue2->runAction(action1);
			auto action2 = FadeIn::create(1.5);
			prologue3->runAction(action2);
		}
		else if (count == 4){
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("./Effect Music/1~3/1_3.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Effect Music/4~9/4_9.mp3");
			auto action1 = FadeOut::create(1.5);
			prologue3->runAction(action1);
			auto action2 = FadeIn::create(1.5);
			prologue4->runAction(action2);
		}
		else if (count == 5){
			auto action1 = FadeOut::create(1.5);
			prologue4->runAction(action1);
			auto action2 = FadeIn::create(1.5);
			prologue5->runAction(action2);
		}
		else if (count == 6){
			auto action1 = FadeOut::create(1.5);
			prologue5->runAction(action1);
			auto action2 = FadeIn::create(1.5);
			prologue6->runAction(action2);
		}
		else if (count == 7){
			auto action1 = FadeOut::create(1.5);
			prologue6->runAction(action1);
			auto action2 = FadeIn::create(1.5);
			prologue7->runAction(action2);
		}
		else if (count == 8){
			auto action1 = FadeOut::create(1.5);
			prologue7->runAction(action1);
			auto action2 = FadeIn::create(1.5);
			prologue8->runAction(action2);
		}
		else if (count == 9){
			auto action1 = FadeOut::create(1.5);
			prologue8->runAction(action1);
			auto action2 = FadeIn::create(1.5);
			prologue9->runAction(action2);
		}
		else if (count == 10){
			UserDefault::getInstance()->setBoolForKey("End", true);
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic("./Effect Music/4~9/4_9.mp3");
			changeGameScene1_R(this);
		}
	}
	}
}