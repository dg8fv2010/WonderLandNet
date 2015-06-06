#ifndef _SCENE_H
#define _SCENE_H

#include "otherClient.h"
#include "netClient.h"
#include "utility.h"
#include "GUI.h"

#include <vector>

using namespace std;

class CScene
{
public:
	CScene();
	CScene(IrrlichtDevice* myDevice);
	void setIrrlichtDevice(IrrlichtDevice* myDevice);

	void CreateScene(/*vector<vector3df> otherClientPosition*/);
	void UpdateScene(vector<vector3df> otherClientPosition, ICameraSceneNode* camera);

	IAnimatedMesh* GetIAnimatedMesh(int ID);
	ITerrainSceneNode* GetITerrainSceneNode(int ID);

	//void Pick(ICameraSceneNode* camera, bool LButtonDown, IAnimatedMeshSceneNode* personNode);
	void Pick(ICameraSceneNode* camera, bool LButtonDown, netClient& client, CGui& newGui);

	void moveCameraControl(IAnimatedMeshSceneNode* node);

	CGui getGui();

	int GetPickedBuildingID(){return this->pickedBuilding;}

protected:
private:
	IrrlichtDevice* device;
	// Land	
	IAnimatedMesh* landMesh;
	IAnimatedMeshSceneNode* landNode;
	ITerrainSceneNode* terrain;

	// Building1
	IAnimatedMesh* building1Mesh;
	IAnimatedMeshSceneNode* building1Node;

	// Building2
	IAnimatedMesh* building2Mesh;
	IAnimatedMeshSceneNode* building2Node;

	// Pick
	ISceneNode* selectedSceneNode;
	ISceneNode* lastSelectedSceneNode;
	float GetLengthBuilding(ICameraSceneNode* camera, IAnimatedMeshSceneNode* building);
	float CScene::GetLengthBuilding(ICameraSceneNode* camera, ISceneNode* building);
	float GetLengthOtherClient(ICameraSceneNode* camera, vector3df clientPosition);
	vector<ISceneNode*> otherClientNode;

	// GUI
	CGui myGui;

	// Camera
	float direction;
	float zdirection;

	int pickedBuilding;
};


#endif