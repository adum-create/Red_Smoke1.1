#include "Camera.h"



Camera::Camera()
{
	//初始化时播放句柄设置为100
	IRealPlayHandle = 100;
}


Camera::~Camera()
{
}

/* qstring转char* */
char * Camera::qstringToChar(QString a)
{
	char * b;
	QByteArray c;
	c = a.toLatin1();
	b = c.data();
	return b;
}
