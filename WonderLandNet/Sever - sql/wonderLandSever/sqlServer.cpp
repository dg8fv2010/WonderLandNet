
#include "sqlServer.h"
#include <mysql++.h>
#include<iostream>
#include<string>


using namespace std;
using namespace mysqlpp;

//定义全局变量   减少代码的冗余
static const string databaseName="3ddb";
static const string databaseIP="127.0.0.1";
static const string adminName="root";
static const string password="123";
static Connection conn;

////////////////////////////////////////////////////////////////
//定义全局变量 保存评论信息
typedef struct  comm
{
	string buildingNo;
	vector<Comment> list;
}commentList;
//vector<commentList> allComments;

void Operation::view_comment(string buildingID, vector<Comment>& commenList)
{
	commenList.clear();
	commentList comLs;
//	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
	Query query=conn.query();
	query<<"select*from comment where buildingID=%0q";
	query.parse();
	StoreQueryResult res=query.store(buildingID);
//	comLs.buildingNo=buildingID;
	for(int i=0;i!=res.num_rows();i++)
	{
		Comment comment;
		comment.setUserName(res[i]["userName"].c_str());
		comment.setEditDate(res[i]["commentTime"].c_str());
		comment.setContent(res[i]["content"].c_str());
//		comLs.list.push_back(comment);
		commenList.push_back(comment);
	}
//	allComments.push_back(comLs);
}
bool Operation::add_comment(Comment comment)
{

	SimpleResult res1;
//	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
	Query query=conn.query();
	query<<"insert into comment(buildingID,userName,content,commentTime)values(%0q,%1q,%2q,%3q)";
	query.parse();
	res1=query.execute(comment.getBuildingID(),comment.getUsername(),comment.getContent(),comment.getEditDate());
	if (res1.rows()==0)
	{
		return false;
	}
	return true;
}
bool Operation::delete_comment(Comment comment)
{
	SimpleResult res;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
	Query query=conn.query();
	query<<"delete from comment where buildingID=%0q and userName=%1q and commentTime=%2q";
	query.parse();
	res=query.execute(comment.getBuildingID(),comment.getUsername(),comment.getEditDate());
	if(res.rows()==0)
		return false;

	return true;
}

bool Operation:: log_in(Information infor) //检查用户名和密码 真确则返回 true
{              
	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<"select username from userTable where username=%0q and password=%1q";
	query.parse();
	StoreQueryResult res=query.store(infor.getUsername(),infor.getPassword());

	if(res.num_rows())
	{
		query.reset();
		query<<"update userInformation set isOnLine='true' where userName=%0q ";
		query.parse();
		query.execute(infor.getUsername());
		return true;
	}
	else
		return false;
}
unsigned int  Operation:: sign_In(Information infor)//注册，在客户端显示注册成功提示
{		

	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<"select userName from userTable where userName=%0q";
	query.parse();
	StoreQueryResult res=query.store(infor.getUsername());//在用户注册时，一旦填入用户名，就检查此用户名是否已存在
	if(res.num_rows())
	{
		return 0;//用户名已存在  
	}
	else
	{
		SimpleResult res1,res2;
		query.reset();
		query<<"insert into userInformation (address,signature,nickName,username,realname,sex,age,isOnLine,education,profession,myPhoneNum,email,hobby,selfInfo)values(%0q,%1q,%2q,%3q,%4q,%5q,%6q,%7q,%8q,%9q,%10q,%11q,%12q,%13q)";
		query.parse();
		res2=query.execute(infor.getAddress(),infor.getSignature(),infor.getNickName(),infor.getUsername(),infor.getRealname(),infor.getSex(),infor.getAge(),infor.getIsOnLine(),infor.getEducation(),infor.getProfession(),infor.getMyphoneNum(),infor.getEmail(),infor.getHobby(),infor.getSelfInfo());
		query.reset();
		query<<"insert into userTable(username,password) values(%0q,%1q)";
		query.parse();
		res1=query.execute(infor.getUsername(),infor.getPassword());
		if(res1.rows()&&res2.rows())
			return 1;  //注册成功
		else
			return 2; //注册失败，请稍后重试
	}
}


