#include "netSever.h"

netSever::netSever()
{
//	clientPosition=(0.0f,0.0f,0.0f);
}

netSever::netSever(const netSever&)
{

}

netSever::~netSever()
{

}

void netSever::netInitialize()
{
	peerSever = RakNet::RakPeerInterface::GetInstance();


	RakNet::SocketDescriptor sd(SERVER_PORT,0);
	sd.socketFamily=AF_INET;
	bool result = (peerSever->Startup(MAX_CLIENTS, &sd, 1)==RakNet::RAKNET_STARTED);
	if (!result)
	{
		cout<<"Sever Startup-Failed!"<<endl;
		exit(1);
	}

	printf("Starting the server.\n");
	// We need to let the server accept incoming connections from the clients
	peerSever->SetMaximumIncomingConnections(MAX_CLIENTS);
}

unsigned char netSever::GetPacketIdentifier(Packet* p)
{
	if (p==0)
		return 255;
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
	{
		return (unsigned char)p->data[0];
	}
}

void netSever::netRecvLandFromClient()
{
	cout<<"netRecvLandFromClient()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	StringCompressor stringCompressor;
	char userName[256];
	char password[256];

	bsIn.IgnoreBytes(sizeof(MessageID));
	stringCompressor.DecodeString(userName,256,&bsIn);
	stringCompressor.DecodeString(password,256,&bsIn);
	Information registerInfo;
	std::string temp;
	temp.assign(userName);
	registerInfo.setUsername(temp);
	temp.assign(password);
	registerInfo.setPassword(temp);


	Operation operation;
	bool result=operation.log_in(registerInfo);
	if (result==true)
	{
		landResult=1;
		cout<<"netRecvLandFromClient-�û���¼�ɹ�"<<endl;
	}
	else
	{
		landResult=0;
		cout<<"netRecvLandFromClient-�û���¼ʧ��"<<endl;
	}

	cout<<"netRecvLandFromClient()-finished"<<endl;
}
void netSever::netRecvRegisterFromClient()
{
	cout<<"netRecvRegisterFromClient()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	StringCompressor stringCompressor;
	char userName[256];
	char password[256];
	char nickName[256];
	char signature[256];
	char sex[256];
	char age[256];
	char adddress[256];
	stringCompressor.DecodeString(userName,256,&bsIn);
	stringCompressor.DecodeString(password,256,&bsIn);
	stringCompressor.DecodeString(nickName,256,&bsIn);
	stringCompressor.DecodeString(signature,256,&bsIn);
	stringCompressor.DecodeString(sex,256,&bsIn);
	stringCompressor.DecodeString(age,256,&bsIn);
	stringCompressor.DecodeString(adddress,256,&bsIn);

	Information registerInfo;
	std::string temp;
	temp.assign(userName);
	registerInfo.setUsername(temp);
	temp.assign(password);
	registerInfo.setPassword(temp);
	temp.assign(nickName);
	registerInfo.setNickName(temp);
	temp.assign(signature);
	registerInfo.setSignature(temp);
	temp.assign(sex);
	registerInfo.setSex(temp);
	temp.assign(age);
	registerInfo.setAge(temp);
	temp.assign(adddress);
	registerInfo.setAddress(temp);
	
	Operation operation;
	registerResult=operation.sign_In(registerInfo);

	// 0-�û����ظ�
	// 1-ע��ɹ�
	// 2-ע��ʧ�ܣ����������
	switch (registerResult)
	{
	case 0:
		cout<<"ע��ʧ��-�û����ظ�"<<endl;
		break;
	case 1:
		cout<<"ע��ɹ�"<<endl;
		break;
	case 2:
		cout<<"ע��ʧ��-����ԭ��"<<endl;
		break;
	default:
		break;
	}

	// ע��ɹ����趨�û���ʼλ��
	if (registerResult == 1)
	{
		vector3df positionTemp;
		positionTemp.X=0.0f;
		positionTemp.Y=20.0f;
		positionTemp.Z=0.0f;
		std::string positionStr;
		char xChar[20];
		char yChar[20];
		char zChar[20];
		itoa((int)positionTemp.X,xChar,10);
		itoa((int)positionTemp.Y,yChar,10);
		itoa((int)positionTemp.Z,zChar,10);
		positionStr.assign(xChar);
		positionStr.append(",");
		positionStr.append(yChar);
		positionStr.append(",");
		positionStr.append(zChar);

		Location location;
		temp.assign(userName);
		location.setUserName(temp);
		location.setLocation(positionStr);
		Operation operation;
		operation.log_off(location);
	}

	cout<<"netRecvRegisterFromClient()-finished"<<endl;
}
void netSever::netSendLandResultToClient()
{
	cout<<"netSendLandResultToClient()-started"<<endl;

	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_RECV_LAND_FROM_SEVER;

	bsOut.Write(typeId);
	//////////////////////////////////////////////////////////////////////////
	// ���ݿ��ѯ���
	//////////////////////////////////////////////////////////////////////////
	bsOut.Write(landResult);

	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,false);

	cout<<"netSendLandResultToClient()-finished"<<endl;
}
void netSever::netSendRegisterResultToClient()
{
	cout<<"netSendRegisterResultToClient()-started"<<endl;

	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_RECV_REGISTER_FROM_SEVER;
	
	bsOut.Write(typeId);
	//////////////////////////////////////////////////////////////////////////
	// ���ݿ��ѯ���
	//////////////////////////////////////////////////////////////////////////
	bsOut.Write(registerResult);

	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,false);

	cout<<"netSendRegisterResultToClient()-finished"<<endl;
}

