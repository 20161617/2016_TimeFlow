#include "MenuLayer.h"
#include "MENU_SCENE.h"

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CCLOG("MenuLayer::init()");

	MenuSprite = Sprite::create("MenuSprite.png");
	MenuSprite->setPosition(Point(120, 208));
	MenuSprite->setAnchorPoint(Point::ZERO);
	this->addChild(MenuSprite, 4);

	spr_exit = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_1(MenuLayer::changeMenuScene_R, this));
	exit = Menu::create(spr_exit, NULL);
	exit->setPosition(Point(850.0f, 100.0f));
	this->addChild(exit, 4);

	return true;
}

void MenuLayer::changeMenuScene_R(Ref *sender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}