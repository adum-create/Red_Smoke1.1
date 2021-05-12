#include "FileManage.h"



FileManage::FileManage()
{
}


FileManage::~FileManage()
{
}

/*删除文件或文件夹*/
bool FileManage::deleteFileOrFolder(const QString &strPath)
{
	if (strPath.isEmpty() || !QDir().exists(strPath))//是否传入了空的路径||路径是否存在
		return false;

	QFileInfo FileInfo(strPath);

	if (FileInfo.isFile())//如果是文件
		QFile::remove(strPath);
	else if (FileInfo.isDir())//如果是文件夹
	{
		QDir qDir(strPath);
		qDir.removeRecursively();
	}
	return true;
}