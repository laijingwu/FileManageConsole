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
	
    pMain->showCmdPrefix();
    
    delete pMain;    
	return 0;
}
