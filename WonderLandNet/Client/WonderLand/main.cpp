#include "WonderLand.h"
#include "LandMenu.h"

void main()
{
	CMainMenu mainMenu;
	CWonderLand wonderLand;
	stringw s(L"Test");

	if (mainMenu.run(s)==true)
	{
		wonderLand.setDevice(mainMenu.getDevice());
		wonderLand.setNetClient(mainMenu.getClient());
		wonderLand.run();
	}
}



