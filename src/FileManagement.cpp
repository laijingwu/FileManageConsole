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
	// ֻ���̷� 
	string tmp = path;
	if (path.substr(path.length() - 1) == ":") {
		tmp.append("/");
	}
	// ��֤�Ƿ���ڸ�Ŀ¼
	if (this->isDir(tmp.c_str()))
		path.copy(this->currentDirPath, DIRPATH_MAX, 0);
	else
		this->getCurrentDirPath(this->currentDirPath);
}

// ��ȡ��ǰ����·�� 
void FileManagement::getCurrentDirPath(char *path) {
	getcwd(path, DIRPATH_MAX);
}

// ͨ��·������ļ�/�ļ����Ƿ���� 
bool FileManagement::isExist(const char *path) {
	// if (access(path, 0) != -1)
	struct stat buf = { 0 };
	if (stat(path, &buf) == 0) // ���� 
    	return true;
    else
    	return false;
}

// ͨ��·������Ƿ�Ϊ�ļ��� 
bool FileManagement::isDir(const char *path) {
	if (!strcmp(path, ".."))
		return false;
	
    struct stat buf = { 0 };
	if (stat(path, &buf) == 0 && (buf.st_mode & S_IFDIR)) // Ϊ�ļ��� 
		return true;
	else
		return false;
}

// ͨ��·������Ƿ�Ϊ�ļ�
bool FileManagement::isFile(const char *path) {
    struct stat buf = { 0 };
	if (stat(path, &buf) == 0 && !(buf.st_mode & S_IFDIR)) // ��Ϊ�ļ��� 
		return true;
	else
		return false;
}

// �������ǰ׺ 
void FileManagement::showCmdPrefix() {
	cout << this->currentDirPath << "> ";
}

// �ַ����滻 
void FileManagement::strReplace(string &str, const char *search, const char *replace) {
	int pos = 0;
	while ((pos = str.find(search, pos)) >= 0) {
		str.replace(pos, strlen(search), replace);
	    pos += strlen(replace);
	}
}

// ͨ��·����ȡ�ļ���/Ŀ¼�� 
string FileManagement::getNameFromPath(string path) {
	if (path.substr(path.length() - 1) == ":")
		return string();
	else
		return path.substr(path.find_last_of("/") + 1);
}

// ��ȡ��һ��Ŀ¼·�� 
string FileManagement::getLastDirPath(string path) {
	int pos = path.find_last_of("/");
	if (pos != -1) {
		return path.substr(0, pos);
	} else {
		return path;
	}
}

// ʱ���ת�ַ��� 
string FileManagement::getStringTime(time_t lt) {
	time_t tick = lt;
	char timeStr[100] = {0};
	struct tm *ptr = localtime(&tick);
	strftime(timeStr, sizeof(timeStr), "%Y/%m/%d  %H:%M:%S", ptr);
	return string(timeStr);
}

// �г�Ŀ¼
void FileManagement::cmdLs() {
	cout << endl << "   Directory: " << this->currentDirPath << endl << endl;
	
	string path = this->currentDirPath;
	_finddata_t filefind;
	string curr = path + "/*.*"; // ���ڱ����ļ��� 
	long handle;

	unsigned long n_dir, n_file;	// Ŀ¼���ļ����� 
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
		(filefind.attrib >= 48 && filefind.attrib <= 55)) { // Ŀ¼ 
			n_dir++;
			cout << "<DIR>" << "\t";
		} else { // �ļ� 
			n_file++;
			cout << "\t" << filefind.size << " Byte";
		}
		cout << "\t" << filefind.name << endl;
    }
    cout << "\t\t" << n_file << " files   " << n_dir << " directories" << endl << endl;
    _findclose(handle);
}

// ��ʽ��·�������ڵ�ַת�� 
void FileManagement::formatPathToConvert(string &path) {
	// ͳһĿ¼�ָ���Ϊ / 
	this->strReplace(path, "\\\\", "/");
	this->strReplace(path, "\\", "/");
	this->strReplace(path, "//", "/");
	// ȥ��ͷ���ķָ��� 
	if (path.find_first_of("/") == 0) {
		path = path.substr(1, path.length() - 1);
	}
} 

