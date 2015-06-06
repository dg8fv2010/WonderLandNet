#include "netClient.h"



netClient::netClient()
{
	landResult=0;
	registerResult=0;
}

netClient::netClient(const netClient&)
{

}

netClient::~netClient()
{

}
void netClient::setDevice(IrrlichtDevice* newDevice)
{
	this->device=newDevice;
}
void netClient::setGui(CGui newGui)
{
	this->myGui=newGui;
}
void netClient::netInitialize()
{
	char str[]="127.0.0.1";
//	char str[]="183.221.17.31";
	peerClient = RakNet::RakPeerInterface::GetInstance();


	RakNet::SocketDescriptor sd(CLIENT_PORT,0);
	sd.socketFamily=AF_INET;
	while (SocketLayer::IsPortInUse(sd.port, sd.hostAddress, sd.socketFamily)==true)
		sd.port++;
	peerClient->Startup(1,&sd, 1);
	this->port=sd.port;

	
	this->SetPort(sd.port);

	cout<<str<<endl;
	cout<<sd.hostAddress<<endl;
	cout<<sd.port<<endl;
	
	peerClient->Connect(str, SERVER_PORT, 0,0);


//////////////////////////////////////////////////////////////////////////
// 	packet=peerClient->Receive();
// 	if (packet->data[0] != ID_CONNECTION_REQUEST_ACCEPTED)
// 	{
// 		cout<<"Connect-Failed!"<<endl;
// 	}
}


void netClient::SetSystemAddress(SystemAddress newSa)
{
	this->systemAddress=newSa;
}
SystemAddress netClient::GetSystemAddress()
{
	return this->systemAddress;
}
void netClient::SetPort(unsigned int newPort)
{
	this->port=newPort;
}
unsigned int netClient::GetPort()
{
	return this->port;
}
void netClient::setUserName(stringc newuserName)
{
	this->userName=newuserName;
}
stringc netClient::getUserName()
{
	return this->userName;
}
void netClient::setPassword(stringc newPassword)
{
	this->password=newPassword;
}
stringc netClient::getPassword()
{
	return this->password;
}
void netClient::setNickName(stringc nickName)
{
	this->nickName=nickName;
}
stringc netClient::getNickName()
{
	return this->nickName;
}
void netClient::setSignature(stringc signature)
{
	this->signature=signature;
}
stringc netClient::getSignature()
{
	return this->signature;
}
void netClient::setSex(stringc sex)
{
	this->sex=sex;
}
stringc netClient::getSex()
{
	return this->sex;
}
void netClient::setAge(stringc age)
{
	this->age=age;
}
stringc netClient::getAge()
{
	return this->age;
}
void netClient::setAdddress(stringc adddress)
{
	this->adddress=adddress;
}
stringc netClient::getAdddress()
{
	return this->adddress;
}
void netClient::setClientPosition(vector3df newPosition)
{
	this->clientPosition=newPosition;
}
vector3df netClient::getClientPosition()
{
	return this->clientPosition;
}
void netClient::setSceneCamera(ICameraSceneNode* newCamera)
{
	this->camera=newCamera;
}
ICameraSceneNode* netClient::getSceneCamera()
{
	return this->camera;
}
void netClient::setFriendList(vector<std::string> newFirendList)
{
	this->friendList=newFirendList;
}
vector<std::string> netClient::getFriendList()
{
	return this->friendList;
}

unsigned char netClient::GetPacketIdentifier(Packet* p)
{

	if (p==0)
		return 255;

	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char) p->data[0];
}


void netClient::netSetNetworkID(NetworkID newID)
{
	this->networkId=newID;
}
NetworkID netClient::netGetNetworkID()
{
	return this->networkId;
}

// ??????????????????????????????
// 只能将信息发送给服务器？？
void netClient::netSendMoveMessage(vector3df position)
{
	cout<<"netSendMoveMessage()-started"<<endl;

	this->useTimeStamp=ID_TIMESTAMP;
	this->timeStamp=RakNet::GetTime();
	this->typeId=ID_GAME_MESSAGE_CLIENT_MOVE;

	RakNet::BitStream bsOut;
	bsOut.Write(useTimeStamp);
	bsOut.Write(timeStamp);
	bsOut.Write(typeId);
	bsOut.Write(this->netGetNetworkID());
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->getUserName().c_str(),256,&bsOut);
	bsOut.Write(position);
	

	for (int i=0;i!=otherClient.size();i++)
	{
		peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,otherClient[i]->getSystemAddress(),false);
	}
	
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netSendMoveMessage()-finished"<<endl;
}
void netClient::netRecvMoveMessage()
{
	cout<<"netReceiveMoveMessage()-started"<<endl;

	NetworkID netId;
	vector3df newPosition;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.Read(useTimeStamp);
	bsIn.Read(timeStamp);
	bsIn.Read(typeId);
	bsIn.Read(netId);
	StringCompressor stringCompressor;
	char clientNameTemp[256];
	stringCompressor.DecodeString(clientNameTemp,256,&bsIn);
	bsIn.Read(newPosition);

	for (int i=0;i!=otherClient.size();i++)
	{
// 		if (netId == otherClient[i]->getNetworkID())
// 		{
// 			otherClient[i]->clientMove(newPosition);
// 			break;
// 		}
		if ( (otherClient[i]->getOtherClientUserName()).equals_ignore_case(clientNameTemp))
		{
			otherClient[i]->clientMove(newPosition);
			break;
		}
	}

	cout<<"netReceiveMoveMessage()-finished"<<endl;
}

void netClient::netSendCreateClient()
{
	cout<<"netSendCreateClient()-started"<<endl;

	this->typeId=ID_GAME_MESSAGE_CREATE_CLIENT_FROM_CLIENT;

	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	bsOut.Write(vector3df(-84.0f,10,-238.0f));
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->getUserName().c_str(),256,&bsOut);
	if (packet == NULL)
	{
		RakNet::AddressOrGUID severAddress;
		severAddress.systemAddress="127.0.0.1";
		peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	} 
	else
	{
		peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	}

	cout<<"netSendCreateClient()-finished"<<endl;
}

// 每当有一个客户登陆服务器时，服务器会广播该用户
// 用户会比对被广播的用户的IP和端口号
// 如果相等，则将被广播用户的networkID设为自己的networkID
// 如果不相等，则将被广播用户的信息进行保存，并显示对应的客户
void netClient::netRecvCreateClient(IrrlichtDevice* myDevice)
{
	cout<<"netRecvCreateClient()-started"<<endl;

	vector3df clientPosition;
	NetworkID netID;
	SystemAddress orignAddress;
	SystemAddress addressTemp;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(clientPosition);
	bsIn.Read(netID);
	bsIn.Read(addressTemp);  // 第一次接收服务器发送的消息时，获取客户机自身的地址
	
	StringCompressor stringCompressor;
	char clientNameTemp[256];
	stringCompressor.DecodeString(clientNameTemp,256,&bsIn);
	char clientPositionTemp[256];
	stringCompressor.DecodeString(clientPositionTemp,256,&bsIn);
	
	bsIn.Read(orignAddress);
	if (this->getUserName().equals_ignore_case(clientNameTemp) == true)
	{
		this->netSetNetworkID(netID);

		char *token=NULL;
		char *next_token=NULL;
		vector<int> positionTemp;
		token=strtok_s(clientPositionTemp,",",&next_token);
		while (token!=NULL)
		{
			positionTemp.push_back(atoi(token));
			token=strtok_s(NULL,",",&next_token);
		}
		vector3df position;
		position.X=(f32)positionTemp[0];
		position.Y=(f32)positionTemp[1];
		position.Z=(f32)positionTemp[2];
		this->setClientPosition(position);
		this->SetSystemAddress(addressTemp);
	}
	else
	{
		cOtherClient *newClient=new cOtherClient;
		newClient->setSystemAddress(orignAddress);
		newClient->setNetworkID(netID);
		newClient->setPosition(clientPosition);
		newClient->setOtherClientUserName(clientNameTemp);
		// 接收新登录用户的信息，并进行绘制
		newClient->createPersonNode(myDevice,clientPosition);
		otherClient.push_back(newClient);
	}


	cout<<"netRecvCreateClient()-finished"<<endl;

}

