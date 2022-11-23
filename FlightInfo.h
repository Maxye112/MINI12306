#pragma once
#include <cstring>
struct Seats {
	int price = 0; //价格
	int cnt = 0; //票的数量
};

class FlightInfo {
private:
	Seats First, Second; //分别代表头等舱、商务舱、经济舱
	char No[10] = {}; //航班编号
	char StartTime[10] = {}; //出发时间
	char ArriveTime[10] = {}; //到达时间
	char Date[20] = {}; //出发日期
	char Origin[20] = {}; //出发地点
	char Destination[20] = {}; //到达地点
public:
	FlightInfo(char* Num, char* Date) { 
		strcpy_s(No, Num); 
		strcpy_s(this->Date, Date);
	}
	FlightInfo() {}
	~FlightInfo() {}
	char* GetNum(void) { return No; }
	char* GetStartTime(void) { return StartTime; }
	char* GetArriveTime(void) { return ArriveTime; }
	char* GetDate(void) { return Date; }
	char* GetOrigin(void) { return Origin; }
	char* GetDestination(void) { return Destination; }
	Seats GetFirst(void) { return First; }
	Seats GetSecond(void) { return Second; }
	void SetFirstInfo(int c, int p) { 
		First.cnt = c, First.price = p; 
	}
	void SetSecondInfo(int c, int p) { 
		Second.cnt = c, Second.price = p; 
	}
	void SetOrigin(char* O) { strcpy_s(Origin, O); }
	void SetDestination(char* Dest) { strcpy_s(Destination, Dest); }
	void SetTime(char s[], char a[]) { 
		strcpy_s(StartTime, s); 
		strcpy_s(ArriveTime, a); 
	}
};
