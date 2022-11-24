
// MINI12306.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once
#include "FlightManager.h"
#include "CityManager.h"
#include "UsersManager.h"
#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CMINI12306App:
// 有关此类的实现，请参阅 MINI12306.cpp
//
class CMINI12306App : public CWinApp
{
public:
	CMINI12306App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMINI12306App theApp;
extern User CurrentUser;
extern FlightInfo CurrentFlight;
extern UsersManager UM;