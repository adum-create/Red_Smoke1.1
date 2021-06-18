#include "Red_Smoke.h"
#pragma execution_character_set("utf-8")
/*
2021.05.10
添加软件图标
析构函数优化
同时预览4个画面
其实也没有改什么
2021.06.10
解决ui大小适应问题
添加烟雾图像保存
.exe图标制作
*/



/*Red_Smoke构造函数*/
Red_Smoke::Red_Smoke(QWidget *parent)
    : QMainWindow(parent)
{
	/*相机初始化*/
	camera_1 = new Camera();
	camera_2 = new Camera();
	camera_3 = new Camera();
	camera_4 = new Camera();
	debug = false;
	day = 1;

	/*界面初始化*/
	ui = new Ui::Red_SmokeClass();
    ui->setupUi(this);
	ui->mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); //将工具栏标题放在图标下面
	//报警记录表初始化
	subwindow_of_table = new TableWidget();
	subwindow_of_table->setWindowTitle(tr("历史报警记录"));
	//开始界面初始化
	subwindow_of_help = new BeginWidget();
	subwindow_of_help->setWindowTitle(tr("系统简介"));
	ui->mdiArea->addSubWindow(subwindow_of_help);
	subwindow_of_help->show();
	QMdiSubWindow *subwindow_of_init_name = ui->mdiArea->activeSubWindow();

	//四个相机显示界面初始化
	subwindow_of_video = new VideoWidget();
	subwindow_of_video->setWindowTitle(tr("预览"));
	//串口初始化
	initPort();
	//默认核心窗口为tab模式
	ui->mdiArea->setViewMode(QMdiArea::TabbedView);
	ui->mdiArea->setTabsClosable(false); //页面可关闭
	ui->mdiArea->setTabsMovable(true);
	//设置软件图标
	this->setWindowIcon(QPixmap(":/img/img/smoke.png"));

	/*工具栏槽函数*/
	//相机部分
	connect(ui->action_manage_of_camera1, &QAction::triggered, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->page_camera1);
	});
	connect(ui->action_manage_of_camera2, &QAction::triggered, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->page_camera2);
	});
	connect(ui->action_manage_of_camera3, &QAction::triggered, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->page_camera3);
	});
	connect(ui->action_manage_of_camera4, &QAction::triggered, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->page_camera4);
	});
	//中心窗口设置子窗口模式
	connect(ui->action_subWindow, &QAction::triggered, [=]() {
		ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
	});
	//中心窗口设置tab模式
	connect(ui->action_tabWindow, &QAction::triggered, [=]() {
		ui->mdiArea->setViewMode(QMdiArea::TabbedView);
		ui->mdiArea->setTabsClosable(false); //页面可关闭
		ui->mdiArea->setTabsMovable(true);
	});
	//参数设置
	connect(ui->action_of_set_parameters, &QAction::triggered, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->page_setParameters);
	});
	//历史报警回溯
	connect(ui->action_warning_table, &QAction::triggered, [=]() {

		//测试
		test = ui->mdiArea->subWindowList();
		for (int i = 0; i < test.size(); i++)
		{
			if (test[i] == subwindow_of_table_name)
			{
				ui->mdiArea->setActiveSubWindow(subwindow_of_table_name);
				open_table = false;
			}
		}
		if (open_table)
		{
			ui->mdiArea->addSubWindow(subwindow_of_table);
			subwindow_of_table->show();
			subwindow_of_table_name = ui->mdiArea->activeSubWindow();
		}
	});
	//串口
	connect(ui->action_of_serialport_set, &QAction::triggered, [=]() {
		ui->stackedWidget->setCurrentWidget(ui->page_setPort);
	});
	//帮助
	connect(ui->action_of_begin, &QAction::triggered, [=]() {
		ui->mdiArea->setActiveSubWindow(test[0]);
	});



	/*相机1登录、预览、关闭预览*/
	//登录
	connect(ui->pushButton_login_1, &QPushButton::clicked, this, &Red_Smoke::login_C1);
	//预览
	connect(ui->pushButton_display_1, &QPushButton::clicked, [=]() {
		ui->mdiArea->addSubWindow(subwindow_of_video);
		subwindow_of_video->setVideo_1(camera_1);
		subwindow_of_video->setWindowIcon(QPixmap(":/img/img/display.png"));
		subwindow_of_video->show();
	});
	//关闭预览
	connect(ui->pushButton_close_1, &QPushButton::clicked, [=]() {
		RealPlay::closeplay(camera_1->IRealPlayHandle, camera_1->userID);
	});

	/*相机2登录、预览、关闭预览*/
	//登录
	connect(ui->pushButton_login_2, &QPushButton::clicked, this, &Red_Smoke::login_C2);
	//预览
	connect(ui->pushButton_display_2, &QPushButton::clicked, [=]() {
		subwindow_of_video->setVideo_2(camera_2);
	});
	//关闭预览
	connect(ui->pushButton_close_2, &QPushButton::clicked, [=]() {
		RealPlay::closeplay(camera_2->IRealPlayHandle, camera_2->userID);
	});

	/*相机3登录、预览、关闭预览*/
	//登录
	connect(ui->pushButton_login_3, &QPushButton::clicked, this, &Red_Smoke::login_C3);
	//预览
	connect(ui->pushButton_display_3, &QPushButton::clicked, [=]() {
		subwindow_of_video->setVideo_3(camera_3);
	});
	//关闭预览
	connect(ui->pushButton_close_3, &QPushButton::clicked, [=]() {
		RealPlay::closeplay(camera_3->IRealPlayHandle, camera_3->userID);
	});

	/*相机4登录、预览、关闭预览*/
	//登录
	connect(ui->pushButton_login_4, &QPushButton::clicked, this, &Red_Smoke::login_C4);
	//预览
	connect(ui->pushButton_display_4, &QPushButton::clicked, [=]() {
		subwindow_of_video->setVideo_4(camera_4);
	});
	//关闭预览
	connect(ui->pushButton_close_4, &QPushButton::clicked, [=]() {
		RealPlay::closeplay(camera_4->IRealPlayHandle, camera_4->userID);
	});


	/*设置图片保存路径*/
	connect(ui->pushButton_SaveFilePath, &QPushButton::clicked, [=]() {
		filename = QFileDialog::getExistingDirectory(this, tr("save path"), "D:");
		ui->lineEdit_save_path->setText(filename);//显示保存的文件夹路径
	});

	/*设置参数和数据处理*/
	connect(ui->pushButton_ensure_parameters, &QPushButton::clicked, this, &Red_Smoke::setParameters);
	//connect(ui->pushButton_ensure_parameters, &QPushButton::clicked, this, &Red_Smoke::collectAndProcessed);

	/*调试*/
	connect(ui->pushButton_begin_debug, &QPushButton::clicked, [=]() {
		debug = true;
	});
	connect(ui->pushButton_stop_debug, &QPushButton::clicked, [=]() {
		debug = false;
	});

	/*实验数据处理*/
	////第一次图像显示测试
	//Mat test = imread("E:/test1/Camera1_20210507_10_36_3_main.bmp");
	//ImageWidget *imagewidget = new ImageWidget();
	//ui->mdiArea->addSubWindow(imagewidget);
	//imagewidget->show();
	//QString ab = "xixi";
	//imagewidget->setImage(test, tr("哈哈"));
	//Mat a = imread("E:/test2/Camera1_20210508_19_18_3_refer.bmp");
	//RedAnalyze::redAnalyze2(a, 20);

}

