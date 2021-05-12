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

	/* qstringתchar* */
	static char* qstringToChar(QString devip1);

	/*������Ϣ*/
	char* devip;						 //�豸IP
	char* user;							 //�û���
	char* password;						 //����
	int port;							 //�˿ں�

	/*���Բ���*/
	long userID;						 //�豸ID
	long IRealPlayHandle;				 //Ԥ���Ĵ��ھ��
	NET_DVR_PREVIEWINFO struPlayInfo;    //Ԥ�������ṹ��
	NET_DVR_DEVICEINFO_V30 DeviceInfoTmp;//�豸��Ϣ�ṹ�壨��Ϊ����ֵ��
};

#endif