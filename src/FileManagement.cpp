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
}

// 获取当前程序路径 
void FileManagement::getCurrentDirPath(char *path) {
	getcwd(path, DIRPATH_MAX);
}

// 通过路径检测文件/文件夹是否存在 
bool FileManagement::isExist(const char *path) {
	// if (access(path, 0) != -1)
	struct stat buf = { 0 };
	if (stat(path, &buf) == 0) // 存在 
    	return true;
    else
    	return false;
}

// 通过路径检测是否为文件夹 
bool FileManagement::isDir(const char *path) {
	if (!strcmp(path, ".."))
		return false;
	
    struct stat buf = { 0 };
	if (stat(path, &buf) == 0 && (buf.st_mode & S_IFDIR)) // 为文件夹 
		return true;
	else
		return false;
}

// 通过路径检测是否为文件
bool FileManagement::isFile(const char *path) {
    struct stat buf = { 0 };
	if (stat(path, &buf) == 0 && !(buf.st_mode & S_IFDIR)) // 不为文件夹 
		return true;
	else
		return false;
}

// 输出命令前缀 
void FileManagement::showCmdPrefix() {
	cout << this->currentDirPath << "> ";
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
		return path;
	}
}

// 时间戳转字符串 
string FileManagement::getStringTime(time_t lt) {
	time_t tick = lt;
	char timeStr[100] = {0};
	struct tm *ptr = localtime(&tick);
	strftime(timeStr, sizeof(timeStr), "%Y/%m/%d  %H:%M:%S", ptr);
	return string(timeStr);
}

// 列出目录
void FileManagement::cmdLs() {
	cout << endl << "   Directory: " << this->currentDirPath << endl << endl;
	
	string path = this->currentDirPath;
	_finddata_t filefind;
	string curr = path + "/*.*"; // 用于遍历文件夹 
	long handle;

	unsigned long n_dir, n_file;	// 目录、文件计数 
	n_dir = n_file = 0;
	
    if ((handle = _findfirst(curr.c_str(), &filefind)) == -1l) {
    	return;
    }
    while (!_findnext(handle, &filefind)) {
		if (!strcmp(filefind.name, "..")) {
			continue;
		}
		cout << this->getStringTime(filefind.time_write) << "\t";
		if ((filefind.attrib >= 16 && filefind.attrib <= 23) || 
		(filefind.attrib >= 48 && filefind.attrib <= 55)) { // 目录 
			n_dir++;
			cout << "<DIR>" << "\t";
		} else { // 文件 
			n_file++;
			cout << "\t" << filefind.size << " Byte";
		}
		cout << "\t" << filefind.name << endl;
    }
    cout << "\t\t" << n_file << " files   " << n_dir << " directories" << endl << endl;
    _findclose(handle);
}

// 格式化路径以用于地址转换 
void FileManagement::formatPathToConvert(string &path) {
	// 统一目录分隔符为 / 
	this->strReplace(path, "\\\\", "/");
	this->strReplace(path, "\\", "/");
	this->strReplace(path, "//", "/");
	// 去掉头部的分隔符 
	if (path.find_first_of("/") == 0) {
		path = path.substr(1, path.length() - 1);
	}
} 

// 相对地址转换成绝对地址 
string FileManagement::pathRelativePathTo(string path, bool checkExist) {
	// 末尾添加斜杠用于分隔 
	if (path.find_last_of("/") != path.length() - 1) {
		path.append("/"); 
	}
	
	vector<string> path_part;
	
	// 分开路径各部分 
	size_t pathTmp, pathPos = 0;
	while ((pathTmp = path.find('/', pathPos)) != string::npos) {
		path_part.push_back(path.substr(pathPos, pathTmp - pathPos));
		pathPos = pathTmp + 1;
	}
	
	string strTmp(this->currentDirPath);
	for (vector<string>::iterator iter = path_part.begin(); iter != path_part.end(); iter++) {
		if (*iter == "..") { // 上一级 
			strTmp = getLastDirPath(strTmp);
			if (strTmp.empty()) {
				return string();
			}
		} else if (*iter == ".") { // 当前目录跳过 
			continue;
		} else {
			// 拼接路径字符串 
			if (strTmp.length() < 3 || strTmp.substr(strTmp.length() - 2, 1) != ":")
				strTmp.append("/");
			strTmp.append(*iter);
			if (this->isExist(strTmp.c_str()) || checkExist == false) { // 仅存在 
				continue;
			} else {
				return string();
			}
		}
	}
	return strTmp;
} 

