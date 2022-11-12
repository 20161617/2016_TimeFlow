#include "GAME_SCENE_6.h"
#include "SimpleAudioEngine.h"
#include "MENU_SCENE.h"
#include "Menu_Layer.h"
#include "ExpandLayer.h"
#include "MixLayer.h"
#include "Hint_Layer.h"
#include "Think.h"

ExpandMenuLayer* expandLayer6;
MenuLayer* menuLayer6;
MixMenuLayer* mixLayer6;
HintLayer* hintLayer6;

Scene* GameScene6::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene6::create();

	scene->addChild(layer);

	expandLayer6 = ExpandMenuLayer::create();
	expandLayer6->setVisible(false);
	scene->addChild(expandLayer6, 4);

	mixLayer6 = MixMenuLayer::create();
	mixLayer6->setVisible(false);
	scene->addChild(mixLayer6, 4);

	menuLayer6 = MenuLayer::create();
	menuLayer6->setVisible(false);
	scene->addChild(menuLayer6, 5);

	hintLayer6 = HintLayer::create();
	hintLayer6->setVisible(false);
	scene->addChild(hintLayer6, 4);

	//�� ���� ����
	expandLayer6->KnowMapLevel(6);
	mixLayer6->KnowMapLevel(6);
	hintLayer6->findHint(0);
	hintLayer6->findHint(1);
	hintLayer6->findHint(2);
	hintLayer6->findHint(3);
	hintLayer6->findHint(4);
	hintLayer6->findHint(5);

	mixLayer6->expandLayer = expandLayer6;
	mixLayer6->gameScene6 = layer;

	return scene;
}

bool GameScene6::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Item_get.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/door_open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Mouse_click.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/password.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Safe_Close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Closet_Door_Close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Closet_Door_Safe_Carrier_Open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Wrong_Answer/mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map6/piano_wrong_answer.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Drawer_close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map4/Curtain.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/desk_drawer_close.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map2/USB_Laptop.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map6/Book_Turning_Pages.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Map6/Piano.wav");

	//plist �ҷ�����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Characters/sprites.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Items/Map6/WNumber/Wnumber.plist");

	//Ÿ�ϸ� �ҷ�����
	_tileMap = CCTMXTiledMap::create("./Maps/Map6.tmx");
	_background = _tileMap->getLayer("Background6");
	this->addChild(_tileMap, 0);

	//��ǥ����, �÷��̾� ������ǥ �� ������Ʈ �߰�
	playerSpawn = _tileMap->objectGroupNamed("PlayerSpawn6");

	if (playerSpawn == NULL){
		return false;
	}

	ValueMap spawnPoint = playerSpawn->getObject("PlayerSpawnXY6");

	//ĳ���� ���� ��ǥ����
	characterX = spawnPoint["x"].asInt();
	characterY = spawnPoint["y"].asInt();

	//�÷��̾� �����
	playerSprite = Sprite::createWithSpriteFrameName("sprites4.png");
	playerSprite->setPosition(Point(characterX, characterY));
	playerSprite->setTag(11);
	this->addChild(playerSprite, 1, 11);

	//������ ����
	firePlaceLayer = Layer::create();
	firePlaceLayer->setVisible(false);
	this->addChild(firePlaceLayer, 2);

	firePlaceLock = Sprite::create("./Items/Map6/Fireplace.png");
	firePlaceLock->setPosition(Point(Point(512, 384) + Point(0, 114)));
	firePlaceLayer->addChild(firePlaceLock, 2);

	firePlaceNumber1 = Sprite::createWithSpriteFrameName("W0.png");
	firePlaceNumber1->setPosition(Point(FIRE_PLACE_X, FIRE_PLACE_Y1));
	firePlaceNumber1->setAnchorPoint(Point::ZERO);
	firePlaceLayer->addChild(firePlaceNumber1, 3);

	firePlaceNumber2 = Sprite::createWithSpriteFrameName("W0.png");
	firePlaceNumber2->setPosition(Point(FIRE_PLACE_X, FIRE_PLACE_Y2));
	firePlaceNumber2->setAnchorPoint(Point::ZERO);
	firePlaceLayer->addChild(firePlaceNumber2, 3);

	firePlaceNumber3 = Sprite::createWithSpriteFrameName("W0.png");
	firePlaceNumber3->setPosition(Point(FIRE_PLACE_X, FIRE_PLACE_Y3));
	firePlaceNumber3->setAnchorPoint(Point::ZERO);
	firePlaceLayer->addChild(firePlaceNumber3, 3);

	firePlaceNumber4 = Sprite::createWithSpriteFrameName("W0.png");
	firePlaceNumber4->setPosition(Point(FIRE_PLACE_X, FIRE_PLACE_Y4));
	firePlaceNumber4->setAnchorPoint(Point::ZERO);
	firePlaceLayer->addChild(firePlaceNumber4, 3);

	//�ķ�Ʈ ����
	palleteCutIn = Sprite::create("./Items/Map6/Pallette.png");
	palleteCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	palleteCutIn->setVisible(false);
	this->addChild(palleteCutIn, 2);

	//å ����
	bookCutIn = Sprite::create("./Items/Map6/Book.png");
	bookCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	bookCutIn->setVisible(false);
	this->addChild(bookCutIn, 2);

	//�ǾƳ� ����
	pianoCutin = Sprite::create("./Items/Map6/Piano.png");
	pianoCutin->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
	pianoCutin->setVisible(false);
	this->addChild(pianoCutin, 2);

	//��ȭâ �����
	communication = Sprite::create("./Layers/communication.png");
	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setOpacity(255);
	communication->setVisible(false);
	this->addChild(communication, 3);

	this->schedule(schedule_selector(GameScene6::CallEveryFrame));

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene6::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene6::onKeyReleased, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameScene6::onMouseDown, this);
	// regist listener to dispatcher
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	Director::getInstance()->resume();

	return true;
}

