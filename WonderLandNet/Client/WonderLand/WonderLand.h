#ifdef _MSC_VER
// We'll also define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

//#include "utility.h"
#include "netClient.h"
#include <irrlicht.h>
#include "driverChoice.h"

#include "GUI.h"
#include "utility.h"
#include "scene.h"


using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace gui;
using namespace video;

// Movement speed
const f32 MOVEMENT_SPEED = 0.5f;;

class CWonderLand : public IEventReceiver
{
public:
	CWonderLand();
	CWonderLand(const CWonderLand&);

	void setNetClient(netClient* newClient);
	void setDevice(IrrlichtDevice* newdevice);

	void run();

	virtual bool OnEvent(const SEvent& event);

	virtual bool IsKeyDown(EKEY_CODE keyCode);
protected:
private:

	// GUI接口
	CGui myGui;

	// 场景接口
	CScene myScene;
	// 人物移动，每隔nms向服务器发送数据
	u32 lastTime;

	netClient client;
	//vector<vector3df> otherClientPosition;

	IrrlichtDevice* device;
	ICameraSceneNode* camera;
	ISceneNode* SkyBox;
	/*CScene myScene(device);*/
	bool LButtonDown;

	


	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};