/*Red_Smoke析构函数*/
Red_Smoke::~Red_Smoke()
{
	//关闭串口
	if (m_serialPort->isOpen())
	{
		m_serialPort->close();
	}
	delete m_serialPort;
	//释放相机sdk
	NET_DVR_Cleanup();
	//ui删除
	delete ui;
}

/*初始化*/
void Red_Smoke::init()
{
	bool isok = NET_DVR_Init();
	if (isok == false)
	{
		return;
	}

	//设置连接时间与重连时间
	NET_DVR_SetConnectTime(2000, 1);
	NET_DVR_SetReconnect(10000, true);
}

/*相机1登录*/
void Red_Smoke::login_C1()
{
	//初始化
	init();
	//获取QString
	QString IP1 = ui->lineEdit_IP_1->text();
	QString name1 = ui->lineEdit_name_1->text();
	QString password1 = ui->lineEdit_password_1->text();
	QString port1 = ui->lineEdit_port_1->text();

	//QString转化为QByteArray
	QByteArray IP1_tmp = IP1.toLatin1();
	QByteArray name1_tmp = name1.toLatin1();
	QByteArray password1_tmp = password1.toLatin1();

	//QString转化为char*
	camera_1->devip = IP1_tmp.data();
	camera_1->user = name1_tmp.data();
	camera_1->password = password1_tmp.data();
	camera_1->port = port1.toInt();
	//登录
	camera_1->userID = NET_DVR_Login_V30(camera_1->devip, camera_1->port, camera_1->user, camera_1->password, &camera_1->DeviceInfoTmp);//用户ID具有唯一性，后续对设备的操作都需要通过此ID实现

	//相机登录情况反馈
	if (camera_1->userID==-1)
	{
		setErrorMessage();
	}
	else
	{
		ui->label_of_info->setText(tr("相机1登录成功"));
	}
}

/*相机2登录*/
void Red_Smoke::login_C2()
{
	//初始化
	init();
	//获取QString
	QString IP2 = ui->lineEdit_IP_2->text();
	QString name2 = ui->lineEdit_name_2->text();
	QString password2 = ui->lineEdit_password_2->text();
	QString port2 = ui->lineEdit_port_2->text();

	//QString转化为QByteArray
	QByteArray IP2_tmp = IP2.toLatin1();
	QByteArray name2_tmp = name2.toLatin1();
	QByteArray password2_tmp = password2.toLatin1();

	//QString转化为char*
	camera_2->devip = IP2_tmp.data();
	camera_2->user = name2_tmp.data();
	camera_2->password = password2_tmp.data();
	camera_2->port = port2.toInt();
	//登录
	camera_2->userID = NET_DVR_Login_V30(camera_2->devip, camera_2->port, camera_2->user, camera_2->password, &camera_2->DeviceInfoTmp);//用户ID具有唯一性，后续对设备的操作都需要通过此ID实现

	//相机登录情况反馈
	if (camera_2->userID==-1)
	{
		setErrorMessage();
	}
	else
	{
		ui->label_of_info->setText(tr("相机2登录成功"));
	}
}

