
#include "pch.h"
#include "FlightInfo.h"
#include <vector>
#include <fstream>
using std::vector;
using std::ios;
using std::fstream;
#include "FlightManager.h"
FlightManager::FlightManager()
{
	fstream f;
	f.open("FlightDataBase.txt", ios::in);
	unsigned int size = 0;
	f.read((char*)&size, sizeof(unsigned));
	if (size)
		for (int i = 0; i < size; ++i)
		{
			char Num[10], Ori[20], Dest[20], Date[20], ST[10], AT[10];
			f.read(Num, 10 * sizeof(char));
			f.read(Ori, 20 * sizeof(char));
			f.read(Dest, 20 * sizeof(char));
			f.read(Date, 20 * sizeof(char));
			f.read(ST, 10 * sizeof(char));
			f.read(AT, 10 * sizeof(char));
			int F1, F2, E1, E2, t;
			f.read((char*)&F1, sizeof(int));
			f.read((char*)&F2, sizeof(int));
			f.read((char*)&E1, sizeof(int));
			f.read((char*)&E2, sizeof(int));
			f.read((char*)&t, sizeof(int));
			bool sta = t;
			FlightInfo New(Num, Date);
			New.SetFirstInfo(F1, F2);
			New.SetSecondInfo(E1, E2);
			New.SetOrigin(Ori);
			New.SetDestination(Dest);
			New.SetTime(ST, AT);
			New.SetStatus(sta);
			FQ.push_back(New);
		}
	f.close();
}

FlightManager::~FlightManager()
{
	fstream f;
	f.open("FlightDataBase.txt", ios::out);
	unsigned int size = FQ.size();
	f.write((char*)&size, sizeof(unsigned));
	if (size)
		for (int i = 0; i < size; ++i)
		{
			FlightInfo tmp = FQ[i];
			f.write(tmp.GetNum(), 10 * sizeof(char));
			f.write(tmp.GetOrigin(), 20 * sizeof(char));
			f.write(tmp.GetDestination(), 20 * sizeof(char));
			f.write(tmp.GetDate(), 20 * sizeof(char));
			f.write(tmp.GetStartTime(), 10 * sizeof(char));
			f.write(tmp.GetArriveTime(), 10 * sizeof(char));
			Seats t1 = FQ[i].GetFirst();
			int t11 = t1.cnt, t12 = t1.price;
			f.write((char*)&t11, sizeof(int));
			f.write((char*)&t12, sizeof(int));
			Seats t3 = tmp.GetSecond();
			int t31 = t3.cnt, t32 = t3.price;
			f.write((char*)&t31, sizeof(int));
			f.write((char*)&t32, sizeof(int));
			int Status = tmp.GetStatus() ? 1 : 0;
			f.write((char*)&Status, sizeof(int));
		}
	f.close();
}

bool FlightManager::AddFlight(FlightInfo& t)
{
	unsigned size = FQ.size();
	for (int i = 0; i < size; ++i) {
		FlightInfo tmp = FQ[i];
		if (strcmp(tmp.GetNum(), t.GetNum()) == 0 && strcmp(tmp.GetDate(), t.GetDate()) == 0)
			return false;
	}
	FQ.push_back(t);
	return true;
}

bool FlightManager::DelFlight(char Num[], char Date[])
{
	unsigned size = FQ.size();
	if (size) {
		FlightQueue::iterator i;
		for (i = FQ.begin(); i != FQ.end(); ++i) {
			if (strcmp(i->GetNum(), Num) == 0 && strcmp(i->GetDate(), Date) == 0) {
				FQ.erase(i);
				return true;
			}
		}
	}
	return false;
}

bool FlightManager::EditFlight(char Num[], char Date[], const FlightInfo& t)
{
	FlightQueue::iterator i;
	for (i = FQ.begin(); i != FQ.end(); ++i)
		if (strcmp(i->GetNum(), Num) == 0 && strcmp(i->GetDate(), Date) == 0)
		{
			*i = t;
			return true;
		}
	return false;
}

bool FlightManager::SearchFlightByNum(char Num[], char Date[], FlightQueue& List)
{
	unsigned size = FQ.size();
	for (int i = 0; i < size; ++i)
	{
		FlightInfo tmp = FQ[i];
		if (tmp.GetStatus() == false)
			continue;
		if (strcmp(tmp.GetNum(), Num) == 0 && strcmp(tmp.GetDate(), Date) == 0)
			List.push_back(tmp);
	}
	if (List.size()) return true;
	else return false;
}

bool FlightManager::SearchFlightByPlace(char ST[], char DE[], char Date[], FlightQueue& List)
{
	unsigned size = FQ.size();
	for (int i = 0; i < size; ++i)
	{
		FlightInfo tmp = FQ[i];
		if (tmp.GetStatus() == false)
			continue;
		if (strcmp(tmp.GetOrigin(), ST) == 0 && strcmp(tmp.GetDestination(), DE) == 0 && strcmp(tmp.GetDate(), Date) == 0)
			List.push_back(tmp);
	}
	if (List.size()) return true;
	else return false;
}

FlightInfo FlightManager::FindFlight(FlightInfo& t) {
	unsigned size = FQ.size();
	FlightInfo tmp;
	for (int i = 0; i < size; ++i) {
		FlightInfo tmp = FQ[i];
		if (strcmp(tmp.GetNum(), t.GetNum()) == 0 && strcmp(tmp.GetDate(), t.GetDate()) == 0)
			return tmp;
	}
	return tmp;
}