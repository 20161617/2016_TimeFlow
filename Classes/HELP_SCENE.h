#ifndef __HELP_SCENE_H___
#define __HELP_SCENE_H___

#include "cocos2d.h"

USING_NS_CC;

class HelpScene : public Layer
{
public:

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);

	//마우스 움직이기
	void onMouseMove(cocos2d::Event* event);
	void onMouseDown(cocos2d::Event* event);
	//메뉴화면으로 돌아가기
	void changeMenuScene_R(Ref *sender);

private:
	//도움말 화면2개
	Sprite* helpSprite1;
	Sprite* helpSprite2;
	//나가기 버튼
	MenuItemSprite* spr_exit;
	Menu* exit;
	Sprite* back1;
	Sprite* back2;
	Sprite* BACK;
	//화면 넘기기용 화살표
	Sprite* leftArrow;
	Sprite* rightArrow;

	//헬프 페이지 1 = false, 2 = true
	bool helpPage = false;
};

#endif