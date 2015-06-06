#pragma once

#include <tchar.h>
#include <iostream>
#include <string>
#include <vector>
#include <irrlicht.h>
#include "driverChoice.h"


#include "utility.h"
#include "Building.h"
//#include "CGUITTFont.h"

using namespace std;


using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace gui;
using namespace video;

#pragma comment(lib,"freetype219ST.lib")

class CGui
{
public:
	CGui();
	CGui(IrrlichtDevice* myDevice);
	CGui(const CGui& newGui);
	void SetIrrlichtDevice(IrrlichtDevice* myDevice);
	void checkInfoIsNull(stringc& newStr,stringw& temp);

	void CreateBuildingInfoBox(char* buildingName, char* pictureName, char* buildingInfo);
	void CreateBuildingInfoBox(CBuilding newBuilding);
	CBuilding GetBuilding();
	void SetBuilding(CBuilding& newBuilding);
	void UpdateBuildingComment(int newCommentPos);

	void CreateOtherClientInfoBox(std::string clientName);
	void CreateOtherClientPersonalInfoBox(stringc newUsername,stringc newNickName,
		stringc newSignature,stringc newSex,stringc newAge,stringc newAddress);

	void CreateFriendInfoBox(std::string newName);
	void CreateFriendPersonalInfoBox(stringc newUsername,stringc newNickName,
		stringc newSignature,stringc newSex,stringc newAge,stringc newAddress);
	void CreateFriendTextChatBox();

	void CreateTextChatBox();

	void CreateFriendListBox(vector<std::string> friendList);

	void CreateMyInfoBox(stringc newUsername,stringc newPassword,stringc newNickName,
		stringc newSignature,stringc newSex,stringc newAge,stringc newAddress);

	void CreateIsStartVideoChatBox();
	void CloseIsStartVideoChatBox();

	void CreateAddFriendResultBox(bool addFriendResult);

	void CreateIsRecvFileBox(char* senderName,char* receiverName,char* fileName);

	void CreateModityResultBox(bool modifyResut);

private:
	IrrlichtDevice* device;

	CBuilding building;
};

