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
		char NewCity[20] = {};
		city.read(NewCity, 20 * sizeof(char));
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
		char* New = (char*)(i->c_str());
		city.write(New, 20 * sizeof(char));
	}
	city.close();
}

bool CityManager::AddCity(City New) {
	u size = CL.size();
	for (u i = 0; i < size; ++i) {
		if (CL[i] == New)
			return false;
	}
	CL.push_back(New);
	return true;
}

bool CityManager::DelCity(City s) {
	u size = CL.size();
	if (!size) return false;
	for (CityList::iterator i = CL.begin(); i != CL.end(); ++i)
		if (*i == s) {
			CL.erase(i);
			return true;
		}
	return false;
}