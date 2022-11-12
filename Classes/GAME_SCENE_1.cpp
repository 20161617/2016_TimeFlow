#include "SimpleAudioEngine.h"
#include "GAME_SCENE_1.h"
#include "MENU_SCENE.h"
#include "Menu_Layer.h"
#include "MixLayer.h"
#include "ExpandLayer.h"
#include "win32_kLanguage.h"
#include "Hint_Layer.h"
#include "GAME_SCENE_2.h"

ExpandMenuLayer* expandLayer;
MenuLayer* menuLayer_;
MixMenuLayer* mixLayer;
HintLayer* hintLayer;

Scene* GameScene::createScene(){
	auto scene = Scene::create();

	auto layer = GameScene::create();
	scene->addChild(layer);
	
	//확대 레이어 받아오기
	expandLayer = ExpandMenuLayer::create();
	expandLayer->setVisible(false);
	scene->addChild(expandLayer, 4);

	//조합 레이어 받아오기
	mixLayer = MixMenuLayer::create();
	mixLayer->setVisible(false);
	scene->addChild(mixLayer, 4);

	//메뉴 레이어 받아오기
	menuLayer_ = MenuLayer::create();
	menuLayer_->setVisible(false);
	scene->addChild(menuLayer_, 5);

	//힌트 레이어 받아오기 
	hintLayer = HintLayer::create();
	hintLayer->setVisible(false);
	scene->addChild(hintLayer, 4);

	//맵 레벨 구별
	expandLayer->KnowMapLevel(1);
	mixLayer->KnowMapLevel(1);
	hintLayer->findHint(0);
	return scene;
}

bool GameScene::init(){ 
	
	if (!Layer::init()){
		return false;
	}

	

	//이펙트 사운드 불러오기
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map1/Carpet_Bed.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map1/Pot_onto_Stove.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Item_get.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Drawer_open.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Drawer_close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/door_open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Mouse_click.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/password.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Closet_Door_Safe_Carrier_Open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Safe_Close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("./Effect Music/DDmyzik_-_Sunrise_Piano.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("./Effect Music/DDmyzik_-_Sunrise_Piano.mp3", true);

	//plist 불러오기
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Characters/sprites.plist");
	
	//타일맵 불러오기
	_tileMap = CCTMXTiledMap::create("./Maps/GameMap1.tmx");
	_background = _tileMap->getLayer("Background1");
	this->addChild(_tileMap, 0);

	//좌표생성, 플레이어 스폰좌표 등 오브젝트 추가
	playerSpawn = _tileMap->objectGroupNamed("PlayerSpawn");
	if (playerSpawn == NULL){
		return false;
	}

	ValueMap spawnPoint = playerSpawn->getObject("PlayerSpawnXY");

	//캐릭터 스폰 좌표설정
	characterX = spawnPoint["x"].asInt();
	characterY = spawnPoint["y"].asInt();

	//플레이어 만들기
	playerSprite = Sprite::createWithSpriteFrameName("sprites4.png");
	playerSprite->setPosition(Point(characterX, characterY));
	playerSprite->setTag(11);
	this->addChild(playerSprite, 1, 11);

	//대화창 만들기
	communication = Sprite::create("./Layers/communication.png");
	communication->setPosition(playerSprite->getPosition() + Point(0, -COMMUNICATION_WINDOW_Y));
	communication->setOpacity(255);
	communication->setVisible(false);
	this->addChild(communication, 3);

	//금고 스프라이트
	safeSPR = Sprite::create("./Layers/SAFE2.png");
	safeSPR->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	safeSPR->setVisible(false);
	this->addChild(safeSPR, 2);

	star1 = Sprite::create("./Layers/star.png");
	star1->setPosition(Point(safeStarX1, safeStarY));
	star1->setVisible(false);
	this->addChild(star1, 2);

	star2 = Sprite::create("./Layers/star.png");
	star2->setPosition(Point(safeStarX2, safeStarY));
	star2->setVisible(false);
	this->addChild(star2, 2);

	star3 = Sprite::create("./Layers/star.png");
	star3->setPosition(Point(safeStarX3, safeStarY));
	star3->setVisible(false);
	this->addChild(star3, 2);

	star4 = Sprite::create("./Layers/star.png");
	star4->setPosition(Point(safeStarX4, safeStarY));
	star4->setVisible(false);
	this->addChild(star4, 2);

	//달력, 액자 컷인 스프라이트
	calenderCutIn = Sprite::create("./Items/Map1/calender.png");
	calenderCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	calenderCutIn->setVisible(false);
	this->addChild(calenderCutIn, 2);

	frameCutIn = Sprite::create("./Items/Map1/frame.png");
	frameCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	frameCutIn->setVisible(false);
	this->addChild(frameCutIn, 2);

	//업데이트 1초에 60프레임
	this->schedule(schedule_selector(GameScene::CallEveryFrame));

	//키보드 리스너
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	//마우스 리스너
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);

	// regist listener to dispatcher
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	Director::getInstance()->resume();

	return true;
}