void netSever::netRecvModifyPersonalInfoFromClient()
{
	cout<<"netRecvModifyPersonalInfoFromClient()-started"<<endl;

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

	std::string temp;
	Information information;
	temp.assign(userNameTemp);
	information.setUsername(temp);
	temp.assign(passwordTemp);
	information.setPassword(temp);
	temp.assign(nickNameTemp);
	information.setNickName(temp);
	temp.assign(signatureTemp);
	information.setSignature(temp);
	temp.assign(sexTemp);
	information.setSex(temp);
	temp.assign(ageTemp);
	information.setAge(temp);
	temp.assign(adddressTemp);
	information.setAddress(temp);

	bool modifyResult=false;
	Operation operation;
	modifyResult=operation.modify_self(information);
	
	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_MODIFY_PERSONAL_INFO_FROM_SERVER;

	bsOut.Write(typeId);
	bsOut.Write(modifyResult);
	if (modifyResult == true)
	{
		stringCompressor.EncodeString(userNameTemp,256,&bsOut);
		stringCompressor.EncodeString(passwordTemp,256,&bsOut);
		stringCompressor.EncodeString(nickNameTemp,256,&bsOut);
		stringCompressor.EncodeString(signatureTemp,256,&bsOut);
		stringCompressor.EncodeString(sexTemp,256,&bsOut);
		stringCompressor.EncodeString(ageTemp,256,&bsOut);
		stringCompressor.EncodeString(adddressTemp,256,&bsOut);
	}
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,false);

	cout<<"netRecvModifyPersonalInfoFromClient()-finished"<<endl;
}

void netSever::netRecvAddFriendFromClient()
{
	cout<<"netRecvAddFriendFromClient()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	StringCompressor stringCompressor;
	char friendNameTemp[256];
	char clientNameTemp[256];
	stringCompressor.DecodeString(clientNameTemp,256,&bsIn);
	stringCompressor.DecodeString(friendNameTemp,256,&bsIn);
	std::string friendNameStr;
	std::string clientnameStr;
	friendNameStr.assign(friendNameTemp);
	clientnameStr.assign(clientNameTemp);
	Operation operation;
	bool addFriendResult;
	addFriendResult=operation.add_friend(clientnameStr,friendNameStr);
	addFriendResult=operation.add_friend(friendNameStr,clientnameStr);
	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_ADD_AS_FRIEND_FROM_SERVER;
	bsOut.Write(typeId);
	bsOut.Write(addFriendResult);
	stringCompressor.EncodeString(friendNameTemp,256,&bsOut);
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,false);

	cout<<"netRecvAddFriendFromClient()-finished"<<endl;
}

