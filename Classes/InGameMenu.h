#ifndef __INGAME_MENU_H__
#define __INGAME_MENU_H__

#include "cocos2d.h"

USING_NS_CC;

class InGameMenu : public Layer
{
public:

	static Scene* createScene();
	void InGameMenu::menuCallback(cocos2d::Ref* sender);
	virtual bool init();
	CREATE_FUNC(InGameMenu);

	void changeMenuScene_R(Ref *sender);
	void changeGameScene_P(Ref *sender);

private:
	cocos2d::Sprite* BG;
};

#endif