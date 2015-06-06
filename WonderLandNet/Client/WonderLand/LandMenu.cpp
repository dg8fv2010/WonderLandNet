
#include "LandMenu.h"


unsigned char GetPacketIdentifier(Packet* p)
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

CMainMenu::CMainMenu()
{
	startButton=0;
	MenuDevice=0;
	selected=2; 
	start=false;
	landResult=0;
	registerResult=0;
	

	landAndRegisterResult=false;
}
	
void CMainMenu::connnectToSever(IrrlichtDevice* myDevice)
{
	this->MenuDevice=myDevice;
	client.setDevice(this->MenuDevice);
	client.netInitialize();
}

netClient* CMainMenu::getClient()
{
	return &(this->client);
}
IrrlichtDevice* CMainMenu::getDevice()
{
	return (this->MenuDevice);
}

stringc CMainMenu::getName()
{
	IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();

	core::stringc s;

	s = root->getElementFromId(GUI_ID_TEXT_NAME, true)->getText();
	root->getElementFromId(GUI_ID_TEXT_NAME, true)->setText(L"");

	return s;
}
stringc CMainMenu::getPassword()
{
	IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	core::stringc s;

	s = root->getElementFromId(GUI_ID_TEXT_PASSWORD, true)->getText();
	root->getElementFromId(GUI_ID_TEXT_PASSWORD, true)->setText(L"");
	return s;
}
void CMainMenu::checkRegisterMessage(stringc &str)
{
	if (str.size()==0)
	{
		str.append("/?/");
	}
}
stringc CMainMenu::getRegisterUserName()
{
	IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	core::stringc s;

	s = root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_USER_NAME, true)->getText();
	root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_USER_NAME, true)->setText(L"");

	checkRegisterMessage(s);
	return s;
}
stringc CMainMenu::getRegisterPassword()
{
	IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	core::stringc s;

	s = root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_PASSWORD, true)->getText();
	root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_PASSWORD, true)->setText(L"");

	checkRegisterMessage(s);
	return s;
}
stringc CMainMenu::getRegisterNickName()
{
	IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	core::stringc s;

	s = root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_NICK_NAME, true)->getText();
	root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_NICK_NAME, true)->setText(L"");

	checkRegisterMessage(s);
	return s;
}
stringc CMainMenu::getRegisterSignature()
{
	IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	core::stringc s;

	s = root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_SINGATURE, true)->getText();
	root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_SINGATURE, true)->setText(L"");

	checkRegisterMessage(s);
	return s;
}
stringc CMainMenu::getRegisterSex()
{
	IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	core::stringc s;

	s = root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_SEX, true)->getText();
	root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_SEX, true)->setText(L"");

	checkRegisterMessage(s);
	return s;
}
stringc CMainMenu::getRegisterAge()
{
	IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	core::stringc s;

	s = root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_AGE, true)->getText();
	root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_AGE, true)->setText(L"");

	checkRegisterMessage(s);
	return s;
}
stringc CMainMenu::getRegisterAddress()
{
	IGUIEnvironment* env = MenuDevice->getGUIEnvironment();
	gui::IGUIElement* root = env->getRootGUIElement();
	core::stringc s;

	s = root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_ADDRESS, true)->getText();
	root->getElementFromId(GUI_ID_REGISTER_WINDOW_TEXT_ADDRESS, true)->setText(L"");

	checkRegisterMessage(s);
	return s;
}


void CMainMenu::createRegisterWindow()
{
	gui::IGUIEnvironment* guienv = MenuDevice->getGUIEnvironment();
	IGUIElement* root=guienv->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_REIGSTER_WINDOW,true);
	if (e)
	{
		e->remove();
	}
	IGUIWindow* wnd=guienv->addWindow(rect<s32>(200,50,500,500),false,L"Reigister Window",0,GUI_ID_REIGSTER_WINDOW);

	guienv->addStaticText(L"USER NAME:",rect<s32>(10,40,75,60),false,true,wnd);
	guienv->addEditBox(L'\0',rect<s32>(90,40,250,60),true,wnd,GUI_ID_REGISTER_WINDOW_TEXT_USER_NAME);

	guienv->addStaticText(L"PASSWORD:",rect<s32>(10,80,75,100),false,true,wnd);
	guienv->addEditBox(L'\0',rect<s32>(90,80,250,100),true,wnd,GUI_ID_REGISTER_WINDOW_TEXT_PASSWORD);

	guienv->addStaticText(L"NICK NAME:",rect<s32>(10,120,75,140),false,true,wnd);
	guienv->addEditBox(L'\0',rect<s32>(90,120,250,140),true,wnd,GUI_ID_REGISTER_WINDOW_TEXT_NICK_NAME);

	guienv->addStaticText(L"SIGNATURE:",rect<s32>(10,160,75,180),false,true,wnd);
	guienv->addEditBox(L'\0',rect<s32>(90,160,250,180),true,wnd,GUI_ID_REGISTER_WINDOW_TEXT_SINGATURE);

	guienv->addStaticText(L"SEX:",rect<s32>(10,200,75,220),false,true,wnd);
	guienv->addEditBox(L'\0',rect<s32>(90,200,250,220),true,wnd,GUI_ID_REGISTER_WINDOW_TEXT_SEX);

	guienv->addStaticText(L"AGE:",rect<s32>(10,240,75,260),false,true,wnd);
	guienv->addEditBox(L'\0',rect<s32>(90,240,250,260),true,wnd,GUI_ID_REGISTER_WINDOW_TEXT_AGE);

	guienv->addStaticText(L"ADDRESS:",rect<s32>(10,280,75,300),false,true,wnd);
	guienv->addEditBox(L'\0',rect<s32>(90,280,250,300),true,wnd,GUI_ID_REGISTER_WINDOW_TEXT_ADDRESS);

	guienv->addButton(rect<s32>(100,350,150,380),wnd,GUI_ID_REGISTER_WINDOW_BUTTON_SUBMIT,L"SUBMIT");
}