/*相机3登录*/
void Red_Smoke::login_C3()
{
	//初始化
	init();
	//获取QString
	QString IP3 = ui->lineEdit_IP_3->text();
	QString name3 = ui->lineEdit_name_3->text();
	QString password3 = ui->lineEdit_password_3->text();
	QString port3 = ui->lineEdit_port_3->text();

	//QString转化为QByteArray
	QByteArray IP3_tmp = IP3.toLatin1();
	QByteArray name3_tmp = name3.toLatin1();
	QByteArray password3_tmp = password3.toLatin1();

	//QString转化为char*
	camera_3->devip = IP3_tmp.data();
	camera_3->user = name3_tmp.data();
	camera_3->password = password3_tmp.data();
	camera_3->port = port3.toInt();
	//登录
	camera_3->userID = NET_DVR_Login_V30(camera_3->devip, camera_3->port, camera_3->user, camera_3->password, &camera_3->DeviceInfoTmp);//用户ID具有唯一性，后续对设备的操作都需要通过此ID实现

	//相机登录情况反馈
	if (camera_3->userID == -1)
	{
		setErrorMessage();
	}
	else
	{
		ui->label_of_info->setText(tr("相机3登录成功"));
	}
}

/*相机4登录*/
void Red_Smoke::login_C4()
{
	//初始化
	init();
	//获取QString
	QString IP4 = ui->lineEdit_IP_4->text();
	QString name4 = ui->lineEdit_name_4->text();
	QString password4 = ui->lineEdit_password_4->text();
	QString port4 = ui->lineEdit_port_4->text();

	//QString转化为QByteArray
	QByteArray IP4_tmp = IP4.toLatin1();
	QByteArray name4_tmp = name4.toLatin1();
	QByteArray password4_tmp = password4.toLatin1();

	//QString转化为char*
	camera_4->devip = IP4_tmp.data();
	camera_4->user = name4_tmp.data();
	camera_4->password = password4_tmp.data();
	camera_4->port = port4.toInt();
	//登录
	camera_4->userID = NET_DVR_Login_V30(camera_4->devip, camera_4->port, camera_4->user, camera_4->password, &camera_4->DeviceInfoTmp);//用户ID具有唯一性，后续对设备的操作都需要通过此ID实现

	//相机登录情况反馈
	if (camera_4->userID == -1)
	{
		setErrorMessage();
	}
	else
	{
		ui->label_of_info->setText(tr("相机4登录成功"));
	}
}

/*设置参数*/
void Red_Smoke::setParameters()
{

	//定时采集参数分钟（刷新时间）
	QString detect_time_qstring = ui->lineEdit_detect_time->text();
	detect_time = detect_time_qstring.toDouble();
	detect_time = detect_time * 60 * 1000;

	//差分阈值
	QString lineEdit_dif_threshold_qstring = ui->lineEdit_dif_threshold->text();
	threshold1 = lineEdit_dif_threshold_qstring.toDouble();

	//过滤阈值
	QString lineEdit_filter_threshold_qstring = ui->lineEdit_filter_threshold->text();
	threshold2 = lineEdit_filter_threshold_qstring.toInt();

	//消除因子
	QString lineEdit_elimination_factor_qstring = ui->lineEdit_elimination_factor->text();
	a = lineEdit_elimination_factor_qstring.toDouble();

	//连续图片间隔时间
	QString lineEdit_dif_time = ui->lineEdit_dif_time->text();
	dif_time = lineEdit_dif_time.toInt();

	//最大图片数量
	QString lineEdit_max_img_amount = ui->lineEdit_amount_max_img->text();
	max_img_amount = lineEdit_max_img_amount.toInt();

	//报警记录阈值
	QString lineEdit_warning_record = ui->lineEdit_threshold_of_warning_record->text();
	threshold_of_warning_record = lineEdit_warning_record.toDouble();

	/*采集图片并处理数据*/
	if (process)
	{
		collectAndProcessed();
	}
	process = false;
}

