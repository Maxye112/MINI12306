#include "pch.h"
#include "CityManager.h"
#include <fstream>
#include <vector>
#include <string>

CityManager::CityManager() {
	std::fstream city;
	city.open("CityDataBase.txt", std::ios::in);
	u size = 0;
	city.read((char*)&size, sizeof(u));
	for (u i = 0; i < size; ++i) {
		char NewCityName[20] = {};
		city.read(NewCityName, 20 * sizeof(char));
		int cnt;
		city.read((char*)&cnt, sizeof(int));
		CityInfo NewCity = {NewCityName, cnt};
		CL.push_back(NewCity);
	}
	city.close();
}

CityManager::~CityManager() {
	std::fstream city;
	u size = CL.size();
	city.open("CityDataBase.txt", std::ios::out);
	city.write((char*)&size, sizeof(u));
	for (CityList::iterator i = CL.begin(); i != CL.end(); ++i) {
		char* New = (char*)(i->City.c_str());
		city.write(New, 20 * sizeof(char));
		int cnt = i->cnt;
		city.write((char*)&cnt, sizeof(int));
	}
	city.close();
}

bool CityManager::AddCity(CityName New) {
	u size = CL.size();
	for (u i = 0; i < size; ++i) {
		if (CL[i].City == New)
			return false;
	}
	CL.push_back({ New, 0 });
	return true;
}

bool CityManager::DelCity(CityName s) {
	u size = CL.size();
	if (!size) return false;
	for (CityList::iterator i = CL.begin(); i != CL.end(); ++i) {
		CityInfo tmp = *i;
		if (tmp.City == s)
			if (tmp.cnt == 0) {
				CL.erase(i);
				return true;
			}
			else return false;
	}
	return false;
}

void CityManager::EditCity(CityName s, bool ope) {
	u size = CL.size();
	if (!size) return;
	for (u i = 0; i < size; ++i) {
		CityInfo &tmp = CL[i];
		if (tmp.City == s)
			!ope?tmp.cnt++:tmp.cnt--;
	}
	return;
}