// 新登录的用户，需要接受其他所有在线用户的信息
void netClient::netRecvOtherClientInfo(IrrlichtDevice* myDevice)
{
	cout<<"netRecvOtherClientInfo()-started"<<endl;

	if (otherClient.empty()==false)
	{
		otherClient.clear();
	}	
	
	int count=0;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(count);
	StringCompressor stringCompressor;

	for (int i=0;i!=(count-1);i++)
	{			
// 		SystemAddress sysAddress;
// 		bsIn.Read(sysAddress);
// 		NetworkID netID;
// 		bsIn.Read(netID);
		vector3df clientPosition;
		bsIn.Read(clientPosition);
		char clientNameTemp[256];
		stringCompressor.DecodeString(clientNameTemp,256,&bsIn);
		SystemAddress saTemp;
		bsIn.Read(saTemp);
// 		if (netID == this->netGetNetworkID())
// 		{
// 			continue;
// 		}
		if (this->getUserName().equals_ignore_case(clientNameTemp) == true)
		{
			continue;
		}

		cOtherClient *newClient=new cOtherClient;
// 		newClient->setAddress(sysAddress);
// 		newClient->setNetworkID(netID);
		newClient->setPosition(clientPosition);
		newClient->setOtherClientUserName(clientNameTemp);
		newClient->setSystemAddress(saTemp);
		// 接收新登录用户的信息，并进行绘制
		newClient->createPersonNode(myDevice,clientPosition);
		otherClient.push_back(newClient);
	}

	cout<<"netRecvOtherClientInfo()-finished"<<endl;
}

void netClient::setPickedClient(cOtherClient& newClient)
{
	this->pickedClient=newClient;
	this->pickedClient.setOtherClientUserName(newClient.getOtherClientUserName());
}
cOtherClient netClient::getPickedClient()
{
	return this->pickedClient;
}
cOtherClient* netClient::getPickedClientPtr()
{
	return &(this->pickedClient);
}
void netClient::netRecvPickedClientInfoToServer()
{
	cout<<"netRecvPickedClientInfo()-started"<<endl;
	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_RECV_OTHER_CLIENT_INFO_TO_SERVER;
	bsOut.Write(typeId);
	bsOut.Write(this->pickedClient.getSystemAddress());
	bsOut.Write(this->pickedClient.getNetworkID());
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->pickedClient.getOtherClientUserName().c_str(),256,&bsOut);

	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netRecvPickedClientInfo()-finished"<<endl;
}
void netClient::netRecvPickedClientInfoFromServer()
{
	cout<<"netRecvPickedClientInfoFromServer()-started"<<endl;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	StringCompressor stringCompressor;

	char userNameOtherClient[256];
	char nickNameOtherClient[256];
	char signatureOtherClient[256];
	char sexOtherClient[256];
	char ageOtherClient[256];
	char adddressOtherClient[256];

	stringCompressor.DecodeString(userNameOtherClient,256,&bsIn);
	stringCompressor.DecodeString(nickNameOtherClient,256,&bsIn);
	stringCompressor.DecodeString(signatureOtherClient,256,&bsIn);
	stringCompressor.DecodeString(sexOtherClient,256,&bsIn);
	stringCompressor.DecodeString(ageOtherClient,256,&bsIn);
	stringCompressor.DecodeString(adddressOtherClient,256,&bsIn);

	this->pickedClient.setOtherClientUserName(userNameOtherClient);
	this->pickedClient.setOtherClientNickName(nickNameOtherClient);
	this->pickedClient.setOtherClientSignature(signatureOtherClient);
	this->pickedClient.setOtherClientSex(sexOtherClient);
	this->pickedClient.setOtherClientAge(ageOtherClient);
	this->pickedClient.setOtherClientAdddress(adddressOtherClient);
	
	cout<<"netRecvPickedClientInfoFromServer()-finished"<<endl;
}
void netClient::netSendChatMessage()
{
	cout<<"netSendChatMessage()-started"<<endl;

// 	if (this->pickedClient.getPersonalNode()==NULL)
// 	{
// 		cout<<"this->pickedClient.getPersonalNode()==NULL-failed"<<endl;
// 		return;
// 	}
	IGUIEnvironment* env = device->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	IGUIElement* dlg = root->getElementFromId(GUI_ID_TEXT_CHAT_WINDOW, true);
	core::stringc s;
	
	s = root->getElementFromId(GUI_ID_TEXT_PERSON_SAY_STRING, true)->getText();
	root->getElementFromId(GUI_ID_TEXT_PERSON_SAY_STRING, true)->setText(L"");
	const char* mes=s.c_str();
	RakString message(mes);

	this->useTimeStamp=ID_TIMESTAMP;
	this->timeStamp=RakNet::GetTime();
	this->typeId=ID_GAME_MESSAGE_SEND_CHAT_MESSAGE;

	RakNet::BitStream bsOut;
	
	
	if (textChatString.size()==0)			// 若为发起会话者，textChatString开始为空
	{
		textChatClient=pickedClient;
		textChatClient.setOtherClientUserName(pickedClient.getOtherClientUserName().c_str());
	} 
	else									// 若是被动的接收会话,则发起对话者在接收信息时已被记录
	{	
// 		for (int i=0;i!=otherClient.size();i++)
// 		{
// 			if (textChatClient.getAddress() == otherClient[i]->getAddress())
// 			{
// 				textChatClient=(*otherClient[i]);
// 				break;
// 			}
// 		}
	}
	bsOut.Write(typeId);
//	bsOut.Write(this->textChatClient.getAddress());
//	bsOut.Write(this->textChatClient.getNetworkID());
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->getUserName().c_str(),256,&bsOut);
	stringCompressor.EncodeString(this->textChatClient.getOtherClientUserName().c_str(),256,&bsOut);
	bsOut.Write(message);
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	// 更新对话框中的信息
	IGUIStaticText *  aniInfo = (IGUIStaticText *)(dlg->getElementFromId(GUI_ID_TEXT_STRING, true));
	if (aniInfo)
	{
		core::stringw str(L"I said: ");
		str += message.C_String();
		str += "\r\n";
		textChatString+=str;
		aniInfo->setText(textChatString.c_str());
	}

	cout<<"netSendChatMessage()-finished"<<endl;
}

