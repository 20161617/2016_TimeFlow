#include "GAME_SCENE_3.h"
#include "SimpleAudioEngine.h"
#include "MENU_SCENE.h"
#include "Menu_Layer.h"
#include "ExpandLayer.h"
#include "MixLayer.h"
#include "Hint_Layer.h"
#include "GAME_SCENE_4.h"

ExpandMenuLayer* expandLayer3;
MenuLayer* menuLayer3;
MixMenuLayer* mixLayer3;
HintLayer* hintLayer3;

Scene* GameScene3::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene3::create();

	scene->addChild(layer);

	expandLayer3 = ExpandMenuLayer::create();
	expandLayer3->setVisible(false);
	scene->addChild(expandLayer3, 4);

	mixLayer3 = MixMenuLayer::create();
	mixLayer3->setVisible(false);
	scene->addChild(mixLayer3, 4);

	menuLayer3 = MenuLayer::create();
	menuLayer3->setVisible(false);
	scene->addChild(menuLayer3, 5);

	hintLayer3 = HintLayer::create();
	hintLayer3->setVisible(false);
	scene->addChild(hintLayer3, 4);

	//�� ���� ����
	expandLayer3->KnowMapLevel(3);
	mixLayer3->KnowMapLevel(3);
	hintLayer3->findHint(0);
	hintLayer3->findHint(1);
	hintLayer3->findHint(2);

	mixLayer3->expandLayer = expandLayer3;
	mixLayer3->gameScene3 = layer;

	return scene;
}

bool GameScene3::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//����Ʈ ���� �ҷ�����
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Item_get.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/door_open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Mouse_click.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/password.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Safe_Close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Wrong_Answer/mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map3/Corn.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map3/Puzzle_Frame.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map3/Swallow_Water.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map3/TV_Broken.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map3/TV_Noise.wav");
	
	//plist �ҷ�����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Characters/sprites.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Items/Map3/number/closetNum.plist");

	//Ÿ�ϸ� �ҷ�����
	_tileMap = CCTMXTiledMap::create("./Maps/Map3.tmx");
	_background = _tileMap->getLayer("Background3");
	this->addChild(_tileMap, 0);

	//��ǥ����, �÷��̾� ������ǥ �� ������Ʈ �߰�
	playerSpawn = _tileMap->objectGroupNamed("PlayerSpawn3");

	if (playerSpawn == NULL){
		return false;
	}

	ValueMap spawnPoint = playerSpawn->getObject("PlayerSpawnXY3");

	//ĳ���� ���� ��ǥ����
	characterX = spawnPoint["x"].asInt();
	characterY = spawnPoint["y"].asInt();

	//�÷��̾� �����
	playerSprite = Sprite::createWithSpriteFrameName("sprites4.png");
	playerSprite->setPosition(Point(characterX, characterY));
	playerSprite->setTag(11);
	this->addChild(playerSprite, 1, 11);

	communication = Sprite::create("./Layers/communication.png");
	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setOpacity(255);
	communication->setVisible(false);
	this->addChild(communication, 3);

	//�������� ��������Ʈ
	puzzleAfter = Sprite::create("./Items/Map3/puzzleAfter.png");
	puzzleAfter->setPosition(Point(PUZZLE_AFTER_X, PUZZLE_AFTER_Y));
	puzzleAfter->setAnchorPoint(Point::ZERO);
	puzzleAfter->setVisible(false);
	this->addChild(puzzleAfter, 0);

	//�ݰ� ��������Ʈ
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

	//���� ����
	closetLayer = Layer::create();
	closetLayer->setVisible(false);
	this->addChild(closetLayer, 2);

	closetLock = Sprite::create("/Items/Map3/closet.png");
	closetLock->setPosition(Point(Point(512, 384) + Point(0, 114)));
	closetLayer->addChild(closetLock, 2);

	closetNumber1 = Sprite::createWithSpriteFrameName("0.png");
	closetNumber1->setAnchorPoint(Point::ZERO);
	closetNumber1->setPosition(Point(405, 413));
	closetLayer->addChild(closetNumber1, 3);

	closetNumber2 = Sprite::createWithSpriteFrameName("0.png");
	closetNumber2->setAnchorPoint(Point::ZERO);
	closetNumber2->setPosition(Point(455, 413));
	closetLayer->addChild(closetNumber2, 3);

	closetNumber3 = Sprite::createWithSpriteFrameName("0.png");
	closetNumber3->setAnchorPoint(Point::ZERO);
	closetNumber3->setPosition(Point(505, 413));
	closetLayer->addChild(closetNumber3, 3);

	closetNumber4 = Sprite::createWithSpriteFrameName("0.png");
	closetNumber4->setAnchorPoint(Point::ZERO);
	closetNumber4->setPosition(Point(555, 413));
	closetLayer->addChild(closetNumber4, 3);

	//Ƽ�� �μ��� ��������Ʈ
	brokenTV = Sprite::create("./Items/Map3/broken_tv.png");
	brokenTV->setPosition(Point(967, 846));
	brokenTV->setAnchorPoint(Point::ZERO);
	brokenTV->setVisible(false);
	this->addChild(brokenTV, 0);

	//���� ����
	frameCutIn = Sprite::create("./Items/Map3/puzzle2.png");
	frameCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	frameCutIn->setVisible(false);
	this->addChild(frameCutIn, 2);

	//�޴��� ����
	cellphoneLockCutIn = Sprite::create("./Items/Map3/phone_lock.png");
	cellphoneLockCutIn->setPosition(Point(playerSprite->getPosition()));
	cellphoneLockCutIn->setVisible(false);
	this->addChild(cellphoneLockCutIn, 2);

	star1C = Sprite::create("./Items/Map3/starC.png");
	star1C->setPosition(Point::ZERO);
	star1C->setVisible(false);
	this->addChild(star1C, 2);

	star2C = Sprite::create("./Items/Map3/starC.png");
	star2C->setPosition(Point::ZERO);
	star2C->setVisible(false);
	this->addChild(star2C, 2);

	star3C = Sprite::create("./Items/Map3/starC.png");
	star3C->setPosition(Point::ZERO);
	star3C->setVisible(false);
	this->addChild(star3C, 2);

	star4C = Sprite::create("./Items/Map3/starC.png");
	star4C->setPosition(Point::ZERO);
	star4C->setVisible(false);
	this->addChild(star4C, 2);

	this->schedule(schedule_selector(GameScene3::CallEveryFrame));

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene3::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene3::onKeyReleased, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene3::onMouseDown, this);
    // regist listener to dispatcher
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	Director::getInstance()->resume();

	return true;
}