bool CMainMenu::checkRegisterinfo(stringc newName,stringc newPassword,stringc nickName, 
	stringc signature,stringc sex,stringc age,stringc adddress)
{
	if (newName.equals_ignore_case("/?/") || newName.size()<=5 || newName.size()>=20)
	{
		createRegisterFailedWindow("USER NAME must between 5~20!");
		return false;
	}
	if (newPassword.equals_ignore_case("/?/") || newPassword.size()<=5 || newPassword.size()>=20)
	{
		createRegisterFailedWindow("PASSWORD must between 5~20!");
		return false;
	}
	if (nickName.equals_ignore_case("/?/") || nickName.size()<=5 || nickName.size()>=12)
	{
		createRegisterFailedWindow("NICK NAME must between 5~12!");
		return false;
	}
	if (signature.size()<=0 || signature.size()>=200)
	{
		createRegisterFailedWindow("SIGNATURE must between 0~200!");
		return false;
	}
	if (sex.size()<=0 || sex.size()>=10)
	{
		createRegisterFailedWindow("SEX must between 5~20!");
		return false;
	}	
	if (sex.size()<=0 || sex.size()>=10)
	{
		createRegisterFailedWindow("AGE must between 5~20!");
		return false;
	}
	if (adddress.size()<=0 || adddress.size()>=50)
	{
		createRegisterFailedWindow("ADDRESS must between 0~50!");
		return false;
	}
	return true;
}

void CMainMenu::createRegisterFailedWindow(std::string failedInfo)
{
	IGUIEnvironment* env=MenuDevice->getGUIEnvironment();
	IGUIElement* root=env->getRootGUIElement();
	IGUIElement* e=root->getElementFromId(GUI_ID_REGISTER_FAILED_WINDOW,true);
	if (e)
	{
		e->remove();
	}
	
	IGUIWindow* wnd=env->addWindow(rect<s32>(300,200,550,300),false,L"Register Failed Window",0,GUI_ID_REGISTER_FAILED_WINDOW);

	stringw temp;
	temp=failedInfo.c_str();
	env->addStaticText(temp.c_str(),rect<s32>(10,50,200,150),false,false,wnd);
}
bool CMainMenu::run(core::stringw &playerName)
{
	video::E_DRIVER_TYPE driverType = video::EDT_DIRECT3D9;

	MenuDevice = createDevice(driverType,
		core::dimension2d<u32>(1300, 700), 16, false, false, true, this);

	connnectToSever(MenuDevice);
	video::IVideoDriver* driver = MenuDevice->getVideoDriver();
	scene::ISceneManager* smgr = MenuDevice->getSceneManager();
	gui::IGUIEnvironment* guienv = MenuDevice->getGUIEnvironment();

	core::stringw str = "Land Menu";
	str += MenuDevice->getVersion();
	MenuDevice->setWindowCaption(str.c_str());

	// set new Skin
//	gui::IGUISkin* newskin = guienv->createSkin(gui::EGST_BURNING_SKIN);
//	guienv->setSkin(newskin);
//	newskin->drop();

	// load font
	gui::IGUIFont* font = guienv->getFont("../media/fonthaettenschweiler.bmp");
	if (font)
		guienv->getSkin()->setFont(font);
//	font->setKerningHeight(1);
//	font->setKerningWidth(2);


	// add images

	const s32 leftX = 260;

	// 增加登陆界面
	guienv->addStaticText(landAndRegisterResult,rect<s32>(100,400,400,600),true,true,NULL,GUI_ID_TEXT_LAND_AND_REGISTER_RESULT);
	guienv->addStaticText(L"Name:",rect<s32>(100,450,170,470),true,true,0,-1,true);
	wchar_t* temp=NULL;
	guienv->addEditBox(temp,rect<s32>(200,450,400,470),true,NULL,GUI_ID_TEXT_NAME);
	guienv->addStaticText(L"Password:",rect<s32>(100,550,170,570),true,true,0,-1,true);
	guienv->addEditBox(temp,rect<s32>(200,550,400,570),true,NULL,GUI_ID_TEXT_PASSWORD);

	guienv->addButton(rect<s32>(100,640,170,670),NULL,GUI_ID_BUTTON_LAND,L"Land");
	guienv->addButton(rect<s32>(300,640,370,670),NULL,GUI_ID_BUTTON_REGISTR,L"Register");

	// create a fixed camera
	smgr->addCameraSceneNode(0, core::vector3df(45,0,0), core::vector3df(0,0,10));

	// irrlicht logo and background
	// add irrlicht logo
	bool oldMipMapState = driver->getTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS);
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

	guienv->addImage(driver->getTexture("../media/irrlichtlogo2.png"),
		core::position2d<s32>(5,5));

	video::ITexture* irrlichtBack = driver->getTexture("../media/back.jpg");
	driver->makeColorKeyTexture(irrlichtBack,vector2d<s32>(0,0));
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, oldMipMapState);

	// query original skin color
	//getOriginalSkinColor();

	// set transparency
	//setTransparency();

	// draw all

	//////////////////////////////////////////////////////////////////////////
	// 测试使用
	//return true;
	//////////////////////////////////////////////////////////////////////////


	while(MenuDevice->run())
	{
		if (MenuDevice->isWindowActive())
		{
			driver->beginScene(false, true, video::SColor(0,0,0,0));

			if (irrlichtBack)
				driver->draw2DImage(irrlichtBack,core::position2d<int>(0,0));

			smgr->drawAll();
			guienv->drawAll();
			driver->endScene();
		}
		start=client.netReceiveMessage();
		if (start==1)
		{
			break;
		}
	}


	
