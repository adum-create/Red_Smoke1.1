#pragma once
#ifndef Red_Smoke_H
#define Red_Smoke_H
#include <QtWidgets/QMainWindow>
#include<opencv/opencv2/core/core.hpp>
#include<opencv/opencv2/highgui/highgui.hpp>
#include<opencv/opencv2/imgproc/imgproc.hpp>
#include "HCNetSDK.h"
#include <Windows.h>
#include <QWidget>
#include<QMainWindow>
#include "HCNetSDK.h"
#include "realplay.h"
#include<QFileDialog>
#include <QTimer>
#include<QDateTime>
#include"SmokeRecongnize.h"
#include"redanalyze.h"
#include"camera.h"
#include<iostream>
#include <QtMath>
#include<QtXLSX/xlsxdocument.h>
#include<QtXLSX/xlsxformat.h>
#include<QtXLSX/xlsxcellrange.h>
#include<QtXLSX/xlsxchart.h>
#include"FileManage.h"
#include<QMenu>
#include<QMenuBar>
#include<QToolBar>
#include<QList>
#include<QStatusBar>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QComboBox>
#include<QByteArray>
#include<QMdiArea>
#include<QVector>
#include<QTableWidgetItem>
#include<QTableWidget>

#include"VideoWidget.h"
#include"GraphOfRedValue.h"
#include"ImageWidget.h"
#include"TableWidget.h"
#include"BeginWidget.h"
#include"FourWidget.h"

#include "ui_Red_Smoke.h"

namespace Ui { class Red_Smoke; };

class Red_Smoke : public QMainWindow
{
    Q_OBJECT

public:
	Red_Smoke(QWidget *parent = Q_NULLPTR);
	~Red_Smoke();

	/*��ʼ��*/
	void init();


public slots:
	/*�����¼*/
	void login_C1();
	void login_C2();
	void login_C3();
	void login_C4();

	/*���ò���*/
	void setParameters();
	/*�ɼ�ͼƬ����������*/
	void collectAndProcessed();

	/*�����¼�����з�������*/
	void setErrorMessage();

	/*������غ���*/
	//��ȡ���п��õĴ����б�
	QStringList getPortNameList();
	//QStringת16����
	void convertStringToHex(const QString &str, QByteArray &byteData);
	char convertCharToHex(char ch);
	//�򴮿ڷ�����Ϣ
	void sendInfo(const QString &info);
	//CRCУ��
	uint16_t MB_CRC16_calculate(uint8_t * array, uint8_t index);
	//���÷��͵ı���֡
	void setSendMessage_test(int send_data);
	//�򿪴���
	void openPort();
	// ��16�����ַ���ת��Ϊ��Ӧ���ֽ�����
	QByteArray HexStringToByteArray(QString HexString);
	//��������
	void sendMyMessage_test();
	//���յ���Ƭ�����͵����ݽ��н���
	void receiveInfo();
	//���ڳ�ʼ��
	void initPort();


private:
	
	/*ui����*/
    Ui::Red_SmokeClass *ui;

	/*4̨���*/
	Camera *camera_1;
	Camera *camera_2;
	Camera *camera_3;
	Camera *camera_4;

	/*ͼ�������*/
	double threshold1;  //�����ֵ
	int threshold2;     //������ֵ
	double a;           //��ɫ������������
	double detect_time; //����ɼ�ʱ��
	int dif_time;       //��������ʱ��
	int max_img_amount; //���ͼƬ��������
	double threshold_of_warning_record;  //������¼��ֵ

	/*������¼������*/
	int row = 0;

	/*ͼ����ز���*/
	int num_picture;	//����ͼ������к�
	bool capture_img_deal_data;//��ʼ����ʹ�������bool��
	QString filename;
	double red_value;
	QVector<QString> delete_img_array;//ɾ��ͼƬ������

	/*��ʱ��*/
	QTimer *mytimer;

	/*������¼��񣬰������棬��̨�����ʾ����*/
	TableWidget *subwindow_of_table;
	BeginWidget *subwindow_of_help;
	VideoWidget *subwindow_of_video;
	GraphOfRedValue *subwindow_of_Graph;
	QMdiSubWindow *subwindow_of_table_name;
	QMdiSubWindow *subwindow_of_curve_name;
	QList<QMdiSubWindow*> test;
	bool open_table = true;
	bool open_curve = true;
	bool process = true;

	/*�������*/
	QSerialPort* m_serialPort; //������
	QStringList m_portNameList;//������
	QByteArray info;   //���յ�Ƭ������
	QByteArray test_refer;
	QByteArray frame;//���͵ı���֡
};


#endif // WIDGET_H