void netClient::netRecvChatMessage()
{
	cout<<"netrecvChatMessage()-started"<<endl;

	// 接受到来自服务器的数据，address是自会话发起方，id会话接收方
// 	SystemAddress address;
// 	NetworkID netId;
	RakString message;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
//	bsIn.Read(address);
//	bsIn.Read(netId);
	char clientNameSend[256];
	char clientNameRecv[256];
	StringCompressor stringCompressor;
	stringCompressor.DecodeString(clientNameSend,256,&bsIn);
	stringCompressor.DecodeString(clientNameRecv,256,&bsIn);
	bsIn.Read(message);
	if (this->getUserName().equals_ignore_case(clientNameRecv) == false)
	{
		return;
	}
// 	if (address == this->systemAddress)
// 	{
// 		return;
// 	}
// 	if (netId != this->netGetNetworkID())
// 	{
// 		return;
// 	}
//	textChatClient.setAddress(address);
	// 确定会话发起方的address和id
// 	for (int i=0;i!=otherClient.size();i++)
// 	{
// 		if (address == otherClient[i]->getAddress())
// 		{
// 			netId=otherClient[i]->getNetworkID();
// 		}
// 	}
//	textChatClient.setNetworkID(netId);
	textChatClient.setOtherClientUserName(clientNameSend);

	IGUIEnvironment* env = device->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	IGUIElement* dlg = root->getElementFromId(GUI_ID_TEXT_CHAT_WINDOW, true);

	// 创建文本聊天窗口
	if (dlg)
	{
		dlg->remove();
	}
	wchar_t* temp=NULL;

	char* charTemp="PersonalInfo";
	charTowchar(charTemp,temp,strlen(charTemp));
	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,550,350),false,temp,0,GUI_ID_TEXT_CHAT_WINDOW);
	// 说话人的姓名
	env->addStaticText(L"Test1 say:",rect<s32>(10,270,50,290),false,false,wnd);
	env->addEditBox(temp,rect<s32>(50,270,325,290),true,wnd,GUI_ID_TEXT_PERSON_SAY_STRING);
	env->addButton(rect<s32>(325,270,350,290),wnd,GUI_ID_BUTTON_SEND_CHAT_MESSAGE,L"Send");
	env->addStaticText(L"",rect<s32>(0,30,350,250),true,true,wnd,GUI_ID_TEXT_STRING);
	

	

	// 更新对话框中的信息
	dlg = root->getElementFromId(GUI_ID_TEXT_CHAT_WINDOW, true);
	IGUIStaticText *  aniInfo = (IGUIStaticText *)(dlg->getElementFromId(GUI_ID_TEXT_STRING, true));
	if (aniInfo)
	{
		stringw str;
		str=clientNameSend;
		str.append(L" said: ");
		str += message.C_String();
		str += "\r\n";
		textChatString+=str;
		aniInfo->setText(textChatString.c_str());
	}

	cout<<"netrecvChatMessage()-finished"<<endl;
}

// 客户端关闭时，要向服务器和其他在线用户广播自己的信息，便于他们删除自己的记录
void netClient::netSendClientShutdown()
{
	cout<<"netSendClientShutdown()-started"<<endl;

	BitStream bsOut;
	
	this->typeId=ID_GAME_MESSAGE_CLIENT_SHUTDOWN;
	NetworkID netid=netGetNetworkID();
	bsOut.Write(typeId);
	bsOut.Write(netid);
	bsOut.Write(this->getClientPosition().X);
	bsOut.Write(this->getClientPosition().Y);
	bsOut.Write(this->getClientPosition().Z);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->getUserName().c_str(),256,&bsOut);
// 	stringc test=this->getUserName();
// 	StringCompressor stringCompressor;
// 	std::string usernameStr;
// 	usernameStr.assign(this->getUserName().c_str());
// 	stringCompressor.EncodeString(usernameStr.c_str(),256,&bsOut);
// 	bsOut.Write(this->characterPosition);
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netSendClientShutdown()-finished"<<endl;
}

// 客户端接收到其他客户关闭的消息时，要删除该客户的记录
void netClient::netRecvClientShutdown()
{
	cout<<"netRecvClientShutdown()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	NetworkID netId;
	bsIn.Read(netId);

	vector<cOtherClient*>::iterator itr;
	for (itr=otherClient.begin();itr!=otherClient.end();itr++)
	{
		if (netId == (*itr)->getNetworkID())
		{
			otherClient.erase(itr);
			break;
		}
	}

	cout<<"netRecvClientShutdown()-finished"<<endl;
}


int netClient::netReceiveMessage()
{
	packet=peerClient->Receive();
	int wonderLandStart=0;

	if (packet==NULL)
	{
		return 0;
	}
	unsigned char packetIdentifier;
	packetIdentifier=GetPacketIdentifier(packet);
	switch (packetIdentifier/*packet->data[0]*/)
	{
	case ID_REMOTE_DISCONNECTION_NOTIFICATION:
		printf("Another client has disconnected.\n");
		break;
	case ID_REMOTE_CONNECTION_LOST:
		printf("Another client has lost the connection.\n");
		break;
	case ID_REMOTE_NEW_INCOMING_CONNECTION:
		printf("Another client has connected.\n");
		break;
	case ID_CONNECTION_REQUEST_ACCEPTED:
		{
			printf("Our connection request has been accepted.\n");

			// Use a BitStream to write a custom user message
			// Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
			RakNet::BitStream bsOut;
			bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
			bsOut.Write("Hello world");
			peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);
		}
		break;
	case ID_NEW_INCOMING_CONNECTION:
		printf("A connection is incoming.\n");
		break;
	case ID_NO_FREE_INCOMING_CONNECTIONS:
		printf("The server is full.\n");
		break;
	case ID_DISCONNECTION_NOTIFICATION:	
		printf("We have been disconnected.\n");
		break;
	case ID_CONNECTION_LOST:
		printf("Connection lost.\n");
		break;
	case ID_GAME_MESSAGE_1:
		{
			RakNet::RakString rs;
			RakNet::BitStream bsIn(packet->data,packet->length,false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			bsIn.Read(rs);
			printf("%s\n", rs.C_String());
		}
		break;
	case ID_GAME_MESSAGE_RECV_LAND_FROM_SEVER:
		wonderLandStart=netRecvLandFromSever();
		break;
	case ID_GAME_MESSAGE_RECV_REGISTER_FROM_SEVER:
		netRecvRegisterFromSever();
		break;
	case ID_GAME_MESSAGE_CREATE_CLIENT_FROM_SEVER:	
		netRecvCreateClient(this->device);
		break;
	case ID_GAME_MESSAGE_OTHER_CLIENT_INFO:
		netRecvOtherClientInfo(this->device);
		break;
	case ID_GAME_MESSAGE_CLIENT_MOVE:
		netRecvMoveMessage();
		break;
	case ID_GAME_MESSAGE_RECV_CHAT_MESSAGE:
		netRecvChatMessage();
		break;
	case ID_GAME_MESSAGE_CLIENT_SHUTDOWN:
		netRecvClientShutdown();
		break;
	case ID_GAME_MESSAGE_RECV_MYINFO_MESSAGE_FROM_SEVER:
		netRecvMyInfoMessageFromServer();
		break;
	case ID_GAME_MESSAGE_RECV_FRIENDLIST_FROM_SEVER:
		netRecvFriendListFromServer();
		break;
	case ID_GAME_MESSAGE_RECV_FRIEND_PERSONAL_INFO_FROM_SEVER:
		netRecvFriendPersonalInfoFromServer();
		break;
	case ID_GAME_MESSAGE_RECV_CHAT_MESSAGE_FROM_FRIEND:
		netRecvCharMessageFromFriend();
		break;
	case ID_GAME_MESSAGE_RECV_OTHER_CLIENT_INFO_FROM_SERVER:
		netRecvPickedClientInfoFromServer();
		break;
	case ID_GAME_MESSAGE_ADD_AS_FRIEND_FROM_SERVER:
		netRecvAddAsFriendFromServer();
		break;
	case ID_GAME_MESSAGE_RECV_VIDEO_CHAT_FROM_OTHER_CLIENT:
		netRecvVideoChatFromOtherClient();
		break;
	case ID_GAME_MESSAGE_RECV_VOICE_CHAT_FROM_OTHER_CLIENT:
		netRecvVoiceChatFromOtherClient();
		break;
	case ID_GAME_MESSAGE_MODIFY_PERSONAL_INFO_FROM_SERVER:
		netRecvModifyPersonalInfoFromServer();
		break;
	case ID_GAME_MESSAGE_SEND_SEND_FILE_REQUEST:
		netRecvSendFileRequset();
		break;
	case ID_GAME_MESSAGE_SEND_IS_ACCEPT_SEND_FILE_REQUEST:
		netRecvIsAcceptSendFileRequest();
		break;
	case ID_GAME_MESSAGE_GET_BUILDING_COMMENT_SERVER:
		netRecvGetBuildingComment();
		break;
	default:
		printf("Message with identifier %i has arrived.\n", /*packet->data[0]*/packetIdentifier);
		break;
	}
	peerClient->DeallocatePacket(packet);

	return wonderLandStart;
}

