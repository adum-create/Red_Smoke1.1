#include "Camera.h"



Camera::Camera()
{
	//��ʼ��ʱ���ž������Ϊ100
	IRealPlayHandle = 100;
}


Camera::~Camera()
{
}

/* qstringתchar* */
char * Camera::qstringToChar(QString a)
{
	char * b;
	QByteArray c;
	c = a.toLatin1();
	b = c.data();
	return b;
}
