#include "GUI.h"


CGui::CGui()
{

}
CGui::CGui(IrrlichtDevice* myDevice)
{
	device=myDevice;
}
CGui::CGui(const CGui& newGui)
{
	this->device=newGui.device;
	this->building=newGui.building;
}
void CGui::SetIrrlichtDevice(IrrlichtDevice* myDevice)
{
	device=myDevice;
}

void CGui::checkInfoIsNull(stringc& newStr,stringw& temp)
{
	if (newStr == "/?/")
	{
		temp="null";
	}
	else
	{
		temp=newStr;
	}
}

void CGui::CreateBuildingInfoBox(char* buildingName, char* pictureName, char* buildingInfo)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_BUILDING_INFORMATION_WINDOW,true);
	IVideoDriver* driver=device->getVideoDriver();
	if (e)
	{
		e->remove();
	}
	wchar_t* temp=NULL;


	charTowchar(buildingName,temp,strlen(buildingName));
	IGUIWindow* wnd=env->addWindow(rect<s32>(200,45,800,480),false,temp,0,GUI_ID_BUILDING_INFORMATION_WINDOW);

	IGUITabControl* tab=env->addTabControl(rect<s32>(2,20,800-202,480-7),wnd,true,true);
	IGUITab* picture=tab->addTab(L"Picture",GUI_ID_TAB_BUILDING_PICTURE);
	IGUITab* info=tab->addTab(L"Information",GUI_ID_TAB_BUILDING_INFORMATION);
	IGUITab* comment=tab->addTab(L"Comment",GUI_ID_TAB_BUILDING_COMMENT);

	// 照片
	env->addImage(driver->getTexture(pictureName),position2d<int>(10,10),false,picture);
	// 滚动条，暂时不需要----显示多张图片
// 	IGUIScrollBar* scrollbar=env->addScrollBar(true,rect<s32>(10,375,550,380),picture,GUI_ID_SCROLL_BAR_BUILDING_PICTURE);
// 	scrollbar->setMax(255);
// 	scrollbar->setPos(0);
// 	scrollbar->setSmallStep(1);

	// 简介
//	charTowchar(buildingInfo,temp,strlen(buildingInfo));
	stringw infoStr;
	infoStr=buildingInfo;
	env->addStaticText(infoStr.c_str(),rect<s32>(10,10,590,480-45-10),false,false,info);


	// 评论
	// 他人评价区
	env->addStaticText(NULL,rect<s32>(0,0,575,320),true,true,comment,GUI_ID_STATIC_TEXT_OTHER_COMMENT,true);
	IGUIScrollBar* buildingCommentScrollbar=env->addScrollBar(false,rect<s32>(575,0,595,320),comment,GUI_ID_SCROLL_BAR_BUILDING_COMMENT);
	buildingCommentScrollbar->setMax(255);	// 他人评论的数量
	buildingCommentScrollbar->setPos(0);
	buildingCommentScrollbar->setSmallStep(1);

	// 自己评价
	env->addEditBox(NULL,rect<s32>(0,340,560,378),true,comment,GUI_ID_EDIT_BOX_MY_COMMENT);
	env->addButton(rect<s32>(560,359,595,378),comment,GUI_ID_BUTTON_SEND_COMMENT,L"Send");
	
}
CBuilding CGui::GetBuilding()
{
	return this->building;
}
void CGui::SetBuilding(CBuilding& newBuilding)
{
	this->building=newBuilding;
}
void CGui::CreateBuildingInfoBox(CBuilding newBuilding)
{
	this->building=newBuilding;

	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_BUILDING_INFORMATION_WINDOW,true);
	IVideoDriver* driver=device->getVideoDriver();
	if (e)
	{
		e->remove();
	}
	wchar_t* temp=NULL;


