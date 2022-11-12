#include "Hint_Layer.h"
#include "GAME_SCENE_1.h"
#include "SimpleAudioEngine.h"

bool HintLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//마우스 클릭 소리 가져오기
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Mouse_click.mp3");

	//마우스 리스너
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(HintLayer::onMouseDown, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	//아이템 큰창, 작은창
	HintWindow = Sprite::create("./Layers/Hint.png");
	this->addChild(HintWindow);

	//돌아가기 버튼
	exit = Sprite::create("./Mainmenu/exit.png");
	exit->setPosition(Point(HintWindow->getPosition() + Point(EXIT_X, -EXIT_Y)));
	exit->setAnchorPoint(Point::ZERO);
	exit->setVisible(false);
	this->addChild(exit, 5);

	return true;
}

bool HintLayer::findHint(int hintNumber){
	if (hintNumber == 0){
		thiefExpand = Sprite::create("./Items/Hints/Criminal_profile.png");
		thiefExpand->setPosition(Point(HintWindow->getPosition()));
		thiefExpand->setVisible(false);
		this->addChild(thiefExpand, 4);

		return theifProfile = true;
	}
	else if (hintNumber == 1){
		map1Hint = Sprite::create("./Items/Hints/1.png");
		map1Hint->setPosition(Point(HintWindow->getPosition() + Point(-POINT_LONG_X2_LEFT, POINT_Y2)));
		this->addChild(map1Hint, 3);

		map1HintExpand = Sprite::create("./Items/Hints/Suspect_1.png");
		map1HintExpand->setPosition(Point(HintWindow->getPosition()));
		map1HintExpand->setVisible(false);
		this->addChild(map1HintExpand, 4);

		return map1hintFind = true;
	}
	else if (hintNumber == 2){
		map2Hint = Sprite::create("./Items/Hints/2.png");
		map2Hint->setPosition(Point(HintWindow->getPosition() + Point(POINT_X, POINT_Y2)));
		this->addChild(map2Hint, 3);

		map2HintExpand = Sprite::create("./Items/Hints/Suspect_2.png");
		map2HintExpand->setPosition(Point(HintWindow->getPosition()));
		map2HintExpand->setVisible(false);
		this->addChild(map2HintExpand, 4);

		return map2hintFind = true;
	}
	else if (hintNumber == 3){
		map3Hint = Sprite::create("./Items/Hints/3.png");
		map3Hint->setPosition(Point(HintWindow->getPosition() + Point(POINT_LONG_X2_RIGHT, POINT_Y2)));
		this->addChild(map3Hint, 3);

		map3HintExpand = Sprite::create("./Items/Hints/Suspect_3.png");
		map3HintExpand->setPosition(Point(HintWindow->getPosition()));
		map3HintExpand->setVisible(false);
		this->addChild(map3HintExpand, 4);

		return map3hintFind = true;
	}
	else if (hintNumber == 4){
		map4Hint = Sprite::create("./Items/Hints/4.png");
		map4Hint->setPosition(Point(HintWindow->getPosition() + Point(-POINT_LONG_X1_LEFT, -POINT_Y1)));
		this->addChild(map4Hint, 3);

		map4HintExpand = Sprite::create("./Items/Hints/Suspect_4.png");
		map4HintExpand->setPosition(Point(HintWindow->getPosition()));
		map4HintExpand->setVisible(false);
		this->addChild(map4HintExpand, 4);

		return map4hintFind = true;
	}
	else if (hintNumber == 5){
		map5Hint = Sprite::create("./Items/Hints/5.png");
		map5Hint->setPosition(Point(HintWindow->getPosition() + Point(POINT_X, -POINT_Y1)));
		this->addChild(map5Hint, 3);

		map5HintExpand = Sprite::create("./Items/Hints/Suspect_5.png");
		map5HintExpand->setPosition(Point(HintWindow->getPosition()));
		map5HintExpand->setVisible(false);
		this->addChild(map5HintExpand, 4);

		return map5hintFind = true;
	}
	else if (hintNumber == 6){
		map6Hint = Sprite::create("./Items/Hints/6.png");
		map6Hint->setPosition(Point(HintWindow->getPosition() + Point(POINT_LONG_X1_RIGHT, -POINT_Y1)));
		this->addChild(map6Hint, 3);

		map6HintExpand = Sprite::create("./Items/Hints/Suspect_6.png");
		map6HintExpand->setPosition(Point(HintWindow->getPosition()));
		map6HintExpand->setVisible(false);
		this->addChild(map6HintExpand, 4);

		return map6hintFind = true;
	}
}

