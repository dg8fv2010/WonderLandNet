#include "BuildingCommentContent.h"


CBuildingCommentContent::CBuildingCommentContent(void)
{
}


CBuildingCommentContent::~CBuildingCommentContent(void)
{
}


std::string CBuildingCommentContent::GetName()
{
	return this->name;
}
void CBuildingCommentContent::SetName(string& newName)
{
	this->name=newName;
}
std::string CBuildingCommentContent::GetComment()
{
	return this->comment;
}
void CBuildingCommentContent::SetComment(string& newComment)
{
	this->comment=newComment;
}
std::string CBuildingCommentContent::GetCommentTime()
{
	return this->commentTime;
}
void CBuildingCommentContent::SetCommentTime(string& newCommentTime)
{
	this->commentTime=newCommentTime;
}

std::string CBuildingCommentContent::GetCompleteComment()
{
	std::string strTemp;
	strTemp.clear();
	strTemp.append("PUBLISHER:		");
	strTemp.append(this->name);
	strTemp.append("\r\n");
	strTemp.append("CONTENT:		");
	strTemp.append(this->comment);
	strTemp.append("\r\n");
	strTemp.append("TIME:		");
	strTemp.append(this->commentTime);
	strTemp.append("\r\n");
	strTemp.append("----------------------------------------------");
	strTemp.append("\r\n");

	return strTemp;
}



CBuildingComment::CBuildingComment()
{

}
CBuildingComment::CBuildingComment(const int newBuidingID)
{
	this->buildingID=newBuidingID;
	GetBuildingCommentByID();
}
CBuildingComment::~CBuildingComment()
{

}

void CBuildingComment::SetBuilding(int newBuildingID)
{
	this->buildingID=newBuildingID;
}
int CBuildingComment::GetBuilding()
{
	return this->buildingID;
}

std::string CBuildingComment::GetOtherCommentAtPos(unsigned int newPos)
{
	std::string strTemp;
	strTemp.clear();
	strTemp.append(this->commentContent[newPos].GetCompleteComment());
	
	return strTemp;
}
std::string CBuildingComment::GetOtherCommentFromPos(unsigned int newPos)
{
	if (newPos>=this->commentContent.size())
	{
		return '\0';
	}
	std::string strTemp;
	strTemp.clear();
	for (int i=newPos;i!=this->commentContent.size();i++)
	{
		strTemp.append(this->commentContent[i].GetCompleteComment());
		//strTemp.append("----------------------------------------------");
		//strTemp.append("\r\n");
	}

	return strTemp;
}
std::string CBuildingComment::GetOtherCommentFromPosToPos(unsigned int beginPos,unsigned int endPos)
{
	if (beginPos<endPos)
	{
		return '\0';
	}
	std::string strTemp;
	strTemp.clear();
	for (int i=beginPos;i!=endPos;i++)
	{
		strTemp.append(this->commentContent[i].GetCompleteComment());
		//strTemp.append("----------------------------------------------");
	}

	return strTemp;
}

void CBuildingComment::GetBuildingCommentByID()
{

}