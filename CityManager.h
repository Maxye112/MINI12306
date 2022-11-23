#pragma once
#include <fstream>
#include <vector>
#include <string>

typedef std::string City;
typedef std::vector<City> CityList;
typedef unsigned u;
class CityManager {
private:

public:
	CityList CL;
	CityManager();
	~CityManager();
	bool AddCity(City);
	bool DelCity(City);
};
