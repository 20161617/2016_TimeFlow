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
	
	//Ȯ�� ���̾� �޾ƿ���
	expandLayer = ExpandMenuLayer::create();
	expandLayer->setVisible(false);
	scene->addChild(expandLayer, 4);

	//���� ���̾� �޾ƿ���
	mixLayer = MixMenuLayer::create();
	mixLayer->setVisible(false);
	scene->addChild(mixLayer, 4);

	//�޴� ���̾� �޾ƿ���
	menuLayer_ = MenuLayer::create();
	menuLayer_->setVisible(false);
	scene->addChild(menuLayer_, 5);

	//��Ʈ ���̾� �޾ƿ��� 
	hintLayer = HintLayer::create();
	hintLayer->setVisible(false);
	scene->addChild(hintLayer, 4);

	//�� ���� ����
	expandLayer->KnowMapLevel(1);
	mixLayer->KnowMapLevel(1);
	hintLayer->findHint(0);
	return scene;
}

bool GameScene::init(){ 
	
	if (!Layer::init()){
		return false;
	}

	

	//����Ʈ ���� �ҷ�����
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

	//plist �ҷ�����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Characters/sprites.plist");
	
	//Ÿ�ϸ� �ҷ�����
	_tileMap = CCTMXTiledMap::create("./Maps/GameMap1.tmx");
	_background = _tileMap->getLayer("Background1");
	this->addChild(_tileMap, 0);

	//��ǥ����, �÷��̾� ������ǥ �� ������Ʈ �߰�
	playerSpawn = _tileMap->objectGroupNamed("PlayerSpawn");
	if (playerSpawn == NULL){
		return false;
	}

	ValueMap spawnPoint = playerSpawn->getObject("PlayerSpawnXY");

	//ĳ���� ���� ��ǥ����
	characterX = spawnPoint["x"].asInt();
	characterY = spawnPoint["y"].asInt();

	//�÷��̾� �����
	playerSprite = Sprite::createWithSpriteFrameName("sprites4.png");
	playerSprite->setPosition(Point(characterX, characterY));
	playerSprite->setTag(11);
	this->addChild(playerSprite, 1, 11);

	//��ȭâ �����
	communication = Sprite::create("./Layers/communication.png");
	communication->setPosition(playerSprite->getPosition() + Point(0, -COMMUNICATION_WINDOW_Y));
	communication->setOpacity(255);
	communication->setVisible(false);
	this->addChild(communication, 3);

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

	//�޷�, ���� ���� ��������Ʈ
	calenderCutIn = Sprite::create("./Items/Map1/calender.png");
	calenderCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	calenderCutIn->setVisible(false);
	this->addChild(calenderCutIn, 2);

	frameCutIn = Sprite::create("./Items/Map1/frame.png");
	frameCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	frameCutIn->setVisible(false);
	this->addChild(frameCutIn, 2);

	//������Ʈ 1�ʿ� 60������
	this->schedule(schedule_selector(GameScene::CallEveryFrame));

	//Ű���� ������
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);

	//���콺 ������
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);

	// regist listener to dispatcher
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	Director::getInstance()->resume();

	return true;
}

