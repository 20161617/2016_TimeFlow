#ifndef __PROLOGUE__H_
#define __PROLOGUE__H_

#include "cocos2d.h"
USING_NS_CC;

class PrologueScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(PrologueScene);

	//메뉴 화면으로 돌아가기
	void PrologueScene::menuCallback(cocos2d::Ref* sender);
	void changeMenuScene_R(Ref *sender);

	//다음맵 넘어가기
	void PrologueScene::changeGameScene1_R(Ref* sender);

	//키보드 누르기
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

private:
	//프롤로그 화면 전환 횟수 10되면 게임 시작
	int count = 1;

	//프롤로그 화면
	Sprite* prologue1;
	Sprite* prologue2;
	Sprite* prologue3;
	Sprite* prologue4;
	Sprite* prologue5;
	Sprite* prologue6;
	Sprite* prologue7;
	Sprite* prologue8;
	Sprite* prologue9;
};
#endif