//	charTowchar(buildingName,temp,strlen(buildingName));
	charTowchar(this->building.GetBuildingname().c_str(),temp,strlen(newBuilding.GetBuildingname().c_str()));
	IGUIWindow* wnd=env->addWindow(rect<s32>(200,45,800,480),false,temp,0,GUI_ID_BUILDING_INFORMATION_WINDOW);

	IGUITabControl* tab=env->addTabControl(rect<s32>(2,20,800-202,480-7),wnd,true,true);
	IGUITab* picture=tab->addTab(L"Picture",GUI_ID_TAB_BUILDING_PICTURE);
	IGUITab* info=tab->addTab(L"Information",GUI_ID_TAB_BUILDING_INFORMATION);
	IGUITab* comment=tab->addTab(L"Comment",GUI_ID_TAB_BUILDING_COMMENT);

	// 照片
//	env->addImage(driver->getTexture(pictureName),position2d<int>(10,10),false,picture);
	env->addImage(driver->getTexture(this->building.GetBuildingPicture().c_str()),position2d<int>(10,10),false,picture);

	// 简介
	stringw infoStr;
//	infoStr=buildingInfo;
	infoStr=this->building.GetBuildingInfo().c_str();
	env->addStaticText(infoStr.c_str(),rect<s32>(10,10,590,480-45-10),false,false,info);
	

	// 评论
	// 他人评价区
	env->addStaticText(NULL,rect<s32>(0,0,575,320),true,true,comment,GUI_ID_STATIC_TEXT_OTHER_COMMENT,true);
	IGUIScrollBar* buildingCommentScrollbar=env->addScrollBar(false,rect<s32>(575,0,595,320),comment,GUI_ID_SCROLL_BAR_BUILDING_COMMENT);
	buildingCommentScrollbar->setMax(255);	// 他人评论的数量
	buildingCommentScrollbar->setPos(0);
	buildingCommentScrollbar->setSmallStep(1);
	env->addButton(rect<s32>(540,320,595,340),comment,GUI_ID_BUTTON_REFRESH_COMMENT,L"Refresh");

	// 自己评价
	env->addEditBox(NULL,rect<s32>(0,340,555,378),true,comment,GUI_ID_EDIT_BOX_MY_COMMENT);
	env->addButton(rect<s32>(560,358,595,378),comment,GUI_ID_BUTTON_SEND_COMMENT,L"Send");

}
void CGui::UpdateBuildingComment(int newCommentPos)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_BUILDING_INFORMATION_WINDOW,true);
	IVideoDriver* driver=device->getVideoDriver();
// 	if (e)
// 	{
// 		e->remove();
// 	}
	
//	IGUIStaticText *  aniInfo = (IGUIStaticText *)(dlg->getElementFromId(GUI_ID_TEXT_STRING, true));
/*	IGUIStaticText* staticBoxBuildingComment=(IGUIStaticText *)(e->getElementFromId(GUI_ID_STATIC_TEXT_OTHER_COMMENT,true));*/
	IGUIStaticText* staticBoxBuildingComment=(IGUIStaticText *)(e->getElementFromId(GUI_ID_STATIC_TEXT_OTHER_COMMENT,true));
	stringw strBuildingComment;
	std::string strTemp;
	strTemp.assign(this->building.GetBuildingComment().GetOtherCommentFromPos(newCommentPos));
	strBuildingComment=strTemp.c_str();
	staticBoxBuildingComment->setText(strBuildingComment.c_str());

}