void netClient::getOtherClientPosition(vector<vector3df> &position)
{
	position.clear();
	for (int i=0;i!=otherClient.size();i++)
	{
		position.push_back(otherClient[i]->getPosition());
	}

}

void netClient::closeClient()
{
	netSendClientShutdown();

	peerClient->Shutdown(300);
	RakPeerInterface::DestroyInstance(peerClient);
}

vector<cOtherClient*> netClient::getOtherClient()
{
	return this->otherClient;
}


int netClient::netRecvLandFromSever()
{
	cout<<"netRecvLandFromSever()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(landResult);

	displayLandResult();

	cout<<"netRecvLandFromSever()-finished"<<endl;

	return landResult;
}
void netClient::netRecvRegisterFromSever()
{
	cout<<"netRecvRegisterFromSever()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(registerResult);

	displayRegisterResult();

	// 注册成功，关闭注册窗口
	if (registerResult == 1)
	{
		IGUIEnvironment* env=this->device->getGUIEnvironment();
		IGUIElement* root=env->getRootGUIElement();
		IGUIElement* e=root->getElementFromId(GUI_ID_REGISTER_FAILED_WINDOW,true);
		if (e)
		{
			e->remove();
		}
	}

	cout<<"netRecvRegisterFromSever()-finished"<<endl;
}

void netClient::netSendLandToSever(stringc newName,stringc newPassword)
{
	cout<<"netSendLandToSever()-started"<<endl;

	core::stringc s=newName+newPassword;
	const char* mes=s.c_str();
	RakString message(mes);

	this->useTimeStamp=ID_TIMESTAMP;
	this->timeStamp=RakNet::GetTime();
	this->typeId=ID_GAME_MESSAGE_SEND_LAND_TO_SEVER;

	RakNet::BitStream bsOut;

	bsOut.Write(typeId);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(newName.c_str(),256,&bsOut);
	stringCompressor.EncodeString(newPassword.c_str(),256,&bsOut);
	
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netSendLandToSever()-finished"<<endl;
}
void netClient::netSendRegisterMessageToSever(stringc newName,stringc newPassword,
	stringc nickName, stringc signature,stringc sex,stringc age,stringc adddress)
{
	cout<<"netSendRegisterToSever()-started"<<endl;


	this->useTimeStamp=ID_TIMESTAMP;
	this->timeStamp=RakNet::GetTime();
	this->typeId=ID_GAME_MESSAGE_SEND_REGISTER_TO_SEVER;

	RakNet::BitStream bsOut;

	bsOut.Write(typeId);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(newName.c_str(),256,&bsOut);
	stringCompressor.EncodeString(newPassword.c_str(),256,&bsOut);
	stringCompressor.EncodeString(nickName.c_str(),256,&bsOut);
	stringCompressor.EncodeString(signature.c_str(),256,&bsOut);
	stringCompressor.EncodeString(sex.c_str(),256,&bsOut);
	stringCompressor.EncodeString(age.c_str(),256,&bsOut);
	stringCompressor.EncodeString(adddress.c_str(),256,&bsOut);
	
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netSendRegisterToSever()-finished"<<endl;
}

void netClient::displayLandResult()
{
	IGUIEnvironment* env = this->device->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	wchar_t* s;

	switch (landResult)
	{
	case 0:
		s=NULL;
		break;
	case 1:
		s=L"Land Succeed";
		break;
	case 2:
		s=L"Land Failed";
		break;
	default:
		break;
	}

	//s = root->getElementFromId(GUI_ID_TEXT_PERSON_SAY_STRING, true)->getText();
	root->getElementFromId(GUI_ID_TEXT_LAND_AND_REGISTER_RESULT, true)->setText(s);
}
void netClient::displayRegisterResult()
{
	IGUIEnvironment* env = this->device->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	wchar_t* s;

	switch (registerResult)
	{
	case 0:
		s=L"Register Failed-the same user name";
		break;
	case 1:
		s=L"Register Succeed";
		break;
	case 2:
		s=L"Register Failed-other problems";
		break;
	default: 
		break;
	}

	//s = root->getElementFromId(GUI_ID_TEXT_PERSON_SAY_STRING, true)->getText();
	root->getElementFromId(GUI_ID_TEXT_LAND_AND_REGISTER_RESULT, true)->setText(s);
}

void netClient::netRecvMyInfoMessageToServer()
{
	cout<<"netRecvMyInfoMessageToServer()-started"<<endl;
	this->typeId=ID_GAME_MESSAGE_RECV_MYINFO_MESSAGE_TO_SEVER;

	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->userName.c_str(),256,&bsOut);	

	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	cout<<"netRecvMyInfoMessageToServer()-finished"<<endl;
}

void netClient::netRecvMyInfoMessageFromServer()
{
	cout<<"netRecvMyInfoMessageFromServer()-started"<<endl;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	StringCompressor stringCompressor;
	char userNameTemp[256];
	char passwordTemp[256];
	char nickNameTemp[256];
	char signatureTemp[256];
	char sexTemp[256];
	char ageTemp[256];
	char adddressTemp[256];
	stringCompressor.DecodeString(userNameTemp,256,&bsIn);
	stringCompressor.DecodeString(passwordTemp,256,&bsIn);
	stringCompressor.DecodeString(nickNameTemp,256,&bsIn);
	stringCompressor.DecodeString(signatureTemp,256,&bsIn);
	stringCompressor.DecodeString(sexTemp,256,&bsIn);
	stringCompressor.DecodeString(ageTemp,256,&bsIn);
	stringCompressor.DecodeString(adddressTemp,256,&bsIn);

	std::string strTemp;
	strTemp.assign(userNameTemp);
	this->userName=strTemp.c_str();
	strTemp.assign(passwordTemp);
	this->password=strTemp.c_str();
	strTemp.assign(nickNameTemp);
	this->nickName=strTemp.c_str();
	strTemp.assign(signatureTemp);
	this->signature=strTemp.c_str();
	strTemp.assign(sexTemp);
	this->sex=strTemp.c_str();
	strTemp.assign(ageTemp);
	this->age=strTemp.c_str();
	strTemp.assign(adddressTemp);
	this->adddress=strTemp.c_str();

//	myGui.CreateMyInfoBox(this->userName,this->password,this->nickName,this->signature,
//		this->sex,this->age,this->adddress);

	cout<<"netRecvMyInfoMessageFromServer()-finished"<<endl;
}