// ��Ե�ַת���ɾ��Ե�ַ 
string FileManagement::pathRelativePathTo(string path, bool checkExist) {
	// ĩβ���б�����ڷָ� 
	if (path.find_last_of("/") != path.length() - 1) {
		path.append("/"); 
	}
	
	vector<string> path_part;
	
	// �ֿ�·�������� 
	size_t pathTmp, pathPos = 0;
	while ((pathTmp = path.find('/', pathPos)) != string::npos) {
		path_part.push_back(path.substr(pathPos, pathTmp - pathPos));
		pathPos = pathTmp + 1;
	}
	
	string strTmp(this->currentDirPath);
	for (vector<string>::iterator iter = path_part.begin(); iter != path_part.end(); iter++) {
		if (*iter == "..") { // ��һ�� 
			strTmp = getLastDirPath(strTmp);
			if (strTmp.empty()) {
				return string();
			}
		} else if (*iter == ".") { // ��ǰĿ¼���� 
			continue;
		} else {
			// ƴ��·���ַ��� 
			if (strTmp.length() < 3 || strTmp.substr(strTmp.length() - 2, 1) != ":")
				strTmp.append("/");
			strTmp.append(*iter);
			if (this->isExist(strTmp.c_str()) || checkExist == false) { // ������ 
				continue;
			} else {
				return string();
			}
		}
	}
	return strTmp;
} 

// �ı�Ŀ¼ 
void FileManagement::cmdCd(string pathname) {
	// ��ʽ��·������ԡ�����ת���� 
	formatPathToConvert(pathname);
	string path = this->pathRelativePathTo(pathname, false);
	if (path.substr(path.length() - 1) == ":") {
		path.append("/");
	}
	
	//cout << path << "|" << pathname << "|" << endl;
	bool bdir = this->isDir(pathname.c_str());
	//cout << bdir << this->isDir(path.c_str());
	if (!this->isDir(path.c_str()) && !bdir) { // ��֤�Ƿ���ڸ�Ŀ¼
		cout << "Cannot find the specified path." << endl << endl;
		return;
	}
	if (bdir && pathname.length() > 1 && pathname.substr(1, 1) == ":") path = pathname;

	// ˢ�µ�ǰĿ¼ 
	memset(this->currentDirPath, 0, DIRPATH_MAX);
	path.copy(this->currentDirPath, DIRPATH_MAX, 0);
}

// ɾ���ļ� 
void FileManagement::cmdRm(string filename) {
	// ��ʽ��·������ԡ�����ת���� 
	formatPathToConvert(filename);
	string path = this->pathRelativePathTo(filename, false);

	bool bfile = this->isFile(filename.c_str());
	if (!this->isFile(path.c_str()) && !bfile) { // ��֤�Ƿ����
		cout << "File does not exist." << endl << endl;
		return;
	}
	if (bfile) path = filename;
	// ɾ���ļ� 
	if (unlink(path.c_str()) < 0) cout << "Delete failed. Maybe it is permission denied." << endl << endl;
}

// �����ļ� 
void FileManagement::cmdCp(string from, string to) {
	// ��ʽ��·������ԡ�����ת���� 
	formatPathToConvert(from);
	string frompath = this->pathRelativePathTo(from);
	formatPathToConvert(to);
	string topath = this->pathRelativePathTo(to, false);
	
	bool bfile = this->isFile(from.c_str());
	if (frompath.empty() && !bfile) { // ��֤�Ƿ����
		cout << from << " does not exist." << endl << endl;
		return;
	}
	if (bfile) frompath = from;
	
	// �ж�Ŀ�ĵ�ַ��Ŀ¼�Ƿ���� 
	string lastDirPath = this->getLastDirPath(to.c_str());
	bool bdir = this->isDir(lastDirPath.c_str());
	lastDirPath = this->getLastDirPath(topath.c_str());
	bool bdir_xd = this->isDir(lastDirPath.c_str());
	if (!bdir_xd && !bdir) { // ��֤�Ƿ����
		cout << "Destination directory does not exist." << endl << endl;
		return;
	}
	if (bdir) topath = to;
	
	ifstream in;
	ofstream out;
	in.open(frompath.c_str(), ios::binary); // ��Դ�ļ�
	if (in.fail()) {
		// ��Դ�ļ�ʧ��
		cout << "Cannot open source file." << endl << endl;
		in.close();
		return;
	}
	out.open(topath.c_str(), ios::binary); // ����Ŀ���ļ� 
	if (out.fail()) {
		// �����ļ�ʧ��
		cout << "Cannot create new file." << endl << endl;
	} else {
		// �����ļ�
		out << in.rdbuf();
	}
	out.close();
	in.close();
}

// �ƶ��ļ� 
void FileManagement::cmdMv(string from, string to) {
	this->cmdCp(from, to); // �����ļ� 
	this->cmdRm(from); // ɾ��ԭ���ļ� 
}

