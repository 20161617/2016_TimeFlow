#include "MENU_Scene.h"
#include "Prologue.h"
#include "HELP_SCENE.h"
#include "GAME_SCENE_1.h"

Scene* MenuScene::createScene(){
	auto scene = Scene::create();

	auto layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}


bool MenuScene::init(){

	if (!Layer::init()){
		return false;
	}
	//메뉴 버튼 불러오기
	start_sprite1 = Sprite::create("./Mainmenu/game_start.png");
	start_sprite2 = Sprite::create("./Mainmenu/game_start2.png");
	help_sprite1 = Sprite::create("./Mainmenu/help.png");
	help_sprite2 = Sprite::create("./Mainmenu/help2.png");
	exit_sprite1 = Sprite::create("./Mainmenu/exit.png");
	exit_sprite2 = Sprite::create("./Mainmenu/exit2.png");

	//메뉴 뒷 배경
	sprite = Sprite::create("./Mainmenu/Title Background.png");
	sprite->setPosition(Point(512.0f, 384.0f));
	sprite->setAnchorPoint(Point(0.5f, 0.5f));
	this->addChild(sprite, 1);

	//메뉴 버튼들
	START = Sprite::create("./Mainmenu/game_start.png");
	START->setPosition(Point(510, 245));
	this->addChild(START, 2);

	spr_start = MenuItemSprite::create(start_sprite2, start_sprite2 , CC_CALLBACK_1(MenuScene::changePrologueScene_R, this));
	start = Menu::create(spr_start, NULL);
	start->setPosition(Point(510, 245));
	start->setVisible(false);
	this->addChild(start, 2);

	arrow1 = Sprite::create("./Mainmenu/arrow.png");
	arrow1->setPosition(Point(405, 245));
	arrow1->setVisible(false);
	this->addChild(arrow1, 2);

	HELP = Sprite::create("./Mainmenu/help.png");
	HELP->setPosition(Point(510, 195));
	this->addChild(HELP, 2);

	spr_help = MenuItemSprite::create(help_sprite2, help_sprite2, CC_CALLBACK_1(MenuScene::changeHelpScene_R, this));
	help = Menu::create(spr_help, NULL);
	help->setPosition(Point(510, 195));
	help->setVisible(false);
	this->addChild(help, 2);

	arrow2 = Sprite::create("./Mainmenu/arrow.png");
	arrow2->setPosition(Point(445, 195));
	arrow2->setVisible(false);
	this->addChild(arrow2, 2);

	EXIT = Sprite::create("./Mainmenu/exit.png");
	EXIT->setPosition(Point(510, 145));
	this->addChild(EXIT, 2);

	spr_exit = MenuItemSprite::create(exit_sprite2, exit_sprite2, CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
	exit = Menu::create(spr_exit, NULL);
	exit->setPosition(Point(510, 145));
	exit->setVisible(false);
	this->addChild(exit, 2);

	arrow3 = Sprite::create("./Mainmenu/arrow.png");
	arrow3->setPosition(Point(455, 145));
	arrow3->setVisible(false);
	this->addChild(arrow3, 2);

	//마우스 리스너-> 버튼 색 변경용
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseMove = CC_CALLBACK_1(MenuScene::onMouseMove, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

void MenuScene::update(float delta)
{

}

void MenuScene::onMouseMove(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;
    Point cursorXY_ = Point(e->getCursorX(), e->getCursorY());

	Rect startR = START->getBoundingBox();
	Rect helpR = HELP->getBoundingBox();
	Rect exitR = EXIT->getBoundingBox();
	Rect backgroundR = sprite->getBoundingBox();

	//메뉴위에 마우스를 올릴시 버튼색 바뀜

	if (backgroundR.containsPoint(cursorXY_)){
		arrow1->setVisible(false);
		START->setVisible(true);
		start->setVisible(false);

		arrow2->setVisible(false);
		HELP->setVisible(true);
		help->setVisible(false);

		arrow3->setVisible(false);
		EXIT->setVisible(true);
		exit->setVisible(false);
	}
	if (startR.containsPoint(cursorXY_)){ //스타트 버튼
		arrow1->setVisible(true);
		START->setVisible(false);
		start->setVisible(true);

		arrow2->setVisible(false);
		HELP->setVisible(true);
		help->setVisible(false);

		arrow3->setVisible(false);
		EXIT->setVisible(true);
		exit->setVisible(false);
	}
	if (helpR.containsPoint(cursorXY_)){ //도움말 버튼
		arrow2->setVisible(true);
		HELP->setVisible(false);
		help->setVisible(true);

		arrow1->setVisible(false);
		START->setVisible(true);
		start->setVisible(false);

		arrow3->setVisible(false);
		EXIT->setVisible(true);
		exit->setVisible(false);
	}
	if (exitR.containsPoint(cursorXY_)){ //나가기 버튼
		arrow3->setVisible(true);
		EXIT->setVisible(false);
		exit->setVisible(true);

		arrow1->setVisible(false);
		START->setVisible(true);
		start->setVisible(false);

		arrow2->setVisible(false);
		HELP->setVisible(true);
		help->setVisible(false);
	}
}

void MenuScene::changePrologueScene_R(Ref *sender){ //프롤로그화면으로 전환
	if (UserDefault::getInstance()->getBoolForKey("End")){
		auto scene = TransitionFade::create(3, GameScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}
	else{
		auto scene = TransitionFade::create(1.5, PrologueScene::createScene());
		Director::getInstance()->replaceScene(scene);
	}
}

void MenuScene::changeHelpScene_R(Ref *sender){ //도움말화면으로 전환
	Director::getInstance()->replaceScene(HelpScene::createScene());
}

void MenuScene::menuCloseCallback(Ref *pSender){ //나가기 버튼 게임 종료
	Director::getInstance()->end();
}

void MenuScene::menuCallback(Ref *sender){
	CCLOG("menuCallback");

	auto item = (MenuItemFont*)sender;
}