void netClient::netSendModifyMyPersonalInfoToServer()
{
	cout<<"netSendModifyPersonalInfoToServer()-started"<<endl;

	this->typeId=ID_GAME_MESSAGE_MODIFY_PERSONAL_INFO_TO_SERVER;
	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	StringCompressor stringCompressor;

	IGUIEnvironment* env=this->device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	stringc userNameTemp;
	stringc passwordTemp;
	stringc nickNameTemp;
	stringc signatureTemp;
	stringc sexTemp;
	stringc ageTemp;
	stringc adddressTemp;

	userNameTemp=root->getElementFromId(GUI_ID_MYINFO_WINDOW_TEXT_USER_NAME, true)->getText();
	passwordTemp=root->getElementFromId(GUI_ID_MYINFO_WINDOW_TEXT_PASSWORD, true)->getText();
	nickNameTemp=root->getElementFromId(GUI_ID_MYINFO_WINDOW_TEXT_NICK_NAME, true)->getText();
	signatureTemp=root->getElementFromId(GUI_ID_MYINFO_WINDOW_TEXT_SINGATURE, true)->getText();
	sexTemp=root->getElementFromId(GUI_ID_MYINFO_WINDOW_TEXT_SEX, true)->getText();
	ageTemp=root->getElementFromId(GUI_ID_MYINFO_WINDOW_TEXT_AGE, true)->getText();
	adddressTemp=root->getElementFromId(GUI_ID_MYINFO_WINDOW_TEXT_ADDRESS, true)->getText();

	stringCompressor.EncodeString(userNameTemp.c_str(),256,&bsOut);
	stringCompressor.EncodeString(passwordTemp.c_str(),256,&bsOut);
	stringCompressor.EncodeString(nickNameTemp.c_str(),256,&bsOut);
	stringCompressor.EncodeString(signatureTemp.c_str(),256,&bsOut);
	stringCompressor.EncodeString(sexTemp.c_str(),256,&bsOut);
	stringCompressor.EncodeString(ageTemp.c_str(),256,&bsOut);
	stringCompressor.EncodeString(adddressTemp.c_str(),256,&bsOut);

	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netSendModifyPersonalInfoToServer()-finished"<<endl;
}
void netClient::netRecvModifyPersonalInfoFromServer()
{
	cout<<"netRecvModifyPersonalInfoFromServer()-started"<<endl;
	
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bool modifyResult=false;
	bsIn.Read(modifyResult);
	if (modifyResult == true)
	{
		StringCompressor stringCompressor;
		char userNameTemp[256];
		char passwordTemp[256];
		char nickNameTemp[256];
		char signatureTemp[256];
		char sexTemp[256];
		char ageTemp[256];
		char adddressTemp[256];
		stringCompressor.DecodeString(userNameTemp,256,&bsIn);
		stringCompressor.DecodeString(passwordTemp,256,&bsIn);
		stringCompressor.DecodeString(nickNameTemp,256,&bsIn);
		stringCompressor.DecodeString(signatureTemp,256,&bsIn);
		stringCompressor.DecodeString(sexTemp,256,&bsIn);
		stringCompressor.DecodeString(ageTemp,256,&bsIn);
		stringCompressor.DecodeString(adddressTemp,256,&bsIn);

		std::string strTemp;
		strTemp.assign(userNameTemp);
		this->userName=strTemp.c_str();
		strTemp.assign(passwordTemp);
		this->password=strTemp.c_str();
		strTemp.assign(nickNameTemp);
		this->nickName=strTemp.c_str();
		strTemp.assign(signatureTemp);
		this->signature=strTemp.c_str();
		strTemp.assign(sexTemp);
		this->sex=strTemp.c_str();
		strTemp.assign(ageTemp);
		this->age=strTemp.c_str();
		strTemp.assign(adddressTemp);
		this->adddress=strTemp.c_str();
	}
	myGui.CreateModityResultBox(modifyResult);

	if (modifyResult == true)
	{
		IGUIEnvironment* env=this->device->getGUIEnvironment();
		IGUIElement* root=env->getRootGUIElement();
		IGUIElement* e=root->getElementFromId(GUI_ID_MYINFO_WINDOW,true);
		if (e)
		{
			e->remove();
		}
	}

	cout<<"netRecvModifyPersonalInfoFromServer()-finished"<<endl;
}


void netClient::netRecvFriendListToServer()
{
	cout<<"netRecvFriendListToServer()-started"<<endl;
	this->typeId=ID_GAME_MESSAGE_RECV_FRIENDLIST_TO_SEVER;

	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->userName.c_str(),256,&bsOut);	

	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	cout<<"netRecvFriendListToServer()-finished"<<endl;
}
void netClient::netRecvFriendListFromServer()
{
	cout<<"netRecvFriendListFromServer()-started"<<endl;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	unsigned int friendListSize=0;
	vector<std::string> friendList;
	bsIn.Read(friendListSize);
	StringCompressor stringCompressor;
	char friendName[256];
	std::string friendNameStr;
	for (int i=0;i!=friendListSize;i++)
	{		
		stringCompressor.DecodeString(friendName,256,&bsIn);	
		friendNameStr.assign(friendName);
		friendList.push_back(friendNameStr);
	}
	
	this->setFriendList(friendList);

//	myGui.CreateFriendListBox(friendList);
	cout<<"netRecvFriendListFromServer()-finished"<<endl;
}

void netClient::setPickedFriend(int friendNo)
{
	this->pickedFriend=friendNo;
}
int netClient::getPickedfriend()
{
	return this->pickedFriend;
}

void netClient::netRecvFriendPersonalInfoToServer(std::string friendName)
{
	cout<<"netRecvFriendPersonalInfoToServer()-started"<<endl;
	this->typeId=ID_GAME_MESSAGE_RECV_FRIEND_PERSONAL_INFO_TO_SEVER;

	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->userName.c_str(),256,&bsOut);	
	stringCompressor.EncodeString(friendName.c_str(),256,&bsOut);

	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	cout<<"netRecvFriendPersonalInfoToServer()-finished"<<endl;
}
void netClient::netRecvFriendPersonalInfoFromServer()
{
	cout<<"netRecvFriendInfoFromServer()-started"<<endl;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	StringCompressor stringCompressor;
	char userNameTemp[256];
	char nickNameTemp[256];
	char signatureTemp[256];
	char sexTemp[256];
	char ageTemp[256];
	char adddressTemp[256];
	stringCompressor.DecodeString(userNameTemp,256,&bsIn);
	stringCompressor.DecodeString(nickNameTemp,256,&bsIn);
	stringCompressor.DecodeString(signatureTemp,256,&bsIn);
	stringCompressor.DecodeString(sexTemp,256,&bsIn);
	stringCompressor.DecodeString(ageTemp,256,&bsIn);
	stringCompressor.DecodeString(adddressTemp,256,&bsIn);

	stringc strTempUserName;
	strTempUserName.append(userNameTemp);	
	stringc strTempNickName;
	strTempNickName.append(nickNameTemp);	
	stringc strTempSignature;
	strTempSignature.append(signatureTemp);	
	stringc strTempSex;
	strTempSex.append(sexTemp);	
	stringc strTempAge;
	strTempAge.append(ageTemp);	
	stringc strTempAddress;
	strTempAddress.append(adddressTemp);
	
	myGui.CreateFriendPersonalInfoBox(strTempUserName,strTempNickName,strTempSignature,strTempSex,
		strTempAge,strTempAddress);
	cout<<"netRecvFriendInfoFromServer()-finished"<<endl;
}

