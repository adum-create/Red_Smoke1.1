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

	/*初始化*/
	void init();


public slots:
	/*相机登录*/
	void login_C1();
	void login_C2();
	void login_C3();
	void login_C4();

	/*设置参数*/
	void setParameters();
	/*采集图片并处理数据*/
	void collectAndProcessed();

	/*相机登录过程中反馈错误*/
	void setErrorMessage();

	/*串口相关函数*/
	//获取所有可用的串口列表
	QStringList getPortNameList();
	//QString转16进制
	void convertStringToHex(const QString &str, QByteArray &byteData);
	char convertCharToHex(char ch);
	//向串口发送信息
	void sendInfo(const QString &info);
	//CRC校验
	uint16_t MB_CRC16_calculate(uint8_t * array, uint8_t index);
	//设置发送的报文帧
	void setSendMessage_test(int send_data);
	//打开串口
	void openPort();
	// 将16进制字符串转换为对应的字节序列
	QByteArray HexStringToByteArray(QString HexString);
	//设置数据
	void sendMyMessage_test();
	//接收到单片机发送的数据进行解析
	void receiveInfo();
	//串口初始化
	void initPort();


private:
	
	/*ui界面*/
    Ui::Red_SmokeClass *ui;

	/*4台相机*/
	Camera *camera_1;
	Camera *camera_2;
	Camera *camera_3;
	Camera *camera_4;

	/*图像处理参数*/
	double threshold1;  //差分阈值
	int threshold2;     //过滤阈值
	double a;           //黄色干扰消除因子
	double detect_time; //间隔采集时间
	int dif_time;       //连续采样时间
	int max_img_amount; //最大图片存在数量
	double threshold_of_warning_record;  //报警记录阈值

	/*报警记录表格参数*/
	int row = 0;

	/*图像相关参数*/
	int num_picture;	//捕获图像的序列号
	bool capture_img_deal_data;//开始保存和处理数据bool量
	QString filename;
	double red_value;
	QVector<QString> delete_img_array;//删除图片数组名

	/*计时器*/
	QTimer *mytimer;

	/*报警记录表格，帮助界面，四台相机显示界面*/
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

	/*串口相关*/
	QSerialPort* m_serialPort; //串口类
	QStringList m_portNameList;//串口名
	QByteArray info;   //接收单片机数据
	QByteArray test_refer;
	QByteArray frame;//发送的报文帧
};


#endif // WIDGET_H