#include <iostream>
#include <vector>
#include "FileManagement.h"
using namespace std;

int main(int argc, char *argv[]) {
	FileManagement *pMain;
	if (argc > 1) {
		pMain = new FileManagement(argv[1]); // ͨ������·������ 
	} else {
		pMain = new FileManagement(); // ͨ����ǰ����·������ 
	
	}
	
	string cmdFull, cmd;
	vector<string> commandArray; // �ָ�������� 
	while (cmdFull != "exit") {
		commandArray.clear();
		pMain->showCmdPrefix(); // �������ǰ׺
		getline(cin, cmdFull);
		// ĩβ��ӿո����ڷָ�����  
		if (cmdFull.find_last_of(' ') == string::npos || 
		cmdFull.find_last_of(' ') != cmdFull.length() - 1) {
			cmdFull.append(1, ' ');
		}
		
		// �ָ�������� 
		size_t cmdTmp, cmdPos = 0;
		while ((cmdTmp = cmdFull.find(' ', cmdPos)) != string::npos) {
			commandArray.push_back(cmdFull.substr(cmdPos, cmdTmp - cmdPos));
			cmdPos = cmdTmp + 1;
		}
		cmd = commandArray.at(0); // ���� 
		
		if (cmd == "ls") {
			pMain->cmdLs();
		} else if (cmd == "cd") {
			if (commandArray.size() > 1)
				pMain->cmdCd(commandArray.at(1));
			else
				cout << "cd: invalid parameter." << endl;  
		} else if (cmd == "rm") {
			if (commandArray.size() > 1)
				pMain->cmdRm(commandArray.at(1));
			else
				cout << "rm: invalid parameter." << endl;  
		} else if (cmd == "cp") {
			if (commandArray.size() > 2)
				pMain->cmdCp(commandArray.at(1), commandArray.at(2));
			else
				cout << "cp: invalid parameter." << endl;  
		} else if (cmd == "mv") {
			if (commandArray.size() > 2)
				pMain->cmdMv(commandArray.at(1), commandArray.at(2));
			else
				cout << "mv: invalid parameter." << endl; 
		} else if (cmd == "touch") {
			if (commandArray.size() > 1)
				pMain->cmdTouch(commandArray.at(1));
			else
				cout << "touch: invalid parameter." << endl; 
		} else if (cmd == "mkdir") {
			if (commandArray.size() > 1)
				pMain->cmdMkDir(commandArray.at(1));
			else
				cout << "mkdir: invalid parameter." << endl; 
		} else if (cmd == "rmdir") {
			if (commandArray.size() > 1)
				pMain->cmdRmDir(commandArray.at(1));
			else
				cout << "rmdir: invalid parameter." << endl; 
		} else if (cmd == "exit") {
			cout << "bye." << endl;
			break;
		} else if (cmd == "help") {
			cout << endl;
			cout << "********************************" << endl;
			cout << "*    File Management v1.0.1    *" << endl;
			cout << "*        HELP DOCUMENT         *" << endl;
			cout << "********************************" << endl << endl;
			cout << "ls\t--- to list the files in a directory" << endl; 
			cout << "cd\t--- to change the current directory" << endl; 
			cout << "rm\t--- to remove a file" << endl; 
			cout << "cp\t--- to copy a file to another location" << endl; 
			cout << "mv\t--- to move one from one directory to another" << endl; 
			cout << "touch\t--- to create a new file" << endl; 
			cout << "mkdir\t--- to make a new directory" << endl; 
			cout << "rmdir\t--- to remove a directory(warning: delete all the files in the directory)" << endl; 
			cout << "help\t--- to get the help list" << endl; 
			cout << endl << " *** Copyright @ laijingwu *** " << endl << endl;
		} else if (cmd.empty()) { // ������ 
		} else { // ��Ч���� 
			cout << cmd << ": command not found." << endl << "Input 'help' --- Get help!" << endl;
		}
	}
    delete pMain;
	return 0;
}