void netClient::netSendChatMessageToFriend()
{
	cout<<"netSendChatMessageToFriend()-started"<<endl;

	IGUIEnvironment* env = device->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	IGUIElement* dlg = root->getElementFromId(GUI_ID_TEXT_CHAT_WINDOW_FRIEND, true);
	core::stringc s;

	s = root->getElementFromId(GUI_ID_TEXT_PERSON_SAY_STRING_FRIEND, true)->getText();
	root->getElementFromId(GUI_ID_TEXT_PERSON_SAY_STRING_FRIEND, true)->setText(L"");
	const char* mes=s.c_str();
	RakString message(mes);

	this->useTimeStamp=ID_TIMESTAMP;
	this->timeStamp=RakNet::GetTime();
	this->typeId=ID_GAME_MESSAGE_SEND_CHAT_MESSAGE_TO_FRIEND;

	RakNet::BitStream bsOut;
	if (friendList.empty() == true)
	{
		cout<<"netSendChatMessageToFriend-friendList is null!"<<endl;
		return;
	}
	if (friendList[pickedFriend].length() == 0)
	{
		cout<<"netSendChatMessageToFriend-friendList error!"<<endl;
	}

/*	if (textChatString.size()==0)			// 若为发起会话者，textChatString开始为空
	{
		textChatClient=pickedClient;
	} 
	else									// 若是被动的接收会话,则发起对话者在接收信息时已被记录
	{	
		
	}*/
	bsOut.Write(typeId);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->getUserName().c_str(),256,&bsOut);
	stringCompressor.EncodeString(friendList[pickedFriend].c_str(),256,&bsOut);
	stringCompressor.EncodeString(message.C_String(),256,&bsOut);

	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	// 更新对话框中的信息
	IGUIStaticText *  aniInfo = (IGUIStaticText *)(dlg->getElementFromId(GUI_ID_TEXT_STRING_FRIEND, true));
	if (aniInfo)
	{
		core::stringw str(L"I said: ");
		str += message.C_String();
		str += "\r\n";
		textChatString+=str;
		aniInfo->setText(textChatString.c_str());
	}

	cout<<"netSendChatMessageToFriend()-finished"<<endl;
}
void netClient::netRecvCharMessageFromFriend()
{
	cout<<"netRecvCharMessageFromFriend()-started"<<endl;

	// 接受到来自服务器的数据
	char recvMessage[256];
	std::string message;
	StringCompressor stringCompressor;
//	char friendName[256];
	char chatStartClient[256];
	char chatRecvClient[256];
	BitStream bsIn(packet->data,packet->length,false);	
	bsIn.IgnoreBytes(sizeof(MessageID));
	stringCompressor.DecodeString(chatStartClient,256,&bsIn);
	stringCompressor.DecodeString(chatRecvClient,256,&bsIn);
	stringCompressor.DecodeString(recvMessage,256,&bsIn);
	message.assign(recvMessage);
	
	if (this->userName.equals_ignore_case(chatRecvClient) == false)
	{
		return;
	}

	// 确定聊天对象在好友列表中的位置
	for (int i=0;i!=friendList.size();i++)
	{
		if (friendList[i].compare(chatStartClient)==0)
		{
			pickedFriend=i;
			break;
		}
	}
	//	this->myGui.CreateTextChatBox();
	IGUIEnvironment* env = device->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	IGUIElement* dlg = root->getElementFromId(GUI_ID_TEXT_CHAT_WINDOW_FRIEND, true);

	// 创建文本聊天窗口
	if (dlg)
	{
		dlg->remove();
	}
	
	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,550,350),false,L"Friend Text Chat Window",0,GUI_ID_TEXT_CHAT_WINDOW_FRIEND);
	// 说话人的姓名
	env->addStaticText(L"I say:",rect<s32>(10,270,50,290),false,false,wnd);
	env->addEditBox(L"",rect<s32>(50,270,325,290),true,wnd,GUI_ID_TEXT_PERSON_SAY_STRING_FRIEND);
	env->addButton(rect<s32>(325,270,350,290),wnd,GUI_ID_BUTTON_SEND_CHAT_MESSAGE_FRIEND,L"Send");
	env->addStaticText(L"",rect<s32>(0,30,350,250),true,true,wnd,GUI_ID_TEXT_STRING_FRIEND);




	// 更新对话框中的信息
	dlg = root->getElementFromId(GUI_ID_TEXT_CHAT_WINDOW_FRIEND, true);
	IGUIStaticText *  aniInfo = (IGUIStaticText *)(dlg->getElementFromId(GUI_ID_TEXT_STRING_FRIEND, true));
	if (aniInfo)
	{
		//core::stringw str(L"He said: ");
		core::stringw str;
		str.append(chatStartClient);
		str.append(L" said: ");
		str += message.c_str();
		str += "\r\n";
		textChatString+=str;
		aniInfo->setText(textChatString.c_str());
	}

	cout<<"netRecvCharMessageFromFriend()-finished"<<endl;
}

void netClient::netSendAddAsFriendToServer()
{
	cout<<"netSendAddAsFriendToServer()-started"<<endl;
	
	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_ADD_AS_FRIEND_TO_SERVER;
	bsOut.Write(typeId);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->userName.c_str(),256,&bsOut);
	stringCompressor.EncodeString(this->pickedClient.getOtherClientUserName().c_str(),256,&bsOut);
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	
	cout<<"netSendAddAsFriendToServer()-finished"<<endl;
}
void netClient::netRecvAddAsFriendFromServer()
{
	cout<<"netRecvAddAsFriendFromServer()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bool addFriendResult=false;
	bsIn.Read(addFriendResult);
	StringCompressor stringCompressor;
	char friendNameTemp[256];
	stringCompressor.DecodeString(friendNameTemp,256,&bsIn);
	std::string friendNameStr;
	friendNameStr.assign(friendNameTemp);
	if (addFriendResult == true)	// 增加好友成功，更新好友列表
	{
		friendList.push_back(friendNameStr);
	}
	myGui.CreateAddFriendResultBox(addFriendResult);
	cout<<"netRecvAddAsFriendFromServer()-finished"<<endl;
}

