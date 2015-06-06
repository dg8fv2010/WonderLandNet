#include "Building.h"


CBuilding::CBuilding(void)
{
	this->buildingID=-1;
}


CBuilding::~CBuilding(void)
{
}

CBuilding::CBuilding(const CBuilding& newBuilding)
{
	this->buildingID=newBuilding.buildingID;
	this->buildingName=newBuilding.buildingName;
	this->buildingPicture=newBuilding.buildingPicture;
	this->buildingInfo=newBuilding.buildingInfo;
	this->buildingComment=newBuilding.buildingComment;
}

int CBuilding::GetbuildingID()
{
	return this->buildingID;
}
void CBuilding::SetBuildingID(int newID)
{
	this->buildingID=newID;
}
std::string CBuilding::GetBuildingname()
{
	return this->buildingName;
}
void CBuilding::SetBuildingName(std::string& newBuildingName)
{
	this->buildingName=newBuildingName;
}
std::string CBuilding::GetBuildingPicture()
{
	return this->buildingPicture;
}
void CBuilding::SetBuildingPicture(std::string& newBuildingPicture)
{
	this->buildingPicture=newBuildingPicture;
}
std::string CBuilding::GetBuildingInfo()
{
	return this->buildingInfo;
}
void CBuilding::SetBuildingInfo(std::string& newBuildingInfo)
{
	this->buildingInfo=newBuildingInfo;
}


CBuildingComment CBuilding::GetBuildingComment()
{
	return this->buildingComment;
}
void CBuilding::SetBuildingComment(CBuildingComment& newBuildingComment)
{
	this->buildingComment=newBuildingComment;
}

CBuilding& CBuilding::operator=(const CBuilding& newBuilding)
{
	this->buildingID=newBuilding.buildingID;
	this->buildingName=newBuilding.buildingName;
	this->buildingPicture=newBuilding.buildingPicture;
	this->buildingInfo=newBuilding.buildingInfo;
	this->buildingComment=newBuilding.buildingComment;
	return *this;
}