//타일맵
CCPoint GameScene::tileCoordForPosition(CCPoint position){
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height* _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

//카메라
void GameScene::setViewPointCenter(CCPoint position){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	cameraX = MAX(position.x, winSize.width / 2);
	cameraY = MAX(position.y, winSize.height / 2);

	cameraX = MIN(cameraX, (_tileMap->getMapSize().width* _tileMap->getTileSize().width) - winSize.width / 2);
	cameraY = MIN(cameraY, (_tileMap->getMapSize().height* _tileMap->getTileSize().height) - winSize.height / 2);

	CCPoint actualposition = ccp(cameraX, cameraY);
	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualposition);
	this->setPosition(viewPoint);
}

//메뉴씬으로 전환
void GameScene::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

//다음맵으로 전환
void GameScene::changeGameScene2_R(Ref *sender){
	auto scene = TransitionFade::create(3, GameScene2::createScene());
	Director::getInstance()->replaceScene(scene);
}

//대화창 불러오기
void GameScene::CallCommunicationWindow(std::string info){
	
	communication->setPosition(playerSprite->getPosition() + Point(0, -COMMUNICATION_WINDOW_Y));
	communication->setVisible(true);

	Texts = Label::createWithTTF(info, "./Moris.ttf", 30, Size(TALK_SIZE_X, TALK_SIZE_Y));
	Texts->setPosition(playerSprite->getPosition() + Point(0, -TALK_Y));
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

//대화창 내보내기
void GameScene::BackCommunicationWindow(){
	communication->setVisible(false);
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

//키보드 입력
void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	//플레이어 태그
	auto sprPlayer = (Sprite*)this->getChildByTag(11);

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{ //A를 눌렀을때
		checkLeft = true, Go_Left = true;
		
		if (Go_Event == false) { //모든 이벤트 변수 초기화
			door = false, calender = false, frame = false;
			bed = false, rightCarpet = false, leftCarpet = false, flavorDrawer = false;
			foodDrawer = false, gasRange = false, cuttingBoard = false;
		}
		//진행중 액션 삭제
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//진행중 애니메이션 삭제
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//왼쪽으로 이동하는 액션
		auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
		sprPlayer->runAction(action2);
		
		//왼쪽키만 눌려져있을시의 애니메이션
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 5; i < 9; i++){
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(21);//왼쪽 애니메이션
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{ //D를 눌렀을 때
		checkRight = true, Go_Right = true;
		
		if (Go_Event == false) { //모든 이벤트변수 초기화
			door = false, calender = false, frame = false;
			bed = false, rightCarpet = false, leftCarpet = false, flavorDrawer = false;
			foodDrawer = false, gasRange = false, cuttingBoard = false;
		}
		//진행중 액션 삭제
		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//진행중 애니메이션 삭제
		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//오른쪽으로 이동하는 액션
		auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
		sprPlayer->runAction(action2);

		//오른쪽키만 눌려있을때 실행되는 애니메이션
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 9; i < 13; i++)	{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(22);//오른쪽 애니메이션
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{ //W키를 눌렀을 때

		checkUp = true, Go_Up = true;

		if (Go_Event == false) {//이벤트 변수 초기화
			door = false, calender = false, frame = false;
			bed = false, rightCarpet = false, leftCarpet = false, flavorDrawer = false;
			foodDrawer = false, gasRange = false, cuttingBoard = false;
		}
		//진행중 액션 삭제
		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//진행중 애니메이션 삭제
		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//캐릭터 이동
		auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
		sprPlayer->runAction(action2);
		
		//위쪽키만 눌려있을때 애니메이션
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 13; i < 17; i++)
		{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(23);//위쪽 애니메이션
		sprPlayer->runAction(action);
		
        break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{ //S키를 눌렀을 때
		checkDown = true, Go_Down = true;

		if (Go_Event == false) { //이벤트 변수 초기화
			door = false, calender = false, frame = false;
			bed = false, rightCarpet = false, leftCarpet = false, flavorDrawer = false;
			foodDrawer = false, gasRange = false, cuttingBoard = false;
		}

		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);

		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);

		//캐릭터 이동 액션
		auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
		sprPlayer->runAction(action2);

		//아래쪽키만 눌려있을때 캐릭터 애니메이션
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 1; i < 5; i++)
		{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);

		auto action = RepeatForever::create(animate);
		action->setTag(24);//아래쪽 애니메이션

		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:{ //ESC레이어(일시정지, 메뉴)
		if (Go_Menu == false){ //메뉴 창이 꺼져있을때
			Go_Menu = true;
            menuLayer_->setPosition(Point::ZERO);	//레이어 띄우기 
			menuLayer_->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //음악
			Director::getInstance()->pause(); //게임 퍼즈
		}
		else if (Go_Menu == true)	{ //ESC레이어가 활성화 되있을 때
			menuLayer_->setVisible(false); //레이어 숨기기
			Go_Menu = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//다른 창들이 다 꺼져있을 때만 게임 재개
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:{	//확대레이어
		if (Go_Menu == false && goExpand == false && Go_Event == false){	//ESC레이어와 확대 레이어가 비활성화 일때
			if (goMix == true){
				mixLayer->setVisible(false); //조합레이어가 켜져있으면 비활성화시킴
				goMix = false;
			}
			else if (goHint == true){ //힌트레이어가 켜져있으면 비활성화시킴
				hintLayer->setVisible(false);
				goHint = false;
			}
			goExpand = true; //확대 레이어 활성화
			expandLayer->setPosition(Point( Point(512, 384) + Point(0, 114)));
			expandLayer->setVisible(true);
			mixLayer->MixLayerOnOff = false;
			hintLayer->HintLayerOnOff = false;
			expandLayer->ExpandLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goExpand == true){ //확대 레이어가 활성화 일때
			expandLayer->setVisible(false); //확대레이어 비활성화
			goExpand = false;
			expandLayer->ExpandLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//다른 레이어들이 모두 비활성화 일때 개임 재개
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_E:{	//조합레이어
		if (Go_Menu == false && goMix == false && Go_Event == false){
			if (goExpand == true){	//확대레이어 활성화시 비활성화 시킴
				expandLayer->setVisible(false);
				goExpand = false;
			}
			else if (goHint == true){	//힌트레이어 활성화시 비활성화 시킴
				hintLayer->setVisible(false);
				goHint = false;
			}
			goMix = true;	//조합레이어 활성화
			mixLayer->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			mixLayer->setVisible(true);
			mixLayer->MixLayerOnOff = true;
			hintLayer->HintLayerOnOff = false;
			expandLayer->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goMix == true){	//조합레이어 활성화시 비활성화 시키기
			mixLayer->setVisible(false);
			goMix = false;
			mixLayer->MixLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//모든 레이어들이 비활성화일때 게임재개
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_H:{	//힌트레이어
		if (Go_Menu == false && goHint == false && Go_Event == false){
			if (goMix == true){	//조합레이어 활성화시 비활성화시키기
				mixLayer->setVisible(false);
				goMix = false;
			}
			else if (goExpand == true){	//확대레이어 활성화시 비활성화 시키기
				expandLayer->setVisible(false);
				goExpand = false;
			}
			goHint = true;	//힌트레이어 활성화
			hintLayer->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			hintLayer->setVisible(true);
			mixLayer->MixLayerOnOff = false;
			hintLayer->HintLayerOnOff = true;
			expandLayer->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){	//힌트레이어 활성화시 비활성화 시키기
			hintLayer->setVisible(false);
			goHint = false;
			hintLayer->HintLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//모든레이어가 비활성화일시 게임재개
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{	//이벤트 활성화 시키기(이벤트 오브젝트에서만)
		if (goExpand == false && goMix == false && Go_Menu == false && Go_Event == false && goHint == false){
			//모든 레이어가 꺼져있을때만 활성가능하다.
			if (cuttingBoard == true){		//도마
				Go_Event = true;  // 이벤트 활성화
				GameScene::CallCommunicationWindow("요리를 하시다 나가셨나 보다.");
				Director::getInstance()->pause();
			}
			if (gasRange == true){		//가스레인지
				Go_Event = true;  // 이벤트 활성화
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map1/Pot_onto_Stove.mp3");
				GameScene::CallCommunicationWindow("가스레인지 불이 켜지지 않는다");
				Director::getInstance()->pause();
			}
			if (foodDrawer == true){		//음식 수납장, 금고
				Go_Event = true;  // 이벤트 활성화
				if (clockGear1 == false){		//톱니바퀴를 얻기 전
					GameScene::CallCommunicationWindow("비밀번호가 걸려있다..");
					//금고레이어 띄우기
					safeSPR->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					safeSPR->setVisible(true);
					star1->setPosition(Point(playerSprite->getPosition() + Point(safeStarX1, safeStarY)));
					star2->setPosition(Point(playerSprite->getPosition() + Point(safeStarX2, safeStarY)));
					star3->setPosition(Point(playerSprite->getPosition() + Point(safeStarX3, safeStarY)));
					star4->setPosition(Point(playerSprite->getPosition() + Point(safeStarX4, safeStarY)));
				}
				else if (clockGear1 == true){		//톱니바퀴를 얻은 후
					GameScene::CallCommunicationWindow("빵이 들어있다. 하나만 먹을까?");
				}
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Drawer_open.wav");
				Director::getInstance()->pause();
			}
			if (flavorDrawer == true){		//향신료 수납장
				Go_Event = true;  // 이벤트 활성화
				GameScene::CallCommunicationWindow("조미료가 잔뜩 들어있다. 요리를 자주 하시나 보다.");
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Drawer_open.wav");
				Director::getInstance()->pause();
			}
			if (leftCarpet == true){		//좌상단 카펫
				Go_Event = true;  // 이벤트 활성화
				if (leftCarpetItem == false){		//카펫에 있는 아이템 얻기 전
					expandLayer->MapItemEvents(1, 2);
					mixLayer->MapItemEvents(2);
					leftCarpetItem = true;
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene::CallCommunicationWindow("카펫 밑에 무언가 있는듯 하다...\n\n\n쪽지를 발견했다.");
				}
				else if (leftCarpetItem == true){		//카펫에 있는 아이템 얻은 후
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map1/Carpet_Bed.mp3");
					GameScene::CallCommunicationWindow("취향이 독특하신 것 같다.");
				}
				Director::getInstance()->pause();
			}
			if (rightCarpet == true){		//우하단 카펫
				Go_Event = true;  // 이벤트 활성화
				GameScene::CallCommunicationWindow("구름 모양 카펫인가?");
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map1/Carpet_Bed.mp3");
				Director::getInstance()->pause();
			}
			if (bed == true){		//침대
				Go_Event = true;  // 이벤트 활성화
				if (bedItem == false){		//침대 아이템 얻기 전
					expandLayer->MapItemEvents(1, 1);
					mixLayer->MapItemEvents(1);
					bedItem = true;
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene::CallCommunicationWindow("이불 속에 무언가가 있는거 같다...\n\n\n쪽지를 발견했다.");
				}
				else if (bedItem == true){		//침대 아이템 얻은 후
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map1/Carpet_Bed.mp3");
					GameScene::CallCommunicationWindow("이불정리가 되어 있지 않다.");
				}
				Director::getInstance()->pause();
			}
			if (frame == true){		//액자
				Go_Event = true;  // 이벤트 활성화
				GameScene::CallCommunicationWindow("무슨 꽃이지?");
				//액자 컷인 보여주기
				frameCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
				frameCutIn->setVisible(true);
				Director::getInstance()->pause();
			}
			if (calender == true){		//달력
				Go_Event = true;  // 이벤트 활성화
				GameScene::CallCommunicationWindow("아직도 작년 달력이다.");
				//달력 컷인 보여주기
				calenderCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
				calenderCutIn->setVisible(true);
				Director::getInstance()->pause();
			}
			if (door == true){		//문
				Go_Event = true;  // 이벤트 활성화
				if (clockGear1 == false){	//톱니바퀴를 얻기 전
					GameScene::CallCommunicationWindow("분명 무언가가 있을꺼야...");
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
				}
				else if (clockGear1 == true){	//톱니바퀴를 얻은 후
					CallCommunicationWindow("혹시 모르니 다른집도 가보자...");
					nextmap = true;
				}
				Director::getInstance()->pause();
			}
		}
		else if (Go_Menu == false && Go_Event == true){ // 이벤트 활성화 시
		    if (door == true && nextmap == true){// 톱니바퀴를 얻은 후의 문 이벤트
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
					GameScene::changeGameScene2_R(this);
	     	}
			else if (gasRange == true ||cuttingBoard == true || leftCarpet == true ||
				rightCarpet == true || door == true || bed == true){
				//가스레인지, 도마, 좌상단카펫, 우하단카펫, 톱니바퀴 얻기전 문, 침대
				Go_Event = false;
				GameScene::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (calender == true){	// 달력
				calenderCutIn->setVisible(false);	//컷인 숨기기
				Go_Event = false;
				GameScene::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (frame == true){	//액자
				frameCutIn->setVisible(false);	//컷인 숨기기
				Go_Event = false;
				GameScene::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (foodDrawer == true || flavorDrawer == true){//음식 수납장, 향신료 수납장
				Go_Event = false;
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Drawer_close.mp3");
				GameScene::BackCommunicationWindow();
				if (foodDrawer == true){ //음식 수납장(금고) 활성화시->금고 정보 초기화
					safeSPR->setVisible(false);
					star1->setVisible(false);
					star2->setVisible(false);
					star3->setVisible(false);
					star4->setVisible(false);
					blink = 1;
					password1 = NULL;
					password2 = NULL;
					password3 = NULL;
					password4 = NULL;
				}
				Director::getInstance()->resume();
			}
		}
		break;
	}
	}
}

//키입력->키를 땠을때
void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(11);	//플레이어 태그(11)

	switch (keyCode){
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{	//왼쪽키를 땠을 때
		//키 체크, 애니메이션 초기화
		Go_Left = false, checkLeft = false;
		checkRightAnimation = false, checkUpAnimation = false, checkDownAnimation = false;

		//캐릭터 이동 액션 중지
		auto action = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
		sprPlayer->getActionManager()->removeAction(action);
		//캐릭터 애니메이션 중지
		auto animationAction = (Action*)sprPlayer->getActionByTag(21);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//캐릭터 중지 스프라이트 지정
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
				sprPlayer->setSpriteFrame("sprites8.png");
		}

		if (checkRight == true && checkRightAnimation != true){//왼쪽키 땐후 오른쪽키가 눌려있을때

			auto actionD = (Action*)sprPlayer->getActionByTag(17);
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//오른쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){// 왼쪽키 땐후 위쪽키가 눌려있을때

			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//위쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//왼쪽키 땐후 아래쪽키가 눌려있을때

			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//아래쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{//오른쪽 키를 땠을 때
		//체크, 애니메이션 초기화
		Go_Right = false, checkRight = false;
		checkLeftAnimation = false, checkDownAnimation = false, checkUpAnimation = false;

		//오른쪽 이동액션 중지
		auto action = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(action);
		//애니메이션 중지
		auto animationAction = (Action*)sprPlayer->getActionByTag(22);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//캐릭터 중지 스프라이트 지정
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites12.png");
		}

		if (checkLeft == true && checkLeftAnimation != true){//오른쪽키를 땐후 왼쪽키가 눌려있을때

			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//왼쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){//오른쪽키를 땐후 위쪽키가 눌려있을때
			
			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//애니메이션 실행
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//위쪽 애니메이션2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//오른쪽키를 땐후 아래쪽키가 눌려있을때

			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

				checkDownAnimation = true;
				auto animation = Animation::create();
				animation->setDelayPerUnit(ANI_SPEED);

				//애니메이션 실행
				for (int i = 1; i < 5; i++){
					auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
					animation->addSpriteFrame(frame);
				}

				auto animate = Animate::create(animation);
				auto action = RepeatForever::create(animate);
				action->setTag(24);//아래쪽 애니메이션2

				sprPlayer->runAction(action);

				auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
				sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{//위쪽키를 땠을 때
		//체크, 애니메이션 초기화
		Go_Up = false, checkUp = false;
		checkLeftAnimation = false, checkRightAnimation = false, checkDownAnimation = false;

		//캐릭터 이동 액션 중지
		auto action = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(action);
		//애니메이션 중지
		auto animationAction = (Action*)sprPlayer->getActionByTag(23);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//캐릭터 중지 스프라이트 지정
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
				sprPlayer->setSpriteFrame("sprites16.png");
		}
		if (checkLeft == true && checkLeftAnimation != true){//위쪽키를 땐후 왼쪽키가 눌려있을때

			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

				checkLeftAnimation = true;
				auto animation = Animation::create();
				animation->setDelayPerUnit(ANI_SPEED);

				//애니메이션 실행
				for (int i = 5; i < 9; i++){
					auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
					animation->addSpriteFrame(frame);
				}

				auto animate = Animate::create(animation);
				auto action = RepeatForever::create(animate);
				action->setTag(21);//왼쪽 애니메이션2

				sprPlayer->runAction(action);

				auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
				sprPlayer->runAction(action2);
		}
		if (checkRight == true && checkRightAnimation != true){//윗쪽키를 땐후 오른쪽키가 눌려있을때
			auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

				checkRightAnimation = true;
				auto animation = Animation::create();
				animation->setDelayPerUnit(ANI_SPEED);

				//애니메이션 실행
				for (int i = 9; i < 13; i++){
					auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
					animation->addSpriteFrame(frame);
				}

				auto animate = Animate::create(animation);
				auto action = RepeatForever::create(animate);
				action->setTag(22);//오른쪽 애니메이션2

				sprPlayer->runAction(action);

				auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
				sprPlayer->runAction(action2);
	    }
		if (checkDown == true && checkDownAnimation != true){//윗쪽키를 땐후 아래쪽키가 눌려있을때
			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

				checkDownAnimation = true;
				auto animation = Animation::create();
				animation->setDelayPerUnit(ANI_SPEED);

				//애니메이션 실행
				for (int i = 1; i < 5; i++){
					auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
					animation->addSpriteFrame(frame);
				}

				auto animate = Animate::create(animation);
				auto action = RepeatForever::create(animate);
				action->setTag(24);//아래쪽 애니메이션2

				sprPlayer->runAction(action);

				auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
				sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{//아래쪽 키를 땠을때
		//체크, 애니메이션 초기화
		Go_Down = false, checkDown = false;
		checkLeftAnimation = false, checkRightAnimation = false, checkUpAnimation = false;

		//캐릭터 이동 액션 중지
		auto action = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(action);

		//애니메이션 중지
		auto animationAction = (Action*)sprPlayer->getActionByTag(24);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//캐릭터 중지 스프라이트 지정
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
				sprPlayer->setSpriteFrame("sprites4.png");
		}

		if (checkLeft == true && checkLeftAnimation != true){//아래쪽키를 땐후 왼쪽키가 눌려있을때
			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

				checkLeftAnimation = true;
				auto animation = Animation::create();
				animation->setDelayPerUnit(ANI_SPEED);

				//애니메이션 실행
				for (int i = 5; i < 9; i++){
					auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
					animation->addSpriteFrame(frame);
				}
				auto animate = Animate::create(animation);
				auto action = RepeatForever::create(animate);
				action->setTag(21);//왼쪽 애니메이션2

				sprPlayer->runAction(action);

				auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
				sprPlayer->runAction(action2);
		}
		if (checkRight == true && checkRightAnimation != true){//아래쪽키를 땐후 오른쪽키가 눌려있을때
			auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

				checkRightAnimation = true;
				auto animation = Animation::create();
				animation->setDelayPerUnit(ANI_SPEED);

				//애니메이션 실행
				for (int i = 9; i < 13; i++){
					auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
					animation->addSpriteFrame(frame);
				}

				auto animate = Animate::create(animation);
				auto action = RepeatForever::create(animate);
				action->setTag(22);//오른쪽 애니메이션2

				sprPlayer->runAction(action);

				auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
				sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){//아래쪽키를 땐후 위쪽키가 눌려있을때
			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

				checkUpAnimation = true;
				auto animation = Animation::create();
				animation->setDelayPerUnit(ANI_SPEED);

				//애니메이션 실행
				for (int i = 13; i < 17; i++){
					auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
					animation->addSpriteFrame(frame);
				}

				auto animate = Animate::create(animation);
				auto action = RepeatForever::create(animate);
				action->setTag(23);//위쪽 애니메이션2

				sprPlayer->runAction(action);

				auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
				sprPlayer->runAction(action2);
		}
		break;
	}
	}
}

// 1초에 60프레임
void GameScene::CallEveryFrame(float f)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(11); //플레이어 태그
	this->setViewPointCenter(playerSprite->getPosition()); //카메라

	if (checkLeft){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();
		
		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(-BREAK_TOO_X, BREAK_ZERO_Y));//좌상단
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_TOO_X, -BREAK_DOWN_Y));//좌하단
		
		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);
		
		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);
		
		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();
		
		String propertyValue1 = map1["Collidable"].asString();//충돌체크
		String propertyValue2 = map2["Collidable"].asString();
		String LeftCarpet1 = map1["LeftCarpet"].asString();//좌상단 카펫 이벤트
		String LeftCarpet2 = map2["LeftCarpet"].asString();
		String RightCarpet1 = map1["RightCarpet"].asString();//우하단 카펫 이벤트
		String RightCarpet2 = map2["RightCarpet"].asString();
		String Calender1 = map1["Calender"].asString();//달력 이벤트
		String Calender2 = map2["Calender"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(16);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Left = false;
		}
		else{
			if (!Go_Left){
				Go_Left = true;
				//캐릭터 이동 액션
				auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
				sprPlayer->runAction(action2);
			}
		}

		if (LeftCarpet1.compare("True") == 0 && LeftCarpet2.compare("True") == 0){
			leftCarpet = true;
		}
		if (RightCarpet1.compare("True") == 0 && RightCarpet2.compare("True") == 0){
			rightCarpet = true;
		}
		if (Calender1.compare("True") == 0 && Calender2.compare("True") == 0){
			calender = true;
		}
	}

	if (checkRight){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();
		
		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_TOO_X, BREAK_ZERO_Y));//우상단
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(BREAK_TOO_X, -BREAK_DOWN_Y));//우하단
		
		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);
		
		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);
		
		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();
		
		String propertyValue1 = map1["Collidable"].asString();//충돌체크
		String propertyValue2 = map2["Collidable"].asString();
		String LeftCarpet1 = map1["LeftCarpet"].asString();//좌상단 카펫 이벤트
		String LeftCarpet2 = map2["LeftCarpet"].asString();
		String RightCarpet1 = map1["RightCarpet"].asString();//우하단 카펫 이벤트
		String RightCarpet2 = map2["RightCarpet"].asString();
		String Bed1 = map1["Bed"].asString();//침대 이벤트
		String Bed2 = map2["Bed"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(17);

			sprPlayer->getActionManager()->removeAction(action);

			Go_Right = false;
		}
		else{
			if (!Go_Right){
				Go_Right = true;
				//캐릭터 이동 액션
				auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
				sprPlayer->runAction(action2);
			}
		}

		if (LeftCarpet1.compare("True") == 0 && LeftCarpet2.compare("True") == 0){
			leftCarpet = true;
		}
		if (RightCarpet1.compare("True") == 0 && RightCarpet2.compare("True") == 0){
			rightCarpet = true;
		}
		if (Bed1.compare("True") == 0 && Bed2.compare("True") == 0){
			bed = true;
		}
	}
	if (checkUp){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();
		
		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, BREAK_UP_Y));//우상단
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, BREAK_UP_Y));//좌상단
		
		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);
		
		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);
		
		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();
		
		String propertyValue1 = map1["Collidable"].asString();//충돌체크
		String propertyValue2 = map2["Collidable"].asString();
		String CuttingBoard1 = map1["CuttingBoard"].asString();//도마 이벤트
		String CuttingBoard2 = map2["CuttingBoard"].asString();
		String GasRange1 = map1["GasRange"].asString();//가스레인지 이벤트
		String GasRange2 = map2["GasRange"].asString();
		String FlavorDrawer1 = map1["FlavorDrawer"].asString();//향신료 수납장 이벤트
		String FlavorDrawer2 = map2["FlavorDrawer"].asString();
		String FoodDrawer1 = map1["FoodDrawer"].asString();//음식 수납장 이벤트(금고)
		String FoodDrawer2 = map2["FoodDrawer"].asString();
		String Bed1 = map1["Bed"].asString();//침대 이벤트
		String Bed2 = map2["Bed"].asString();
		String Frame1 = map1["Frame"].asString();//액자 이벤트
		String Frame2 = map2["Frame"].asString();
		String LeftCarpet1 = map1["LeftCarpet"].asString();//좌상단 카펫 이벤트
		String LeftCarpet2 = map2["LeftCarpet"].asString();
		String RightCarpet1 = map1["RightCarpet"].asString();//우하단 카펫 이벤트
		String RightCarpet2 = map2["RightCarpet"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(18);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Up = false;
		}
		else{
			if (!Go_Up){
				Go_Up = true;
				//캐릭터 이동 액션 
				auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
				sprPlayer->runAction(action2);
			}
		}

		if (CuttingBoard1.compare("True") == 0 && CuttingBoard2.compare("True") == 0){
			cuttingBoard = true;
		}
		if (GasRange1.compare("True") == 0 && GasRange2.compare("True") == 0){
			gasRange = true;
		}
		if (FlavorDrawer1.compare("True") == 0 && FlavorDrawer2.compare("True") == 0){
			flavorDrawer = true;
		}
		if (FoodDrawer1.compare("True") == 0 && FoodDrawer2.compare("True") == 0){
			foodDrawer = true;
		}
		if (Bed1.compare("True") == 0 && Bed2.compare("True") == 0){
			bed = true;
		}
		if (Frame1.compare("True") == 0 && Frame2.compare("True") == 0){
			frame = true;
		}
		if (LeftCarpet1.compare("True") == 0 && LeftCarpet2.compare("True") == 0){
			leftCarpet = true;
		}
		if (RightCarpet1.compare("True") == 0 && RightCarpet2.compare("True") == 0){
			rightCarpet = true;
		}
	}
	if (checkDown){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();
		
		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, -BREAK_TOO_DOWN_Y));//우하단
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, -BREAK_TOO_DOWN_Y));//좌하단
		
		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);
		
		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);
		
		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();
		
		String propertyValue1 = map1["Collidable"].asString();//충돌체크
		String propertyValue2 = map2["Collidable"].asString();
		String LeftCarpet1 = map1["LeftCarpet"].asString();//좌상단 카펫 이벤트
		String LeftCarpet2 = map2["LeftCarpet"].asString();
		String RightCarpet1 = map1["RightCarpet"].asString();//우하단 카펫 이벤트
		String RightCarpet2 = map2["RightCarpet"].asString();
		String Door1 = map1["Door"].asString();//문 이벤트
		String Door2 = map2["Door"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(19);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Down = false;
		}
		else{
			if (!Go_Down){
				Go_Down = true;
				//캐릭터 이동 액션
				auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
				sprPlayer->runAction(action2);
			}
		}
		if (LeftCarpet1.compare("True") == 0 && LeftCarpet2.compare("True") == 0){
			leftCarpet = true;
		}
		if (RightCarpet1.compare("True") == 0 && RightCarpet2.compare("True") == 0){
			rightCarpet = true;
		}
		if (Door1.compare("True") == 0 && Door2.compare("True") == 0){
			door = true;
		}
	}

}

