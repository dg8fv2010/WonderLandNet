#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <irrlicht.h>

using namespace std;

using namespace irr;
using namespace core;
using namespace io;
using namespace scene;
using namespace gui;
using namespace video;



enum
{
	GUI_ID_BUILDING_INFORMATION_WINDOW,
	GUI_ID_BUILDING_PICTURE,
	GUI_ID_BUILDING_1,
	GUI_ID_BUILDING_2,

	GUI_ID_PERSONAL_INFORMATION_WINDOW,
	GUI_ID_PERSONAL_NAME,

	ID_ISPICKABLE,
	ID_ISNOTPICKABLE,

	ID_LAND,
	ID_BUILDING_1,
	ID_BUILDING_2,

};

//function: charTowchar
//purpose:char to WCHAR 、wchar_t、LPWSTR etc
void charTowchar(const char *chr, wchar_t *wchar, int size);  
 
//function: wcharTochar
//purpose:WCHAR 、wchar_t、LPWSTR to char
void wcharTochar(const wchar_t *wchar, char *chr, int length);  



#endif