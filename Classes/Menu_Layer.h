#ifndef __MENU_LAYER___
#define __MENU_LAYER___

#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public Layer
{
public:

	virtual bool init();

	//�޴�ȭ�� ���ư���
	void changeMenuScene_R(Ref *sender);

	CREATE_FUNC(MenuLayer);

private:
	//ESC���̾� �� ���, ������ ��ư
	Sprite* pause_background;
	MenuItemSprite* spr_exit;
	Menu* exit;
};

#endif