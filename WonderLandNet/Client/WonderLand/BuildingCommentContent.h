#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CBuildingCommentContent
{
public:
	CBuildingCommentContent(void);
	~CBuildingCommentContent(void);

	std::string GetName();
	void SetName(std::string& newName);
	std::string GetComment();
	void SetComment(std::string& newComment);
	std::string GetCommentTime();
	void SetCommentTime(std::string& newCommentTime);

	std::string GetCompleteComment();

private:
	std::string name;
	std::string comment;
	std::string commentTime;
};

class CBuildingComment
{
public:
	CBuildingComment();
	CBuildingComment(const int newBuidingID);
	~CBuildingComment();

	void SetBuilding(int newBuildingID);
	int GetBuilding();

	std::string GetOtherCommentAtPos(unsigned int newPos);
	std::string GetOtherCommentFromPos(unsigned int newPos);
	std::string GetOtherCommentFromPosToPos(unsigned int beginPos,unsigned int endPos);

	void AddComment(CBuildingCommentContent& newContent){this->commentContent.push_back(newContent);}

protected:
	void GetBuildingCommentByID();

private:
	int buildingID;
	vector<CBuildingCommentContent> commentContent;
};