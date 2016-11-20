#include "FileManagement.h"

// ͨ����ǰ����·������ 
FileManagement::FileManagement() : currentDirPath() {
	this->getCurrentDirPath(this->currentDirPath);
	this->initRoot(); 
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
	
	this->initRoot(); 
}

FileNode* CreateFileNode(string filename, bool isdir, int i_nlink, string path)  {
    FileNode* node = new FileNode; //������ռ�
	// ��ʼ����Ӧ����
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


// ��ʼ����ǰĿ¼ �������� 
void FileManagement::initRoot() {
	this->root = CreateFileNode(this->getNameFromPath(this->currentDirPath), true, 0, this->currentDirPath);
	// TODO: ѭ������һ��Ŀ¼ ��ǰĿ¼ ��һ��Ŀ¼ ��ʹ������ṹ 
	this->root->parent = NULL;
	this->root->child = NULL;
	this->root->sibling_prev = this->root->sibling_next = NULL;
}

// ��ȡ��ǰ����·�� 
void FileManagement::getCurrentDirPath(char *path) {
	getcwd(path, DIRPATH_MAX);
}

// ͨ��·������ļ�/�ļ����Ƿ���� 
bool FileManagement::isExist(const char *path) {
	//if (access(path, 0) != -1)
	struct stat buf = { 0 };
	if (stat(path, &buf) == 0)
    	return true;
    else
    	return false;
}

// ͨ��·������Ƿ�Ϊ�ļ��� 
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
		(filefind.attrib >= 48 && filefind.attrib <= 55)) { // Ŀ¼ 
			curr = path + "/" + filefind.name;
			cout << curr << "(dir)" << endl;
		} else { // �ļ� 
			cout << path + "/" + filefind.name << endl;
		}
    }
    _findclose(handle);
} 

// �г�Ŀ¼ 
void FileManagement::cmdLs() {
	//cout << this->getName("D:");
	//cout << this->getLastDirPath(this->currentDirPath); 
	this->traverseDir(this->currentDirPath);
}

// �ı�Ŀ¼ 
void FileManagement::cmdCd() {
	//
}

// ɾ���ļ� 
void FileManagement::cmdRm() {
	//
}

//  �����ļ� 
void FileManagement::cmdCp() {
	// 
}

// �ƶ��ļ� 
void FileManagement::cmdMv() {
	//
}

// �½��ļ� 
void FileManagement::cmdTouch() {
	//
}

// �½�Ŀ¼ 
void FileManagement::cmdMkDir() {
	//
}

// ɾ��Ŀ¼ 
void FileManagement::cmdRmDir() {
	//
}
