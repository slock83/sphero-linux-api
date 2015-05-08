/*************************************************************************
	CommandHandler  -  Sphero control applicaiton -- command interpreter
							 -------------------
	started                : 08/05/2015
*************************************************************************/

#ifndef C_HANDLER_H
#define C_HANDLER_H

//-------------------------------------------------------- System includes
#include <sstream>
using namespace std;



//-------------------------------------------------------------- Functions
void init();
int handleCommand(const string& command);
void showHelp();

#endif //C_HANDLER_H
