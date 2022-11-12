#include "GAME_SCENE.h"
#include "InGameMenu.h"
#include "MENU_SCENE.h"

Scene* InGameMenu::createScene()
{
	auto scene = Scene::create();

	auto layer = InGameMenu::create();
	scene->addChild(layer);

	return scene;
}

bool InGameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	BG = Sprite::create("BG.png");
	BG->setPosition(Point(0, 0));
	BG->setAnchorPoint(Point::ZERO);
	BG->setOpacity(0);
	this->addChild(BG, 1);

	auto spr_exit = MenuItemImage::create("exit.png", "exit2.png", CC_CALLBACK_1(InGameMenu::changeMenuScene_R, this));
	auto exit = Menu::create(spr_exit, NULL);
	exit->setPosition(Vec2(850.0f, 100.0f));
	this->addChild(exit, 2);

	auto spr_start = MenuItemImage::create("start1.png", "startS.png", CC_CALLBACK_1(InGameMenu::changeGameScene_P, this));
	auto start = Menu::create(spr_start, NULL);
	start->setPosition(Point(850.0f, 200.0f));
	this->addChild(start, 2);

	return true;
}

void InGameMenu::changeMenuScene_R(Ref *sender)
{
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void InGameMenu::changeGameScene_P(Ref*sender)
{
	Director::getInstance()->popScene();
}