void netSever::netRecvPickedClientInfoToClient()
{
	cout<<"netRecvPickedClientInfoToClient()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	StringCompressor stringCompressor;
	SystemAddress sysAddresstemp;
	NetworkID netIdTemp;
	bsIn.Read(sysAddresstemp);
	bsIn.Read(netIdTemp);
	char clientNameTemp[256];
	stringCompressor.DecodeString(clientNameTemp,256,&bsIn);
	std::string clientNameStr;
	clientNameStr.assign(clientNameTemp);
	for (int i=0;i!=client.size();i++)
	{
		if ((client[i])->getSystemAddresss() == sysAddresstemp)
		{
			if ((client[i])->getNetworkID() == netIdTemp)
			{
				break;
			}
		}
	}
	

	Information information;
	Operation operation;
	information=operation.query_messege(clientNameStr);
	this->typeId=ID_GAME_MESSAGE_RECV_OTHER_CLIENT_INFO_FROM_SERVER;
	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	stringCompressor.EncodeString(information.getUsername().c_str(),256,&bsOut);
	stringCompressor.EncodeString(information.getNickName().c_str(),256,&bsOut);
	stringCompressor.EncodeString(information.getSignature().c_str(),256,&bsOut);	
	stringCompressor.EncodeString(information.getSex().c_str(),256,&bsOut);
	stringCompressor.EncodeString(information.getAge().c_str(),256,&bsOut);
	stringCompressor.EncodeString(information.getAddress().c_str(),256,&bsOut);

	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,false);
	cout<<"netRecvPickedClientInfoToClient()-finished"<<endl;
}
void netSever::netRecvMyInfoMessageToClient()
{
	cout<<"netRecvMyInfoMessageToClient()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	StringCompressor stringCompressor;
	char userNameTemp[256];
	stringCompressor.DecodeString(userNameTemp,256,&bsIn);
	std::string userNameStr;
	userNameStr.assign(userNameTemp);
	Operation operation;
	Information info=operation.query_messege(userNameStr);

	std::string clientUserName=info.getUsername();
	std::string clientPassword=info.getPassword();
	std::string clientNickName=info.getNickName();
	std::string clientSignature=info.getSignature();
	std::string clientSex=info.getSex();
	std::string clientAge=info.getAge();
	std::string clientAddress=info.getAddress();


	this->typeId=ID_GAME_MESSAGE_RECV_MYINFO_MESSAGE_FROM_SEVER;
	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	stringCompressor.EncodeString(clientUserName.c_str(),256,&bsOut);
	stringCompressor.EncodeString(clientPassword.c_str(),256,&bsOut);
	stringCompressor.EncodeString(clientNickName.c_str(),256,&bsOut);
	stringCompressor.EncodeString(clientSignature.c_str(),256,&bsOut);
	stringCompressor.EncodeString(clientSex.c_str(),256,&bsOut);
	stringCompressor.EncodeString(clientAge.c_str(),256,&bsOut);
	stringCompressor.EncodeString(clientAddress.c_str(),256,&bsOut);

	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,false);
	cout<<"netRecvMyInfoMessageToClient()-finished"<<endl;
}

void netSever::netRecvFriendListToClient()
{
	cout<<"netRecvFriendListToClient()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	StringCompressor stringCompressor;
	char userNameTemp[256];
	stringCompressor.DecodeString(userNameTemp,256,&bsIn);
	std::string userNameStr;
	userNameStr.assign(userNameTemp);


	this->typeId=ID_GAME_MESSAGE_RECV_FRIENDLIST_FROM_SEVER;
	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	vector<std::string> friendList;
	Operation operation;
	friendList=operation.query_friends(userNameStr);
	unsigned int friendListSize=friendList.size();
	bsOut.Write(friendListSize);
	for (int i=0;i!=friendList.size();i++)
	{
		stringCompressor.EncodeString(friendList[i].c_str(),256,&bsOut);
	}

	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,false);
	cout<<"netRecvFriendListToClient()-finished"<<endl;
}

void netSever::netRecvFriendPersonalInfoToClient()
{
	cout<<"netRecvFriendPersonalInfoToClient()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));

	StringCompressor stringCompressor;
	char userNameTemp[256];
	char friendNameTemp[256];
	stringCompressor.DecodeString(userNameTemp,256,&bsIn);
	stringCompressor.DecodeString(friendNameTemp,256,&bsIn);
	std::string userNameStr;
	userNameStr.assign(userNameTemp);
	std::string friendNameStr;
	friendNameStr.assign(friendNameTemp);


	this->typeId=ID_GAME_MESSAGE_RECV_FRIEND_PERSONAL_INFO_FROM_SEVER;
	RakNet::BitStream bsOut;
	bsOut.Write(typeId);
	Operation operation;
	Information information;
	information=operation.query_messege(friendNameStr);

	stringCompressor.EncodeString(information.getUsername().c_str(),256,&bsOut);
	stringCompressor.EncodeString(information.getNickName().c_str(),256,&bsOut);
	stringCompressor.EncodeString(information.getSignature().c_str(),256,&bsOut);
	stringCompressor.EncodeString(information.getSex().c_str(),256,&bsOut);
	stringCompressor.EncodeString(information.getAge().c_str(),256,&bsOut);
	stringCompressor.EncodeString(information.getAddress().c_str(),256,&bsOut);

	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,false);
	cout<<"netRecvFriendPersonalInfoToClient()-finished"<<endl;
}

