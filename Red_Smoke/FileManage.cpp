#include "FileManage.h"



FileManage::FileManage()
{
}


FileManage::~FileManage()
{
}

/*ɾ���ļ����ļ���*/
bool FileManage::deleteFileOrFolder(const QString &strPath)
{
	if (strPath.isEmpty() || !QDir().exists(strPath))//�Ƿ����˿յ�·��||·���Ƿ����
		return false;

	QFileInfo FileInfo(strPath);

	if (FileInfo.isFile())//������ļ�
		QFile::remove(strPath);
	else if (FileInfo.isDir())//������ļ���
	{
		QDir qDir(strPath);
		qDir.removeRecursively();
	}
	return true;
}