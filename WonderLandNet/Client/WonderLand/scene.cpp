#include "scene.h"


CScene::CScene()
{
}

CScene::CScene(IrrlichtDevice* myDevice)
{
	device=myDevice;
	//CGui myGui(myDevice);
	myGui.SetIrrlichtDevice(myDevice);
	selectedSceneNode=0;
	lastSelectedSceneNode=0;

	direction=0;
	zdirection=0;

	this->pickedBuilding=-1;
}

void CScene::setIrrlichtDevice(IrrlichtDevice* myDevice)
{
	device=myDevice;
	//CGui myGui(myDevice);
	myGui.SetIrrlichtDevice(myDevice);
	selectedSceneNode=0;
	lastSelectedSceneNode=0;

	direction=0;
	zdirection=0;
}

void CScene::CreateScene(/*vector<vector3df> otherClientPosition*/)
{
	ISceneManager* smgr=device->getSceneManager();
	IVideoDriver* driver=device->getVideoDriver();

	smgr->setAmbientLight(SColorf(0.0f, 0.0f, 0.0f));


	// 天空盒
// 	ISceneNode* SkyBox=smgr->addSkyBoxSceneNode(driver->getTexture("../../media/irrlicht2_up.jpg"),
// 		driver->getTexture("../../media/irrlicht2_dn.jpg"),
// 		driver->getTexture("../../media/irrlicht2_lf.jpg"),
// 		driver->getTexture("../../media/irrlicht2_rt.jpg"),
// 		driver->getTexture("../../media/irrlicht2_ft.jpg"),
// 		driver->getTexture("../../media/irrlicht2_bk.jpg"));
	ISceneNode* SkyBox=smgr->addSkyBoxSceneNode(driver->getTexture("../../media/skyBoxTop.jpg"),
		driver->getTexture("../../media/skyBoxTop.jpg"),
		driver->getTexture("../../media/skyBoxTop.jpg"),
		driver->getTexture("../../media/skyBoxTop.jpg"),
		driver->getTexture("../../media/skyBoxTop.jpg"),
		driver->getTexture("../../media/skyBoxTop.jpg"));
	



	terrain=smgr->addTerrainSceneNode(
		"../../media/land.jpg",0,-1,
		core::vector3df(-500.0f, 0.0f, -1500.0f), // 节点坐标
		core::vector3df(0.f, 0.f, 0.f), // 旋转矩阵
		core::vector3df(20.0f, 0.0f, 20.0f), // 缩放矩阵
		video::SColor ( 255, 255, 255, 255 ), // 顶点颜色
		1, // LOD最大程度
		scene::ETPS_17, // 地形块大小
		0 // 平滑度
		);
	terrain->setMaterialFlag(EMF_LIGHTING,false);
	terrain->setMaterialTexture(0,driver->getTexture("../../media/terrain-texture.jpg"));
//	terrain->setMaterialTexture(1,driver->getTexture("../../media/terrain-texture.jpg"));
	terrain->setMaterialType(EMT_DETAIL_MAP);
	terrain->scaleTexture(1.0f);

	/*
	// Building1
	building1Mesh=smgr->getMesh("../../media/building1.obj");
	building1Node=smgr->addAnimatedMeshSceneNode(building1Mesh);
	if (building1Node)
	{			
		building1Node->setPosition(vector3df(0,-10,140));
		building1Node->setMaterialTexture(0,driver->getTexture("../../media/wall.bmp"));
		building1Node->setMaterialFlag(EMF_LIGHTING,false);
	}

	// Building2
	building2Mesh=smgr->getMesh("../../media/building2.obj");
	building2Node=smgr->addAnimatedMeshSceneNode(building2Mesh);
	if (building2Node)
	{			
		building2Node->setPosition(vector3df(30,0,0));
		building2Node->setMaterialTexture(0,driver->getTexture("../../media/wall.bmp"));
		building2Node->setMaterialFlag(EMF_LIGHTING,false);
	}
	*/

	smgr->loadScene("../../media/test.irr");
}


