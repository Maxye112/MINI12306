#include "pch.h"
#include "User.h"
#include <fstream>
#include <vector>
using std::vector;
using std::ios;
using std::fstream;

#include "UsersManager.h"
UsersManager::UsersManager() {
	fstream f;
	f.open("UserDataBase.txt", ios::in | ios::binary);
	unsigned total = 0;
	f.read((char*)&total, sizeof(unsigned));
	for (unsigned i = 0; i < total; ++i) {
		char Name[20], Password[20], Tel[20], ID[20];
		f.read(Name, 20 * sizeof(char));
		f.read(Tel, 20 * sizeof(char));
		f.read(Password, 20 * sizeof(char));
		unsigned type, money;
		f.read((char*)&type, sizeof(unsigned));
		f.read(ID, 20 * sizeof(char));
		f.read((char*)&money, sizeof(money));
		unsigned n = 0;
		f.read((char*)&n, sizeof(unsigned));
		User New(Name, Password, Tel, type, money);
		UserList.push_back(New);
	}
	f.close();
}

UsersManager::~UsersManager() {
	fstream f;
	f.open("UserDataBase.txt", ios::out | ios::binary);
	unsigned size = UserList.size();
	f.write((char*)&size, sizeof(unsigned));
	for (unsigned i = 0; i < size; ++i) {
		User tmp = UserList[i];
		f.write(tmp.GetName(), 20 * sizeof(char));
		f.write(tmp.GetTel(), 20 * sizeof(char));
		f.write(tmp.GetPassword(), 20 * sizeof(char));
		unsigned type = tmp.GetUserType(), money = tmp.GetMoney();
		f.write((char*)&type, sizeof(unsigned));
		f.write(tmp.GetID(), 20 * sizeof(char));
		f.write((char*)&money, sizeof(unsigned));
		unsigned total = tmp.BookedList.size();
		f.write((char*)&total, sizeof(unsigned));
		if (total) {
			for (unsigned j = 0; j < total; ++j) {
				FlightInfo t = tmp.BookedList[j];
				char* No = t.GetNum();
				char* Date = t.GetDate();
				f.write(No, 10 * sizeof(char));
				f.write(Date, 20 * sizeof(char));
			}
		}
	}
	f.close();
}

bool UsersManager::AddUser(char Name[], char Password[], char Tel[], char *ID, unsigned type) {
	unsigned size = UserList.size();
	for (unsigned i = 0; i < size; ++i) {
		User tmp = UserList[i];
		if (strcmp(Tel, tmp.GetTel()) == 0)
			return false;
	}
	User New(Name, Password, Tel, type);
	New.SetID(ID);
	UserList.push_back(New);
	return true;
}

bool UsersManager::DelUser(char Tel[]) {
	vector <User>::iterator it;
	for (it = UserList.begin(); it != UserList.end(); ++it)
		if (strcmp(Tel, it->GetTel()) == 0) {
			UserList.erase(it);
			return true;
		}
	return false;
}

bool UsersManager::ResetPassword(char Tel[], char pw[]) {
	vector<User>::iterator it;
	for (it = UserList.begin(); it != UserList.end(); ++it)
		if (strcmp(Tel, it->GetTel()) == 0) {
			it->SetPassword(pw);
			return true;
		}
	return false; //输出未找到用户信息
}

bool UsersManager::ValidateUser(char Tel[], char Password[], unsigned type) {
	unsigned size = UserList.size();
	for (unsigned i = 0; i < size; ++i) {
		User tmp = UserList[i];
		if ((strcmp(Tel, tmp.GetTel()) == 0) && (strcmp(Password, tmp.GetPassword()) == 0) && (type == tmp.GetUserType()))
			return true;
	}
	return false;
}

bool UsersManager::FindUserByTel(char* Tel, User& Dest) {
	unsigned size = UserList.size();
	for (unsigned i = 0; i < size; ++i) {
		User tmp = UserList[i];
		if ((strcmp(Tel, tmp.GetTel()) == 0)) {
			Dest = tmp;
			return true;
		}
	}
	return false;
}