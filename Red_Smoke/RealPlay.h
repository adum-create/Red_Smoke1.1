#pragma once
#ifndef REALPLAY_H
#define REALPLAY_H

#include <Windows.h>
#include "HCNetSDK.h"
#include <QDebug>
#include "ui_Red_Smoke.h"
class RealPlay
{
public:
	RealPlay();
	~RealPlay();

	/*‘§¿¿*/
	static long play(long userID, HWND hWnd, NET_DVR_PREVIEWINFO struPlayInfo);

	/*πÿ±’‘§¿¿*/
	static void closeplay(long IRealPlayHandle, long userID);

	/*ªÒ»°µ•÷°ÕºœÒ*/
	static void captureSinglePicture(long userID, long IChannel, QString FileNamePath);




};


#endif // REALPLAY_H