CCPoint GameScene3::tileCoordForPosition(CCPoint position){
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height* _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

void GameScene3::setViewPointCenter(CCPoint position){
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

void GameScene3::CallCommunicationWindow(std::string info){

	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setVisible(true);

	Texts = Label::createWithTTF(info, "./Moris.ttf", 30, Size(630, 150));
	Texts->setPosition(playerSprite->getPosition() + Point(0, -262));
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

void GameScene3::BackCommunicationWindow(){
	communication->setVisible(false);
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

void GameScene3::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

void GameScene3::changeGameScene4_R(Ref *sender){
	auto scene = TransitionFade::create(3, GameScene4::createScene());
	Director::getInstance()->replaceScene(scene);
}

bool GameScene3::knowEvent(int mapLevel, int eventCode){
	if (mapLevel == 3){
		if (eventCode == 1){
			return makeHammer = true;
		}
	}
	return 0;
}
void GameScene3::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	auto sprPlayer = (Sprite*)this->getChildByTag(11);

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{
		checkLeft = true, Go_Left = true;

		if (Go_Event == false){
			TV = false, cup = false, puzzleFrame = false;
			clothes = false, closet = false, cornBox = false, tomatoBox = false;
			door = false, puzzlePiece = false;
		}

		//������ �׼� ����
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//������ �ִϸ��̼� ����
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//�������� �̵��ϴ� �׼�
		auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
		sprPlayer->runAction(action2);

		//����Ű�� �������������� �ִϸ��̼�
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 5; i < 9; i++){
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(21);//���� �ִϸ��̼�
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{
		checkRight = true, Go_Right = true;

		if (Go_Event == false) {
			TV = false, cup = false, puzzleFrame = false;
			clothes = false, closet = false, cornBox = false, tomatoBox = false;
			door = false, puzzlePiece = false;
		}

		//������ �׼� ����
		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionW);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//������ �ִϸ��̼� ����
		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionW = (Action*)sprPlayer->getActionByTag(23);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionW);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//���������� �̵��ϴ� �׼�
		auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
		sprPlayer->runAction(action2);

		//������Ű�� ���������� ����Ǵ� �ִϸ��̼�
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 9; i < 13; i++)	{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(22);//������ �ִϸ��̼�
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{

		checkUp = true, Go_Up = true;

		if (Go_Event == false) {
			TV = false, cup = false, puzzleFrame = false;
			clothes = false, closet = false, cornBox = false, tomatoBox = false;
			door = false, puzzlePiece = false;
		}

		//������ �׼� ����
		auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(actionA);
		auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(actionD);
		auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(actionS);
		//������ �ִϸ��̼� ����
		auto animationActionA = (Action*)sprPlayer->getActionByTag(21);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(animationActionA);
		auto animationActionD = (Action*)sprPlayer->getActionByTag(22);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(animationActionD);
		auto animationActionS = (Action*)sprPlayer->getActionByTag(24);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(animationActionS);

		//ĳ���� �̵�
		auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
		sprPlayer->runAction(action2);

		//����Ű�� ���������� �ִϸ��̼�
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 13; i < 17; i++)
		{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);
		auto action = RepeatForever::create(animate);
		action->setTag(23);//���� �ִϸ��̼�
		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{
		checkDown = true, Go_Down = true;

		if (Go_Event == false){
			TV = false, cup = false, puzzleFrame = false;
			clothes = false, closet = false, cornBox = false, tomatoBox = false;
			door = false, puzzlePiece = false;
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

		//ĳ���� �̵� �׼�
		auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
		auto action2 = RepeatForever::create(action1);
		action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
		sprPlayer->runAction(action2);

		//�Ʒ���Ű�� ���������� ĳ���� �ִϸ��̼�
		auto animation = Animation::create();
		animation->setDelayPerUnit(ANI_SPEED);

		for (int i = 1; i < 5; i++)
		{
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
			animation->addSpriteFrame(frame);
		}

		auto animate = Animate::create(animation);

		auto action = RepeatForever::create(animate);
		action->setTag(24);//�Ʒ��� �ִϸ��̼�

		sprPlayer->runAction(action);

		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:{
		if (Go_Menu == false){
			Go_Menu = true;
			menuLayer3->setPosition(Point::ZERO);
			menuLayer3->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
			Director::getInstance()->pause();
		}
		else if (Go_Menu == true)	{
			menuLayer3->setVisible(false);
			Go_Menu = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:{
		if (Go_Menu == false && goExpand == false && Go_Event == false){
			if (goMix == true){
				mixLayer3->setVisible(false);
				goMix = false;
			}
			else if (goHint == true){
				hintLayer3->setVisible(false);
				goHint = false;
			}
			goExpand = true;
			expandLayer3->setPosition(Point(Point(512, 384) + Point(0, 114)));
			expandLayer3->setVisible(true);
			mixLayer3->MixLayerOnOff = false;
			hintLayer3->HintLayerOnOff = false;
			expandLayer3->ExpandLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goExpand == true){
			expandLayer3->setVisible(false);
			goExpand = false;
			expandLayer3->ExpandLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_E:{
		if (Go_Menu == false && goMix == false && Go_Event == false){
			if (goExpand == true){
				expandLayer3->setVisible(false);
				goExpand = false;
			}
			else if (goHint == true){
				hintLayer3->setVisible(false);
				goHint = false;
			}
			goMix = true;
			mixLayer3->setPosition(Point(Point(512, 498)));
			mixLayer3->setVisible(true);
			mixLayer3->MixLayerOnOff = true;
			hintLayer3->HintLayerOnOff = false;
			expandLayer3->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goMix == true){
			mixLayer3->setVisible(false);
			goMix = false;
			mixLayer3->MixLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_H:{
		if (Go_Menu == false && goHint == false && Go_Event == false){
			if (goMix == true){
				mixLayer3->setVisible(false);
				goMix = false;
			}
			else if (goExpand == true){
				expandLayer3->setVisible(false);
				goExpand = false;
			}
			goHint = true;
			hintLayer3->setPosition(Point(Point(512, 384) + Point(0, 114)));
			hintLayer3->setVisible(true);
			mixLayer3->MixLayerOnOff = false;
			hintLayer3->HintLayerOnOff = true;
			expandLayer3->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){
			hintLayer3->setVisible(false);
			goHint = false;
			hintLayer3->HintLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{
		if (goExpand == false && goMix == false && Go_Menu == false && Go_Event == false && goHint == false){
			if (TV == true){
				Go_Event = true;
				if (makeHammer == false && TVItem == false){
					GameScene3::CallCommunicationWindow(UTF8("�̻��� ȭ���� ���´�..."));
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map3/TV_Noise.wav");
				}
				else if (makeHammer == true && TVItem == false && cellphoneLocked == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map3/TV_Broken.wav");
					GameScene3::CallCommunicationWindow(UTF8("��ġ�� TV�� �μ̴�.\n�޴����� �߰��ߴ�. ������ ����� Ǯ��� ����� �� ���� �� ����."));
					brokenTV->setVisible(true);
					cellphoneLocked = true;
				}
				else if (makeHammer == true && TVItem == false && cellphoneLocked == true){
					cellphoneLockCutIn->setPosition(Point(playerSprite->getPosition()));
					cellphoneLockCutIn->setVisible(true);
					star1C->setPosition(Point(playerSprite->getPosition() + Point(-40, 124)));
					star2C->setPosition(Point(playerSprite->getPosition() + Point(-6, 124)));
					star3C->setPosition(Point(playerSprite->getPosition() + Point(28, 124)));
					star4C->setPosition(Point(playerSprite->getPosition() + Point(62, 124)));
				}
				else if (makeHammer == true && TVItem == true){
					GameScene3::CallCommunicationWindow(UTF8("���� TV�� �� �� ����."));
				}
				Director::getInstance()->pause();
			}
			else if (cup == true){
				Go_Event = true;
				if (cupItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map3/Swallow_Water.wav");
					GameScene3::CallCommunicationWindow(UTF8("��... �׸� �ȿ� ���� ����ִ�.\n\n\n��ġ �� ���� ȹ���ߴ�."));
					mixLayer3->MapItemEvents(2);
					expandLayer3->MapItemEvents(3, 2);
					cupItem = true;
				}
				else if (cupItem == true){
					GameScene3::CallCommunicationWindow(UTF8("������ �� ���� ���� �� ����."));
				}
					Director::getInstance()->pause();
			}
			else if (puzzleFrame == true){
				Go_Event = true;
				if (makeHammer == false){
					GameScene3::CallCommunicationWindow(UTF8("������ ���� ���ڷ� �ɾ� ���Ҵ�."));
				}
				else if (makeHammer == true && breakFrame == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map3/Puzzle_Frame.mp3");
					GameScene3::CallCommunicationWindow(UTF8("�� �ؿ� ���� ������ ��������, ���ڿ� � ����� ��Ÿ����!"));
					breakFrame = true;
					//���ڸ� �μ��� ���� ���� ����
					puzzleAfter->setVisible(true);
					}
				else if (makeHammer == true && breakFrame == true){
					GameScene3::CallCommunicationWindow(UTF8("��..."));
					frameCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					frameCutIn->setVisible(true);
				}
				Director::getInstance()->pause();
			}
			else if (puzzlePiece == true){
				if (breakFrame == true && puzzleFrameItem == false){
					Go_Event = true;
					expandLayer3->MapItemEvents(3, 4);
					mixLayer3->MapItemEvents(4);
					puzzleFrameItem = true;
					GameScene3::CallCommunicationWindow(UTF8("���� ������ ȹ���ߴ�."));
					puzzleAfter->setVisible(false);
					removeChild(puzzleAfter, true);
					Director::getInstance()->pause();
				}
				else if (breakFrame == true && puzzleFrameItem == true){
					Go_Event = true;
					GameScene3::CallCommunicationWindow(UTF8("�ٴڿ��� �ƹ��͵� ������ �ʴ´�."));
					Director::getInstance()->pause();
				}
			}
			else if (clothes == true){
				Go_Event = true;
				if (clothesItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene3::CallCommunicationWindow(UTF8("�ʿ��� ���� Ƣ��Դ�.\n\n\n����⸦ �ֿ���."));
					mixLayer3->MapItemEvents(1);
					expandLayer3->MapItemEvents(3, 1);
					clothesItem = true;
				}
				else if (clothesItem == true){
					GameScene3::CallCommunicationWindow(UTF8("��� �ô� ���ε�?"));
				}
				Director::getInstance()->pause();
			}
			else if (closet == true){
				Go_Event = true;
				if (closetItem == false){
					GameScene3::CallCommunicationWindow(UTF8("��й�ȣ�� �Է��ϼ���"));
					closetLayer->setPosition(Point(playerSprite->getPosition() - Director::getInstance()->getWinSize() * 0.5));
				    closetLayer->setVisible(true);
				}
				else if (closetItem == true){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Closet_Door_Close.mp3");
					GameScene3::CallCommunicationWindow(UTF8("�� �����̴�."));
				}
				Director::getInstance()->pause();
			}
			else if (cornBox == true){
				Go_Event = true;
				if (eatCorn == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map3/Corn.mp3");
					GameScene3::CallCommunicationWindow(UTF8("�������� ���ƺ��δ� �Ѱ�����...\n\n\n���� ����?"));
					eatCorn = true;
				}
				else if (eatCorn == true){
					if (clockGear3 == false){
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Closet_Door_Safe_Carrier_Open.mp3");
						GameScene3::CallCommunicationWindow(UTF8("��й�ȣ�� �Է��ϼ���."));
						safeSPR->setPosition(Point(playerSprite->getPosition() + Point(0, 114)));
						safeSPR->setVisible(true);
						star1->setPosition(Point(playerSprite->getPosition() + Point(46, 259)));
						star2->setPosition(Point(playerSprite->getPosition() + Point(105, 259)));
						star3->setPosition(Point(playerSprite->getPosition() + Point(164, 259)));
						star4->setPosition(Point(playerSprite->getPosition() + Point(223, 259)));
					}
					else if (clockGear3 == true){
						GameScene3::CallCommunicationWindow(UTF8("�ϳ��� �� ������?"));
					}
				}
				Director::getInstance()->pause();
			}
			else if (tomatoBox == true){
				Go_Event = true;
				GameScene3::CallCommunicationWindow(UTF8("�� ���� �丶����� ����ִ�."));
				Director::getInstance()->pause();
			}
			else if (door == true){
				Go_Event = true;
				if (clockGear3 == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
					GameScene3::CallCommunicationWindow(UTF8("� ��Ϲ����� ã�ƾ� ��."));
				}
				else if (clockGear3 == true){
					GameScene3::CallCommunicationWindow(UTF8("���� ������ � ����."));
				}
				Director::getInstance()->pause();
			}
		}
		else if (Go_Menu == false && Go_Event == true){ //��ȭâ �ݱ�
			if (tomatoBox == true || cup == true || clothes == true){ //�丶�� ����, ��, ��
				Go_Event = false;
				GameScene3::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (TV == true){ //Ƽ��
				Go_Event = false;
				if (makeHammer == false && TVItem == false){ //��ġ ����� ��, Ƽ������� ȹ�� ��
					GameScene3::BackCommunicationWindow();
				}
				else if (makeHammer == true && TVItem == false && cellphoneLocked == false){
					// ��ġ ���� ��, Ƽ������� ȹ�� ��, �޴������ �˱� ��
					GameScene3::BackCommunicationWindow();
				}
				else if (makeHammer == true && TVItem == false && cellphoneLocked == true){
					// ��ġ ���� ��, Ƽ������� ȹ�� ��, �޴������ �� ��
					GameScene3::BackCommunicationWindow();
					cellphoneLockCutIn->setVisible(false);
					star1C->setVisible(false);
					star2C->setVisible(false);
					star3C->setVisible(false);
					star4C->setVisible(false);
					place = 1;
					password1C = NULL;
					password2C = NULL;
					password3C = NULL;
					password4C = NULL;
				}
				else if (makeHammer == true && TVItem == true){ //��ġ ���� ��, Ƽ�� ������ȹ�� ��
					GameScene3::BackCommunicationWindow();
				}
				Director::getInstance()->resume();
			}
			else if (puzzleFrame == true){ //���� ����
				Go_Event = false;
				if (puzzleFrame == true && breakFrame == false){
					GameScene3::BackCommunicationWindow();
				}
				else if (puzzleFrame == true && breakFrame == true){
					GameScene3::BackCommunicationWindow();
					frameCutIn->setVisible(false);
				}
				Director::getInstance()->resume();
			}
			else if (puzzlePiece == true){
				if (puzzleFrameItem == true){
					Go_Event = false;
					GameScene3::BackCommunicationWindow();
					Director::getInstance()->resume();
				}
			}
			else if (closet == true){
				Go_Event = false;
				if (closetItem == false){
					closetLayer->setVisible(false);
					GameScene3::BackCommunicationWindow();
				}
				else if (closetItem == true){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Closet_Door_Close.mp3");
					GameScene3::BackCommunicationWindow();
				}
				Director::getInstance()->resume();
			}
			else if (cornBox == true){
				Go_Event = false;
				if (eatCorn == false){
					GameScene3::BackCommunicationWindow();
				}
				else if (eatCorn == true){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Drawer_close.mp3");
					GameScene3::BackCommunicationWindow();
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
			else if (door == true){
				Go_Event = false;
				if (clockGear3 == false){
					GameScene3::BackCommunicationWindow();
				}
				else if (clockGear3 == true){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
					GameScene3::changeGameScene4_R(this);
				}
				Director::getInstance()->resume();
			}
		}
		break;
	}
	}
}

void GameScene3::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	auto sprPlayer = (Sprite*)this->getChildByTag(11);//PLAYER_SPRITE_TAG

	switch (keyCode){
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{
		Go_Left = false, checkLeft = false;
		checkRightAnimation = false, checkUpAnimation = false, checkDownAnimation = false;

		//ĳ���� �̵� �׼� ����
		auto action = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
		sprPlayer->getActionManager()->removeAction(action);
		//ĳ���� �ִϸ��̼� ����
		auto animationAction = (Action*)sprPlayer->getActionByTag(21);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//ĳ���� ���� ��������Ʈ ����
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites8.png");
		}

		if (checkRight == true && checkRightAnimation != true){//����Ű ���� ������Ű�� ����������

			auto actionD = (Action*)sprPlayer->getActionByTag(17);
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//������ �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){// ����Ű ���� ����Ű�� ����������

			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//����Ű ���� �Ʒ���Ű�� ����������

			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//�Ʒ��� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{
		Go_Right = false, checkRight = false;
		checkLeftAnimation = false, checkDownAnimation = false, checkUpAnimation = false;

		//������ �̵��׼� ����
		auto action = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
		sprPlayer->getActionManager()->removeAction(action);
		//�ִϸ��̼� ����
		auto animationAction = (Action*)sprPlayer->getActionByTag(22);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//ĳ���� ���� ��������Ʈ ����
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites12.png");
		}

		if (checkLeft == true && checkLeftAnimation != true){//������Ű�� ���� ����Ű�� ����������

			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){//������Ű�� ���� ����Ű�� ����������

			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//������Ű�� ���� �Ʒ���Ű�� ����������

			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//�Ʒ��� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{
		Go_Up = false, checkUp = false;
		checkLeftAnimation = false, checkRightAnimation = false, checkDownAnimation = false;

		//ĳ���� �̵� �׼� ����
		auto action = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
		sprPlayer->getActionManager()->removeAction(action);
		//�ִϸ��̼� ����
		auto animationAction = (Action*)sprPlayer->getActionByTag(23);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//ĳ���� ���� ��������Ʈ ����
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites16.png");
		}
		if (checkLeft == true && checkLeftAnimation != true){//����Ű�� ���� ����Ű�� ����������

			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkRight == true && checkRightAnimation != true){//����Ű�� ���� ������Ű�� ����������
			auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//������ �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
			sprPlayer->runAction(action2);
		}
		if (checkDown == true && checkDownAnimation != true){//����Ű�� ���� �Ʒ���Ű�� ����������
			auto actionS = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
			sprPlayer->getActionManager()->removeAction(actionS);

			auto animationActionS = (Action*)sprPlayer->getActionByTag(24);
			sprPlayer->getActionManager()->removeAction(animationActionS);

			checkDownAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 1; i < 5; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(24);//�Ʒ��� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
			sprPlayer->runAction(action2);
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{
		Go_Down = false, checkDown = false;
		checkLeftAnimation = false, checkRightAnimation = false, checkUpAnimation = false;

		//ĳ���� �̵� �׼� ����
		auto action = (Action*)sprPlayer->getActionByTag(19);//(TAG_PLAYER_ACTION_S)
		sprPlayer->getActionManager()->removeAction(action);

		//�ִϸ��̼� ����
		auto animationAction = (Action*)sprPlayer->getActionByTag(24);
		sprPlayer->getActionManager()->removeAction(animationAction);

		//ĳ���� ���� ��������Ʈ ����
		if (checkLeft == false && checkRight == false && checkUp == false && checkDown == false &&
			goExpand == false && goMix == false && Go_Menu == false && Go_Event == false){
			sprPlayer->setSpriteFrame("sprites4.png");
		}

		if (checkLeft == true && checkLeftAnimation != true){//�Ʒ���Ű�� ���� ����Ű�� ����������
			auto actionA = (Action*)sprPlayer->getActionByTag(16);//(TAG_PLAYER_ACTION_A)
			sprPlayer->getActionManager()->removeAction(actionA);

			auto animationActionA = (Action*)sprPlayer->getActionByTag(21);
			sprPlayer->getActionManager()->removeAction(animationActionA);

			checkLeftAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 5; i < 9; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}
			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(21);//���� �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
			sprPlayer->runAction(action2);
		}
		if (checkRight == true && checkRightAnimation != true){//�Ʒ���Ű�� ���� ������Ű�� ����������
			auto actionD = (Action*)sprPlayer->getActionByTag(17);//(TAG_PLAYER_ACTION_D)
			sprPlayer->getActionManager()->removeAction(actionD);

			auto animationActionD = (Action*)sprPlayer->getActionByTag(22);
			sprPlayer->getActionManager()->removeAction(animationActionD);

			checkRightAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 9; i < 13; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(22);//������ �ִϸ��̼�2

			sprPlayer->runAction(action);

			auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
			auto action2 = RepeatForever::create(action1);
			action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
			sprPlayer->runAction(action2);
		}
		if (checkUp == true && checkUpAnimation != true){//�Ʒ���Ű�� ���� ����Ű�� ����������
			auto actionW = (Action*)sprPlayer->getActionByTag(18);//(TAG_PLAYER_ACTION_W)
			sprPlayer->getActionManager()->removeAction(actionW);

			auto animationActionW = (Action*)sprPlayer->getActionByTag(23);
			sprPlayer->getActionManager()->removeAction(animationActionW);

			checkUpAnimation = true;
			auto animation = Animation::create();
			animation->setDelayPerUnit(ANI_SPEED);

			//�ִϸ��̼� ����
			for (int i = 13; i < 17; i++){
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("sprites%d.png", i));
				animation->addSpriteFrame(frame);
			}

			auto animate = Animate::create(animation);
			auto action = RepeatForever::create(animate);
			action->setTag(23);//���� �ִϸ��̼�2

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
void GameScene3::CallEveryFrame(float f){

	auto sprPlayer = (Sprite*)this->getChildByTag(11);
	this->setViewPointCenter(playerSprite->getPosition());

	if (checkLeft){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(-BREAK_TOO_X, BREAK_ZERO_Y));//���ϴ�
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_TOO_X, -BREAK_DOWN_Y));//�»��

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();
		String propertyValue2 = map2["Collidable"].asString();
		String cup1 = map1["Cup"].asString();
		String cup2 = map2["Cup"].asString();
	    String tomatoBox1 = map1["TomatoBox"].asString();
		String tomatoBox2 = map2["TomatoBox"].asString();
		String puzzlePiece1 = map1["PuzzlePiece"].asString();
		String puzzlePiece2 = map2["PuzzlePiece"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(16);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Left = false;
		}
		else{
			if (!Go_Left){
				Go_Left = true;

				auto action1 = MoveBy::create(MOVE_TIME, Point(-SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(16);//Tag_SPRITE_PLAYER_ACTION_A
				sprPlayer->runAction(action2);
			}
		}
		if (cup1.compare("True") == 0 && cup2.compare("True") == 0){
			cup = true;
		}
		if (tomatoBox1.compare("True") == 0 && tomatoBox2.compare("True") == 0){
			tomatoBox = true;
		}
		if (puzzlePiece1.compare("True") == 0 && puzzlePiece2.compare("True") == 0){
			puzzlePiece = true;
		}
	}

	if (checkRight){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_TOO_X, BREAK_ZERO_Y));
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(BREAK_TOO_X, -BREAK_DOWN_Y));

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();
		String propertyValue2 = map2["Collidable"].asString();
		String puzzlePiece1 = map1["PuzzlePiece"].asString();
		String puzzlePiece2 = map2["PuzzlePiece"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(17);

			sprPlayer->getActionManager()->removeAction(action);

			Go_Right = false;
		}
		else{
			if (!Go_Right){
				Go_Right = true;

				auto action1 = MoveBy::create(MOVE_TIME, Point(SPEED, 0));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(17);//Tag_SPRTIE_PLAYER_ACTION_D
				sprPlayer->runAction(action2);
			}
		}
		if (puzzlePiece1.compare("True") == 0 && puzzlePiece2.compare("True") == 0){
			puzzlePiece = true;
		}
	}
	if (checkUp){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, BREAK_UP_Y));
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, BREAK_UP_Y));

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();
		String propertyValue2 = map2["Collidable"].asString();
		String cornBox1 = map1["CornBox"].asString();
		String cornBox2 = map2["CornBox"].asString();
		String tomatoBox1 = map1["TomatoBox"].asString();
		String tomatoBox2 = map2["TomatoBox"].asString();
		String TV1 = map1["TV"].asString();
		String TV2 = map2["TV"].asString();
		String puzzleFrame1 = map1["PuzzleFrame"].asString();
		String puzzleFrame2 = map2["PuzzleFrame"].asString();
		String clothes1 = map1["Clothes"].asString();
		String clothes2 = map2["Clothes"].asString();
		String closet1 = map1["Closet"].asString();
		String closet2 = map2["Closet"].asString();
		String puzzlePiece1 = map1["PuzzlePiece"].asString();
		String puzzlePiece2 = map2["PuzzlePiece"].asString();
		
		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(18);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Up = false;
		}
		else{
			if (!Go_Up){
				Go_Up = true;

				auto action1 = MoveBy::create(MOVE_TIME, Point(0, SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(18);//Tag_SPRTIE_PLAYER_ACTION_W
				sprPlayer->runAction(action2);
			}
		}
		if (cornBox1.compare("True") == 0 && cornBox2.compare("True") == 0){
			cornBox = true;
		}
		if (tomatoBox1.compare("True") == 0 && tomatoBox2.compare("True") == 0){
			tomatoBox = true;
		}
		if (TV1.compare("True") == 0 && TV2.compare("True") == 0){
			TV = true;
		}
		if (puzzleFrame1.compare("True") == 0 && puzzleFrame2.compare("True") == 0){
			puzzleFrame = true;
		}
		if (clothes1.compare("True") == 0 && clothes2.compare("True") == 0){
			clothes = true;
		}
		if (closet1.compare("True") == 0 && closet2.compare("True") == 0){
			closet = true;
		}
		if (puzzlePiece1.compare("True") == 0 && puzzlePiece2.compare("True") == 0){
			puzzlePiece = true;
		}
	}
	if (checkDown){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();

		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, -BREAK_TOO_DOWN_Y));
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, -BREAK_TOO_DOWN_Y));

		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);

		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);

		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();

		String propertyValue1 = map1["Collidable"].asString();
		String propertyValue2 = map2["Collidable"].asString();
		String cup1 = map1["Cup"].asString();
		String cup2 = map2["Cup"].asString();
		String door1 = map1["Door"].asString();
		String door2 = map2["Door"].asString();
		String puzzlePiece1 = map1["PuzzlePiece"].asString();
		String puzzlePiece2 = map2["PuzzlePiece"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(19);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Down = false;
		}
		else{
			if (!Go_Down){
				Go_Down = true;

				auto action1 = MoveBy::create(MOVE_TIME, Point(0, -SPEED));
				auto action2 = RepeatForever::create(action1);
				action2->setTag(19);//Tag_SPRTIE_PLAYER_ACTION_S
				sprPlayer->runAction(action2);
			}
		}
		if (cup1.compare("True") == 0 && cup2.compare("True") == 0){
			cup = true;
		}
		if (door1.compare("True") == 0 && door2.compare("True") == 0){
			door = true;
		}
		if (puzzlePiece1.compare("True") == 0 && puzzlePiece2.compare("True") == 0){
			puzzlePiece = true;
		}
	}
}
//���콺 ���뵵 -> ������
void GameScene3::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;

	Point result = Point(e->getCursorX(), e->getCursorY()); //���콺 Ŀ�� ��ǥ

	//�ݰ� ��ư��ǥ
	Rect button1 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect button2 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect button3 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect button4 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect button5 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect button6 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect button7 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect button8 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect button9 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect buttonC = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect button0 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);
	Rect buttonE = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE);

	//���� ��ư��ǥ
	Rect closetButton1 = Rect(CLOSET_BUTTON_X1, CLOSET_BUTTON_Y1, CLOSET_BUTTON_SIZE, CLOSET_BUTTON_SIZE);
	Rect closetButton2 = Rect(CLOSET_BUTTON_X2, CLOSET_BUTTON_Y1, CLOSET_BUTTON_SIZE, CLOSET_BUTTON_SIZE);
	Rect closetButton3 = Rect(CLOSET_BUTTON_X3, CLOSET_BUTTON_Y1, CLOSET_BUTTON_SIZE, CLOSET_BUTTON_SIZE);
	Rect closetButton4 = Rect(CLOSET_BUTTON_X4, CLOSET_BUTTON_Y1, CLOSET_BUTTON_SIZE, CLOSET_BUTTON_SIZE);

	// �ڵ��� ��ư ��ǥ
	Rect cellphone1R = Rect(CELLPHONE_X1, CELLPHONE_Y1, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphone2R = Rect(CELLPHONE_X2, CELLPHONE_Y1, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphone3R = Rect(CELLPHONE_X3, CELLPHONE_Y1, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphone4R = Rect(CELLPHONE_X1, CELLPHONE_Y2, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphone5R = Rect(CELLPHONE_X2, CELLPHONE_Y2, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphone6R = Rect(CELLPHONE_X3, CELLPHONE_Y2, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphone7R = Rect(CELLPHONE_X1, CELLPHONE_Y3, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphone8R = Rect(CELLPHONE_X2, CELLPHONE_Y3, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphone9R = Rect(CELLPHONE_X3, CELLPHONE_Y3, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphoneCR = Rect(CELLPHONE_X1, CELLPHONE_Y4, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphone0R = Rect(CELLPHONE_X2, CELLPHONE_Y4, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);
	Rect cellphoneER = Rect(CELLPHONE_X3, CELLPHONE_Y4, CELLPHONE_BUTTON_SIZE, CELLPHONE_BUTTON_SIZE);

	//TV�� �μ��� ������ �߰����� ��
	if (Go_Event == true && cellphoneLocked == true && TV == true){
		if (cellphone1R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 1;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 1;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 1;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 1;
				place++;
			}
		}
		if (cellphone2R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 2;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 2;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 2;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 2;
				place++;
			}
		}
		if (cellphone3R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 3;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 3;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 3;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 3;
				place++;
			}
		}
		if (cellphone4R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 4;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 4;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 4;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 4;
				place++;
			}
		}
		if (cellphone5R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 5;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 5;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 5;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 5;
				place++;
			}
		}
		if (cellphone6R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 6;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 6;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 6;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 6;
				place++;
			}
		}
		if (cellphone7R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 7;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 7;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 7;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 7;
				place++;
			}
		}
		if (cellphone8R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 8;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 8;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 8;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 8;
				place++;
			}
		}
		if (cellphone9R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 9;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 9;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 9;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 9;
				place++;
			}
		}
		if (cellphone0R.containsPoint(result)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			if (place == 1){
				star1C->setVisible(true);
				password1C = 0;
				place++;
			}
			else if (place == 2){
				star2C->setVisible(true);
				password2C = 0;
				place++;
			}
			else if (place == 3){
				star3C->setVisible(true);
				password3C = 0;
				place++;
			}
			else if (place == 4){
				star4C->setVisible(true);
				password4C = 0;
				place++;
			}
		}
		if (cellphoneCR.containsPoint(result)){
			place = 1;
			password1C = NULL, password2C = NULL, password3C = NULL, password4C = NULL;
			star1C->setVisible(false);
			star2C->setVisible(false);
			star3C->setVisible(false);
			star4C->setVisible(false);
		}
		if (cellphoneER.containsPoint(result)){
			if (password1C == 2 && password2C == 8 && password3C == 6 && password4C == 4){
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
				GameScene3::BackCommunicationWindow();
				GameScene3::CallCommunicationWindow(UTF8("�޴����� ����� Ǯ����.\n\n\n�޴����� ȹ���ߴ�."));
				cellphoneLockCutIn->setVisible(false);
				star1C->setVisible(false);
				star2C->setVisible(false);
				star3C->setVisible(false);
				star4C->setVisible(false);
				expandLayer3->MapItemEvents(3, 3);
				mixLayer3->MapItemEvents(3);
				TVItem = true;
			}
			else{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Wrong_Answer/mp3");
				star1C->setVisible(false);
				star2C->setVisible(false);
				star3C->setVisible(false);
				star4C->setVisible(false);
				place = 1;
				password1C = NULL;
				password2C = NULL;
				password3C = NULL;
				password4C = NULL;
			}
		}
	}

	//�ݰ� ��ư Ŭ����
	if (Go_Event == true && cornBox == true && eatCorn == true){
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
			if (cornBox == true && password1 == 3 && password2 == 9 && password3 == 6 && password4 == 3){
				safeSPR->setVisible(false);
				star1->setVisible(false);
				star2->setVisible(false);
				star3->setVisible(false);
				star4->setVisible(false);
				BackCommunicationWindow();
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
				GameScene3::CallCommunicationWindow(UTF8("�ݰ��� ��й�ȣ�� Ǯ����.\n\n\n��Ϲ����� ȹ���ߴ�."));
				clockGear3 = true;
				hintLayer3->findHint(3);
			}
			else{
				star1->setVisible(false);
				star2->setVisible(false);
				star3->setVisible(false);
				star4->setVisible(false);
				BackCommunicationWindow();
				CallCommunicationWindow(UTF8("�߸��� ��й�ȣ����."));
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
	else if (closet == true && closetItem == false){
		if (closetButton1.containsPoint(result)){
			if (closetPassWord1 < 9){
				closetPassWord1++;
			}
			else{
				closetPassWord1 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			closetNumber1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%d.png", closetPassWord1)));
		}
		else if (closetButton2.containsPoint(result)){
			if (closetPassWord2 < 9){
				closetPassWord2++;
			}
			else{
				closetPassWord2 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			closetNumber2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%d.png", closetPassWord2)));
		}
		else if (closetButton3.containsPoint(result)){
			if (closetPassWord3 < 9){
				closetPassWord3++;
			}
			else{
				closetPassWord3 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			closetNumber3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%d.png", closetPassWord3)));
		}
		else if (closetButton4.containsPoint(result)){
			if (closetPassWord4 < 9){
				closetPassWord4++;
			}
			else{
				closetPassWord4 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			closetNumber4->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("%d.png", closetPassWord4)));
		}
		if (closetPassWord1 == 1 && closetPassWord2 == 6 && closetPassWord3 == 0 && closetPassWord4 == 3){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
			closetItem = true;
			closetLayer->setVisible(false);
			GameScene3::BackCommunicationWindow();
			GameScene3::CallCommunicationWindow(UTF8("�ڹ��谡 Ǯ�ȴ�.\n\n\n������ ȹ���ߴ�."));
			expandLayer3->MapItemEvents(3, 5);
			mixLayer3->MapItemEvents(5);
		}
	}
}
