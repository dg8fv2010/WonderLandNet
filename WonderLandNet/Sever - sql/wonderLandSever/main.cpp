
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "BitStream.h"
#include "RakNetTypes.h"  // MessageID

#include "netSever.h"


using namespace std;

int main(void)
{
	netSever sever;
	sever.netInitialize();

	while (1)
	{
		sever.netReceiveMessage();
	}

	return 0;
}


