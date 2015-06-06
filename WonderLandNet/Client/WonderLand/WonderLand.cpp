#include "WonderLand.h"

CWonderLand::CWonderLand()
{
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;

	lastTime=0;
	LButtonDown=false;
	
}

CWonderLand::CWonderLand(const CWonderLand&)
{

}
void CWonderLand::setNetClient(netClient* newClient)
{	
	this->client=(*newClient);
	this->client.setUserName(newClient->getUserName());
	this->client.setPassword(newClient->getPassword());
}
void CWonderLand::setDevice(IrrlichtDevice* newdevice)
{
	this->device=newdevice;
}
void CWonderLand::run()
{	
	device->setEventReceiver(this);

	if (device == 0)
		return ; 

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();
	driver->clearZBuffer();
	smgr->clear();
	guienv->clear();
	myScene.setIrrlichtDevice(device);
	
	// 初始化客户端
	client.setDevice(device);
//	client.setGui(myGui);
	client.setGui(myScene.getGui());
//	client.netInitialize();

	//////////////////////////////////////////////////////////////////////////
	// FPS视角
	//////////////////////////////////////////////////////////////////////////
	SKeyMap keyMap[9];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_UP;
	keyMap[1].Action = EKA_MOVE_FORWARD;
	keyMap[1].KeyCode = KEY_KEY_W;
	keyMap[2].Action = EKA_MOVE_BACKWARD;
	keyMap[2].KeyCode = KEY_DOWN;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;
	keyMap[4].Action = EKA_STRAFE_LEFT;
	keyMap[4].KeyCode = KEY_LEFT;
	keyMap[5].Action = EKA_STRAFE_LEFT;
	keyMap[5].KeyCode = KEY_KEY_A;
	keyMap[6].Action = EKA_STRAFE_RIGHT;
	keyMap[6].KeyCode = KEY_RIGHT;
	keyMap[7].Action = EKA_STRAFE_RIGHT;
	keyMap[7].KeyCode = KEY_KEY_D;
	keyMap[8].Action = EKA_JUMP_UP;
	keyMap[8].KeyCode = KEY_KEY_C;
	camera=smgr->addCameraSceneNodeFPS(0,100.0f,0.1f,-1,keyMap,9);
//	camera=smgr->addCameraSceneNode(0,vector3df(0.0f,0.0f,0.0f),vector3df(0.0f,0.0f,0.0f));
	device->getCursorControl()->setVisible(true);
	//////////////////////////////////////////////////////////////////////////
	// 人物绑定
	//////////////////////////////////////////////////////////////////////////
/*	IAnimatedMesh* personMesh=smgr->getMesh("../../media/sydney.md2");
	IAnimatedMeshSceneNode* personNode = smgr->addAnimatedMeshSceneNode( personMesh );
	if (!personMesh)
	{
		device->drop();
		return ;
	}
	if (personNode)
	{
		personNode->setScale(vector3df(0.4f,0.4f,0.4f));
		personNode->setPosition(vector3df(-84.0f,10,-238.0f));
		personNode->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
		personNode->setMaterialFlag(EMF_LIGHTING, false);
		personNode->getMaterial(0).Shininess=28.0f;
		personNode->getMaterial(0).NormalizeNormals=true;
		personNode->setMD2Animation ( scene::EMAT_STAND );
		
	}
	personMesh->setMaterialFlag(EMF_LIGHTING,false);
*/
	camera->setPosition(vector3df(-84.0f,20,-238.0f));



	myScene.CreateScene(/*otherClientPosition*/);

	ITerrainSceneNode* terrain;
	terrain=myScene.GetITerrainSceneNode(ID_LAND);
	ITriangleSelector* selector=smgr->createTerrainTriangleSelector(terrain,0);
	terrain->setTriangleSelector(selector);
	ISceneNodeAnimator* anim=smgr->createCollisionResponseAnimator(selector,camera,
	vector3df(30,15,30),vector3df(0,0,0),vector3df(0,0,0));
	selector->drop();
	camera->addAnimator(anim);
	anim->drop();

	
	int lastFPS = -1;
//	u32 then = device->getTimer()->getTime();

	ISceneNode* selectedSceneNode=0;
	ISceneNode* lastSelectedSceneNode=0;

	client.netSendCreateClient();
	client.netRecvMyInfoMessageToServer();
	client.netRecvFriendListToServer();
	

	// 刚进入场景时先进行判断设定场景
	int firestsetPosition=0;

	while(device->run())
	{
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, video::SColor(255,120,120,120));
//			myScene.UpdateScene(otherClientPosition,camera);

			smgr->drawAll(); // draw the 3d scene
			device->getGUIEnvironment()->drawAll(); // draw the gui environment (the logo)
//			myScene.moveCameraControl(personNode);


			// 拾取
			myScene.Pick(camera,LButtonDown,client,myGui);

			vector3df camPos(camera->getPosition());
			if (camPos.Y!=CAMERA_POSITION_Y)
			{
				camera->setPosition(vector3df(camPos.X,CAMERA_POSITION_Y,camPos.Z));
			}
	
			driver->endScene();
	
			int fps = driver->getFPS();
	
			if (lastFPS != fps)
			{
				core::stringw tmp(L"WonderLand [");
				tmp += driver->getName();
				tmp += L"] fps: ";
				tmp += fps;
	
				device->setWindowCaption(tmp.c_str());
				lastFPS = fps;
			}
		}
		myGui.SetIrrlichtDevice(device);
		client.setGui(myGui);
		client.netReceiveMessage();

	}


	client.closeClient();
	device->drop();
	
	return ;
}