void CScene::UpdateScene(vector<vector3df> otherClientPosition, ICameraSceneNode* camera)
{
	ISceneManager* smgr=device->getSceneManager();
	IVideoDriver* driver=device->getVideoDriver();

	// 测试用
	IAnimatedMesh* personMeshTest=smgr->getMesh("../../media/sydney.md2");
	IAnimatedMeshSceneNode* personNode = smgr->addAnimatedMeshSceneNode( personMeshTest );
	if (!personMeshTest)
	{
		device->drop();
		return ;
	}
	if (personNode)
	{
		personNode->setScale(vector3df(0.4f,0.4f,0.4f));
		personNode->setPosition(vector3df(0.0f,10.0f,0.0f));
		personNode->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
		personNode->setMaterialFlag(EMF_LIGHTING, false);
		personNode->getMaterial(0).Shininess=28.0f;
		personNode->getMaterial(0).NormalizeNormals=true;
		personNode->setMD2Animation ( scene::EMAT_STAND );

	}
	personMeshTest->setMaterialFlag(EMF_LIGHTING,false);

	// 显示其他客户端
	for (int i=0;i!=otherClientPosition.size();i++)
	{
		IAnimatedMesh* personMesh=smgr->getMesh("../../media/sydney.md2");
		IAnimatedMeshSceneNode* personNode = smgr->addAnimatedMeshSceneNode( personMesh );
		if (!personMesh)
		{
			device->drop();
			return ;
		}
		if (personNode && personNode->getPosition()!=camera->getPosition())
		{
//			personNode->setPosition(vector3df(10,20,0));
//			personNode->setScale(vector3df(0.5,0.5,0.5));
			personNode->setPosition(otherClientPosition[i]);
			personNode->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
			personNode->setMaterialFlag(EMF_LIGHTING, false);
			personNode->getMaterial(0).Shininess=28.0f;
			personNode->getMaterial(0).NormalizeNormals=true;
			personNode->setMD2Animation ( scene::EMAT_STAND );

		}
		personMesh->setMaterialFlag(EMF_LIGHTING,false);
	}
}

CGui CScene::getGui()
{
	return this->myGui;
}

IAnimatedMesh* CScene::GetIAnimatedMesh(int ID)
{
	switch (ID)
	{
	case ID_LAND:
		return landMesh;
		break;
	default:
		break;
	}

	return NULL;
}

ITerrainSceneNode* CScene::GetITerrainSceneNode(int ID)
{
	switch (ID)
	{
	case ID_LAND:
		return terrain;
		break;
	default:
		break;
	}

	return NULL;
}

float CScene::GetLengthBuilding(ICameraSceneNode* camera, IAnimatedMeshSceneNode* building)
{
// 	line3d<f32> line;
// 	float len;
// 	line.start=camera->getPosition();
// 	line.end=building->getPosition();
// 	len=abs(abs(line.start.Z)-abs(line.end.Z));

	float len;
	vector3df start=camera->getPosition();
	vector3df end=building->getPosition();
	len=(start.X-end.X)*(start.X-end.X)+(start.Y-end.Y)*(start.Y-end.Y);
	return sqrt(len);
}
float CScene::GetLengthBuilding(ICameraSceneNode* camera, ISceneNode* building)
{
	// 	line3d<f32> line;
	// 	float len;
	// 	line.start=camera->getPosition();
	// 	line.end=building->getPosition();
	// 	len=abs(abs(line.start.Z)-abs(line.end.Z));

	float len;
	vector3df start=camera->getPosition();
	vector3df end=building->getPosition();
	len=(start.X-end.X)*(start.X-end.X)+(start.Z-end.Z)*(start.Z-end.Z);
	return sqrt(len);
}