/*采集图片并处理数据*/
void Red_Smoke::collectAndProcessed()
{
	/*定时器、图片序号、保存excel的bool变量 初始化*/
	mytimer = new QTimer(this);
	mytimer->start();
	mytimer->setInterval(detect_time);//设置计时器间隔时间
	num_picture = 1;
	capture_img_deal_data = true;

	/*曲线窗口生成*/
	//检测重复窗口
	test = ui->mdiArea->subWindowList();
	for (int i = 0; i < test.size(); i++)
	{
		if (test[i] == subwindow_of_curve_name)
		{
			ui->mdiArea->setActiveSubWindow(subwindow_of_curve_name);
			open_curve = false;
		}
	}
	if (open_curve)
	{
		subwindow_of_Graph = new GraphOfRedValue();
		ui->mdiArea->addSubWindow(subwindow_of_Graph);
		subwindow_of_Graph->show();
		subwindow_of_Graph->setWindowTitle(tr("曲线"));
		subwindow_of_curve_name = ui->mdiArea->activeSubWindow();
	}
	subwindow_of_Graph->renew();
	connect(mytimer, &QTimer::timeout, [=]() {
		if (capture_img_deal_data == true)
		{

			QDateTime now_time = QDateTime::currentDateTime();//获取系统现在的时间
			QString time = now_time.toString("_yyyyMMdd_hh_mm_");
			QString time_of_table = now_time.toString("yyyy-MM-dd hh:mm");
			QString num = QString::number(num_picture);

			/*截取相机1两张图片*/
			//定义相机1的两张图片文件名
			QString filename_camera1_main = filename;//获取的第一张文件路径
			QString filename_camera1_refer = filename;//第二张文件路径

			//定义相机名(QString)
			filename_camera1_main.append("/Camera1");
			filename_camera1_main.append(time);
			filename_camera1_main.append(num);
			filename_camera1_main.append("_main.bmp");

			filename_camera1_refer.append("/Camera1");
			filename_camera1_refer.append(time);
			filename_camera1_refer.append(num);
			filename_camera1_refer.append("_refer.bmp");

			//保存报警图像路径
			QString filename_camera1_main_alarm;
			QString filename_camera1_refer_alarm;
			filename_camera1_main_alarm.append("C:/Warning_Record");
			filename_camera1_refer_alarm.append("C:/Warning_Record");

			filename_camera1_main_alarm.append("/Camera1");
			filename_camera1_main_alarm.append(time);
			filename_camera1_main_alarm.append("warning");
			filename_camera1_main_alarm.append("_main.jpg");

			filename_camera1_refer_alarm.append("/Camera1");
			filename_camera1_refer_alarm.append(time);
			filename_camera1_refer_alarm.append("warning");
			filename_camera1_refer_alarm.append("_refer.jpg");

			//保存烟雾图像路径
			QString filename_camera1_smoke;
			filename_camera1_smoke.append("C:/Debug");
			filename_camera1_smoke.append("/Camera1");
			filename_camera1_smoke.append(time);
			filename_camera1_smoke.append(num);
			filename_camera1_smoke.append(".jpg");

			//将QString转化为char*
			QByteArray filename_camera1_main_QByteArray = filename_camera1_main.toLatin1();
			char* filename_camera1_main_char = filename_camera1_main_QByteArray.data();

			QByteArray filename_camera1_refer_QByteArray = filename_camera1_refer.toLatin1();
			char* filename_camera1_refer_char = filename_camera1_refer_QByteArray.data();

			//捕获两张图
			bool isok1 = NET_DVR_CapturePictureBlock(camera_1->IRealPlayHandle, filename_camera1_main_char, 8000);
			//采集成功就接着采集，采集失败就不sleep了直接跳过
			cv::Mat img_camera1_isok = cv::imread(filename_camera1_main.toStdString());
			if (img_camera1_isok.type() == 0)
			{
			}
			else
			{
				Sleep(dif_time);
				NET_DVR_CapturePictureBlock(camera_1->IRealPlayHandle, filename_camera1_refer_char, 8000);
			}

			if (isok1 == false)
			{
				ui->label_of_info->setText(tr("1号相机保存图片失败"));
				//return;
			}

			/*截取相机2两张图片*/
			//定义相机2的两张图片文件名
			QString filename_camera2_main = filename;//获取的第一张文件路径
			QString filename_camera2_refer = filename;//第二张文件路径

			//定义相机名(QString)
			filename_camera2_main.append("/Camera2");
			filename_camera2_main.append(time);
			filename_camera2_main.append(num);
			filename_camera2_main.append("_main.bmp");

			filename_camera2_refer.append("/Camera2");
			filename_camera2_refer.append(time);
			filename_camera2_refer.append(num);
			filename_camera2_refer.append("_refer.bmp");

			//保存报警图像路径
			QString filename_camera2_main_alarm;
			QString filename_camera2_refer_alarm;
			filename_camera2_main_alarm.append("C:/Warning_Record");
			filename_camera2_refer_alarm.append("C:/Warning_Record");

			filename_camera2_main_alarm.append("/Camera2");
			filename_camera2_main_alarm.append(time);
			filename_camera2_main_alarm.append("warning");
			filename_camera2_main_alarm.append("_main.jpg");

			filename_camera2_refer_alarm.append("/Camera2");
			filename_camera2_refer_alarm.append(time);
			filename_camera2_refer_alarm.append("warning");
			filename_camera2_refer_alarm.append("_refer.jpg");

			//保存烟雾图像路径
			QString filename_camera2_smoke;
			filename_camera2_smoke.append("C:/Debug");
			filename_camera2_smoke.append("/Camera2");
			filename_camera2_smoke.append(time);
			filename_camera2_smoke.append(num);
			filename_camera2_smoke.append(".jpg");
			//将QString转化为char*
			QByteArray filename_camera2_main_QByteArray = filename_camera2_main.toLatin1();
			char* filename_camera2_main_char = filename_camera2_main_QByteArray.data();

			QByteArray filename_camera2_refer_QByteArray = filename_camera2_refer.toLatin1();
			char* filename_camera2_refer_char = filename_camera2_refer_QByteArray.data();

			//捕获两张图
			bool isok2 = NET_DVR_CapturePictureBlock(camera_2->IRealPlayHandle, filename_camera2_main_char, 8000);


			//采集成功就接着采集，采集失败就不sleep了直接跳过
			cv::Mat img_camera2_isok = cv::imread(filename_camera2_main.toStdString());
			if (img_camera2_isok.type() == 0)
			{
			}
			else
			{
				Sleep(dif_time);
				NET_DVR_CapturePictureBlock(camera_2->IRealPlayHandle, filename_camera2_refer_char, 8000);
			}
			if (isok2 == false)
			{
				//return;
			}

			/*截取相机3两张图片*/
			//定义相机3的两张图片文件名
			QString filename_camera3_main = filename;//获取的第一张文件路径
			QString filename_camera3_refer = filename;//第二张文件路径

			//定义相机名(QString)
			filename_camera3_main.append("/Camera3");
			filename_camera3_main.append(time);
			filename_camera3_main.append(num);
			filename_camera3_main.append("_main.bmp");

			filename_camera3_refer.append("/Camera3");
			filename_camera3_refer.append(time);
			filename_camera3_refer.append(num);
			filename_camera3_refer.append("_refer.bmp");

			//保存报警图像路径
			QString filename_camera3_main_alarm;
			QString filename_camera3_refer_alarm;
			filename_camera3_main_alarm.append("C:/Warning_Record");
			filename_camera3_refer_alarm.append("C:/Warning_Record");

			filename_camera3_main_alarm.append("/Camera3");
			filename_camera3_main_alarm.append(time);
			filename_camera3_main_alarm.append("warning");
			filename_camera3_main_alarm.append("_main.jpg");

			filename_camera3_refer_alarm.append("/Camera3");
			filename_camera3_refer_alarm.append(time);
			filename_camera3_refer_alarm.append("warning");
			filename_camera3_refer_alarm.append("_refer.jpg");

			//保存烟雾图像路径
			QString filename_camera3_smoke;
			filename_camera3_smoke.append("C:/Debug");
			filename_camera3_smoke.append("/Camera3");
			filename_camera3_smoke.append(time);
			filename_camera3_smoke.append(num);
			filename_camera3_smoke.append(".jpg");

			//将QString转化为char*
			QByteArray filename_camera3_main_QByteArray = filename_camera3_main.toLatin1();
			char* filename_camera3_main_char = filename_camera3_main_QByteArray.data();

			QByteArray filename_camera3_refer_QByteArray = filename_camera3_refer.toLatin1();
			char* filename_camera3_refer_char = filename_camera3_refer_QByteArray.data();

			//捕获两张图
			bool isok3 = NET_DVR_CapturePictureBlock(camera_3->IRealPlayHandle, filename_camera3_main_char, 8000);


			//采集成功就接着采集，采集失败就不sleep了直接跳过
			cv::Mat img_camera3_isok = cv::imread(filename_camera3_main.toStdString());
			if (img_camera3_isok.type() == 0)
			{
			}
			else
			{
				Sleep(dif_time);
				NET_DVR_CapturePictureBlock(camera_3->IRealPlayHandle, filename_camera3_refer_char, 8000);
			}
			if (isok3 == false)
			{
				//return;
			}

			/*截取相机4两张图片*/
			//定义相机4的两张图片文件名
			QString filename_camera4_main = filename;//获取的第一张文件路径
			QString filename_camera4_refer = filename;//第二张文件路径

			//定义相机名(QString)
			filename_camera4_main.append("/Camera4");
			filename_camera4_main.append(time);
			filename_camera4_main.append(num);
			filename_camera4_main.append("_main.bmp");

			filename_camera4_refer.append("/Camera4");
			filename_camera4_refer.append(time);
			filename_camera4_refer.append(num);
			filename_camera4_refer.append("_refer.bmp");

			//保存报警图像路径
			QString filename_camera4_main_alarm;
			QString filename_camera4_refer_alarm;
			filename_camera4_main_alarm.append("C:/Warning_Record");
			filename_camera4_refer_alarm.append("C:/Warning_Record");

			filename_camera4_main_alarm.append("/Camera4");
			filename_camera4_main_alarm.append(time);
			filename_camera4_main_alarm.append("warning");
			filename_camera4_main_alarm.append("_main.jpg");

			filename_camera4_refer_alarm.append("/Camera4");
			filename_camera4_refer_alarm.append(time);
			filename_camera4_refer_alarm.append("warning");
			filename_camera4_refer_alarm.append("_refer.jpg");
			//将QString转化为char*
			QByteArray filename_camera4_main_QByteArray = filename_camera4_main.toLatin1();
			char* filename_camera4_main_char = filename_camera4_main_QByteArray.data();

			QByteArray filename_camera4_refer_QByteArray = filename_camera4_refer.toLatin1();
			char* filename_camera4_refer_char = filename_camera4_refer_QByteArray.data();

			//捕获两张图
			bool isok4 = NET_DVR_CapturePictureBlock(camera_4->IRealPlayHandle, filename_camera4_main_char, 8000);


			//采集成功就接着采集，采集失败就不sleep了直接跳过
			cv::Mat img_camera4_isok = cv::imread(filename_camera4_main.toStdString());
			if (img_camera4_isok.type() == 0)
			{
			}
			else
			{
				Sleep(dif_time);
				NET_DVR_CapturePictureBlock(camera_4->IRealPlayHandle, filename_camera4_refer_char, 8000);
			}
			if (isok4 == false)
			{
				//return;
			}


			/*数据处理部分*/
			//采集4个摄像头的图像
			cv::Mat img_camera1_main = cv::imread(filename_camera1_main.toStdString());
			cv::Mat img_camera1_refer = cv::imread(filename_camera1_refer.toStdString());
			cv::Mat img_camera2_main = cv::imread(filename_camera2_main.toStdString());
			cv::Mat img_camera2_refer = cv::imread(filename_camera2_refer.toStdString());
			cv::Mat img_camera3_main = cv::imread(filename_camera3_main.toStdString());
			cv::Mat img_camera3_refer = cv::imread(filename_camera3_refer.toStdString());
			cv::Mat img_camera4_main = cv::imread(filename_camera4_main.toStdString());
			cv::Mat img_camera4_refer = cv::imread(filename_camera4_refer.toStdString());

			//四个烟雾图像
			cv::Mat img_smoke_camera1;
			cv::Mat img_smoke_camera2;
			cv::Mat img_smoke_camera3;
			cv::Mat img_smoke_camera4;

			//检测采集相机有效个数
			int effect_camera_num = 0;
			//每个相机所采集到的红色值
			double red_value_camera1 = 0.0;
			double red_value_camera2 = 0.0;
			double red_value_camera3 = 0.0;
			double red_value_camera4 = 0.0;
			if (img_camera1_main.type() == 0)
			{
			}
			else
			{
				effect_camera_num++;
				red_value_camera1 = SmokeRecongnize::recognizeAnalyze(img_camera1_main, img_camera1_refer, threshold1, threshold2, a);
			}

			if (img_camera2_main.type() == 0)
			{
			}
			else
			{
				effect_camera_num++;
				red_value_camera2 = SmokeRecongnize::recognizeAnalyze(img_camera2_main, img_camera2_refer,threshold1, threshold2, a);
			}

			if (img_camera3_main.type() == 0)
			{
			}
			else
			{
				effect_camera_num++;
				red_value_camera3 = SmokeRecongnize::recognizeAnalyze(img_camera3_main, img_camera3_refer, threshold1, threshold2, a);
			}

			if (img_camera4_main.type() == 0)
			{
			}
			else
			{
				effect_camera_num++;
				red_value_camera4 = SmokeRecongnize::poolAnalyze(img_camera4_main);
			}

		
			//红烟气有效值应该是最大的那个值
			double Max_Red = 0;
			if (red_value_camera1>Max_Red)
			{
				Max_Red = red_value_camera1;
			}
			if (red_value_camera2>Max_Red)
			{
				Max_Red = red_value_camera2;
			}
			if (red_value_camera3>Max_Red)
			{
				Max_Red = red_value_camera3;
			}
			if (red_value_camera4>Max_Red)
			{
				Max_Red = red_value_camera4;
			}

			

			double red_value_tmp = Max_Red;

			red_value = 0;

			//如果检测值等于0，说明图片没有变化就置为0，如果不为0，则将其-100再平方
			if (red_value_tmp < 100)
			{
				red_value = 0;
			}
			if (red_value_tmp <= 100.3 && red_value_tmp >= 100)
			{
				red_value = red_value_tmp - 100 + 5;
			}
			if (red_value_tmp <= 100.5 && red_value_tmp >= 100.3)
			{
				red_value = red_value_tmp - 100 + 10;
			}

			if (red_value_tmp <= 101 && red_value_tmp >= 100.5)
			{
				red_value = red_value_tmp - 100 + 20;
			}
			if (red_value_tmp>101)
			{
				red_value = (red_value_tmp - 100)*(red_value_tmp - 100) + 20;
			}

			//设置红色值
			subwindow_of_Graph->setRedValue(red_value);
			subwindow_of_video->setRedValue(red_value);

			//保存红烟图片
			if (red_value > threshold_of_warning_record)
			{
				if (red_value_camera1 == Max_Red)
				{
					cv::imwrite(filename_camera1_main_alarm.toStdString(), img_camera1_main);
					cv::imwrite(filename_camera1_refer_alarm.toStdString(), img_camera1_refer);
				}

				if (red_value_camera2 == Max_Red)
				{
					cv::imwrite(filename_camera2_main_alarm.toStdString(), img_camera2_main);
					cv::imwrite(filename_camera2_refer_alarm.toStdString(), img_camera2_refer);
				}

				if (red_value_camera3 == Max_Red)
				{
					cv::imwrite(filename_camera3_main_alarm.toStdString(), img_camera3_main);
					cv::imwrite(filename_camera3_refer_alarm.toStdString(), img_camera3_refer);
				}

				if (red_value_camera4 == Max_Red)
				{
					cv::imwrite(filename_camera4_main_alarm.toStdString(), img_camera4_main);
					cv::imwrite(filename_camera4_refer_alarm.toStdString(), img_camera4_refer);
				}
			}

			//如果处于调试状态就保存烟雾图片
			if (debug)
			{
				img_smoke_camera1 = SmokeRecongnize::smokeImg(img_camera1_main, img_camera1_refer, threshold1, threshold2, a);
				img_smoke_camera2 = SmokeRecongnize::smokeImg(img_camera2_main, img_camera2_refer, threshold1, threshold2, a);
				img_smoke_camera3 = SmokeRecongnize::smokeImg(img_camera3_main, img_camera3_refer, threshold1, threshold2, a);

				cv::imwrite(filename_camera1_smoke.toStdString(), img_smoke_camera1);
				cv::imwrite(filename_camera2_smoke.toStdString(), img_smoke_camera2);
				cv::imwrite(filename_camera3_smoke.toStdString(), img_smoke_camera3);
			}
			else
			{

			}
			/*更新曲线*/
			
			//到了15号自动清空
			QDateTime time_of_now = QDateTime::currentDateTime();//获取系统现在的时间
			QString x_label = time_of_now.toString("yy MM dd hh mm ss");//利用空格将数据分隔开
			QStringList x_label_list = x_label.split(" ");
			QString day = x_label_list[2];
			int days = day.toInt();
			if (days == 15)
			{
				subwindow_of_Graph->clearData();
			}

			//画点
			double x_label_data = QDateTime::currentSecsSinceEpoch();
			subwindow_of_Graph->rePaint(x_label_data, red_value);
		
			

			/*当大于报警记录阈值时，就保存在表格中*/
			if (red_value > threshold_of_warning_record)
			{
				//时间
				subwindow_of_table->addData(row, 0, new QTableWidgetItem(time_of_table));
				//报警阈值
				subwindow_of_table->addData(row, 1, new QTableWidgetItem(QString::number(threshold_of_warning_record)));
				//当前报警值
				subwindow_of_table->addData(row, 2, new QTableWidgetItem(QString::number(red_value)));
				row++;
			}
			/*大于记录的报表则清除*/
			if (row >= 10000)
			{
				subwindow_of_table->clearContent();
				row = 0;
			}
			
			/*自动删除图片*/
			//图像序列号加一
			num_picture = num_picture + 1;
			delete_img_array.append(filename_camera1_main);
			delete_img_array.append(filename_camera1_refer);
			delete_img_array.append(filename_camera2_main);
			delete_img_array.append(filename_camera2_refer);
			delete_img_array.append(filename_camera3_main);
			delete_img_array.append(filename_camera3_refer);
			delete_img_array.append(filename_camera4_main);
			delete_img_array.append(filename_camera4_refer);

			//当存储图像大于一定数量后自动删除
			if (num_picture >= (max_img_amount + 2))
			{
				for (int i = 0; i<delete_img_array.size(); i++)
				{
					bool isok = FileManage::deleteFileOrFolder(delete_img_array[i]);
				}
				delete_img_array.clear();
				num_picture = 1;
			}

		}//开始保存和处理数据bool量

	});//定时器

}

