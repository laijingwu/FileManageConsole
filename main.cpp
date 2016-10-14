#include <iostream>
#include "FileManagement.h"
using namespace std;

int main(int argc, char *argv[]) {
	FileManagement *pMain;
	if (argc > 1) {
		pMain = new FileManagement(argv[1]);
	} else {
		pMain = new FileManagement();
	
	}
	
	string cmd;
	while (cmd != "exit") {
		pMain->showCmdPrefix();
		cin >> cmd;
		
		if (cmd == "ls") {
			//
		} else if (cmd == "cd") {
			//
		} else if (cmd == "rm") {
			//
		} else if (cmd == "cp") {
			//
		} else if (cmd == "mv") {
			//
		} else if (cmd == "touch") {
			//
		} else if (cmd == "mkdir") {
			//
		} else if (cmd == "rmdir") {
			//
		} else {
			cout << cmd << ": command not found. 'help' -- Get help!" << endl;
		}
	}

    delete pMain;    
	return 0;
}