// 改变目录 
void FileManagement::cmdCd(string pathname) {
	// 格式化路径（相对、绝对转换） 
	formatPathToConvert(pathname);
	string path = this->pathRelativePathTo(pathname, false);
	if (path.substr(path.length() - 1) == ":") {
		path.append("/");
	}
	
	//cout << path << "|" << pathname << "|" << endl;
	bool bdir = this->isDir(pathname.c_str());
	//cout << bdir << this->isDir(path.c_str());
	if (!this->isDir(path.c_str()) && !bdir) { // 验证是否存在该目录
		cout << "Cannot find the specified path." << endl << endl;
		return;
	}
	if (bdir && pathname.length() > 1 && pathname.substr(1, 1) == ":") path = pathname;

	// 刷新当前目录 
	memset(this->currentDirPath, 0, DIRPATH_MAX);
	path.copy(this->currentDirPath, DIRPATH_MAX, 0);
}

// 删除文件 
void FileManagement::cmdRm(string filename) {
	// 格式化路径（相对、绝对转换） 
	formatPathToConvert(filename);
	string path = this->pathRelativePathTo(filename, false);

	bool bfile = this->isFile(filename.c_str());
	if (!this->isFile(path.c_str()) && !bfile) { // 验证是否存在
		cout << "File does not exist." << endl << endl;
		return;
	}
	if (bfile) path = filename;
	// 删除文件 
	if (unlink(path.c_str()) < 0) cout << "Delete failed. Maybe it is permission denied." << endl << endl;
}

// 复制文件 
void FileManagement::cmdCp(string from, string to) {
	// 格式化路径（相对、绝对转换） 
	formatPathToConvert(from);
	string frompath = this->pathRelativePathTo(from);
	formatPathToConvert(to);
	string topath = this->pathRelativePathTo(to, false);
	
	bool bfile = this->isFile(from.c_str());
	if (frompath.empty() && !bfile) { // 验证是否存在
		cout << from << " does not exist." << endl << endl;
		return;
	}
	if (bfile) frompath = from;
	
	// 判断目的地址的目录是否存在 
	string lastDirPath = this->getLastDirPath(to.c_str());
	bool bdir = this->isDir(lastDirPath.c_str());
	lastDirPath = this->getLastDirPath(topath.c_str());
	bool bdir_xd = this->isDir(lastDirPath.c_str());
	if (!bdir_xd && !bdir) { // 验证是否存在
		cout << "Destination directory does not exist." << endl << endl;
		return;
	}
	if (bdir) topath = to;
	
	ifstream in;
	ofstream out;
	in.open(frompath.c_str(), ios::binary); // 打开源文件
	if (in.fail()) {
		// 打开源文件失败
		cout << "Cannot open source file." << endl << endl;
		in.close();
		return;
	}
	out.open(topath.c_str(), ios::binary); // 创建目标文件 
	if (out.fail()) {
		// 创建文件失败
		cout << "Cannot create new file." << endl << endl;
	} else {
		// 复制文件
		out << in.rdbuf();
	}
	out.close();
	in.close();
}

// 移动文件 
void FileManagement::cmdMv(string from, string to) {
	this->cmdCp(from, to); // 复制文件 
	this->cmdRm(from); // 删除原有文件 
}