void CGui::CreateOtherClientInfoBox(std::string clientName)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_PERSONAL_INFORMATION_WINDOW,true);
	if (e)
	{
		e->remove();
	}
	wchar_t* temp=NULL;

	char* charTemp="PersonalInfo";
	charTowchar(charTemp,temp,strlen(charTemp));
	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,350,400),false,temp,0,GUI_ID_PERSONAL_INFORMATION_WINDOW);

	// 姓名
	stringw clientNameTemp=clientName.c_str();
	env->addStaticText(L"Name:",rect<s32>(5,25,25,55),false,false,wnd);
	env->addEditBox(clientNameTemp.c_str(),rect<s32>(35,25,100,45),true,wnd,GUI_ID_PERSONAL_NAME);

	env->addButton(rect<s32>(10,50,110,75),wnd,GUI_ID_BUTTON_OTHER_CLIENT_PERSONAL_INFO,L"INFO");
	env->addButton(rect<s32>(10,100,110,125),wnd,GUI_ID_BUTTON_OTHER_CLIENT_TEXT_CHAT,L"TEXT");
	env->addButton(rect<s32>(10,150,110,175),wnd,GUI_ID_BUTTON_OTHER_CLIENT_VOICE_CHAT,L"VOICE");
	env->addButton(rect<s32>(10,200,110,225),wnd,GUI_ID_BUTTON_OTHER_CLIENT_VIDEO_CHAT,L"VIDEO");
	env->addButton(rect<s32>(10,250,110,275),wnd,GUI_ID_BUTTON_OTHER_CLIENT_ADD_FRIEND,L"ADD FRIEND");
	env->addButton(rect<s32>(10,300,110,325),wnd,GUI_ID_BUTTON_OTHER_CLIENT_SEND_FILE,L"SEND FILE");
}

void CGui::CreateOtherClientPersonalInfoBox(stringc newUsername,stringc newNickName,
	stringc newSignature,stringc newSex,stringc newAge,stringc newAddress)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_FRIENDINFO_WINDOW,true);
	if (e)
	{
		e->remove();
	}

	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,500,500),false,L"My Information",0,GUI_ID_FRIENDINFO_WINDOW);

	core::stringw temp;

	temp=newUsername;
	env->addStaticText(L"USER NAME:",rect<s32>(10,40,75,60),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,40,250,60),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_USER_NAME);

	//	temp=newNickName;
	checkInfoIsNull(newNickName,temp);
	env->addStaticText(L"NICK NAME:",rect<s32>(10,120,75,140),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,120,250,140),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_NICK_NAME);

	//	temp=newSignature;
	checkInfoIsNull(newSignature,temp);
	env->addStaticText(L"SIGNATURE:",rect<s32>(10,160,75,180),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,160,250,180),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_SINGATURE);

	//	temp=newSex;
	checkInfoIsNull(newSex,temp);
	env->addStaticText(L"SEX:",rect<s32>(10,200,75,220),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,200,250,220),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_SEX);

	//	temp=newAge;
	checkInfoIsNull(newAge,temp);
	env->addStaticText(L"AGE:",rect<s32>(10,240,75,260),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,240,250,260),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_AGE);

	//	temp=newAddress;
	checkInfoIsNull(newAddress,temp);
	env->addStaticText(L"ADDRESS:",rect<s32>(10,280,75,300),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,280,250,300),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_ADDRESS);

}

void CGui::CreateFriendInfoBox(std::string newName)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_FRIEND_INFORMATION_WINDOW,true);
	if (e)
	{
		e->remove();
	}
	wchar_t* temp=NULL;

	char* charTemp="PersonalInfo";
	charTowchar(charTemp,temp,strlen(charTemp));
	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,350,400),false,temp,0,GUI_ID_FRIEND_INFORMATION_WINDOW);

	// 姓名
	stringw friendName=newName.c_str();
	env->addStaticText(L"Name:",rect<s32>(5,25,25,55),false,false,wnd);
	env->addEditBox(friendName.c_str(),rect<s32>(35,25,100,45),true,wnd,GUI_ID_FRIEND_NAME);

	env->addButton(rect<s32>(10,50,110,75),wnd,GUI_ID_BUTTON_FRIEND_INFO,L"INFO");
	env->addButton(rect<s32>(10,100,110,125),wnd,GUI_ID_BUTTON_FRIEND_TEXT_CHAT,L"TEXT");
	env->addButton(rect<s32>(10,150,110,175),wnd,GUI_ID_BUTTON_FRIEND_VOICE_CHAT,L"VOICE");
	env->addButton(rect<s32>(10,200,110,225),wnd,GUI_ID_BUTTON_FRIEND_VIDEO_CHAT,L"VIDEO");
	env->addButton(rect<s32>(10,250,110,275),wnd,GUI_ID_BUTTON_FRIEND_FRIEND_SPACE,L"FRIEND SPACE");
}

