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
		User NewU(Name, Password, Tel, type, money);
		NewU.SetID(ID);
		if (n) 
			for (int j = 0; j < n; ++j) {
				char No[10], Date[20], Dest[20], Ori[20], ST[10], AT[20];
				f.read(No, 10 * sizeof(char));
				f.read(Date, 20 * sizeof(char));
				f.read(Ori, 20 * sizeof(char));
				f.read(Dest, 20 * sizeof(char));
				f.read(ST, 10 * sizeof(char));
				f.read(AT, 10 * sizeof(char));
				int Fc, Fp, Sc, Sp;
				f.read((char*)&Fc, sizeof(int));
				f.read((char*)&Fp, sizeof(int));
				f.read((char*)&Sc, sizeof(int));
				f.read((char*)&Sp, sizeof(int));
				FlightInfo New(No, Date);
				New.SetOrigin(Ori);
				New.SetDestination(Dest);
				New.SetTime(ST, AT);
				New.SetFirstInfo(Fc, Fp);
				New.SetSecondInfo(Sc, Sp);
				NewU.BookedList.push_back(New);
			}

		UserList.push_back(NewU);
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
				f.write(t.GetOrigin(), 20 * sizeof(char));
				f.write(t.GetDestination(), 20 * sizeof(char));
				f.write(t.GetStartTime(), 10 * sizeof(char));
				f.write(t.GetArriveTime(), 10 * sizeof(char));
				Seats t1 = t.GetFirst();
				int t11 = t1.cnt, t12 = t1.price;
				f.write((char*)&t11, sizeof(int));
				f.write((char*)&t12, sizeof(int));
				Seats t3 = t.GetSecond();
				int t31 = t3.cnt, t32 = t3.price;
				f.write((char*)&t31, sizeof(int));
				f.write((char*)&t32, sizeof(int));
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
			Dest.BookedList = tmp.BookedList;
			return true;
		}
	}
	return false;
}

void UsersManager::EditUserFlight(User& t, FlightInfo & r) {
	vector<User>::iterator it;
	for (it = UserList.begin(); it != UserList.end(); ++it) {
		if (strcmp(t.GetTel(), it->GetTel()) == 0)
			it->BookedList.push_back(r);
	}
}

void UsersManager::EditUser(User& t) {
	vector<User>::iterator it;
	for (it = UserList.begin(); it != UserList.end(); ++it) {
		if (strcmp(t.GetTel(), it->GetTel()) == 0)
			*it = t;
	}
}