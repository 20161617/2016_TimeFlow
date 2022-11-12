#include "Think.h"
#include "Hint_Layer.h"
#include "SimpleAudioEngine.h"
#include "MENU_SCENE.h"
#include "Menu_Layer.h"
#include "Correct.h"
#include "Incorrect.h"

HintLayer* hintLayerT;
MenuLayer* menuLayerT;

Scene* ThinkScene::createScene()
{
	auto scene = Scene::create();

	auto layer = ThinkScene::create();

	scene->addChild(layer);

	menuLayerT = MenuLayer::create();
	menuLayerT->setVisible(false);
	scene->addChild(menuLayerT, 5);

	hintLayerT = HintLayer::create();
	hintLayerT->setVisible(false);
	scene->addChild(hintLayerT, 4);

	//�� ���� ����
	hintLayerT->findHint(0);
	hintLayerT->findHint(1);
	hintLayerT->findHint(2);
	hintLayerT->findHint(3);
	hintLayerT->findHint(4);
	hintLayerT->findHint(5);
	hintLayerT->findHint(6);

	return scene;
}
bool ThinkScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//ȿ���� �ҷ�����
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/door_open.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("./Effect Music/Mouse_click.mp3");
	//plist �ҷ�����
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("./Characters/sprites.plist");

	//Ÿ�ϸ� �ҷ�����
	_tileMap = CCTMXTiledMap::create("./Maps/Time.tmx");
	_background = _tileMap->getLayer("Background7");
	this->addChild(_tileMap, 0);

	//��ǥ����, �÷��̾� ������ǥ �� ������Ʈ �߰�
	playerSpawn = _tileMap->objectGroupNamed("Spawn");

	if (playerSpawn == NULL){
		return false;
	}

	ValueMap spawnPoint = playerSpawn->getObject("SpawnXY");

	//ĳ���� ���� ��ǥ����
	characterX = spawnPoint["x"].asInt();
	characterY = spawnPoint["y"].asInt();

	//�÷��̾� �����
	playerSprite = Sprite::createWithSpriteFrameName("sprites4.png");
	playerSprite->setPosition(Point(characterX, characterY));
	playerSprite->setTag(11);
	this->addChild(playerSprite, 1, 11);

	//���� ���� â
	select_thief = Sprite::create("./Pro_Thi_Epi/Catch_Thief/criminal_choice.png");
	select_thief->setPosition(Point::ZERO);
	select_thief->setVisible(false);
	this->addChild(select_thief, 5);

	//��ȭâ �����
	communication = Sprite::create("./Layers/communication.png");
	communication->setPosition(playerSprite->getPosition() + Point(0, -COMMUNICATION_WINDOW_Y));
	communication->setOpacity(255);
	communication->setVisible(false);
	this->addChild(communication, 3);

	this->schedule(schedule_selector(ThinkScene::CallEveryFrame));

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(ThinkScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(ThinkScene::onKeyReleased, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(ThinkScene::onMouseDown, this);
	// regist listener to dispatcher
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}
//Ÿ�ϸ�
CCPoint ThinkScene::tileCoordForPosition(CCPoint position){
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height* _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

//ī�޶�
void ThinkScene::setViewPointCenter(CCPoint position){
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
void ThinkScene::CallCommunicationWindow(std::string info){

	communication->setPosition(playerSprite->getPosition() + Point(0, -254));
	communication->setVisible(true);

	Texts = Label::createWithTTF(info, "./Moris.ttf", 30, Size(630, 150));
	Texts->setPosition(playerSprite->getPosition() + Point(0, -262));
	Texts->setColor(ccc3(0, 0, 0));
	this->addChild(Texts, 4);
}

//��ȭâ ��������
void ThinkScene::BackCommunicationWindow(){
	communication->setVisible(false);
	Texts->setVisible(false);
	Texts->removeChild(Texts, true);
}

//�޴������� ��ȯ
void ThinkScene::changeMenuScene_R(Ref *sender){
	Director::getInstance()->replaceScene(MenuScene::createScene());
}

//������ �Ѿ��
//���� ����
void ThinkScene::changeIncorrect_R(Ref *sender){
	auto scene = TransitionFade::create(3, IncorrectScene::createScene());
	Director::getInstance()->replaceScene(scene);
}
//���� ����
void ThinkScene::changeCorrect_R(Ref *sender){
	auto scene = TransitionFade::create(3, CorrectScene::createScene());
	Director::getInstance()->replaceScene(scene);
}

//Ű���� �Է�
void ThinkScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event){

	//�÷��̾� �±�
	auto sprPlayer = (Sprite*)this->getChildByTag(11);

	switch (keyCode){
	case cocos2d::EventKeyboard::KeyCode::KEY_A:{ //A�� ��������
		checkLeft = true, Go_Left = true;

		if (Go_Event == false) { //��� �̺�Ʈ ���� �ʱ�ȭ
			door = false, hint = false;
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
			door = false, hint = false;
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
			door = false, hint = false;
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
			door = false, hint = false;
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
			menuLayerT->setPosition(Point::ZERO);	//���̾� ���� 
			menuLayerT->setVisible(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //����
			Director::getInstance()->pause(); //���� ����
		}
		else if (Go_Menu == true)	{ //ESC���̾ Ȱ��ȭ ������ ��
			menuLayerT->setVisible(false); //���̾� �����
			Go_Menu = false;
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
			if (Go_Menu == false && Go_Event == false && goHint == false){
				//�ٸ� â���� �� �������� ���� ���� �簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:{	//Ȯ�뷹�̾�
		if (Go_Menu == false && goHint == false){
			goHint = true;	//��Ʈ���̾� Ȱ��ȭ
			hintLayerT->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			hintLayerT->setVisible(true);
			hintLayerT->HintLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){	//��Ʈ���̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
			hintLayerT->setVisible(false);
			goHint = false;
			hintLayerT->HintLayerOnOff = false;
			if (Go_Menu == false && Go_Event == false && goHint == false){
				//��緹�̾ ��Ȱ��ȭ�Ͻ� �����簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_E:{	//���շ��̾�
		if (Go_Menu == false && goHint == false){
			goHint = true;	//��Ʈ���̾� Ȱ��ȭ
			hintLayerT->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			hintLayerT->setVisible(true);
			hintLayerT->HintLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){	//��Ʈ���̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
			hintLayerT->setVisible(false);
			goHint = false;
			hintLayerT->HintLayerOnOff = false;
			if (Go_Menu == false && Go_Event == false && goHint == false){
				//��緹�̾ ��Ȱ��ȭ�Ͻ� �����簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_H:{	//��Ʈ���̾�
		if (Go_Menu == false && goHint == false){
			goHint = true;	//��Ʈ���̾� Ȱ��ȭ
			hintLayerT->setPosition(Point(Point(LAYERS_X, LAYERS_Y)));
			hintLayerT->setVisible(true);
			hintLayerT->HintLayerOnOff = true;
			Director::getInstance()->pause();
		}
		else if (Go_Menu == false && goHint == true){	//��Ʈ���̾� Ȱ��ȭ�� ��Ȱ��ȭ ��Ű��
			hintLayerT->setVisible(false);
			goHint = false;
			hintLayerT->HintLayerOnOff = false;
			if (Go_Menu == false&& Go_Event == false && goHint == false){
				//��緹�̾ ��Ȱ��ȭ�Ͻ� �����簳
				Director::getInstance()->resume();
			}
		}
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:{	//�̺�Ʈ Ȱ��ȭ ��Ű��(�̺�Ʈ ������Ʈ������)
		if (Go_Menu == false && Go_Event == false && goHint == false){
			//��� ���̾ ������������ Ȱ�������ϴ�.
			if (door == true){
				Go_Event = true;
				select_thief->setPosition(playerSprite->getPosition());
				select_thief->setVisible(true);
				Director::getInstance()->pause();
			}
			else if (hint == true){
				Go_Event = true;
				ThinkScene::CallCommunicationWindow(UTF8("Q, E, H �� �ƹ� ��ư�̳� ������ ���ο� ���� �߸��� ����.\n\n�߸��� �� �ߴٸ� ������ ���� ������ ����."));
				Director::getInstance()->pause();
			}
		}
		else if (Go_Menu == false && Go_Event == true){
			if (door == true){
				Go_Event = false;
				select_thief->setVisible(false);
				Director::getInstance()->resume();
			}
			else if (hint == true){
				Go_Event = false;
				ThinkScene::BackCommunicationWindow();
				Director::getInstance()->resume();
			}
		}
		break;
	}
	}
}

//Ű�Է�->Ű�� ������
void ThinkScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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
			Go_Menu == false && Go_Event == false){
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
			Go_Menu == false && Go_Event == false){
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
			Go_Menu == false && Go_Event == false){
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
			Go_Menu == false && Go_Event == false){
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
void ThinkScene::CallEveryFrame(float f)
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
		String hint1 = map1["Hint"].asString();//��Ʈ
		String hint2 = map2["Hint"].asString();

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
		if (hint1.compare("True") == 0 && hint2.compare("True") == 0){
			hint = true;
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
		String hint1 = map1["Hint"].asString();//��Ʈ
		String hint2 = map2["Hint"].asString();
		
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
		if (hint1.compare("True") == 0 && hint2.compare("True") == 0){
			hint = true;
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
void ThinkScene::onMouseDown(cocos2d::Event* event){
	EventMouse* e = (EventMouse*)event;

	//���콺 Ŀ�� ��ġ �ޱ�
	Point cursorXY = Point(e->getCursorX(), e->getCursorY());

	//���� ��ư
	Rect thiefButton1R = Rect(THIEF_BUTTON_X1, THIEF_BUTTON_Y1, THIEF_BUTTON_SIZE_X, THIEF_BUTTON_SIZE_Y);
	Rect thiefButton2R = Rect(THIEF_BUTTON_X2, THIEF_BUTTON_Y1, THIEF_BUTTON_SIZE_X, THIEF_BUTTON_SIZE_Y);
	Rect thiefButton3R = Rect(THIEF_BUTTON_X3, THIEF_BUTTON_Y1, THIEF_BUTTON_SIZE_X, THIEF_BUTTON_SIZE_Y);
	Rect thiefButton4R = Rect(THIEF_BUTTON_X1, THIEF_BUTTON_Y2, THIEF_BUTTON_SIZE_X, THIEF_BUTTON_SIZE_Y);
	Rect thiefButton5R = Rect(THIEF_BUTTON_X2, THIEF_BUTTON_Y2, THIEF_BUTTON_SIZE_X, THIEF_BUTTON_SIZE_Y);
	Rect thiefButton6R = Rect(THIEF_BUTTON_X3, THIEF_BUTTON_Y2, THIEF_BUTTON_SIZE_X, THIEF_BUTTON_SIZE_Y);

	if (door == true){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/Mouse_click.mp3");
		if (thiefButton1R.containsPoint(cursorXY)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			changeIncorrect_R(this);
			Director::getInstance()->resume();
		}
		else if (thiefButton2R.containsPoint(cursorXY)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			changeIncorrect_R(this);
			Director::getInstance()->resume();
		}
		else if (thiefButton3R.containsPoint(cursorXY)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			changeIncorrect_R(this);
			Director::getInstance()->resume();
		}
		else if (thiefButton4R.containsPoint(cursorXY)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			changeIncorrect_R(this);
			Director::getInstance()->resume();
		}
		else if (thiefButton5R.containsPoint(cursorXY)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			changeCorrect_R(this);
			Director::getInstance()->resume();
		}
		else if (thiefButton6R.containsPoint(cursorXY)){
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("./Effect Music/door_open.mp3");
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			changeIncorrect_R(this);
			Director::getInstance()->resume();
		}
	}
}