void CGui::CreateFriendPersonalInfoBox(stringc newUsername,stringc newNickName,
	stringc newSignature,stringc newSex,stringc newAge,stringc newAddress)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_FRIENDINFO_WINDOW,true);
	if (e)
	{
		e->remove();
	}

	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,500,500),false,L"My Information",0,GUI_ID_FRIENDINFO_WINDOW);

	core::stringw temp;

	temp=newUsername;
	env->addStaticText(L"USER NAME:",rect<s32>(10,40,75,60),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,40,250,60),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_USER_NAME);

	//	temp=newNickName;
	checkInfoIsNull(newNickName,temp);
	env->addStaticText(L"NICK NAME:",rect<s32>(10,120,75,140),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,120,250,140),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_NICK_NAME);

	//	temp=newSignature;
	checkInfoIsNull(newSignature,temp);
	env->addStaticText(L"SIGNATURE:",rect<s32>(10,160,75,180),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,160,250,180),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_SINGATURE);

	//	temp=newSex;
	checkInfoIsNull(newSex,temp);
	env->addStaticText(L"SEX:",rect<s32>(10,200,75,220),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,200,250,220),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_SEX);

	//	temp=newAge;
	checkInfoIsNull(newAge,temp);
	env->addStaticText(L"AGE:",rect<s32>(10,240,75,260),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,240,250,260),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_AGE);

	//	temp=newAddress;
	checkInfoIsNull(newAddress,temp);
	env->addStaticText(L"ADDRESS:",rect<s32>(10,280,75,300),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,280,250,300),true,wnd,GUI_ID_FRIENDINFO_WINDOW_TEXT_ADDRESS);

//	env->addButton(rect<s32>(100,330,150,360),wnd,GUI_ID_MYINFO_WINDOW_BUTTON_SUBMIT,L"SUBMIT");

//	env->addButton(rect<s32>(140,380,240,410),wnd,GUI_ID_MYINFO_WINDOW_BUTTON_FRIEND_LIST,L"FRIEND LIST");

}

void CGui::CreateTextChatBox()
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_TEXT_CHAT_WINDOW,true);
	if (e)
	{
		e->remove();
	}
	wchar_t* temp=NULL;

	char* charTemp="PersonalInfo";
	charTowchar(charTemp,temp,strlen(charTemp));
	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,550,350),false,temp,0,GUI_ID_TEXT_CHAT_WINDOW);


	// 说话人的姓名
	env->addStaticText(L"I say:",rect<s32>(10,270,50,290),false,false,wnd);
	env->addEditBox(temp,rect<s32>(50,270,325,290),true,wnd,GUI_ID_TEXT_PERSON_SAY_STRING);
	env->addButton(rect<s32>(325,270,350,290),wnd,GUI_ID_BUTTON_SEND_CHAT_MESSAGE,L"Send");

	//env->addEditBox(temp,rect<s32>(0,30,350,250),true,wnd,GUI_ID_TEXT_STRING);
	env->addStaticText(L"",rect<s32>(0,30,350,250),true,true,wnd,GUI_ID_TEXT_STRING);
}

