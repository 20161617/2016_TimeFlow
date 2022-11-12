#ifndef __MENU_LAYER__
#define __MENU_LAYER__

#include"cocos2d.h"

USING_NS_CC;

class MenuLayer : public Layer
{
public:

	virtual bool init();
	void changeMenuScene_R(Ref *sender);
	void MenuLayer::menuCallback(cocos2d::Ref* sender);
	CREATE_FUNC(MenuLayer);

private:
	cocos2d::Sprite* MenuSprite;
	cocos2d::MenuItemImage* spr_exit;
	cocos2d::Menu* exit;
};

#endif