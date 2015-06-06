#ifndef _NET_CLIENT_H_
#define _NET_CLIENT_H_

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <time.h>

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID
#include "GetTime.h"
#include "BitStream.h"
#include "SocketLayer.h"
#include "NetworkIDObject.h"
#include "NetworkIDManager.h"
#include "StringCompressor.h"
#include "FileListTransfer.h"
#include "RakSleep.h"
#include "FileListTransferCBInterface.h"
#include "FileOperations.h"
#include "SuperFastHash.h"
#include "RakAssert.h"
#include "IncrementalReadInterface.h"
#include "PacketizedTCP.h"
#include "SocketLayer.h"
#include "Gets.h"

#include "utility.h"
#include "otherClient.h"
#include "GUI.h"

#include "fileTransper.h"

using namespace std;
using namespace RakNet;

#pragma comment(lib,"RakNetLibStaticDebug.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib, "Shell32.lib") 


#define MAX_CLIENTS 10
#define CLIENT_PORT 60001
#define SERVER_PORT 60000




struct registerMessage 
{
	stringc userName;
	stringc password;
	stringc nickName;
	stringc signature;
	stringc sex;
	stringc age;
	stringc adddress;
};


enum GameMessages
{
	ID_GAME_MESSAGE_1=ID_USER_PACKET_ENUM+1,

	ID_GAME_MESSAGE_CREATE_CLIENT_FROM_CLIENT=ID_USER_PACKET_ENUM+2,
	ID_GAME_MESSAGE_CREATE_CLIENT_FROM_SEVER=ID_USER_PACKET_ENUM+3,
	ID_GAME_MESSAGE_GET_ANOTHER_CLIENT_ID=ID_USER_PACKET_ENUM+4,
	ID_GAME_MESSAGE_CLIENT_MOVE=ID_USER_PACKET_ENUM+5,
	ID_GAME_MESSAGE_ANOTHER_CLIENT_MOVE=ID_USER_PACKET_ENUM+6,

	ID_GAME_MESSAGE_TEXT_CHAT=ID_USER_PACKET_ENUM+7,
	ID_GAME_MESSAGE_VOICE_CHAT=ID_USER_PACKET_ENUM+8,
	ID_GAME_MESSAGE_VIDEO_CHAT=ID_USER_PACKET_ENUM+9,

	ID_GAME_MESSAGE_PICK_CLIENT=ID_USER_PACKET_ENUM+10,
	ID_GAME_MESSAGE_LOOK_CLIENT_INFO=ID_USER_PACKET_ENUM+11,
	ID_GAME_MESSAGE_ADD_CLIENT_AS_FRIEND=ID_USER_PACKET_ENUM+12,

	ID_GAME_MESSAGE_NETWORKID=ID_USER_PACKET_ENUM+13,

	ID_GAME_MESSAGE_OTHER_CLIENT_INFO=ID_USER_PACKET_ENUM+14,


	ID_GAME_MESSAGE_CLIENT_SHUTDOWN=ID_USER_PACKET_ENUM+15,

	ID_GAME_MESSAGE_SEND_CHAT_MESSAGE=ID_USER_PACKET_ENUM+16,
	ID_GAME_MESSAGE_RECV_CHAT_MESSAGE=ID_USER_PACKET_ENUM+17,

	ID_GAME_MESSAGE_SEND_LAND_TO_SEVER=ID_USER_PACKET_ENUM+18,
	ID_GAME_MESSAGE_SEND_REGISTER_TO_SEVER=ID_USER_PACKET_ENUM+19,
	ID_GAME_MESSAGE_RECV_LAND_FROM_SEVER=ID_USER_PACKET_ENUM+20,
	ID_GAME_MESSAGE_RECV_REGISTER_FROM_SEVER=ID_USER_PACKET_ENUM+21,

	ID_GAME_MESSAGE_RECV_MYINFO_MESSAGE_TO_SEVER=ID_USER_PACKET_ENUM+22,
	ID_GAME_MESSAGE_RECV_MYINFO_MESSAGE_FROM_SEVER=ID_USER_PACKET_ENUM+23,

	ID_GAME_MESSAGE_RECV_FRIENDLIST_TO_SEVER=ID_USER_PACKET_ENUM+24,
	ID_GAME_MESSAGE_RECV_FRIENDLIST_FROM_SEVER=ID_USER_PACKET_ENUM+25,