void CGui::CreateFriendListBox(vector<std::string> friendList)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_FRIENDLIST_WINDOW,true);
	if (e)
	{
		e->remove();
	}
	wchar_t* temp=NULL;

	char* charTemp="FriendList";
	charTowchar(charTemp,temp,strlen(charTemp));
	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,350,400),false,temp,0,GUI_ID_FRIENDLIST_WINDOW);

	for (int i=0;i!=friendList.size();i++)
	{
		stringw friendName=friendList[i].c_str();
		env->addButton(rect<s32>(10,50+i*30,140,75+i*30),wnd,GUI_ID_FRIENDLIST_WINDOW_FRIEND+i,friendName.c_str());
	}

}

void CGui::CreateMyInfoBox(stringc newUsername,stringc newPassword,stringc newNickName,
	stringc newSignature,stringc newSex,stringc newAge,stringc newAddress)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_MYINFO_WINDOW,true);
	if (e)
	{
		e->remove();
	}

	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,500,500),false,L"My Information",0,GUI_ID_MYINFO_WINDOW);

	core::stringw temp;

	temp=newUsername;
	env->addStaticText(L"USER NAME:",rect<s32>(10,40,75,60),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,40,250,60),true,wnd,GUI_ID_MYINFO_WINDOW_TEXT_USER_NAME);

	temp=newPassword;
	env->addStaticText(L"PASSWORD:",rect<s32>(10,80,75,100),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,80,250,100),true,wnd,GUI_ID_MYINFO_WINDOW_TEXT_PASSWORD);

//	temp=newNickName;
	checkInfoIsNull(newNickName,temp);
	env->addStaticText(L"NICK NAME:",rect<s32>(10,120,75,140),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,120,250,140),true,wnd,GUI_ID_MYINFO_WINDOW_TEXT_NICK_NAME);

//	temp=newSignature;
	checkInfoIsNull(newSignature,temp);
	env->addStaticText(L"SIGNATURE:",rect<s32>(10,160,75,180),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,160,250,180),true,wnd,GUI_ID_MYINFO_WINDOW_TEXT_SINGATURE);

//	temp=newSex;
	checkInfoIsNull(newSex,temp);
	env->addStaticText(L"SEX:",rect<s32>(10,200,75,220),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,200,250,220),true,wnd,GUI_ID_MYINFO_WINDOW_TEXT_SEX);

//	temp=newAge;
	checkInfoIsNull(newAge,temp);
	env->addStaticText(L"AGE:",rect<s32>(10,240,75,260),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,240,250,260),true,wnd,GUI_ID_MYINFO_WINDOW_TEXT_AGE);

//	temp=newAddress;
	checkInfoIsNull(newAddress,temp);
	env->addStaticText(L"ADDRESS:",rect<s32>(10,280,75,300),false,true,wnd);
	env->addEditBox(temp.c_str(),rect<s32>(90,280,250,300),true,wnd,GUI_ID_MYINFO_WINDOW_TEXT_ADDRESS);

	env->addButton(rect<s32>(100,330,150,360),wnd,GUI_ID_MYINFO_WINDOW_BUTTON_SUBMIT,L"SUBMIT");

	env->addButton(rect<s32>(140,380,240,410),wnd,GUI_ID_MYINFO_WINDOW_BUTTON_FRIEND_LIST,L"FRIEND LIST");

}

void CGui::CreateFriendTextChatBox()
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_TEXT_CHAT_WINDOW_FRIEND,true);
	if (e)
	{
		e->remove();
	}
	wchar_t* temp=NULL;

	char* charTemp="PersonalInfo";
	charTowchar(charTemp,temp,strlen(charTemp));
	IGUIWindow* wnd=env->addWindow(rect<s32>(200,50,550,350),false,temp,0,GUI_ID_TEXT_CHAT_WINDOW_FRIEND);


	// 说话人的姓名
	env->addStaticText(L"I say:",rect<s32>(10,270,50,290),false,false,wnd);
	env->addEditBox(temp,rect<s32>(50,270,325,290),true,wnd,GUI_ID_TEXT_PERSON_SAY_STRING_FRIEND);
	env->addButton(rect<s32>(325,270,350,290),wnd,GUI_ID_BUTTON_SEND_CHAT_MESSAGE_FRIEND,L"Send");

	//env->addEditBox(temp,rect<s32>(0,30,350,250),true,wnd,GUI_ID_TEXT_STRING);
	env->addStaticText(L"",rect<s32>(0,30,350,250),true,true,wnd,GUI_ID_TEXT_STRING_FRIEND);
}