//Ÿ�ϸ�
CCPoint GameScene::tileCoordForPosition(CCPoint position){
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height* _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

//ī�޶�
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

//�޴������� ��ȯ
void GameScene::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

//���������� ��ȯ
void GameScene::changeGameScene2_R(Ref *sender){
	auto scene = TransitionFade::create(3, GameScene2::createScene());
	Director::getInstance()->replaceScene(scene);
}

//��ȭâ �ҷ�����
void GameScene::CallCommunicationWindow(std::string info){
	
	communication->setPosition(playerSprite->getPosition() + Point(0, -COMMUNICATION_WINDOW_Y));
	communication->setVisible(true);

	Texts = Label::createWithTTF(info, "./Moris.ttf", 30, Size(TALK_SIZE_X, TALK_SIZE_Y));
	Texts->setPosition(playerSprite->getPosition() + Point(0, -TALK_Y));
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

//��ȭâ ��������
void GameScene::BackCommunicationWindow(){
	communication->setVisible(false);
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

//Ű���� �Է�
void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	//�÷��̾� �±�
	auto sprPlayer = (Sprite*)this->getChildByTag(11);

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{ //A�� ��������
		checkLeft = true, Go_Left = true;
		
		if (Go_Event == false) { //��� �̺�Ʈ ���� �ʱ�ȭ
			door = false, calender = false, frame = false;
			bed = false, rightCarpet = false, leftCarpet = false, flavorDrawer = false;
			foodDrawer = false, gasRange = false, cuttingBoard = false;
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
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{ //D�� ������ ��
		checkRight = true, Go_Right = true;
		
		if (Go_Event == false) { //��� �̺�Ʈ���� �ʱ�ȭ
			door = false, calender = false, frame = false;
			bed = false, rightCarpet = false, leftCarpet = false, flavorDrawer = false;
			foodDrawer = false, gasRange = false, cuttingBoard = false;
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
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{ //WŰ�� ������ ��

		checkUp = true, Go_Up = true;

		if (Go_Event == false) {//�̺�Ʈ ���� �ʱ�ȭ
			door = false, calender = false, frame = false;
			bed = false, rightCarpet = false, leftCarpet = false, flavorDrawer = false;
			foodDrawer = false, gasRange = false, cuttingBoard = false;
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
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{ //SŰ�� ������ ��
		checkDown = true, Go_Down = true;

		if (Go_Event == false) { //�̺�Ʈ ���� �ʱ�ȭ
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
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:{ //ESC���̾�(�Ͻ�����, �޴�)
		if (Go_Menu == false){ //�޴� â�� ����������
			Go_Menu = true;
            menuLayer_->setPosition(Point::ZERO);	//���̾� ���� 
			menuLayer_->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //����
			Director::getInstance()->pause(); //���� ����
		}
		else if (Go_Menu == true)	{ //ESC���̾ Ȱ��ȭ ������ ��
			menuLayer_->setVisible(false); //���̾� �����
			Go_Menu = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//�ٸ� â���� �� �������� ���� ���� �簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:{	//Ȯ�뷹�̾�
		if (Go_Menu == false && goExpand == false && Go_Event == false){	//ESC���̾�� Ȯ�� ���̾ ��Ȱ��ȭ �϶�
			if (goMix == true){
				mixLayer->setVisible(false); //���շ��̾ ���������� ��Ȱ��ȭ��Ŵ
				goMix = false;
			}
			else if (goHint == true){ //��Ʈ���̾ ���������� ��Ȱ��ȭ��Ŵ
				hintLayer->setVisible(false);
				goHint = false;
			}
			goExpand = true; //Ȯ�� ���̾� Ȱ��ȭ
			expandLayer->setPosition(Point( Point(512, 384) + Point(0, 114)));
			expandLayer->setVisible(true);
			mixLayer->MixLayerOnOff = false;
			hintLayer->HintLayerOnOff = false;
			expandLayer->ExpandLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goExpand == true){ //Ȯ�� ���̾ Ȱ��ȭ �϶�
			expandLayer->setVisible(false); //Ȯ�뷹�̾� ��Ȱ��ȭ
			goExpand = false;
			expandLayer->ExpandLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//�ٸ� ���̾���� ��� ��Ȱ��ȭ �϶� ���� �簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_E:{	//���շ��̾�
		if (Go_Menu == false && goMix == false && Go_Event == false){
			if (goExpand == true){	//Ȯ�뷹�̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ŵ
				expandLayer->setVisible(false);
				goExpand = false;
			}
			else if (goHint == true){	//��Ʈ���̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ŵ
				hintLayer->setVisible(false);
				goHint = false;
			}
			goMix = true;	//���շ��̾� Ȱ��ȭ
			mixLayer->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			mixLayer->setVisible(true);
			mixLayer->MixLayerOnOff = true;
			hintLayer->HintLayerOnOff = false;
			expandLayer->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goMix == true){	//���շ��̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
			mixLayer->setVisible(false);
			goMix = false;
			mixLayer->MixLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//��� ���̾���� ��Ȱ��ȭ�϶� �����簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_H:{	//��Ʈ���̾�
		if (Go_Menu == false && goHint == false && Go_Event == false){
			if (goMix == true){	//���շ��̾� Ȱ��ȭ�� ��Ȱ��ȭ��Ű��
				mixLayer->setVisible(false);
				goMix = false;
			}
			else if (goExpand == true){	//Ȯ�뷹�̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
				expandLayer->setVisible(false);
				goExpand = false;
			}
			goHint = true;	//��Ʈ���̾� Ȱ��ȭ
			hintLayer->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			hintLayer->setVisible(true);
			mixLayer->MixLayerOnOff = false;
			hintLayer->HintLayerOnOff = true;
			expandLayer->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){	//��Ʈ���̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
			hintLayer->setVisible(false);
			goHint = false;
			hintLayer->HintLayerOnOff = false;
			if (Go_Menu == false && goExpand == false && goMix == false && Go_Event == false && goHint == false){
				//��緹�̾ ��Ȱ��ȭ�Ͻ� �����簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{	//�̺�Ʈ Ȱ��ȭ ��Ű��(�̺�Ʈ ������Ʈ������)
		if (goExpand == false && goMix == false && Go_Menu == false && Go_Event == false && goHint == false){
			//��� ���̾ ������������ Ȱ�������ϴ�.
			if (cuttingBoard == true){		//����
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				GameScene::CallCommunicationWindow("�丮�� �Ͻô� �����̳� ����.");
				Director::getInstance()->pause();
			}
			if (gasRange == true){		//����������
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map1/Pot_onto_Stove.mp3");
				GameScene::CallCommunicationWindow("���������� ���� ������ �ʴ´�");
				Director::getInstance()->pause();
			}
			if (foodDrawer == true){		//���� ������, �ݰ�
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				if (clockGear1 == false){		//��Ϲ����� ��� ��
					GameScene::CallCommunicationWindow("��й�ȣ�� �ɷ��ִ�..");
					//�ݰ��̾� ����
					safeSPR->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					safeSPR->setVisible(true);
					star1->setPosition(Point(playerSprite->getPosition() + Point(safeStarX1, safeStarY)));
					star2->setPosition(Point(playerSprite->getPosition() + Point(safeStarX2, safeStarY)));
					star3->setPosition(Point(playerSprite->getPosition() + Point(safeStarX3, safeStarY)));
					star4->setPosition(Point(playerSprite->getPosition() + Point(safeStarX4, safeStarY)));
				}
				else if (clockGear1 == true){		//��Ϲ����� ���� ��
					GameScene::CallCommunicationWindow("���� ����ִ�. �ϳ��� ������?");
				}
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Drawer_open.wav");
				Director::getInstance()->pause();
			}
			if (flavorDrawer == true){		//��ŷ� ������
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				GameScene::CallCommunicationWindow("���̷ᰡ �ܶ� ����ִ�. �丮�� ���� �Ͻó� ����.");
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Drawer_open.wav");
				Director::getInstance()->pause();
			}
			if (leftCarpet == true){		//�»�� ī��
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				if (leftCarpetItem == false){		//ī�꿡 �ִ� ������ ��� ��
					expandLayer->MapItemEvents(1, 2);
					mixLayer->MapItemEvents(2);
					leftCarpetItem = true;
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene::CallCommunicationWindow("ī�� �ؿ� ���� �ִµ� �ϴ�...\n\n\n������ �߰��ߴ�.");
				}
				else if (leftCarpetItem == true){		//ī�꿡 �ִ� ������ ���� ��
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map1/Carpet_Bed.mp3");
					GameScene::CallCommunicationWindow("������ ��Ư�Ͻ� �� ����.");
				}
				Director::getInstance()->pause();
			}
			if (rightCarpet == true){		//���ϴ� ī��
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				GameScene::CallCommunicationWindow("���� ��� ī���ΰ�?");
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map1/Carpet_Bed.mp3");
				Director::getInstance()->pause();
			}
			if (bed == true){		//ħ��
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				if (bedItem == false){		//ħ�� ������ ��� ��
					expandLayer->MapItemEvents(1, 1);
					mixLayer->MapItemEvents(1);
					bedItem = true;
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene::CallCommunicationWindow("�̺� �ӿ� ���𰡰� �ִ°� ����...\n\n\n������ �߰��ߴ�.");
				}
				else if (bedItem == true){		//ħ�� ������ ���� ��
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map1/Carpet_Bed.mp3");
					GameScene::CallCommunicationWindow("�̺������� �Ǿ� ���� �ʴ�.");
				}
				Director::getInstance()->pause();
			}
			if (frame == true){		//����
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				GameScene::CallCommunicationWindow("���� ������?");
				//���� ���� �����ֱ�
				frameCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
				frameCutIn->setVisible(true);
				Director::getInstance()->pause();
			}
			if (calender == true){		//�޷�
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				GameScene::CallCommunicationWindow("������ �۳� �޷��̴�.");
				//�޷� ���� �����ֱ�
				calenderCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
				calenderCutIn->setVisible(true);
				Director::getInstance()->pause();
			}
			if (door == true){		//��
				Go_Event = true;  // �̺�Ʈ Ȱ��ȭ
				if (clockGear1 == false){	//��Ϲ����� ��� ��
					GameScene::CallCommunicationWindow("�и� ���𰡰� ��������...");
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
				}
				else if (clockGear1 == true){	//��Ϲ����� ���� ��
					CallCommunicationWindow("Ȥ�� �𸣴� �ٸ����� ������...");
					nextmap = true;
				}
				Director::getInstance()->pause();
			}
		}
		else if (Go_Menu == false && Go_Event == true){ // �̺�Ʈ Ȱ��ȭ ��
		    if (door == true && nextmap == true){// ��Ϲ����� ���� ���� �� �̺�Ʈ
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
					GameScene::changeGameScene2_R(this);
	     	}
			else if (gasRange == true ||cuttingBoard == true || leftCarpet == true ||
				rightCarpet == true || door == true || bed == true){
				//����������, ����, �»��ī��, ���ϴ�ī��, ��Ϲ��� ����� ��, ħ��
				Go_Event = false;
				GameScene::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (calender == true){	// �޷�
				calenderCutIn->setVisible(false);	//���� �����
				Go_Event = false;
				GameScene::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (frame == true){	//����
				frameCutIn->setVisible(false);	//���� �����
				Go_Event = false;
				GameScene::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (foodDrawer == true || flavorDrawer == true){//���� ������, ��ŷ� ������
				Go_Event = false;
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Drawer_close.mp3");
				GameScene::BackCommunicationWindow();
				if (foodDrawer == true){ //���� ������(�ݰ�) Ȱ��ȭ��->�ݰ� ���� �ʱ�ȭ
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

//Ű�Է�->Ű�� ������
void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(11);	//�÷��̾� �±�(11)

	switch (keyCode){
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{	//����Ű�� ���� ��
		//Ű üũ, �ִϸ��̼� �ʱ�ȭ
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
	case cocos2d::EventKeyboard::KeyCode::KEY_D:{//������ Ű�� ���� ��
		//üũ, �ִϸ��̼� �ʱ�ȭ
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
	case cocos2d::EventKeyboard::KeyCode::KEY_W:{//����Ű�� ���� ��
		//üũ, �ִϸ��̼� �ʱ�ȭ
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
	case cocos2d::EventKeyboard::KeyCode::KEY_S:{//�Ʒ��� Ű�� ������
		//üũ, �ִϸ��̼� �ʱ�ȭ
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

// 1�ʿ� 60������
void GameScene::CallEveryFrame(float f)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(11); //�÷��̾� �±�
	this->setViewPointCenter(playerSprite->getPosition()); //ī�޶�

	if (checkLeft){
		CCPoint playerPos1 = sprPlayer->getPosition();
		CCPoint playerPos2 = sprPlayer->getPosition();
		
		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(-BREAK_TOO_X, BREAK_ZERO_Y));//�»��
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_TOO_X, -BREAK_DOWN_Y));//���ϴ�
		
		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);
		
		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);
		
		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();
		
		String propertyValue1 = map1["Collidable"].asString();//�浹üũ
		String propertyValue2 = map2["Collidable"].asString();
		String LeftCarpet1 = map1["LeftCarpet"].asString();//�»�� ī�� �̺�Ʈ
		String LeftCarpet2 = map2["LeftCarpet"].asString();
		String RightCarpet1 = map1["RightCarpet"].asString();//���ϴ� ī�� �̺�Ʈ
		String RightCarpet2 = map2["RightCarpet"].asString();
		String Calender1 = map1["Calender"].asString();//�޷� �̺�Ʈ
		String Calender2 = map2["Calender"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(16);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Left = false;
		}
		else{
			if (!Go_Left){
				Go_Left = true;
				//ĳ���� �̵� �׼�
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
		
		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_TOO_X, BREAK_ZERO_Y));//����
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(BREAK_TOO_X, -BREAK_DOWN_Y));//���ϴ�
		
		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);
		
		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);
		
		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();
		
		String propertyValue1 = map1["Collidable"].asString();//�浹üũ
		String propertyValue2 = map2["Collidable"].asString();
		String LeftCarpet1 = map1["LeftCarpet"].asString();//�»�� ī�� �̺�Ʈ
		String LeftCarpet2 = map2["LeftCarpet"].asString();
		String RightCarpet1 = map1["RightCarpet"].asString();//���ϴ� ī�� �̺�Ʈ
		String RightCarpet2 = map2["RightCarpet"].asString();
		String Bed1 = map1["Bed"].asString();//ħ�� �̺�Ʈ
		String Bed2 = map2["Bed"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(17);

			sprPlayer->getActionManager()->removeAction(action);

			Go_Right = false;
		}
		else{
			if (!Go_Right){
				Go_Right = true;
				//ĳ���� �̵� �׼�
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
		
		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, BREAK_UP_Y));//����
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, BREAK_UP_Y));//�»��
		
		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);
		
		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);
		
		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();
		
		String propertyValue1 = map1["Collidable"].asString();//�浹üũ
		String propertyValue2 = map2["Collidable"].asString();
		String CuttingBoard1 = map1["CuttingBoard"].asString();//���� �̺�Ʈ
		String CuttingBoard2 = map2["CuttingBoard"].asString();
		String GasRange1 = map1["GasRange"].asString();//���������� �̺�Ʈ
		String GasRange2 = map2["GasRange"].asString();
		String FlavorDrawer1 = map1["FlavorDrawer"].asString();//��ŷ� ������ �̺�Ʈ
		String FlavorDrawer2 = map2["FlavorDrawer"].asString();
		String FoodDrawer1 = map1["FoodDrawer"].asString();//���� ������ �̺�Ʈ(�ݰ�)
		String FoodDrawer2 = map2["FoodDrawer"].asString();
		String Bed1 = map1["Bed"].asString();//ħ�� �̺�Ʈ
		String Bed2 = map2["Bed"].asString();
		String Frame1 = map1["Frame"].asString();//���� �̺�Ʈ
		String Frame2 = map2["Frame"].asString();
		String LeftCarpet1 = map1["LeftCarpet"].asString();//�»�� ī�� �̺�Ʈ
		String LeftCarpet2 = map2["LeftCarpet"].asString();
		String RightCarpet1 = map1["RightCarpet"].asString();//���ϴ� ī�� �̺�Ʈ
		String RightCarpet2 = map2["RightCarpet"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(18);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Up = false;
		}
		else{
			if (!Go_Up){
				Go_Up = true;
				//ĳ���� �̵� �׼� 
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
		
		CCPoint tileCoord1 = this->tileCoordForPosition(playerPos1 + Point(BREAK_X, -BREAK_TOO_DOWN_Y));//���ϴ�
		CCPoint tileCoord2 = this->tileCoordForPosition(playerPos2 + Point(-BREAK_X, -BREAK_TOO_DOWN_Y));//���ϴ�
		
		unsigned int tileGid1 = _background->tileGIDAt(tileCoord1);
		unsigned int tileGid2 = _background->tileGIDAt(tileCoord2);
		
		auto properties1 = _tileMap->propertiesForGID(tileGid1);
		auto properties2 = _tileMap->propertiesForGID(tileGid2);
		
		ValueMap map1 = properties1.asValueMap();
		ValueMap map2 = properties2.asValueMap();
		
		String propertyValue1 = map1["Collidable"].asString();//�浹üũ
		String propertyValue2 = map2["Collidable"].asString();
		String LeftCarpet1 = map1["LeftCarpet"].asString();//�»�� ī�� �̺�Ʈ
		String LeftCarpet2 = map2["LeftCarpet"].asString();
		String RightCarpet1 = map1["RightCarpet"].asString();//���ϴ� ī�� �̺�Ʈ
		String RightCarpet2 = map2["RightCarpet"].asString();
		String Door1 = map1["Door"].asString();//�� �̺�Ʈ
		String Door2 = map2["Door"].asString();

		if (propertyValue1.compare("True") == 0 || propertyValue2.compare("True") == 0){
			auto action = (Action*)sprPlayer->getActionByTag(19);

			sprPlayer->getActionManager()->removeAction(action);
			Go_Down = false;
		}
		else{
			if (!Go_Down){
				Go_Down = true;
				//ĳ���� �̵� �׼�
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

//���콺 ���뵵 -> ������
void GameScene::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;
	
	Point result = Point(e->getCursorX(), e->getCursorY());
	//���콺 Ŀ�� ��ġ �ޱ�

	Rect button1 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 1�� ��ư
	Rect button2 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 2�� ��ư
	Rect button3 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y1, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 3�� ��ư
	Rect button4 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 4�� ��ư
	Rect button5 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 5�� ��ư
	Rect button6 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y2, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 6�� ��ư
	Rect button7 = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 7�� ��ư
	Rect button8 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 8�� ��ư
	Rect button9 = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y3, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 9�� ��ư 
	Rect buttonC = Rect(SAFE_BUTTON_X1, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� C�� ��ư
	Rect button0 = Rect(SAFE_BUTTON_X2, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� 0�� ��ư
	Rect buttonE = Rect(SAFE_BUTTON_X3, SAFE_BUTTON_Y4, SAFE_BUTTON_SIZE, SAFE_BUTTON_SIZE); //�ݰ� E�� ��ư

	/*
	�ý��� ����

	��ư�� ������ blink������ 1�� �����Ѵ� �̰ɷ� ��й�ȣ�� ��ġ�� �˾Ƴ���.
	4���� �� �Է����� �� �ٸ��� �� �ʱ�ȭ ���� �� ������ ȹ��

	C��ư ������ ��ȣ �ʱ�ȭ -> ���찳 ��ư
	E��ư ������ ��ȣ �Է� ->�´� ��ȣ���� �Ǵ�
	*/
	if (foodDrawer == true && Go_Event == true){ //���� ������(�ݰ�) �̺�Ʈ Ȱ��ȭ ��
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
				CallCommunicationWindow("�ݰ� ������. \n\n\n��Ϲ����� ȹ���ߴ�.");
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
			}
			else{
				star1->setVisible(false);
				star2->setVisible(false);
				star3->setVisible(false);
				star4->setVisible(false);
				BackCommunicationWindow();
				CallCommunicationWindow("�߸��� ��й�ȣ����.");
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