	ID_GAME_MESSAGE_RECV_FRIEND_PERSONAL_INFO_TO_SEVER=ID_USER_PACKET_ENUM+26,
	ID_GAME_MESSAGE_RECV_FRIEND_PERSONAL_INFO_FROM_SEVER=ID_USER_PACKET_ENUM+27,

	ID_GAME_MESSAGE_SEND_CHAT_MESSAGE_TO_FRIEND=ID_USER_PACKET_ENUM+28,
	ID_GAME_MESSAGE_RECV_CHAT_MESSAGE_FROM_FRIEND=ID_USER_PACKET_ENUM+29,

	ID_GAME_MESSAGE_ADD_AS_FRIEND_TO_SERVER=ID_USER_PACKET_ENUM+30,
	ID_GAME_MESSAGE_ADD_AS_FRIEND_FROM_SERVER=ID_USER_PACKET_ENUM+31,

	ID_GAME_MESSAGE_RECV_OTHER_CLIENT_INFO_TO_SERVER=ID_USER_PACKET_ENUM+32,
	ID_GAME_MESSAGE_RECV_OTHER_CLIENT_INFO_FROM_SERVER=ID_USER_PACKET_ENUM+33,

	ID_GAME_MESSAGE_SEND_VIDEO_CHAT_TO_OTHER_CLIENT=ID_USER_PACKET_ENUM+34,
	ID_GAME_MESSAGE_RECV_VIDEO_CHAT_FROM_OTHER_CLIENT=ID_USER_PACKET_ENUM+35,

	ID_GAME_MESSAGE_SEND_VOICE_CHAT_TO_OTHER_CLIENT=ID_USER_PACKET_ENUM+36,
	ID_GAME_MESSAGE_RECV_VOICE_CHAT_FROM_OTHER_CLIENT=ID_USER_PACKET_ENUM+37,

	ID_GAME_MESSAGE_MODIFY_PERSONAL_INFO_TO_SERVER=ID_USER_PACKET_ENUM+38,
	ID_GAME_MESSAGE_MODIFY_PERSONAL_INFO_FROM_SERVER=ID_USER_PACKET_ENUM+39,

	ID_GAME_MESSAGE_SEND_SEND_FILE_REQUEST=ID_USER_PACKET_ENUM+40,
	ID_GAME_MESSAGE_RECV_SEND_FILE_REQUEST=ID_USER_PACKET_ENUM+41,

	ID_GAME_MESSAGE_SEND_IS_ACCEPT_SEND_FILE_REQUEST=ID_USER_PACKET_ENUM+42,
	ID_GAME_MESSAGE_RECV_IS_ACCEPT_SEND_FILE_REQUEST=ID_USER_PACKET_ENUM+43,

	ID_GAME_MESSAGE_SEND_FILE=ID_USER_PACKET_ENUM+44,
	ID_GAME_MESSAGE_RECV_FIL=ID_USER_PACKET_ENUM+45,

	ID_GAME_MESSAGE_GET_BUILDING_COMMENT_CLIENT=ID_USER_PACKET_ENUM+46,
	ID_GAME_MESSAGE_GET_BUILDING_COMMENT_SERVER=ID_USER_PACKET_ENUM+47,

	ID_GAME_MESSAGE_SEND_CLIENT_BUILDING_COMMENT=ID_USER_PACKET_ENUM+48

};


class netClient:public NetworkIDObject
{
public:
	netClient();
	netClient(const netClient&);
	~netClient();


	void setDevice(IrrlichtDevice* newDevice);
	void setGui(CGui newGui);
	void netInitialize();
	
	void SetSystemAddress(SystemAddress newSa);
	SystemAddress GetSystemAddress();
	void SetPort(unsigned int newPort);
	unsigned int GetPort();

	void setUserName(stringc newuserName);
	stringc getUserName();
	void setPassword(stringc newPassword);
	stringc getPassword();
	void setNickName(stringc nickName);
	stringc getNickName();
	void setSignature(stringc signature);
	stringc getSignature();
	void setSex(stringc sex);
	stringc getSex();
	void setAge(stringc age);
	stringc getAge();
	void setAdddress(stringc adddress);
	stringc getAdddress();

	void setSceneCamera(ICameraSceneNode* newCamera);
	ICameraSceneNode* getSceneCamera();

	void setClientPosition(vector3df newPosition);
	vector3df getClientPosition();

	void setFriendList(vector<std::string> newFirendList);
	vector<std::string> getFriendList();

	unsigned char GetPacketIdentifier(Packet* p);


