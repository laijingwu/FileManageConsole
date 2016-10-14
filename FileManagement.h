#include <iostream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <direct.h>
// #include <unistd.h> // Linux
using namespace std;

class FileManagement {
    static const size_t DIRPATH_MAX = 255;
    char currentDirPath[DIRPATH_MAX];
    void getCurrentDirPath(char *path);
    
public:
    FileManagement();
    FileManagement(string path);
	void showCmdPrefix();
	bool isExist(const char *path);
	bool isDir(const char* path);
	void strReplace(string &str, const char *search, const char *replace);
	
	/*void cmdLs();
	void cmdCd();
	void cmdRm();
	void cmdCp();
	void cmdMv();
	void cmdTouch();
	void cmdMkDir();
	void cmdRmDir();*/
};

