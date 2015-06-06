#pragma once

#include "netClient.h"
#include <irrlicht.h>
#include "driverChoice.h"

#include "GUI.h"
#include "scene.h"


using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace gui;
using namespace video;


class CMainMenu : public IEventReceiver
{
public:

	CMainMenu();

	bool run(core::stringw &playerName);

	virtual bool OnEvent(const SEvent& event);

	netClient* getClient();
	IrrlichtDevice* getDevice();

// 	void netSqlSendRegisterMessage();
// 	void netSqlRecvRegisterMessage();
// 	
// 	void netSqlSendLandMessage();
// 	void netSqlrecvLandMessage();

private:

	void connnectToSever(IrrlichtDevice* myDevice);

	stringc getName();
	stringc getPassword();
	void checkRegisterMessage(stringc &str);
	stringc getRegisterUserName();
	stringc getRegisterPassword();
	stringc getRegisterNickName();
	stringc getRegisterSignature();
	stringc getRegisterSex();
	stringc getRegisterAge();
	stringc getRegisterAddress();
	void createRegisterWindow();
	bool checkRegisterinfo(stringc newName,stringc newPassword,
		stringc nickName, stringc signature,stringc sex,stringc age,stringc adddress);
	void createRegisterFailedWindow(std::string failedInfo);
// 	void netSendLandToSever();
// 	void netSendRegisterToSever();
// 
// 	void netRecvFromSever();
// 	void netRecvLandFromSever();
// 	void netRecvRegisterFromSever();
// 
// 	void displayLandResult();
// 	void displayRegisterResult();

	void setTransparency();

	gui::IGUIButton* startButton;
	IrrlichtDevice *MenuDevice;
	s32 selected;
	int start;
	int landResult;
	int registerResult;
	

	scene::IAnimatedMesh* quakeLevel;
	scene::ISceneNode* lightMapNode;
	scene::ISceneNode* dynamicNode;

	video::SColor SkinColor [ gui::EGDC_COUNT ];
	void getOriginalSkinColor();

	// RakNet: Store the edit box pointer so we can get the text later
	irr::gui::IGUIEditBox* nameEditBox;

	// 显示登陆和注册的结果
	wchar_t* landAndRegisterResult;

	netClient client;
};
