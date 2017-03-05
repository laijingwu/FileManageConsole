#include <iostream>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class FileManagement {
    static const size_t DIRPATH_MAX = 255; // 目录路径最大长度 
    char currentDirPath[DIRPATH_MAX]; // 当前目录路径 
    void getCurrentDirPath(char *path); // 获取当前程序路径 
    string getNameFromPath(string path); // 通过路径获取文件名/目录名 
    string getLastDirPath(string path); // 获取上一级目录路径 
    string getStringTime(time_t lt); // 时间戳转字符串 
    string pathRelativePathTo(string path, bool checkExist = true); // 相对地址转换成绝对地址 
    void formatPathToConvert(string &path); // 格式化路径以用于地址转换 
    void traverseRemoveDir(string path); // 删除目录递归函数 
    
public:
    FileManagement();
    FileManagement(string path);
	void showCmdPrefix(); // 输出命令前缀
	bool isExist(const char *path); // 通过路径检测文件/文件夹是否存在 
	bool isDir(const char* path); // 通过路径检测是否为文件夹
	bool isFile(const char *path); // 通过路径检测是否为文件
	void strReplace(string &str, const char *search, const char *replace); // 字符串替换
	
	void cmdLs(); // 列出目录
	void cmdCd(string pathname); // 改变目录 
	void cmdRm(string filename); // 删除文件 
	void cmdCp(string from, string to); // 复制文件 
	void cmdMv(string from, string to); // 移动文件 
	void cmdTouch(string filename); // 新建文件 
	void cmdMkDir(string dirname); // 新建目录 
	void cmdRmDir(string dirname); // 删除目录 
	
};

