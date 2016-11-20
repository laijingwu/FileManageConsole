#include "FileManagement.h"

// 通过当前程序路径构造 
FileManagement::FileManagement() : currentDirPath() {
	this->getCurrentDirPath(this->currentDirPath);
	this->initRoot(); 
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
	// 只有盘符 
	string tmp = path;
	if (path.substr(path.length() - 1) == ":") {
		tmp.append("/");
	}
	// 验证是否存在该目录
	if (this->isDir(tmp.c_str()))
		path.copy(this->currentDirPath, DIRPATH_MAX, 0);
	else
		this->getCurrentDirPath(this->currentDirPath);
	
	this->initRoot(); 
}

FileNode* CreateFileNode(string filename, bool isdir, int i_nlink, string path)  {
    FileNode* node = new FileNode; //申请结点空间
	// 初始化相应内容
    node->fileName = filename;
	node->isDir = isdir;
	node->addr = path;
	node->i_nlink = i_nlink;
	node->parent = NULL;
	node->child = NULL;
	node->sibling_prev = NULL;
	node->sibling_next = NULL;
    return node;
}


// 初始化当前目录 建立链表 
void FileManagement::initRoot() {
	this->root = CreateFileNode(this->getNameFromPath(this->currentDirPath), true, 0, this->currentDirPath);
	// TODO: 循环出上一级目录 当前目录 下一级目录 并使用链表结构 
	this->root->parent = NULL;
	this->root->child = NULL;
	this->root->sibling_prev = this->root->sibling_next = NULL;
}

// 获取当前程序路径 
void FileManagement::getCurrentDirPath(char *path) {
	getcwd(path, DIRPATH_MAX);
}

// 通过路径检测文件/文件夹是否存在 
bool FileManagement::isExist(const char *path) {
	//if (access(path, 0) != -1)
	struct stat buf = { 0 };
	if (stat(path, &buf) == 0)
    	return true;
    else
    	return false;
}

// 通过路径检测是否为文件夹 
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

// 通过路径获取文件名/目录名 
string FileManagement::getNameFromPath(string path) {
	if (path.substr(path.length() - 1) == ":")
		return string();
	else
		return path.substr(path.find_last_of("/") + 1);
}

// 获取上一级目录路径 
string FileManagement::getLastDirPath(string path) {
	int pos = path.find_last_of("/");
	if (pos != -1) {
		return path.substr(0, pos);
	} else {
		return NULL;
	}
}

void FileManagement::traverseDir(string path) {
	_finddata_t filefind;
	string curr = path + "/*.*";
	long handle;
    if((handle = _findfirst(curr.c_str(), &filefind)) == -1l) {
    	return;
    }
    while (!_findnext(handle,&filefind)) {
		cout << filefind.name;
		if (!strcmp(filefind.name, "..")){
			continue;
		}
		cout << "     ";
		if ((filefind.attrib >= 16 && filefind.attrib <= 23) || 
		(filefind.attrib >= 48 && filefind.attrib <= 55)) { // 目录 
			curr = path + "/" + filefind.name;
			cout << curr << "(dir)" << endl;
		} else { // 文件 
			cout << path + "/" + filefind.name << endl;
		}
    }
    _findclose(handle);
} 

// 列出目录 
void FileManagement::cmdLs() {
	//cout << this->getName("D:");
	//cout << this->getLastDirPath(this->currentDirPath); 
	this->traverseDir(this->currentDirPath);
}

// 改变目录 
void FileManagement::cmdCd() {
	//
}

// 删除文件 
void FileManagement::cmdRm() {
	//
}

//  复制文件 
void FileManagement::cmdCp() {
	// 
}

// 移动文件 
void FileManagement::cmdMv() {
	//
}

// 新建文件 
void FileManagement::cmdTouch() {
	//
}

// 新建目录 
void FileManagement::cmdMkDir() {
	//
}

// 删除目录 
void FileManagement::cmdRmDir() {
	//
}
