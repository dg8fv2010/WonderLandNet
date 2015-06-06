
#pragma once

#include<iostream>
#include <string>
#include <vector>
#include <mysql++.h>

#pragma comment(lib,"mysqlpp.lib")

using namespace std;

enum commands{LOG_IN,USER_REGISTER,LOG_OFF,MODIFY_SELF,QUERY_MAN,QUERY_SENCE,FRIEND_D,FRIEND_A};
////////////////////////////要添加的mysql脚本////////////////////
// create table Comment(
// 	buildingID BINARY char(20) NOT NULL,
// 	contention char(500) ,
// 	userName char(12),
// 	primary key buildingID
// 	)
//////////////////////////////////////////////////
class Comment{
public:
	Comment(){
		this->content="none";
	}
	~Comment(){}
public:
	void setUserName(std::string userName){this->userName=userName;}
	void setContent(std::string content){this->content=content;}
	void setBuildingID(std::string buildingID){this->buildingID=buildingID;}
	void setEditDate(std::string editDate){this->editDate=editDate;}

	std::string getUsername(){return this->userName;	}
	std::string getContent(){return this->content;}
	std::string getBuildingID(){return this->buildingID;	}
	std::string getEditDate(){return this->editDate;	}

	std::string getComment()
	{
		std::string temp;
		temp.assign(userName);
		temp.append(content);
		temp.append(editDate);
		return temp;
	}
private:
	std::string userName;
	std::string content;
	std::string buildingID; 
	std::string editDate;
};
/////////////////////////////////////////////////////
class Information{
public:
	Information(){
		this->username="none";
		this->password="none";
		this->nickName="/?/";
		this->signature="/?/";
		this->sex="/?/";
		this->age="/?/";
		this->address="/?/";
		this->isOnLine="/?/";
		this->realname="/?/";
		this->education="/?/";	
		this->profession="/?/";
		this->myPhoneNum="/?/";
		this->email="/?/";
		this->hobby="/?/";
		this->selfInfo="/?/";

	}
	~Information(){

	}
	
	std::string getRealname(){
		return this->realname;
	}
	void setRealname(std::string realname){
		this->realname.assign(realname);
	}
	std::string getIsOnLine(){
		return this->isOnLine;
	}
	void setIsOnLine(std::string isOnLine){
		this->isOnLine.assign(isOnLine);
	}
	std::string getEducation(){
		return this->education;
	}
	void setEducation(std::string education){
		this->education.assign(education);
	}
	std::string getProfession(){
		return this->profession;
	}
	void setProfession(std::string profession){
		this->profession.assign(profession);
	}
	std::string getMyphoneNum(){
		return this->myPhoneNum;
	}
	void setMyphoneNum(std::string myPhoneNum){
		this->myPhoneNum.assign(myPhoneNum);
	}
	std::string getEmail(){
		return this->email;
	}
	void setEmail(std::string email){
		this->email.assign(email);
	}
	std::string getHobby(){
		return this->hobby;
	}
	void setHobby(std::string hobby){
		this->hobby.assign(hobby);
	}
	std::string getSelfInfo(){
		return this->selfInfo;
	}
	void setSelfInfo(std::string selfInfo){
		this->selfInfo.assign(selfInfo);
	}

	std::string getUsername(){
		return this->username;
	}
	void setUsername(std::string username){
		this->username.assign(username);
	}
	std::string getPassword(){
		return this->password;
	}
	void setPassword(std::string password){
		this->password.assign(password);
	}
	std::string getNickName()
	{
		return this->nickName;
	}
	void setNickName(std::string nickName)
	{
		this->nickName.assign(nickName);
	}
	std::string getSignature()
	{
		return this->signature;
	}
	void setSignature(std::string signature)
	{
		this->signature.assign(signature);
	}
	std::string getSex(){
		return this->sex;
	}
	void setSex(std::string sex){
		this->sex.assign(sex);
	}
	std::string getAge(){
		return this->age;
	}
	void setAge(std::string age){
		this->age.assign(age);
	}
	std::string getAddress(){
		return this->address;
	}
	void setAddress(std::string address){
		this->address.assign(address);
	}
private:
	
	std::string realname;	
	std::string isOnLine;
	std::string education;
	std::string profession;
	std::string myPhoneNum;
	std::string email;
	std::string hobby;
	std::string selfInfo;
	
	
	std::string username;// 规定输入字节数的大小，有客户端判断然后再提交服务器
	std::string password;
	std::string nickName;
	std::string signature;
	std::string sex;
	std::string age;
	std::string address;

};
class Messenger{
public:
	Messenger(){

	}
	Messenger(Information information,commands command,std::string table=NULL){

		this->command=command;
		this->table=table;
		this->information=information;
	}
	~Messenger(){

	}
	commands getCommand(){
		return this->command;
	}
	void setCommand(commands command1){
		this->command=command1;
	}
	std::string getTable(){
		return this->table;
	}
	void setTable(){
		this->table=table;
	}
	Information getInformation(){
		return this->information;
	}
	void setInformation(Information information){
		this->information=information;
	}
private:
	commands command;
	std::string table;
	Information information;
	bool flog;//用来标识，无返回值的操作是否成功（登录、修改等）

};
class Building{

public:


	std::string getBuildingID(){

		return this->buildingID;
	}
	void setBuildingID(std::string buildingID){

		this->buildingID=buildingID;
	}
	std::string getIntroduction(){

		return this->introduction;
	}
	void setIntroduction(std::string introduction){

		this->introduction=introduction;
	}
private:
	std::string buildingID;//主码
	std::string introduction;
};

class Location{

public:
	Location(){
		senceID="/?/";
		location="/?/";
		userName="/?/";
	}
	std::string getSenceID(){

		return this->senceID;
	}
	void setSenceID(std::string senceID){

		this->senceID=senceID;
	}
	std::string getUserName(){

		return this->userName;
	}
	void setUserName(std::string userName){

		this->userName=userName;
	}
	std::string getLocation(){

		return this->location;
	}
	void setLocation(std::string location){

		this->location=location;
	}
private:
	std::string senceID;
	std::string userName;//主码
	std::string location;
};
class Operation{
public:
	Operation(){}
	~Operation(){}

	bool log_in(Information infor); //登录     （已完成）

	Information query_messege(std::string username);// 用户个人信息 或好友个人信息     （已完成）

	Building query_sence(std::string username);//建筑物 (完成)  (还用使用senceID作为标识码吗？？？来表示来自那个场景（那就要不同的场景不同表？？）) (应只需返回string)

	unsigned int sign_In(Information infor);//注册			（已完成）

	std::string query_loction(Location location);//特定场景下人物起始位置	(已完成)		（主码 应为senceID和userName）   // 只需返回位置的 一个string

	bool log_off(Location location);//保存用户退出时的位置		（已完成）// 要有返回值，若保存失败，就不停执行保存

	bool new_sence(Location location); //当用户进入一个新场景时，插入并初始化信息 （已完成）

	bool modify_self(Information infor);  //个人信息、密码 （已完成）

	vector<std::string> query_friends(std::string userName);//好友表 （主码应为userName和friendName）

	bool add_friend(std::string userName,std::string friendName);//增加好友  (要有返回值吗) (完成)   // 返回false 如果该用户已在好友列表中

	void delete_friend(std::string userName,std::string friendName);//删除好友   (要有返回值吗)（完成）

	bool delete_user(std::string username);//注销  （还有问题）（完成）

	void view_comment(std::string buildingID, vector<Comment>& commenList);
	bool add_comment(Comment comment);
	bool delete_comment(Comment comment);
};
