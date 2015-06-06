drop database 3Ddb;

create database 3Ddb;
use 3Ddb;

create table userTable(
	userName varchar(12) BINARY NOT NULL,
	password varchar(10)  BINARY NOT NULL,
	primary key (userName)
);
insert into userTable(userName,password) values('111','111');
insert into userTable(userName,password) values('222','222');
insert into userTable(userName,password) values('333','333');
insert into userTable(userName,password) values('444','444');
create table userInformation(
	 userName varchar(20) binary not NULL ,
	 password varchar(20) binary,
	 realName varchar(12) binary,
	 sex varchar(10) binary,
	 age varchar(10) binary,
	 isOnLine varchar(50) binary,
	 education varchar(20) binary,
	 profession varchar(20) binary,
	 myPhoneNum varchar(20) binary,
	 email varchar(30) binary,
	 hobby varchar(50) binary,
	 selfInfo varchar(100) binary,
	 
	 nickName varchar(12) binary,
	 signature varchar(200) binary,
	 address varchar(50) binary,
	 primary key (userName)
);
insert into userInformation(userName,realName,sex,age,isOnLine ,education,profession,myPhoneNum,email,hobby,selfInfo,nickName,signature,address)
values('111','fanghui','male','20','chengdu','College Student','Sofware Engineer','18782975540','qq.com','reading','Hello','nickname','signature','address');
insert into userInformation(userName,sex)values('222','male');
insert into userInformation(userName,sex)values('333','male');
insert into userInformation(userName,sex)values('444','male');

create table friendTable(userName varchar(12) binary not NULL,friendName varchar(12) binary not NULL,
primary key(userName,friendName)
);

insert into friendTable values('111','222');
insert into friendTable values('111','333');
insert into friendTable values('111','444');
insert into friendTable values('222','111');
insert into friendTable values('444','222');

create table buildingInformation (buildingID varchar(20) binary not NULL ,introduction varchar(200),primary key (buildingID));
insert into buildingInformation values('library','222');
insert into buildingInformation values('classroom','222');
insert into buildingInformation values('restaurant','222');
insert into buildingInformation values('laboratory','222');

create table userLocation(senceID varchar(30) binary not NULL,userName varchar(12 ) binary not NULL,
	location varchar(30) not NULL ,primary key (userName)
);
insert into userLocation (senceID,userName,location) values ('Sichuan University','111','room');
insert into userLocation (senceID,userName,location) values ('Sichuan University','222','room');

create table Comment(
buildingID varchar(20) BINARY  NOT NULL,
content varchar(200) ,
userName varchar(12),
commentTime datetime
);
insert into Comment (buildingID,content,userName,commentTime) values ('27','test1','111','2013-01-01');
insert into Comment (buildingID,content,userName,commentTime) values ('27','test2','111','2013-01-02');
insert into Comment (buildingID,content,userName,commentTime) values ('28','test1','222','2013-01-01');
insert into Comment (buildingID,content,userName,commentTime) values ('28','test2','222','2013-01-02');
insert into Comment (buildingID,content,userName,commentTime) values ('29','test1','333','2013-01-01');
insert into Comment (buildingID,content,userName,commentTime) values ('29','test2','333','2013-01-02');

