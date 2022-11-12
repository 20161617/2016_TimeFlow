#ifndef __GAME_SCENE_4_H__
#define __GAME_SCENE_4_H__

#include "cocos2d.h"
USING_NS_CC;

class GameScene4 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(GameScene4);

	//메뉴 화면으로 돌아가기
	void GameScene4::menuCallback(cocos2d::Ref* sender);
	void changeMenuScene_R(Ref *sender);

	//프레임호출
	void CallEveryFrame(float f);

	//대화창 호출
	void CallCommunicationWindow(std::string info);
	void BackCommunicationWindow();

	//이벤트 발생 받기
	bool GameScene4::knowEvent(int mapLevel, int eventCode);

	//다음맵 넘어가기
	void GameScene4::changeGameScene5_R(Ref *sender);

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

	//확대 활성
	bool goExpand = false;

	//조합 활성
	bool goMix = false;

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

	//이벤트 발생 판단
	bool curtain = false, carrier = false, jar = false, drawer = false;
	bool chair = false, desk = false, teddyBear = false, closet = false;
	bool vanity = false, floor = false, door = false;

	//이벤트 진행
	bool makeHead = false, openCurtain = false, drawerItem = false, useKey = false;
	bool carrierItem = false, jarItem = false, chairItem = false, deskItem = false;
	bool makeCloth = false, makeTeddyBear = false;
	//톱니바퀴, 다음맵 넘어가기 판단
	bool clockGear4 = false;

	//커튼 컷인
	Sprite* curtainCutIn;

	//곰인형 스프라이트 (머리달아주면 나옴)
	Sprite* teddyMake;
	const int TEDDY_X = 768;
	const int TEDDY_Y = 896;

	//캐리어 비밀번호 컷인
	Layer* carrierLayer;
	Sprite* carrierLock;
	Sprite* carrierNumber1;
	Sprite* carrierNumber2;
	Sprite* carrierNumber3;
	Sprite* carrierNumber4;

	int carrierPassWord1 = 0;
	int carrierPassWord2 = 0;
	int carrierPassWord3 = 0;
	int carrierPassWord4 = 0;

	const int CARRIER_BUTTON_X1 = 632;
	const int CARRIER_BUTTON_Y1 = 599;
	const int CARRIER_BUTTON_Y2 = 523;
	const int CARRIER_BUTTON_Y3 = 444;
	const int CARRIER_BUTTON_Y4 = 368;

	const int CARRIER_BUTTON_SIZE_X = 30;
	const int CARRIER_BUTTON_SIZE_Y = 30;
};
#endif