#pragma once
#include <cstring>
struct Seats {
	int price = 0; //�۸�
	int cnt = 0; //Ʊ������
};

class FlightInfo {
private:
	Seats First, Second; //�ֱ����ͷ�Ȳա�����ա����ò�
	char No[10] = {}; //������
	char StartTime[10] = {}; //����ʱ��
	char ArriveTime[10] = {}; //����ʱ��
	char Date[20] = {}; //��������
	char Origin[20] = {}; //�����ص�
	char Destination[20] = {}; //����ص�
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