void netSever::netRecvClientFriendTextChatMessage()
{
	cout<<"netRecvClientFriendTextChatMessage()-started"<<endl;

	// �Ự���𷽵���Ϣ�ȴ��ݸ������������������յ��Ự���շ���address��id
	char recvMessage[256];
	StringCompressor stringCompressor;
//	char friendName[256];
	char chatStartClient[256];
	char chatRecvClient[256];
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	stringCompressor.DecodeString(chatStartClient,256,&bsIn);
	stringCompressor.DecodeString(chatRecvClient,256,&bsIn);
	stringCompressor.DecodeString(recvMessage,256,&bsIn);
	

	
	//  ���������Ự��Ϣת�����Ự���𷽵�address�ͻỰ���շ���id
	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_RECV_CHAT_MESSAGE_FROM_FRIEND;
	bsOut.Write(typeId);
	stringCompressor.EncodeString(chatStartClient,256,&bsOut);
	stringCompressor.EncodeString(chatRecvClient,256,&bsOut);
	stringCompressor.EncodeString(recvMessage,256,&bsOut);
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,RakNet::UNASSIGNED_SYSTEM_ADDRESS,true);
	
	cout<<"netRecvClientFriendTextChatMessage()-finished"<<endl;
}

void netSever::netReceiveCreateClient()
{
	cout<<"netReceiveCreateClient()-started"<<endl;

	netClient* newClient=new netClient;	
	vector3df clientPosition;
	char clientNameTemp[256];
	StringCompressor stringCompressor;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(clientPosition);
	stringCompressor.DecodeString(clientNameTemp,2256,&bsIn);
	
	newClient->SetNetworkIDManager(&networkIDManager);
	newClient->setNetworkID(newClient->GetNetworkID());
	newClient->setSystemAddress(packet->systemAddress);
	newClient->setPosition(clientPosition);
	std::string temp;
	temp.assign(clientNameTemp);
	newClient->setClientName(temp);
	client.push_back(newClient);		// ���µ�¼���û�����ĩβ

	// 		SystemAddress addrTemp[10];
	// 		unsigned short numConnections;
	// 		peerSever->GetConnectionList((SystemAddress*)&addrTemp,&numConnections);
	// 		for (int i=0; i < numConnections; i++)
	// 		{
	// 			printf("%i. %s\n", i+1, addrTemp[i].ToString(true));
	// 		}
	// �����½�������Ŀͻ����ĵ�ַ��λ��
	for (int i=0;i!=client.size();i++)
	{
		printf("%i. %s\n", i+1, client[i]->getSystemAddresss().ToString(true));
		cout<<"�ͻ�������"<<client[i]->getClientName()<<"�ͻ�ID��"<<client[i]->getNetworkID()<<"��λ�ã�"<<client[i]->getPosition().X<< " "<<client[i]->getPosition().Y<<" "<<client[i]->getPosition().Z<<endl;
	}
	cout<<endl;

	// delete newClient;			// �Ƿ��������ͷţ�����

	cout<<"netReceiveCreateClient()-finished"<<endl;
}

// ÿ����һ���û���¼ʱ��������Ϊ�����һ��networkID���������û�����Ϣ�㲥�������ѵ�¼���û�
// ͬʱ�����ѵ�¼�û�����Ϣ���͸����û�
void netSever::netSendCreateClient()
{
	cout<<"netSendCreateClient()-started"<<endl;

	
	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_CREATE_CLIENT_FROM_SEVER;
	NetworkID netID=client.at(client.size()-1)->getNetworkID();
	SystemAddress orignAddress=packet->systemAddress;
	vector3df clientPosition=client.at(client.size()-1)->getPosition();
	bsOut.Write(typeId);
	bsOut.Write(clientPosition);
	bsOut.Write(netID);
	bsOut.Write(packet->systemAddress);		// ���ؿͻ����ĵ�ַ

	StringCompressor stringCompressor;
	std:: string clientNameTemp=(client.at(client.size()-1))->getClientName();
	stringCompressor.EncodeString(clientNameTemp.c_str(),256,&bsOut);
	Location location;
	location.setUserName(clientNameTemp);
	Operation operation;
	std::string clientPositionTemp;
	clientPositionTemp = operation.query_loction(location);
	//clientPositionTemp.assign(operation.query_loction(location));
	stringCompressor.EncodeString(clientPositionTemp.c_str(),256,&bsOut);
	bsOut.Write(orignAddress);
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netSendCreateClient()-finished"<<endl;
}