//	MenuDevice->drop();
	if (start==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CMainMenu::OnEvent(const SEvent& event)
{
	stringc registerUserName;
	stringc registerPassword;
	stringc registereNickName;
	stringc registerSignature;
	stringc registereSex;
	stringc registerAge;
	stringc registereAddress;
	
	if (event.EventType == EET_GUI_EVENT)
	{
		s32 id = event.GUIEvent.Caller->getID();
		switch (event.GUIEvent.EventType)
		{
		case EGET_BUTTON_CLICKED:
			switch(id)
			{
			case GUI_ID_BUTTON_REGISTR: 
				createRegisterWindow();				
				break;
			case GUI_ID_REGISTER_WINDOW_BUTTON_SUBMIT:
				registerUserName=this->getRegisterUserName();
				registerPassword=this->getRegisterPassword();
				registereNickName=this->getRegisterNickName();
				registerSignature=this->getRegisterSignature();				
				registereSex=this->getRegisterSex();
				registerAge=this->getRegisterAge();
				registereAddress=this->getRegisterAddress();
				if (checkRegisterinfo(registerUserName,registerPassword,registereNickName,
					registerSignature,registereSex,registerAge,registereAddress) == true)
				{
					client.netSendRegisterMessageToSever(registerUserName,registerPassword,
						registereNickName,registerSignature,registereSex,registerAge,
						registereAddress);
				}
// 				if (checkRegisterinfo(this->getRegisterUserName(),
// 					this->getRegisterPassword(),this->getRegisterNickName(),
// 					this->getRegisterSignature(),this->getRegisterSex(),
// 					this->getRegisterAge(),this->getRegisterAddress()) == true)
// 				{
// 					client.netSendRegisterMessageToSever(this->getRegisterUserName(),
// 						this->getRegisterPassword(),this->getRegisterNickName(),
// 						this->getRegisterSignature(),this->getRegisterSex(),
// 						this->getRegisterAge(),this->getRegisterAddress());
// 				}
				break;
			case GUI_ID_BUTTON_LAND:
				client.setUserName(this->getName());
				client.setPassword(this->getPassword());
				client.netSendLandToSever(client.getUserName(),client.getPassword());
				break;
			default:
				break;
			}
		}
	}

	return false;
}


void CMainMenu::getOriginalSkinColor()
{
	irr::gui::IGUISkin * skin = MenuDevice->getGUIEnvironment()->getSkin();
	for (s32 i=0; i<gui::EGDC_COUNT ; ++i)
	{
		SkinColor[i] = skin->getColor( (gui::EGUI_DEFAULT_COLOR)i );
	}

}


void CMainMenu::setTransparency()
{
	irr::gui::IGUISkin * skin = MenuDevice->getGUIEnvironment()->getSkin();

	for (u32 i=0; i<gui::EGDC_COUNT ; ++i)
	{
		video::SColor col = SkinColor[i];

//		if (false == transparent)
			col.setAlpha(255);

		skin->setColor((gui::EGUI_DEFAULT_COLOR)i, col);
	}
}

