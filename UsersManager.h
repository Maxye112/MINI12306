#pragma once
#include "User.h"
#include <fstream>
#include <vector>
using std::vector;
using std::ios;
using std::fstream;

class UsersManager {
private:
public:
	vector <User> UserList;
	UsersManager();
	UsersManager(const UsersManager&) = delete;
	~UsersManager();
	bool AddUser(char[], char[], char[], char*, unsigned);
	bool DelUser(char[]);
	bool ResetPassword(char[], char[]);
	bool ValidateUser(char[], char[], unsigned);
	bool FindUserByTel(char*, User&);
	void EditUserFlight(User&, FlightInfo&);
};

