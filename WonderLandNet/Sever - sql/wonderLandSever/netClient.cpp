
#include "netClient.h"

netClient::netClient()
{
//	clientName=NULL;
}

netClient::netClient(const netClient&)
{

}

netClient::~netClient()
{
	networkId=0;
	systemAddress=NULL;
	characterPosition=vector3df(0,0,0);
}
void netClient::setClientName(std::string newName)
{
	this->clientName=newName;
}
std::string netClient::getClientName()
{
	return this->clientName;
}

void netClient::setSystemAddress(RakNet::SystemAddress newAddress)
{
	this->systemAddress=newAddress;
}

SystemAddress netClient::getSystemAddresss()
{
	return this->systemAddress;
}

void netClient::setPosition(vector3df newPosition)
{
	this->characterPosition=newPosition;
}

vector3df netClient::getPosition()
{
	return this->characterPosition;
}

void netClient::setNetworkID(NetworkID newID)
{
	this->networkId=newID;
}

NetworkID netClient::getNetworkID()
{
	return this->networkId;
}