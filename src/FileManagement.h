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
    static const size_t DIRPATH_MAX = 255; // Ŀ¼·����󳤶� 
    char currentDirPath[DIRPATH_MAX]; // ��ǰĿ¼·�� 
    void getCurrentDirPath(char *path); // ��ȡ��ǰ����·�� 
    string getNameFromPath(string path); // ͨ��·����ȡ�ļ���/Ŀ¼�� 
    string getLastDirPath(string path); // ��ȡ��һ��Ŀ¼·�� 
    string getStringTime(time_t lt); // ʱ���ת�ַ��� 
    string pathRelativePathTo(string path, bool checkExist = true); // ��Ե�ַת���ɾ��Ե�ַ 
    void formatPathToConvert(string &path); // ��ʽ��·�������ڵ�ַת�� 
    void traverseRemoveDir(string path); // ɾ��Ŀ¼�ݹ麯�� 
    
public:
    FileManagement();
    FileManagement(string path);
	void showCmdPrefix(); // �������ǰ׺
	bool isExist(const char *path); // ͨ��·������ļ�/�ļ����Ƿ���� 
	bool isDir(const char* path); // ͨ��·������Ƿ�Ϊ�ļ���
	bool isFile(const char *path); // ͨ��·������Ƿ�Ϊ�ļ�
	void strReplace(string &str, const char *search, const char *replace); // �ַ����滻
	
	void cmdLs(); // �г�Ŀ¼
	void cmdCd(string pathname); // �ı�Ŀ¼ 
	void cmdRm(string filename); // ɾ���ļ� 
	void cmdCp(string from, string to); // �����ļ� 
	void cmdMv(string from, string to); // �ƶ��ļ� 
	void cmdTouch(string filename); // �½��ļ� 
	void cmdMkDir(string dirname); // �½�Ŀ¼ 
	void cmdRmDir(string dirname); // ɾ��Ŀ¼ 
	
};