void CGui::CreateAddFriendResultBox(bool addFriendResult)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_WINDOW_OTHER_CLIENT_ADD_FRIEND,true);
	if (e)
	{
		e->remove();
	}
	
	IGUIWindow* wnd=env->addWindow(rect<s32>(300,200,550,300),false,L"Add Friend Result",0,GUI_ID_WINDOW_OTHER_CLIENT_ADD_FRIEND);

	if (addFriendResult == true) // 增加好友成功
	{
		env->addStaticText(L"ADD FRIEND SUCCEED",rect<s32>(10,10,200,90),false,false,wnd);
	} 
	else
	{
		env->addStaticText(L"ADD FRIEND FAILED",rect<s32>(10,10,200,90),false,false,wnd);
	}
}

void CGui::CreateModityResultBox(bool modifyResut)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_WIMDOW_MODIFY_MYSELF_RESULT,true);
	if (e)
	{
		e->remove();
	}
	
	IGUIWindow* wnd=env->addWindow(rect<s32>(300,200,550,300),false,L"Modify Result",0,GUI_ID_WIMDOW_MODIFY_MYSELF_RESULT);

	if (modifyResut == true) 
	{
		env->addStaticText(L"Modify SUCCEED",rect<s32>(10,10,200,90),false,false,wnd);
	} 
	else
	{
		env->addStaticText(L"Modify FAILED",rect<s32>(10,10,200,90),false,false,wnd);
	}
}

void CGui::CreateIsStartVideoChatBox()
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_WINDOW_IS_START_VIDEO_CHAT,true);
	if (e)
	{
		e->remove();
	}
	wchar_t* temp=NULL;

	char* charTemp="PersonalInfo";
	charTowchar(charTemp,temp,strlen(charTemp));
	IGUIWindow* wnd=env->addWindow(rect<s32>(600,200,800,300),false,temp,0,GUI_ID_WINDOW_IS_START_VIDEO_CHAT);

	env->addButton(rect<s32>(10,20,90,80),wnd,GUI_ID_BUTTON_VIDEO_CAHT_START,L"OK");
	env->addButton(rect<s32>(100,20,190,80),wnd,GUI_ID_BUTTON_VIDEO_CHAT_CANCLE,L"CANCLE");

}

void CGui::CloseIsStartVideoChatBox()
{

	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_WINDOW_IS_START_VIDEO_CHAT,true);
	if (e)
	{
		e->remove();
	}
}


void CGui::CreateIsRecvFileBox(char* senderName,char* receiverName,char* fileName)
{
	IGUIEnvironment* env=device->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_WINDOW_IS_RECV_FILE,true);
	if (e)
	{
		e->remove();
	}

	core::stringw strTemp(senderName);
	strTemp+=" send a file(";
	strTemp+=fileName;
	strTemp+=") to you.\nDo you want to receive it?";

	IGUIWindow* wnd=env->addWindow(rect<s32>(500,200,800,300),false,L"Recv File",0,GUI_ID_WINDOW_IS_RECV_FILE);
	env->addStaticText(strTemp.c_str(),rect<s32>(20,40,280,60),true,true,wnd,-1,true);
	env->addButton(rect<s32>(80,70,130,90),wnd,GUI_ID_BUTTON_SEND_FILE_REQUEST_OK,L"Ok");
	env->addButton(rect<s32>(170,70,220,90),wnd,GUI_ID_BUTTON_SEND_FILE_REQUEST_CANCEL,L"Cancel");
	
}