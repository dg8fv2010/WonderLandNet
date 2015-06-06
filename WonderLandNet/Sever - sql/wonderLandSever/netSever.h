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

	// ��ȡĳ������ȫ���û����ۣ������ظ��û�
	void netRecvGetBuildingComment();
	// ��ȡ�û��Խ��������ۣ������浽���ݿ�
	void netRecvClientBuildingComment();

	// ��ȡ�ڱ����Ͻ��еĸ��ֲ���
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
	
	// ÿ����һ���û���¼ʱ��������Ϊ�����һ��networkID���������û�����Ϣ�㲥�������ѵ�¼���û�
	// ͬʱ�����ѵ�¼�û�����Ϣ���͸����û�
	void netSendCreateClient();

	// ÿ����һ���û���¼ʱ�����ѵ�¼�û�����Ϣ���͸����û�
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

	// �������������ѵ�¼�Ŀͻ�
	vector<netClient*> client;

	// ĳ�ͻ���¼ʱ��Ҫ����λ�÷��͸�������
	vector3df clientPosition;

	// �û�ע����
	// 0-�û����ظ�
	// 1-ע��ɹ�
	// 2-ע��ʧ�ܣ����������
	int registerResult;

	// �û���¼���
	// 0-�û����ظ�
	// 1-ע��ɹ�
	// 2-ע��ʧ�ܣ����������
	int landResult;
};