// ÿ����һ���û���¼ʱ�����ѵ�¼�û�����Ϣ���͸����û�
void netSever::netSendOtherOnLineClientInfo()
{
	cout<<"netSendOtherOnLineClientInfo()-started"<<endl;

	if (client.size()-1 == 0)
	{
		cout<<"netSendOtherOnLineClientInfo()-finished"<<endl;
		return;
	}
	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_OTHER_CLIENT_INFO;
	bsOut.Write(typeId);
	int count=0;
	count=client.size();
	bsOut.Write(count);
	StringCompressor stringCompressor;

	for (int i=0;i!=client.size()-1;i++)		// ���һ���û������µ�¼�ģ����÷���
	{
//		bsOut.Write(client[i]->getSystemAddresss());
//		bsOut.Write(client[i]->getNetworkID());
		bsOut.Write(client[i]->getPosition());
		stringCompressor.EncodeString(client[i]->getClientName().c_str(),256,&bsOut);
		bsOut.Write(client[i]->getSystemAddresss());
	}
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,false);

	cout<<"netSendOtherOnLineClientInfo()-finished"<<endl;
}

// ��û��ʹ�á�û���ô�������
void netSever::netSendCharacterMoveMessage()
{
	cout<<"netSendCharacterMoveMessage()-started"<<endl;

	this->useTimeStamp=ID_TIMESTAMP;
	this->timeStamp=RakNet::GetTime();
	this->typeId=ID_GAME_MESSAGE_CLIENT_MOVE;

	RakNet::BitStream streamOut;
	streamOut.Write(useTimeStamp);
	streamOut.Write(timeStamp);
	streamOut.Write(typeId);
	peerSever->Send(&streamOut,HIGH_PRIORITY,RELIABLE,0,packet->systemAddress,true);

	cout<<"netSendCharacterMoveMessage()-finished"<<endl;
}

// ���յ��û��ƶ���Ϣ��������㲥
void netSever::netReceiveCharacterMoveMessage()
{
	cout<<"netReceiveCharacterMoveMessage()-started"<<endl;

	vector3df position;
	NetworkID netId;
	
	RakNet::BitStream bsIn(packet->data,packet->length,false);
	bsIn.Read(useTimeStamp);
	bsIn.Read(timeStamp);
	bsIn.Read(typeId);
	bsIn.Read(netId);
	StringCompressor stringCompressor;
	char clientNameTemp[256];
	stringCompressor.DecodeString(clientNameTemp,256,&bsIn);
	bsIn.Read(position);
	
	for (int i=0;i!=client.size();i++)
	{
		if (netId == client[i]->getNetworkID())
		{
			client[i]->setPosition(position);
		}
	}
	printf("%s\n", packet->systemAddress.ToString(true));
	cout<<"λ�ã�"<<position.X<< " "<<position.Y<<" "<<position.Z<<endl;


	// ���յ�ĳ�û��ƶ��󣬽��ƶ���Ϣ�㲥
	RakNet::BitStream bsOut;
	this->useTimeStamp=ID_TIMESTAMP;
	this->timeStamp=RakNet::GetTime();
	this->typeId=ID_GAME_MESSAGE_CLIENT_MOVE;
	bsOut.Write(useTimeStamp);
	bsOut.Write(timeStamp);
	bsOut.Write(typeId);
	bsOut.Write(netId);
	stringCompressor.EncodeString(clientNameTemp,256,&bsOut);
	bsOut.Write(position);
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
	cout<<"netReceiveCharacterMoveMessage()-finished"<<endl;
}

void netSever::netRecvClientTextChatMessage()
{
	cout<<"netRecvClientTextChatMessage()-started"<<endl;
	
	// �Ự���𷽵���Ϣ�ȴ��ݸ������������������յ��Ự���շ���address��id
	SystemAddress address;
//	NetworkID netId;
	RakString message;
	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
// 	bsIn.Read(address);
// 	bsIn.Read(netId);
	char clientNameStart[256];
	char clientNameRecv[256];
	StringCompressor stringCompressor;
	stringCompressor.DecodeString(clientNameStart,256,&bsIn);
	stringCompressor.DecodeString(clientNameRecv,256,&bsIn);
	bsIn.Read(message);

	cout<<"netRecvClientTextChatMessage()-finished"<<endl;

	//  ���������Ự��Ϣת�����Ự���𷽵�address�ͻỰ���շ���id
	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_RECV_CHAT_MESSAGE;
	bsOut.Write(typeId);
// 	bsOut.Write(packet->systemAddress);
// 	bsOut.Write(netId);
	stringCompressor.EncodeString(clientNameStart,256,&bsOut);
	stringCompressor.EncodeString(clientNameRecv,256,&bsOut);
	bsOut.Write(message);
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
}
void netSever::netSendClientTextChatMessage()
{

}

