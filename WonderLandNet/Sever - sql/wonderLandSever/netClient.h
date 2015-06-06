#ifndef _NET_CLIENT_H_
#define _NET_CLIENT_H_

#include <stdio.h>
#include <string.h>
#include <iostream>

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

#include "utility.h"


using namespace std;
using namespace RakNet;

#pragma comment(lib,"RakNetLibStaticDebug.lib")
#pragma comment(lib,"ws2_32.lib")

#define MAX_CLIENTS 10
#define CLIENT_PORT 60001
#define SERVER_PORT 60000

#define  CLIENT_INITIALIZE_POSITION (-84.0f,50.0f,-238.0f)

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

/***********************************************************/
// 服务器端的客户端类
// 需要每个客户的systemaddress(IP,端口号),网络ID
// 客户端的实时位置
/***********************************************************/
class netClient:public NetworkIDObject
{
public:
	netClient();
	netClient(const netClient&);
	~netClient();


	void setSystemAddress(RakNet::SystemAddress newAddress);
	SystemAddress getSystemAddresss();
	
	void setPosition(vector3df newPosition);
	vector3df getPosition();

	void setNetworkID(NetworkID newID);
	NetworkID getNetworkID();

	void setClientName(std::string newName);
	std::string getClientName();
protected:
private:
// 	RakNet::RakPeerInterface* peerClient;
// 	RakNet::Packet* packet;


// 	MessageID useTimeStamp;
// 	RakNet::Time timeStamp;
// 	MessageID typeId;
	NetworkID networkId;
	SystemAddress systemAddress;

	vector3df characterPosition;

	std::string clientName;

//	NetworkIDManager networkIDManager;
};


#endif