#include <iostream>
#include <string>

#include "CommandHandler.h"

using namespace std;

int main(void)
{
	string command("");
	do
	{
		getline(cin, command);
	}
	while(handleCommand(command));
	
	
	return 0;
}