float CScene::GetLengthOtherClient(ICameraSceneNode* camera,vector3df clientPosition)
{
// 	line3d<f32> line;
// 	float len;
// 	line.start=camera->getPosition();
// 	line.end=clientPosition;
// 	len=abs(abs(line.start.Z)-abs(line.end.Z));
	IVideoDriver* driver=device->getVideoDriver();
	ISceneManager* smgr=device->getSceneManager();
	
	/*
	line.start = camera->getPosition();
	line.end = line.start + (camera->getTarget() - line.start).normalize() * 1000.0f;
	*/
	float len;
	vector3df start=camera->getPosition();
	vector3df end=clientPosition;
	len=(start.X-end.X)*(start.X-end.X)+(start.Y-end.Y)*(start.Y-end.Y);

	return sqrt(len);
}
//void CScene::Pick(ICameraSceneNode* camera, bool LButtonDown, IAnimatedMeshSceneNode* personNode)
void CScene::Pick(ICameraSceneNode* camera, bool LButtonDown,  netClient& client, CGui& newGui)
{
	if (LButtonDown==false)
	{
		return;
	}
	vector<cOtherClient*> otherClient=client.getOtherClient();
	ISceneManager* smgr=device->getSceneManager();
	myGui.SetIrrlichtDevice(device);
	// 拾取
	scene::IMetaTriangleSelector * meta = smgr->createMetaTriangleSelector();
	core::array<scene::ISceneNode *> nodes;
	smgr->getSceneNodesFromType(scene::ESNT_ANY,nodes);
	for (int i=0;i!=nodes.size();i++)
	{
		scene::ISceneNode * node = nodes[i];
		scene::ITriangleSelector * selector = 0;

		switch(node->getType())
		{
		case scene::ESNT_CUBE:
		case scene::ESNT_ANIMATED_MESH:
			selector = smgr->createTriangleSelectorFromBoundingBox(node);
			break;
		case scene::ESNT_MESH:
		case scene::ESNT_SPHERE: 
			selector = smgr->createTriangleSelector(((scene::IMeshSceneNode*)node)->getMesh(), node);
			break;
		default:
			break;
		}

		if(selector)
		{
			meta->addTriangleSelector(selector);
			selector->drop();
		}
	}
	
	ISceneNodeAnimator* anim=smgr->createCollisionResponseAnimator(meta,camera,
		vector3df(30,15,30),vector3df(0,0,0),vector3df(0,0,0));
	meta->drop(); 

	camera->addAnimator(anim);
	anim->drop(); 


	scene::ISceneNode* building1Node=smgr->getSceneNodeFromId(1);
	scene::ISceneNode* building2Node=smgr->getSceneNodeFromId(2);
	scene::ISceneNode* building3Node=smgr->getSceneNodeFromId(3);

	float len;
	if (building1Node)
	{
		len=GetLengthBuilding(camera,building1Node);
		if (len<=120)
		{
			CBuilding buidingTemp;
			std::string strTemp;
			buidingTemp.SetBuildingID(GUI_ID_BUILDING_HUALIAN);
			strTemp.assign("Building-HuaLian");
			buidingTemp.SetBuildingName(strTemp);
			strTemp.assign("../../media/myPictureHuaLian.jpg");
			buidingTemp.SetBuildingPicture(strTemp);
			strTemp.assign("Hua Lian");
			buidingTemp.SetBuildingInfo(strTemp);
			myGui.CreateBuildingInfoBox(buidingTemp);
			client.netSendGetBuildingComment(GUI_ID_BUILDING_HUALIAN);
			//myGui.CreateBuildingInfoBox("Building1","../../media/myPictureHuaLian.jpg","Hua Lian");
			this->pickedBuilding=GUI_ID_BUILDING_HUALIAN;
			myGui.SetBuilding(buidingTemp);
		}
	}
	if (building2Node)
	{
		len=GetLengthBuilding(camera,building2Node);
		if (len<=120)
		{
			CBuilding buidingTemp;
			std::string strTemp;
			buidingTemp.SetBuildingID(GUI_ID_BUILDING_CHINAUNICOM);
			strTemp.assign("Building-China Unicom");
			buidingTemp.SetBuildingName(strTemp);
			strTemp.assign("../../media/myPictureChinaUnicom.jpg");
			buidingTemp.SetBuildingPicture(strTemp);
			strTemp.assign("China Unicom");
			buidingTemp.SetBuildingInfo(strTemp);
			myGui.CreateBuildingInfoBox(buidingTemp);
			//myGui.CreateBuildingInfoBox("Building2","../../media/myPictureChinaUnicom.jpg","China Unicom!");
			this->pickedBuilding=GUI_ID_BUILDING_CHINAUNICOM;
			myGui.SetBuilding(buidingTemp);
		}
	}
	if (building3Node)
	{
		len=GetLengthBuilding(camera,building3Node);
		if (len<=120)
		{
			CBuilding buidingTemp;
			std::string strTemp;
			buidingTemp.SetBuildingID(GUI_ID_BUILDING_CHINAUNICOM);
			strTemp.assign("Building-Fruit Store");
			buidingTemp.SetBuildingName(strTemp);
			strTemp.assign("../../media/myPictureFriuteShop.jpg");
			buidingTemp.SetBuildingPicture(strTemp);
			strTemp.assign("Fruit Store");
			buidingTemp.SetBuildingInfo(strTemp);
			myGui.CreateBuildingInfoBox(buidingTemp);
			//myGui.CreateBuildingInfoBox("Building2","../../media/myPictureFriuteShop.jpg","Friute Shop!");
			this->pickedBuilding=GUI_ID_BUILDING_CHINAUNICOM;
			myGui.SetBuilding(buidingTemp);
		}
	}

	selectedSceneNode=smgr->getSceneCollisionManager()->getSceneNodeFromCameraBB(camera);
	for (int i=0;i!=otherClient.size();i++)
	{
		len=GetLengthOtherClient(camera,otherClient[i]->getPosition());
		if (len<=50)
		{
			myGui.CreateOtherClientInfoBox((*otherClient[i]).getOtherClientUserName().c_str());
			client.setPickedClient(*otherClient[i]);
			client.netRecvPickedClientInfoToServer();
			//myGui.CreateTextChatBox();
			//myGui.CreateFriendListBox();
			// 鼠标单击一次只能选中一个客户
			break;
		}
	}
	lastSelectedSceneNode=selectedSceneNode;
	newGui=this->getGui();

}

