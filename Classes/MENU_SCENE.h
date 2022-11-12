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
	//종료하기
	void menuCloseCallback(cocos2d::Ref* pSender);

	//불러오기
	void MenuScene::menuCallback(Ref* sender);

	void onMouseMove(cocos2d::Event* event);
	void update(float delta);

	//프롤로그화면으로 넘어감
	void changePrologueScene_R(Ref* sender);

	//도움말 화면으로 넘어감
	void changeHelpScene_R(Ref* sender);

private:
	//메뉴 뒷 배경
	Sprite* sprite;
	//버튼 옆 화살표
	Sprite* arrow1;
	Sprite* arrow2;
	Sprite* arrow3;
	//버튼들
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
