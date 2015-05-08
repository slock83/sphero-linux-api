#ifndef C_HANDLER_H
#define C_HANDLER_H

#include <sstream>

using namespace std;

void init();
int handleCommand(const string& command);
void showHelp();

#endif //C_HANDLER_H