// ���շ�����Ƶ������û�����Ϣ����ת����������Ƶ������û�
void netSever::netRecvClientVideoChatMessage()
{
	cout<<"netRecvClientVideoChatMessage()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	int roomNo=0;
	bsIn.Read(roomNo);
	StringCompressor stringCompressor;
	char sendVideoChatClient[256];
	char recvVideoChatClient[256];
	stringCompressor.DecodeString(sendVideoChatClient,256,&bsIn);
	stringCompressor.DecodeString(recvVideoChatClient,256,&bsIn);

	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_RECV_VIDEO_CHAT_FROM_OTHER_CLIENT;
	bsOut.Write(typeId);
	bsOut.Write(roomNo);
	stringCompressor.EncodeString(sendVideoChatClient,256,&bsOut);
	stringCompressor.EncodeString(recvVideoChatClient,256,&bsOut);
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netRecvClientVideoChatMessage()-finished"<<endl;
}
void netSever::netRecvClientVoiceChatMessage()
{
	cout<<"netRecvClientVideoChatMessage()-started"<<endl;

	BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	int roomNo=0;
	bsIn.Read(roomNo);
	StringCompressor stringCompressor;
	char sendVideoChatClient[256];
	char recvVideoChatClient[256];
	stringCompressor.DecodeString(sendVideoChatClient,256,&bsIn);
	stringCompressor.DecodeString(recvVideoChatClient,256,&bsIn);

	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_RECV_VOICE_CHAT_FROM_OTHER_CLIENT;
	bsOut.Write(typeId);
	bsOut.Write(roomNo);
	stringCompressor.EncodeString(sendVideoChatClient,256,&bsOut);
	stringCompressor.EncodeString(recvVideoChatClient,256,&bsOut);
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);

	cout<<"netRecvClientVideoChatMessage()-finished"<<endl;
}


// ���������յ��ͻ��˷����ļ��������ҵ�����ķ��𷽺ͽ��շ�
void netSever::netRecvSendFileRequestMessage()
{
	cout<<"netRecvSendFileRequestMessage()-started"<<endl;

	RakNet::BitStream bsIn(packet->data,packet->length,false);
	StringCompressor stringCompressor;
	bsIn.IgnoreBytes(sizeof(MessageID));
	char sender[256];
	char receiver[256];
	char fileName[256];
	stringCompressor.DecodeString(sender,256,&bsIn);
	stringCompressor.DecodeString(receiver,256,&bsIn);
	stringCompressor.DecodeString(fileName,256,&bsIn);

	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_SEND_SEND_FILE_REQUEST;
	bsOut.Write(typeId);
	stringCompressor.EncodeString(sender,256,&bsOut);
	stringCompressor.EncodeString(receiver,256,&bsOut);
	stringCompressor.EncodeString(fileName,256,&bsOut);

	RakNet::SystemAddress saTemp;
	for (int i=0;i!=client.size();i++)
	{
		if (client[i]->getClientName().compare(receiver) == 0)
		{
			saTemp=client[i]->getSystemAddresss();
			break;
		}
	}
//	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,UNASSIGNED_SYSTEM_ADDRESS,true);
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,saTemp,false);

	cout<<"netRecvSendFileRequestMessage()-finished"<<endl;
}

// �ļ����շ���������ļ�������������Ϣ֪ͨ�ļ����ͷ�
void netSever::netRecvIsAcceptSendFileRequest()
{
	cout<<"netRecvAcceptSendFileRequest()-started"<<endl;

	RakNet::BitStream bsIn(packet->data,packet->length,false);
	StringCompressor stringCompressor;
	bsIn.IgnoreBytes(sizeof(MessageID));
	bool isAccept=false;
	bsIn.Read(isAccept);
	SystemAddress saFileSender;
	SystemAddress saFileReceiver;
	bsIn.Read(saFileSender);
	bsIn.Read(saFileReceiver);
	for (int i=0;i!=this->client.size();i++)
	{
		if (saFileSender == this->client[i]->getSystemAddresss())
		{
			BitStream bsOut;
			this->typeId=ID_GAME_MESSAGE_SEND_IS_ACCEPT_SEND_FILE_REQUEST;
			bsOut.Write(typeId);
			bsOut.Write(isAccept);
			bsOut.Write(saFileSender);
			bsOut.Write(saFileReceiver);
			peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,saFileSender,false);
			break;
		}
	}

	cout<<"netRecvAcceptSendFileRequest()-finished"<<endl;
}
// �ļ����շ��ܾ������ļ�������������Ϣ֪ͨ�ļ����ͷ�
void netSever::netRecvRefuseSendFileRequest()
{

}