//Ÿ�ϸ�
CCPoint GameScene6::tileCoordForPosition(CCPoint position){
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height* _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

//ī�޶�
void GameScene6::setViewPointCenter(CCPoint position){
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

//��ȭâ �ҷ�����
void GameScene6::CallCommunicationWindow(std::string info){

	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setVisible(true);

	Texts = Label::createWithTTF(info, "./Moris.ttf", 30, Size(630, 150));
	Texts->setPosition(playerSprite->getPosition() + Point(0, -262));
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

//��ȭâ ��������
void GameScene6::BackCommunicationWindow(){
	communication->setVisible(false);
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

//�޴������� ��ȯ
void GameScene6::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

//������ �Ѿ��
void GameScene6::changeThink_R(Ref *sender){
	auto scene = TransitionFade::create(3, ThinkScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

//Ű���� �Է�
void GameScene6::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	//�÷��̾� �±�
	auto sprPlayer = (Sprite*)this->getChildByTag(11);

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{ //A�� ��������
		checkLeft = true, Go_Left = true;

		if (Go_Event == false) { //��� �̺�Ʈ ���� �ʱ�ȭ
			pallete = false, book = false, piano = false, pianoChair = false, safe = false;
			flowerFrame = false, firePlace = false, vine = false, closet = false;
			pot = false, bookshelf = false, door = false;
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
			pallete = false, book = false, piano = false, pianoChair = false, safe = false;
			flowerFrame = false, firePlace = false, vine = false, closet = false;
			pot = false, bookshelf = false, door = false;
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
			pallete = false, book = false, piano = false, pianoChair = false, safe = false;
			flowerFrame = false, firePlace = false, vine = false, closet = false;
			pot = false, bookshelf = false, door = false;
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
			pallete = false, book = false, piano = false, pianoChair = false, safe = false;
			flowerFrame = false, firePlace = false, vine = false, closet = false;
			pot = false, bookshelf = false, door = false;
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
			menuLayer6->setPosition(Point::ZERO);	//���̾� ���� 
			menuLayer6->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //����
			Director::getInstance()->pause(); //���� ����
		}
		else if (Go_Menu == true)	{ //ESC���̾ Ȱ��ȭ ������ ��
			menuLayer6->setVisible(false); //���̾� �����
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
				mixLayer6->setVisible(false); //���շ��̾ ���������� ��Ȱ��ȭ��Ŵ
				goMix = false;
			}
			else if (goHint == true){ //��Ʈ���̾ ���������� ��Ȱ��ȭ��Ŵ
				hintLayer6->setVisible(false);
				goHint = false;
			}
			goExpand = true; //Ȯ�� ���̾� Ȱ��ȭ
			expandLayer6->setPosition(Point(Point(512, 384) + Point(0, 114)));
			expandLayer6->setVisible(true);
			mixLayer6->MixLayerOnOff = false;
			hintLayer6->HintLayerOnOff = false;
			expandLayer6->ExpandLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goExpand == true){ //Ȯ�� ���̾ Ȱ��ȭ �϶�
			expandLayer6->setVisible(false); //Ȯ�뷹�̾� ��Ȱ��ȭ
			goExpand = false;
			expandLayer6->ExpandLayerOnOff = false;
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
				expandLayer6->setVisible(false);
				goExpand = false;
			}
			else if (goHint == true){	//��Ʈ���̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ŵ
				hintLayer6->setVisible(false);
				goHint = false;
			}
			goMix = true;	//���շ��̾� Ȱ��ȭ
			mixLayer6->setPosition(Point(Point(512, 498)));
			mixLayer6->setVisible(true);
			mixLayer6->MixLayerOnOff = true;
			hintLayer6->HintLayerOnOff = false;
			expandLayer6->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goMix == true){	//���շ��̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
			mixLayer6->setVisible(false);
			goMix = false;
			mixLayer6->MixLayerOnOff = false;
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
				mixLayer6->setVisible(false);
				goMix = false;
			}
			else if (goExpand == true){	//Ȯ�뷹�̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
				expandLayer6->setVisible(false);
				goExpand = false;
			}
			goHint = true;	//��Ʈ���̾� Ȱ��ȭ
			hintLayer6->setPosition(Point(Point(512, 384) + Point(0, 114)));
			hintLayer6->setVisible(true);
			mixLayer6->MixLayerOnOff = false;
			hintLayer6->HintLayerOnOff = true;
			expandLayer6->ExpandLayerOnOff = false;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){	//��Ʈ���̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
			hintLayer6->setVisible(false);
			goHint = false;
			hintLayer6->HintLayerOnOff = false;
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
			if (pallete == true){
				Go_Event = true;
				GameScene6::CallCommunicationWindow(UTF8("������, �ʷϻ�, ����� ������ �� ������ �ִ�."));
				palleteCutIn->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
				palleteCutIn->setVisible(true);
				Director::getInstance()->pause();
			}
			else if (book == true){
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Book_Turning_Pages.wav");
				Go_Event = true;
				bookCutIn->setPosition(Point(playerSprite->getPosition()));
				bookCutIn->setVisible(true);
				Director::getInstance()->pause();
			}
			else if (piano == true){
				Go_Event = true;
				if (pianoItem == false){
					GameScene6::CallCommunicationWindow(UTF8("�ǾƳ� ���ָ� �Ͻÿ�."));
					pianoCutin->setPosition(Point(playerSprite->getPosition() + Point(0, ITEM_WINDOW_Y)));
					pianoCutin->setVisible(true);
				}
				else if (pianoItem == true){
					GameScene6::CallCommunicationWindow(UTF8("�ǾƳ��."));
				}
				Director::getInstance()->pause();
			}
			else if (pianoChair == true){
				Go_Event = true;
				if (pianoChairItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene6::CallCommunicationWindow(UTF8("���� �ؿ��� ������ �����."));
					mixLayer6->MapItemEvents(1);
					expandLayer6->MapItemEvents(6, 1);
					pianoChairItem = true;
				}
				else if (pianoChairItem == true){
					GameScene6::CallCommunicationWindow(UTF8("�� �̻� �ƹ��͵� ����."));
				}
				Director::getInstance()->pause();
			}
			else if (safe == true){
				Go_Event = true;
				if (pianoItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map2/USB_Laptop.mp3");
					GameScene6::CallCommunicationWindow(UTF8("����ִ�. �߿��� �� ��� �ִ� �� ����."));
				}
				else if (pianoItem == true && safeItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene6::CallCommunicationWindow(UTF8("����� �ݰ� ������.\n\n\n���� ������ �����."));
					mixLayer6->MapItemEvents(31);
					expandLayer6->MapItemEvents(6, 31);
					mixLayer6->MapItemEvents(4);
					expandLayer6->MapItemEvents(6, 4);
					safeItem = true;
				}
				else if (pianoItem == true && safeItem == true){
					GameScene6::CallCommunicationWindow(UTF8("���� �ݰ�ȿ� �ƹ��͵� ����"));
				}
				Director::getInstance()->pause();
			}
			else if (flowerFrame == true){
				Go_Event = true;
				if (flowerFrameItem == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
					GameScene6::CallCommunicationWindow(UTF8("���� �ڿ� ������ �־���.\n\n\n������ ȹ���ߴ�."));
					flowerFrameItem = true;
					mixLayer6->MapItemEvents(2);
					expandLayer6->MapItemEvents(6, 2);
				}
				else if (flowerFrameItem == true){
					GameScene6::CallCommunicationWindow(UTF8("�� �׸��� �����ΰ�? �� ���� �ɷ��ֳ�."));
				}
				Director::getInstance()->pause();
			}
			else if (firePlace == true){
				Go_Event = true;
				if (clockGear6 == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Closet_Door_Safe_Carrier_Open.mp3");
					firePlaceLayer->setPosition(Point(playerSprite->getPosition() - Director::getInstance()->getWinSize() * 0.5));
					firePlaceLayer->setVisible(true);
					GameScene6::CallCommunicationWindow(UTF8("��й�ȣ�� �Է��Ͻÿ�."));
				}
				else if (clockGear6 == true){
					GameScene6::CallCommunicationWindow(UTF8("��� ��Ϲ����� ã�Ҵ�."));
				}
				Director::getInstance()->pause();
			}
			else if (vine == true){
				Go_Event = true;
				GameScene6::CallCommunicationWindow(UTF8("�� �ȿ��� ������ �ڶ�?"));
				Director::getInstance()->pause();
			}
			else if (closet == true){
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map2/USB_Laptop.mp3");
				Go_Event = true;
				GameScene6::CallCommunicationWindow(UTF8("������ �ʴ´�. �����ʿ�� ���� ���δ�."));
				Director::getInstance()->pause();
			}
			else if (pot == true){
				Go_Event = true;
				GameScene6::CallCommunicationWindow(UTF8("��Ⱑ ���� �ʴ´�. ��ȭ�ΰ�?"));
				Director::getInstance()->pause();
			}
			else if (bookshelf == true){
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Book_Turning_Pages.wav");
				Go_Event = true;
				GameScene6::CallCommunicationWindow(UTF8("å�� ��� �����ó� ����."));
				Director::getInstance()->pause();
			}
			else if (door == true){
				Go_Event = true;
				if (clockGear6 == false){
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map5/Door_Spigot_Put.mp3");
					GameScene6::CallCommunicationWindow(UTF8("������ ��Ϲ����� � ã�Ƴ���."));
				}
				else if (clockGear6 == true){
					GameScene6::CallCommunicationWindow(UTF8("���� ������ ��Ϲ����� ã�Ҵ�! ���� �츮������ ���ư��� ��¥ ��Ϲ����� ��������!"));
				}
				Director::getInstance()->pause();
			}
		}
		else if (Go_Menu == false && Go_Event == true){
			if (pianoChair == true || safe == true || flowerFrame == true || vine == true || closet == true ||
				pot == true || bookshelf == true){
				Go_Event = false;
				GameScene6::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
			else if (door == true){
				Go_Event = false;
				if (clockGear6 == false){
					GameScene6::BackCommunicationWindow();
				}
				else if (clockGear6 == true){
					GameScene6::changeThink_R(this);
				}
				Director::getInstance()->resume();
			}
			else if (pallete == true){
				Go_Event = false;
				GameScene6::BackCommunicationWindow();
				palleteCutIn->setVisible(false);
				Director::getInstance()->resume();
			}
			else if (book == true){
				Go_Event = false;
				GameScene6::BackCommunicationWindow();
				bookCutIn->setVisible(false);
				Director::getInstance()->resume();
			}
			else if (piano == true){
				Go_Event = false;
				GameScene6::BackCommunicationWindow();
				pianoCutin->setVisible(false);
				Director::getInstance()->resume();
			}
			else if (firePlace == true){
				Go_Event = false;
				if (clockGear6 == false){
					firePlaceLayer->setVisible(false);
					GameScene6::BackCommunicationWindow();
				}
				else if (clockGear6 == true){
					GameScene6::BackCommunicationWindow();
				}
				Director::getInstance()->resume();
			}
		}
			break;
		}
	}
}

//Ű�Է�->Ű�� ������
void GameScene6::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
void GameScene6::CallEveryFrame(float f)
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
		String safe1 = map1["Safe"].asString();//�ݰ�
		String safe2 = map2["Safe"].asString();
		String pianoChair1 = map1["PianoChair"].asString();//�ǾƳ� ����
		String pianoChair2 = map2["PianoChair"].asString();
		String piano1 = map1["Piano"].asString();//�ǾƳ�
		String piano2 = map2["Piano"].asString();
	
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
		if (safe1.compare("True") == 0 && safe2.compare("True") == 0){
			safe = true;
		}
		else if (pianoChair1.compare("True") == 0 && pianoChair2.compare("True") == 0){
			pianoChair = true;
		}
		if (piano1.compare("True") == 0 && piano2.compare("True") == 0){
			piano = true;
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
		String pianoChair1 = map1["PianoChair"].asString();//�ǾƳ�����
		String pianoChair2 = map2["PianoChair"].asString();
		String pallete1 = map1["Pallete"].asString();//�ķ�Ʈ
		String pallete2 = map2["Pallete"].asString();
		String piano1 = map1["Piano"].asString();//�ǾƳ�
		String piano2 = map2["Piano"].asString();
	
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
		if (pianoChair1.compare("True") == 0 && pianoChair2.compare("True") == 0){
			pianoChair = true;
		}
		if (pallete1.compare("True") == 0 && pallete2.compare("True") == 0){
			pallete = true;
		}
		if (piano1.compare("True") == 0 && piano2.compare("True") == 0){
			piano = true;
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
		String safe1 = map1["Safe"].asString();//�ݰ�
		String safe2 = map2["Safe"].asString();
		String firePlace1 = map1["FirePlace"].asString();//������
		String firePlace2 = map2["FirePlace"].asString();
		String vine1 = map1["Vine"].asString();//����
		String vine2 = map2["Vine"].asString();
		String frame1 = map1["FlowerFrame"].asString();//����
		String frame2 = map2["FlowerFrame"].asString();
		String closet1 = map1["Closet"].asString();//����
		String closet2 = map2["Closet"].asString();
		String pot1 = map1["FlowerPot"].asString();//ȭ��
		String pot2 = map2["FlowerPot"].asString();
		String bookshelf1 = map1["Bookshelf"].asString();//å��
		String bookshelf2 = map2["Bookshelf"].asString();
		String book1 = map1["Book"].asString();//å
		String book2 = map2["Book"].asString();
		String pallete1 = map1["Pallete"].asString();//�ķ�Ʈ
		String pallete2 = map2["Pallete"].asString();
		
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
		if (safe1.compare("True") == 0 && safe2.compare("True") == 0){
			safe = true;
		}
		if (firePlace1.compare("True") == 0 && firePlace2.compare("True") == 0){
			firePlace = true;
		}
		if (vine1.compare("True") == 0 && vine2.compare("True") == 0){
			vine = true;
		}
		if (frame1.compare("True") == 0 && frame2.compare("True") == 0){
			flowerFrame = true;
		}
		if (closet1.compare("True") == 0 && closet2.compare("True") == 0){
			closet = true;
		}
		if (pot1.compare("True") == 0 && pot2.compare("True") == 0){
			pot = true;
		}
		if (bookshelf1.compare("True") == 0 && bookshelf2.compare("True") == 0){
			bookshelf = true;
		}
		if (book1.compare("True") == 0 && book2.compare("True") == 0){
			book = true;
		}
		if (pallete1.compare("True") == 0 && pallete2.compare("True") == 0){
			pallete = true;
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
		String door1 = map1["Door"].asString();//��
		String door2 = map2["Door"].asString();
		
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
		if (door1.compare("True") == 0 && door2.compare("True") == 0){
			door = true;
		}
	}
}

//���콺 ���뵵 -> ������
void GameScene6::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;

	//���콺 Ŀ�� ��ġ �ޱ�
	Point result = Point(e->getCursorX(), e->getCursorY());

	//���� ��ư��ǥ
	Rect firePlaceButton1 = Rect(FIRE_PLACE_X, FIRE_PLACE_Y1, FIRE_PLACE_SIZE, FIRE_PLACE_SIZE);
	Rect firePlaceButton2 = Rect(FIRE_PLACE_X, FIRE_PLACE_Y2, FIRE_PLACE_SIZE, FIRE_PLACE_SIZE);
	Rect firePlaceButton3 = Rect(FIRE_PLACE_X, FIRE_PLACE_Y3, FIRE_PLACE_SIZE, FIRE_PLACE_SIZE);
	Rect firePlaceButton4 = Rect(FIRE_PLACE_X, FIRE_PLACE_Y4, FIRE_PLACE_SIZE, FIRE_PLACE_SIZE);

	Rect pianoButton1 = Rect(PIANO_X1, PIANO_Y1, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton2 = Rect(PIANO_X2, PIANO_Y1, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton3 = Rect(PIANO_X3, PIANO_Y1, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton4 = Rect(PIANO_X4, PIANO_Y1, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton5 = Rect(PIANO_X5, PIANO_Y1, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton6 = Rect(PIANO_X6, PIANO_Y1, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton7 = Rect(PIANO_X7, PIANO_Y1, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton8 = Rect(PIANO_X8, PIANO_Y2, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton9 = Rect(PIANO_X9, PIANO_Y2, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton10 = Rect(PIANO_X10, PIANO_Y2, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton11 = Rect(PIANO_X11, PIANO_Y2, PIANO_SIZE, PIANO_SIZE);
	Rect pianoButton12 = Rect(PIANO_X12, PIANO_Y2, PIANO_SIZE, PIANO_SIZE);

	if (firePlace == true && clockGear6 == false){
		if (firePlaceButton1.containsPoint(result)){
			if (firePlacePassword1 < 9){
				firePlacePassword1++;
			}
			else{
				firePlacePassword1 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			firePlaceNumber1->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("W%d.png", firePlacePassword1)));
		}
		if (firePlaceButton2.containsPoint(result)){
			if (firePlacePassword2 < 9){
				firePlacePassword2++;
			}
			else{
				firePlacePassword2 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			firePlaceNumber2->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("W%d.png", firePlacePassword2)));
		}if (firePlaceButton3.containsPoint(result)){
			if (firePlacePassword3 < 9){
				firePlacePassword3++;
			}
			else{
				firePlacePassword3 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			firePlaceNumber3->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("W%d.png", firePlacePassword3)));
		}if (firePlaceButton4.containsPoint(result)){
			if (firePlacePassword4 < 9){
				firePlacePassword4++;
			}
			else{
				firePlacePassword4 = 0;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/password.mp3");
			firePlaceNumber4->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("W%d.png", firePlacePassword4)));
		}
		if (firePlacePassword1 == 5 && firePlacePassword2 == 3 && firePlacePassword3 == 5 && firePlacePassword4 == 7){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
			clockGear6 = true;
			firePlaceLayer->setVisible(false);
			GameScene6::BackCommunicationWindow();
			GameScene6::CallCommunicationWindow(UTF8("����� Ǯ�ȴ�.\n\n\n������ ��Ϲ����� ȹ���ߴ�."));
			hintLayer6->findHint(6);
		}
	}
	if (piano == true && pianoItem == false){
		if (pianoButton1.containsPoint(result)){
			if (piano_check1 == false){
				piano_Num1 = 1;
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_Num2 = 1;
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_Num3 = 1;
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton2.containsPoint(result)){
			if (piano_check1 == false){
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton3.containsPoint(result)){
			if (piano_check1 == false){
				piano_Num1 = 3;
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_Num2 = 3;
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_Num3 = 3;
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton4.containsPoint(result)){
			if (piano_check1 == false){
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton5.containsPoint(result)){
			if (piano_check1 == false){
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton6.containsPoint(result)){
			if (piano_check1 == false){
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton7.containsPoint(result)){
			if (piano_check1 == false){
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton8.containsPoint(result)){
			if (piano_check1 == false){
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton9.containsPoint(result)){
			if (piano_check1 == false){
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton10.containsPoint(result)){
			if (piano_check1 == false){
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton11.containsPoint(result)){
			if (piano_check1 == false){
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		else if (pianoButton12.containsPoint(result)){
			if (piano_check1 == false){
				piano_Num1 = 12;
				piano_check1 = true;
			}
			else if (piano_check2 == false){
				piano_Num2 = 12;
				piano_check2 = true;
			}
			else if (piano_check3 == false){
				piano_Num3 = 12;
				piano_check3 = true;
			}
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/Piano.wav");
		}
		if (piano_check3 == true){
			if (piano_Num1 != NULL && piano_Num2 != NULL && piano_Num3 != NULL){
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Item_get.wav");
				GameScene6::BackCommunicationWindow();
				GameScene6::CallCommunicationWindow(UTF8("�ǾƳ� �ǹ� ���̿��� ���谡 Ƣ��Դ�."));
				pianoCutin->setVisible(false);
				pianoItem = true;
				mixLayer6->MapItemEvents(3);
				expandLayer6->MapItemEvents(6, 3);
			}
			else if (piano_Num1 == NULL || piano_Num2 == NULL || piano_Num3 == NULL){
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Map6/piano_wrong_answer.wav");
				GameScene6::BackCommunicationWindow();
				GameScene6::CallCommunicationWindow(UTF8("�߸��� �ǹ��� ���� �� ����."));
				piano_Num1 = NULL, piano_Num2 = NULL, piano_Num3 = NULL;
				piano_check1 = false, piano_check2 = false, piano_check3 = false;
			}
		}
	}
}