#pragma once
#include <fstream>
#include <vector>
#include <string>

struct CityInfo {
	std::string City;
	int cnt = 0; //�����ں����г��ֵĴ���
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
	void EditCity(CityName, bool);//0��ʾ����й����ĺ���������
};