// 需要经过服务器转发给选中的客户机？？
void netClient::netSendVideoChatToOtherClient()
{
	cout<<"netSendVideoChatToOtherClient()-started"<<endl;

	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_SEND_VIDEO_CHAT_TO_OTHER_CLIENT;
	bsOut.Write(this->typeId);
	int roomNo=GetTickCount();
	bsOut.Write(roomNo);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->getUserName().c_str(),256,&bsOut);
	stringCompressor.EncodeString(this->pickedClient.getOtherClientUserName().c_str(),256,&bsOut);
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netSendVideoChatToOtherClient()-finished"<<endl;
}
void netClient::netRecvVideoChatFromOtherClient()
{
	cout<<"netRecvVideoChatFromOtherClient()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	int roomNum=0;
	bsIn.Read(roomNum);
	StringCompressor stringCompressor;
	char sendVideoChatClient[256];
	char recvVideoChatClient[256];
	stringCompressor.DecodeString(sendVideoChatClient,256,&bsIn);
	stringCompressor.DecodeString(recvVideoChatClient,256,&bsIn);

	if (this->getUserName().equals_ignore_case(sendVideoChatClient) == true)
	{
		return;
	}

	HINSTANCE his=ShellExecute(NULL,"open","..\..\BRAnyChatSDKDemo.exe",NULL,NULL,SW_SHOWNORMAL);
	cout<<his<<endl;
	his=ShellExecute(NULL,"open","NOTEPAD.EXE",NULL,NULL,SW_SHOWNORMAL);
	cout<<his<<endl;

	if (this->getUserName().equals_ignore_case(recvVideoChatClient) == true)
	{
		cout<<"开始视频聊天"<<endl;
	}

	cout<<"netRecvVideoChatFromOtherClient()-finished"<<endl;
}

void netClient::netSendVoiceChatToOtherClient()
{
	cout<<"netSendVoiceChatToOtherClient()-started"<<endl;

	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_SEND_VOICE_CHAT_TO_OTHER_CLIENT;
	bsOut.Write(this->typeId);
	int roomNo=GetTickCount();
	bsOut.Write(roomNo);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->getUserName().c_str(),256,&bsOut);
	stringCompressor.EncodeString(this->pickedClient.getOtherClientUserName().c_str(),256,&bsOut);
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netSendVoiceChatToOtherClient()-finished"<<endl;
}
void netClient::netRecvVoiceChatFromOtherClient()
{
	cout<<"netRecvVoiceChatFromOtherClient()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	int roomNum=0;
	bsIn.Read(roomNum);
	StringCompressor stringCompressor;
	char sendVideoChatClient[256];
	char recvVideoChatClient[256];
	stringCompressor.DecodeString(sendVideoChatClient,256,&bsIn);
	stringCompressor.DecodeString(recvVideoChatClient,256,&bsIn);

	if (this->getUserName().equals_ignore_case(sendVideoChatClient) == true)
	{
		return;
	}

	ShellExecute(NULL,"open","voice192.168.1.100.EXE",NULL,NULL,SW_SHOWNORMAL);

	if (this->getUserName().equals_ignore_case(recvVideoChatClient) == true)
	{
		cout<<"开始语音聊天"<<endl;
	}

	cout<<"netRecvVoiceChatFromOtherClient()-finished"<<endl;
}


// 发送文件之前先发送请求
void netClient::netSendSendFileRequset(const c8* fn)
{
	cout<<"netSendSendFileRequset()-started"<<endl;

	this->typeId=ID_GAME_MESSAGE_SEND_SEND_FILE_REQUEST;
	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	StringCompressor stringCompressor;
	stringCompressor.EncodeString(this->getUserName().c_str(),256,&bsOut);
	stringCompressor.EncodeString(this->pickedClient.getOtherClientUserName().c_str(),256,&bsOut);
	stringCompressor.EncodeString(fn,256,&bsOut);
//	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,this->pickedClient.getAddress(),true);
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netSendSendFileRequset()-finished"<<endl;
}
void netClient::netRecvSendFileRequset()
{
	cout<<"netRecvSendFileRequset()-started"<<endl;
	RakNet::BitStream bsIn(packet->data,packet->length,false);
	StringCompressor stringCompressor;
	bsIn.IgnoreBytes(sizeof(MessageID));
	char senderName[256];
	char recverName[256];
	char filename[256];
	stringCompressor.DecodeString(senderName,256,&bsIn);
	stringCompressor.DecodeString(recverName,256,&bsIn);
	stringCompressor.DecodeString(filename,256,&bsIn);

	if (this->getUserName().equals_ignore_case(recverName) == true)
	{
		for (int i=0;i!=this->otherClient.size();i++)
		{
			if (this->otherClient[i]->getOtherClientUserName().equals_ignore_case(senderName))
			{
				this->pickedClient=*(this->otherClient[i]);
			}
		}
		cout<<"RECVED"<<endl;
	}

	this->myGui.CreateIsRecvFileBox(senderName,recverName,filename);

	cout<<"netRecvSendFileRequset()-finished"<<endl;
}


void netClient::netSendIsAcceptSendFileRequest(bool isAcccept)
{
	cout<<"netSendIsAcceptSendFileRequest()-started"<<endl;

	this->typeId=ID_GAME_MESSAGE_SEND_IS_ACCEPT_SEND_FILE_REQUEST;
	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	bsOut.Write(isAcccept);
	StringCompressor stringCompressor;
//	stringCompressor.EncodeString(this->getPickedClient().getSystemAddress().ToString(),256,&bsOut);
	bsOut.Write(this->getPickedClient().getSystemAddress());
	bsOut.Write(this->systemAddress);
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,UNASSIGNED_SYSTEM_ADDRESS,true);
	//	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);

	if (isAcccept == true)
	{
		cout<<"netSendIsAcceptSendFileRequest()-finished"<<endl;
		this->netRecvFile();
	}
	else
	{
		cout<<"netSendIsAcceptSendFileRequest()-finished"<<endl;
		return;
	}

//	cout<<"netSendIsAcceptSendFileRequest()-finished"<<endl;
}
void netClient::netRecvIsAcceptSendFileRequest()
{
	cout<<"netRecvIsAcceptSendFileRequest()-started"<<endl;

	RakNet::BitStream bsIn(packet->data,packet->length,false);
	StringCompressor stringCompressor;
	bsIn.IgnoreBytes(sizeof(MessageID));
	bool isAccept=false;
	bsIn.Read(isAccept);
	SystemAddress saFileSender;
	SystemAddress saFileReceiver;
	bsIn.Read(saFileSender);
	bsIn.Read(saFileReceiver);
	if (saFileSender != this->GetSystemAddress())
	{
		cout<<"netRecvIsAcceptSendFileRequest()-finished"<<endl;
		return;
	}

	if (isAccept == true)
	{
		cout<<"netRecvIsAcceptSendFileRequest()-finished"<<endl;
		this->netSendFile();
	}
	else
	{
		cout<<"netRecvIsAcceptSendFileRequest()-finished"<<endl;
		return;
	}
	
//	cout<<"netRecvIsAcceptSendFileRequest()-finished"<<endl;
}


