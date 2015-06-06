#include "otherClient.h"

cOtherClient::cOtherClient()
{
	networkID=NULL;
	position=vector3df(0,0,0);
//	address=NULL;
	personNode=NULL;
}
cOtherClient::cOtherClient(const cOtherClient& newClient)
{
	this->sysAddress=newClient.sysAddress;
	this->position=newClient.position;
	this->networkID=newClient.networkID;
}
cOtherClient::~cOtherClient()
{

}
void cOtherClient::setOtherClientUserName(stringc newuserName)
{
	this->userName=newuserName;
}
stringc cOtherClient::getOtherClientUserName()
{
	return this->userName;
}
void cOtherClient::setOtherClientPassword(stringc newPassword)
{
	this->password=newPassword;
}
stringc cOtherClient::getOtherClientPassword()
{
	return this->password;
}
void cOtherClient::setOtherClientNickName(stringc nickName)
{
	this->nickName=nickName;
}
stringc cOtherClient::getOtherClientNickName()
{
	return this->nickName;
}
void cOtherClient::setOtherClientSignature(stringc signature)
{
	this->signature=signature;
}
stringc cOtherClient::getOtherClientSignature()
{
	return this->signature;
}
void cOtherClient::setOtherClientSex(stringc sex)
{
	this->sex=sex;
}
stringc cOtherClient::getOtherClientSex()
{
	return this->sex;
}
void cOtherClient::setOtherClientAge(stringc age)
{
	this->age=age;
}
stringc cOtherClient::getOtherClientAge()
{
	return this->age;
}
void cOtherClient::setOtherClientAdddress(stringc adddress)
{
	this->userAdddress=adddress;
}
stringc cOtherClient::getOtherClientAdddress()
{
	return this->userAdddress;
}
void cOtherClient::setNetworkID(NetworkID newID)
{
	this->networkID=newID;
}
NetworkID cOtherClient::getNetworkID()
{
	return this->networkID;
}
void cOtherClient::setPosition(vector3df newPosition)
{
	this->position=newPosition;
}
vector3df cOtherClient::getPosition()
{
	return this->position;
}
void cOtherClient::setSystemAddress(SystemAddress newAddress)
{
	this->sysAddress=newAddress;
}
SystemAddress cOtherClient::getSystemAddress()
{
	return this->sysAddress;
}

void cOtherClient::createPersonNode(IrrlichtDevice* myDevice, vector3df newPosition)
{
	ISceneManager* smgr=myDevice->getSceneManager();
	IVideoDriver* driver=myDevice->getVideoDriver();

	IAnimatedMesh* personMesh=smgr->getMesh("../../media/sydney.md2");
	this->personNode= smgr->addAnimatedMeshSceneNode( personMesh );
	if (!personMesh)
	{
		myDevice->drop();
		//return 1;
	}
	if (this->personNode)
	{
		this->personNode->setScale(vector3df(0.4f,0.4f,0.4f));
		this->personNode->setPosition(newPosition);
		this->personNode->setMaterialTexture( 0, driver->getTexture("../../media/sydney.bmp") );
		this->personNode->setMaterialFlag(EMF_LIGHTING, false);
		this->personNode->getMaterial(0).Shininess=28.0f;
		this->personNode->getMaterial(0).NormalizeNormals=true;
		this->personNode->setMD2Animation ( scene::EMAT_STAND );

	}
	personMesh->setMaterialFlag(EMF_LIGHTING,false);

}

IAnimatedMeshSceneNode* cOtherClient::getPersonalNode()
{
	return this->personNode;
}

void cOtherClient::clientMove(vector3df newPosition)
{
	this->personNode->setPosition(newPosition);
	this->position=newPosition;
}