#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class MenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	
	virtual bool init();
	CREATE_FUNC(MenuScene);
	//�����ϱ�
	void menuCloseCallback(cocos2d::Ref* pSender);

	//�ҷ�����
	void MenuScene::menuCallback(Ref* sender);

	void onMouseMove(cocos2d::Event* event);
	void update(float delta);

	//���ѷα�ȭ������ �Ѿ
	void changePrologueScene_R(Ref* sender);

	//���� ȭ������ �Ѿ
	void changeHelpScene_R(Ref* sender);

private:
	//�޴� �� ���
	Sprite* sprite;
	//��ư �� ȭ��ǥ
	Sprite* arrow1;
	Sprite* arrow2;
	Sprite* arrow3;
	//��ư��
	Sprite* START;
	Sprite* HELP;
	Sprite* EXIT;
	MenuItemSprite* spr_start;
	MenuItemSprite* spr_help;
	MenuItemSprite* spr_exit;
	Sprite* start_sprite1;
	Sprite* start_sprite2;
	Sprite* help_sprite1;
	Sprite* help_sprite2;
	Sprite* exit_sprite1;
	Sprite* exit_sprite2;
	Menu* start;
	Menu* help;
	Menu* exit;
};

#endif
