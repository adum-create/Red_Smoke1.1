#pragma once
#ifndef FILEMANAGE_H
#define FILEMANAGE_H
#include <QFile>
#include <QDir>
#include <QString>



class FileManage
{
public:
	FileManage();
	~FileManage();

	/*ɾ���ļ����ļ���*/
	static bool deleteFileOrFolder(const QString &strPath);

};

#endif // FILEMANAGE_H
