#pragma once
#include <fstream>
#include <vector>
#include <string>

struct CityInfo {
	std::string City;
	int cnt = 0; //城市在航班中出现的次数
};
typedef std::string CityName;
typedef std::vector<CityInfo> CityList;
typedef unsigned u;
class CityManager {
private:

public:
	CityList CL;
	CityManager();
	~CityManager();
	bool AddCity(CityName);
	bool DelCity(CityName);
	void EditCity(CityName, bool);//0表示与城市关联的航班增加了
};