//마우스 사용용도 -> 선택지
void GameScene::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;
	
	Point result = Point(e->getCursorX(), e->getCursorY());
	//마우스 커서 위치 받기

	Rect button1 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 1번 버튼
	Rect button2 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 2번 버튼
	Rect button3 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 3번 버튼
	Rect button4 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 4번 버튼
	Rect button5 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 5번 버튼
	Rect button6 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 6번 버튼
	Rect button7 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 7번 버튼
	Rect button8 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 8번 버튼
	Rect button9 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 9번 버튼 
	Rect buttonC = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 C번 버튼
	Rect button0 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 0번 버튼
	Rect buttonE = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //금고 E번 버튼

	/*
	시스템 구성

	버튼을 누르면 blink변수가 1씩 증가한다 이걸로 비밀번호의 위치를 알아낸다.
	4개를 다 입력했을 때 다르면 다 초기화 맞을 시 아이템 획득

	C버튼 누를시 번호 초기화 -> 지우개 버튼
	E버튼 누를시 번호 입력 ->맞는 번호인지 판단
	*/
	if (foodDrawer == true && Go_Event == true){ //음식 수납장(금고) 이벤트 활성화 시
		if (button1.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 1;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 1;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 1;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 1;
				blink++;
			}
		}
		if (button2.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 2;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 2;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 2;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 2;
				blink++;
			}

		}
		if (button3.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3"); 
			if (blink == 1){
				star1->setVisible(true);
				password1 = 3;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 3;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 3;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 3;
				blink++;
			}
		}
		if (button4.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 4;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 4;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 4;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 4;
				blink++;
			}
		}
		if (button5.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 5;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 5;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 5;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 5;
				blink++;
			}
		}
		if (button6.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 6;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 6;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 6;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 6;
				blink++;
			}
		}
		if (button7.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 7;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 7;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 7;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 7;
				blink++;
			}
		}
		if (button8.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 8;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 8;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 8;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 8;
				blink++;
			}
		}
		if (button9.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 9;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 9;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 9;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 9;
				blink++;
			}
		}
		if (button0.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (blink == 1){
				star1->setVisible(true);
				password1 = 0;
				blink++;
			}
			else if (blink == 2){
				star2->setVisible(true);
				password2 = 0;
				blink++;
			}
			else if (blink == 3){
				star3->setVisible(true);
				password3 = 0;
				blink++;
			}
			else if (blink == 4){
				star4->setVisible(true);
				password4 = 0;
				blink++;
			}
		}
		if (buttonC.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			blink = 1;
			password1 = NULL, password2 = NULL, password3 = NULL, password4 = NULL;
			star1->setVisible(false);
			star2->setVisible(false);
			star3->setVisible(false);
			star4->setVisible(false);
		}
		if (buttonE.containsPoint(result)){
			if (password1 == 1 && password2 == 6 && password3 == 7 && password4 == 3){
				safeSPR->setVisible(false);
				star1->setVisible(false);
				star2->setVisible(false);
				star3->setVisible(false);
				star4->setVisible(false);
				hintLayer->findHint(1);
				clockGear1 = true;
				BackCommunicationWindow();
				CallCommunicationWindow("금고를 열었다. \n\n\n톱니바퀴를 획득했다.");
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
			}
			else{
				star1->setVisible(false);
				star2->setVisible(false);
				star3->setVisible(false);
				star4->setVisible(false);
				BackCommunicationWindow();
				CallCommunicationWindow("잘못된 비밀번호였다.");
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Safe_Close.mp3");
			}
			blink = 1;
			password1 = NULL;
			password2 = NULL;
			password3 = NULL;
			password4 = NULL;
			star1->setVisible(false);
			star2->setVisible(false);
			star3->setVisible(false);
			star4->setVisible(false);
		}
	}
}

