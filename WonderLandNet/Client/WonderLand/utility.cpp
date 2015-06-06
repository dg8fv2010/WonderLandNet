#include "utility.h"



//function: charTowchar
//purpose:char to WCHAR 、wchar_t、LPWSTR etc
void charTowchar(const char *chr, wchar_t *wchar, int size)  
{     
	MultiByteToWideChar( CP_ACP, 0, chr,  
		strlen(chr)+1, wchar, size/sizeof(wchar[0]) );  
}  
//function: wcharTochar
//purpose:WCHAR 、wchar_t、LPWSTR to char
void wcharTochar(const wchar_t *wchar, char *chr, int length)  
{  
	WideCharToMultiByte( CP_ACP, 0, wchar, -1,  
		chr, length, NULL, NULL );  
} 