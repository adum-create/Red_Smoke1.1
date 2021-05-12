#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include<QString>
#include"HCNetSDK.h"



class Camera
{
public:
	Camera();
	~Camera();

	/* qstring转char* */
	static char* qstringToChar(QString devip1);

	/*基础信息*/
	char* devip;						 //设备IP
	char* user;							 //用户名
	char* password;						 //密码
	int port;							 //端口号

	/*属性参数*/
	long userID;						 //设备ID
	long IRealPlayHandle;				 //预览的窗口句柄
	NET_DVR_PREVIEWINFO struPlayInfo;    //预览参数结构体
	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;//设备信息结构体（作为返回值）
};

#endif