#pragma once

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID
#include "GetTime.h"
#include "BitStream.h"
#include "SocketLayer.h"
#include "NetworkIDObject.h"
#include "NetworkIDManager.h"

#include "utility.h"

using namespace std;
using namespace RakNet;


class cOtherClient
{
public:
	cOtherClient();	
	cOtherClient(const cOtherClient& newClient);	
	~cOtherClient();
	
	void setOtherClientUserName(stringc newuserName);
	stringc getOtherClientUserName();
	void setOtherClientPassword(stringc newPassword);
	stringc getOtherClientPassword();
	void setOtherClientNickName(stringc nickName);
	stringc getOtherClientNickName();
	void setOtherClientSignature(stringc signature);
	stringc getOtherClientSignature();
	void setOtherClientSex(stringc sex);
	stringc getOtherClientSex();
	void setOtherClientAge(stringc age);
	stringc getOtherClientAge();
	void setOtherClientAdddress(stringc adddress);
	stringc getOtherClientAdddress();

	void setNetworkID(NetworkID newID);	
	NetworkID getNetworkID();
	
	void setPosition(vector3df newPosition);	
	vector3df getPosition();
	
	void setSystemAddress(SystemAddress newAddress);	
	SystemAddress getSystemAddress();


	void createPersonNode(IrrlichtDevice* myDevice, vector3df newPosition);
	IAnimatedMeshSceneNode* getPersonalNode();
	void clientMove(vector3df newPosition);

	cOtherClient& operator=(const cOtherClient &newClient)
	{
		this->networkID=newClient.networkID;
		this->position=newClient.position;
		this->sysAddress=newClient.sysAddress;
		return *this;
	}
protected:
private:

	NetworkID networkID;
	vector3df position;
	SystemAddress sysAddress;


	stringc userName;
	stringc password;
	stringc nickName;
	stringc signature;
	stringc sex;
	stringc age;
	stringc userAdddress;

	IAnimatedMeshSceneNode* personNode;
};