// 新建文件 
void FileManagement::cmdTouch(string filename) {
	// 格式化路径（相对、绝对转换） 
	formatPathToConvert(filename);
	string path = this->pathRelativePathTo(filename, false);
	string lastDirPath = this->getLastDirPath(path.c_str());
	
	// 使用相对路径转换来的绝对路径 
	if (this->isDir(lastDirPath.c_str())) {
		if (this->isExist(path.c_str())) {
			cout << "File or directory already exists." << endl << endl;
			return;
		}
		// 创建文件 
		FILE *fp = fopen(path.c_str(), "w+");
    	fclose(fp);
	} else { // 使用绝对路径
		lastDirPath = this->getLastDirPath(filename.c_str());
		if (this->isDir(lastDirPath.c_str())) {
			if (this->isExist(filename.c_str())) {
				cout << "File or directory already exists." << endl << endl;
				return;
			}
			// 创建文件 
			FILE *fp = fopen(filename.c_str(), "w+");
    		fclose(fp);
		} else {
			cout << "Destination directory does not exist." << endl << endl;
			return;
		}
	}
}

// 新建目录 
void FileManagement::cmdMkDir(string dirname) {
	// 格式化路径（相对、绝对转换） 
	formatPathToConvert(dirname);
	string path = this->pathRelativePathTo(dirname, false);
	string lastDirPath = this->getLastDirPath(path.c_str());
	
	// 使用相对路径转换来的绝对路径 
	if (this->isDir(lastDirPath.c_str())) {
		if (this->isDir(path.c_str())) {
			cout << "Destination directory already exists." << endl << endl;
			return;
		}
		// 创建目录 
		if (mkdir(path.c_str()) < 0) cout << "Failed to create directory. Maybe it is permission denied." << endl << endl;
	} else { // 使用绝对路径
		lastDirPath = this->getLastDirPath(dirname.c_str());
		if (this->isDir(lastDirPath.c_str())) {
			if (this->isDir(dirname.c_str())) {
				cout << "Destination directory already exists." << endl << endl;
				return;
			}
			// 创建目录 
			if (mkdir(dirname.c_str()) < 0) cout << "Failed to create directory. Maybe it is permission denied." << endl << endl;
		} else {
			cout << "The last directory of destination directory does not exist." << endl << endl;
			return;
		}
	}
}

// 删除目录递归函数 
void FileManagement::traverseRemoveDir(string path) {
	_finddata_t fileDir;
	string curr = path + "/*.*";
	long lfDir;
     
    // 目录下没有文件 
    if((lfDir = _findfirst(curr.c_str(), &fileDir)) == -1l) {
    	return;
    }
	
	string tmp;
	// 遍历文件夹下所有文件 
	do {
		// 去除.. 和 . 
		if (!strcmp(fileDir.name, "..") || !strcmp(fileDir.name, ".")) {
			continue;
		}
		// 判断目录 递归 
		if ((fileDir.attrib >= 16 && fileDir.attrib <= 23) || 
		(fileDir.attrib >= 48 && fileDir.attrib <= 55)) {
			this->traverseRemoveDir(path + "/" + fileDir.name);
			continue;
		}
		
		tmp = path;
		tmp.append("/");
		tmp.append(fileDir.name);
		if (unlink(tmp.c_str()) < 0) { // 删除文件 
			cout << "Failed to delete files in the directory. Maybe it is permission denied." << endl << endl;
			return;
		}
	} while (_findnext(lfDir, &fileDir) == 0);
    _findclose(lfDir);
    if (rmdir(path.c_str()) < 0) { // 删除文件夹 
    	cout << "Failed to delete directory. Maybe it is permission denied." << endl << endl;
    	return;
    } 
}

// 删除目录 
void FileManagement::cmdRmDir(string dirname) {
	// 格式化路径（相对、绝对转换） 
	formatPathToConvert(dirname);
	string path = this->pathRelativePathTo(dirname, false);
	
	bool bdir = this->isDir(dirname.c_str());
	if (!this->isDir(path.c_str()) && !bdir) {
		cout << "Directory does not exist." << endl << endl;
		return;
	}
	if (bdir) path = dirname; 
	// 遍历目录并删除文件、目录 
    traverseRemoveDir(path);
}

