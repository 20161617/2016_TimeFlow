#ifndef __INCORRECT_H__
#define __INCORRECT_H__

#include "cocos2d.h"
USING_NS_CC;

class IncorrectScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(IncorrectScene);

	//메뉴 화면으로 돌아가기
	void IncorrectScene::menuCallback(Ref* sender);
	void changeMenuScene_R(Ref *sender);

	//대화 보이기, 없애기
	void IncorrectScene::CallCommunication(std::string info);
	void IncorrectScene::BackCommunication();
	//키보드 누르기
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	Label* Texts; //대화

	const std::string UTF8(const std::string& string)
	{
		int bufflen = MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, NULL, 0);
		WCHAR* widebuff = new WCHAR[bufflen + 1];
		memset(widebuff, 0, sizeof(WCHAR)* (bufflen + 1));
		MultiByteToWideChar(CP_ACP, 0, string.c_str(), -1, widebuff, bufflen);

		bufflen = WideCharToMultiByte(CP_UTF8, 0, widebuff, -1, NULL, 0, NULL, NULL);
		char* buff = new char[bufflen + 1];
		memset(buff, 0, sizeof(char)* (bufflen + 1));
		WideCharToMultiByte(CP_UTF8, 0, widebuff, -1, buff, bufflen, NULL, NULL);

		std::string strResult(buff);

		delete[] widebuff;
		delete[] buff;

		return strResult;
	}

private:

	//텍스트 출력함수에 쓰임(초반 시험작 추후에 변경)
	std::string text = "";

	//에필로그 화면 전환 횟수 일정 횟수 되면 게임 오버
	int count = 1;

	//왕궁 화면
	Sprite* palace;

	//내용 화면
	Sprite* epilogue1;
	Sprite* epilogue2;

	//왕, 딸 대화
	Sprite* daughter;
	Sprite* king1;
	Sprite* king2;
	
};
#endif