Information Operation::query_messege(string username){//查询人的讯息
	Information temp_infor;
	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<"select*from userInformation where username=%0q";
	query.parse();
	StoreQueryResult res=query.store(username);
	if(!res.num_rows())                         //如果没有此用户在此处理
	{
		temp_infor.setUsername("/?/");//客户端检查若用户名username值为 NULL则表示无此用户，并提示用户
		return temp_infor;
	}
	
	else
	{//填入对象值cout<<<<endl;

	query.reset();
	query<<"select password from usertable where username=%0q";
	query.parse();
	StoreQueryResult res1=query.store(username);

		temp_infor.setUsername(res[0]["username"].c_str());
		temp_infor.setRealname(res[0]["realName"].c_str());
		temp_infor.setSex(res[0]["sex"].c_str());
		temp_infor.setAge(res[0]["age"].c_str());
		temp_infor.setIsOnLine(res[0]["isOnLine"].c_str());
		temp_infor.setEducation(res[0]["education"].c_str());
		temp_infor.setProfession(res[0]["profession"].c_str());
		temp_infor.setMyphoneNum(res[0]["myPhoneNum"].c_str());
		temp_infor.setEmail(res[0]["email"].c_str());
		temp_infor.setHobby(res[0]["hobby"].c_str());
		temp_infor.setSelfInfo(res[0]["selfInfo"].c_str());//如果返回的是空值，会怎样？
		temp_infor.setNickName(res[0]["nickName"].c_str());
		temp_infor.setSignature(res[0]["signature"].c_str());
		temp_infor.setAddress(res[0]["address"].c_str());
		temp_infor.setPassword(res1[0]["password"].c_str());
		return  temp_infor;
	}
}


bool Operation::modify_self(Information infor){

	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();

	query<<"update userInformation set realname=%1q,sex=%2q,age=%3q,isOnLine=%4q,education=%5q,profession=%6q,myPhoneNum=%7q,email=%8q,hobby=%9q,selfInfo=%10q,nickName=%11q,signature=%12q,address=%13q where username=%0q";
	query.parse();
	SimpleResult res=query.execute(infor.getUsername(),infor.getRealname(),infor.getSex(),infor.getAge(),infor.getIsOnLine(),infor.getEducation(),infor.getProfession(),infor.getMyphoneNum(),infor.getEmail(),infor.getHobby(),infor.getSelfInfo(),infor.getNickName(),infor.getSignature(),infor.getAddress());
	cout<<res.rows()<<endl;
	if(res.rows() == 0)
	{
		cout<<"SQL-modify-self-res.rows() = 0"<<endl;
		return false;
	}
	query.reset();
	query<<"select password from usertable where username=%0q";
	query.parse();
	StoreQueryResult storeQueryResult=query.store(infor.getUsername());
	
	if(infor.getPassword().compare(storeQueryResult[0][0].c_str()) == 0)
	{
		return true;
	}
	query.reset();
	query<<"update usertable set password=%1q where userName=%0q";
	query.parse();
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	SimpleResult res2=query.execute(infor.getUsername(),infor.getPassword());
	if(res2.rows() == 0)
	{
		cout<<"SQL-modify-res2.rows() = 0"<<endl;
		return false;
	}

	return true;
}
bool  Operation:: delete_user(string username){				//根据用户名全部删除 (用户名密码，个人信息，好友表，在场景中的位置)

	SimpleResult temp1,temp2,temp3,temp4;
	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<" delete from userInformation where username=%0q";
	query.parse();
	temp1=query.execute(username);
	query.reset();
	query<<" delete from userTable where username=%0q";
	query.parse();
	temp2=query.execute(username);
	query.reset();
	query<<" delete from friendTable where username=%0q";
	query.parse();
	temp3=query.execute(username);
	query.reset();
	query<<" delete from userLocation where username=%0q";// 如果用户开始 没有加好友和没进入场景  就注册 怎么办 
	// 可行解决办法： 先将用户名插入表中，其他可为空，客户端要做检查好友若为空则不显示在界面
	query.parse();										// 待解决
	temp4=query.execute(username);
	if(temp1.rows()&&temp2.rows())
		return true;
	else
		return false;
}