void HintLayer::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;
	Point cursorXY = Point(e->getCursorX(), e->getCursorY());

	if (HintLayerOnOff == true){
		Rect clockGear1R = Rect(ORIGIN_X1, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
		Rect clockGear2R = Rect(ORIGIN_X2, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
		Rect clockGear3R = Rect(ORIGIN_X3, ORIGIN_Y2, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
		Rect clockGear4R = Rect(ORIGIN_X1, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
		Rect clockGear5R = Rect(ORIGIN_X2, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
		Rect clockGear6R = Rect(ORIGIN_X3, ORIGIN_Y1, ITEM_WINDOW_SIZE_X, ITEM_WINDOW_SIZE_Y);
		Rect theifR = Rect(THIEF_ORIGIN_X, THIEF_ORIGIN_Y, THIEF_SIZE_X, THIEF_SIZE_Y);
		Rect exitR = Rect(EXIT_RECT_X, EXIT_RECT_Y, EXIT_RECT_SIZE_X, EXIT_RECT_SIZE_Y);

		if (theifProfile == true && theifR.containsPoint(cursorXY) && HintExpand == false){
			thiefExpand->setVisible(true);
			exit->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = true;
		}
		else if (theifProfile == true && exitR.containsPoint(cursorXY)){
			thiefExpand->setVisible(false);
			exit->setVisible(false);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = false;
		}
		if (map1hintFind == true && clockGear1R.containsPoint(cursorXY) && HintExpand == false){
			map1HintExpand->setVisible(true);
			exit->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = true;
		}
		else if (map1hintFind == true && exitR.containsPoint(cursorXY)){
			map1HintExpand->setVisible(false);
			exit->setVisible(false);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = false;
		}
		if (map2hintFind == true && clockGear2R.containsPoint(cursorXY) && HintExpand == false){
			map2HintExpand->setVisible(true);
			exit->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = true;
		}
		else if (map2hintFind == true && exitR.containsPoint(cursorXY)){
			map2HintExpand->setVisible(false);
			exit->setVisible(false);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = false;
		}
		if (map3hintFind == true && clockGear3R.containsPoint(cursorXY) && HintExpand == false){
			map3HintExpand->setVisible(true);
			exit->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = true;
		}
		else if (map3hintFind == true && exitR.containsPoint(cursorXY)){
			map3HintExpand->setVisible(false);
			exit->setVisible(false);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = false;
		}
		if (map4hintFind == true && clockGear4R.containsPoint(cursorXY) && HintExpand == false){
			map4HintExpand->setVisible(true);
			exit->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = true;
		}
		else if (map4hintFind == true && exitR.containsPoint(cursorXY)){
			map4HintExpand->setVisible(false);
			exit->setVisible(false);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = false;
		}
		if (map5hintFind == true && clockGear5R.containsPoint(cursorXY) && HintExpand == false){
			map5HintExpand->setVisible(true);
			exit->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = true;
		}
		else if (map5hintFind == true && exitR.containsPoint(cursorXY)){
			map5HintExpand->setVisible(false);
			exit->setVisible(false);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = false;
		}
		if (map6hintFind == true && clockGear6R.containsPoint(cursorXY) && HintExpand == false){
			map6HintExpand->setVisible(true);
			exit->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = true;
		}
		else if (map6hintFind == true && exitR.containsPoint(cursorXY)){
			map6HintExpand->setVisible(false);
			exit->setVisible(false);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
			HintExpand = false;
		}
	}
}