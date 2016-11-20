#include <iostream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <direct.h>
#include <stdlib.h>
#include <io.h>
// #include <unistd.h> // Linux
// #include <dirent.h>	// Linux
using namespace std;

struct FileNode {
	string fileName;
	bool isDir;
	string addr;
	int i_nlink;//文件的链接数
	FileNode *parent;
	FileNode *child;
	FileNode *sibling_prev;
	FileNode *sibling_next;
};

class FileManagement {
    static const size_t DIRPATH_MAX = 255;
    char currentDirPath[DIRPATH_MAX];
    void getCurrentDirPath(char *path);
    FileNode* root;//
    string getNameFromPath(string path);
    void initRoot(); 
    string getLastDirPath(string path);
    
public:
    FileManagement();
    FileManagement(string path);
	void showCmdPrefix();
	bool isExist(const char *path);
	bool isDir(const char* path);
	void strReplace(string &str, const char *search, const char *replace);
	
	void cmdLs();
	void cmdCd();
	void cmdRm();
	void cmdCp();
	void cmdMv();
	void cmdTouch();
	void cmdMkDir();
	void cmdRmDir();
	
	void traverseDir(string path);
};

