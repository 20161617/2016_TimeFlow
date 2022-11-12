#include "Menu_Layer.h"
#include "MENU_SCENE.h"

bool MenuLayer::init(){
	if (!Layer::init()){
		return false;
	}

	//ESC레이어 백그라운드 
	pause_background = Sprite::create("./Layers/pause_background.png");
	pause_background->setAnchorPoint(Point::ZERO);
	this->addChild(pause_background, 1);

	//나가기 버튼 
	spr_exit = MenuItemImage::create("./Layers/pause_exit.png", "./Layers/pause_exit2.png", CC_CALLBACK_1(MenuLayer::changeMenuScene_R, this));
	exit = Menu::create(spr_exit, NULL);
	this->addChild(exit,2);

	return true;
}

//메뉴로 나가기
void MenuLayer::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}