	int netRecvLandFromSever();
	void netRecvRegisterFromSever();
	void netSendLandToSever(stringc newName,stringc newPassword);
	void netSendRegisterMessageToSever(stringc newName,stringc newPassword,stringc nickName,
	stringc signature,stringc sex,stringc age,stringc adddress);
	void displayLandResult();
	void displayRegisterResult();
	// 获取在本机上进行的各种操作
	void netGetMoveMessage();
	void netGetMouseMessage();
	
	// 点击某一建筑，获取用户评论信息
	void netSendGetBuildingComment(int newBuildingID);
	void netRecvGetBuildingComment();
	// 发送用户对建筑的评论信息
	void netSendClientBuildingComment(int newBuildingID);

	// 按下Tab键，打开用户个人信息窗口
	void netRecvMyInfoMessageToServer();
	void netRecvMyInfoMessageFromServer();

	// 在好友信息窗口中，点击INFO按钮
	void netRecvFriendPersonalInfoToServer(std::string friendName);
	void netRecvFriendPersonalInfoFromServer();

	// 在用户个人信息窗口中点击SUBMIT，修改个人信息
	void ModifyMyPersonalInfo();
	void netSendModifyMyPersonalInfoToServer();
	void netRecvModifyPersonalInfoFromServer();

	// 在用户个人信息窗口中点击FIRENDLIAT，打开好友列表
	void setPickedFriend(int friendNo);
	int getPickedfriend();
	void netRecvFriendListToServer();
	void netRecvFriendListFromServer();

	// 和好友进行文本聊天，通过pickedFriend确定好友
	void netSendChatMessageToFriend();
	void netRecvCharMessageFromFriend();


	// 点击好友按钮，增加某个陌生人为好友
	void netSendAddAsFriendToServer();
	void netRecvAddAsFriendFromServer();

	// 和他人进行视频聊天
	void netSendVideoChatToOtherClient();
	void netRecvVideoChatFromOtherClient();

	// 和他人进行语音聊天
	void netSendVoiceChatToOtherClient();
	void netRecvVoiceChatFromOtherClient();

	// 发送文件之前先发送请求
	void netSendSendFileRequset(const c8* fn);
	void netRecvSendFileRequset();

	void netSendIsAcceptSendFileRequest(bool isAcccept);
	void netRecvIsAcceptSendFileRequest();

	// 发送文件
	void netSendFile();
	void netRecvFile();

	int netReceiveMessage();

	void netSendMoveMessage(vector3df position);
	void netRecvMoveMessage();
	
	void netSendCreateClient();
	void netRecvCreateClient(IrrlichtDevice* myDevice);

	void netSetNetworkID(NetworkID newID);
	NetworkID netGetNetworkID();

	void netRecvOtherClientInfo(IrrlichtDevice* myDevice);

	void getOtherClientPosition(vector<vector3df> &position);
	
	// 用鼠标选取某个用户，获取被拾取的用户的信息
	void setPickedClient(cOtherClient& newClient);
	cOtherClient getPickedClient();
	cOtherClient* getPickedClientPtr();
	void netRecvPickedClientInfoToServer();
	void netRecvPickedClientInfoFromServer();

	void netSendChatMessage();
	void netRecvChatMessage();

	void netSendClientShutdown();
	void netRecvClientShutdown();
	void closeClient();


	vector<cOtherClient*> getOtherClient();
protected:
private:
	RakNet::RakPeerInterface* peerClient;
	RakNet::Packet* packet;


	MessageID useTimeStamp;
	RakNet::Time timeStamp;
	MessageID typeId;
	NetworkID networkId;
	SystemAddress systemAddress;
	unsigned short port;

	vector3df clientPosition;

	char* clientName;

	// 文件传输相关
	TestCB transferCallback;
	RakNet::FileListTransfer flt;
	RakNet::PacketizedTCP tcp;

	IrrlichtDevice* device;
	CGui myGui;
	ICameraSceneNode* camera;
	vector<cOtherClient*> otherClient;
	cOtherClient pickedClient;
	cOtherClient textChatClient;
//	vector<vector3df> otherClientPosition;

	vector<std::string> friendList;
	int pickedFriend;

	// 文本聊天所显示的信息
	core::stringw textChatString;

	// 登陆界面
	// 0--空		1--成功		2--失败
	int landResult;
	// 登陆界面
	// 0--空		1--成功		2--失败
	int registerResult;

	stringc userName;
	stringc password;
	stringc nickName;
	stringc signature;
	stringc sex;
	stringc age;
	stringc adddress;
};


#endif