#pragma once
#include "FlightInfo.h"
#include <vector>
#include <fstream>
using std::vector;
using std::ios;
using std::fstream;
typedef vector<FlightInfo> FlightQueue;

class FlightManager 
{
public:
	FlightQueue FQ;
	FlightManager();
	~FlightManager();
	FlightManager(const FlightManager&) = delete;
	bool AddFlight(FlightInfo&);
	bool DelFlight(char[], char[]);
	bool EditFlight(char[], char[], const FlightInfo&);
	bool SearchFlightByPlace(char[], char[], char[], FlightQueue&);
	bool SearchFlightByNum(char[], char[], FlightQueue&);
};

