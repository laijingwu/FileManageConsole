#include "FileManagement.h"

// ͨ����ǰ����·������ 
FileManagement::FileManagement() : currentDirPath() {
	this->getCurrentDirPath(this->currentDirPath);
}

// ͨ������·������ 
FileManagement::FileManagement(string path) : currentDirPath() {
	// ͳһĿ¼�ָ���Ϊ / 
	this->strReplace(path, "\\\\", "/");
	this->strReplace(path, "\\", "/");
	// ȥ��Ŀ¼ĩβ 
	if (path.find_last_of("/") == path.length() - 1) {
		path = path.substr(0, path.length() - 1);
	}
	// ��֤�Ƿ���ڸ�Ŀ¼
	if (this->isDir(path.c_str()))
		path.copy(this->currentDirPath, DIRPATH_MAX, 0);
	else
		this->getCurrentDirPath(this->currentDirPath);
}

// ��ȡ��ǰ����·�� 
void FileManagement::getCurrentDirPath(char *path) {
	getcwd(path, DIRPATH_MAX);
}

// �ļ�/�ļ����Ƿ���� 
bool FileManagement::isExist(const char *path) {
	//if (access(path, 0) != -1)
	struct stat buf = { 0 };
	if (stat(path, &buf) == 0)
    	return true;
    else
    	return false;
}

// ����Ƿ�Ϊ�ļ��� 
bool FileManagement::isDir(const char *path) {
    struct stat buf = { 0 };
	if (stat(path, &buf) == 0 && (buf.st_mode & S_IFDIR))
		return true;
	else
		return false;
}

// �������ǰ׺ 
void FileManagement::showCmdPrefix() {
	cout << this->currentDirPath << "# ";
}

// �ַ����滻 
void FileManagement::strReplace(string &str, const char *search, const char *replace) {
	int pos = 0;
	while ((pos = str.find(search, pos)) >= 0) {
		str.replace(pos, strlen(search), replace);
	    pos += strlen(replace);
	}
}