// ��ȡĳ������ȫ���û����ۣ������ظ��û�
void netSever::netRecvGetBuildingComment()
{
	cout<<"netRecvGetBuildingComment()-started"<<endl;

	RakNet::BitStream bsIn(packet->data,packet->length,false);
	StringCompressor stringCompressor;
	int buildingID;
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(buildingID);

	char build[256];
	itoa(buildingID,build,10);
	std::string strBuildingID;
	strBuildingID.assign(build);
	Operation operation;
	vector<Comment> commenList;
	operation.view_comment(strBuildingID,commenList);
	
	BitStream bsOut;
	this->typeId=ID_GAME_MESSAGE_GET_BUILDING_COMMENT_SERVER;
	bsOut.Write(typeId);
	bsOut.Write(commenList.size());
	//////////////////////////////////////////////////////////////////////////
	//���Ȼ�ȡ�û����۵��ܳ���
	for (int i=0;i!=commenList.size();i++)
	{
		stringCompressor.EncodeString(commenList[i].getUsername().c_str(),256,&bsOut);
		stringCompressor.EncodeString(commenList[i].getContent().c_str(),256,&bsOut);
		stringCompressor.EncodeString(commenList[i].getEditDate().c_str(),256,&bsOut);
	}
	//////////////////////////////////////////////////////////////////////////
	peerSever->Send(&bsOut,HIGH_PRIORITY,RELIABLE_ORDERED,0,packet->systemAddress,false);

	cout<<"netRecvGetBuildingComment()-finished"<<endl;
}

// ��ȡ�û��Խ��������ۣ������浽���ݿ�
void netSever::netRecvClientBuildingComment()
{
	cout<<"netRecvClientBuildingComment()-started"<<endl;

	RakNet::BitStream bsIn(packet->data,packet->length,false);
	StringCompressor stringCompressor;
	char charTemp[256];
	int buildingID;
	std::string clientName;
	std::string commentTime;
	std::string commentContent;
	bsIn.IgnoreBytes(sizeof(MessageID));
	bsIn.Read(buildingID);
	stringCompressor.DecodeString(charTemp,256,&bsIn);
	clientName.assign(charTemp);	
	stringCompressor.DecodeString(charTemp,256,&bsIn);
	commentContent.assign(charTemp);
	stringCompressor.DecodeString(charTemp,256,&bsIn);
	commentTime.assign(charTemp);
	
	std::string strTemp;
	Comment clientComment;
	itoa(buildingID,charTemp,10);
	std::string strBuildingID;
	strBuildingID.assign(charTemp);
	clientComment.setBuildingID(strBuildingID);
	clientComment.setUserName(clientName);
	clientComment.setContent(commentContent);
	clientComment.setEditDate(commentTime);

	Operation operation;
	operation.add_comment(clientComment);

	cout<<"netRecvClientBuildingComment()-finished"<<endl;
}

