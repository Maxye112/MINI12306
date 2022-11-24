#pragma once
#include <cstring>
#include <vector>
#include "FlightInfo.h"
using std::vector;

class User {
protected:
	char Name[20]; //姓名
	char TelNum[20]; //手机号码
	char Password[20]; //密码
	int isManager; //是否是管理员，1为是，0为否
	char IDNum[20];//身份证号
	int Money; //余额
public:
	vector <FlightInfo> BookedList;
	User() { Money = 0; }
	User(const User& t) {
		strcpy_s(Name, t.Name);
		strcpy_s(TelNum, t.TelNum);
		strcpy_s(Password, t.Password);
		strcpy_s(IDNum, t.IDNum);
		isManager = t.isManager;
		Money = t.Money;
		BookedList = t.BookedList;
	}
	User(char name[], char pw[], char Tel[], int iM, int Mon = 0) {
		strcpy_s(TelNum, Tel);
		strcpy_s(Name, name);
		strcpy_s(Password, pw);
		isManager = iM;
		Money = Mon;
	}
	char* GetTel() { return TelNum; }
	char* GetName() { return Name; }
	char* GetPassword() { return Password; }
	int GetUserType() { return isManager; }
	void SetName(char* name) { strcpy_s(Name, name); }
	void SetType(int tp) { isManager = tp; }
	void SetPassword(char* pw) { strcpy_s(Password, pw); }
	void SetTelNum(char* Tel) { strcpy_s(TelNum, Tel); }
	void SetID(char* id) { strcpy_s(IDNum, id); }
	void Recharge(int t) { Money += t; } //充值
	char* GetID(){ return IDNum; }
	int GetMoney() { return Money; }
	
};
