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
	
	string cmdFull, cmd;
	while (cmdFull != "exit") {
		pMain->showCmdPrefix();
		getline(cin, cmdFull);
		if (cmdFull.find_last_of(' ') == cmdFull.length() - 1) {
			cmdFull.append(1, ' ');
		}
		cmd = cmdFull.substr(0, cmdFull.find_first_of(' '));
		
		if (cmd == "ls") {
			pMain->cmdLs();
		} else if (cmd == "cd") {
			pMain->cmdCd();
		} else if (cmd == "rm") {
			pMain->cmdRm();
		} else if (cmd == "cp") {
			pMain->cmdCp();
		} else if (cmd == "mv") {
			pMain->cmdMv();
		} else if (cmd == "touch") {
			pMain->cmdTouch();
		} else if (cmd == "mkdir") {
			pMain->cmdMkDir();
		} else if (cmd == "rmdir") {
			pMain->cmdRmDir();
		} else if (cmd == "exit") {
			cout << "quit." << endl;
		} else if (cmd.empty()) {
		} else {
			cout << cmd << ": command not found. 'help' -- Get help!" << endl;
		}
	}

    delete pMain;
	return 0;
}
