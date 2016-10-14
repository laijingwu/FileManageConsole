#include "FileManagement.h"

// 通过当前程序路径构造 
FileManagement::FileManagement() : currentDirPath() {
	this->getCurrentDirPath(this->currentDirPath);
}

// 通过参数路径构造 
FileManagement::FileManagement(string path) : currentDirPath() {
	// 统一目录分隔符为 / 
	this->strReplace(path, "\\\\", "/");
	this->strReplace(path, "\\", "/");
	// 去掉目录末尾 
	if (path.find_last_of("/") == path.length() - 1) {
		path = path.substr(0, path.length() - 1);
	}
	// 验证是否存在该目录
	if (this->isDir(path.c_str()))
		path.copy(this->currentDirPath, DIRPATH_MAX, 0);
	else
		this->getCurrentDirPath(this->currentDirPath);
}

// 获取当前程序路径 
void FileManagement::getCurrentDirPath(char *path) {
	getcwd(path, DIRPATH_MAX);
}

// 文件/文件夹是否存在 
bool FileManagement::isExist(const char *path) {
	//if (access(path, 0) != -1)
	struct stat buf = { 0 };
	if (stat(path, &buf) == 0)
    	return true;
    else
    	return false;
}

// 检测是否为文件夹 
bool FileManagement::isDir(const char *path) {
    struct stat buf = { 0 };
	if (stat(path, &buf) == 0 && (buf.st_mode & S_IFDIR))
		return true;
	else
		return false;
}

// 输出命令前缀 
void FileManagement::showCmdPrefix() {
	cout << this->currentDirPath << "# ";
}

// 字符串替换 
void FileManagement::strReplace(string &str, const char *search, const char *replace) {
	int pos = 0;
	while ((pos = str.find(search, pos)) >= 0) {
		str.replace(pos, strlen(search), replace);
	    pos += strlen(replace);
	}
}