bool Operation::add_friend(string userName,string friendName){

	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<"select * from  friendTable where userName=%0q and friendName=%1q"; // 提示好友已在列表中
	query.parse();
	StoreQueryResult res1=query.store(userName,friendName);
	if(res1.num_rows())
		return false;
	else
	{
		query.reset();
		query<<"insert into friendTable values(%0q,%1q)";
		query.parse();
		SimpleResult res2=query.execute(userName,friendName);
		return true;
	} 

}

void Operation:: delete_friend(string userName,string friendName){
	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<"delete from friendTable where userName=%0q and friendName=%1q";
	query.parse();
	query.execute(userName,friendName);
}
Building Operation:: query_sence(string buildingID){		//建筑物

	Building building;
	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<"select *from buildingInformation where buildingID=%0q";
	query.parse();
	StoreQueryResult res=query.store(buildingID);
	building.setBuildingID(res[0]["buildingID"].c_str()); // 不用返回buildingID了吧，这个函数应该只需要返回 一个string！
	building.setIntroduction(res[0]["introduction"].c_str());
	return building;
}

string Operation:: query_loction(Location location){

	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<"select location from userLocation where senceID=%0q and userName=%1q";
	query.parse();
	StoreQueryResult res=query.store(location.getSenceID(),location.getUserName());
	
	if (res.size() == 0)
	{
		return "-84,50,-238";
	}

	return res[0]["location"].c_str();
}

bool Operation::log_off(Location location){

	if(new_sence(location))
		return true;		//如果是新场景，则执行了插入操作后 返回true；否则进行更新。
	else
	{
		Connection conn;
		conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
		conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//		conn.connect("3ddb","127.0.0.1", "root", "xwt");
		Query query=conn.query();
		query<<"update userLocation set location=%0q where senceID=%1q and userName=%2q";//选择新场景则 进行插入操作 建立初始信息
		query.parse();
		SimpleResult res=query.execute(location.getLocation(),location.getSenceID(),location.getUserName());
		query.reset(); 
		query<<"update userInformation set isOnLine='false' where userName=%0q";
		query.parse();
		query.execute(location.getUserName());
		if(res.rows())
		{
			return true;
		}
		else
			return false;
	}
}

//每当用户更新 location时，都要做插入操作，如果插入操作失败，在进行更新   （用来判断是否是 新场景）
bool Operation:: new_sence(Location location){

	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<"select * from userLocation where userName=%0q ";
	query.parse();
	StoreQueryResult res1=query.store(location.getUserName());
	if(res1.num_rows())
		return false;
	else
	{
		query.reset();
		query<<"insert into userLocation (senceID,userName,location) values(%0q,%1q,%2q)";
		query.parse();
		query.execute(location.getSenceID(),location.getUserName(),location.getLocation());
		return true;
	}
}

vector<string> Operation:: query_friends(string userName){


	std::vector<string> friend_list;
	Connection conn;
	conn.set_option( new mysqlpp::SetCharsetNameOption( "gbk" ) );
	conn.connect(databaseName.c_str(),databaseIP.c_str(),adminName.c_str(), password.c_str());
//	conn.connect("3ddb","127.0.0.1", "root", "xwt");
	Query query=conn.query();
	query<<"select friendName from friendTable where userName=%0q ";
	query.parse();
	StoreQueryResult res=query.store(userName);
	for(int i=0;i!=res.num_rows();i++)
		friend_list.push_back(res[i][0].c_str());
	return friend_list;
}

