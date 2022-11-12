#ifndef __INFERENCE_H__
#define __INFERENCE_H__

#include "cocos2d.h"
USING_NS_CC;

class ThinkScene : public Layer
{
public:
	static Scene* createScene();

	virtual bool init();
	CREATE_FUNC(ThinkScene);

	//메뉴 화면으로 돌아가기
	void ThinkScene::menuCallback(Ref* sender);
	void changeMenuScene_R(Ref *sender);

	//프레임호출
	void CallEveryFrame(float f);

	//대화 호출
	void CallCommunicationWindow(std::string info);
	void BackCommunicationWindow();

	//다음맵 넘어가기
	void ThinkScene::changeIncorrect_R(Ref *sender);
	void ThinkScene::changeCorrect_R(Ref *sender);

	//키보드 누르기, 때기
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//마우스 누르기, 때기
	void onMouseDown(Event* event);

	//캐릭터 카메라 이동
	void setViewPointCenter(CCPoint position);

	//캐릭터 충돌판정
	CCPoint tileCoordForPosition(CCPoint position);

	Sprite* playerSprite; //플레이어 스프라이트
	Sprite* communication; //대화창
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
	CCTMXTiledMap* _tileMap; //타일맵
	CCTMXLayer* _background; //타일맵 뒷 배경
	CCTMXObjectGroup* playerSpawn; //타일맵 플레이어 스폰장소

	//이동 속도, 이동 시간, 애니메이션 변환 속도
	const int SPEED = 4;
	const float MOVE_TIME = 0.025;
	const float ANI_SPEED = 0.15;

	//아이템 큰 창 y추가로 올라간 좌표(금고 포함)
	const int ITEM_WINDOW_Y = 114;

	//대화창 좌표 내리기 y축
	const int COMMUNICATION_WINDOW_Y = 254;

	//대화 사이즈, 좌표
	const int TALK_SIZE_X = 630;
	const int TALK_SIZE_Y = 150;
	const int TALK_Y = 262;

	//조합, 확대, 힌트 레이어 위치
	const int LAYERS_X = 512;
	const int LAYERS_Y = 498;

	//캐릭터 이동용 true시 움직임, false시 멈춤
	bool Go_Left = false;
	bool Go_Right = false;
	bool Go_Down = false;
	bool Go_Up = false;
	bool checkLeft = false;
	bool checkRight = false;
	bool checkUp = false;
	bool checkDown = false;

	//캐릭터 대각선 애니메이션 겹침 판정 체크
	bool checkLeftAnimation = false;
	bool checkRightAnimation = false;
	bool checkUpAnimation = false;
	bool checkDownAnimation = false;

	//메뉴 활성
	bool Go_Menu = false;

	//이벤트 활성
	bool Go_Event = false;

	//힌트 활성
	bool goHint = false;

	//텍스트 출력함수에 쓰임(초반 시험작 추후에 변경)
	std::string text = "";

	//캐릭터 좌표
	int characterX = NULL;
	int characterY = NULL;

	//카메라 좌표
	int cameraX = NULL;
	int cameraY = NULL;

	//충돌체크 좌표 
	const int BREAK_TOO_X = 28; //왼쪽,오른쪽 충돌체크시 x좌표용도
	const int BREAK_ZERO_Y = 0; //왼쪽,오른쪽 충돌체크시 y좌표용도
	const int BREAK_DOWN_Y = 48; //왼쪽,오른쪽 충돌체크시 y좌표용도

	const int BREAK_X = 24; //위,아래 충돌체크시 x좌표용도
	const int BREAK_UP_Y = 4; //위,아래 충돌체크시 y좌표용도
	const int BREAK_TOO_DOWN_Y = 52; //위,아래 충돌체크시 y좌표용도

	//범인 선택 창
	Sprite* select_thief;

	//이벤트 판단
	bool door = false, hint = false;

	//범인 선택 창
	const int THIEF_BUTTON_X1 = 114;
	const int THIEF_BUTTON_X2 = 433;
	const int THIEF_BUTTON_X3 = 752;
	const int THIEF_BUTTON_Y1 = 368;
	const int THIEF_BUTTON_Y2 = 70;

	const int THIEF_BUTTON_SIZE_X = 160;
	const int THIEF_BUTTON_SIZE_Y = 192;
};
#endif