// ���������յ��ͻ��˵Ĺر�ָ�����networkID�������û�vector��ɾ�����û�
void netSever::netRecvClientShutdown()
{
	cout<<"netRecvClientShutdown()-started"<<endl;

	RakNet::BitStream bsIn(packet->data,packet->length,false);
	bsIn.IgnoreBytes(sizeof(MessageID));
	NetworkID netId;
//	char userNameClient[256];
	bsIn.Read(netId);
	
	f32 xTemp=0;
	f32 yTemp=0;
	f32 zTemp=0;
	bsIn.Read(xTemp);
	bsIn.Read(yTemp);
	bsIn.Read(zTemp);
	std::string positionStr;
	char xChar[20];
	char yChar[20];
	char zChar[20];
	itoa((int)xTemp,xChar,10);
	itoa((int)yTemp,yChar,10);
	itoa((int)zTemp,zChar,10);
	positionStr.assign(xChar);
	positionStr.append(",");
	positionStr.append(yChar);
	positionStr.append(",");
	positionStr.append(zChar);


	StringCompressor stringCompressor;
	char clientNameTemp[256];
	stringCompressor.DecodeString(clientNameTemp,256,&bsIn);
	std::string clientnameStr;
	clientnameStr.assign(clientNameTemp);
	Location location;
	location.setUserName(clientnameStr);
	location.setLocation(positionStr);
	Operation operation;
	operation.log_off(location);


	vector<netClient*>::iterator itr;
	for (itr=client.begin();itr!=client.end();itr++)
	{
		if (netId == (*itr)->GetNetworkID())
		{
			client.erase(itr);
			break;
		}
	}

	cout<<"netRecvClientShutdown()-finished"<<endl;
}
void netSever::netReceiveMessage()
{
	packet=peerSever->Receive();
	if (packet == NULL)
	{
		return;
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
			
		}
		break;
	case ID_NEW_INCOMING_CONNECTION:
		printf("A connection is incoming.\n");
//		netReceiveCreateClient();
		break;
	case ID_NO_FREE_INCOMING_CONNECTIONS:
		printf("The server is full.\n");
		break;
	case ID_DISCONNECTION_NOTIFICATION:
		printf("A client has disconnected.\n");
		break;
	case ID_CONNECTION_LOST:
		printf("A client lost the connection.\n");
		netRecvClientShutdown();
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
	case ID_GAME_MESSAGE_SEND_LAND_TO_SEVER:
		netRecvLandFromClient();
		netSendLandResultToClient();
		break;
	case ID_GAME_MESSAGE_SEND_REGISTER_TO_SEVER:
		netRecvRegisterFromClient();
		netSendRegisterResultToClient();
		break;
	case ID_GAME_MESSAGE_CREATE_CLIENT_FROM_CLIENT:
		netReceiveCreateClient();
		netSendCreateClient();
		netSendOtherOnLineClientInfo();
		break;
	case ID_GAME_MESSAGE_CLIENT_MOVE:
		netReceiveCharacterMoveMessage();
		break;
	case ID_GAME_MESSAGE_CLIENT_SHUTDOWN:
		netRecvClientShutdown();
		break;
	case ID_GAME_MESSAGE_SEND_CHAT_MESSAGE:
		netRecvClientTextChatMessage();
		break;
	case ID_GAME_MESSAGE_RECV_MYINFO_MESSAGE_TO_SEVER:
		netRecvMyInfoMessageToClient();
		break;
	case ID_GAME_MESSAGE_RECV_FRIENDLIST_TO_SEVER:
		netRecvFriendListToClient();
		break;
	case ID_GAME_MESSAGE_RECV_FRIEND_PERSONAL_INFO_TO_SEVER:
		netRecvFriendPersonalInfoToClient();
		break;
	case ID_GAME_MESSAGE_SEND_CHAT_MESSAGE_TO_FRIEND:
		netRecvClientFriendTextChatMessage();
		break;
	case ID_GAME_MESSAGE_RECV_OTHER_CLIENT_INFO_TO_SERVER:
		netRecvPickedClientInfoToClient();
		break;
	case ID_GAME_MESSAGE_ADD_AS_FRIEND_TO_SERVER:
		netRecvAddFriendFromClient();
		break;
	case ID_GAME_MESSAGE_MODIFY_PERSONAL_INFO_TO_SERVER:
		netRecvModifyPersonalInfoFromClient();
		break;
	case ID_GAME_MESSAGE_SEND_VIDEO_CHAT_TO_OTHER_CLIENT:
		netRecvClientVideoChatMessage();
		break;
	case ID_GAME_MESSAGE_SEND_VOICE_CHAT_TO_OTHER_CLIENT:
		netRecvClientVoiceChatMessage();
		break;
	case ID_GAME_MESSAGE_SEND_SEND_FILE_REQUEST:
		netRecvSendFileRequestMessage();
		break;
	case ID_GAME_MESSAGE_GET_BUILDING_COMMENT_CLIENT:
		netRecvGetBuildingComment();
		break;
	case ID_GAME_MESSAGE_SEND_IS_ACCEPT_SEND_FILE_REQUEST:
		netRecvIsAcceptSendFileRequest();
		break;
	case ID_GAME_MESSAGE_SEND_CLIENT_BUILDING_COMMENT:
		netRecvClientBuildingComment();
		break;
// 	case ID_GAME_MESSAGE_RECV_IS_ACCEPT_SEND_FILE_REQUEST:
// 		netRecvRefuseSendFileRequest();
// 		break;
	default:
		printf("Message with identifier %i has arrived.\n", packet->data[0]);
		break;
	}

	
	peerSever->DeallocatePacket(packet);
}