/*串口初始化*/
void Red_Smoke::initPort()
{
	//初始化串口
	m_serialPort = new QSerialPort();
	//获取能用的串口名称
	m_portNameList = getPortNameList();
	//下拉框显示
	ui->comboBox->addItems(m_portNameList);
	connect(ui->pushButton_open_serial, &QPushButton::clicked, this, &Red_Smoke::openPort);
}

/*获取所有可用的串口列表*/
QStringList Red_Smoke::getPortNameList()
{
	QStringList m_serialPortName;
	QSerialPortInfo info;
	QList<QSerialPortInfo> listport;
	listport = QSerialPortInfo::availablePorts();
	for (int i = 0; i<listport.size(); i++)
	{
		m_serialPortName << listport[i].portName();
	}
	return m_serialPortName;
}

/*打开串口*/
void Red_Smoke::openPort()
{
	if (m_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
	{
		m_serialPort->clear();
		m_serialPort->close();
	}

	//设置串口名字
	m_serialPort->setPortName(ui->comboBox->currentText());//当前选择的串口名字
	 //打开串口
	if (!m_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
	{
		return;
	}
	//设置串口通讯参数
	m_serialPort->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);//设置波特率和读写方向
	m_serialPort->setDataBits(QSerialPort::Data8);      //数据位为8位
	m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
	m_serialPort->setParity(QSerialPort::NoParity); //无校验位
	m_serialPort->setStopBits(QSerialPort::OneStop); //一位停止位

	connect(m_serialPort, SIGNAL(readyRead()), this, SLOT(receiveInfo()));
}

/*接收到单片机发送的数据进行解析*/
void Red_Smoke::receiveInfo()
{
	info = m_serialPort->readAll();
	//info.resize(8);
	test_refer.resize(8);
	test_refer[0] = 0x01;
	test_refer[1] = 0x04;
	test_refer[2] = 0x00;
	test_refer[3] = 0x02;
	test_refer[4] = 0x00;
	test_refer[5] = 0x01;
	test_refer[6] = 0x90;
	test_refer[7] = 0x0A;

	int a = info.size();

	//如果相等就发送数据
	if (info == test_refer)
	{
		sendMyMessage_test();
	}
}


/*QString转16进制*/
void Red_Smoke::convertStringToHex(const QString &str, QByteArray &byteData)
{
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = str.length();
	byteData.resize(len / 2);
	char lstr, hstr;
	for (int i = 0; i<len; )
	{
		//char lstr,
		hstr = str[i].toLatin1();
		if (hstr == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		lstr = str[i].toLatin1();
		hexdata = convertCharToHex(hstr);
		lowhexdata = convertCharToHex(lstr);
		if ((hexdata == 16) || (lowhexdata == 16))
			break;
		else
			hexdata = hexdata * 16 + lowhexdata;
		i++;
		byteData[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}
	byteData.resize(hexdatalen);
}
char Red_Smoke::convertCharToHex(char ch)
{
	/*
	0x30等于十进制的48，48也是0的ASCII值，，
	1-9的ASCII值是49-57，，所以某一个值－0x30，，
	就是将字符0-9转换为0-9

	*/
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else return (-1);
}

/*向串口发送信息*/
void Red_Smoke::sendInfo(const QString &info)
{
	QByteArray sendBuf;

	convertStringToHex(info, sendBuf); //把QString 转换 为 hex

	m_serialPort->write(sendBuf);//这句是真正的给单片机发数据 用到的是QIODevice::write 具体可以看文档
}

/*设置发送的报文帧*/
void Red_Smoke::setSendMessage_test(int send_data)
{
	frame.clear();
	frame.resize(7);
	//从机地址
	QString a = ui->lineEdit_slave_adress->text();
	frame[0] = 1;

	//功能码
	QString b = ui->lineEdit_function->text();
	frame[1] = 4;

	//数据字节长度


	QString d = ui->lineEdit_3_start_address_2->text();
	frame[2] = 2;

	//写如的数据为88
	int data = send_data;
	uint8_t data_bit[2];
	data_bit[0] = data >> 8;
	data_bit[1] = data;
	frame[3] = data_bit[0];

	frame[4] = data_bit[1];

	//CRC校验

	uint8_t  crc16[5];

	crc16[0] = 1;
	crc16[1] = 4;

	crc16[2] = 2;
	crc16[3] = data_bit[0];
	crc16[4] = data_bit[1];

	uint16_t res = MB_CRC16_calculate(crc16, 5);

	int tmp = res;
	uint8_t data_bit_tmp[2];
	data_bit_tmp[0] = tmp >> 8;
	data_bit_tmp[1] = tmp;
	frame[5] = data_bit_tmp[1];

	frame[6] = data_bit_tmp[0];
	frame = frame.toHex();


}

/*CRC*/
uint16_t Red_Smoke::MB_CRC16_calculate(uint8_t * array, uint8_t index)
{
	uint16_t tmp = 0xffff;
	uint16_t ret1 = 0;

	for (int n = 0; n < index; n++) {
		tmp = array[n] ^ tmp;
		for (int i = 0; i < 8; i++) {
			if (tmp & 0x01) {
				tmp = tmp >> 1;
				tmp = tmp ^ 0xa001;
			}
			else {
				tmp = tmp >> 1;
			}
		}
	}


	ret1 = tmp >> 8;
	ret1 = ret1 | (tmp << 8);
	return tmp;
}

/*将16进制字符串转换为对应的字节序列*/
QByteArray Red_Smoke::HexStringToByteArray(QString HexString)
{
	bool ok;
	QByteArray ret;
	HexString = HexString.trimmed();
	HexString = HexString.simplified();
	QStringList sl = HexString.split(" ");
	sl.size();
	//foreach(QString s, sl) 
	for (int i = 0; i< sl.size(); i++)
	{
		QString s = sl[i];
		if (!s.isEmpty())
		{
			char c = s.toInt(&ok, 16) & 0xFF;
			if (ok) {
				ret.append(c);
			}
			else {
				//QMessageBox::warning(0,tr("错误："),QString("非法的16进制字符: \"%1\"").arg(s));
			}
		}
	}
	return ret;
}

/*发送我的消息帧*/
void Red_Smoke::sendMyMessage_test()
{
	//实战
	int sendData = red_value;
	setSendMessage_test(sendData);//设置参数
	QString str = frame;
	str = str.toUpper();
	ui->label_send_message->setText(str);
	//处理字符串
	QString end = "";
	end = end + str.left(2);
	str.remove(0, 2);
	end = end + " " + str.left(2);
	str.remove(0, 2);
	end = end + " " + str.left(2);
	str.remove(0, 2);
	end = end + " " + str.left(2);
	str.remove(0, 2);
	end = end + " " + str.left(2);
	str.remove(0, 2);
	end = end + " " + str.left(2);
	str.remove(0, 2);
	end = end + " " + str.left(2);
	str.remove(0, 2);
	end = end + " " + str.left(2);

	QByteArray myDate = HexStringToByteArray(end);
	m_serialPort->write(myDate);
}

/*相机登录过程中反馈错误*/
void Red_Smoke::setErrorMessage()
{
		int error_num = NET_DVR_GetLastError();
		if (error_num == 1)
		{
			ui->label_of_info->setText(tr("用户名或者密码错误"));
		}
		if (error_num == 7)
		{
			ui->label_of_info->setText(tr("设备不在线，请检查网络连接状态"));
		}
}