bool CWonderLand::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	if (event.EventType == EET_MOUSE_INPUT_EVENT)
	{
		switch (event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			LButtonDown=true;
			break;
		case EMIE_LMOUSE_LEFT_UP:
			LButtonDown=false;
			break;
		default:
			break;
		}
	}
	if (event.EventType == EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
	{
		u32 newTime=device->getTimer()->getTime();
		myGui=myScene.getGui();

		vector3df clientPositionTemp;
		clientPositionTemp.X=camera->getPosition().X;
		clientPositionTemp.Y=10;
		clientPositionTemp.Z=camera->getPosition().Z;
		switch (event.KeyInput.Key)
		{	
		case KEY_TAB:
			myGui.CreateMyInfoBox(client.getUserName(),client.getPassword(),client.getNickName(),
				client.getSignature(),client.getSex(),client.getAge(),client.getAdddress());
			break;
		case KEY_KEY_W:				
		case KEY_KEY_S:
		case KEY_KEY_A:
		case KEY_KEY_D:	
			if (abs((long)(lastTime-newTime))>=10)
			{
// 				client.netSendMoveMessage(camera->getPosition());
// 				client.setClientPosition(camera->getPosition());
				client.netSendMoveMessage(clientPositionTemp);
				client.setClientPosition(clientPositionTemp);
				lastTime=newTime;
			}

			break;
		default:
			break;
		}
	}
	if (event.EventType == EET_GUI_EVENT)
	{
		myGui=myScene.getGui();
		s32 id=event.GUIEvent.Caller->getID();
		IGUIEnvironment* env=device->getGUIEnvironment();
		IGUIFileOpenDialog* selectFileDialog;
		cOtherClient* pickedTemp;

		switch (event.GUIEvent.EventType)
		{
		case EGET_BUTTON_CLICKED:
			{
				vector<std::string> friendList=client.getFriendList();
				switch (id)
				{
				case GUI_ID_MYINFO_WINDOW_BUTTON_SUBMIT:				// 登陆后修改个人信息
					client.netSendModifyMyPersonalInfoToServer();
					break;
				case GUI_ID_MYINFO_WINDOW_BUTTON_FRIEND_LIST:
					//myGui.CreateFriendListBox();
					myGui.CreateFriendListBox(client.getFriendList());
//					client.netRecvFriendListToServer();
					break;
				case GUI_ID_BUTTON_OTHER_CLIENT_PERSONAL_INFO:			// 查看其他用户信息
					pickedTemp=client.getPickedClientPtr();
					myGui.CreateOtherClientPersonalInfoBox(pickedTemp->getOtherClientUserName(),
						pickedTemp->getOtherClientNickName(),pickedTemp->getOtherClientSignature(),
						pickedTemp->getOtherClientSex(),pickedTemp->getOtherClientAge(),
						pickedTemp->getOtherClientAdddress());
					break;
				case GUI_ID_BUTTON_OTHER_CLIENT_TEXT_CHAT:				// 文本聊天窗口
					myGui.CreateTextChatBox();
					break;
				case GUI_ID_BUTTON_SEND_CHAT_MESSAGE:
					client.netSendChatMessage();
					break;
				case GUI_ID_BUTTON_OTHER_CLIENT_VOICE_CHAT:				// 语音聊天窗口
					client.netSendVoiceChatToOtherClient();
					ShellExecute(NULL,"open","voice192.168.1.100.EXE",NULL,NULL,SW_SHOWNORMAL);
					break;
				case GUI_ID_BUTTON_OTHER_CLIENT_VIDEO_CHAT:				// 视频聊天窗口
					client.netSendVideoChatToOtherClient();
					ShellExecute(NULL,"open","BRAnyChatSDKDemo.EXE",NULL,NULL,SW_SHOWNORMAL);
					break;	
				case GUI_ID_BUTTON_VIDEO_CAHT_START:					// 确认接收视频聊天
					ShellExecute(NULL,"open","NOTEPAD.EXE",NULL,NULL,SW_SHOWNORMAL);
					break;
				case GUI_ID_BUTTON_VIDEO_CHAT_CANCLE:					// 确认取消视频聊天
					myGui.CloseIsStartVideoChatBox();
					break;
				case GUI_ID_BUTTON_FRIEND_INFO:						// 获取好友信息
					client.netRecvFriendPersonalInfoToServer(friendList.at(client.getPickedfriend()));
					break;
				case GUI_ID_BUTTON_FRIEND_TEXT_CHAT:				// 好友文本聊天窗口
					myGui.CreateFriendTextChatBox();
					break;
				case GUI_ID_BUTTON_SEND_CHAT_MESSAGE_FRIEND:
					client.netSendChatMessageToFriend();
					break;
				case GUI_ID_BUTTON_OTHER_CLIENT_ADD_FRIEND:				// 增加陌生人为好友
					client.netSendAddAsFriendToServer();
					break;
				case GUI_ID_BUTTON_OTHER_CLIENT_SEND_FILE:			// 向陌生人发送文件，打开文件选择窗口
					env->addFileOpenDialog(L"Please select a model file to send");
					break;
				case GUI_ID_BUTTON_SEND_FILE_REQUEST_OK:
					client.netSendIsAcceptSendFileRequest(true);
					break;
				case GUI_ID_BUTTON_SEND_FILE_REQUEST_CANCEL:
					client.netSendIsAcceptSendFileRequest(false);
					break;
				case GUI_ID_BUTTON_REFRESH_COMMENT:						// 用户刷新建筑信息评论
					client.netSendGetBuildingComment(myScene.GetPickedBuildingID());
					break;
				case GUI_ID_BUTTON_SEND_COMMENT:						// 用户发布建筑信息评论
					client.netSendClientBuildingComment(myScene.GetPickedBuildingID());
					break;
				default:
					break;
				}
				
				int i=0;
				while (i!=friendList.size())
				{
					if (id == GUI_ID_FRIENDLIST_WINDOW_FRIEND+i)
					{
						client.setPickedFriend(i);
						myGui.CreateFriendInfoBox(friendList[i]);
						break;
					}
					i++;
				}
			}
			break;

		case EGET_SCROLL_BAR_CHANGED:
			if (id == GUI_ID_SCROLL_BAR_BUILDING_COMMENT)
			{
				const s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
				myGui.UpdateBuildingComment(pos);
			}
			break;
		case EGET_FILE_SELECTED:
			selectFileDialog=(IGUIFileOpenDialog*)event.GUIEvent.Caller;
			client.netSendSendFileRequset(core::stringc(selectFileDialog->getFileName()).c_str());
			break;
		default:
			break;
		}
	}
	return false;
}


bool CWonderLand::IsKeyDown(EKEY_CODE keyCode)
{
	return KeyIsDown[keyCode];
}