#pragma once

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <irrlicht.h>
#include "netClient.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID
#include "GetTime.h"
#include "BitStream.h"
#include "NetworkIDManager.h"
#include "NetworkIDObject.h"

#include "sqlServer.h"

using namespace std;

using namespace RakNet;

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace gui;
using namespace video;
//#pragma comment(lib,"RakNetLibStaticDebug.lib")

#define SERVER_PORT 60000


class netSever: public NetworkIDObject
{
public:
	netSever();
	netSever(const netSever&);
	~netSever();


	void netInitialize();

	unsigned char GetPacketIdentifier(Packet* p);


	void netRecvLandFromClient();
	void netRecvRegisterFromClient();
	void netSendLandResultToClient();
	void netSendRegisterResultToClient();

	void netRecvModifyPersonalInfoFromClient();
	void netRecvAddFriendFromClient();
	void netRecvPickedClientInfoToClient();
	void netRecvMyInfoMessageToClient();
	void netRecvFriendListToClient();
	void netRecvFriendPersonalInfoToClient();
	void netRecvClientFriendTextChatMessage();

	// 获取某建筑的全部用户评论，并返回给用户
	void netRecvGetBuildingComment();
	// 获取用户对建筑的评论，并保存到数据库
	void netRecvClientBuildingComment();

	// 获取在本机上进行的各种操作
	void netGetMoveMessage();
	void netGetMouseMessage();


	void netReceiveMessage();

	void netReceiveCharacterMoveMessage();
	void netSendCharacterMoveMessage();

	void netRecvClientTextChatMessage();
	void netSendClientTextChatMessage();

	void netRecvClientVideoChatMessage();
	void netRecvClientVoiceChatMessage();

	void netRecvSendFileRequestMessage();
	void netRecvIsAcceptSendFileRequest();
	void netRecvRefuseSendFileRequest();

	void netRecvClientShutdown();
protected:
private:
	void netReceiveCreateClient();
	
	// 每当有一个用户登录时，服务器为其分配一个networkID，并将新用户的信息广播给所有已登录的用户
	// 同时，将已登录用户的信息发送给新用户
	void netSendCreateClient();

	// 每当有一个用户登录时，将已登录用户的信息发送给新用户
	void netSendOtherOnLineClientInfo();
	

private:
	RakNet::RakPeerInterface* peerSever;
	RakNet::Packet* packet;


	unsigned char useTimeStamp;
	RakNet::Time timeStamp;
	unsigned char typeId;
	NetworkID networkId;
	SystemAddress systemAddress;


	NetworkIDManager networkIDManager;

	// 服务器保留的已登录的客户
	vector<netClient*> client;

	// 某客户登录时需要将其位置发送给服务器
	vector3df clientPosition;

	// 用户注册结果
	// 0-用户名重复
	// 1-注册成功
	// 2-注册失败（其他情况）
	int registerResult;

	// 用户登录结果
	// 0-用户名重复
	// 1-注册成功
	// 2-注册失败（其他情况）
	int landResult;
};
