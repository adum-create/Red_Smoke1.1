#include "RealPlay.h"
#define cout qDebug() << "[" << __FILE__ << ":"<< __LINE__ <<"]"


RealPlay::RealPlay()
{
}


RealPlay::~RealPlay()
{
}

/*Ԥ��*/
long RealPlay::play(long userID, HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo)
{
	struPlayInfo = { 0 };
	struPlayInfo.hPlayWnd = hWnd;	//��Ҫ SDK ����ʱ�����Ϊ��Чֵ����ȡ��������ʱ����Ϊ��
	struPlayInfo.lChannel = 1;		//Ԥ��ͨ����
	struPlayInfo.dwStreamType = 0;	//�������ͣ�0-��������1-��������2-��������3-�����������Դ�����
	struPlayInfo.dwLinkMode = 0;	//0- TCP ��ʽ��1- UDP ��ʽ��2- �ಥ��ʽ��3- RTP ��ʽ��4-RTP/RTSP��5-RSTP/HTTP
	struPlayInfo.bBlocked = 1;		//0- ������ȡ����1- ����ȡ��

	long IRealPlayHandle = NET_DVR_RealPlay_V40(userID, &struPlayInfo, NULL, NULL);

	if (IRealPlayHandle <0)
	{
		cout << "NET_DVR_RealPlay_V40 error;error number " << NET_DVR_GetLastError();
		NET_DVR_Logout(userID);
		return 0;
	}
	else
	return IRealPlayHandle;
}

/*�ر�Ԥ��*/
void RealPlay::closeplay(long IRealPlayHandle, long userID)
{
	
	//�ر�Ԥ��
	NET_DVR_StopRealPlay(IRealPlayHandle);

	//ע���û�
	NET_DVR_Logout(userID);
	//�ͷ�SDK ��Դ
	//NET_DVR_Cleanup();

}

/*��ȡ��֡ͼ��*/
void RealPlay::captureSinglePicture(long userID, long IChannel, QString FileNamePath)
{
	//�ļ���·���ַ�ת��
	QByteArray file_name_path1;
	char * file_name_path2;
	file_name_path1 = FileNamePath.toLatin1();
	file_name_path2 = file_name_path1.data();

	//�������ش�С
	LPNET_DVR_JPEGPARA pixel;
	pixel->wPicQuality = 1;
	pixel->wPicSize = 19;

	//������ͼ��
	bool isok = NET_DVR_CaptureJPEGPicture(userID, IChannel, pixel, file_name_path2);
	qDebug() << "NET_DVR_CaptureJPEGPicture erro" << NET_DVR_GetLastError();
}