void CScene::moveCameraControl(IAnimatedMeshSceneNode* node)
{

		core::position2d<f32> cursorPos = device->getCursorControl()->getRelativePosition();
		scene::ICameraSceneNode* camera = device->getSceneManager()->getActiveCamera();
		core::vector3df cameraPos = camera->getAbsolutePosition();

		float change_x = (float)( cursorPos.X - 0.5 ) * 256.0f;
		float change_y = (float)( cursorPos.Y - 0.5 ) * 256.0f;
		direction += change_x;
		zdirection -= change_y;
		if( zdirection <- 90 )
			zdirection = -90;
		else
			if( zdirection > 90 )
				zdirection = 90;
		device->getCursorControl()->setPosition( 0.5f, 0.5f );

		core::vector3df playerPos = node->getPosition();

		float xf = playerPos.X - cos( direction * PI / 180.0f ) * 64.0f;
		float yf = playerPos.Y - sin( zdirection * PI / 180.0f ) * 64.0f;
		float zf = playerPos.Z + sin( direction * PI / 180.0f ) * 64.0f;

		camera->setPosition( core::vector3df( xf, yf, zf ) );
		camera->setTarget( core::vector3df( playerPos.X, playerPos.Y+25.0f, playerPos.Z ) );
		node->setRotation( core::vector3df( 0, direction, 0 ) );
}