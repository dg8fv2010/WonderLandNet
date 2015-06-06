
#pragma once

#include<iostream>
#include <string>
#include <vector>
#include <mysql++.h>

#pragma comment(lib,"mysqlpp.lib")

using namespace std;

enum commands{LOG_IN,USER_REGISTER,LOG_OFF,MODIFY_SELF,QUERY_MAN,QUERY_SENCE,FRIEND_D,FRIEND_A};
////////////////////////////Ҫ��ӵ�mysql�ű�////////////////////
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
	
	
	std::string username;// �涨�����ֽ����Ĵ�С���пͻ����ж�Ȼ�����ύ������
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
	bool flog;//������ʶ���޷���ֵ�Ĳ����Ƿ�ɹ�����¼���޸ĵȣ�

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
	std::string buildingID;//����
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
	std::string userName;//����
	std::string location;
};
class Operation{
public:
	Operation(){}
	~Operation(){}

	bool log_in(Information infor); //��¼     ������ɣ�

	Information query_messege(std::string username);// �û�������Ϣ ����Ѹ�����Ϣ     ������ɣ�

	Building query_sence(std::string username);//������ (���)  (����ʹ��senceID��Ϊ��ʶ���𣿣�������ʾ�����Ǹ��������Ǿ�Ҫ��ͬ�ĳ�����ͬ������) (Ӧֻ�践��string)

	unsigned int sign_In(Information infor);//ע��			������ɣ�

	std::string query_loction(Location location);//�ض�������������ʼλ��	(�����)		������ ӦΪsenceID��userName��   // ֻ�践��λ�õ� һ��string

	bool log_off(Location location);//�����û��˳�ʱ��λ��		������ɣ�// Ҫ�з���ֵ��������ʧ�ܣ��Ͳ�ִͣ�б���

	bool new_sence(Location location); //���û�����һ���³���ʱ�����벢��ʼ����Ϣ ������ɣ�

	bool modify_self(Information infor);  //������Ϣ������ ������ɣ�

	vector<std::string> query_friends(std::string userName);//���ѱ� ������ӦΪuserName��friendName��

	bool add_friend(std::string userName,std::string friendName);//���Ӻ���  (Ҫ�з���ֵ��) (���)   // ����false ������û����ں����б���

	void delete_friend(std::string userName,std::string friendName);//ɾ������   (Ҫ�з���ֵ��)����ɣ�

	bool delete_user(std::string username);//ע��  ���������⣩����ɣ�

	void view_comment(std::string buildingID, vector<Comment>& commenList);
	bool add_comment(Comment comment);
	bool delete_comment(Comment comment);
};
