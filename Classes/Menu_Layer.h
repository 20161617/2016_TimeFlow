#ifndef __MENU_LAYER___
#define __MENU_LAYER___

#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public Layer
{
public:

	virtual bool init();

	//메뉴화면 돌아가기
	void changeMenuScene_R(Ref *sender);

	CREATE_FUNC(MenuLayer);

private:
	//ESC레이어 뒷 배경, 나가기 버튼
	Sprite* pause_background;
	MenuItemSprite* spr_exit;
	Menu* exit;
};

#endif