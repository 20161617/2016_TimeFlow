#include "HELP_SCENE.h"
#include "MENU_SCENE.h"

Scene* HelpScene::createScene(){
	auto scene = Scene::create();

	auto layer = HelpScene::create();
	scene->addChild(layer);

	return scene;
}

bool HelpScene::init(){
	if (!Layer::init()){
		return false;
	}

	//돌아가기 버튼 받아오기
	back1 = Sprite::create("./Help/back.png");
	back2 = Sprite::create("./Help/back2.png");

	//도움말 화면
	helpSprite1 = Sprite::create("./Help/helpSPR.png");
	helpSprite1->setPosition(Point(512.0f, 384.0f));
	this->addChild(helpSprite1, 1);

	helpSprite2 = Sprite::create("./Help/helpSPR2.png");
	helpSprite2->setPosition(Point(512, 384));
	helpSprite2->setVisible(false);
	this->addChild(helpSprite2, 1);

	//화면 넘기기용 화살표
	leftArrow = Sprite::create("./Help/leftArrow.png");
	leftArrow->setPosition(Point(874, 227));
	this->addChild(leftArrow, 2);

	rightArrow = Sprite::create("./Help/rightArrow.png");
	rightArrow->setPosition(Point(918, 227));
	this->addChild(rightArrow, 2);

	// 돌아가기 버튼
	BACK = Sprite::create("./Help/back2.png");
	BACK->setPosition(Point(760, 48));
	this->addChild(BACK, 2);

	//나가기 버튼 만들기
	spr_exit = MenuItemSprite::create(back1, back1, CC_CALLBACK_1(HelpScene::changeMenuScene_R, this));
	exit = Menu::create(spr_exit, NULL);
	exit->setPosition(Point(760, 48));
	exit->setAnchorPoint(Point::ZERO);
	exit->setVisible(false);
	this->addChild(exit, 2);

	//마우스 리스너
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(HelpScene::onMouseMove, this);
	mouseListener->onMouseDown = CC_CALLBACK_1(HelpScene::onMouseDown, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void HelpScene::onMouseMove(cocos2d::Event* event){ //마우스 움직임 감지
	EventMouse* e = (EventMouse*)event;
	Point cursorXY_ = Point(e->getCursorX(), e->getCursorY());

	Rect backR = BACK->getBoundingBox();
	Rect helpSprite1R = helpSprite1->getBoundingBox();

	//버튼 색바뀌게 하는 용도
	if (helpSprite1R.containsPoint(cursorXY_)){
		BACK->setVisible(true);
		exit->setVisible(false);
	}
	if (backR.containsPoint(cursorXY_)){
		BACK->setVisible(false);
		exit->setVisible(true);
	}
}
void HelpScene::onMouseDown(cocos2d::Event* event){//도움말 화면 넘기는 용도

	EventMouse* e = (EventMouse*)event;
	Point cursorXY_ = Point(e->getCursorX(), e->getCursorY());

	Rect leftArrowR = leftArrow->getBoundingBox();
	Rect rightArrowR = rightArrow->getBoundingBox();

	//도움말1에서 누르면 2로, 2에서 누르면 1로
	if (leftArrowR.containsPoint(cursorXY_)){
		if (helpPage == false){
			helpSprite1->setVisible(false);
			helpSprite2->setVisible(true);
			helpPage = true;
		}
		else if (helpPage == true){
			helpSprite1->setVisible(true);
			helpSprite2->setVisible(false);
			helpPage = false;
		}
	}
	if (rightArrowR.containsPoint(cursorXY_)){
		if (helpPage == false){
			helpSprite1->setVisible(false);
			helpSprite2->setVisible(true);
			helpPage = true;
		}
		else if (helpPage == true){
			helpSprite1->setVisible(true);
			helpSprite2->setVisible(false);
			helpPage = false;
		}
	}
}
void HelpScene::changeMenuScene_R(Ref *sender){//메뉴로 돌아가기
	Director::getInstance()->replaceScene(MenuScene::createScene());
}