#include "FileManagement.h"

FileManagement::FileManagement() {
	this->getCurrentDirPath(this->currentDirPath);
}

FileManagement::FileManagement(string path) {
	// 验证是否存在该目录 
	if (this->isExist(path.c_str()))
		path.copy(this->currentDirPath, DIRPATH_MAX, 0);
	else
		this->getCurrentDirPath(this->currentDirPath);
}

void FileManagement::getCurrentDirPath(char *path) {
	getcwd(path, DIRPATH_MAX);
}

bool FileManagement::isExist(const char *path) {
	//if (access(path, 0) != -1)
	struct stat buf = { 0 };
	if (stat(path, &buf) == 0)
    	return true;
    else
    	return false;
}

bool FileManagement::isDir(const char* path) {
    struct stat buf = { 0 };
	if (stat(path, &buf) == 0 && (buf.st_mode & S_IFDIR))
		return true;
	else
		return false;
}

void FileManagement::showCmdPrefix() {
	cout << this->currentDirPath << "# ";
}

