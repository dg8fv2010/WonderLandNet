#pragma once

#include <iostream>
#include <string>
#include "BuildingCommentContent.h"

using namespace std;

class CBuilding
{
public:
	CBuilding(void);
	~CBuilding(void);
	CBuilding(const CBuilding& newBuilding);

	int GetbuildingID();
	void SetBuildingID(int newID);

	std::string GetBuildingname();
	void SetBuildingName(std::string& newBuildingName);
	std::string GetBuildingPicture();
	void SetBuildingPicture(std::string& newBuildingPicture);
	std::string GetBuildingInfo();
	void SetBuildingInfo(std::string& newBuildingInfo);
	CBuildingComment GetBuildingComment();
	void SetBuildingComment(CBuildingComment& newBuildingComment);

	CBuilding& operator=(const CBuilding& newBuilding);

private: 
	int buildingID;

	std::string buildingName;
	std::string buildingPicture;
	std::string buildingInfo;
	CBuildingComment buildingComment;
};