// 发送文件
void netClient::netSendFile()
{
	cout<<"netSendFile()-started"<<endl;

	RakNet::RakString file;
	RakNet::RakString fileCopy;

	TestCB testCB;
	RakNet::FileListTransfer flt1;
	RakNet::PacketizedTCP tcp1;
	const bool testInet6=false;

	tcp1.Start(60100,1,-99999,AF_INET);

	tcp1.AttachPlugin(&flt1);


	// Run incremental reads in a thread so the read does not block the main thread
	flt1.StartIncrementalReadThreads(1);
	RakNet::FileList fileList;
	RakNet::IncrementalReadInterface incrementalReadInterface;
//	printf("Enter complete filename with path to test:\n");
	char str[256];
//	Gets(str, sizeof(str));
//	if (str[0]==0)
	strcpy(str,"E:\\1.txt" /*"D:\\RakNet\\Lib\\RakNetLibStaticDebug.lib"*/);
	file=str;
	fileCopy="E:\\2.txt";
	testCB.setFile(file);
	fileCopy.Clear();
	testCB.setFileCopy(fileCopy);

	unsigned int fileLength = GetFileLength(file.C_String());
	if (fileLength==0)
	{
		printf("Test file %s not found.\n", file.C_String());
		return ;
	}
	fileList.AddFile(file.C_String(), file.C_String(), 0, fileLength, fileLength, FileListNodeContext(0,0), true);

	printf("File added.\n");
	RakSleep(100);
	RakNet::Packet *packet1;


	SYSTEMTIME curTime;
	SYSTEMTIME preTime;
	GetLocalTime(&curTime);
	preTime=curTime;
	while (1)
	{
		packet1=tcp1.Receive();
		RakNet::SystemAddress sa;
		sa = tcp1.HasNewIncomingConnection();
		if (sa!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
			flt1.Send(&fileList,0,sa,0,HIGH_PRIORITY,0, &incrementalReadInterface, 2000000);
		tcp1.DeallocatePacket(packet1);
		RakSleep(0);
		GetLocalTime(&curTime);
		if ((curTime.wSecond-preTime.wSecond)>5)
		{
			break;
		}
	}

	cout<<"netSendFile()-finished"<<endl;
}
void netClient::netRecvFile()
{
	cout<<"netRecvFile()-started"<<endl;

	RakNet::RakString file;
	RakNet::RakString fileCopy;

	TestCB testCB;
	RakNet::FileListTransfer flt2;
	RakNet::PacketizedTCP tcp2;

	const bool testInet6=false;

	tcp2.Start(60100,1,-99999,AF_INET);
	tcp2.Connect("127.0.0.1",60101,false,AF_INET);

	tcp2.AttachPlugin(&flt2);

	file="E:\\1.txt";		// 如果接收方没有该文件是否也可运行
	fileCopy="E:\\2.txt";
	testCB.setFile(file);
	testCB.setFileCopy(fileCopy);

	RakNet::Packet *packet2;

	while (1)
	{
		RakNet::SystemAddress sa;
		sa=tcp2.HasCompletedConnectionAttempt();
		if (sa!=RakNet::UNASSIGNED_SYSTEM_ADDRESS)
		{
			flt2.SetupReceive(&testCB, false, sa);
			break;
		}
		RakSleep(30);
	}

	SYSTEMTIME curTime;
	SYSTEMTIME preTime;
	GetLocalTime(&curTime);
	preTime=curTime;
	while (1)
	{
		packet2=tcp2.Receive();
		tcp2.DeallocatePacket(packet2);
		RakSleep(0);
		GetLocalTime(&curTime);
		if ((curTime.wSecond-preTime.wSecond)>5)
		{
			break;
		}
	}

	cout<<"netRecvFile()-finished"<<endl;
}


// 点击某一建筑，获取用户评论信息
void netClient::netSendGetBuildingComment(int newBuildingID)
{
	cout<<"netSendGetBuildingComment()-started"<<endl;

	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_GET_BUILDING_COMMENT_CLIENT;
	bsOut.Write(typeId);
	bsOut.Write(newBuildingID);
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);


	cout<<"netSendGetBuildingComment()-finished"<<endl;
}
void netClient::netRecvGetBuildingComment()
{
	cout<<"netRecvGetBuildingComment()-started"<<endl;

	RakNet::BitStream bsIn(packet->data,packet->length,false);
	StringCompressor stringCompressor;
	bsIn.IgnoreBytes(sizeof(MessageID));
	//////////////////////////////////////////////////////////////////////////
	CBuildingComment buildingComment;
	int commentSize;
	bsIn.Read(commentSize);
	for (int i=0;i!=commentSize;i++)
	{
		CBuildingCommentContent commentTemp;
		char charTemp[256];
		std::string strtemp;
		stringCompressor.DecodeString(charTemp,256,&bsIn);
		strtemp.assign(charTemp);
		commentTemp.SetName(strtemp);
		stringCompressor.DecodeString(charTemp,256,&bsIn);
		strtemp.assign(charTemp);
		commentTemp.SetComment(strtemp);
		stringCompressor.DecodeString(charTemp,256,&bsIn);
		strtemp.assign(charTemp);
		commentTemp.SetCommentTime(strtemp);
		buildingComment.AddComment(commentTemp);
	}
	//////////////////////////////////////////////////////////////////////////
	CBuilding buildingTemp=this->myGui.GetBuilding();
	buildingTemp.SetBuildingComment(buildingComment);
	this->myGui.SetBuilding(buildingTemp);
	this->myGui.UpdateBuildingComment(0);

	cout<<"netRecvGetBuildingComment()-finished"<<endl;
}

void netClient::netSendClientBuildingComment(int newBuildingID)
{
	cout<<"netSendClientBuildingComment()-started"<<endl;

	IGUIEnvironment* env = device->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	IGUIElement* dlg = root->getElementFromId(GUI_ID_BUILDING_INFORMATION_WINDOW, true);
	core::stringc s;

	s = root->getElementFromId(GUI_ID_EDIT_BOX_MY_COMMENT, true)->getText();
	root->getElementFromId(GUI_ID_EDIT_BOX_MY_COMMENT, true)->setText(L"");
	const char* mes=s.c_str();
	RakString message(mes);

	this->useTimeStamp=ID_TIMESTAMP;
	this->timeStamp=RakNet::GetTime();
	this->typeId=ID_GAME_MESSAGE_SEND_CLIENT_BUILDING_COMMENT;

	RakNet::BitStream bsOut;

	// 获取系统时间
	tm T;
	SYSTEMTIME curTime;
	char charTime[40];
	GetLocalTime(&curTime);
	T.tm_year=curTime.wYear-1900;
	T.tm_mon=curTime.wMonth-1;
	T.tm_mday=curTime.wDay;
	T.tm_hour=curTime.wHour;
	T.tm_min=curTime.wMinute;
	T.tm_sec=curTime.wSecond;
	strftime(charTime,sizeof(charTime),"%Y-%m-%d %H:%M:%S",&T);

	bsOut.Write(typeId);
	StringCompressor stringCompressor;
	bsOut.Write(newBuildingID);
	stringCompressor.EncodeString(this->getUserName().c_str(),256,&bsOut);
	stringCompressor.EncodeString(message.C_String(),256,&bsOut);
	//bsOut.Write(message);
	stringCompressor.EncodeString(charTime,256,&bsOut);
	peerClient->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	// 更新对话框中的信息
	IGUIStaticText *  aniInfo = (IGUIStaticText *)(dlg->getElementFromId(GUI_ID_STATIC_TEXT_OTHER_COMMENT, true));
	if (aniInfo)
	{
		std::string strTemp;
		strTemp.clear();
		strTemp.append("PUBLISHER:		");
		strTemp.append(this->userName.c_str());
		strTemp.append("\r\n");
		strTemp.append("CONTENT:		");
		strTemp.append(message);
		strTemp.append("\r\n");
		strTemp.append("TIME:		");	
		strTemp.append(charTime);
		strTemp.append("\r\n");
		strTemp.append("----------------------------------------------");
		strTemp.append("\r\n");
		core::stringw commentHistory;
		commentHistory=root->getElementFromId(GUI_ID_STATIC_TEXT_OTHER_COMMENT, true)->getText();
 		core::stringw str(strTemp.c_str());
		commentHistory+=str;
		aniInfo->setText(commentHistory.c_str());
	}

	cout<<"netSendClientBuildingComment()-finished"<<endl;
}
