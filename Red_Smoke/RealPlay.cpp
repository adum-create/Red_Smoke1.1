#include "RealPlay.h"
#define cout qDebug() << "[" << __FILE__ << ":"<< __LINE__ <<"]"


RealPlay::RealPlay()
{
}


RealPlay::~RealPlay()
{
}

/*预览*/
long RealPlay::play(long userID, HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo)
{
	struPlayInfo = { 0 };
	struPlayInfo.hPlayWnd = hWnd;	//需要 SDK 解码时句柄设为有效值，仅取流不解码时可设为空
	struPlayInfo.lChannel = 1;		//预览通道号
	struPlayInfo.dwStreamType = 0;	//码流类型：0-主码流，1-子码流，2-三码流，3-虚拟码流，以此类推
	struPlayInfo.dwLinkMode = 0;	//0- TCP 方式，1- UDP 方式，2- 多播方式，3- RTP 方式，4-RTP/RTSP，5-RSTP/HTTP
	struPlayInfo.bBlocked = 1;		//0- 非阻塞取流，1- 阻塞取流

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

/*关闭预览*/
void RealPlay::closeplay(long IRealPlayHandle, long userID)
{
	
	//关闭预览
	NET_DVR_StopRealPlay(IRealPlayHandle);

	//注销用户
	NET_DVR_Logout(userID);
	//释放SDK 资源
	//NET_DVR_Cleanup();

}

/*获取单帧图像*/
void RealPlay::captureSinglePicture(long userID, long IChannel, QString FileNamePath)
{
	//文件夹路径字符转换
	QByteArray file_name_path1;
	char * file_name_path2;
	file_name_path1 = FileNamePath.toLatin1();
	file_name_path2 = file_name_path1.data();

	//设置像素大小
	LPNET_DVR_JPEGPARA pixel;
	pixel->wPicQuality = 1;
	pixel->wPicSize = 19;

	//捕获单张图像
	bool isok = NET_DVR_CaptureJPEGPicture(userID, IChannel, pixel, file_name_path2);
	qDebug() << "NET_DVR_CaptureJPEGPicture erro" << NET_DVR_GetLastError();
}