// �½��ļ� 
void FileManagement::cmdTouch(string filename) {
	// ��ʽ��·������ԡ�����ת���� 
	formatPathToConvert(filename);
	string path = this->pathRelativePathTo(filename, false);
	string lastDirPath = this->getLastDirPath(path.c_str());
	
	// ʹ�����·��ת�����ľ���·�� 
	if (this->isDir(lastDirPath.c_str())) {
		if (this->isExist(path.c_str())) {
			cout << "File or directory already exists." << endl << endl;
			return;
		}
		// �����ļ� 
		FILE *fp = fopen(path.c_str(), "w+");
    	fclose(fp);
	} else { // ʹ�þ���·��
		lastDirPath = this->getLastDirPath(filename.c_str());
		if (this->isDir(lastDirPath.c_str())) {
			if (this->isExist(filename.c_str())) {
				cout << "File or directory already exists." << endl << endl;
				return;
			}
			// �����ļ� 
			FILE *fp = fopen(filename.c_str(), "w+");
    		fclose(fp);
		} else {
			cout << "Destination directory does not exist." << endl << endl;
			return;
		}
	}
}

// �½�Ŀ¼ 
void FileManagement::cmdMkDir(string dirname) {
	// ��ʽ��·������ԡ�����ת���� 
	formatPathToConvert(dirname);
	string path = this->pathRelativePathTo(dirname, false);
	string lastDirPath = this->getLastDirPath(path.c_str());
	
	// ʹ�����·��ת�����ľ���·�� 
	if (this->isDir(lastDirPath.c_str())) {
		if (this->isDir(path.c_str())) {
			cout << "Destination directory already exists." << endl << endl;
			return;
		}
		// ����Ŀ¼ 
		if (mkdir(path.c_str()) < 0) cout << "Failed to create directory. Maybe it is permission denied." << endl << endl;
	} else { // ʹ�þ���·��
		lastDirPath = this->getLastDirPath(dirname.c_str());
		if (this->isDir(lastDirPath.c_str())) {
			if (this->isDir(dirname.c_str())) {
				cout << "Destination directory already exists." << endl << endl;
				return;
			}
			// ����Ŀ¼ 
			if (mkdir(dirname.c_str()) < 0) cout << "Failed to create directory. Maybe it is permission denied." << endl << endl;
		} else {
			cout << "The last directory of destination directory does not exist." << endl << endl;
			return;
		}
	}
}

// ɾ��Ŀ¼�ݹ麯�� 
void FileManagement::traverseRemoveDir(string path) {
	_finddata_t fileDir;
	string curr = path + "/*.*";
	long lfDir;
     
    // Ŀ¼��û���ļ� 
    if((lfDir = _findfirst(curr.c_str(), &fileDir)) == -1l) {
    	return;
    }
	
	string tmp;
	// �����ļ����������ļ� 
	do {
		// ȥ��.. �� . 
		if (!strcmp(fileDir.name, "..") || !strcmp(fileDir.name, ".")) {
			continue;
		}
		// �ж�Ŀ¼ �ݹ� 
		if ((fileDir.attrib >= 16 && fileDir.attrib <= 23) || 
		(fileDir.attrib >= 48 && fileDir.attrib <= 55)) {
			this->traverseRemoveDir(path + "/" + fileDir.name);
			continue;
		}
		
		tmp = path;
		tmp.append("/");
		tmp.append(fileDir.name);
		if (unlink(tmp.c_str()) < 0) { // ɾ���ļ� 
			cout << "Failed to delete files in the directory. Maybe it is permission denied." << endl << endl;
			return;
		}
	} while (_findnext(lfDir, &fileDir) == 0);
    _findclose(lfDir);
    if (rmdir(path.c_str()) < 0) { // ɾ���ļ��� 
    	cout << "Failed to delete directory. Maybe it is permission denied." << endl << endl;
    	return;
    } 
}

// ɾ��Ŀ¼ 
void FileManagement::cmdRmDir(string dirname) {
	// ��ʽ��·������ԡ�����ת���� 
	formatPathToConvert(dirname);
	string path = this->pathRelativePathTo(dirname, false);
	
	bool bdir = this->isDir(dirname.c_str());
	if (!this->isDir(path.c_str()) && !bdir) {
		cout << "Directory does not exist." << endl << endl;
		return;
	}
	if (bdir) path = dirname; 
	// ����Ŀ¼��ɾ���ļ���Ŀ¼ 
    traverseRemoveDir(path);
}

