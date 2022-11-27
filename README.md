# MINI12306

## 前言
这是一个大一萌新兼蒟蒻的大作业. 请使用Visual Studio 2022编译，且为了保证程序的正确运行，如果将编译的程序拷贝至其他位置运行，请将res文件夹与编译后的程序放在同一目录下。

## 内容说明：
*Manager.h/*Manager.cpp/User.cpp/FlightInfo.cpp 涉及数据库的读写

*DataBase.txt将在程序第一次运行后生成，这是程序所需的数据库

AddFlightDlg ——航班信息的添加和编辑共用的对话框

CbookedDlg ——乘客查看自己的订单，并决定退票的对话框

CEnsureInfo ——确认订票/退票的对话框

CFindFlightDlg ——查询航班的页面

CRechargeDlg ——充值的页面（后续可能会改造成个人中心）

CustomDraw* 和SkinColor——第三方库，用以重绘MFC控件

EditInfoDlg ——编辑账户信息的页面（乘客和管理员共用）

CResetDialog1 ——重置密码的页面（乘客和管理员共用）

pch ——预编译头文件（需要有它才可正确编译）

CPassenger——用户主页

ManagerDlg——管理员主页

MINI12306Dlg——登陆页面
